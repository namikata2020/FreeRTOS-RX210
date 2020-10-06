/************************************************************************
*
* Device     : RX/RX200/RX210
*
* File Name  : vecttbl.c
*
* Abstract   : Initialize of Vector Table and MDE register.
*
* History    : 0.10 (2010-12-17) [Hardware Manual Revision : 0.10]
*            : 0.20 (2011-02-21) [Hardware Manual Revision : 0.12]
*            : 0.21 (2011-06-20) [Hardware Manual Revision : 0.50]
*            : 1.00 (2012-12-19) [Hardware Manual Revision : 1.30]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2012 (2010 - 2011) Renesas Electronics Corporation. and
* Renesas Solutions Corp. All rights reserved.
*
************************************************************************/

#include "vect.h"

typedef void (*fp) (void);

#pragma section C FIXEDVECT

void (*const Fixed_Vectors[])(void) = {
//;0xffffff80  
#ifdef __BIG
    (fp)0xFFFFFFF8, // big
#else
    (fp)0xFFFFFFFF, // little
#endif
//;0xffffff84  Reserved
    Dummy,    
//;0xffffff88  OFS1
    (fp)0xFFFFFFFF,
//;0xffffff8C  OFS0
    (fp)0xFFFFFFFF,
//;0xffffff90  Reserved
    Dummy,    
//;0xffffff94  Reserved
    Dummy,    
//;0xffffff98  Reserved
    Dummy,   
//;0xffffff9C  Reserved
    Dummy,    
//;0xffffffA0  Reserved
// ID codes (Default)
   (fp)0xFFFFFFFF,
 //;0xffffffA4  Reserved
   (fp)0xFFFFFFFF,
//;0xffffffA8  Reserved
   (fp)0xFFFFFFFF,
//;0xffffffAC  Reserved
   (fp)0xFFFFFFFF,
//;0xffffffB0  Reserved
    Dummy,
//;0xffffffB4  Reserved
    Dummy,
//;0xffffffB8  Reserved
    Dummy,
//;0xffffffBC  Reserved
    Dummy,
//;0xffffffC0  Reserved
    Dummy,
//;0xffffffC4  Reserved
    Dummy,
//;0xffffffC8  Reserved
    Dummy,
//;0xffffffCC  Reserved
    Dummy,
//;0xffffffd0  Exception(Supervisor Instruction)
    Excep_SuperVisorInst,
//;0xffffffd4  Reserved
    Dummy,
//;0xffffffd8  Reserved
    Dummy,
//;0xffffffdc  Exception(Undefined Instruction)
    Excep_UndefinedInst,
//;0xffffffe0  Reserved
    Dummy,
//;0xffffffe4  Reserved
    Dummy,
//;0xffffffe8  Reserved
    Dummy,
//;0xffffffec  Reserved
    Dummy,
//;0xfffffff0  Reserved
    Dummy,
//;0xfffffff4  Reserved
    Dummy,
//;0xfffffff8  NMI
    NonMaskableInterrupt,
//;0xfffffffc  RESET
//;<<VECTOR DATA START (POWER ON RESET)>>
//;Power On Reset PC
    /*(void*)*/ PowerON_Reset_PC                                                                                                                 
//;<<VECTOR DATA END (POWER ON RESET)>>
};

