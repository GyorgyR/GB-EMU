//
// Created by gyorgy on 11/08/18.
//

#include "Decoder.h"
#include "ROM.h"
#include <cstdio>

Decoder::~Decoder()
{
}

Decoder::Decoder(uint8_t* _rom) : rom(_rom)
{
}

inline int op0x00(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x00\n");
    return -1;
}

inline int op0x01(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x01\n");
    return -1;
}

inline int op0x02(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x02\n");
    return -1;
}

inline int op0x03(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x03\n");
    return -1;
}

inline int op0x04(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x04\n");
    return -1;
}

inline int op0x05(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x05\n");
    return -1;
}

inline int op0x06(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x06\n");
    return -1;
}

inline int op0x07(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x07\n");
    return -1;
}

inline int op0x08(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x08\n");
    return -1;
}

inline int op0x09(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x09\n");
    return -1;
}

inline int op0x0A(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x0A\n");
    return -1;
}

inline int op0x0B(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x0B\n");
    return -1;
}

inline int op0x0C(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x0C\n");
    return -1;
}

inline int op0x0D(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x0D\n");
    return -1;
}

inline int op0x0E(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x0E\n");
    return -1;
}

inline int op0x0F(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x0F\n");
    return -1;
}

inline int op0x10(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x10\n");
    return -1;
}

inline int op0x11(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x11\n");
    return -1;
}

inline int op0x12(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x12\n");
    return -1;
}

inline int op0x13(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x13\n");
    return -1;
}

inline int op0x14(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x14\n");
    return -1;
}

inline int op0x15(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x15\n");
    return -1;
}

inline int op0x16(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x16\n");
    return -1;
}

inline int op0x17(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x17\n");
    return -1;
}

inline int op0x18(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x18\n");
    return -1;
}

inline int op0x19(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x19\n");
    return -1;
}

inline int op0x1A(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x1A\n");
    return -1;
}

inline int op0x1B(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x1B\n");
    return -1;
}

inline int op0x1C(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x1C\n");
    return -1;
}

inline int op0x1D(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x1D\n");
    return -1;
}

inline int op0x1E(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x1E\n");
    return -1;
}

inline int op0x1F(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x1F\n");
    return -1;
}

inline int op0x20(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x20\n");
    return -1;
}

inline int op0x21(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x21\n");
    return -1;
}

inline int op0x22(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x22\n");
    return -1;
}

inline int op0x23(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x23\n");
    return -1;
}

inline int op0x24(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x24\n");
    return -1;
}

inline int op0x25(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x25\n");
    return -1;
}

inline int op0x26(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x26\n");
    return -1;
}

inline int op0x27(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x27\n");
    return -1;
}

inline int op0x28(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x28\n");
    return -1;
}

inline int op0x29(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x29\n");
    return -1;
}

inline int op0x2A(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x2A\n");
    return -1;
}

inline int op0x2B(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x2B\n");
    return -1;
}

inline int op0x2C(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x2C\n");
    return -1;
}

inline int op0x2D(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x2D\n");
    return -1;
}

inline int op0x2E(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x2E\n");
    return -1;
}

inline int op0x2F(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x2F\n");
    return -1;
}

inline int op0x30(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x30\n");
    return -1;
}

inline int op0x31(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x31\n");
    return -1;
}

inline int op0x32(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x32\n");
    return -1;
}

inline int op0x33(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x33\n");
    return -1;
}

inline int op0x34(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x34\n");
    return -1;
}

inline int op0x35(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x35\n");
    return -1;
}

inline int op0x36(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x36\n");
    return -1;
}

inline int op0x37(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x37\n");
    return -1;
}

inline int op0x38(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x38\n");
    return -1;
}

inline int op0x39(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x39\n");
    return -1;
}

inline int op0x3A(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x3A\n");
    return -1;
}

inline int op0x3B(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x3B\n");
    return -1;
}

inline int op0x3C(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x3C\n");
    return -1;
}

inline int op0x3D(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x3D\n");
    return -1;
}

inline int op0x3E(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x3E\n");
    return -1;
}

inline int op0x3F(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x3F\n");
    return -1;
}

inline int op0x40(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x40\n");
    return -1;
}

inline int op0x41(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x41\n");
    return -1;
}

inline int op0x42(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x42\n");
    return -1;
}

inline int op0x43(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x43\n");
    return -1;
}

inline int op0x44(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x44\n");
    return -1;
}

inline int op0x45(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x45\n");
    return -1;
}

inline int op0x46(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x46\n");
    return -1;
}

inline int op0x47(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x47\n");
    return -1;
}

inline int op0x48(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x48\n");
    return -1;
}

inline int op0x49(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x49\n");
    return -1;
}

inline int op0x4A(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x4A\n");
    return -1;
}

inline int op0x4B(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x4B\n");
    return -1;
}

inline int op0x4C(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x4C\n");
    return -1;
}

inline int op0x4D(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x4D\n");
    return -1;
}

inline int op0x4E(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x4E\n");
    return -1;
}

inline int op0x4F(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x4F\n");
    return -1;
}

inline int op0x50(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x50\n");
    return -1;
}

inline int op0x51(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x51\n");
    return -1;
}

inline int op0x52(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x52\n");
    return -1;
}

inline int op0x53(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x53\n");
    return -1;
}

inline int op0x54(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x54\n");
    return -1;
}

inline int op0x55(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x55\n");
    return -1;
}

inline int op0x56(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x56\n");
    return -1;
}

inline int op0x57(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x57\n");
    return -1;
}

inline int op0x58(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x58\n");
    return -1;
}

inline int op0x59(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x59\n");
    return -1;
}

inline int op0x5A(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x5A\n");
    return -1;
}

inline int op0x5B(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x5B\n");
    return -1;
}

inline int op0x5C(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x5C\n");
    return -1;
}

inline int op0x5D(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x5D\n");
    return -1;
}

inline int op0x5E(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x5E\n");
    return -1;
}

inline int op0x5F(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x5F\n");
    return -1;
}

inline int op0x60(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x60\n");
    return -1;
}

inline int op0x61(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x61\n");
    return -1;
}

inline int op0x62(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x62\n");
    return -1;
}

inline int op0x63(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x63\n");
    return -1;
}

inline int op0x64(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x64\n");
    return -1;
}

inline int op0x65(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x65\n");
    return -1;
}

inline int op0x66(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x66\n");
    return -1;
}

inline int op0x67(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x67\n");
    return -1;
}

inline int op0x68(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x68\n");
    return -1;
}

inline int op0x69(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x69\n");
    return -1;
}

inline int op0x6A(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x6A\n");
    return -1;
}

inline int op0x6B(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x6B\n");
    return -1;
}

inline int op0x6C(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x6C\n");
    return -1;
}

inline int op0x6D(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x6D\n");
    return -1;
}

inline int op0x6E(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x6E\n");
    return -1;
}

inline int op0x6F(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x6F\n");
    return -1;
}

inline int op0x70(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x70\n");
    return -1;
}

inline int op0x71(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x71\n");
    return -1;
}

inline int op0x72(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x72\n");
    return -1;
}

inline int op0x73(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x73\n");
    return -1;
}

inline int op0x74(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x74\n");
    return -1;
}

inline int op0x75(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x75\n");
    return -1;
}

inline int op0x76(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x76\n");
    return -1;
}

inline int op0x77(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x77\n");
    return -1;
}

inline int op0x78(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x78\n");
    return -1;
}

inline int op0x79(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x79\n");
    return -1;
}

inline int op0x7A(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x7A\n");
    return -1;
}

inline int op0x7B(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x7B\n");
    return -1;
}

inline int op0x7C(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x7C\n");
    return -1;
}

inline int op0x7D(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x7D\n");
    return -1;
}

inline int op0x7E(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x7E\n");
    return -1;
}

inline int op0x7F(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x7F\n");
    return -1;
}

inline int op0x80(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x80\n");
    return -1;
}

inline int op0x81(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x81\n");
    return -1;
}

inline int op0x82(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x82\n");
    return -1;
}

inline int op0x83(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x83\n");
    return -1;
}

inline int op0x84(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x84\n");
    return -1;
}

inline int op0x85(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x85\n");
    return -1;
}

inline int op0x86(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x86\n");
    return -1;
}

inline int op0x87(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x87\n");
    return -1;
}

inline int op0x88(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x88\n");
    return -1;
}

inline int op0x89(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x89\n");
    return -1;
}

inline int op0x8A(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x8A\n");
    return -1;
}

inline int op0x8B(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x8B\n");
    return -1;
}

inline int op0x8C(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x8C\n");
    return -1;
}

inline int op0x8D(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x8D\n");
    return -1;
}

inline int op0x8E(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x8E\n");
    return -1;
}

inline int op0x8F(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x8F\n");
    return -1;
}

inline int op0x90(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x90\n");
    return -1;
}

inline int op0x91(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x91\n");
    return -1;
}

inline int op0x92(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x92\n");
    return -1;
}

inline int op0x93(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x93\n");
    return -1;
}

inline int op0x94(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x94\n");
    return -1;
}

inline int op0x95(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x95\n");
    return -1;
}

inline int op0x96(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x96\n");
    return -1;
}

inline int op0x97(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x97\n");
    return -1;
}

inline int op0x98(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x98\n");
    return -1;
}

inline int op0x99(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x99\n");
    return -1;
}

inline int op0x9A(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x9A\n");
    return -1;
}

inline int op0x9B(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x9B\n");
    return -1;
}

inline int op0x9C(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x9C\n");
    return -1;
}

inline int op0x9D(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x9D\n");
    return -1;
}

inline int op0x9E(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x9E\n");
    return -1;
}

inline int op0x9F(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0x9F\n");
    return -1;
}

inline int op0xA0(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xA0\n");
    return -1;
}

inline int op0xA1(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xA1\n");
    return -1;
}

inline int op0xA2(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xA2\n");
    return -1;
}

inline int op0xA3(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xA3\n");
    return -1;
}

inline int op0xA4(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xA4\n");
    return -1;
}

inline int op0xA5(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xA5\n");
    return -1;
}

inline int op0xA6(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xA6\n");
    return -1;
}

inline int op0xA7(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xA7\n");
    return -1;
}

inline int op0xA8(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xA8\n");
    return -1;
}

inline int op0xA9(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xA9\n");
    return -1;
}

inline int op0xAA(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xAA\n");
    return -1;
}

inline int op0xAB(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xAB\n");
    return -1;
}

inline int op0xAC(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xAC\n");
    return -1;
}

inline int op0xAD(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xAD\n");
    return -1;
}

inline int op0xAE(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xAE\n");
    return -1;
}

inline int op0xAF(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xAF\n");
    return -1;
}

inline int op0xB0(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xB0\n");
    return -1;
}

inline int op0xB1(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xB1\n");
    return -1;
}

inline int op0xB2(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xB2\n");
    return -1;
}

inline int op0xB3(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xB3\n");
    return -1;
}

inline int op0xB4(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xB4\n");
    return -1;
}

inline int op0xB5(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xB5\n");
    return -1;
}

inline int op0xB6(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xB6\n");
    return -1;
}

inline int op0xB7(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xB7\n");
    return -1;
}

inline int op0xB8(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xB8\n");
    return -1;
}

inline int op0xB9(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xB9\n");
    return -1;
}

inline int op0xBA(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xBA\n");
    return -1;
}

inline int op0xBB(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xBB\n");
    return -1;
}

inline int op0xBC(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xBC\n");
    return -1;
}

inline int op0xBD(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xBD\n");
    return -1;
}

inline int op0xBE(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xBE\n");
    return -1;
}

inline int op0xBF(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xBF\n");
    return -1;
}

inline int op0xC0(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xC0\n");
    return -1;
}

inline int op0xC1(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xC1\n");
    return -1;
}

inline int op0xC2(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xC2\n");
    return -1;
}

inline int op0xC3(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xC3\n");
    return -1;
}

inline int op0xC4(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xC4\n");
    return -1;
}

inline int op0xC5(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xC5\n");
    return -1;
}

inline int op0xC6(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xC6\n");
    return -1;
}

inline int op0xC7(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xC7\n");
    return -1;
}

inline int op0xC8(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xC8\n");
    return -1;
}

inline int op0xC9(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xC9\n");
    return -1;
}

inline int op0xCA(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xCA\n");
    return -1;
}

inline int op0xCB(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xCB\n");
    return -1;
}

inline int op0xCC(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xCC\n");
    return -1;
}

inline int op0xCD(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xCD\n");
    return -1;
}

inline int op0xCE(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xCE\n");
    return -1;
}

inline int op0xCF(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xCF\n");
    return -1;
}

inline int op0xD0(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xD0\n");
    return -1;
}

inline int op0xD1(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xD1\n");
    return -1;
}

inline int op0xD2(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xD2\n");
    return -1;
}

inline int op0xD3(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xD3\n");
    return -1;
}

inline int op0xD4(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xD4\n");
    return -1;
}

inline int op0xD5(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xD5\n");
    return -1;
}

inline int op0xD6(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xD6\n");
    return -1;
}

inline int op0xD7(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xD7\n");
    return -1;
}

inline int op0xD8(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xD8\n");
    return -1;
}

inline int op0xD9(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xD9\n");
    return -1;
}

inline int op0xDA(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xDA\n");
    return -1;
}

inline int op0xDB(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xDB\n");
    return -1;
}

inline int op0xDC(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xDC\n");
    return -1;
}

inline int op0xDD(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xDD\n");
    return -1;
}

inline int op0xDE(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xDE\n");
    return -1;
}

inline int op0xDF(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xDF\n");
    return -1;
}

inline int op0xE0(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xE0\n");
    return -1;
}

inline int op0xE1(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xE1\n");
    return -1;
}

inline int op0xE2(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xE2\n");
    return -1;
}

inline int op0xE3(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xE3\n");
    return -1;
}

inline int op0xE4(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xE4\n");
    return -1;
}

inline int op0xE5(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xE5\n");
    return -1;
}

inline int op0xE6(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xE6\n");
    return -1;
}

inline int op0xE7(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xE7\n");
    return -1;
}

inline int op0xE8(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xE8\n");
    return -1;
}

inline int op0xE9(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xE9\n");
    return -1;
}

inline int op0xEA(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xEA\n");
    return -1;
}

inline int op0xEB(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xEB\n");
    return -1;
}

inline int op0xEC(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xEC\n");
    return -1;
}

inline int op0xED(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xED\n");
    return -1;
}

inline int op0xEE(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xEE\n");
    return -1;
}

inline int op0xEF(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xEF\n");
    return -1;
}

inline int op0xF0(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xF0\n");
    return -1;
}

inline int op0xF1(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xF1\n");
    return -1;
}

inline int op0xF2(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xF2\n");
    return -1;
}

inline int op0xF3(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xF3\n");
    return -1;
}

inline int op0xF4(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xF4\n");
    return -1;
}

inline int op0xF5(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xF5\n");
    return -1;
}

inline int op0xF6(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xF6\n");
    return -1;
}

inline int op0xF7(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xF7\n");
    return -1;
}

inline int op0xF8(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xF8\n");
    return -1;
}

inline int op0xF9(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xF9\n");
    return -1;
}

inline int op0xFA(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xFA\n");
    return -1;
}

inline int op0xFB(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xFB\n");
    return -1;
}

inline int op0xFC(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xFC\n");
    return -1;
}

inline int op0xFD(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xFD\n");
    return -1;
}

inline int op0xFE(uint16_t address, uint8_t* rom)
{
    printf("Op not implemented: 0xFE\n");
    return -1;
}

int Decoder::DecodeInstr(uint16_t address)
{
    uint8_t op_code = ROM::GetByteAt(address);
    switch(op_code) {
        case 0x00: return op0x00(address, rom);
        case 0x01: return op0x01(address, rom);
        case 0x02: return op0x02(address, rom);
        case 0x03: return op0x03(address, rom);
        case 0x04: return op0x04(address, rom);
        case 0x05: return op0x05(address, rom);
        case 0x06: return op0x06(address, rom);
        case 0x07: return op0x07(address, rom);
        case 0x08: return op0x08(address, rom);
        case 0x09: return op0x09(address, rom);
        case 0x0A: return op0x0A(address, rom);
        case 0x0B: return op0x0B(address, rom);
        case 0x0C: return op0x0C(address, rom);
        case 0x0D: return op0x0D(address, rom);
        case 0x0E: return op0x0E(address, rom);
        case 0x0F: return op0x0F(address, rom);
        case 0x10: return op0x10(address, rom);
        case 0x11: return op0x11(address, rom);
        case 0x12: return op0x12(address, rom);
        case 0x13: return op0x13(address, rom);
        case 0x14: return op0x14(address, rom);
        case 0x15: return op0x15(address, rom);
        case 0x16: return op0x16(address, rom);
        case 0x17: return op0x17(address, rom);
        case 0x18: return op0x18(address, rom);
        case 0x19: return op0x19(address, rom);
        case 0x1A: return op0x1A(address, rom);
        case 0x1B: return op0x1B(address, rom);
        case 0x1C: return op0x1C(address, rom);
        case 0x1D: return op0x1D(address, rom);
        case 0x1E: return op0x1E(address, rom);
        case 0x1F: return op0x1F(address, rom);
        case 0x20: return op0x20(address, rom);
        case 0x21: return op0x21(address, rom);
        case 0x22: return op0x22(address, rom);
        case 0x23: return op0x23(address, rom);
        case 0x24: return op0x24(address, rom);
        case 0x25: return op0x25(address, rom);
        case 0x26: return op0x26(address, rom);
        case 0x27: return op0x27(address, rom);
        case 0x28: return op0x28(address, rom);
        case 0x29: return op0x29(address, rom);
        case 0x2A: return op0x2A(address, rom);
        case 0x2B: return op0x2B(address, rom);
        case 0x2C: return op0x2C(address, rom);
        case 0x2D: return op0x2D(address, rom);
        case 0x2E: return op0x2E(address, rom);
        case 0x2F: return op0x2F(address, rom);
        case 0x30: return op0x30(address, rom);
        case 0x31: return op0x31(address, rom);
        case 0x32: return op0x32(address, rom);
        case 0x33: return op0x33(address, rom);
        case 0x34: return op0x34(address, rom);
        case 0x35: return op0x35(address, rom);
        case 0x36: return op0x36(address, rom);
        case 0x37: return op0x37(address, rom);
        case 0x38: return op0x38(address, rom);
        case 0x39: return op0x39(address, rom);
        case 0x3A: return op0x3A(address, rom);
        case 0x3B: return op0x3B(address, rom);
        case 0x3C: return op0x3C(address, rom);
        case 0x3D: return op0x3D(address, rom);
        case 0x3E: return op0x3E(address, rom);
        case 0x3F: return op0x3F(address, rom);
        case 0x40: return op0x40(address, rom);
        case 0x41: return op0x41(address, rom);
        case 0x42: return op0x42(address, rom);
        case 0x43: return op0x43(address, rom);
        case 0x44: return op0x44(address, rom);
        case 0x45: return op0x45(address, rom);
        case 0x46: return op0x46(address, rom);
        case 0x47: return op0x47(address, rom);
        case 0x48: return op0x48(address, rom);
        case 0x49: return op0x49(address, rom);
        case 0x4A: return op0x4A(address, rom);
        case 0x4B: return op0x4B(address, rom);
        case 0x4C: return op0x4C(address, rom);
        case 0x4D: return op0x4D(address, rom);
        case 0x4E: return op0x4E(address, rom);
        case 0x4F: return op0x4F(address, rom);
        case 0x50: return op0x50(address, rom);
        case 0x51: return op0x51(address, rom);
        case 0x52: return op0x52(address, rom);
        case 0x53: return op0x53(address, rom);
        case 0x54: return op0x54(address, rom);
        case 0x55: return op0x55(address, rom);
        case 0x56: return op0x56(address, rom);
        case 0x57: return op0x57(address, rom);
        case 0x58: return op0x58(address, rom);
        case 0x59: return op0x59(address, rom);
        case 0x5A: return op0x5A(address, rom);
        case 0x5B: return op0x5B(address, rom);
        case 0x5C: return op0x5C(address, rom);
        case 0x5D: return op0x5D(address, rom);
        case 0x5E: return op0x5E(address, rom);
        case 0x5F: return op0x5F(address, rom);
        case 0x60: return op0x60(address, rom);
        case 0x61: return op0x61(address, rom);
        case 0x62: return op0x62(address, rom);
        case 0x63: return op0x63(address, rom);
        case 0x64: return op0x64(address, rom);
        case 0x65: return op0x65(address, rom);
        case 0x66: return op0x66(address, rom);
        case 0x67: return op0x67(address, rom);
        case 0x68: return op0x68(address, rom);
        case 0x69: return op0x69(address, rom);
        case 0x6A: return op0x6A(address, rom);
        case 0x6B: return op0x6B(address, rom);
        case 0x6C: return op0x6C(address, rom);
        case 0x6D: return op0x6D(address, rom);
        case 0x6E: return op0x6E(address, rom);
        case 0x6F: return op0x6F(address, rom);
        case 0x70: return op0x70(address, rom);
        case 0x71: return op0x71(address, rom);
        case 0x72: return op0x72(address, rom);
        case 0x73: return op0x73(address, rom);
        case 0x74: return op0x74(address, rom);
        case 0x75: return op0x75(address, rom);
        case 0x76: return op0x76(address, rom);
        case 0x77: return op0x77(address, rom);
        case 0x78: return op0x78(address, rom);
        case 0x79: return op0x79(address, rom);
        case 0x7A: return op0x7A(address, rom);
        case 0x7B: return op0x7B(address, rom);
        case 0x7C: return op0x7C(address, rom);
        case 0x7D: return op0x7D(address, rom);
        case 0x7E: return op0x7E(address, rom);
        case 0x7F: return op0x7F(address, rom);
        case 0x80: return op0x80(address, rom);
        case 0x81: return op0x81(address, rom);
        case 0x82: return op0x82(address, rom);
        case 0x83: return op0x83(address, rom);
        case 0x84: return op0x84(address, rom);
        case 0x85: return op0x85(address, rom);
        case 0x86: return op0x86(address, rom);
        case 0x87: return op0x87(address, rom);
        case 0x88: return op0x88(address, rom);
        case 0x89: return op0x89(address, rom);
        case 0x8A: return op0x8A(address, rom);
        case 0x8B: return op0x8B(address, rom);
        case 0x8C: return op0x8C(address, rom);
        case 0x8D: return op0x8D(address, rom);
        case 0x8E: return op0x8E(address, rom);
        case 0x8F: return op0x8F(address, rom);
        case 0x90: return op0x90(address, rom);
        case 0x91: return op0x91(address, rom);
        case 0x92: return op0x92(address, rom);
        case 0x93: return op0x93(address, rom);
        case 0x94: return op0x94(address, rom);
        case 0x95: return op0x95(address, rom);
        case 0x96: return op0x96(address, rom);
        case 0x97: return op0x97(address, rom);
        case 0x98: return op0x98(address, rom);
        case 0x99: return op0x99(address, rom);
        case 0x9A: return op0x9A(address, rom);
        case 0x9B: return op0x9B(address, rom);
        case 0x9C: return op0x9C(address, rom);
        case 0x9D: return op0x9D(address, rom);
        case 0x9E: return op0x9E(address, rom);
        case 0x9F: return op0x9F(address, rom);
        case 0xA0: return op0xA0(address, rom);
        case 0xA1: return op0xA1(address, rom);
        case 0xA2: return op0xA2(address, rom);
        case 0xA3: return op0xA3(address, rom);
        case 0xA4: return op0xA4(address, rom);
        case 0xA5: return op0xA5(address, rom);
        case 0xA6: return op0xA6(address, rom);
        case 0xA7: return op0xA7(address, rom);
        case 0xA8: return op0xA8(address, rom);
        case 0xA9: return op0xA9(address, rom);
        case 0xAA: return op0xAA(address, rom);
        case 0xAB: return op0xAB(address, rom);
        case 0xAC: return op0xAC(address, rom);
        case 0xAD: return op0xAD(address, rom);
        case 0xAE: return op0xAE(address, rom);
        case 0xAF: return op0xAF(address, rom);
        case 0xB0: return op0xB0(address, rom);
        case 0xB1: return op0xB1(address, rom);
        case 0xB2: return op0xB2(address, rom);
        case 0xB3: return op0xB3(address, rom);
        case 0xB4: return op0xB4(address, rom);
        case 0xB5: return op0xB5(address, rom);
        case 0xB6: return op0xB6(address, rom);
        case 0xB7: return op0xB7(address, rom);
        case 0xB8: return op0xB8(address, rom);
        case 0xB9: return op0xB9(address, rom);
        case 0xBA: return op0xBA(address, rom);
        case 0xBB: return op0xBB(address, rom);
        case 0xBC: return op0xBC(address, rom);
        case 0xBD: return op0xBD(address, rom);
        case 0xBE: return op0xBE(address, rom);
        case 0xBF: return op0xBF(address, rom);
        case 0xC0: return op0xC0(address, rom);
        case 0xC1: return op0xC1(address, rom);
        case 0xC2: return op0xC2(address, rom);
        case 0xC3: return op0xC3(address, rom);
        case 0xC4: return op0xC4(address, rom);
        case 0xC5: return op0xC5(address, rom);
        case 0xC6: return op0xC6(address, rom);
        case 0xC7: return op0xC7(address, rom);
        case 0xC8: return op0xC8(address, rom);
        case 0xC9: return op0xC9(address, rom);
        case 0xCA: return op0xCA(address, rom);
        case 0xCB: return op0xCB(address, rom);
        case 0xCC: return op0xCC(address, rom);
        case 0xCD: return op0xCD(address, rom);
        case 0xCE: return op0xCE(address, rom);
        case 0xCF: return op0xCF(address, rom);
        case 0xD0: return op0xD0(address, rom);
        case 0xD1: return op0xD1(address, rom);
        case 0xD2: return op0xD2(address, rom);
        case 0xD3: return op0xD3(address, rom);
        case 0xD4: return op0xD4(address, rom);
        case 0xD5: return op0xD5(address, rom);
        case 0xD6: return op0xD6(address, rom);
        case 0xD7: return op0xD7(address, rom);
        case 0xD8: return op0xD8(address, rom);
        case 0xD9: return op0xD9(address, rom);
        case 0xDA: return op0xDA(address, rom);
        case 0xDB: return op0xDB(address, rom);
        case 0xDC: return op0xDC(address, rom);
        case 0xDD: return op0xDD(address, rom);
        case 0xDE: return op0xDE(address, rom);
        case 0xDF: return op0xDF(address, rom);
        case 0xE0: return op0xE0(address, rom);
        case 0xE1: return op0xE1(address, rom);
        case 0xE2: return op0xE2(address, rom);
        case 0xE3: return op0xE3(address, rom);
        case 0xE4: return op0xE4(address, rom);
        case 0xE5: return op0xE5(address, rom);
        case 0xE6: return op0xE6(address, rom);
        case 0xE7: return op0xE7(address, rom);
        case 0xE8: return op0xE8(address, rom);
        case 0xE9: return op0xE9(address, rom);
        case 0xEA: return op0xEA(address, rom);
        case 0xEB: return op0xEB(address, rom);
        case 0xEC: return op0xEC(address, rom);
        case 0xED: return op0xED(address, rom);
        case 0xEE: return op0xEE(address, rom);
        case 0xEF: return op0xEF(address, rom);
        case 0xF0: return op0xF0(address, rom);
        case 0xF1: return op0xF1(address, rom);
        case 0xF2: return op0xF2(address, rom);
        case 0xF3: return op0xF3(address, rom);
        case 0xF4: return op0xF4(address, rom);
        case 0xF5: return op0xF5(address, rom);
        case 0xF6: return op0xF6(address, rom);
        case 0xF7: return op0xF7(address, rom);
        case 0xF8: return op0xF8(address, rom);
        case 0xF9: return op0xF9(address, rom);
        case 0xFA: return op0xFA(address, rom);
        case 0xFB: return op0xFB(address, rom);
        case 0xFC: return op0xFC(address, rom);
        case 0xFD: return op0xFD(address, rom);
        case 0xFE: return op0xFE(address, rom);
    }
    return -1;
}
