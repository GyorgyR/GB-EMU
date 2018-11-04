//
// Created by gyorgy on 11/08/18.
//

#undef DEBUG
#define REGISTERS

#define INSTPERSEC 4194304
#define FPS 60

#include "../include/Processor.h"
#include "../include/RegisterBank.h"
#include "../include/Helper.h"
#include "../include/PPU.h"
#include "../include/Types.h"
#include "../include/Timer.h"
#include "../include/EventMiddleware.h"

#include <iostream>

FILE *debugStream = stdout;

Processor::~Processor()
{
}

Processor::Processor()
{
}

inline uint16 getNextTwoBytes()
{
    uint8 first = MMU::ReadByteAt(++RegisterBank::PC);
    uint8 second = MMU::ReadByteAt(++RegisterBank::PC);
    return Helper::ConcatTwoBytes(second, first);
}

inline void basePush(uint16 value)
{
    std::pair<uint8, uint8> pcBytes = Helper::DivideIntoTwoBytes(value);
    MMU::WriteByteAt(RegisterBank::SP--, pcBytes.second);
    MMU::WriteByteAt(RegisterBank::SP--, pcBytes.first);
}

inline uint16 basePop()
{
    uint8 first = MMU::ReadByteAt(++RegisterBank::SP);
    uint8 second = MMU::ReadByteAt(++RegisterBank::SP);
    return Helper::ConcatTwoBytes(first, second);
}

inline int baseLoadReg(uint8 *destination, uint8 value)
{
    *destination = value;
    return 4;
}

inline int baseSub(uint8 value)
{
    RegisterBank::SetH((RegisterBank::A & 0b1111) < (value & 0b1111));
    RegisterBank::SetC(RegisterBank::A < value);

    RegisterBank::A -= value;

    RegisterBank::SetZ(RegisterBank::A == 0);
    RegisterBank::SetN(true);

    return 4;
}

inline int baseSbc(uint8 value)
{
    if (RegisterBank::IsCSet()) ++value;
    return baseSub(value);
}

inline int baseDec(uint8 *reg)
{
    RegisterBank::SetH(((*reg) & 0b000) > 0);

    --(*reg);

    RegisterBank::SetZ((*reg) == 0);
    RegisterBank::SetN(true);
    return 4;
}

inline int baseAdd(uint8 value)
{
    uint8 halfBitmask = 0b1111;
    uint16 result = RegisterBank::A + value;
    uint8 halfResult = (RegisterBank::A & halfBitmask) + (value & halfBitmask);
    RegisterBank::A = result;

    RegisterBank::SetZ((uint8)result == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(halfResult > halfBitmask);
    RegisterBank::SetC(result > UINT8_MAX);

    return 4;
}

inline int baseAdc(uint8 value)
{
    if (RegisterBank::IsCSet()) ++value;

    return baseAdd(value);
}

inline int baseAdd(uint16 value)
{
    uint16 halfBitmask = 0b111111111111;
    uint32 result = RegisterBank::HL() + value;
    uint16 halfResult = (RegisterBank::HL() & halfBitmask) + (value + halfBitmask);
    RegisterBank::HL(result);

    RegisterBank::SetN(false);
    RegisterBank::SetC(result & (UINT16_MAX + 1));
    RegisterBank::SetH(halfResult & (halfBitmask + 1));

    return 8;
}

inline int baseSwap(uint8 *op)
{
    uint8 lowerNibble = *op & 0b1111;
    uint8 highrNibble = (*op >> 4) & 0b1111;

    *op = (lowerNibble << 4) + highrNibble;

    return 8;
}

inline int baseOr(uint8 op)
{
    RegisterBank::A |= op;

    RegisterBank::SetZ(RegisterBank::A == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(false);

    return 4;
}

inline int baseXor(uint8 op)
{
    RegisterBank::A ^= op;

    RegisterBank::SetZ(RegisterBank::A == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(false);

    return 4;
}

inline int baseAnd(uint8 op)
{
    RegisterBank::A &= op;

    RegisterBank::SetZ(RegisterBank::A == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(true);
    RegisterBank::SetC(false);

    return 4;
}

inline int baseRST(uint16 address)
{
    basePush(++RegisterBank::PC);

    RegisterBank::PC = address - 1;

    return 16;
}

inline int baseInc(uint8 *op)
{
    RegisterBank::SetH((*op & 0b1111) == 0b1111);
    ++*op;

    RegisterBank::SetZ(*op == 0);
    RegisterBank::SetN(false);

    return 4;
}

inline int baseCP(uint8 op)
{
    uint8 originalA = RegisterBank::A;
    baseSub(op);
    RegisterBank::A = originalA;

    return 4;
}

inline int op0x00()
{
    Helper::CPULog("NOP\n");
    return 4;
}

inline int op0x01()
{
    RegisterBank::BC(getNextTwoBytes());
    Helper::CPULog("LD\tBC, 0x%04X\n", RegisterBank::BC());
    return 12;
}

inline int op0x02()
{
    MMU::WriteByteAt(RegisterBank::BC(), RegisterBank::A);
    Helper::CPULog("LD\t[BC], A\n");
    return 8;
}

inline int op0x03()
{
    RegisterBank::BC(RegisterBank::BC() + 1);
    Helper::CPULog("INC\tBC\n");
    return 8;
}

inline int op0x04()
{
    Helper::CPULog("INC\tB\n");
    return baseInc(&RegisterBank::B);
}

inline int op0x05()
{
    Helper::CPULog("DEC\tB\n");
    return baseDec(&RegisterBank::B);
}

inline int op0x06()
{
    RegisterBank::B = MMU::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("LD\tB, 0x%02X\n", RegisterBank::B);
    return 8;
}

inline int op0x07()
{
    bool is7BitSet = Helper::IsBitSet(RegisterBank::A, 7);
    RegisterBank::A <<= 1;
    if (is7BitSet) Helper::SetBit(&RegisterBank::A, 0);

    RegisterBank::SetZ(false);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(is7BitSet);

    Helper::CPULog("RLCA\n");
    return 4;
}

inline int op0x08()
{
    printf("Op not implemented: 0x08\n");
    return -1;
}

inline int op0x09()
{
    Helper::CPULog("ADD\tHL, BC\n");
    return baseAdd(RegisterBank::BC());
}

inline int op0x0A()
{
    printf("Op not implemented: 0x0A\n");
    return -1;
}

inline int op0x0B()
{
    RegisterBank::BC(RegisterBank::BC() - 1);
    Helper::CPULog("DEC\tBC\n");
    return 8;
}

inline int op0x0C()
{
    Helper::CPULog("INC\tC\n");
    return baseInc(&RegisterBank::C);
}

inline int op0x0D()
{
    Helper::CPULog("DEC\tC\n");
    return baseDec(&RegisterBank::C);
}

inline int op0x0E()
{
    RegisterBank::C = MMU::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("LD\tC, 0x%02X\n", RegisterBank::C);
    return 8;
}

inline int op0x0F()
{
    printf("Op not implemented: 0x0F\n");
    return -1;
}

inline int op0x10()
{
    printf("Op not implemented: 0x10\n");
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
    MMU::WriteByteAt(RegisterBank::DE(), RegisterBank::A);
    Helper::CPULog("LD\t[DE], A (0x%02X)\n", RegisterBank::A);
    return 8;
}

inline int op0x13()
{
    RegisterBank::DE(RegisterBank::DE() + 1);
    Helper::CPULog("INC\tDE(0x%04X)\n", RegisterBank::DE());
    return 8;
}

inline int op0x14()
{
    Helper::CPULog("INC\tD\n");
    return baseInc(&RegisterBank::D);
}

inline int op0x15()
{
    Helper::CPULog("DEC\tD\n");
    return baseDec(&RegisterBank::D);
}

inline int op0x16()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
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
    int8 value = MMU::ReadByteAt(++RegisterBank::PC);
    RegisterBank::PC += value;
    Helper::CPULog("JR\t%d\n", value);
    return 12;
}

inline int op0x19()
{
    Helper::CPULog("ADD\tHL, DE\n");
    return baseAdd(RegisterBank::DE());
}

inline int op0x1A()
{
    RegisterBank::A = MMU::ReadByteAt(RegisterBank::DE());
    Helper::CPULog("LD\tA, [DE]\n");
    return 8;
}

inline int op0x1B()
{
    printf("Op not implemented: 0x1B\n");
    return -1;
}

inline int op0x1C()
{
    Helper::CPULog("INC\tE (0x%02X)\n", RegisterBank::E + 1);
    return baseInc(&RegisterBank::E);
}

inline int op0x1D()
{
    Helper::CPULog("DEC\tE\n");
    return baseDec(&RegisterBank::E);
}

inline int op0x1E()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
    RegisterBank::E = value;
    Helper::CPULog("LD\tE, 0x%02X\n", value);
    return 8;
}

inline int op0x1F()
{
    bool wasBit0Set = Helper::IsBitSet(RegisterBank::A, 0);
    RegisterBank::A >>= 1;
    if (RegisterBank::IsCSet()) Helper::SetBit(&RegisterBank::A, 7);

    RegisterBank::SetZ(false);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(wasBit0Set);

    Helper::CPULog("RRA\n");
    return 4;
}

inline int op0x20()
{
    int cycles = 8;
    int8 value = MMU::ReadByteAt(++RegisterBank::PC);
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
    MMU::WriteByteAt(RegisterBank::HL(), RegisterBank::A);
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
    Helper::CPULog("INC\tH\n");
    return baseInc(&RegisterBank::H);
}

inline int op0x25()
{
    Helper::CPULog("DEC\tH\n");
    return baseDec(&RegisterBank::H);
}

inline int op0x26()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
    baseLoadReg(&RegisterBank::H, value);
    Helper::CPULog("LD\tH, 0x%02X\n", value);
    return 8;
}

inline int op0x27()
{
    printf("Op not implemented: 0x27\n");
    return -1;
}

inline int op0x28()
{
    int cycles = 8;
    int8 value = MMU::ReadByteAt(++RegisterBank::PC);
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
    Helper::CPULog("ADD\tHL, HL\n");
    return baseAdd(RegisterBank::HL());
}

inline int op0x2A()
{
    RegisterBank::A = MMU::ReadByteAt(RegisterBank::HL());
    RegisterBank::HL(RegisterBank::HL() + 1);
    Helper::CPULog("LD\tA, [HL++]\n");
    return 8;
}

inline int op0x2B()
{
    printf("Op not implemented: 0x2B\n");
    return -1;
}

inline int op0x2C()
{
    Helper::CPULog("INC\tL\n");
    return baseInc(&RegisterBank::L);
}

inline int op0x2D()
{
    Helper::CPULog("DEC\tL\n");
    return baseDec(&RegisterBank::L);
}

inline int op0x2E()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
    RegisterBank::L = value;
    Helper::CPULog("LD\tL, 0x%02X\n", value);
    return 8;
}

inline int op0x2F()
{
    RegisterBank::A = ~RegisterBank::A;

    RegisterBank::SetN(true);
    RegisterBank::SetH(true);

    Helper::CPULog("CPL\n");
    return 4;
}

inline int op0x30()
{
    int cycles = 8;
    int8 value = MMU::ReadByteAt(++RegisterBank::PC);

    if (!RegisterBank::IsCSet()) {
        RegisterBank::PC += value;
    }

    Helper::CPULog("JR\tNC, %d\n", value);
    return cycles;
}

inline int op0x31()
{
    RegisterBank::SP = getNextTwoBytes();
    Helper::CPULog("LD\tSP, 0x%04X\n", RegisterBank::SP);
    return 12;
}

inline int op0x32()
{
    MMU::WriteByteAt(RegisterBank::HL(), RegisterBank::A);
    RegisterBank::HL(RegisterBank::HL() - 1);
    Helper::CPULog("LD\t[HL--], A\n");
    return 8;
}

inline int op0x33()
{
    ++RegisterBank::SP;
    Helper::CPULog("INC\tSP\n");
    return 8;
}

inline int op0x34()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    baseInc(&value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("INC\t[HL]\n");
    return 12;
}

inline int op0x35()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    baseDec(&value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("DEC\t[HL]\n");
    return 12;
}

inline int op0x36()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("LD\t[0x%04X], 0x%02X\n", RegisterBank::HL(), value);
    return 12;
}

inline int op0x37()
{
    printf("Op not implemented: 0x37\n");
    return -1;
}

inline int op0x38()
{
    int cycles = 8;
    int8 value = MMU::ReadByteAt(++RegisterBank::PC);

    if (RegisterBank::IsCSet()) {
        RegisterBank::PC += value;
    }

    Helper::CPULog("JR\tC, %d\n", value);
    return cycles;
}

inline int op0x39()
{
    Helper::CPULog("ADD\tHL, SP\n");
    return baseAdd(RegisterBank::SP);
}

inline int op0x3A()
{
    printf("Op not implemented: 0x3A\n");
    return -1;
}

inline int op0x3B()
{
    printf("Op not implemented: 0x3B\n");
    return -1;
}

inline int op0x3C()
{
    Helper::CPULog("INC\tA\n");
    return baseInc(&RegisterBank::A);
}

inline int op0x3D()
{
    Helper::CPULog("DEC\tA\n");
    return baseDec(&RegisterBank::A);
}

inline int op0x3E()
{
    RegisterBank::A = MMU::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("LD\tA, 0x%02X\n", RegisterBank::A);
    return 8;
}

inline int op0x3F()
{
    printf("Op not implemented: 0x3F\n");
    return -1;
}

inline int op0x40()
{
    Helper::CPULog("LD\tB, B\n");
    return baseLoadReg(&RegisterBank::B, RegisterBank::B);
}

inline int op0x41()
{
    Helper::CPULog("LD\tB, C\n");
    return baseLoadReg(&RegisterBank::B, RegisterBank::C);
}

inline int op0x42()
{
    Helper::CPULog("LD\tB, D\n");
    return baseLoadReg(&RegisterBank::B, RegisterBank::D);
}

inline int op0x43()
{
    Helper::CPULog("LD\tB, E\n");
    return baseLoadReg(&RegisterBank::B, RegisterBank::E);
}

inline int op0x44()
{
    Helper::CPULog("LD\tB, H\n");
    return baseLoadReg(&RegisterBank::B, RegisterBank::H);
}

inline int op0x45()
{
    Helper::CPULog("LD\tB, L\n");
    return baseLoadReg(&RegisterBank::B, RegisterBank::L);
}

inline int op0x46()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("LD\tB, [HL]\n");
    return baseLoadReg(&RegisterBank::B, value) + 4;
}

inline int op0x47()
{
    Helper::CPULog("LD\tB, A\n");
    return baseLoadReg(&RegisterBank::B, RegisterBank::A);
}

inline int op0x48()
{
    Helper::CPULog("LD\tC, B\n");
    return baseLoadReg(&RegisterBank::C, RegisterBank::B);
}

inline int op0x49()
{
    Helper::CPULog("LD\tC, C\n");
    return baseLoadReg(&RegisterBank::C, RegisterBank::C);
}

inline int op0x4A()
{
    Helper::CPULog("LD\tC, D\n");
    return baseLoadReg(&RegisterBank::C, RegisterBank::D);
}

inline int op0x4B()
{
    Helper::CPULog("LD\tC, E\n");
    return baseLoadReg(&RegisterBank::C, RegisterBank::E);
}

inline int op0x4C()
{
    Helper::CPULog("LD\tC, H\n");
    return baseLoadReg(&RegisterBank::C, RegisterBank::H);
}

inline int op0x4D()
{
    Helper::CPULog("LD\tC, L\n");
    return baseLoadReg(&RegisterBank::C, RegisterBank::L);
}

inline int op0x4E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("LD\tC, [HL]\n");
    return baseLoadReg(&RegisterBank::C, value) + 4;
}

inline int op0x4F()
{
    Helper::CPULog("LD\tC, A\n");
    return baseLoadReg(&RegisterBank::C, RegisterBank::A);
}

inline int op0x50()
{
    Helper::CPULog("LD\tD, B\n");
    return baseLoadReg(&RegisterBank::D, RegisterBank::B);
}

inline int op0x51()
{
    Helper::CPULog("LD\tD, C\n");
    return baseLoadReg(&RegisterBank::D, RegisterBank::C);
}

inline int op0x52()
{
    Helper::CPULog("LD\tD, D\n");
    return baseLoadReg(&RegisterBank::D, RegisterBank::D);
}

inline int op0x53()
{
    Helper::CPULog("LD\tD, E\n");
    return baseLoadReg(&RegisterBank::D, RegisterBank::E);
}

inline int op0x54()
{
    Helper::CPULog("LD\tD, H\n");
    return baseLoadReg(&RegisterBank::D, RegisterBank::H);
}

inline int op0x55()
{
    Helper::CPULog("LD\tD, L\n");
    return baseLoadReg(&RegisterBank::D, RegisterBank::L);
}

inline int op0x56()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("LD\tD, [HL]\n");
    return baseLoadReg(&RegisterBank::D, value) + 4;
}

inline int op0x57()
{
    Helper::CPULog("LD\tD, A\n");
    return baseLoadReg(&RegisterBank::D, RegisterBank::A);
}

inline int op0x58()
{
    Helper::CPULog("LD\tE, B\n");
    return baseLoadReg(&RegisterBank::E, RegisterBank::B);
}

inline int op0x59()
{
    Helper::CPULog("LD\tE, C\n");
    return baseLoadReg(&RegisterBank::E, RegisterBank::C);
}

inline int op0x5A()
{
    Helper::CPULog("LD\tE, D\n");
    return baseLoadReg(&RegisterBank::E, RegisterBank::D);
}

inline int op0x5B()
{
    Helper::CPULog("LD\tE, E\n");
    return baseLoadReg(&RegisterBank::E, RegisterBank::E);
}

inline int op0x5C()
{
    Helper::CPULog("LD\tE, H\n");
    return baseLoadReg(&RegisterBank::E, RegisterBank::H);
}

inline int op0x5D()
{
    Helper::CPULog("LD\tE, L\n");
    return baseLoadReg(&RegisterBank::E, RegisterBank::L);
}

inline int op0x5E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("LD\tE, [HL]\n");
    return baseLoadReg(&RegisterBank::E, value) + 4;
}

inline int op0x5F()
{
    Helper::CPULog("LD\tE, A\n");
    return baseLoadReg(&RegisterBank::E, RegisterBank::A);
}

inline int op0x60()
{
    Helper::CPULog("LD\tH, B\n");
    return baseLoadReg(&RegisterBank::H, RegisterBank::B);
}

inline int op0x61()
{
    Helper::CPULog("LD\tH, C\n");
    return baseLoadReg(&RegisterBank::H, RegisterBank::C);
}

inline int op0x62()
{
    Helper::CPULog("LD\tH, D\n");
    return baseLoadReg(&RegisterBank::H, RegisterBank::D);
}

inline int op0x63()
{
    Helper::CPULog("LD\tH, E\n");
    return baseLoadReg(&RegisterBank::H, RegisterBank::E);
}

inline int op0x64()
{
    Helper::CPULog("LD\tH, H\n");
    return baseLoadReg(&RegisterBank::H, RegisterBank::H);
}

inline int op0x65()
{
    Helper::CPULog("LD\tH, L\n");
    return baseLoadReg(&RegisterBank::H, RegisterBank::L);
}

inline int op0x66()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("LD\tH, [HL]\n");
    return baseLoadReg(&RegisterBank::H, value) + 4;
}

inline int op0x67()
{
    Helper::CPULog("LD\tH, A\n");
    return baseLoadReg(&RegisterBank::H, RegisterBank::A);
}

inline int op0x68()
{
    Helper::CPULog("LD\tL, B\n");
    return baseLoadReg(&RegisterBank::L, RegisterBank::B);
}

inline int op0x69()
{
    Helper::CPULog("LD\tL, C\n");
    return baseLoadReg(&RegisterBank::L, RegisterBank::C);
}

inline int op0x6A()
{
    Helper::CPULog("LD\tL, D\n");
    return baseLoadReg(&RegisterBank::L, RegisterBank::D);
}

inline int op0x6B()
{
    Helper::CPULog("LD\tL, E\n");
    return baseLoadReg(&RegisterBank::L, RegisterBank::E);
}

inline int op0x6C()
{
    Helper::CPULog("LD\tL, H\n");
    return baseLoadReg(&RegisterBank::L, RegisterBank::H);
}

inline int op0x6D()
{
    Helper::CPULog("LD\tL, L\n");
    return baseLoadReg(&RegisterBank::L, RegisterBank::L);
}

inline int op0x6E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("LD\tL, [HL]\n");
    return baseLoadReg(&RegisterBank::L, value) + 4;
}

inline int op0x6F()
{
    Helper::CPULog("LD\tL, A\n");
    return baseLoadReg(&RegisterBank::L, RegisterBank::A);
}

inline int op0x70()
{
    MMU::WriteByteAt(RegisterBank::HL(), RegisterBank::B);
    Helper::CPULog("LD\t[HL], B\n");
    return 8;
}

inline int op0x71()
{
    MMU::WriteByteAt(RegisterBank::HL(), RegisterBank::C);
    Helper::CPULog("LD\t[HL], C\n");
    return 8;
}

inline int op0x72()
{
    MMU::WriteByteAt(RegisterBank::HL(), RegisterBank::D);
    Helper::CPULog("LD\t[HL], D\n");
    return 8;;
}

inline int op0x73()
{
    MMU::WriteByteAt(RegisterBank::HL(), RegisterBank::E);
    Helper::CPULog("LD\t[HL], E\n");
    return 8;
}

inline int op0x74()
{
    MMU::WriteByteAt(RegisterBank::HL(), RegisterBank::H);
    Helper::CPULog("LD\t[HL], H\n");
    return 8;
}

inline int op0x75()
{
    MMU::WriteByteAt(RegisterBank::HL(), RegisterBank::L);
    Helper::CPULog("LD\t[HL], L\n");
    return 8;
}

inline int op0x76()
{
    printf("Op not implemented: 0x76\n");
    return -1;
}

inline int op0x77()
{
    MMU::WriteByteAt(RegisterBank::HL(), RegisterBank::A);
    Helper::CPULog("LD\t[HL], A\n");
    return 8;
}

inline int op0x78()
{
    Helper::CPULog("LD\tA, B\n");
    return baseLoadReg(&RegisterBank::A, RegisterBank::B);
}

inline int op0x79()
{
    Helper::CPULog("LD\tA, C\n");
    return baseLoadReg(&RegisterBank::A, RegisterBank::C);
}

inline int op0x7A()
{
    Helper::CPULog("LD\tA, D\n");
    return baseLoadReg(&RegisterBank::A, RegisterBank::D);
}

inline int op0x7B()
{
    Helper::CPULog("LD\tA, E\n");
    return baseLoadReg(&RegisterBank::A, RegisterBank::E);
}

inline int op0x7C()
{
    Helper::CPULog("LD\tA, H\n");
    return baseLoadReg(&RegisterBank::A, RegisterBank::H);
}

inline int op0x7D()
{
    Helper::CPULog("LD\tA, L\n");
    return baseLoadReg(&RegisterBank::A, RegisterBank::L);
}

inline int op0x7E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("LD\tA, [HL]\n");
    return baseLoadReg(&RegisterBank::A, value) + 4;
}

inline int op0x7F()
{
    Helper::CPULog("LD\tA, A\n");
    return baseLoadReg(&RegisterBank::A, RegisterBank::A);
}

inline int op0x80()
{
    Helper::CPULog("ADD\tA, B\n");
    return baseAdd(RegisterBank::B);
}

inline int op0x81()
{
    Helper::CPULog("ADD\tA, C\n");
    return baseAdd(RegisterBank::C);
}

inline int op0x82()
{
    Helper::CPULog("ADD\tA, D\n");
    return baseAdd(RegisterBank::D);
}

inline int op0x83()
{
    Helper::CPULog("ADD\tA, E\n");
    return baseAdd(RegisterBank::E);
}

inline int op0x84()
{
    Helper::CPULog("ADD\tA, H\n");
    return baseAdd(RegisterBank::H);
}

inline int op0x85()
{
    Helper::CPULog("ADD\tA, L\n");
    return baseAdd(RegisterBank::L);
}

inline int op0x86()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("ADD\tA, [0x%04X]\n", RegisterBank::HL());
    return baseAdd(value) + 4;
}

inline int op0x87()
{
    Helper::CPULog("ADD\tA, A\n");
    return baseAdd(RegisterBank::A);
}

inline int op0x88()
{
    Helper::CPULog("ADC\tA, B\n");
    return baseAdc(RegisterBank::B);
}

inline int op0x89()
{
    Helper::CPULog("ADC\tA, C\n");
    return baseAdc(RegisterBank::C);
}

inline int op0x8A()
{
    Helper::CPULog("ADC\tA, D\n");
    return baseAdc(RegisterBank::D);
}

inline int op0x8B()
{
    Helper::CPULog("ADC\tA, E\n");
    return baseAdc(RegisterBank::E);
}

inline int op0x8C()
{
    Helper::CPULog("ADC\tA, H\n");
    return baseAdc(RegisterBank::H);
}

inline int op0x8D()
{
    Helper::CPULog("ADC\tA, L\n");
    return baseAdc(RegisterBank::L);
}

inline int op0x8E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("ADC\tA, [HL]\n");
    return baseAdc(value) + 4;
}

inline int op0x8F()
{
    Helper::CPULog("ADC\tA, A\n");
    return baseAdc(RegisterBank::A);
}

inline int op0x90()
{
    Helper::CPULog("SUB\tB\n");
    return baseSub(RegisterBank::B);
}

inline int op0x91()
{
    Helper::CPULog("SUB\tC\n");
    return baseSub(RegisterBank::C);
}

inline int op0x92()
{
    Helper::CPULog("SUB\tD\n");
    return baseSub(RegisterBank::D);
}

inline int op0x93()
{
    Helper::CPULog("SUB\tE\n");
    return baseSub(RegisterBank::E);
}

inline int op0x94()
{
    Helper::CPULog("SUB\tH\n");
    return baseSub(RegisterBank::H);
}

inline int op0x95()
{
    Helper::CPULog("SUB\tL\n");
    return baseSub(RegisterBank::L);
}

inline int op0x96()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("SUB\t[HL]\n");
    return baseSub(value) + 4;
}

inline int op0x97()
{
    Helper::CPULog("SUB\tA, A\n");
    return baseSub(RegisterBank::A);
}

inline int op0x98()
{
    Helper::CPULog("SBC\tA, B\n");
    return baseSbc(RegisterBank::B);
}

inline int op0x99()
{
    Helper::CPULog("SBC\tA, C\n");
    return baseSbc(RegisterBank::C);
}

inline int op0x9A()
{
    Helper::CPULog("SBC\tA, D\n");
    return baseSbc(RegisterBank::D);
}

inline int op0x9B()
{
    Helper::CPULog("SBC\tA, E\n");
    return baseSbc(RegisterBank::E);
}

inline int op0x9C()
{
    Helper::CPULog("SBC\tA, H\n");
    return baseSbc(RegisterBank::H);
}

inline int op0x9D()
{
    Helper::CPULog("SBC\tA, L\n");
    return baseSbc(RegisterBank::L);
}

inline int op0x9E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("SBC\tA, [HL]\n");
    return baseSbc(value) + 4;
}

inline int op0x9F()
{
    Helper::CPULog("SBC\tA, A\n");
    return baseSbc(RegisterBank::A);
}

inline int op0xA0()
{
    Helper::CPULog("AND\tB\n");
    return baseAnd(RegisterBank::B);
}

inline int op0xA1()
{
    Helper::CPULog("AND\tC\n");
    return baseAnd(RegisterBank::C);
}

inline int op0xA2()
{
    Helper::CPULog("AND\tD\n");
    return baseAnd(RegisterBank::D);
}

inline int op0xA3()
{
    Helper::CPULog("AND\tE\n");
    return baseAnd(RegisterBank::E);
}

inline int op0xA4()
{
    Helper::CPULog("AND\tH\n");
    return baseAnd(RegisterBank::H);
}

inline int op0xA5()
{
    Helper::CPULog("AND\tL\n");
    return baseAnd(RegisterBank::L);
}

inline int op0xA6()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("AND\t[HL]\n");
    return baseAnd(value) + 4;
}

inline int op0xA7()
{
    Helper::CPULog("AND\tA\n");
    return baseAnd(RegisterBank::A);
}

inline int op0xA8()
{
    Helper::CPULog("XOR\tB\n");
    return baseXor(RegisterBank::B);
}

inline int op0xA9()
{
    Helper::CPULog("XOR\tC\n");
    return baseXor(RegisterBank::C);
}

inline int op0xAA()
{
    Helper::CPULog("XOR\tD\n");
    return baseXor(RegisterBank::D);
}

inline int op0xAB()
{
    Helper::CPULog("XOR\tE\n");
    return baseXor(RegisterBank::E);
}

inline int op0xAC()
{
    Helper::CPULog("XOR\tH\n");
    return baseXor(RegisterBank::H);
}

inline int op0xAD()
{
    Helper::CPULog("XOR\tL\n");
    return baseXor(RegisterBank::L);
}

inline int op0xAE()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("XOR\t[HL]\n");
    return baseXor(value) + 4;
}

inline int op0xAF()
{
    Helper::CPULog("XOR\tA\n");
    return baseXor(RegisterBank::A);
}

inline int op0xB0()
{
    Helper::CPULog("OR\tB\n");
    return baseOr(RegisterBank::B);
}

inline int op0xB1()
{
    Helper::CPULog("OR\tC\n");
    return baseOr(RegisterBank::C);
}

inline int op0xB2()
{
    Helper::CPULog("OR\tD\n");
    return baseOr(RegisterBank::D);
}

inline int op0xB3()
{
    Helper::CPULog("OR\tE\n");
    return baseOr(RegisterBank::E);
}

inline int op0xB4()
{
    Helper::CPULog("OR\tH\n");
    return baseOr(RegisterBank::H);
}

inline int op0xB5()
{
    Helper::CPULog("OR\tL\n");
    return baseOr(RegisterBank::L);
}

inline int op0xB6()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("OR\t[HL]\n");
    return baseOr(value) + 4;
}

inline int op0xB7()
{
    Helper::CPULog("OR\tA\n");
    return baseOr(RegisterBank::A);
}

inline int op0xB8()
{
    Helper::CPULog("CP\tB\n");
    return baseCP(RegisterBank::B);
}

inline int op0xB9()
{
    Helper::CPULog("CP\tC\n");
    return baseCP(RegisterBank::C);
}

inline int op0xBA()
{
    Helper::CPULog("CP\tD\n");
    return baseCP(RegisterBank::D);
}

inline int op0xBB()
{
    Helper::CPULog("CP\tE\n");
    return baseCP(RegisterBank::E);
}

inline int op0xBC()
{
    Helper::CPULog("CP\tH\n");
    return baseCP(RegisterBank::H);
}

inline int op0xBD()
{
    Helper::CPULog("CP\tL\n");
    return baseCP(RegisterBank::L);
}

inline int op0xBE()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    Helper::CPULog("CP\t[HL]\n");
    return baseCP(value);
}

inline int op0xBF()
{
    Helper::CPULog("CP\tA\n");
    return baseCP(RegisterBank::A);
}

inline int op0xC0()
{
    int cycles = 8;

    if (!RegisterBank::IsZSet()) {
        RegisterBank::PC = basePop() - 1;
        cycles += 16;
    }

    Helper::CPULog("RET\tNZ\n");
    return cycles;
}

inline int op0xC1()
{
    RegisterBank::BC(basePop());
    Helper::CPULog("POP\tBC(0x%04X)\n", RegisterBank::BC());
    return 12;
}

inline int op0xC2()
{
    int cycles = 12;
    uint16 address = getNextTwoBytes();
    if (!RegisterBank::IsZSet()) {
        RegisterBank::PC = address - 1;
        cycles += 4;
    }
    Helper::CPULog("JP\tNZ, 0x%04X\n", address);
    return cycles;
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
    uint16 address = getNextTwoBytes();
    int cycles = 12;
    if (!RegisterBank::IsZSet()) {
        cycles = 24;
        basePush(++RegisterBank::PC);
        RegisterBank::PC = address - 1;
    }

    Helper::CPULog("CALL\tNZ, 0x%04X\n", address);
    return cycles;
}

inline int op0xC5()
{
    basePush(RegisterBank::BC());
    Helper::CPULog("PUSH\tBC(0x%04X)\n", RegisterBank::BC());
    return 16;
}

inline int op0xC6()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
    baseAdd(value);
    Helper::CPULog("ADD\tA, 0x%02X\n", value);
    return 8;
}

inline int op0xC7()
{
    Helper::CPULog("RST\t0x00\n");
    return baseRST(0x00);
}

inline int op0xC8()
{
    int cycles = 8;

    if (RegisterBank::IsZSet()) {
        RegisterBank::PC = basePop() - 1;
        cycles += 16;
    }

    Helper::CPULog("RET\tZ\n");
    return cycles;
}

inline int op0xC9()
{
    RegisterBank::PC = basePop();
    Helper::CPULog("RET\t(0x%04X)\n", RegisterBank::PC);
    --RegisterBank::PC; //offset the one that gets added.
    return 16;
}

inline int op0xCA()
{
    int cycles = 12;
    uint16 address = getNextTwoBytes();
    if (RegisterBank::IsZSet()) {
        RegisterBank::PC = address - 1;
        cycles += 4;
    }
    Helper::CPULog("JP\tZ, 0x%04X\n", address);
    return cycles;
}

inline int cbBaseRLC(uint8 *op)
{
    bool is7BitSet = Helper::IsBitSet(*op, 7);
    *op <<= 1;
    if (is7BitSet) Helper::SetBit(op, 0);

    RegisterBank::SetZ(*op == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(is7BitSet);
    return 8;
}

inline int cbBaseRRC(uint8 *op)
{
    bool is0BitSet = Helper::IsBitSet(*op, 0);
    *op >>= 1;
    if (is0BitSet) Helper::SetBit(op, 7);

    RegisterBank::SetZ(*op == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(is0BitSet);
    return 8;
}

inline int cbBaseSRL(uint8 *op)
{
    RegisterBank::SetC(Helper::IsBitSet(*op, 0));

    *op >>= 1;

    RegisterBank::SetZ(*op == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);

    return 8;
}

inline int cbBaseRR(uint8 *op)
{
    bool wasBit0Set = Helper::IsBitSet(*op, 0);
    *op >>= 1;
    if (RegisterBank::IsCSet()) Helper::SetBit(op, 7);

    RegisterBank::SetZ(*op == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(wasBit0Set);

    return 8;
}

inline int cbBaseRL(uint8 *op)
{
    bool wasBit7Set = Helper::IsBitSet(*op, 7);
    *op <<= 1;
    if (RegisterBank::IsCSet()) Helper::SetBit(op, 0);

    RegisterBank::SetZ(*op == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(wasBit7Set);

    return 8;
}

inline int cbBaseSLA(uint8 *op)
{
    bool wasBit7Set = Helper::IsBitSet(*op, 7);
    *op <<= 1;

    RegisterBank::SetZ(*op == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(wasBit7Set);
    return 8;
}

inline int cbBaseSRA(uint8 *op)
{
    bool wasBit7Set = Helper::IsBitSet(*op, 7);
    bool wasBit0Set = Helper::IsBitSet(*op, 0);
    *op >>= 1;

    //Make sure MSB is the same as it was
    if (wasBit7Set) Helper::SetBit(op, 7);
    else Helper::ClearBit(op, 7);

    RegisterBank::SetZ(*op == 0);
    RegisterBank::SetN(false);
    RegisterBank::SetH(false);
    RegisterBank::SetC(wasBit0Set);
    return 8;
}

inline int cbBaseBit(int pos, uint8 op)
{
    RegisterBank::SetZ(!Helper::IsBitSet(op, pos));
    RegisterBank::SetN(false);
    RegisterBank::SetH(true);

    return 8;
}

inline int cbBaseRes(int pos, uint8 *op)
{
    Helper::ClearBit(op, pos);
    return 8;
}

inline int cbBaseSet(int pos, uint8 *op)
{
    Helper::SetBit(op, pos);
    return 8;
}

inline int cbOp0x00()
{
    Helper::CPULog("RLC\tB\n");
    return cbBaseRLC(&RegisterBank::B);
}

inline int cbOp0x01()
{
    Helper::CPULog("RLC\tC\n");
    return cbBaseRLC(&RegisterBank::C);
}

inline int cbOp0x02()
{
    Helper::CPULog("RLC\tD\n");
    return cbBaseRLC(&RegisterBank::D);
}

inline int cbOp0x03()
{
    Helper::CPULog("RLC\tE\n");
    return cbBaseRLC(&RegisterBank::E);
}

inline int cbOp0x04()
{
    Helper::CPULog("RLC\tH\n");
    return cbBaseRLC(&RegisterBank::H);
}

inline int cbOp0x05()
{
    Helper::CPULog("RLC\tL\n");
    return cbBaseRLC(&RegisterBank::L);
}

inline int cbOp0x06()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRLC(&value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RLC\t[HL]\n");
    return 16;
}

inline int cbOp0x07()
{
    Helper::CPULog("RLC\tA\n");
    return cbBaseRLC(&RegisterBank::A);
}

inline int cbOp0x08()
{
    Helper::CPULog("RRC\tB\n");
    return cbBaseRRC(&RegisterBank::B);
}

inline int cbOp0x09()
{
    Helper::CPULog("RRC\tC\n");
    return cbBaseRRC(&RegisterBank::C);
}

inline int cbOp0x0A()
{
    Helper::CPULog("RRC\tD\n");
    return cbBaseRRC(&RegisterBank::D);
}

inline int cbOp0x0B()
{
    Helper::CPULog("RRC\tE\n");
    return cbBaseRRC(&RegisterBank::E);
}

inline int cbOp0x0C()
{
    Helper::CPULog("RRC\tH\n");
    return cbBaseRRC(&RegisterBank::H);
}

inline int cbOp0x0D()
{
    Helper::CPULog("RRC\tL\n");
    return cbBaseRRC(&RegisterBank::L);
}

inline int cbOp0x0E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRRC(&value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RRC\t[HL]\n");
    return 16;
}

inline int cbOp0x0F()
{
    Helper::CPULog("RRC\tA\n");
    return cbBaseRRC(&RegisterBank::A);
}

inline int cbOp0x10()
{
    Helper::CPULog("RL\tB\n");
    return cbBaseRL(&RegisterBank::B);
}

inline int cbOp0x11()
{
    Helper::CPULog("RL\tC\n");
    return cbBaseRL(&RegisterBank::C);
}

inline int cbOp0x12()
{
    Helper::CPULog("RL\tD\n");
    return cbBaseRL(&RegisterBank::D);
}

inline int cbOp0x13()
{
    Helper::CPULog("RL\tE\n");
    return cbBaseRL(&RegisterBank::E);
}

inline int cbOp0x14()
{
    Helper::CPULog("RL\tH\n");
    return cbBaseRL(&RegisterBank::H);
}

inline int cbOp0x15()
{
    Helper::CPULog("RL\tL\n");
    return cbBaseRL(&RegisterBank::L);
}

inline int cbOp0x16()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRL(&value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RL\t[HL]\n");
    return 16;
}

inline int cbOp0x17()
{
    Helper::CPULog("RL\tA\n");
    return cbBaseRL(&RegisterBank::A);
}

inline int cbOp0x18()
{
    Helper::CPULog("RR\tB\n");
    return cbBaseRR(&RegisterBank::B);
}

inline int cbOp0x19()
{
    Helper::CPULog("RR\tC\n");
    return cbBaseRR(&RegisterBank::C);
}

inline int cbOp0x1A()
{
    Helper::CPULog("RR\tD\n");
    return cbBaseRR(&RegisterBank::D);
}

inline int cbOp0x1B()
{
    Helper::CPULog("RR\tE\n");
    return cbBaseRR(&RegisterBank::E);
}

inline int cbOp0x1C()
{
    Helper::CPULog("RR\tH\n");
    return cbBaseRR(&RegisterBank::H);
}

inline int cbOp0x1D()
{
    Helper::CPULog("RR\tL\n");
    return cbBaseRR(&RegisterBank::L);
}

inline int cbOp0x1E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRR(&value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("RR\t[HL]\n");
    return 16;
}

inline int cbOp0x1F()
{
    Helper::CPULog("RR\tA\n");
    return cbBaseRR(&RegisterBank::A);
}

inline int cbOp0x20()
{
    Helper::CPULog("SLA\tB\n");
    return cbBaseSLA(&RegisterBank::B);
}

inline int cbOp0x21()
{
    Helper::CPULog("SLA\tC\n");
    return cbBaseSLA(&RegisterBank::C);
}

inline int cbOp0x22()
{
    Helper::CPULog("SLA\tD\n");
    return cbBaseSLA(&RegisterBank::D);
}

inline int cbOp0x23()
{
    Helper::CPULog("SLA\tE\n");
    return cbBaseSLA(&RegisterBank::E);
}

inline int cbOp0x24()
{
    Helper::CPULog("SLA\tH\n");
    return cbBaseSLA(&RegisterBank::H);
}

inline int cbOp0x25()
{
    Helper::CPULog("SLA\tL\n");
    return cbBaseSLA(&RegisterBank::L);
}

inline int cbOp0x26()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSLA(&value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("SLA\t[HL]\n");
    return 16;
}

inline int cbOp0x27()
{
    Helper::CPULog("SLA\tA\n");
    return cbBaseSLA(&RegisterBank::A);
}

inline int cbOp0x28()
{
    Helper::CPULog("SRA\tB\n");
    return cbBaseSRA(&RegisterBank::B);
}

inline int cbOp0x29()
{
    Helper::CPULog("SRA\tC\n");
    return cbBaseSRA(&RegisterBank::C);
}

inline int cbOp0x2A()
{
    Helper::CPULog("SRA\tD\n");
    return cbBaseSRA(&RegisterBank::D);
}

inline int cbOp0x2B()
{
    Helper::CPULog("SRA\tE\n");
    return cbBaseSRA(&RegisterBank::E);
}

inline int cbOp0x2C()
{
    Helper::CPULog("SRA\tH\n");
    return cbBaseSRA(&RegisterBank::H);
}

inline int cbOp0x2D()
{
    Helper::CPULog("SRA\tL\n");
    return cbBaseSRA(&RegisterBank::L);
}

inline int cbOp0x2E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSRA(&value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("SRA\t[HL]\n");
    return 16;
}

inline int cbOp0x2F()
{
    Helper::CPULog("SRA\tA\n");
    return cbBaseSRA(&RegisterBank::A);
}

inline int cbOp0x30()
{
    Helper::CPULog("SWAP\tB\n");
    return baseSwap(&RegisterBank::B);
}

inline int cbOp0x31()
{
    Helper::CPULog("SWAP\tC\n");
    return baseSwap(&RegisterBank::C);
}

inline int cbOp0x32()
{
    Helper::CPULog("SWAP\tD\n");
    return baseSwap(&RegisterBank::D);
}

inline int cbOp0x33()
{
    Helper::CPULog("SWAP\tE\n");
    return baseSwap(&RegisterBank::E);
}

inline int cbOp0x34()
{
    Helper::CPULog("SWAP\tH\n");
    return baseSwap(&RegisterBank::H);
}

inline int cbOp0x35()
{
    Helper::CPULog("SWAP\tL\n");
    return baseSwap(&RegisterBank::L);
}

inline int cbOp0x36()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    baseSwap(&value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("SWAP\t[HL]\n");
    return 16;
}

inline int cbOp0x37()
{
    Helper::CPULog("SWAP\tA\n");
    return baseSwap(&RegisterBank::A);
}

inline int cbOp0x38()
{
    Helper::CPULog("SRL\tB\n");
    return cbBaseSRL(&RegisterBank::B);
}

inline int cbOp0x39()
{
    Helper::CPULog("SRL\tC\n");
    return cbBaseSRL(&RegisterBank::C);
}

inline int cbOp0x3A()
{
    Helper::CPULog("SRL\tD\n");
    return cbBaseSRL(&RegisterBank::D);
}

inline int cbOp0x3B()
{
    Helper::CPULog("SRL\tE\n");
    return cbBaseSRL(&RegisterBank::E);
}

inline int cbOp0x3C()
{
    Helper::CPULog("SRL\tH\n");
    return cbBaseSRL(&RegisterBank::H);
}

inline int cbOp0x3D()
{
    Helper::CPULog("SRL\tL\n");
    return cbBaseSRL(&RegisterBank::L);
}

inline int cbOp0x3E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSRL(&value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("SRL\t[HL]\n");
    return 16;
}

inline int cbOp0x3F()
{
    Helper::CPULog("SRL\tA\n");
    return cbBaseSRL(&RegisterBank::A);
}

inline int cbOp0x40()
{
    Helper::CPULog("BIT\t0, B\n");
    return cbBaseBit(0, RegisterBank::B);
}

inline int cbOp0x41()
{
    Helper::CPULog("BIT\t0, C\n");
    return cbBaseBit(0, RegisterBank::C);
}

inline int cbOp0x42()
{
    Helper::CPULog("BIT\t0, D\n");
    return cbBaseBit(0, RegisterBank::D);
}

inline int cbOp0x43()
{
    Helper::CPULog("BIT\t0, E\n");
    return cbBaseBit(0, RegisterBank::E);
}

inline int cbOp0x44()
{
    Helper::CPULog("BIT\t0, H\n");
    return cbBaseBit(0, RegisterBank::H);
}

inline int cbOp0x45()
{
    Helper::CPULog("BIT\t0, L\n");
    return cbBaseBit(0, RegisterBank::L);
}

inline int cbOp0x46()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());

    Helper::CPULog("BIT\t0, [HL]\n");
    return cbBaseBit(0, value) + 8; //TODO not sure if this is 8, doc says so but I think it should be 4.
}

inline int cbOp0x47()
{
    Helper::CPULog("BIT\t0, A\n");
    return cbBaseBit(0, RegisterBank::A);
}

inline int cbOp0x48()
{
    Helper::CPULog("BIT\t1, B\n");
    return cbBaseBit(1, RegisterBank::B);
}

inline int cbOp0x49()
{
    Helper::CPULog("BIT\t1, C\n");
    return cbBaseBit(1, RegisterBank::C);
}

inline int cbOp0x4A()
{
    Helper::CPULog("BIT\t1, D\n");
    return cbBaseBit(1, RegisterBank::D);
}

inline int cbOp0x4B()
{
    Helper::CPULog("BIT\t1, E\n");
    return cbBaseBit(1, RegisterBank::E);
}

inline int cbOp0x4C()
{
    Helper::CPULog("BIT\t1, H\n");
    return cbBaseBit(1, RegisterBank::H);
}

inline int cbOp0x4D()
{
    Helper::CPULog("BIT\t1, L\n");
    return cbBaseBit(1, RegisterBank::L);
}

inline int cbOp0x4E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());

    Helper::CPULog("BIT\t1, [HL]\n");
    return cbBaseBit(1, value) + 8; //TODO not sure if this is 8, doc says so but I think it should be 4.
}

inline int cbOp0x4F()
{
    Helper::CPULog("BIT\t1, A\n");
    return cbBaseBit(1, RegisterBank::A);
}

inline int cbOp0x50()
{
    Helper::CPULog("BIT\t2, B\n");
    return cbBaseBit(2, RegisterBank::B);
}

inline int cbOp0x51()
{
    Helper::CPULog("BIT\t2, C\n");
    return cbBaseBit(2, RegisterBank::C);
}

inline int cbOp0x52()
{
    Helper::CPULog("BIT\t2, D\n");
    return cbBaseBit(2, RegisterBank::D);
}

inline int cbOp0x53()
{
    Helper::CPULog("BIT\t2, E\n");
    return cbBaseBit(2, RegisterBank::E);
}

inline int cbOp0x54()
{
    Helper::CPULog("BIT\t2, H\n");
    return cbBaseBit(2, RegisterBank::H);
}

inline int cbOp0x55()
{
    Helper::CPULog("BIT\t2, L\n");
    return cbBaseBit(2, RegisterBank::L);
}

inline int cbOp0x56()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());

    Helper::CPULog("BIT\t2, [HL]\n");
    return cbBaseBit(2, value) + 8; //TODO not sure if this is 8, doc says so but I think it should be 4.
}

inline int cbOp0x57()
{
    Helper::CPULog("BIT\t2, A\n");
    return cbBaseBit(2, RegisterBank::A);
}

inline int cbOp0x58()
{
    Helper::CPULog("BIT\t3, B\n");
    return cbBaseBit(3, RegisterBank::B);
}

inline int cbOp0x59()
{
    Helper::CPULog("BIT\t3, C\n");
    return cbBaseBit(3, RegisterBank::C);
}

inline int cbOp0x5A()
{
    Helper::CPULog("BIT\t3, D\n");
    return cbBaseBit(3, RegisterBank::D);
}

inline int cbOp0x5B()
{
    Helper::CPULog("BIT\t3, E\n");
    return cbBaseBit(3, RegisterBank::E);
}

inline int cbOp0x5C()
{
    Helper::CPULog("BIT\t3, H\n");
    return cbBaseBit(3, RegisterBank::H);
}

inline int cbOp0x5D()
{
    Helper::CPULog("BIT\t3, L\n");
    return cbBaseBit(3, RegisterBank::L);
}

inline int cbOp0x5E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());

    Helper::CPULog("BIT\t3, [HL]\n");
    return cbBaseBit(3, value) + 8; //TODO not sure if this is 8, doc says so but I think it should be 4.
}

inline int cbOp0x5F()
{
    Helper::CPULog("BIT\t3, A\n");
    return cbBaseBit(3, RegisterBank::A);
}

inline int cbOp0x60()
{
    Helper::CPULog("BIT\t4, B\n");
    return cbBaseBit(4, RegisterBank::B);
}

inline int cbOp0x61()
{
    Helper::CPULog("BIT\t4, C\n");
    return cbBaseBit(4, RegisterBank::C);
}

inline int cbOp0x62()
{
    Helper::CPULog("BIT\t4, D\n");
    return cbBaseBit(4, RegisterBank::D);
}

inline int cbOp0x63()
{
    Helper::CPULog("BIT\t4, E\n");
    return cbBaseBit(4, RegisterBank::E);
}

inline int cbOp0x64()
{
    Helper::CPULog("BIT\t4, H\n");
    return cbBaseBit(4, RegisterBank::H);
}

inline int cbOp0x65()
{
    Helper::CPULog("BIT\t4, L\n");
    return cbBaseBit(4, RegisterBank::L);
}

inline int cbOp0x66()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());

    Helper::CPULog("BIT\t4, [HL]\n");
    return cbBaseBit(4, value) + 8; //TODO not sure if this is 8, doc says so but I think it should be 4.
}

inline int cbOp0x67()
{
    Helper::CPULog("BIT\t4, A\n");
    return cbBaseBit(4, RegisterBank::A);
}

inline int cbOp0x68()
{
    Helper::CPULog("BIT\t5, B\n");
    return cbBaseBit(5, RegisterBank::B);
}

inline int cbOp0x69()
{
    Helper::CPULog("BIT\t5, C\n");
    return cbBaseBit(5, RegisterBank::C);
}

inline int cbOp0x6A()
{
    Helper::CPULog("BIT\t5, D\n");
    return cbBaseBit(5, RegisterBank::D);
}

inline int cbOp0x6B()
{
    Helper::CPULog("BIT\t5, E\n");
    return cbBaseBit(5, RegisterBank::E);
}

inline int cbOp0x6C()
{
    Helper::CPULog("BIT\t5, H\n");
    return cbBaseBit(5, RegisterBank::H);
}

inline int cbOp0x6D()
{
    Helper::CPULog("BIT\t5, L\n");
    return cbBaseBit(5, RegisterBank::L);
}

inline int cbOp0x6E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());

    Helper::CPULog("BIT\t5, [HL]\n");
    return cbBaseBit(5, value) + 8; //TODO not sure if this is 8, doc says so but I think it should be 4.
}

inline int cbOp0x6F()
{
    Helper::CPULog("BIT\t5, A\n");
    return cbBaseBit(5, RegisterBank::A);
}

inline int cbOp0x70()
{
    Helper::CPULog("BIT\t0, B\n");
    return cbBaseBit(0, RegisterBank::B);
}

inline int cbOp0x71()
{
    Helper::CPULog("BIT\t6, C\n");
    return cbBaseBit(6, RegisterBank::C);
}

inline int cbOp0x72()
{
    Helper::CPULog("BIT\t6, D\n");
    return cbBaseBit(6, RegisterBank::D);
}

inline int cbOp0x73()
{
    Helper::CPULog("BIT\t6, E\n");
    return cbBaseBit(6, RegisterBank::E);
}

inline int cbOp0x74()
{
    Helper::CPULog("BIT\t6, H\n");
    return cbBaseBit(6, RegisterBank::H);
}

inline int cbOp0x75()
{
    Helper::CPULog("BIT\t6, L\n");
    return cbBaseBit(6, RegisterBank::L);
}

inline int cbOp0x76()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());

    Helper::CPULog("BIT\t6, [HL]\n");
    return cbBaseBit(6, value) + 8; //TODO not sure if this is 8, doc says so but I think it should be 4.
}

inline int cbOp0x77()
{
    Helper::CPULog("BIT\t6, A\n");
    return cbBaseBit(6, RegisterBank::A);
}

inline int cbOp0x78()
{
    Helper::CPULog("BIT\t7, B\n");
    return cbBaseBit(7, RegisterBank::B);
}

inline int cbOp0x79()
{
    Helper::CPULog("BIT\t7, C\n");
    return cbBaseBit(7, RegisterBank::C);
}

inline int cbOp0x7A()
{
    Helper::CPULog("BIT\t7, D\n");
    return cbBaseBit(7, RegisterBank::D);
}

inline int cbOp0x7B()
{
    Helper::CPULog("BIT\t7, E\n");
    return cbBaseBit(7, RegisterBank::E);
}

inline int cbOp0x7C()
{
    Helper::CPULog("BIT\t7, H\n");
    return cbBaseBit(7, RegisterBank::H);
}

inline int cbOp0x7D()
{
    Helper::CPULog("BIT\t7, L\n");
    return cbBaseBit(7, RegisterBank::L);
}

inline int cbOp0x7E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());

    Helper::CPULog("BIT\t7, [HL]\n");
    return cbBaseBit(7, value) + 8; //TODO not sure if this is 8, doc says so but I think it should be 4.
}

inline int cbOp0x7F()
{
    Helper::CPULog("BIT\t7, A\n");
    return cbBaseBit(7, RegisterBank::A);
}

inline int cbOp0x80()
{
    Helper::CPULog("RES\t0, B\n");
    return cbBaseRes(0, &RegisterBank::B);
}

inline int cbOp0x81()
{
    Helper::CPULog("RES\t0, C\n");
    return cbBaseRes(0, &RegisterBank::C);
}

inline int cbOp0x82()
{
    Helper::CPULog("RES\t0, D\n");
    return cbBaseRes(0, &RegisterBank::D);
}

inline int cbOp0x83()
{
    Helper::CPULog("RES\t0, E\n");
    return cbBaseRes(0, &RegisterBank::E);
}

inline int cbOp0x84()
{
    Helper::CPULog("RES\t0, H\n");
    return cbBaseRes(0, &RegisterBank::H);
}

inline int cbOp0x85()
{
    Helper::CPULog("RES\t0, L\n");
    return cbBaseRes(0, &RegisterBank::L);
}

inline int cbOp0x86()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRes(0, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RES\t0, [HL]\n");
    return 16;
}

inline int cbOp0x87()
{
    Helper::CPULog("RES\t0, A\n");
    return cbBaseRes(0, &RegisterBank::A);
}

inline int cbOp0x88()
{
    Helper::CPULog("RES\t1, B\n");
    return cbBaseRes(1, &RegisterBank::B);
}

inline int cbOp0x89()
{
    Helper::CPULog("RES\t1, C\n");
    return cbBaseRes(1, &RegisterBank::C);
}

inline int cbOp0x8A()
{
    Helper::CPULog("RES\t1, D\n");
    return cbBaseRes(1, &RegisterBank::D);
}

inline int cbOp0x8B()
{
    Helper::CPULog("RES\t1, E\n");
    return cbBaseRes(1, &RegisterBank::E);
}

inline int cbOp0x8C()
{
    Helper::CPULog("RES\t1, H\n");
    return cbBaseRes(1, &RegisterBank::H);
}

inline int cbOp0x8D()
{
    Helper::CPULog("RES\t1, L\n");
    return cbBaseRes(1, &RegisterBank::L);
}

inline int cbOp0x8E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRes(1, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RES\t1, [HL]\n");
    return 16;
}

inline int cbOp0x8F()
{
    Helper::CPULog("RES\t1, A\n");
    return cbBaseRes(1, &RegisterBank::A);
}

inline int cbOp0x90()
{
    Helper::CPULog("RES\t0, B\n");
    return cbBaseRes(2, &RegisterBank::B);
}

inline int cbOp0x91()
{
    Helper::CPULog("RES\t0, C\n");
    return cbBaseRes(2, &RegisterBank::C);
}

inline int cbOp0x92()
{
    Helper::CPULog("RES\t0, D\n");
    return cbBaseRes(2, &RegisterBank::D);
}

inline int cbOp0x93()
{
    Helper::CPULog("RES\t0, E\n");
    return cbBaseRes(2, &RegisterBank::E);
}

inline int cbOp0x94()
{
    Helper::CPULog("RES\t0, H\n");
    return cbBaseRes(2, &RegisterBank::H);
}

inline int cbOp0x95()
{
    Helper::CPULog("RES\t0, L\n");
    return cbBaseRes(2, &RegisterBank::L);
}

inline int cbOp0x96()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRes(2, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RES\t2, [HL]\n");
    return 16;
}

inline int cbOp0x97()
{
    Helper::CPULog("RES\t2, A\n");
    return cbBaseRes(2, &RegisterBank::A);
}

inline int cbOp0x98()
{
    Helper::CPULog("RES\t3, B\n");
    return cbBaseRes(3, &RegisterBank::B);
}

inline int cbOp0x99()
{
    Helper::CPULog("RES\t3, C\n");
    return cbBaseRes(3, &RegisterBank::C);
}

inline int cbOp0x9A()
{
    Helper::CPULog("RES\t3, D\n");
    return cbBaseRes(3, &RegisterBank::D);
}

inline int cbOp0x9B()
{
    Helper::CPULog("RES\t3, E\n");
    return cbBaseRes(3, &RegisterBank::E);
}

inline int cbOp0x9C()
{
    Helper::CPULog("RES\t3, H\n");
    return cbBaseRes(3, &RegisterBank::H);
}

inline int cbOp0x9D()
{
    Helper::CPULog("RES\t3, L\n");
    return cbBaseRes(3, &RegisterBank::L);
}

inline int cbOp0x9E()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRes(3, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RES\t3, [HL]\n");
    return 16;
}

inline int cbOp0x9F()
{
    Helper::CPULog("RES\t3, A\n");
    return cbBaseRes(3, &RegisterBank::A);
}

inline int cbOp0xA0()
{
    Helper::CPULog("RES\t4, B\n");
    return cbBaseRes(4, &RegisterBank::B);
}

inline int cbOp0xA1()
{
    Helper::CPULog("RES\t4, C\n");
    return cbBaseRes(4, &RegisterBank::C);
}

inline int cbOp0xA2()
{
    Helper::CPULog("RES\t4, D\n");
    return cbBaseRes(4, &RegisterBank::D);
}

inline int cbOp0xA3()
{
    Helper::CPULog("RES\t4, E\n");
    return cbBaseRes(4, &RegisterBank::E);
}

inline int cbOp0xA4()
{
    Helper::CPULog("RES\t4, H\n");
    return cbBaseRes(4, &RegisterBank::H);
}

inline int cbOp0xA5()
{
    Helper::CPULog("RES\t4, L\n");
    return cbBaseRes(4, &RegisterBank::L);
}

inline int cbOp0xA6()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRes(4, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RES\t4, [HL]\n");
    return 16;
}

inline int cbOp0xA7()
{
    Helper::CPULog("RES\t4, A\n");
    return cbBaseRes(0, &RegisterBank::A);
}

inline int cbOp0xA8()
{
    Helper::CPULog("RES\t5, B\n");
    return cbBaseRes(5, &RegisterBank::B);
}

inline int cbOp0xA9()
{
    Helper::CPULog("RES\t5, C\n");
    return cbBaseRes(5, &RegisterBank::C);
}

inline int cbOp0xAA()
{
    Helper::CPULog("RES\t5, D\n");
    return cbBaseRes(5, &RegisterBank::D);
}

inline int cbOp0xAB()
{
    Helper::CPULog("RES\t5, E\n");
    return cbBaseRes(5, &RegisterBank::E);
}

inline int cbOp0xAC()
{
    Helper::CPULog("RES\t5, H\n");
    return cbBaseRes(5, &RegisterBank::H);
}

inline int cbOp0xAD()
{
    Helper::CPULog("RES\t5, L\n");
    return cbBaseRes(5, &RegisterBank::L);
}

inline int cbOp0xAE()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRes(5, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RES\t5, [HL]\n");
    return 16;
}

inline int cbOp0xAF()
{
    Helper::CPULog("RES\t5, A\n");
    return cbBaseRes(5, &RegisterBank::A);
}

inline int cbOp0xB0()
{
    Helper::CPULog("RES\t6, B\n");
    return cbBaseRes(6, &RegisterBank::B);
}

inline int cbOp0xB1()
{
    Helper::CPULog("RES\t6, C\n");
    return cbBaseRes(6, &RegisterBank::C);
}

inline int cbOp0xB2()
{
    Helper::CPULog("RES\t6, D\n");
    return cbBaseRes(6, &RegisterBank::D);
}

inline int cbOp0xB3()
{
    Helper::CPULog("RES\t6, E\n");
    return cbBaseRes(6, &RegisterBank::E);
}

inline int cbOp0xB4()
{
    Helper::CPULog("RES\t6, H\n");
    return cbBaseRes(6, &RegisterBank::H);
}

inline int cbOp0xB5()
{
    Helper::CPULog("RES\t6, L\n");
    return cbBaseRes(6, &RegisterBank::L);
}

inline int cbOp0xB6()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRes(6, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RES\t6, [HL]\n");
    return 16;
}

inline int cbOp0xB7()
{
    Helper::CPULog("RES\t6, A\n");
    return cbBaseRes(6, &RegisterBank::A);
}

inline int cbOp0xB8()
{
    Helper::CPULog("RES\t7, B\n");
    return cbBaseRes(7, &RegisterBank::B);
}

inline int cbOp0xB9()
{
    Helper::CPULog("RES\t7, C\n");
    return cbBaseRes(7, &RegisterBank::C);
}

inline int cbOp0xBA()
{
    Helper::CPULog("RES\t7, D\n");
    return cbBaseRes(7, &RegisterBank::D);
}

inline int cbOp0xBB()
{
    Helper::CPULog("RES\t7, E\n");
    return cbBaseRes(7, &RegisterBank::E);
}

inline int cbOp0xBC()
{
    Helper::CPULog("RES\t7, H\n");
    return cbBaseRes(7, &RegisterBank::H);
}

inline int cbOp0xBD()
{
    Helper::CPULog("RES\t7, L\n");
    return cbBaseRes(7, &RegisterBank::L);
}

inline int cbOp0xBE()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseRes(7, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);
    Helper::CPULog("RES\t7, [HL]\n");
    return 16;
}

inline int cbOp0xBF()
{
    Helper::CPULog("RES\t7, A\n");
    return cbBaseRes(7, &RegisterBank::A);
}

inline int cbOp0xC0()
{
    Helper::CPULog("SET\t0, B\n");
    return  cbBaseSet(0, &RegisterBank::B);
}

inline int cbOp0xC1()
{
    Helper::CPULog("SET\t0, C\n");
    return  cbBaseSet(0, &RegisterBank::C);
}

inline int cbOp0xC2()
{
    Helper::CPULog("SET\t0, D\n");
    return  cbBaseSet(0, &RegisterBank::D);
}

inline int cbOp0xC3()
{
    Helper::CPULog("SET\t0, E\n");
    return  cbBaseSet(0, &RegisterBank::E);
}

inline int cbOp0xC4()
{
    Helper::CPULog("SET\t0, H\n");
    return  cbBaseSet(0, &RegisterBank::H);
}

inline int cbOp0xC5()
{
    Helper::CPULog("SET\t0, L\n");
    return  cbBaseSet(0, &RegisterBank::L);
}

inline int cbOp0xC6()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSet(0, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("SET\t0, [HL]\n");
    return  16;
}

inline int cbOp0xC7()
{
    Helper::CPULog("SET\t0, A\n");
    return  cbBaseSet(0, &RegisterBank::A);
}

inline int cbOp0xC8()
{
    Helper::CPULog("SET\t1, B\n");
    return  cbBaseSet(1, &RegisterBank::B);
}

inline int cbOp0xC9()
{
    Helper::CPULog("SET\t1, C\n");
    return  cbBaseSet(1, &RegisterBank::C);
}

inline int cbOp0xCA()
{
    Helper::CPULog("SET\t1, D\n");
    return  cbBaseSet(1, &RegisterBank::D);
}

inline int cbOp0xCB()
{
    Helper::CPULog("SET\t1, E\n");
    return  cbBaseSet(1, &RegisterBank::E);
}

inline int cbOp0xCC()
{
    Helper::CPULog("SET\t1, H\n");
    return  cbBaseSet(1, &RegisterBank::H);
}

inline int cbOp0xCD()
{
    Helper::CPULog("SET\t1, L\n");
    return  cbBaseSet(1, &RegisterBank::L);
}

inline int cbOp0xCE()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSet(1, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("SET\t1, [HL]\n");
    return  16;
}

inline int cbOp0xCF()
{
    Helper::CPULog("SET\t1, A\n");
    return  cbBaseSet(1, &RegisterBank::A);
}

inline int cbOp0xD0()
{
    Helper::CPULog("SET\t2, B\n");
    return  cbBaseSet(2, &RegisterBank::B);
}

inline int cbOp0xD1()
{
    Helper::CPULog("SET\t2, C\n");
    return  cbBaseSet(2, &RegisterBank::C);
}

inline int cbOp0xD2()
{
    Helper::CPULog("SET\t2, D\n");
    return  cbBaseSet(2, &RegisterBank::D);
}

inline int cbOp0xD3()
{
    Helper::CPULog("SET\t2, E\n");
    return  cbBaseSet(2, &RegisterBank::E);
}

inline int cbOp0xD4()
{
    Helper::CPULog("SET\t2, H\n");
    return  cbBaseSet(2, &RegisterBank::H);
}

inline int cbOp0xD5()
{
    Helper::CPULog("SET\t2, L\n");
    return  cbBaseSet(2, &RegisterBank::L);
}

inline int cbOp0xD6()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSet(2, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("SET\t2, [HL]\n");
    return  16;
}

inline int cbOp0xD7()
{
    Helper::CPULog("SET\t2, A\n");
    return  cbBaseSet(2, &RegisterBank::A);
}

inline int cbOp0xD8()
{
    Helper::CPULog("SET\t3, B\n");
    return  cbBaseSet(3, &RegisterBank::B);
}

inline int cbOp0xD9()
{
    Helper::CPULog("SET\t3, C\n");
    return  cbBaseSet(3, &RegisterBank::C);
}

inline int cbOp0xDA()
{
    Helper::CPULog("SET\t3, D\n");
    return  cbBaseSet(3, &RegisterBank::D);
}

inline int cbOp0xDB()
{
    Helper::CPULog("SET\t3, E\n");
    return  cbBaseSet(3, &RegisterBank::E);
}

inline int cbOp0xDC()
{
    Helper::CPULog("SET\t3, H\n");
    return  cbBaseSet(3, &RegisterBank::H);
}

inline int cbOp0xDD()
{
    Helper::CPULog("SET\t3, L\n");
    return  cbBaseSet(3, &RegisterBank::L);
}

inline int cbOp0xDE()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSet(3, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("SET\t3, [HL]\n");
    return  16;
}

inline int cbOp0xDF()
{
    Helper::CPULog("SET\t3, A\n");
    return  cbBaseSet(3, &RegisterBank::A);
}

inline int cbOp0xE0()
{
    Helper::CPULog("SET\t4, B\n");
    return  cbBaseSet(4, &RegisterBank::B);
}

inline int cbOp0xE1()
{
    Helper::CPULog("SET\t4, C\n");
    return  cbBaseSet(4, &RegisterBank::C);
}

inline int cbOp0xE2()
{
    Helper::CPULog("SET\t4, D\n");
    return  cbBaseSet(4, &RegisterBank::D);
}

inline int cbOp0xE3()
{
    Helper::CPULog("SET\t4, E\n");
    return  cbBaseSet(4, &RegisterBank::E);
}

inline int cbOp0xE4()
{
    Helper::CPULog("SET\t4, H\n");
    return  cbBaseSet(4, &RegisterBank::H);
}

inline int cbOp0xE5()
{
    Helper::CPULog("SET\t4, L\n");
    return  cbBaseSet(4, &RegisterBank::L);
}

inline int cbOp0xE6()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSet(4, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("SET\t4, [HL]\n");
    return  16;
}

inline int cbOp0xE7()
{
    Helper::CPULog("SET\t4, A\n");
    return  cbBaseSet(4, &RegisterBank::A);
}

inline int cbOp0xE8()
{
    Helper::CPULog("SET\t5, B\n");
    return  cbBaseSet(5, &RegisterBank::B);
}

inline int cbOp0xE9()
{
    Helper::CPULog("SET\t5, C\n");
    return  cbBaseSet(5, &RegisterBank::C);
}

inline int cbOp0xEA()
{
    Helper::CPULog("SET\t5, D\n");
    return  cbBaseSet(5, &RegisterBank::D);
}

inline int cbOp0xEB()
{
    Helper::CPULog("SET\t5, E\n");
    return  cbBaseSet(5, &RegisterBank::E);
}

inline int cbOp0xEC()
{
    Helper::CPULog("SET\t5, H\n");
    return  cbBaseSet(5, &RegisterBank::H);
}

inline int cbOp0xED()
{
    Helper::CPULog("SET\t5, L\n");
    return  cbBaseSet(5, &RegisterBank::L);
}

inline int cbOp0xEE()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSet(5, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("SET\t5, [HL]\n");
    return  16;
}

inline int cbOp0xEF()
{
    Helper::CPULog("SET\t5, A\n");
    return  cbBaseSet(5, &RegisterBank::A);
}

inline int cbOp0xF0()
{
    Helper::CPULog("SET\t6, B\n");
    return  cbBaseSet(6, &RegisterBank::B);
}

inline int cbOp0xF1()
{
    Helper::CPULog("SET\t6, C\n");
    return  cbBaseSet(6, &RegisterBank::C);
}

inline int cbOp0xF2()
{
    Helper::CPULog("SET\t6, D\n");
    return  cbBaseSet(6, &RegisterBank::D);
}

inline int cbOp0xF3()
{
    Helper::CPULog("SET\t6, E\n");
    return  cbBaseSet(6, &RegisterBank::E);
}

inline int cbOp0xF4()
{
    Helper::CPULog("SET\t6, H\n");
    return  cbBaseSet(6, &RegisterBank::H);
}

inline int cbOp0xF5()
{
    Helper::CPULog("SET\t6, L\n");
    return  cbBaseSet(6, &RegisterBank::L);
}

inline int cbOp0xF6()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSet(6, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("SET\t6, [HL]\n");
    return  16;
}

inline int cbOp0xF7()
{
    Helper::CPULog("SET\t6, A\n");
    return  cbBaseSet(6, &RegisterBank::A);
}

inline int cbOp0xF8()
{
    Helper::CPULog("SET\t7, B\n");
    return  cbBaseSet(7, &RegisterBank::B);
}

inline int cbOp0xF9()
{
    Helper::CPULog("SET\t7, C\n");
    return  cbBaseSet(7, &RegisterBank::C);
}

inline int cbOp0xFA()
{
    Helper::CPULog("SET\t7, D\n");
    return  cbBaseSet(7, &RegisterBank::D);
}

inline int cbOp0xFB()
{
    Helper::CPULog("SET\t7, E\n");
    return  cbBaseSet(7, &RegisterBank::E);
}

inline int cbOp0xFC()
{
    Helper::CPULog("SET\t7, H\n");
    return  cbBaseSet(7, &RegisterBank::H);
}

inline int cbOp0xFD()
{
    Helper::CPULog("SET\t7, L\n");
    return  cbBaseSet(7, &RegisterBank::L);
}

inline int cbOp0xFE()
{
    uint8 value = MMU::ReadByteAt(RegisterBank::HL());
    cbBaseSet(7, &value);
    MMU::WriteByteAt(RegisterBank::HL(), value);

    Helper::CPULog("SET\t7, [HL]\n");
    return  16;
}

inline int cbOp0xFF()
{
    Helper::CPULog("SET\t7, A\n");
    return  cbBaseSet(7, &RegisterBank::A);
}

inline int op0xCB()
{
    uint8 cb_op = MMU::ReadByteAt(++RegisterBank::PC);
    switch (cb_op) {
        case 0x00: return cbOp0x00();
        case 0x01: return cbOp0x01();
        case 0x02: return cbOp0x02();
        case 0x03: return cbOp0x03();
        case 0x04: return cbOp0x04();
        case 0x05: return cbOp0x05();
        case 0x06: return cbOp0x06();
        case 0x07: return cbOp0x07();
        case 0x08: return cbOp0x08();
        case 0x09: return cbOp0x09();
        case 0x0A: return cbOp0x0A();
        case 0x0B: return cbOp0x0B();
        case 0x0C: return cbOp0x0C();
        case 0x0D: return cbOp0x0D();
        case 0x0E: return cbOp0x0E();
        case 0x0F: return cbOp0x0F();
        case 0x10: return cbOp0x10();
        case 0x11: return cbOp0x11();
        case 0x12: return cbOp0x12();
        case 0x13: return cbOp0x13();
        case 0x14: return cbOp0x14();
        case 0x15: return cbOp0x15();
        case 0x16: return cbOp0x16();
        case 0x17: return cbOp0x17();
        case 0x18: return cbOp0x18();
        case 0x19: return cbOp0x19();
        case 0x1A: return cbOp0x1A();
        case 0x1B: return cbOp0x1B();
        case 0x1C: return cbOp0x1C();
        case 0x1D: return cbOp0x1D();
        case 0x1E: return cbOp0x1E();
        case 0x1F: return cbOp0x1F();
        case 0x20: return cbOp0x20();
        case 0x21: return cbOp0x21();
        case 0x22: return cbOp0x22();
        case 0x23: return cbOp0x23();
        case 0x24: return cbOp0x24();
        case 0x25: return cbOp0x25();
        case 0x26: return cbOp0x26();
        case 0x27: return cbOp0x27();
        case 0x28: return cbOp0x28();
        case 0x29: return cbOp0x29();
        case 0x2A: return cbOp0x2A();
        case 0x2B: return cbOp0x2B();
        case 0x2C: return cbOp0x2C();
        case 0x2D: return cbOp0x2D();
        case 0x2E: return cbOp0x2E();
        case 0x2F: return cbOp0x2F();
        case 0x30: return cbOp0x30();
        case 0x31: return cbOp0x31();
        case 0x32: return cbOp0x32();
        case 0x33: return cbOp0x33();
        case 0x34: return cbOp0x34();
        case 0x35: return cbOp0x35();
        case 0x36: return cbOp0x36();
        case 0x37: return cbOp0x37();
        case 0x38: return cbOp0x38();
        case 0x39: return cbOp0x39();
        case 0x3A: return cbOp0x3A();
        case 0x3B: return cbOp0x3B();
        case 0x3C: return cbOp0x3C();
        case 0x3D: return cbOp0x3D();
        case 0x3E: return cbOp0x3E();
        case 0x3F: return cbOp0x3F();
        case 0x40: return cbOp0x40();
        case 0x41: return cbOp0x41();
        case 0x42: return cbOp0x42();
        case 0x43: return cbOp0x43();
        case 0x44: return cbOp0x44();
        case 0x45: return cbOp0x45();
        case 0x46: return cbOp0x46();
        case 0x47: return cbOp0x47();
        case 0x48: return cbOp0x48();
        case 0x49: return cbOp0x49();
        case 0x4A: return cbOp0x4A();
        case 0x4B: return cbOp0x4B();
        case 0x4C: return cbOp0x4C();
        case 0x4D: return cbOp0x4D();
        case 0x4E: return cbOp0x4E();
        case 0x4F: return cbOp0x4F();
        case 0x50: return cbOp0x50();
        case 0x51: return cbOp0x51();
        case 0x52: return cbOp0x52();
        case 0x53: return cbOp0x53();
        case 0x54: return cbOp0x54();
        case 0x55: return cbOp0x55();
        case 0x56: return cbOp0x56();
        case 0x57: return cbOp0x57();
        case 0x58: return cbOp0x58();
        case 0x59: return cbOp0x59();
        case 0x5A: return cbOp0x5A();
        case 0x5B: return cbOp0x5B();
        case 0x5C: return cbOp0x5C();
        case 0x5D: return cbOp0x5D();
        case 0x5E: return cbOp0x5E();
        case 0x5F: return cbOp0x5F();
        case 0x60: return cbOp0x60();
        case 0x61: return cbOp0x61();
        case 0x62: return cbOp0x62();
        case 0x63: return cbOp0x63();
        case 0x64: return cbOp0x64();
        case 0x65: return cbOp0x65();
        case 0x66: return cbOp0x66();
        case 0x67: return cbOp0x67();
        case 0x68: return cbOp0x68();
        case 0x69: return cbOp0x69();
        case 0x6A: return cbOp0x6A();
        case 0x6B: return cbOp0x6B();
        case 0x6C: return cbOp0x6C();
        case 0x6D: return cbOp0x6D();
        case 0x6E: return cbOp0x6E();
        case 0x6F: return cbOp0x6F();
        case 0x70: return cbOp0x70();
        case 0x71: return cbOp0x71();
        case 0x72: return cbOp0x72();
        case 0x73: return cbOp0x73();
        case 0x74: return cbOp0x74();
        case 0x75: return cbOp0x75();
        case 0x76: return cbOp0x76();
        case 0x77: return cbOp0x77();
        case 0x78: return cbOp0x78();
        case 0x79: return cbOp0x79();
        case 0x7A: return cbOp0x7A();
        case 0x7B: return cbOp0x7B();
        case 0x7C: return cbOp0x7C();
        case 0x7D: return cbOp0x7D();
        case 0x7E: return cbOp0x7E();
        case 0x7F: return cbOp0x7F();
        case 0x80: return cbOp0x80();
        case 0x81: return cbOp0x81();
        case 0x82: return cbOp0x82();
        case 0x83: return cbOp0x83();
        case 0x84: return cbOp0x84();
        case 0x85: return cbOp0x85();
        case 0x86: return cbOp0x86();
        case 0x87: return cbOp0x87();
        case 0x88: return cbOp0x88();
        case 0x89: return cbOp0x89();
        case 0x8A: return cbOp0x8A();
        case 0x8B: return cbOp0x8B();
        case 0x8C: return cbOp0x8C();
        case 0x8D: return cbOp0x8D();
        case 0x8E: return cbOp0x8E();
        case 0x8F: return cbOp0x8F();
        case 0x90: return cbOp0x90();
        case 0x91: return cbOp0x91();
        case 0x92: return cbOp0x92();
        case 0x93: return cbOp0x93();
        case 0x94: return cbOp0x94();
        case 0x95: return cbOp0x95();
        case 0x96: return cbOp0x96();
        case 0x97: return cbOp0x97();
        case 0x98: return cbOp0x98();
        case 0x99: return cbOp0x99();
        case 0x9A: return cbOp0x9A();
        case 0x9B: return cbOp0x9B();
        case 0x9C: return cbOp0x9C();
        case 0x9D: return cbOp0x9D();
        case 0x9E: return cbOp0x9E();
        case 0x9F: return cbOp0x9F();
        case 0xA0: return cbOp0xA0();
        case 0xA1: return cbOp0xA1();
        case 0xA2: return cbOp0xA2();
        case 0xA3: return cbOp0xA3();
        case 0xA4: return cbOp0xA4();
        case 0xA5: return cbOp0xA5();
        case 0xA6: return cbOp0xA6();
        case 0xA7: return cbOp0xA7();
        case 0xA8: return cbOp0xA8();
        case 0xA9: return cbOp0xA9();
        case 0xAA: return cbOp0xAA();
        case 0xAB: return cbOp0xAB();
        case 0xAC: return cbOp0xAC();
        case 0xAD: return cbOp0xAD();
        case 0xAE: return cbOp0xAE();
        case 0xAF: return cbOp0xAF();
        case 0xB0: return cbOp0xB0();
        case 0xB1: return cbOp0xB1();
        case 0xB2: return cbOp0xB2();
        case 0xB3: return cbOp0xB3();
        case 0xB4: return cbOp0xB4();
        case 0xB5: return cbOp0xB5();
        case 0xB6: return cbOp0xB6();
        case 0xB7: return cbOp0xB7();
        case 0xB8: return cbOp0xB8();
        case 0xB9: return cbOp0xB9();
        case 0xBA: return cbOp0xBA();
        case 0xBB: return cbOp0xBB();
        case 0xBC: return cbOp0xBC();
        case 0xBD: return cbOp0xBD();
        case 0xBE: return cbOp0xBE();
        case 0xBF: return cbOp0xBF();
        case 0xC0: return cbOp0xC0();
        case 0xC1: return cbOp0xC1();
        case 0xC2: return cbOp0xC2();
        case 0xC3: return cbOp0xC3();
        case 0xC4: return cbOp0xC4();
        case 0xC5: return cbOp0xC5();
        case 0xC6: return cbOp0xC6();
        case 0xC7: return cbOp0xC7();
        case 0xC8: return cbOp0xC8();
        case 0xC9: return cbOp0xC9();
        case 0xCA: return cbOp0xCA();
        case 0xCB: return cbOp0xCB();
        case 0xCC: return cbOp0xCC();
        case 0xCD: return cbOp0xCD();
        case 0xCE: return cbOp0xCE();
        case 0xCF: return cbOp0xCF();
        case 0xD0: return cbOp0xD0();
        case 0xD1: return cbOp0xD1();
        case 0xD2: return cbOp0xD2();
        case 0xD3: return cbOp0xD3();
        case 0xD4: return cbOp0xD4();
        case 0xD5: return cbOp0xD5();
        case 0xD6: return cbOp0xD6();
        case 0xD7: return cbOp0xD7();
        case 0xD8: return cbOp0xD8();
        case 0xD9: return cbOp0xD9();
        case 0xDA: return cbOp0xDA();
        case 0xDB: return cbOp0xDB();
        case 0xDC: return cbOp0xDC();
        case 0xDD: return cbOp0xDD();
        case 0xDE: return cbOp0xDE();
        case 0xDF: return cbOp0xDF();
        case 0xE0: return cbOp0xE0();
        case 0xE1: return cbOp0xE1();
        case 0xE2: return cbOp0xE2();
        case 0xE3: return cbOp0xE3();
        case 0xE4: return cbOp0xE4();
        case 0xE5: return cbOp0xE5();
        case 0xE6: return cbOp0xE6();
        case 0xE7: return cbOp0xE7();
        case 0xE8: return cbOp0xE8();
        case 0xE9: return cbOp0xE9();
        case 0xEA: return cbOp0xEA();
        case 0xEB: return cbOp0xEB();
        case 0xEC: return cbOp0xEC();
        case 0xED: return cbOp0xED();
        case 0xEE: return cbOp0xEE();
        case 0xEF: return cbOp0xEF();
        case 0xF0: return cbOp0xF0();
        case 0xF1: return cbOp0xF1();
        case 0xF2: return cbOp0xF2();
        case 0xF3: return cbOp0xF3();
        case 0xF4: return cbOp0xF4();
        case 0xF5: return cbOp0xF5();
        case 0xF6: return cbOp0xF6();
        case 0xF7: return cbOp0xF7();
        case 0xF8: return cbOp0xF8();
        case 0xF9: return cbOp0xF9();
        case 0xFA: return cbOp0xFA();
        case 0xFB: return cbOp0xFB();
        case 0xFC: return cbOp0xFC();
        case 0xFD: return cbOp0xFD();
        case 0xFE: return cbOp0xFE();
        case 0xFF: return cbOp0xFF();
        default:printf("NOT IMPLEMENTED CB Prefix(0x%02X)\n", cb_op);
            break;
    }
    return -1;
}

inline int op0xCC()
{
    uint16 address = getNextTwoBytes();
    int cycles = 12;
    if (RegisterBank::IsZSet()) {
        cycles = 24;
        basePush(++RegisterBank::PC);
        RegisterBank::PC = address - 1;
    }

    Helper::CPULog("CALL\tZ, 0x%04X\n", address);
    return cycles;
}

inline int op0xCD()
{
    uint16 funcAddr = getNextTwoBytes();

    basePush(++RegisterBank::PC);

    RegisterBank::PC = funcAddr - 1; //offset the increment that's gonna happen
    Helper::CPULog("CALL\t0x%04X\n", funcAddr);
    return 24;
}

inline int op0xCE()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("ADC\tA, 0x%02X\n", value);
    return baseAdc(value) + 4;
}

inline int op0xCF()
{
    Helper::CPULog("RST\t0x08\n");
    return baseRST(0x08);
}

inline int op0xD0()
{
    int cycles = 8;

    if (!RegisterBank::IsCSet()) {
        RegisterBank::PC = basePop() - 1;
        cycles += 16;
    }

    Helper::CPULog("RET\tNC\n");
    return cycles;
}

inline int op0xD1()
{
    RegisterBank::DE(basePop());
    Helper::CPULog("POP\tDE(0x%04X)\n", RegisterBank::DE());
    return 12;
}

inline int op0xD2()
{
    int cycles = 12;
    uint16 address = getNextTwoBytes();
    if (!RegisterBank::IsCSet()) {
        RegisterBank::PC = address - 1;
        cycles += 4;
    }
    Helper::CPULog("JP\tNC, 0x%04X\n", address);
    return cycles;
}

inline int op0xD3()
{
    printf("Op not implemented: 0xD3\n");
    return -1;
}

inline int op0xD4()
{
    uint16 address = getNextTwoBytes();
    int cycles = 12;
    if (!RegisterBank::IsCSet()) {
        cycles = 24;
        basePush(++RegisterBank::PC);
        RegisterBank::PC = address - 1;
    }

    Helper::CPULog("CALL\tNC, 0x%04X\n", address);
    return cycles;
}

inline int op0xD5()
{
    basePush(RegisterBank::DE());
    Helper::CPULog("PUSH\tDE(0x%04X)\n", RegisterBank::DE());
    return 16;
}

inline int op0xD6()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("SUB\t0x%02X\n", value);
    return baseSub(value) + 4;
}

inline int op0xD7()
{
    Helper::CPULog("RST\t0x10\n");
    return baseRST(0x10);
}

inline int op0xD8()
{
    int cycles = 8;

    if (RegisterBank::IsCSet()) {
        RegisterBank::PC = basePop() - 1;
        cycles += 16;
    }

    Helper::CPULog("RET\tC\n");
    return cycles;
}

inline int op0xD9()
{
    printf("Op not implemented: 0xD9\n");
    return -1;
}

inline int op0xDA()
{
    int cycles = 12;
    uint16 address = getNextTwoBytes();
    if (RegisterBank::IsCSet()) {
        RegisterBank::PC = address - 1;
        cycles += 4;
    }
    Helper::CPULog("JP\tC, 0x%04X\n", address);
    return cycles;
}

inline int op0xDB()
{
    printf("Op not implemented: 0xDB\n");
    return -1;
}

inline int op0xDC()
{
    uint16 address = getNextTwoBytes();
    int cycles = 12;
    if (RegisterBank::IsCSet()) {
        cycles = 24;
        basePush(++RegisterBank::PC);
        RegisterBank::PC = address - 1;
    }

    Helper::CPULog("CALL\tC, 0x%04X\n", address);
    return cycles;
}

inline int op0xDD()
{
    printf("Op not implemented: 0xDD\n");
    return -1;
}

inline int op0xDE()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("SBC\tA, 0x%02X\n", value);
    return baseSbc(value) + 4;
}

inline int op0xDF()
{
    Helper::CPULog("RST\t0x18\n");
    return baseRST(0x18);
}

inline int op0xE0()
{
    uint16 immediate = MMU::ReadByteAt(++RegisterBank::PC) + 0xFF00;
    MMU::WriteByteAt(immediate, RegisterBank::A);
    Helper::CPULog("LDH\t[0x%02X], A\n", immediate);
    return 12;
}

inline int op0xE1()
{
    RegisterBank::HL(basePop());
    Helper::CPULog("POP\tHL(0x%04X)\n", RegisterBank::HL());
    return 12;
}

inline int op0xE2()
{
    MMU::WriteByteAt(0xFF00 + RegisterBank::C, RegisterBank::A);
    Helper::CPULog("LD\t[C], A\n");
    return 8;
}

inline int op0xE3()
{
    printf("Op not implemented: 0xE3\n");
    return -1;
}

inline int op0xE4()
{
    printf("Op not implemented: 0xE4\n");
    return -1;
}

inline int op0xE5()
{
    basePush(RegisterBank::HL());
    Helper::CPULog("PUSH\tHL(0x%04X)\n", RegisterBank::HL());
    return 16;
}

inline int op0xE6()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
    baseAnd(value);
    Helper::CPULog("AND\t0x%02X\n", value);
    return 8;
}

inline int op0xE7()
{
    Helper::CPULog("RST\t0x20\n");
    return baseRST(0x20);
}

inline int op0xE8()
{
    printf("Op not implemented: 0xE8\n");
    return -1;
}

inline int op0xE9()
{
    RegisterBank::PC = RegisterBank::HL() - 1;
    Helper::CPULog("JP\tHL\n");
    return 4;
}

inline int op0xEA()
{
    uint16 address = getNextTwoBytes();
    MMU::WriteByteAt(address, RegisterBank::A);

    Helper::CPULog("LD\t[0x%04X], A\n", address);
    return 16;
}

inline int op0xEB()
{
    printf("Op not implemented: 0xEB\n");
    return -1;
}

inline int op0xEC()
{
    printf("Op not implemented: 0xEC\n");
    return -1;
}

inline int op0xED()
{
    printf("Op not implemented: 0xED\n");
    return -1;
}

inline int op0xEE()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("XOR\t0x%02X\n", value);
    return baseXor(value) + 4;
}

inline int op0xEF()
{
    Helper::CPULog("RST\t0x28\n");
    return baseRST(0x28);
}

inline int op0xF0()
{
    uint16 address = MMU::ReadByteAt(++RegisterBank::PC) + 0xFF00;
    RegisterBank::A = MMU::ReadByteAt(address);
    Helper::CPULog("LD\tA, [0x%04X]\n", address);
    return 12;
}

inline int op0xF1()
{
    uint8 fWas = RegisterBank::F;
    RegisterBank::AF(basePop());
    RegisterBank::F = fWas;
    Helper::CPULog("POP\tAF(0x%04X)\n", RegisterBank::AF());
    return 12;
}

inline int op0xF2()
{
    printf("Op not implemented: 0xF2\n");
    return -1;
}

inline int op0xF3()
{
    RegisterBank::SetInterruptEnabled(false);
    Helper::CPULog("DI\n");
    return 4;
}

inline int op0xF4()
{
    printf("Op not implemented: 0xF4\n");
    return -1;
}

inline int op0xF5()
{
    basePush(RegisterBank::AF());
    Helper::CPULog("PUSH\tAF(0x%04X)\n", RegisterBank::AF());
    return 16;
}

inline int op0xF6()
{
    uint8 value = MMU::ReadByteAt(++RegisterBank::PC);
    Helper::CPULog("OR\t0x%02X\n", value);
    return baseOr(value);
}

inline int op0xF7()
{
    Helper::CPULog("RST\t0x30\n");
    return baseRST(0x30);
}

inline int op0xF8()
{
    int8 value = MMU::ReadByteAt(++RegisterBank::PC);
    uint32 result = RegisterBank::SP + value;
    uint16 halfResult = (RegisterBank::SP & 0b11111111) + value;
    RegisterBank::HL(result);

    RegisterBank::SetZ(false);
    RegisterBank::SetN(false);
    RegisterBank::SetH(halfResult > UINT8_MAX);
    RegisterBank::SetC(result > UINT16_MAX);

    Helper::CPULog("LD\tHL, SP+%d", value);
    return 12;
}

inline int op0xF9()
{
    RegisterBank::SP = RegisterBank::HL();
    Helper::CPULog("LD\tSP, HL\n");
    return 8;
}

inline int op0xFA()
{
    uint16 address = getNextTwoBytes();
    Helper::CPULog("LD\tA, [0x%04X]\n", address);
    return baseLoadReg(&RegisterBank::A, MMU::ReadByteAt(address)) + 3*4;
}

inline int op0xFB()
{
    RegisterBank::SetInterruptEnabled(true);
    Helper::CPULog("EI\n");
    return 4;
}

inline int op0xFC()
{
    printf("Op not implemented: 0xFC\n");
    return -1;
}

inline int op0xFD()
{
    printf("Op not implemented: 0xFD\n");
    return -1;
}

inline int op0xFE()
{
    uint8 immediate = MMU::ReadByteAt(++RegisterBank::PC);

    Helper::CPULog("CP\t0x%02X (0x%02X)\n", immediate, RegisterBank::A);
    return baseCP(immediate) + 4;
}

inline int op0xFF()
{
    Helper::CPULog("RST\t0x38\n");
    return baseRST(0x38);
}

int Processor::decodeInstr(uint16 address)
{
    uint8 op_code = MMU::ReadByteAt(address);
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

void printRegisters()
{
    Helper::CPULog(
            "\e[A\t\t\t\t\t\t\t| AF: 0x%04X, BC: 0x%04X, DE: 0x%04X, HL: 0x%04X, SP: 0x%04X\n",
            RegisterBank::AF(),
            RegisterBank::BC(),
            RegisterBank::DE(),
            RegisterBank::HL(),
            RegisterBank::SP
            );
}

void Processor::StartCPULoop()
{
    Helper::Log("Start CPU loop");
    int status = 1;
    while (status > 0) {
        //Fetch and Decode
        status = decodeInstr(RegisterBank::PC);
        RegisterBank::PC++;


        //Handle Interrupts
        if (
                RegisterBank::AreInterruptsEnabled() &&
                RegisterBank::InterruptEnable() &&
                RegisterBank::InterruptFlag()
                ) {
            for (int i = 0; i < 5; ++i) {
                if (
                        Helper::IsBitSet(RegisterBank::InterruptEnable(), i) &&
                        Helper::IsBitSet(RegisterBank::InterruptFlag(), i)
                        ) {
                    //Reset IF
                    RegisterBank::ClearBitInIF(i);

                    //Turn off interrupts
                    RegisterBank::SetInterruptEnabled(false);

                    //Push PC
                    basePush(RegisterBank::PC);

                    RegisterBank::PC = 0x40 + i * 0x8;

                    status += 12; //TODO not sure if this is 12 or 8
                    break; //TODO: not use break?
                }
            }
        }


        //Notify other components of the cycles passed
        EventMiddleware::PublishCpuCyclesPassed(status);

        #ifdef REGISTERS
        printRegisters();
        #endif
    }
}
