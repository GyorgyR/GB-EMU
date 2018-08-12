#include <fstream>
#include <iostream>
#include <string>
#include "Processor.h"

using std::cout;
using std::endl;
using std::cin;

int main(int argc, char *argv[])
{
    cout << "Welcome to the Game Boy ROM disassembly tool" << endl;
    int rom_file_size = 0;
    uint8_t* rom;
    if (argc == 2) {
        std::ifstream rom_file(argv[1], std::ios::in | std::ios::binary);

        if (!rom_file) {
            fprintf(stderr, "Error opening file: %s\n", argv[1]);
            exit(1);
        }

        rom_file.unsetf(std::ios::skipws);

        rom_file.seekg(0, std::ios::end);
        rom_file_size = rom_file.tellg();
        rom_file.seekg(0, std::ios::beg);

        rom = new uint8_t[rom_file_size];

        rom_file.read(reinterpret_cast<char*>(rom), rom_file_size);

        rom_file.close();
    } //if

    //Create instruction decoder
    Processor cpu(rom);

    bool is_running = true;

    while (is_running) {
        cout << "[ \u001b[34;1mGameBoy\u001b[0m ] $ ";
        std::string command;
        cin >> command;

        if (command == "print-rom") {
            for (int i = 0; i < rom_file_size; ++i)
                    printf("0x%04X: 0x%02X\n", i, rom[i]);
        }
        else if (command == "dump-rom") {
            std::string file;
            cin >> file;

            FILE* log;
            log = fopen(file.c_str(), "w");

            for (int i = 0; i < rom_file_size; ++i)
                fprintf(log, "0x%04X: 0x%02X\n", i, rom[i]);

            fclose(log);

            cout << "Dump done.\n";

        }
        else if (command == "disassemble") {
            std::string start;
            cin >> start;
            int address = stoi(start);

            cout << "Starting from address: " << address << endl;

            while (address > 0) {
                address = cpu.DecodeInstr(address);
            }
            
        }
        else {
            cout << command;
            is_running = false;
        }
    }

} //main
