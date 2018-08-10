#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Welcome to the Game Boy ROM disassembly tool" << endl;

    unsigned char rom[32000];

    ifstream rom_file;
    rom_file.open(argv[1], ios::in | ios::binary);

    if (rom_file.is_open()) {
        for (int i = 0; i < 32000; i++) {
            char temp;
            rom_file.read(&temp, 1);
            rom[i] = temp;
        }

        rom_file.close();

        printf("ROM info: %02x\n", rom[0x014D]);
    }
} //main
