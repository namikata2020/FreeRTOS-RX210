/************************************************************************
*
* Device     : RX/RX200/RX210
*
* File Name  : vect.h
*
* Abstract   : Definition of Vector.
*
* History    : 0.10  (2010-10-06)  [Hardware Manual Revision : 0.11]
*            : 0.11  (2011-06-20)  [Hardware Manual Revision : 0.50]
*            : 1.00  (2012-06-18)  [Hardware Manual Revision : 1.00]
*            : 1.10  (2012-06-18)  [Hardware Manual Revision : 1.00]
*            : 1.20  (2012-12-19)  [Hardware Manual Revision : 1.30]
*            : 1.30  (2013-04-01)  [Hardware Manual Revision : 1.40]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2013(2010 - 2012) Renesas Electronics Corporation and
* Renesas Solutions Corp. All rights reserved.
*
********************************************************************+++*/

// Exception(Supervisor Instruction)
#pragma interrupt (Excep_SuperVisorInst)
void Excep_SuperVisorInst(void);

// Exception(Undefined Instruction)
#pragma interrupt (Excep_UndefinedInst)
void Excep_UndefinedInst(void);

// NMI
#pragma interrupt (NonMaskableInterrupt)
void NonMaskableInterrupt(void);

// Dummy
#pragma interrupt (Dummy)
void Dummy(void);

// BRK
#pragma interrupt (Excep_BRK(vect=0))
void Excep_BRK(void);

// BSC BUSERR
#pragma interrupt (Excep_BSC_BUSERR(vect=16))
void Excep_BSC_BUSERR(void);

// FCU FIFERR
#pragma interrupt (Excep_FCU_FIFERR(vect=21))
void Excep_FCU_FIFERR(void);

// FCU FRDYI
#pragma interrupt (Excep_FCU_FRDYI(vect=23))
void Excep_FCU_FRDYI(void);

// ICU SWINT
//#pragma interrupt (Excep_ICU_SWINT(vect=27))
//void Excep_ICU_SWINT(void);

// CMT0 CMI0
//#pragma interrupt (Excep_CMT0_CMI0(vect=28))
//void Excep_CMT0_CMI0(void);

// CMT1 CMI1
#pragma interrupt (Excep_CMT1_CMI1(vect=29))
void Excep_CMT1_CMI1(void);

// CMT2 CMI2
#pragma interrupt (Excep_CMT2_CMI2(vect=30))
void Excep_CMT2_CMI2(void);

// CMT3 CMI3
#pragma interrupt (Excep_CMT3_CMI3(vect=31))
void Excep_CMT3_CMI3(void);

// CAC FERRF
#pragma interrupt (Excep_CAC_FERRF(vect=32))
void Excep_CAC_FERRF(void);

// CAC MENDF
#pragma interrupt (Excep_CAC_MENDF(vect=33))
void Excep_CAC_MENDF(void);

// CAC OVFF
#pragma interrupt (Excep_CAC_OVFF(vect=34))
void Excep_CAC_OVFF(void);

// RSPI0 SPEI0
#pragma interrupt (Excep_RSPI0_SPEI0(vect=44))
void Excep_RSPI0_SPEI0(void);

// RSPI0 SPRI0
#pragma interrupt (Excep_RSPI0_SPRI0(vect=45))
void Excep_RSPI0_SPRI0(void);

// RSPI0 SPTI0
#pragma interrupt (Excep_RSPI0_SPTI0(vect=46))
void Excep_RSPI0_SPTI0(void);

// RSPI0 SPII0
#pragma interrupt (Excep_RSPI0_SPII0(vect=47))
void Excep_RSPI0_SPII0(void);

// DOC DOPCF
#pragma interrupt (Excep_DOC_DOPCF(vect=57))
void Excep_DOC_DOPCF(void);

// CMPB CMPB0
#pragma interrupt (Excep_CMPB_CMPB0(vect=58))
void Excep_CMPB_CMPB0(void);

// CMPB CMPB1
#pragma interrupt (Excep_CMPB_CMPB1(vect=59))
void Excep_CMPB_CMPB1(void);

// RTC CUP
#pragma interrupt (Excep_RTC_CUP(vect=63))
void Excep_RTC_CUP(void);

// ICU IRQ0
#pragma interrupt (Excep_ICU_IRQ0(vect=64))
void Excep_ICU_IRQ0(void);

// ICU IRQ1
#pragma interrupt (Excep_ICU_IRQ1(vect=65))
void Excep_ICU_IRQ1(void);

// ICU IRQ2
#pragma interrupt (Excep_ICU_IRQ2(vect=66))
void Excep_ICU_IRQ2(void);

// ICU IRQ3
#pragma interrupt (Excep_ICU_IRQ3(vect=67))
void Excep_ICU_IRQ3(void);

// ICU IRQ4
#pragma interrupt (Excep_ICU_IRQ4(vect=68))
void Excep_ICU_IRQ4(void);

// ICU IRQ5
#pragma interrupt (Excep_ICU_IRQ5(vect=69))
void Excep_ICU_IRQ5(void);

// ICU IRQ6
#pragma interrupt (Excep_ICU_IRQ6(vect=70))
void Excep_ICU_IRQ6(void);

// ICU IRQ7
#pragma interrupt (Excep_ICU_IRQ7(vect=71))
void Excep_ICU_IRQ7(void);

// LVD LVD1
#pragma interrupt (Excep_LVD_LVD1(vect=88))
void Excep_LVD_LVD1(void);

// CMPA CMPA1
//#pragma interrupt (Excep_CMPA_CMPA1(vect=88))
//void Excep_CMPA_CMPA1(void);

// LVD LVD2
#pragma interrupt (Excep_LVD_LVD2(vect=89))
void Excep_LVD_LVD2(void);

// CMPA CMPA2
//#pragma interrupt (Excep_CMPA_CMPA2(vect=89))
//void Excep_CMPA_CMPA2(void);

// RTC ALM
#pragma interrupt (Excep_RTC_ALM(vect=92))
void Excep_RTC_ALM(void);

// RTC PRD
#pragma interrupt (Excep_RTC_PRD(vect=93))
void Excep_RTC_PRD(void);

// S12AD S12ADI0
#pragma interrupt (Excep_S12AD_S12ADI0(vect=102))
void Excep_S12AD_S12ADI0(void);

// S12AD GBADI
#pragma interrupt (Excep_S12AD_GBADI(vect=103))
void Excep_S12AD_GBADI(void);

// ELC ELSR18I
#pragma interrupt (Excep_ELC_ELSR18I(vect=106))
void Excep_ELC_ELSR18I(void);

// ELC ELSR19I
#pragma interrupt (Excep_ELC_ELSR19I(vect=107))
void Excep_ELC_ELSR19I(void);

// MTU0 TGIA0
#pragma interrupt (Excep_MTU0_TGIA0(vect=114))
void Excep_MTU0_TGIA0(void);

// MTU0 TGIB0
#pragma interrupt (Excep_MTU0_TGIB0(vect=115))
void Excep_MTU0_TGIB0(void);

// MTU0 TGIC0
#pragma interrupt (Excep_MTU0_TGIC0(vect=116))
void Excep_MTU0_TGIC0(void);

// MTU0 TGID0
#pragma interrupt (Excep_MTU0_TGID0(vect=117))
void Excep_MTU0_TGID0(void);

// MTU0 TCIV0
#pragma interrupt (Excep_MTU0_TCIV0(vect=118))
void Excep_MTU0_TCIV0(void);

// MTU0 TGIE0
#pragma interrupt (Excep_MTU0_TGIE0(vect=119))
void Excep_MTU0_TGIE0(void);

// MTU0 TGIF0
#pragma interrupt (Excep_MTU0_TGIF0(vect=120))
void Excep_MTU0_TGIF0(void);

// MTU1 TGIA1
#pragma interrupt (Excep_MTU1_TGIA1(vect=121))
void Excep_MTU1_TGIA1(void);

// MTU1 TGIB1
#pragma interrupt (Excep_MTU1_TGIB1(vect=122))
void Excep_MTU1_TGIB1(void);

// MTU1 TCIV1
#pragma interrupt (Excep_MTU1_TCIV1(vect=123))
void Excep_MTU1_TCIV1(void);

// MTU1 TCIU1
#pragma interrupt (Excep_MTU1_TCIU1(vect=124))
void Excep_MTU1_TCIU1(void);

// MTU2 TGIA2
#pragma interrupt (Excep_MTU2_TGIA2(vect=125))
void Excep_MTU2_TGIA2(void);

// MTU2 TGIB2
#pragma interrupt (Excep_MTU2_TGIB2(vect=126))
void Excep_MTU2_TGIB2(void);

// MTU2 TCIV2
#pragma interrupt (Excep_MTU2_TCIV2(vect=127))
void Excep_MTU2_TCIV2(void);

// MTU2 TCIU2
#pragma interrupt (Excep_MTU2_TCIU2(vect=128))
void Excep_MTU2_TCIU2(void);

// MTU3 TGIA3
#pragma interrupt (Excep_MTU3_TGIA3(vect=129))
void Excep_MTU3_TGIA3(void);

// MTU3 TGIB3
#pragma interrupt (Excep_MTU3_TGIB3(vect=130))
void Excep_MTU3_TGIB3(void);

// MTU3 TGIC3
#pragma interrupt (Excep_MTU3_TGIC3(vect=131))
void Excep_MTU3_TGIC3(void);

// MTU3 TGID3
#pragma interrupt (Excep_MTU3_TGID3(vect=132))
void Excep_MTU3_TGID3(void);

// MTU3 TCIV3
#pragma interrupt (Excep_MTU3_TCIV3(vect=133))
void Excep_MTU3_TCIV3(void);

// MTU4 TGIA4
#pragma interrupt (Excep_MTU4_TGIA4(vect=134))
void Excep_MTU4_TGIA4(void);

// MTU4 TGIB4
#pragma interrupt (Excep_MTU4_TGIB4(vect=135))
void Excep_MTU4_TGIB4(void);

// MTU4 TGIC4
#pragma interrupt (Excep_MTU4_TGIC4(vect=136))
void Excep_MTU4_TGIC4(void);

// MTU4 TGID4
#pragma interrupt (Excep_MTU4_TGID4(vect=137))
void Excep_MTU4_TGID4(void);

// MTU4 TCIV4
#pragma interrupt (Excep_MTU4_TCIV4(vect=138))
void Excep_MTU4_TCIV4(void);

// MTU5 TGIU5
#pragma interrupt (Excep_MTU5_TGIU5(vect=139))
void Excep_MTU5_TGIU5(void);

// MTU5 TGIV5
#pragma interrupt (Excep_MTU5_TGIV5(vect=140))
void Excep_MTU5_TGIV5(void);

// MTU5 TGIW5
#pragma interrupt (Excep_MTU5_TGIW5(vect=141))
void Excep_MTU5_TGIW5(void);

// TPU0 TGI0A
#pragma interrupt (Excep_TPU0_TGI0A(vect=142))
void Excep_TPU0_TGI0A(void);

// TPU0 TGI0B
#pragma interrupt (Excep_TPU0_TGI0B(vect=143))
void Excep_TPU0_TGI0B(void);

// TPU0 TGI0C
#pragma interrupt (Excep_TPU0_TGI0C(vect=144))
void Excep_TPU0_TGI0C(void);

// TPU0 TGI0D
#pragma interrupt (Excep_TPU0_TGI0D(vect=145))
void Excep_TPU0_TGI0D(void);

// TPU0 TCI0V
#pragma interrupt (Excep_TPU0_TCI0V(vect=146))
void Excep_TPU0_TCI0V(void);

// TPU1 TGI1A
#pragma interrupt (Excep_TPU1_TGI1A(vect=147))
void Excep_TPU1_TGI1A(void);

// TPU1 TGI1B
#pragma interrupt (Excep_TPU1_TGI1B(vect=148))
void Excep_TPU1_TGI1B(void);

// TPU1 TCI1V
#pragma interrupt (Excep_TPU1_TCI1V(vect=149))
void Excep_TPU1_TCI1V(void);

// TPU1 TCI1U
#pragma interrupt (Excep_TPU1_TCI1U(vect=150))
void Excep_TPU1_TCI1U(void);

// TPU2 TGI2A
#pragma interrupt (Excep_TPU2_TGI2A(vect=151))
void Excep_TPU2_TGI2A(void);

// TPU2 TGI2B
#pragma interrupt (Excep_TPU2_TGI2B(vect=152))
void Excep_TPU2_TGI2B(void);

// TPU2 TCI2V
#pragma interrupt (Excep_TPU2_TCI2V(vect=153))
void Excep_TPU2_TCI2V(void);

// TPU2 TCI2U
#pragma interrupt (Excep_TPU2_TCI2U(vect=154))
void Excep_TPU2_TCI2U(void);

// TPU3 TGI3A
#pragma interrupt (Excep_TPU3_TGI3A(vect=155))
void Excep_TPU3_TGI3A(void);

// TPU3 TGI3B
#pragma interrupt (Excep_TPU3_TGI3B(vect=156))
void Excep_TPU3_TGI3B(void);

// TPU3 TGI3C
#pragma interrupt (Excep_TPU3_TGI3C(vect=157))
void Excep_TPU3_TGI3C(void);

// TPU3 TGI3D
#pragma interrupt (Excep_TPU3_TGI3D(vect=158))
void Excep_TPU3_TGI3D(void);

// TPU3 TCI3V
#pragma interrupt (Excep_TPU3_TCI3V(vect=159))
void Excep_TPU3_TCI3V(void);

// TPU4 TGI4A
#pragma interrupt (Excep_TPU4_TGI4A(vect=160))
void Excep_TPU4_TGI4A(void);

// TPU4 TGI4B
#pragma interrupt (Excep_TPU4_TGI4B(vect=161))
void Excep_TPU4_TGI4B(void);

// TPU4 TCI4V
#pragma interrupt (Excep_TPU4_TCI4V(vect=162))
void Excep_TPU4_TCI4V(void);

// TPU4 TCI4U
#pragma interrupt (Excep_TPU4_TCI4U(vect=163))
void Excep_TPU4_TCI4U(void);

// TPU5 TGI5A
#pragma interrupt (Excep_TPU5_TGI5A(vect=164))
void Excep_TPU5_TGI5A(void);

// TPU5 TGI5B
#pragma interrupt (Excep_TPU5_TGI5B(vect=165))
void Excep_TPU5_TGI5B(void);

// TPU5 TCI5V
#pragma interrupt (Excep_TPU5_TCI5V(vect=166))
void Excep_TPU5_TCI5V(void);

// TPU5 TCI5U
#pragma interrupt (Excep_TPU5_TCI5U(vect=167))
void Excep_TPU5_TCI5U(void);

// POE OEI1
#pragma interrupt (Excep_POE_OEI1(vect=170))
void Excep_POE_OEI1(void);

// POE OEI2
#pragma interrupt (Excep_POE_OEI2(vect=171))
void Excep_POE_OEI2(void);

// TMR0 CMIA0
#pragma interrupt (Excep_TMR0_CMIA0(vect=174))
void Excep_TMR0_CMIA0(void);

// TMR0 CMIB0
#pragma interrupt (Excep_TMR0_CMIB0(vect=175))
void Excep_TMR0_CMIB0(void);

// TMR0 OVI0
#pragma interrupt (Excep_TMR0_OVI0(vect=176))
void Excep_TMR0_OVI0(void);

// TMR1 CMIA1
#pragma interrupt (Excep_TMR1_CMIA1(vect=177))
void Excep_TMR1_CMIA1(void);

// TMR1 CMIB1
#pragma interrupt (Excep_TMR1_CMIB1(vect=178))
void Excep_TMR1_CMIB1(void);

// TMR1 OVI1
#pragma interrupt (Excep_TMR1_OVI1(vect=179))
void Excep_TMR1_OVI1(void);

// TMR2 CMIA2
#pragma interrupt (Excep_TMR2_CMIA2(vect=180))
void Excep_TMR2_CMIA2(void);

// TMR2 CMIB2
#pragma interrupt (Excep_TMR2_CMIB2(vect=181))
void Excep_TMR2_CMIB2(void);

// TMR2 OVI2
#pragma interrupt (Excep_TMR2_OVI2(vect=182))
void Excep_TMR2_OVI2(void);

// TMR3 CMIA3
#pragma interrupt (Excep_TMR3_CMIA3(vect=183))
void Excep_TMR3_CMIA3(void);

// TMR3 CMIB3
#pragma interrupt (Excep_TMR3_CMIB3(vect=184))
void Excep_TMR3_CMIB3(void);

// TMR3 OVI3
#pragma interrupt (Excep_TMR3_OVI3(vect=185))
void Excep_TMR3_OVI3(void);

// SCI2 ERI2
#pragma interrupt (Excep_SCI2_ERI2(vect=186))
void Excep_SCI2_ERI2(void);

// SCI2 RXI2
#pragma interrupt (Excep_SCI2_RXI2(vect=187))
void Excep_SCI2_RXI2(void);

// SCI2 TXI2
#pragma interrupt (Excep_SCI2_TXI2(vect=188))
void Excep_SCI2_TXI2(void);

// SCI2 TEI2
#pragma interrupt (Excep_SCI2_TEI2(vect=189))
void Excep_SCI2_TEI2(void);

// SCI3 ERI3
#pragma interrupt (Excep_SCI3_ERI3(vect=190))
void Excep_SCI3_ERI3(void);

// SCI3 RXI3
#pragma interrupt (Excep_SCI3_RXI3(vect=191))
void Excep_SCI3_RXI3(void);

// SCI3 TXI3
#pragma interrupt (Excep_SCI3_TXI3(vect=192))
void Excep_SCI3_TXI3(void);

// SCI3 TEI3
#pragma interrupt (Excep_SCI3_TEI3(vect=193))
void Excep_SCI3_TEI3(void);

// SCI4 ERI4
#pragma interrupt (Excep_SCI4_ERI4(vect=194))
void Excep_SCI4_ERI4(void);

// SCI4 RXI4
#pragma interrupt (Excep_SCI4_RXI4(vect=195))
void Excep_SCI4_RXI4(void);

// SCI4 TXI4
#pragma interrupt (Excep_SCI4_TXI4(vect=196))
void Excep_SCI4_TXI4(void);

// SCI4 TEI4
#pragma interrupt (Excep_SCI4_TEI4(vect=197))
void Excep_SCI4_TEI4(void);

// DMAC DMAC0I
#pragma interrupt (Excep_DMAC_DMAC0I(vect=198))
void Excep_DMAC_DMAC0I(void);

// DMAC DMAC1I
#pragma interrupt (Excep_DMAC_DMAC1I(vect=199))
void Excep_DMAC_DMAC1I(void);

// DMAC DMAC2I
#pragma interrupt (Excep_DMAC_DMAC2I(vect=200))
void Excep_DMAC_DMAC2I(void);

// DMAC DMAC3I
#pragma interrupt (Excep_DMAC_DMAC3I(vect=201))
void Excep_DMAC_DMAC3I(void);

// SCI7 ERI7
#pragma interrupt (Excep_SCI7_ERI7(vect=206))
void Excep_SCI7_ERI7(void);

// SCI7 RXI7
#pragma interrupt (Excep_SCI7_RXI7(vect=207))
void Excep_SCI7_RXI7(void);

// SCI7 TXI7
#pragma interrupt (Excep_SCI7_TXI7(vect=208))
void Excep_SCI7_TXI7(void);

// SCI7 TEI7
#pragma interrupt (Excep_SCI7_TEI7(vect=209))
void Excep_SCI7_TEI7(void);

// SCI10 ERI10
#pragma interrupt (Excep_SCI10_ERI10(vect=210))
void Excep_SCI10_ERI10(void);

// SCI10 RXI10
#pragma interrupt (Excep_SCI10_RXI10(vect=211))
void Excep_SCI10_RXI10(void);

// SCI10 TXI10
#pragma interrupt (Excep_SCI10_TXI10(vect=212))
void Excep_SCI10_TXI10(void);

// SCI10 TEI10
#pragma interrupt (Excep_SCI10_TEI10(vect=213))
void Excep_SCI10_TEI10(void);

// SCI0 ERI0
#pragma interrupt (Excep_SCI0_ERI0(vect=214))
void Excep_SCI0_ERI0(void);

// SCI0 RXI0
#pragma interrupt (Excep_SCI0_RXI0(vect=215))
void Excep_SCI0_RXI0(void);

// SCI0 TXI0
#pragma interrupt (Excep_SCI0_TXI0(vect=216))
void Excep_SCI0_TXI0(void);

// SCI0 TEI0
#pragma interrupt (Excep_SCI0_TEI0(vect=217))
void Excep_SCI0_TEI0(void);

// SCI1 ERI1
#pragma interrupt (Excep_SCI1_ERI1(vect=218))
void Excep_SCI1_ERI1(void);

// SCI1 RXI1
#pragma interrupt (Excep_SCI1_RXI1(vect=219))
void Excep_SCI1_RXI1(void);

// SCI1 TXI1
#pragma interrupt (Excep_SCI1_TXI1(vect=220))
void Excep_SCI1_TXI1(void);

// SCI1 TEI1
#pragma interrupt (Excep_SCI1_TEI1(vect=221))
void Excep_SCI1_TEI1(void);

// SCI5 ERI5
#pragma interrupt (Excep_SCI5_ERI5(vect=222))
void Excep_SCI5_ERI5(void);

// SCI5 RXI5
#pragma interrupt (Excep_SCI5_RXI5(vect=223))
void Excep_SCI5_RXI5(void);

// SCI5 TXI5
#pragma interrupt (Excep_SCI5_TXI5(vect=224))
void Excep_SCI5_TXI5(void);

// SCI5 TEI5
#pragma interrupt (Excep_SCI5_TEI5(vect=225))
void Excep_SCI5_TEI5(void);

// SCI6 ERI6
#pragma interrupt (Excep_SCI6_ERI6(vect=226))
void Excep_SCI6_ERI6(void);

// SCI6 RXI6
#pragma interrupt (Excep_SCI6_RXI6(vect=227))
void Excep_SCI6_RXI6(void);

// SCI6 TXI6
#pragma interrupt (Excep_SCI6_TXI6(vect=228))
void Excep_SCI6_TXI6(void);

// SCI6 TEI6
#pragma interrupt (Excep_SCI6_TEI6(vect=229))
void Excep_SCI6_TEI6(void);

// SCI8 ERI8
#pragma interrupt (Excep_SCI8_ERI8(vect=230))
void Excep_SCI8_ERI8(void);

// SCI8 RXI8
#pragma interrupt (Excep_SCI8_RXI8(vect=231))
void Excep_SCI8_RXI8(void);

// SCI8 TXI8
#pragma interrupt (Excep_SCI8_TXI8(vect=232))
void Excep_SCI8_TXI8(void);

// SCI8 TEI8
#pragma interrupt (Excep_SCI8_TEI8(vect=233))
void Excep_SCI8_TEI8(void);

// SCI9 ERI9
#pragma interrupt (Excep_SCI9_ERI9(vect=234))
void Excep_SCI9_ERI9(void);

// SCI9 RXI9
#pragma interrupt (Excep_SCI9_RXI9(vect=235))
void Excep_SCI9_RXI9(void);

// SCI9 TXI9
#pragma interrupt (Excep_SCI9_TXI9(vect=236))
void Excep_SCI9_TXI9(void);

// SCI9 TEI9
#pragma interrupt (Excep_SCI9_TEI9(vect=237))
void Excep_SCI9_TEI9(void);

// SCI12 ERI12
#pragma interrupt (Excep_SCI12_ERI12(vect=238))
void Excep_SCI12_ERI12(void);

// SCI12 RXI12
#pragma interrupt (Excep_SCI12_RXI12(vect=239))
void Excep_SCI12_RXI12(void);

// SCI12 TXI12
#pragma interrupt (Excep_SCI12_TXI12(vect=240))
void Excep_SCI12_TXI12(void);

// SCI12 TEI12
#pragma interrupt (Excep_SCI12_TEI12(vect=241))
void Excep_SCI12_TEI12(void);

// SCI12 SCIX0
#pragma interrupt (Excep_SCI12_SCIX0(vect=242))
void Excep_SCI12_SCIX0(void);

// SCI12 SCIX1
#pragma interrupt (Excep_SCI12_SCIX1(vect=243))
void Excep_SCI12_SCIX1(void);

// SCI12 SCIX2
#pragma interrupt (Excep_SCI12_SCIX2(vect=244))
void Excep_SCI12_SCIX2(void);

// SCI12 SCIX3
#pragma interrupt (Excep_SCI12_SCIX3(vect=245))
void Excep_SCI12_SCIX3(void);

// RIIC0 EEI0
#pragma interrupt (Excep_RIIC0_EEI0(vect=246))
void Excep_RIIC0_EEI0(void);

// RIIC0 RXI0
#pragma interrupt (Excep_RIIC0_RXI0(vect=247))
void Excep_RIIC0_RXI0(void);

// RIIC0 TXI0
#pragma interrupt (Excep_RIIC0_TXI0(vect=248))
void Excep_RIIC0_TXI0(void);

// RIIC0 TEI0
#pragma interrupt (Excep_RIIC0_TEI0(vect=249))
void Excep_RIIC0_TEI0(void);

// SCI11 ERI11
#pragma interrupt (Excep_SCI11_ERI11(vect=250))
void Excep_SCI11_ERI11(void);

// SCI11 RXI11
#pragma interrupt (Excep_SCI11_RXI11(vect=251))
void Excep_SCI11_RXI11(void);

// SCI11 TXI11
#pragma interrupt (Excep_SCI11_TXI11(vect=252))
void Excep_SCI11_TXI11(void);

// SCI11 TEI11
#pragma interrupt (Excep_SCI11_TEI11(vect=253))
void Excep_SCI11_TEI11(void);

//;<<VECTOR DATA START (POWER ON RESET)>>
//;Power On Reset PC
extern void PowerON_Reset_PC(void);                                                                                                                
//;<<VECTOR DATA END (POWER ON RESET)>>

