#ifndef DEFINES_H_
#define DEFINES_H_

#define M1_FW 0 //richtig
#define M1_RW 2
#define M1_PWM 1

#define M2_FW 3 //richtig
#define M2_RW 5
#define M2_PWM 4

#define M3_FW  6  //richtig!
#define M3_RW 8
#define M3_PWM 7

#define M4_FW  9  //richtig!
#define M4_RW 11
#define M4_PWM 10

#define breite 182
#define laenge 200

//Multiplexer Unten
#define S0 17
#define S1 16
#define S2 15
#define S3 14

#define UAM1 A15 //analog Multiplexer Unten 1
#define UAM2 A16 //analog Multplexer Unten 2
#define UAM3 A14 // analog Multiplexer Unten 3
#define AM1 A17 //analog Multiplexer Oben

#define ButtonIV 2
#define ButtonIII 3
#define ButtonII 4
#define ButtonI 5

#define VR 1 //m1
#define VL 2 //m2
#define HR 3 //m3
#define HL 4 //m4

//Control LEDs
#define LEDIV 13
#define LEDII    17
#define LEDIII  37
#define LEDI    20

#define Nah 25
#define Mittel 50
#define Fern 70

#define LichtSchranke A2

#endif