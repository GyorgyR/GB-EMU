//
// Created by gyorgy on 11/08/18.
//

#undef DEBUG
#undef REGISTERS

#define INSTPERSEC 4194304
#define FPS 60

#include "Processor.h"
#include "../include/Processor.h"
#include "../include/RegisterBank.h"
#include "../include/Helper.h"
#include "../include/PPU.h"
#include "../include/Types.h"

FILE *debugStream = stdout;

Processor::~Processor()
{
}

Processor::Processor()
{
}

inline uint16 getNextTwoBytes()
{
    uint8 first = RAM::ReadByteAt(++RegisterBank::PC);
    uint8 second = RAM::ReadByteAt(++RegisterBank::PC);
    return Helper::ConcatTwoBytes(second, first);
}

inline int baseLoadReg(uint8 *destination, uint8 value)
{
    *destination = value;
    return 4;
}

inline int baseSub(uint8 value)
{
    RegisterBank::SetH((RegisterBank::A & 0b111) > (value & 0b111));
    RegisterBank::SetC(RegisterBank::A > value);

    RegisterBank::A -= value;

    RegisterBank::SetZ(RegisterBank::A == 0);
    RegisterBank::SetN(true);

    return 4;
}

inline int baseDec(uint8 *reg)
{
    RegisterBank::SetH(((*reg) & 0b000) > 0);

    --(*reg);

    RegisterBank::SetZ((*reg) == 0);
    RegisterBank::SetN(true);
    return 4;
}

inline int op0x00()
{
    Helper::CPULog("NOP\n");
    return 1;
}

inline int op0x01()
{
    Helper::CPULog("Op not implemented: 0x01\n");
    return -1;
}

inline int op0x02()
{
    Helper::CPULog("Op not implemented: 0x02\n");
    return -1;
}

inline int op0x03()
{
    Helper::CPULog("Op not implemented: 0x03\n");
    return -1;
}

inline int op0x04()
{
    RegisterBank::SetH((RegisterBank::B & 0b1111) == 0b1111);
    ++RegisterBank::B;

    RegisterBank::SetZ(RegisterBank::B == 0);
    RegisterBank::SetN(false);

    Helper::CPULog("INC\tB\n");
    return 4;
}

inline int op0x05()
{
    Helper::CPULog("DEC\tB\n");
    return baseDec(&RegisterBank::B);
}

inline int op0x06()
{
    RegisterBank::B = RAM::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("LD\tB, 0x%02X\n", RegisterBank::B);
    return 8;
}

inline int op0x07()
{
    Helper::CPULog("Op not implemented: 0x07\n");
    return -1;
}

inline int op0x08()
{
    Helper::CPULog("Op not implemented: 0x08\n");
    return -1;
}

inline int op0x09()
{
    Helper::CPULog("Op not implemented: 0x09\n");
    return -1;
}

inline int op0x0A()
{
    Helper::CPULog("Op not implemented: 0x0A\n");
    return -1;
}

inline int op0x0B()
{
    Helper::CPULog("Op not implemented: 0x0B\n");
    return -1;
}

inline int op0x0C()
{
    RegisterBank::SetH((RegisterBank::C & 0b1111) == 0b1111);

    ++RegisterBank::C;

    RegisterBank::SetZ(RegisterBank::C == 0);
    RegisterBank::SetN(false);

    Helper::CPULog("INC\tC\n");
    return 4;
}

inline int op0x0D()
{
    Helper::CPULog("DEC\tC\n");
    return baseDec(&RegisterBank::C);
}

inline int op0x0E()
{
    RegisterBank::C = RAM::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("LD\tC, 0x%02X\n", RegisterBank::C);
    return 8;
}

inline int op0x0F()
{
    Helper::CPULog("Op not implemented: 0x0F\n");
    return -1;
}

inline int op0x10()
{
    Helper::CPULog("Op not implemented: 0x10\n");
    return -1;
}

inline int op0x11()
{
    RegisterBank::DE(getNextTwoBytes());
    Helper::CPULog("LD\tDE, 0x%04X\n", RegisterBank::DE());
    return 12;
}

inline int op0x12()
{
    Helper::CPULog("Op not implemented: 0x12\n");
    return -1;
}

inline int op0x13()
{
    RegisterBank::DE(RegisterBank::DE() + 1);
    Helper::CPULog("INC\tDE(0x%04X)\n", RegisterBank::DE());
    return 8;
}

inline int op0x14()
{
    Helper::CPULog("Op not implemented: 0x14\n");
    return -1;
}

inline int op0x15()
{
    Helper::CPULog("DEC\tD\n");
    return baseDec(&RegisterBank::D);
}

inline int op0x16()
{
    uint8 value = RAM::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("LD\tD, 0x%02X\n", value);
    return baseLoadReg(&RegisterBank::D, value) + 4;
}

inline int op0x17()
{
    bool wasCarrySet = RegisterBank::IsCSet();
    RegisterBank::SetC(RegisterBank::A & 0b10000000);

    RegisterBank::A <<= 1;
    if (wasCarrySet) ++RegisterBank::A;

    RegisterBank::SetZ(RegisterBank::A == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);

    Helper::CPULog("RLA sets carry: %s\n", RegisterBank::IsCSet() ? "true" : "false");
    return 4;
}

inline int op0x18()
{
    int8_t value = RAM::ReadByteAt(++RegisterBank::PC);
    RegisterBank::PC += value;
    Helper::CPULog("JR\t%d\n", value);
    return 12;
}

inline int op0x19()
{
    Helper::CPULog("Op not implemented: 0x19\n");
    return -1;
}

inline int op0x1A()
{
    RegisterBank::A = RAM::ReadByteAt(RegisterBank::DE());
    Helper::CPULog("LD\tA, [DE]\n");
    return 8;
}

inline int op0x1B()
{
    Helper::CPULog("Op not implemented: 0x1B\n");
    return -1;
}

inline int op0x1C()
{
    Helper::CPULog("Op not implemented: 0x1C\n");
    return -1;
}

inline int op0x1D()
{
    Helper::CPULog("DEC\tE\n");
    return baseDec(&RegisterBank::E);
}

inline int op0x1E()
{
    uint8 value = RAM::ReadByteAt(++RegisterBank::PC);
    RegisterBank::E = value;
    Helper::CPULog("LD\tE, 0x%02X\n", value);
    return 8;
}

inline int op0x1F()
{
    Helper::CPULog("Op not implemented: 0x1F\n");
    return -1;
}

inline int op0x20()
{
    int cycles = 8;
    int8_t value = RAM::ReadByteAt(++RegisterBank::PC);
    if (!RegisterBank::IsZSet()) {
        RegisterBank::PC += value;
        cycles += 4;
    }
    Helper::CPULog("JR\tNZ, %d\n", value);
    return cycles;
}

inline int op0x21()
{
    RegisterBank::HL(getNextTwoBytes());
    Helper::CPULog("LD\tHL, 0x%04X\n", RegisterBank::HL());
    return 12;
}

inline int op0x22()
{
    RAM::WriteByteAt(RegisterBank::HL(), RegisterBank::A);
    RegisterBank::HL(RegisterBank::HL() + 1);
    Helper::CPULog("LD\t[HL++], A\n");
    return 8;
}

inline int op0x23()
{
    RegisterBank::HL(RegisterBank::HL() + 1);
    Helper::CPULog("INC\tHL\n");
    return 8;
}

inline int op0x24()
{
    RegisterBank::SetH((RegisterBank::H & 0b111) == 0b111);

    ++RegisterBank::H;

    RegisterBank::SetZ(RegisterBank::H == 0);
    RegisterBank::SetN(false);

    Helper::CPULog("INC\tH\n");
    return 4;
}

inline int op0x25()
{
    Helper::CPULog("Op not implemented: 0x25\n");
    return -1;
}

inline int op0x26()
{
    Helper::CPULog("Op not implemented: 0x26\n");
    return -1;
}

inline int op0x27()
{
    Helper::CPULog("Op not implemented: 0x27\n");
    return -1;
}

inline int op0x28()
{
    int cycles = 8;
    int8_t value = RAM::ReadByteAt(++RegisterBank::PC);
    if (RegisterBank::IsZSet())
    {
        RegisterBank::PC += value;
        cycles += 4;
    }
    Helper::CPULog("JR\tZ, %d\n", value);
    return cycles;
}

inline int op0x29()
{
    Helper::CPULog("Op not implemented: 0x29\n");
    return -1;
}

inline int op0x2A()
{
    Helper::CPULog("Op not implemented: 0x2A\n");
    return -1;
}

inline int op0x2B()
{
    Helper::CPULog("Op not implemented: 0x2B\n");
    return -1;
}

inline int op0x2C()
{
    Helper::CPULog("Op not implemented: 0x2C\n");
    return -1;
}

inline int op0x2D()
{
    Helper::CPULog("Op not implemented: 0x2D\n");
    return -1;
}

inline int op0x2E()
{
    uint8 value = RAM::ReadByteAt(++RegisterBank::PC);
    RegisterBank::L = value;
    Helper::CPULog("LD\tL, 0x%02X\n", value);
    return 8;
}

inline int op0x2F()
{
    Helper::CPULog("Op not implemented: 0x2F\n");
    return -1;
}

inline int op0x30()
{
    Helper::CPULog("Op not implemented: 0x30\n");
    return -1;
}

inline int op0x31()
{
    RegisterBank::SP = getNextTwoBytes();
    Helper::CPULog("LD\tSP, 0x%04X\n", RegisterBank::SP);
    return 12;
}

inline int op0x32()
{
    RAM::WriteByteAt(RegisterBank::HL(), RegisterBank::A);
    RegisterBank::HL(RegisterBank::HL() - 1);
    Helper::CPULog("LD\t[HL--](0x%04X), A\n", RegisterBank::HL());
    return 8;
}

inline int op0x33()
{
    Helper::CPULog("Op not implemented: 0x33\n");
    return -1;
}

inline int op0x34()
{
    Helper::CPULog("Op not implemented: 0x34\n");
    return -1;
}

inline int op0x35()
{
    Helper::CPULog("Op not implemented: 0x35\n");
    return -1;
}

inline int op0x36()
{
    Helper::CPULog("Op not implemented: 0x36\n");
    return -1;
}

inline int op0x37()
{
    Helper::CPULog("Op not implemented: 0x37\n");
    return -1;
}

inline int op0x38()
{
    Helper::CPULog("Op not implemented: 0x38\n");
    return -1;
}

inline int op0x39()
{
    uint16 halfBitmask = 0b111111111111;
    uint32_t result = RegisterBank::HL() + RegisterBank::SP;
    uint16 halfResult = (RegisterBank::HL() & halfBitmask) + (RegisterBank::SP + halfBitmask);
    RegisterBank::HL(result);

    RegisterBank::SetN(false);
    RegisterBank::SetC(result & (UINT16_MAX + 1));
    RegisterBank::SetH(halfResult & (halfBitmask + 1));
    Helper::CPULog("ADD\tHL, SP\n");
    return -8;
}

inline int op0x3A()
{
    Helper::CPULog("Op not implemented: 0x3A\n");
    return -1;
}

inline int op0x3B()
{
    Helper::CPULog("Op not implemented: 0x3B\n");
    return -1;
}

inline int op0x3C()
{
    Helper::CPULog("Op not implemented: 0x3C\n");
    return -1;
}

inline int op0x3D()
{
    Helper::CPULog("DEC\tA\n");
    return baseDec(&RegisterBank::A);
}

inline int op0x3E()
{
    RegisterBank::A = RAM::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("LD\tA, 0x%02X\n", RegisterBank::A);
    return 8;
}

inline int op0x3F()
{
    Helper::CPULog("Op not implemented: 0x3F\n");
    return -1;
}

inline int op0x40()
{
    Helper::CPULog("Op not implemented: 0x40\n");
    return -1;
}

inline int op0x41()
{
    Helper::CPULog("Op not implemented: 0x41\n");
    return -1;
}

inline int op0x42()
{
    Helper::CPULog("Op not implemented: 0x42\n");
    return -1;
}

inline int op0x43()
{
    Helper::CPULog("Op not implemented: 0x43\n");
    return -1;
}

inline int op0x44()
{
    Helper::CPULog("Op not implemented: 0x44\n");
    return -1;
}

inline int op0x45()
{
    Helper::CPULog("Op not implemented: 0x45\n");
    return -1;
}

inline int op0x46()
{
    Helper::CPULog("Op not implemented: 0x46\n");
    return -1;
}

inline int op0x47()
{
    Helper::CPULog("Op not implemented: 0x47\n");
    return -1;
}

inline int op0x48()
{
    Helper::CPULog("Op not implemented: 0x48\n");
    return -1;
}

inline int op0x49()
{
    Helper::CPULog("Op not implemented: 0x49\n");
    return -1;
}

inline int op0x4A()
{
    Helper::CPULog("Op not implemented: 0x4A\n");
    return -1;
}

inline int op0x4B()
{
    Helper::CPULog("Op not implemented: 0x4B\n");
    return -1;
}

inline int op0x4C()
{
    Helper::CPULog("Op not implemented: 0x4C\n");
    return -1;
}

inline int op0x4D()
{
    Helper::CPULog("Op not implemented: 0x4D\n");
    return -1;
}

inline int op0x4E()
{
    Helper::CPULog("Op not implemented: 0x4E\n");
    return -1;
}

inline int op0x4F()
{
    RegisterBank::C = RegisterBank::A;
    Helper::CPULog("LD\tC, A\n");
    return 4;
}

inline int op0x50()
{
    Helper::CPULog("Op not implemented: 0x50\n");
    return -1;
}

inline int op0x51()
{
    Helper::CPULog("Op not implemented: 0x51\n");
    return -1;
}

inline int op0x52()
{
    Helper::CPULog("Op not implemented: 0x52\n");
    return -1;
}

inline int op0x53()
{
    Helper::CPULog("Op not implemented: 0x53\n");
    return -1;
}

inline int op0x54()
{
    Helper::CPULog("Op not implemented: 0x54\n");
    return -1;
}

inline int op0x55()
{
    Helper::CPULog("Op not implemented: 0x55\n");
    return -1;
}

inline int op0x56()
{
    Helper::CPULog("Op not implemented: 0x56\n");
    return -1;
}

inline int op0x57()
{
    RegisterBank::D = RegisterBank::A;
    Helper::CPULog("LD\tD, A\n");
    return 4;
}

inline int op0x58()
{
    Helper::CPULog("Op not implemented: 0x58\n");
    return -1;
}

inline int op0x59()
{
    Helper::CPULog("Op not implemented: 0x59\n");
    return -1;
}

inline int op0x5A()
{
    Helper::CPULog("Op not implemented: 0x5A\n");
    return -1;
}

inline int op0x5B()
{
    Helper::CPULog("Op not implemented: 0x5B\n");
    return -1;
}

inline int op0x5C()
{
    Helper::CPULog("Op not implemented: 0x5C\n");
    return -1;
}

inline int op0x5D()
{
    Helper::CPULog("Op not implemented: 0x5D\n");
    return -1;
}

inline int op0x5E()
{
    Helper::CPULog("Op not implemented: 0x5E\n");
    return -1;
}

inline int op0x5F()
{
    Helper::CPULog("Op not implemented: 0x5F\n");
    return -1;
}

inline int op0x60()
{
    Helper::CPULog("Op not implemented: 0x60\n");
    return -1;
}

inline int op0x61()
{
    Helper::CPULog("Op not implemented: 0x61\n");
    return -1;
}

inline int op0x62()
{
    Helper::CPULog("Op not implemented: 0x62\n");
    return -1;
}

inline int op0x63()
{
    Helper::CPULog("Op not implemented: 0x63\n");
    return -1;
}

inline int op0x64()
{
    Helper::CPULog("Op not implemented: 0x64\n");
    return -1;
}

inline int op0x65()
{
    Helper::CPULog("Op not implemented: 0x65\n");
    return -1;
}

inline int op0x66()
{
    Helper::CPULog("Op not implemented: 0x66\n");
    return -1;
}

inline int op0x67()
{
    RegisterBank::H = RegisterBank::A;
    Helper::CPULog("LD\tH, A\n");
    return 4;
}

inline int op0x68()
{
    Helper::CPULog("Op not implemented: 0x68\n");
    return -1;
}

inline int op0x69()
{
    Helper::CPULog("Op not implemented: 0x69\n");
    return -1;
}

inline int op0x6A()
{
    Helper::CPULog("Op not implemented: 0x6A\n");
    return -1;
}

inline int op0x6B()
{
    Helper::CPULog("Op not implemented: 0x6B\n");
    return -1;
}

inline int op0x6C()
{
    Helper::CPULog("Op not implemented: 0x6C\n");
    return -1;
}

inline int op0x6D()
{
    Helper::CPULog("Op not implemented: 0x6D\n");
    return -1;
}

inline int op0x6E()
{
    Helper::CPULog("Op not implemented: 0x6E\n");
    return -1;
}

inline int op0x6F()
{
    Helper::CPULog("Op not implemented: 0x6F\n");
    return -1;
}

inline int op0x70()
{
    Helper::CPULog("Op not implemented: 0x70\n");
    return -1;
}

inline int op0x71()
{
    Helper::CPULog("Op not implemented: 0x71\n");
    return -1;
}

inline int op0x72()
{
    Helper::CPULog("Op not implemented: 0x72\n");
    return -1;
}

inline int op0x73()
{
    Helper::CPULog("Op not implemented: 0x73\n");
    return -1;
}

inline int op0x74()
{
    Helper::CPULog("Op not implemented: 0x74\n");
    return -1;
}

inline int op0x75()
{
    Helper::CPULog("Op not implemented: 0x75\n");
    return -1;
}

inline int op0x76()
{
    Helper::CPULog("Op not implemented: 0x76\n");
    return -1;
}

inline int op0x77()
{
    RegisterBank::HL(RegisterBank::A);
    Helper::CPULog("LD\tHL, A\n");
    return 8;
}

inline int op0x78()
{
    Helper::CPULog("Op not implemented: 0x78\n");
    return -1;
}

inline int op0x79()
{
    Helper::CPULog("Op not implemented: 0x79\n");
    return -1;
}

inline int op0x7A()
{
    Helper::CPULog("Op not implemented: 0x7A\n");
    return -1;
}

inline int op0x7B()
{
    RegisterBank::A = RegisterBank::E;
    Helper::CPULog("LD\tA, E\n");
    return 4;
}

inline int op0x7C()
{
    Helper::CPULog("LD\tA, H\n");
    return baseLoadReg(&RegisterBank::A, RegisterBank::H);
}

inline int op0x7D()
{
    Helper::CPULog("Op not implemented: 0x7D\n");
    return -1;
}

inline int op0x7E()
{
    Helper::CPULog("Op not implemented: 0x7E\n");
    return -1;
}

inline int op0x7F()
{
    Helper::CPULog("Op not implemented: 0x7F\n");
    return -1;
}

inline int op0x80()
{
    Helper::CPULog("Op not implemented: 0x80\n");
    return -1;
}

inline int op0x81()
{
    Helper::CPULog("Op not implemented: 0x81\n");
    return -1;
}

inline int op0x82()
{
    Helper::CPULog("Op not implemented: 0x82\n");
    return -1;
}

inline int op0x83()
{
    Helper::CPULog("Op not implemented: 0x83\n");
    return -1;
}

inline int op0x84()
{
    Helper::CPULog("Op not implemented: 0x84\n");
    return -1;
}

inline int op0x85()
{
    Helper::CPULog("Op not implemented: 0x85\n");
    return -1;
}

inline int op0x86()
{
    Helper::CPULog("Op not implemented: 0x86\n");
    return -1;
}

inline int op0x87()
{
    Helper::CPULog("Op not implemented: 0x87\n");
    return -1;
}

inline int op0x88()
{
    Helper::CPULog("Op not implemented: 0x88\n");
    return -1;
}

inline int op0x89()
{
    Helper::CPULog("Op not implemented: 0x89\n");
    return -1;
}

inline int op0x8A()
{
    Helper::CPULog("Op not implemented: 0x8A\n");
    return -1;
}

inline int op0x8B()
{
    Helper::CPULog("Op not implemented: 0x8B\n");
    return -1;
}

inline int op0x8C()
{
    Helper::CPULog("Op not implemented: 0x8C\n");
    return -1;
}

inline int op0x8D()
{
    Helper::CPULog("Op not implemented: 0x8D\n");
    return -1;
}

inline int op0x8E()
{
    Helper::CPULog("Op not implemented: 0x8E\n");
    return -1;
}

inline int op0x8F()
{
    Helper::CPULog("Op not implemented: 0x8F\n");
    return -1;
}

inline int op0x90()
{
    Helper::CPULog("SUB\tB\n");
    return baseSub(RegisterBank::B);
}

inline int op0x91()
{
    Helper::CPULog("Op not implemented: 0x91\n");
    return -1;
}

inline int op0x92()
{
    Helper::CPULog("Op not implemented: 0x92\n");
    return -1;
}

inline int op0x93()
{
    Helper::CPULog("Op not implemented: 0x93\n");
    return -1;
}

inline int op0x94()
{
    Helper::CPULog("Op not implemented: 0x94\n");
    return -1;
}

inline int op0x95()
{
    RegisterBank::SetC(RegisterBank::A >= RegisterBank::L);
    uint8 bitmask = 0b1111;
    uint8 lowerA = RegisterBank::A & bitmask;
    uint8 lowerL = RegisterBank::L & bitmask;
    RegisterBank::SetH(lowerA >= lowerL);

    RegisterBank::A -= RegisterBank::L;

    RegisterBank::SetZ(RegisterBank::A == 0);
    RegisterBank::SetN(true);

    Helper::CPULog("SUB\tL\n");
    return 4;
}

inline int op0x96()
{
    RegisterBank::SetC(RegisterBank::A >= RegisterBank::HL());
    uint8 bitmask = 0b1111;
    uint16 lowerA = RegisterBank::A & bitmask;
    uint16 lowerHL = RegisterBank::HL() & bitmask;
    RegisterBank::SetH(lowerA >= lowerHL);

    RegisterBank::A -= RegisterBank::HL();

    RegisterBank::SetZ(RegisterBank::A == 0);
    RegisterBank::SetN(true);

    Helper::CPULog("SUB\tHL\n");
    return 8;
}

inline int op0x97()
{
    Helper::CPULog("Op not implemented: 0x97\n");
    return -1;
}

inline int op0x98()
{
    Helper::CPULog("Op not implemented: 0x98\n");
    return -1;
}

inline int op0x99()
{
    Helper::CPULog("Op not implemented: 0x99\n");
    return -1;
}

inline int op0x9A()
{
    Helper::CPULog("Op not implemented: 0x9A\n");
    return -1;
}

inline int op0x9B()
{
    Helper::CPULog("Op not implemented: 0x9B\n");
    return -1;
}

inline int op0x9C()
{
    Helper::CPULog("Op not implemented: 0x9C\n");
    return -1;
}

inline int op0x9D()
{
    Helper::CPULog("Op not implemented: 0x9D\n");
    return -1;
}

inline int op0x9E()
{
    Helper::CPULog("Op not implemented: 0x9E\n");
    return -1;
}

inline int op0x9F()
{
    Helper::CPULog("Op not implemented: 0x9F\n");
    return -1;
}

inline int op0xA0()
{
    Helper::CPULog("Op not implemented: 0xA0\n");
    return -1;
}

inline int op0xA1()
{
    Helper::CPULog("Op not implemented: 0xA1\n");
    return -1;
}

inline int op0xA2()
{
    Helper::CPULog("Op not implemented: 0xA2\n");
    return -1;
}

inline int op0xA3()
{
    Helper::CPULog("Op not implemented: 0xA3\n");
    return -1;
}

inline int op0xA4()
{
    Helper::CPULog("Op not implemented: 0xA4\n");
    return -1;
}

inline int op0xA5()
{
    Helper::CPULog("Op not implemented: 0xA5\n");
    return -1;
}

inline int op0xA6()
{
    Helper::CPULog("Op not implemented: 0xA6\n");
    return -1;
}

inline int op0xA7()
{
    Helper::CPULog("Op not implemented: 0xA7\n");
    return -1;
}

inline int op0xA8()
{
    Helper::CPULog("Op not implemented: 0xA8\n");
    return -1;
}

inline int op0xA9()
{
    Helper::CPULog("Op not implemented: 0xA9\n");
    return -1;
}

inline int op0xAA()
{
    Helper::CPULog("Op not implemented: 0xAA\n");
    return -1;
}

inline int op0xAB()
{
    Helper::CPULog("Op not implemented: 0xAB\n");
    return -1;
}

inline int op0xAC()
{
    Helper::CPULog("Op not implemented: 0xAC\n");
    return -1;
}

inline int op0xAD()
{
    Helper::CPULog("Op not implemented: 0xAD\n");
    return -1;
}

inline int op0xAE()
{
    Helper::CPULog("Op not implemented: 0xAE\n");
    return -1;
}

inline int op0xAF()
{
    RegisterBank::A = 0;
    RegisterBank::SetZ(true);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(false);
    Helper::CPULog("XOR A\n");
    return 4;
}

inline int op0xB0()
{
    Helper::CPULog("Op not implemented: 0xB0\n");
    return -1;
}

inline int op0xB1()
{
    Helper::CPULog("Op not implemented: 0xB1\n");
    return -1;
}

inline int op0xB2()
{
    Helper::CPULog("Op not implemented: 0xB2\n");
    return -1;
}

inline int op0xB3()
{
    Helper::CPULog("Op not implemented: 0xB3\n");
    return -1;
}

inline int op0xB4()
{
    Helper::CPULog("Op not implemented: 0xB4\n");
    return -1;
}

inline int op0xB5()
{
    Helper::CPULog("Op not implemented: 0xB5\n");
    return -1;
}

inline int op0xB6()
{
    Helper::CPULog("Op not implemented: 0xB6\n");
    return -1;
}

inline int op0xB7()
{
    Helper::CPULog("Op not implemented: 0xB7\n");
    return -1;
}

inline int op0xB8()
{
    Helper::CPULog("Op not implemented: 0xB8\n");
    return -1;
}

inline int op0xB9()
{
    Helper::CPULog("Op not implemented: 0xB9\n");
    return -1;
}

inline int op0xBA()
{
    Helper::CPULog("Op not implemented: 0xBA\n");
    return -1;
}

inline int op0xBB()
{
    Helper::CPULog("Op not implemented: 0xBB\n");
    return -1;
}

inline int op0xBC()
{
    Helper::CPULog("Op not implemented: 0xBC\n");
    return -1;
}

inline int op0xBD()
{
    Helper::CPULog("Op not implemented: 0xBD\n");
    return -1;
}

inline int op0xBE()
{
    Helper::CPULog("Op not implemented: 0xBE\n");
    return -1;
}

inline int op0xBF()
{
    Helper::CPULog("Op not implemented: 0xBF\n");
    return -1;
}

inline int op0xC0()
{
    Helper::CPULog("Op not implemented: 0xC0\n");
    return -1;
}

inline int op0xC1()
{
    RegisterBank::C = RAM::ReadByteAt(++RegisterBank::SP);
    RegisterBank::B = RAM::ReadByteAt(++RegisterBank::SP);
    Helper::CPULog("POP\tBC(0x%04X)\n", RegisterBank::BC());
    return 12;
}

inline int op0xC2()
{
    Helper::CPULog("Op not implemented: 0xC2\n");
    return -1;
}

inline int op0xC3()
{
    uint16 address = getNextTwoBytes();
    RegisterBank::PC = address - 1; //account for the already incremented pc
    Helper::CPULog("JP\t0x%04X\n", address);
    return 16;
}

inline int op0xC4()
{
    Helper::CPULog("Op not implemented: 0xC4\n");
    return -1;
}

inline int op0xC5()
{
    RAM::WriteByteAt(RegisterBank::SP--, RegisterBank::B);
    RAM::WriteByteAt(RegisterBank::SP--, RegisterBank::C);
    Helper::CPULog("PUSH\tBC(0x%04X)\n", RegisterBank::BC());
    return 16;
}

inline int op0xC6()
{
    Helper::CPULog("Op not implemented: 0xC6\n");
    return -1;
}

inline int op0xC7()
{
    Helper::CPULog("Op not implemented: 0xC7\n");
    return -1;
}

inline int op0xC8()
{
    Helper::CPULog("Op not implemented: 0xC8\n");
    return -1;
}

inline int op0xC9()
{
    uint16 address = RAM::ReadByteAt(++RegisterBank::SP) << 8;
    address += RAM::ReadByteAt(++RegisterBank::SP);
    RegisterBank::PC = address - 1; //offset the one that gets added.
    Helper::CPULog("RET\t(0x%04X)\n", address);
    return 16;
}

inline int op0xCA()
{
    Helper::CPULog("Op not implemented: 0xCA\n");
    return -1;
}

inline int cbOp0x11()
{
    bool wasCarrySet = RegisterBank::IsCSet();

    RegisterBank::SetC(RegisterBank::C & 0b10000000);

    RegisterBank::C <<= 1;
    if (wasCarrySet) ++RegisterBank::C;

    RegisterBank::SetZ(!RegisterBank::C);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);

    Helper::CPULog("RL\tC sets carry: %s\n", RegisterBank::IsCSet() ? "true" : "false");

    return 8;
}

inline int cbOp0x7C()
{
    RegisterBank::SetZ(!Helper::IsBitSet(RegisterBank::H, 7));
    RegisterBank::SetN(false);
    RegisterBank::SetH(true);
    Helper::CPULog("BIT\t7, H\n");

    return 8;
}

inline int op0xCB()
{
    uint8 cb_op = RAM::ReadByteAt(++RegisterBank::PC);
    switch (cb_op) {
        case 0x11: return cbOp0x11();
        case 0x7C: return cbOp0x7C();
        default:Helper::CPULog("NOT IMPLEMENTED CB Prefix(0x%02X)\n", cb_op);
            break;
    }
    return -1;
}

inline int op0xCC()
{
    Helper::CPULog("Op not implemented: 0xCC\n");
    return -1;
}

inline int op0xCD()
{
    uint16 funcAddr = getNextTwoBytes();

    RAM::WriteByteAt(RegisterBank::SP--, RegisterBank::PC + 1);
    RAM::WriteByteAt(RegisterBank::SP--, (RegisterBank::PC + 1) >> 8);

    RegisterBank::PC = funcAddr - 1; //offset the increment that's gonna happen
    Helper::CPULog("CALL\t0x%04X\n", funcAddr);
    return 24;
}

inline int op0xCE()
{
    Helper::CPULog("Op not implemented: 0xCE\n");
    return -1;
}

inline int op0xCF()
{
    Helper::CPULog("Op not implemented: 0xCF\n");
    return -1;
}

inline int op0xD0()
{
    Helper::CPULog("Op not implemented: 0xD0\n");
    return -1;
}

inline int op0xD1()
{
    RegisterBank::E = RAM::ReadByteAt(++RegisterBank::SP);
    RegisterBank::D = RAM::ReadByteAt(++RegisterBank::SP);
    Helper::CPULog("POP\tDE(0x%04X)\n", RegisterBank::DE());
    return 12;
}

inline int op0xD2()
{
    Helper::CPULog("Op not implemented: 0xD2\n");
    return -1;
}

inline int op0xD3()
{
    Helper::CPULog("Op not implemented: 0xD3\n");
    return -1;
}

inline int op0xD4()
{
    Helper::CPULog("Op not implemented: 0xD4\n");
    return -1;
}

inline int op0xD5()
{
    RAM::WriteByteAt(RegisterBank::SP--, RegisterBank::D);
    RAM::WriteByteAt(RegisterBank::SP--, RegisterBank::E);
    Helper::CPULog("PUSH\tDE(0x%04X)\n", RegisterBank::DE());
    return 16;
}

inline int op0xD6()
{
    Helper::CPULog("Op not implemented: 0xD6\n");
    return -1;
}

inline int op0xD7()
{
    Helper::CPULog("Op not implemented: 0xD7\n");
    return -1;
}

inline int op0xD8()
{
    Helper::CPULog("Op not implemented: 0xD8\n");
    return -1;
}

inline int op0xD9()
{
    Helper::CPULog("Op not implemented: 0xD9\n");
    return -1;
}

inline int op0xDA()
{
    Helper::CPULog("Op not implemented: 0xDA\n");
    return -1;
}

inline int op0xDB()
{
    Helper::CPULog("Op not implemented: 0xDB\n");
    return -1;
}

inline int op0xDC()
{
    Helper::CPULog("Op not implemented: 0xDC\n");
    return -1;
}

inline int op0xDD()
{
    Helper::CPULog("Op not implemented: 0xDD\n");
    return -1;
}

inline int op0xDE()
{
    Helper::CPULog("Op not implemented: 0xDE\n");
    return -1;
}

inline int op0xDF()
{
    Helper::CPULog("Op not implemented: 0xDF\n");
    return -1;
}

inline int op0xE0()
{
    uint16 immediate = RAM::ReadByteAt(++RegisterBank::PC) + 0xFF00;
    RAM::WriteByteAt(immediate, RegisterBank::A);
    Helper::CPULog("LDH\t[0x%02X], A\n", immediate);
    return 12;
}

inline int op0xE1()
{
    RegisterBank::H = RAM::ReadByteAt(++RegisterBank::SP);
    RegisterBank::L = RAM::ReadByteAt(++RegisterBank::SP);
    Helper::CPULog("POP\tHL(0x%04X)\n", RegisterBank::HL());
    return 12;
}

inline int op0xE2()
{
    RAM::WriteByteAt(0xFF00 + RegisterBank::C, RegisterBank::A);
    Helper::CPULog("LD\t[C], A\n");
    return 8;
}

inline int op0xE3()
{
    Helper::CPULog("Op not implemented: 0xE3\n");
    return -1;
}

inline int op0xE4()
{
    Helper::CPULog("Op not implemented: 0xE4\n");
    return -1;
}

inline int op0xE5()
{
    RAM::WriteByteAt(RegisterBank::SP--, RegisterBank::L);
    RAM::WriteByteAt(RegisterBank::SP--, RegisterBank::H);
    Helper::CPULog("PUSH\tHL(0x%04X)\n", RegisterBank::HL());
    return 16;
}

inline int op0xE6()
{
    Helper::CPULog("Op not implemented: 0xE6\n");
    return -1;
}

inline int op0xE7()
{
    Helper::CPULog("Op not implemented: 0xE7\n");
    return -1;
}

inline int op0xE8()
{
    Helper::CPULog("Op not implemented: 0xE8\n");
    return -1;
}

inline int op0xE9()
{
    Helper::CPULog("Op not implemented: 0xE9\n");
    return -1;
}

inline int op0xEA()
{
    uint16 address = getNextTwoBytes();
    RAM::WriteByteAt(address, RegisterBank::A);

    Helper::CPULog("LD\t[0x%04X], A", address);
    return 16;
}

inline int op0xEB()
{
    Helper::CPULog("Op not implemented: 0xEB\n");
    return -1;
}

inline int op0xEC()
{
    Helper::CPULog("Op not implemented: 0xEC\n");
    return -1;
}

inline int op0xED()
{
    Helper::CPULog("Op not implemented: 0xED\n");
    return -1;
}

inline int op0xEE()
{
    Helper::CPULog("Op not implemented: 0xEE\n");
    return -1;
}

inline int op0xEF()
{
    Helper::CPULog("Op not implemented: 0xEF\n");
    return -1;
}

inline int op0xF0()
{
    uint16 address = RAM::ReadByteAt(++RegisterBank::PC) + 0xFF00;
    RegisterBank::A = RAM::ReadByteAt(address);
    Helper::CPULog("LD\tA, [0x%04X]\n", address);
    return 12;
}

inline int op0xF1()
{
    RegisterBank::A = RAM::ReadByteAt(++RegisterBank::SP);
    RegisterBank::F = RAM::ReadByteAt(++RegisterBank::SP);
    Helper::CPULog("POP\tAF(0x%04X)\n", RegisterBank::AF());
    return 12;
}

inline int op0xF2()
{
    Helper::CPULog("Op not implemented: 0xF2\n");
    return -1;
}

inline int op0xF3()
{
    Helper::CPULog("Op not implemented: 0xF3\n");
    return -1;
}

inline int op0xF4()
{
    Helper::CPULog("Op not implemented: 0xF4\n");
    return -1;
}

inline int op0xF5()
{
    RAM::WriteByteAt(RegisterBank::SP--, RegisterBank::F);
    RAM::WriteByteAt(RegisterBank::SP--, RegisterBank::A);
    Helper::CPULog("PUSH\tAF(0x%04X)\n", RegisterBank::AF());
    return 16;
}

inline int op0xF6()
{
    Helper::CPULog("Op not implemented: 0xF6\n");
    return -1;
}

inline int op0xF7()
{
    Helper::CPULog("Op not implemented: 0xF7\n");
    return -1;
}

inline int op0xF8()
{
    Helper::CPULog("Op not implemented: 0xF8\n");
    return -1;
}

inline int op0xF9()
{
    Helper::CPULog("Op not implemented: 0xF9\n");
    return -1;
}

inline int op0xFA()
{
    Helper::CPULog("Op not implemented: 0xFA\n");
    return -1;
}

inline int op0xFB()
{
    Helper::CPULog("Op not implemented: 0xFB\n");
    return -1;
}

inline int op0xFC()
{
    Helper::CPULog("Op not implemented: 0xFC\n");
    return -1;
}

inline int op0xFD()
{
    Helper::CPULog("Op not implemented: 0xFD\n");
    return -1;
}

inline int op0xFE()
{
    uint8 immediate = RAM::ReadByteAt(++RegisterBank::PC);

    RegisterBank::SetZ(RegisterBank::A == immediate);
    RegisterBank::SetN(true);
    RegisterBank::SetH((RegisterBank::A & 0b1111) >= (immediate & 0b1111));
    RegisterBank::SetC(RegisterBank::A >= immediate);

    Helper::CPULog("CP\t0x%02X (0x%02X)\n", immediate, RegisterBank::A);
    return 8;
}

inline int op0xFF()
{
    Helper::CPULog("Op not implemented: 0xFF\n");
    return -1;
}

int Processor::decodeInstr(uint16 address)
{
    uint8 op_code = RAM::ReadByteAt(address);
    Helper::CPULog("0x%04X: ", address);
    switch(op_code) {
        case 0x00: return op0x00();
        case 0x01: return op0x01();
        case 0x02: return op0x02();
        case 0x03: return op0x03();
        case 0x04: return op0x04();
        case 0x05: return op0x05();
        case 0x06: return op0x06();
        case 0x07: return op0x07();
        case 0x08: return op0x08();
        case 0x09: return op0x09();
        case 0x0A: return op0x0A();
        case 0x0B: return op0x0B();
        case 0x0C: return op0x0C();
        case 0x0D: return op0x0D();
        case 0x0E: return op0x0E();
        case 0x0F: return op0x0F();
        case 0x10: return op0x10();
        case 0x11: return op0x11();
        case 0x12: return op0x12();
        case 0x13: return op0x13();
        case 0x14: return op0x14();
        case 0x15: return op0x15();
        case 0x16: return op0x16();
        case 0x17: return op0x17();
        case 0x18: return op0x18();
        case 0x19: return op0x19();
        case 0x1A: return op0x1A();
        case 0x1B: return op0x1B();
        case 0x1C: return op0x1C();
        case 0x1D: return op0x1D();
        case 0x1E: return op0x1E();
        case 0x1F: return op0x1F();
        case 0x20: return op0x20();
        case 0x21: return op0x21();
        case 0x22: return op0x22();
        case 0x23: return op0x23();
        case 0x24: return op0x24();
        case 0x25: return op0x25();
        case 0x26: return op0x26();
        case 0x27: return op0x27();
        case 0x28: return op0x28();
        case 0x29: return op0x29();
        case 0x2A: return op0x2A();
        case 0x2B: return op0x2B();
        case 0x2C: return op0x2C();
        case 0x2D: return op0x2D();
        case 0x2E: return op0x2E();
        case 0x2F: return op0x2F();
        case 0x30: return op0x30();
        case 0x31: return op0x31();
        case 0x32: return op0x32();
        case 0x33: return op0x33();
        case 0x34: return op0x34();
        case 0x35: return op0x35();
        case 0x36: return op0x36();
        case 0x37: return op0x37();
        case 0x38: return op0x38();
        case 0x39: return op0x39();
        case 0x3A: return op0x3A();
        case 0x3B: return op0x3B();
        case 0x3C: return op0x3C();
        case 0x3D: return op0x3D();
        case 0x3E: return op0x3E();
        case 0x3F: return op0x3F();
        case 0x40: return op0x40();
        case 0x41: return op0x41();
        case 0x42: return op0x42();
        case 0x43: return op0x43();
        case 0x44: return op0x44();
        case 0x45: return op0x45();
        case 0x46: return op0x46();
        case 0x47: return op0x47();
        case 0x48: return op0x48();
        case 0x49: return op0x49();
        case 0x4A: return op0x4A();
        case 0x4B: return op0x4B();
        case 0x4C: return op0x4C();
        case 0x4D: return op0x4D();
        case 0x4E: return op0x4E();
        case 0x4F: return op0x4F();
        case 0x50: return op0x50();
        case 0x51: return op0x51();
        case 0x52: return op0x52();
        case 0x53: return op0x53();
        case 0x54: return op0x54();
        case 0x55: return op0x55();
        case 0x56: return op0x56();
        case 0x57: return op0x57();
        case 0x58: return op0x58();
        case 0x59: return op0x59();
        case 0x5A: return op0x5A();
        case 0x5B: return op0x5B();
        case 0x5C: return op0x5C();
        case 0x5D: return op0x5D();
        case 0x5E: return op0x5E();
        case 0x5F: return op0x5F();
        case 0x60: return op0x60();
        case 0x61: return op0x61();
        case 0x62: return op0x62();
        case 0x63: return op0x63();
        case 0x64: return op0x64();
        case 0x65: return op0x65();
        case 0x66: return op0x66();
        case 0x67: return op0x67();
        case 0x68: return op0x68();
        case 0x69: return op0x69();
        case 0x6A: return op0x6A();
        case 0x6B: return op0x6B();
        case 0x6C: return op0x6C();
        case 0x6D: return op0x6D();
        case 0x6E: return op0x6E();
        case 0x6F: return op0x6F();
        case 0x70: return op0x70();
        case 0x71: return op0x71();
        case 0x72: return op0x72();
        case 0x73: return op0x73();
        case 0x74: return op0x74();
        case 0x75: return op0x75();
        case 0x76: return op0x76();
        case 0x77: return op0x77();
        case 0x78: return op0x78();
        case 0x79: return op0x79();
        case 0x7A: return op0x7A();
        case 0x7B: return op0x7B();
        case 0x7C: return op0x7C();
        case 0x7D: return op0x7D();
        case 0x7E: return op0x7E();
        case 0x7F: return op0x7F();
        case 0x80: return op0x80();
        case 0x81: return op0x81();
        case 0x82: return op0x82();
        case 0x83: return op0x83();
        case 0x84: return op0x84();
        case 0x85: return op0x85();
        case 0x86: return op0x86();
        case 0x87: return op0x87();
        case 0x88: return op0x88();
        case 0x89: return op0x89();
        case 0x8A: return op0x8A();
        case 0x8B: return op0x8B();
        case 0x8C: return op0x8C();
        case 0x8D: return op0x8D();
        case 0x8E: return op0x8E();
        case 0x8F: return op0x8F();
        case 0x90: return op0x90();
        case 0x91: return op0x91();
        case 0x92: return op0x92();
        case 0x93: return op0x93();
        case 0x94: return op0x94();
        case 0x95: return op0x95();
        case 0x96: return op0x96();
        case 0x97: return op0x97();
        case 0x98: return op0x98();
        case 0x99: return op0x99();
        case 0x9A: return op0x9A();
        case 0x9B: return op0x9B();
        case 0x9C: return op0x9C();
        case 0x9D: return op0x9D();
        case 0x9E: return op0x9E();
        case 0x9F: return op0x9F();
        case 0xA0: return op0xA0();
        case 0xA1: return op0xA1();
        case 0xA2: return op0xA2();
        case 0xA3: return op0xA3();
        case 0xA4: return op0xA4();
        case 0xA5: return op0xA5();
        case 0xA6: return op0xA6();
        case 0xA7: return op0xA7();
        case 0xA8: return op0xA8();
        case 0xA9: return op0xA9();
        case 0xAA: return op0xAA();
        case 0xAB: return op0xAB();
        case 0xAC: return op0xAC();
        case 0xAD: return op0xAD();
        case 0xAE: return op0xAE();
        case 0xAF: return op0xAF();
        case 0xB0: return op0xB0();
        case 0xB1: return op0xB1();
        case 0xB2: return op0xB2();
        case 0xB3: return op0xB3();
        case 0xB4: return op0xB4();
        case 0xB5: return op0xB5();
        case 0xB6: return op0xB6();
        case 0xB7: return op0xB7();
        case 0xB8: return op0xB8();
        case 0xB9: return op0xB9();
        case 0xBA: return op0xBA();
        case 0xBB: return op0xBB();
        case 0xBC: return op0xBC();
        case 0xBD: return op0xBD();
        case 0xBE: return op0xBE();
        case 0xBF: return op0xBF();
        case 0xC0: return op0xC0();
        case 0xC1: return op0xC1();
        case 0xC2: return op0xC2();
        case 0xC3: return op0xC3();
        case 0xC4: return op0xC4();
        case 0xC5: return op0xC5();
        case 0xC6: return op0xC6();
        case 0xC7: return op0xC7();
        case 0xC8: return op0xC8();
        case 0xC9: return op0xC9();
        case 0xCA: return op0xCA();
        case 0xCB: return op0xCB();
        case 0xCC: return op0xCC();
        case 0xCD: return op0xCD();
        case 0xCE: return op0xCE();
        case 0xCF: return op0xCF();
        case 0xD0: return op0xD0();
        case 0xD1: return op0xD1();
        case 0xD2: return op0xD2();
        case 0xD3: return op0xD3();
        case 0xD4: return op0xD4();
        case 0xD5: return op0xD5();
        case 0xD6: return op0xD6();
        case 0xD7: return op0xD7();
        case 0xD8: return op0xD8();
        case 0xD9: return op0xD9();
        case 0xDA: return op0xDA();
        case 0xDB: return op0xDB();
        case 0xDC: return op0xDC();
        case 0xDD: return op0xDD();
        case 0xDE: return op0xDE();
        case 0xDF: return op0xDF();
        case 0xE0: return op0xE0();
        case 0xE1: return op0xE1();
        case 0xE2: return op0xE2();
        case 0xE3: return op0xE3();
        case 0xE4: return op0xE4();
        case 0xE5: return op0xE5();
        case 0xE6: return op0xE6();
        case 0xE7: return op0xE7();
        case 0xE8: return op0xE8();
        case 0xE9: return op0xE9();
        case 0xEA: return op0xEA();
        case 0xEB: return op0xEB();
        case 0xEC: return op0xEC();
        case 0xED: return op0xED();
        case 0xEE: return op0xEE();
        case 0xEF: return op0xEF();
        case 0xF0: return op0xF0();
        case 0xF1: return op0xF1();
        case 0xF2: return op0xF2();
        case 0xF3: return op0xF3();
        case 0xF4: return op0xF4();
        case 0xF5: return op0xF5();
        case 0xF6: return op0xF6();
        case 0xF7: return op0xF7();
        case 0xF8: return op0xF8();
        case 0xF9: return op0xF9();
        case 0xFA: return op0xFA();
        case 0xFB: return op0xFB();
        case 0xFC: return op0xFC();
        case 0xFD: return op0xFD();
        case 0xFE: return op0xFE();
        case 0xFF: return op0xFF();
        default:
            return -1;
    }
    return -1;
}

void Processor::StartCPULoop()
{
    Helper::Log("Start CPU loop");
    int status = 1;
    while (status > 0) {
        status = decodeInstr(RegisterBank::PC);
        PPU::Update(status);
        RegisterBank::PC++;

        #ifdef REGISTERS
        Helper::CPULog(
                "\t[A: 0x%02X] [B: 0x%02X] [C: 0x%02X]\n",
                RegisterBank::A,
                RegisterBank::B,
                RegisterBank::C
        );
        #endif
    }
}