//
// Created by gyorgy on 11/08/18.
//

#include "Processor.h"
#include "ROM.h"
#include "../include/Processor.h"
#include "../include/RegisterBank.h"

#include <cstdio>

Processor::~Processor()
{
}

Processor::Processor()
{
}

inline int op0x00()
{
    printf("Op not implemented: 0x00\n");
    return -1;
}

inline int op0x01()
{
    printf("Op not implemented: 0x01\n");
    return -1;
}

inline int op0x02()
{
    printf("Op not implemented: 0x02\n");
    return -1;
}

inline int op0x03()
{
    printf("Op not implemented: 0x03\n");
    return -1;
}

inline int op0x04()
{
    printf("Op not implemented: 0x04\n");
    return -1;
}

inline int op0x05()
{
    printf("Op not implemented: 0x05\n");
    return -1;
}

inline int op0x06()
{
    printf("Op not implemented: 0x06\n");
    return -1;
}

inline int op0x07()
{
    printf("Op not implemented: 0x07\n");
    return -1;
}

inline int op0x08()
{
    printf("Op not implemented: 0x08\n");
    return -1;
}

inline int op0x09()
{
    printf("Op not implemented: 0x09\n");
    return -1;
}

inline int op0x0A()
{
    printf("Op not implemented: 0x0A\n");
    return -1;
}

inline int op0x0B()
{
    printf("Op not implemented: 0x0B\n");
    return -1;
}

inline int op0x0C()
{
    printf("Op not implemented: 0x0C\n");
    return -1;
}

inline int op0x0D()
{
    printf("Op not implemented: 0x0D\n");
    return -1;
}

inline int op0x0E()
{
    printf("Op not implemented: 0x0E\n");
    return -1;
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
    printf("Op not implemented: 0x11\n");
    return -1;
}

inline int op0x12()
{
    printf("Op not implemented: 0x12\n");
    return -1;
}

inline int op0x13()
{
    printf("Op not implemented: 0x13\n");
    return -1;
}

inline int op0x14()
{
    printf("Op not implemented: 0x14\n");
    return -1;
}

inline int op0x15()
{
    printf("Op not implemented: 0x15\n");
    return -1;
}

inline int op0x16()
{
    printf("Op not implemented: 0x16\n");
    return -1;
}

inline int op0x17()
{
    printf("Op not implemented: 0x17\n");
    return -1;
}

inline int op0x18()
{
    printf("Op not implemented: 0x18\n");
    return -1;
}

inline int op0x19()
{
    printf("Op not implemented: 0x19\n");
    return -1;
}

inline int op0x1A()
{
    printf("Op not implemented: 0x1A\n");
    return -1;
}

inline int op0x1B()
{
    printf("Op not implemented: 0x1B\n");
    return -1;
}

inline int op0x1C()
{
    printf("Op not implemented: 0x1C\n");
    return -1;
}

inline int op0x1D()
{
    printf("Op not implemented: 0x1D\n");
    return -1;
}

inline int op0x1E()
{
    printf("Op not implemented: 0x1E\n");
    return -1;
}

inline int op0x1F()
{
    printf("Op not implemented: 0x1F\n");
    return -1;
}

inline int op0x20()
{
    printf("Op not implemented: 0x20\n");
    return -1;
}

inline int op0x21()
{
    printf("Op not implemented: 0x21\n");
    return -1;
}

inline int op0x22()
{
    printf("Op not implemented: 0x22\n");
    return -1;
}

inline int op0x23()
{
    printf("Op not implemented: 0x23\n");
    return -1;
}

inline int op0x24()
{
    printf("Op not implemented: 0x24\n");
    return -1;
}

inline int op0x25()
{
    printf("Op not implemented: 0x25\n");
    return -1;
}

inline int op0x26()
{
    printf("Op not implemented: 0x26\n");
    return -1;
}

inline int op0x27()
{
    printf("Op not implemented: 0x27\n");
    return -1;
}

inline int op0x28()
{
    printf("Op not implemented: 0x28\n");
    return -1;
}

inline int op0x29()
{
    printf("Op not implemented: 0x29\n");
    return -1;
}

inline int op0x2A()
{
    printf("Op not implemented: 0x2A\n");
    return -1;
}

inline int op0x2B()
{
    printf("Op not implemented: 0x2B\n");
    return -1;
}

inline int op0x2C()
{
    printf("Op not implemented: 0x2C\n");
    return -1;
}

inline int op0x2D()
{
    printf("Op not implemented: 0x2D\n");
    return -1;
}

inline int op0x2E()
{
    printf("Op not implemented: 0x2E\n");
    return -1;
}

inline int op0x2F()
{
    printf("Op not implemented: 0x2F\n");
    return -1;
}

inline int op0x30()
{
    printf("Op not implemented: 0x30\n");
    return -1;
}

inline int op0x31()
{
    printf("Op not implemented: 0x31\n");
    return -1;
}

inline int op0x32()
{
    printf("Op not implemented: 0x32\n");
    return -1;
}

inline int op0x33()
{
    printf("Op not implemented: 0x33\n");
    return -1;
}

inline int op0x34()
{
    printf("Op not implemented: 0x34\n");
    return -1;
}

inline int op0x35()
{
    printf("Op not implemented: 0x35\n");
    return -1;
}

inline int op0x36()
{
    printf("Op not implemented: 0x36\n");
    return -1;
}

inline int op0x37()
{
    printf("Op not implemented: 0x37\n");
    return -1;
}

inline int op0x38()
{
    printf("Op not implemented: 0x38\n");
    return -1;
}

inline int op0x39()
{
    printf("Op not implemented: 0x39\n");
    return -1;
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
    printf("Op not implemented: 0x3C\n");
    return -1;
}

inline int op0x3D()
{
    printf("Op not implemented: 0x3D\n");
    return -1;
}

inline int op0x3E()
{
    printf("Op not implemented: 0x3E\n");
    return -1;
}

inline int op0x3F()
{
    printf("Op not implemented: 0x3F\n");
    return -1;
}

inline int op0x40()
{
    printf("Op not implemented: 0x40\n");
    return -1;
}

inline int op0x41()
{
    printf("Op not implemented: 0x41\n");
    return -1;
}

inline int op0x42()
{
    printf("Op not implemented: 0x42\n");
    return -1;
}

inline int op0x43()
{
    printf("Op not implemented: 0x43\n");
    return -1;
}

inline int op0x44()
{
    printf("Op not implemented: 0x44\n");
    return -1;
}

inline int op0x45()
{
    printf("Op not implemented: 0x45\n");
    return -1;
}

inline int op0x46()
{
    printf("Op not implemented: 0x46\n");
    return -1;
}

inline int op0x47()
{
    printf("Op not implemented: 0x47\n");
    return -1;
}

inline int op0x48()
{
    printf("Op not implemented: 0x48\n");
    return -1;
}

inline int op0x49()
{
    printf("Op not implemented: 0x49\n");
    return -1;
}

inline int op0x4A()
{
    printf("Op not implemented: 0x4A\n");
    return -1;
}

inline int op0x4B()
{
    printf("Op not implemented: 0x4B\n");
    return -1;
}

inline int op0x4C()
{
    printf("Op not implemented: 0x4C\n");
    return -1;
}

inline int op0x4D()
{
    printf("Op not implemented: 0x4D\n");
    return -1;
}

inline int op0x4E()
{
    printf("Op not implemented: 0x4E\n");
    return -1;
}

inline int op0x4F()
{
    printf("Op not implemented: 0x4F\n");
    return -1;
}

inline int op0x50()
{
    printf("Op not implemented: 0x50\n");
    return -1;
}

inline int op0x51()
{
    printf("Op not implemented: 0x51\n");
    return -1;
}

inline int op0x52()
{
    printf("Op not implemented: 0x52\n");
    return -1;
}

inline int op0x53()
{
    printf("Op not implemented: 0x53\n");
    return -1;
}

inline int op0x54()
{
    printf("Op not implemented: 0x54\n");
    return -1;
}

inline int op0x55()
{
    printf("Op not implemented: 0x55\n");
    return -1;
}

inline int op0x56()
{
    printf("Op not implemented: 0x56\n");
    return -1;
}

inline int op0x57()
{
    printf("Op not implemented: 0x57\n");
    return -1;
}

inline int op0x58()
{
    printf("Op not implemented: 0x58\n");
    return -1;
}

inline int op0x59()
{
    printf("Op not implemented: 0x59\n");
    return -1;
}

inline int op0x5A()
{
    printf("Op not implemented: 0x5A\n");
    return -1;
}

inline int op0x5B()
{
    printf("Op not implemented: 0x5B\n");
    return -1;
}

inline int op0x5C()
{
    printf("Op not implemented: 0x5C\n");
    return -1;
}

inline int op0x5D()
{
    printf("Op not implemented: 0x5D\n");
    return -1;
}

inline int op0x5E()
{
    printf("Op not implemented: 0x5E\n");
    return -1;
}

inline int op0x5F()
{
    printf("Op not implemented: 0x5F\n");
    return -1;
}

inline int op0x60()
{
    printf("Op not implemented: 0x60\n");
    return -1;
}

inline int op0x61()
{
    printf("Op not implemented: 0x61\n");
    return -1;
}

inline int op0x62()
{
    printf("Op not implemented: 0x62\n");
    return -1;
}

inline int op0x63()
{
    printf("Op not implemented: 0x63\n");
    return -1;
}

inline int op0x64()
{
    printf("Op not implemented: 0x64\n");
    return -1;
}

inline int op0x65()
{
    printf("Op not implemented: 0x65\n");
    return -1;
}

inline int op0x66()
{
    printf("Op not implemented: 0x66\n");
    return -1;
}

inline int op0x67()
{
    printf("Op not implemented: 0x67\n");
    return -1;
}

inline int op0x68()
{
    printf("Op not implemented: 0x68\n");
    return -1;
}

inline int op0x69()
{
    printf("Op not implemented: 0x69\n");
    return -1;
}

inline int op0x6A()
{
    printf("Op not implemented: 0x6A\n");
    return -1;
}

inline int op0x6B()
{
    printf("Op not implemented: 0x6B\n");
    return -1;
}

inline int op0x6C()
{
    printf("Op not implemented: 0x6C\n");
    return -1;
}

inline int op0x6D()
{
    printf("Op not implemented: 0x6D\n");
    return -1;
}

inline int op0x6E()
{
    printf("Op not implemented: 0x6E\n");
    return -1;
}

inline int op0x6F()
{
    printf("Op not implemented: 0x6F\n");
    return -1;
}

inline int op0x70()
{
    printf("Op not implemented: 0x70\n");
    return -1;
}

inline int op0x71()
{
    printf("Op not implemented: 0x71\n");
    return -1;
}

inline int op0x72()
{
    printf("Op not implemented: 0x72\n");
    return -1;
}

inline int op0x73()
{
    printf("Op not implemented: 0x73\n");
    return -1;
}

inline int op0x74()
{
    printf("Op not implemented: 0x74\n");
    return -1;
}

inline int op0x75()
{
    printf("Op not implemented: 0x75\n");
    return -1;
}

inline int op0x76()
{
    printf("Op not implemented: 0x76\n");
    return -1;
}

inline int op0x77()
{
    printf("Op not implemented: 0x77\n");
    return -1;
}

inline int op0x78()
{
    printf("Op not implemented: 0x78\n");
    return -1;
}

inline int op0x79()
{
    printf("Op not implemented: 0x79\n");
    return -1;
}

inline int op0x7A()
{
    printf("Op not implemented: 0x7A\n");
    return -1;
}

inline int op0x7B()
{
    printf("Op not implemented: 0x7B\n");
    return -1;
}

inline int op0x7C()
{
    printf("Op not implemented: 0x7C\n");
    return -1;
}

inline int op0x7D()
{
    printf("Op not implemented: 0x7D\n");
    return -1;
}

inline int op0x7E()
{
    printf("Op not implemented: 0x7E\n");
    return -1;
}

inline int op0x7F()
{
    printf("Op not implemented: 0x7F\n");
    return -1;
}

inline int op0x80()
{
    printf("Op not implemented: 0x80\n");
    return -1;
}

inline int op0x81()
{
    printf("Op not implemented: 0x81\n");
    return -1;
}

inline int op0x82()
{
    printf("Op not implemented: 0x82\n");
    return -1;
}

inline int op0x83()
{
    printf("Op not implemented: 0x83\n");
    return -1;
}

inline int op0x84()
{
    printf("Op not implemented: 0x84\n");
    return -1;
}

inline int op0x85()
{
    printf("Op not implemented: 0x85\n");
    return -1;
}

inline int op0x86()
{
    printf("Op not implemented: 0x86\n");
    return -1;
}

inline int op0x87()
{
    printf("Op not implemented: 0x87\n");
    return -1;
}

inline int op0x88()
{
    printf("Op not implemented: 0x88\n");
    return -1;
}

inline int op0x89()
{
    printf("Op not implemented: 0x89\n");
    return -1;
}

inline int op0x8A()
{
    printf("Op not implemented: 0x8A\n");
    return -1;
}

inline int op0x8B()
{
    printf("Op not implemented: 0x8B\n");
    return -1;
}

inline int op0x8C()
{
    printf("Op not implemented: 0x8C\n");
    return -1;
}

inline int op0x8D()
{
    printf("Op not implemented: 0x8D\n");
    return -1;
}

inline int op0x8E()
{
    printf("Op not implemented: 0x8E\n");
    return -1;
}

inline int op0x8F()
{
    printf("Op not implemented: 0x8F\n");
    return -1;
}

inline int op0x90()
{
    printf("Op not implemented: 0x90\n");
    return -1;
}

inline int op0x91()
{
    printf("Op not implemented: 0x91\n");
    return -1;
}

inline int op0x92()
{
    printf("Op not implemented: 0x92\n");
    return -1;
}

inline int op0x93()
{
    printf("Op not implemented: 0x93\n");
    return -1;
}

inline int op0x94()
{
    printf("Op not implemented: 0x94\n");
    return -1;
}

inline int op0x95()
{
    printf("Op not implemented: 0x95\n");
    return -1;
}

inline int op0x96()
{
    printf("Op not implemented: 0x96\n");
    return -1;
}

inline int op0x97()
{
    printf("Op not implemented: 0x97\n");
    return -1;
}

inline int op0x98()
{
    printf("Op not implemented: 0x98\n");
    return -1;
}

inline int op0x99()
{
    printf("Op not implemented: 0x99\n");
    return -1;
}

inline int op0x9A()
{
    printf("Op not implemented: 0x9A\n");
    return -1;
}

inline int op0x9B()
{
    printf("Op not implemented: 0x9B\n");
    return -1;
}

inline int op0x9C()
{
    printf("Op not implemented: 0x9C\n");
    return -1;
}

inline int op0x9D()
{
    printf("Op not implemented: 0x9D\n");
    return -1;
}

inline int op0x9E()
{
    printf("Op not implemented: 0x9E\n");
    return -1;
}

inline int op0x9F()
{
    printf("Op not implemented: 0x9F\n");
    return -1;
}

inline int op0xA0()
{
    printf("Op not implemented: 0xA0\n");
    return -1;
}

inline int op0xA1()
{
    printf("Op not implemented: 0xA1\n");
    return -1;
}

inline int op0xA2()
{
    printf("Op not implemented: 0xA2\n");
    return -1;
}

inline int op0xA3()
{
    printf("Op not implemented: 0xA3\n");
    return -1;
}

inline int op0xA4()
{
    printf("Op not implemented: 0xA4\n");
    return -1;
}

inline int op0xA5()
{
    printf("Op not implemented: 0xA5\n");
    return -1;
}

inline int op0xA6()
{
    printf("Op not implemented: 0xA6\n");
    return -1;
}

inline int op0xA7()
{
    printf("Op not implemented: 0xA7\n");
    return -1;
}

inline int op0xA8()
{
    printf("Op not implemented: 0xA8\n");
    return -1;
}

inline int op0xA9()
{
    printf("Op not implemented: 0xA9\n");
    return -1;
}

inline int op0xAA()
{
    printf("Op not implemented: 0xAA\n");
    return -1;
}

inline int op0xAB()
{
    printf("Op not implemented: 0xAB\n");
    return -1;
}

inline int op0xAC()
{
    printf("Op not implemented: 0xAC\n");
    return -1;
}

inline int op0xAD()
{
    printf("Op not implemented: 0xAD\n");
    return -1;
}

inline int op0xAE()
{
    printf("Op not implemented: 0xAE\n");
    return -1;
}

inline int op0xAF()
{
    printf("Op not implemented: 0xAF\n");
    return -1;
}

inline int op0xB0()
{
    printf("Op not implemented: 0xB0\n");
    return -1;
}

inline int op0xB1()
{
    printf("Op not implemented: 0xB1\n");
    return -1;
}

inline int op0xB2()
{
    printf("Op not implemented: 0xB2\n");
    return -1;
}

inline int op0xB3()
{
    printf("Op not implemented: 0xB3\n");
    return -1;
}

inline int op0xB4()
{
    printf("Op not implemented: 0xB4\n");
    return -1;
}

inline int op0xB5()
{
    printf("Op not implemented: 0xB5\n");
    return -1;
}

inline int op0xB6()
{
    printf("Op not implemented: 0xB6\n");
    return -1;
}

inline int op0xB7()
{
    printf("Op not implemented: 0xB7\n");
    return -1;
}

inline int op0xB8()
{
    printf("Op not implemented: 0xB8\n");
    return -1;
}

inline int op0xB9()
{
    printf("Op not implemented: 0xB9\n");
    return -1;
}

inline int op0xBA()
{
    printf("Op not implemented: 0xBA\n");
    return -1;
}

inline int op0xBB()
{
    printf("Op not implemented: 0xBB\n");
    return -1;
}

inline int op0xBC()
{
    printf("Op not implemented: 0xBC\n");
    return -1;
}

inline int op0xBD()
{
    printf("Op not implemented: 0xBD\n");
    return -1;
}

inline int op0xBE()
{
    printf("Op not implemented: 0xBE\n");
    return -1;
}

inline int op0xBF()
{
    printf("Op not implemented: 0xBF\n");
    return -1;
}

inline int op0xC0()
{
    printf("Op not implemented: 0xC0\n");
    return -1;
}

inline int op0xC1()
{
    printf("Op not implemented: 0xC1\n");
    return -1;
}

inline int op0xC2()
{
    printf("Op not implemented: 0xC2\n");
    return -1;
}

inline int op0xC3()
{
    printf("Op not implemented: 0xC3\n");
    return -1;
}

inline int op0xC4()
{
    printf("Op not implemented: 0xC4\n");
    return -1;
}

inline int op0xC5()
{
    printf("Op not implemented: 0xC5\n");
    return -1;
}

inline int op0xC6()
{
    printf("Op not implemented: 0xC6\n");
    return -1;
}

inline int op0xC7()
{
    printf("Op not implemented: 0xC7\n");
    return -1;
}

inline int op0xC8()
{
    printf("Op not implemented: 0xC8\n");
    return -1;
}

inline int op0xC9()
{
    printf("Op not implemented: 0xC9\n");
    return -1;
}

inline int op0xCA()
{
    printf("Op not implemented: 0xCA\n");
    return -1;
}

inline int op0xCB()
{
    printf("Op not implemented: 0xCB\n");
    return -1;
}

inline int op0xCC()
{
    printf("Op not implemented: 0xCC\n");
    return -1;
}

inline int op0xCD()
{
    printf("Op not implemented: 0xCD\n");
    return -1;
}

inline int op0xCE()
{
    printf("Op not implemented: 0xCE\n");
    return -1;
}

inline int op0xCF()
{
    printf("Op not implemented: 0xCF\n");
    return -1;
}

inline int op0xD0()
{
    printf("Op not implemented: 0xD0\n");
    return -1;
}

inline int op0xD1()
{
    printf("Op not implemented: 0xD1\n");
    return -1;
}

inline int op0xD2()
{
    printf("Op not implemented: 0xD2\n");
    return -1;
}

inline int op0xD3()
{
    printf("Op not implemented: 0xD3\n");
    return -1;
}

inline int op0xD4()
{
    printf("Op not implemented: 0xD4\n");
    return -1;
}

inline int op0xD5()
{
    printf("Op not implemented: 0xD5\n");
    return -1;
}

inline int op0xD6()
{
    printf("Op not implemented: 0xD6\n");
    return -1;
}

inline int op0xD7()
{
    printf("Op not implemented: 0xD7\n");
    return -1;
}

inline int op0xD8()
{
    printf("Op not implemented: 0xD8\n");
    return -1;
}

inline int op0xD9()
{
    printf("Op not implemented: 0xD9\n");
    return -1;
}

inline int op0xDA()
{
    printf("Op not implemented: 0xDA\n");
    return -1;
}

inline int op0xDB()
{
    printf("Op not implemented: 0xDB\n");
    return -1;
}

inline int op0xDC()
{
    printf("Op not implemented: 0xDC\n");
    return -1;
}

inline int op0xDD()
{
    printf("Op not implemented: 0xDD\n");
    return -1;
}

inline int op0xDE()
{
    printf("Op not implemented: 0xDE\n");
    return -1;
}

inline int op0xDF()
{
    printf("Op not implemented: 0xDF\n");
    return -1;
}

inline int op0xE0()
{
    printf("Op not implemented: 0xE0\n");
    return -1;
}

inline int op0xE1()
{
    printf("Op not implemented: 0xE1\n");
    return -1;
}

inline int op0xE2()
{
    printf("Op not implemented: 0xE2\n");
    return -1;
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
    printf("Op not implemented: 0xE5\n");
    return -1;
}

inline int op0xE6()
{
    printf("Op not implemented: 0xE6\n");
    return -1;
}

inline int op0xE7()
{
    printf("Op not implemented: 0xE7\n");
    return -1;
}

inline int op0xE8()
{
    printf("Op not implemented: 0xE8\n");
    return -1;
}

inline int op0xE9()
{
    printf("Op not implemented: 0xE9\n");
    return -1;
}

inline int op0xEA()
{
    printf("Op not implemented: 0xEA\n");
    return -1;
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
    printf("Op not implemented: 0xEE\n");
    return -1;
}

inline int op0xEF()
{
    printf("Op not implemented: 0xEF\n");
    return -1;
}

inline int op0xF0()
{
    printf("Op not implemented: 0xF0\n");
    return -1;
}

inline int op0xF1()
{
    printf("Op not implemented: 0xF1\n");
    return -1;
}

inline int op0xF2()
{
    printf("Op not implemented: 0xF2\n");
    return -1;
}

inline int op0xF3()
{
    printf("Op not implemented: 0xF3\n");
    return -1;
}

inline int op0xF4()
{
    printf("Op not implemented: 0xF4\n");
    return -1;
}

inline int op0xF5()
{
    printf("Op not implemented: 0xF5\n");
    return -1;
}

inline int op0xF6()
{
    printf("Op not implemented: 0xF6\n");
    return -1;
}

inline int op0xF7()
{
    printf("Op not implemented: 0xF7\n");
    return -1;
}

inline int op0xF8()
{
    printf("Op not implemented: 0xF8\n");
    return -1;
}

inline int op0xF9()
{
    printf("Op not implemented: 0xF9\n");
    return -1;
}

inline int op0xFA()
{
    printf("Op not implemented: 0xFA\n");
    return -1;
}

inline int op0xFB()
{
    printf("Op not implemented: 0xFB\n");
    return -1;
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
    printf("Op not implemented: 0xFE\n");
    return -1;
}

int Processor::DecodeInstr(uint16_t address)
{
    uint8_t op_code = ROM::GetByteAt(address);
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
    }
    return -1;
}

void Processor::StartCPULoop()
{
    int status = 1;
    while (status > 0) {
        status = DecodeInstr(RegisterBank::PC);
    }
}
