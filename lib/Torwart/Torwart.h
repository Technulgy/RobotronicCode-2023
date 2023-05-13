#ifndef TORWART_H_
#define TORWART_H_

#include<Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <EEPROM.h>
#include <myPixy.h>

void torwartProgramm(Pixy2I2C& pixy2,int* LED,int* Schwellwerte, double rotation,Adafruit_BNO055 &gyro, bool &buttonGpressed, double &minus, int &alterWinkel, double &addRot, bool pireads, int pixyG2, int& PixyG, int *IR, double &IRbest, int &Icball, double &richtung, double &wiIn, int *minWert, bool &irAutoCalibration, double &WinkelBall, bool &IRsave, bool hatBall, bool& torwart);

#endif