//
// Created by gyorgy on 13/10/18.
//

#define OAMSEARCHCYCLES 80
#define CLOCKSPERLINE OAMSEARCHCYCLES+172+204
#define LINES 153

#include "../include/PPU.h"
#include "../include/VideoRegisters.h"
#include "../include/MMU.h"
#include "../include/Types.h"
#include "../include/Helper.h"
#include "../include/Configuration.h"
#include "../include/EventMiddleware.h"
#include "../include/RegisterBank.h"

unsigned int PPU::currentLine = 0;
unsigned int PPU::currentLineCycle = 0;
unsigned int PPU::currentPixel = 0;
unsigned int PPU::fifoFetchState = 0;
unsigned int PPU::PPUState = 0;
int PPU::lastTileNo = 0;
uint8 PPU::lastByte1 = 0;
int PPU::decodedBytes[8];
std::queue<FifoElement> PPU::fifo;
Window *PPU::window = nullptr;
uint16 PPU::fetcherLastAddr = 0;
int PPU::discardedPixels = 0;
OAMEntry *OAMEntrysThisLine[10];
int OAMEntriesFound = 0;
bool wasLastEntryXZero = true;
int ColToTriggerOn = -1;
int objsDrawn = 0;
TileTypes fetcherState = BG;

PPU::PPU() {}

PPU::~PPU() {}

void PPU::Update(int cycles)
{
    for (int iteration = 0; iteration < cycles; iteration += 4) {

        if (++currentLineCycle > CLOCKSPERLINE) {
            ++currentLine;
            currentLineCycle = 0;
            discardedPixels = 0;
            OAMEntriesFound = 0;
            ColToTriggerOn = -1;
            objsDrawn = 0;
            PPUState = 0;
            VideoRegisters::LCDStatMode(2);

            if (currentLine == window->height) {
                window->UpdateScreen();
                PPUState = 3;
                VideoRegisters::LCDStatMode(1);
                RegisterBank::SetBitInIF(0);
            } else if (currentLine > LINES) {
                currentLine = 0;
                PPUState = 0;
                VideoRegisters::LCDStatMode(2);
            }
            VideoRegisters::LCDYCoordinate(currentLine);

            fetcherLastAddr =
                    VideoRegisters::BGTileMapBaseAddr() +
                    ((currentLine + VideoRegisters::ScrollPosY()) / 8) * 32
                    ;
        }

        switch (PPUState) {
            case 0: { //OAMSEARCH
                if (OAMEntriesFound < 10) {
                    int currentEntryNo = currentLineCycle / 2;
                    if (currentLineCycle % 2 == 0) {
                        wasLastEntryXZero = VideoRegisters::OAMEntyArray[currentEntryNo].PosX == 0;
                    }
                    else if (!wasLastEntryXZero) {
                        uint8 posY = VideoRegisters::OAMEntyArray[currentEntryNo].PosY;
                        if (currentLine + 16 >= posY && currentLine + 16 < posY + VideoRegisters::TileHeight()) {
                            OAMEntrysThisLine[OAMEntriesFound++] = &VideoRegisters::OAMEntyArray[currentEntryNo];
                            if (ColToTriggerOn < 0) ColToTriggerOn = VideoRegisters::OAMEntyArray[currentEntryNo].PosX - 8;
                        }
                    }
                }

                if (currentLineCycle == OAMSEARCHCYCLES - 1) {
                    PPUState = 1;
                    VideoRegisters::LCDStatMode(3);
                }
                break;
            }
            case 1: { //Pixel Draw
                //Check for a window
                if (VideoRegisters::IsWindowEnabled) {
                    if (
                            currentLine >= VideoRegisters::WindowPosY() &&
                            currentPixel >= VideoRegisters::WindowPosX() - 7
                            ) {
                        //fifo = std::queue<int>();
                        Helper::Log("Turn on window");
                        exit(1);
                    }
                }
                if (currentLineCycle % 2 == 1) FifoFetch();
                if (fifo.size() > 8 && fetcherState != OBJ) FifoPush();
                if (currentPixel == window->width) {
                    PPUState = 2;
                    VideoRegisters::LCDStatMode(0);
                    currentPixel = 0;
                    fifo = std::queue<FifoElement>();
                    fifoFetchState = 0;
                }
                break;
            }
            case 2: { //H-BLANK
                break;
            }
            case 3: { //V-BLANK
                break;
            }
            default: { //ERROR
                Helper::Log("PPU ERROR -- INVALID STATE");
                exit(1);
            }
        }
    }
}

inline void PPU::PopulateFifo()
{
    switch (fetcherState) {
        case BG: {
            if (fifo.size() <= 8) {
                for (int i = 7; i >= 0; --i) {
                    FifoElement newElem;
                    newElem.colour = decodedBytes[i];
                    newElem.source = fetcherState;
                    fifo.push(newElem);
                }
                fifoFetchState = 0;
            }
            else {
                fifoFetchState = 3;
            }

            break;
        }
        case OBJ: {
            if (fifo.size() <= 8) {
                for (int i = 7; i >= 0; --i) {
                    FifoElement newElem;
                    newElem.colour = decodedBytes[i];
                    newElem.source = fetcherState;
                    fifo.push(newElem);
                }
                fifoFetchState = 0;
                break;
            }
            FifoElement presentElem;
            int sizeDiff = fifo.size() - 8;
            for (int i = 7; i >= 0; --i) {
                presentElem = fifo.front(); fifo.pop();
                if (presentElem.source == OBJ) {
                    fifo.push(presentElem);
                }
                else if (presentElem.source == BG){
                    if (OAMEntrysThisLine[objsDrawn - 1]->Priority && presentElem.colour != 0) {
                        fifo.push(presentElem);
                    }
                    else if (decodedBytes[i] == 0) {
                        fifo.push(presentElem);
                    }
                    else {
                        FifoElement elem;
                        elem.colour = decodedBytes[i];
                        elem.source = fetcherState;
                        fifo.push(elem);
                    }
                }
            }
            for (int j = 0; j < sizeDiff; ++j) {
                FifoElement elem = fifo.front(); fifo.pop();
                fifo.push(elem);
            }
            fifoFetchState = 0;
            fetcherState = BG;
            break;
        }
        case WINDOW: {
            Helper::Log("Cannot populate fifo from window");
            exit(1);
        }
    }
;
}

void PPU::FifoFetch()
{
    Helper::PPULog("FETCH\n");
    switch (fifoFetchState) {
        case 0: { //fetch
            if (fetcherState == OBJ) {
                lastTileNo = OAMEntrysThisLine[objsDrawn++]->SpriteNo;
            }
            else {
                lastTileNo = MMU::ReadByteAt(fetcherLastAddr++);
            }
            ++fifoFetchState;
            return;
        }
        case 1: { //byte 1 fetch
            uint16 address = currentTileRowBaseAddr();
            uint8 byte1 = MMU::ReadByteAt(address);
            lastByte1 = byte1;
            ++fifoFetchState;
            return;
        }
        case 2: { //byte 2 fetch, decode and store to fifo
            uint16 address = currentTileRowBaseAddr() + 1;
            uint8 byte2 = MMU::ReadByteAt(address);

            for (int i = 0; i < 8; ++i) {
                decodedBytes[i] = Helper::IsBitSet(byte2, i) ? 2 : 0;
                decodedBytes[i] += Helper::IsBitSet(lastByte1, i) ? 1 : 0;
            }

            PopulateFifo();
            return;
        }
        case 3: { // idle (put into fifo if possible)
            PopulateFifo();
            return;
        }
        default: //ERROR
            Helper::Log("FIFO FETCH ERROR -- INVALID STATE");
            exit(1);
    }

}

uint16 PPU::currentTileRowBaseAddr()
{
    switch (fetcherState) {
        case BG: {
            //Get base address
            uint16 baseAddr = VideoRegisters::BGTileDataBaseAddr();
            if (baseAddr == 0x8000 || lastTileNo >= 0x80) baseAddr = 0x8000;
            else baseAddr = 0x9000;

            //Calculate tile address
            baseAddr += lastTileNo << 4;

            //Add the current row (in the tile) times 2 to the tile base to get row base
            baseAddr += ((currentLine + VideoRegisters::ScrollPosY()) % 8) * 2;
            return baseAddr;
        }
        case OBJ: {
            //TODO flips
            uint16 baseAddr = 0x8000 + (lastTileNo << 4);
            //Add the current row times 2
            uint16 lineInTile = currentLine - (OAMEntrysThisLine[objsDrawn- 1]->PosY - 16);
            baseAddr += (lineInTile) * 2;
            return baseAddr;

        }
        case WINDOW: {
            Helper::Log("WINDOW NOT IMPLEMENTED");
            exit(1);
        }
    }
    return -1;
}

void PPU::FifoPush()
{
    if (currentPixel == ColToTriggerOn) {
        fetcherState = OBJ;

        int lastTrigger = ColToTriggerOn;
        for (int i = 1; i < OAMEntriesFound - objsDrawn && ColToTriggerOn <= lastTrigger; ++i) {
            ColToTriggerOn = OAMEntrysThisLine[objsDrawn + i]->PosX - 8;
        }

        if (currentPixel == ColToTriggerOn) ColToTriggerOn = -1;

        if (fifoFetchState != 0) --fetcherLastAddr;
        fifoFetchState = 0;
        return;
    }

    FifoElement colour = fifo.front();
    fifo.pop();

    if (discardedPixels < VideoRegisters::ScrollPosX()) ++discardedPixels;
    else window->DrawPixel(currentPixel++, currentLine, VideoRegisters::GetBGColour(colour.colour));

}

void PPU::SetWindow(Window *currWindow)
{
    window = currWindow;
}

