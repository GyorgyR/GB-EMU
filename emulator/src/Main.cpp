#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Decoder.h"
#include "ROM.h"
#include "Processor.h"
#include "RegisterBank.h"
#include "../include/Helper.h"

using std::cout;
using std::endl;
using std::cin;

const char *bootstrap_rom_path = "data/DMG_ROM.bin";

int main(int argc, char *argv[])
{
    cout << "Welcome to the Game Boy ROM disassembly tool" << endl;
    //Load the Bootstrap ROM
    if (argc != 2) {
        cout << "Usage: runner file/to/rom.gb\n";
    } //if
    ROM bootstrap_rom(bootstrap_rom_path);
    ROM rom(argv[1]);

    bool is_running = true;

    while (is_running) {
        cout << "[ \u001b[34;1mGameBoy\u001b[0m ] $ ";
        std::string command;
        cin >> command;

        if (command == "print-rom") {
            for (int i = 0; i < rom.rom_file_size; ++i)
                printf("0x%04X: 0x%02X\n", i, rom.GetByteAt(i));
        } else if (command == "dump-loaded_rom") {
            //This is not ideal, in the future ROM should implement ToString()
            std::string file;
            cin >> file;

            FILE* log;
            log = fopen(file.c_str(), "w");

            for (int i = 0; i < rom.rom_file_size; ++i)
                fprintf(log, "0x%04X: 0x%02X\n", i, rom.GetByteAt(i));

            fclose(log);

            cout << "Dump done.\n";

        }
        else if (command == "disassemble") {
            /*
            std::string start;
            cin >> start;
            int address;
            if (start != "a")
               address = strtoul(start.c_str(), NULL,  16);
            else
                address = 0x150;

            printf("Starting from address: 0x%04X\n", address);

            //Create instruction decoder
            Decoder cpu();

            while (address > 0) {
                address = cpu.decodeInstr(address);
            }
             */
            
        }
        else if (command == "start") {
            RAM::InitRam(&bootstrap_rom);
            RAM::SetDebugStream(fopen("ram-log.txt", "w+"));
            Processor cpu;
            cpu.StartCPULoop();
        }
        else {
            cout << command;
            is_running = false;
        }
    }

} //main
