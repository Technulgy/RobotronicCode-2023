#include<Torwart.h>
#include<Motoren.h>
#include<Kompass.h>
#include<IR2.h>
#include<Boden.h>
#include<myPixy.h>

#define ballUndLinie false //Solle er, wenn er die linie sieht immernoch auf den Ball reagiern?
#define Abweichung 10 //Wie schräg soll er fahren, wenn er auf den Ball und die Linie reagieren soll

void torwartProgramm(Pixy2I2C& pixy2,int* LED,int* Schwellwerte, double rotation,Adafruit_BNO055 &gyro, bool &buttonGpressed, double &minus, int &alterWinkel, double &addRot, bool piread2, int pixyG2, int& PixyG, int *IR, double &IRbest, int &Icball, double &richtung, double &wiIn, int *minWert, bool &irAutoCalibration, double &WinkelBall, bool &IRsave, bool hatBall, bool& torwart,double accel,int&  TorHoehe,int&  TorHoehe2,double &entfSet,PID &wiPID,unsigned long& addRotTime){
    //Serial.println(LED[1]);
    constexpr int Grenze = 40;
    pixyG2 = Pixy2(pixy2,piread2,TorHoehe2);
    //Serial.println(pixyG2);
    compass(gyro,buttonGpressed,minus,rotation,alterWinkel, addRot,piread2,PixyG,pixyG2,hatBall,torwart,accel);
    IRsensTW(IR,IRbest,Icball,richtung,wiIn,minWert,irAutoCalibration,rotation,addRot,WinkelBall,IRsave);
    //Serial.println(wiIn);
    if (LED[12] > Schwellwerte[12] || LED[13] > Schwellwerte[13]) {
        motor(0, 150,rotation);
        //Serial.println("salkd1");
    } else if (LED[20] > Schwellwerte[20] || LED[21] > Schwellwerte[21]) {
        motor(180, 150,rotation);
        //Serial.println("salkd2");
    } else {
        if (onLine(LED,Schwellwerte)) {
            if (IRbest < Grenze&&Icball == 0) {
                Serial.println("vorne");
                motor(90, 100,rotation);
            } else if (IRbest < Grenze&&Icball == 1){
                motor(67,100,rotation);
            } else if(IRbest < Grenze&&Icball == 15){
                motor(112,100,rotation);    
            } else if (richtung == -1) {
                motor(0, 0,rotation);
                Serial.println("nicht");
            } else if (wiIn < 0) {
                Serial.println("links");
                motor(180, 70,rotation);
            } else {
                Serial.println("rechts");
                motor(0, 70,rotation);
            }
            Serial.println("onli");
        }
        else {
            if(IRbest < Grenze&&Icball == 0){                           //hier Ballverfolgung rein basically
                motor(90,100,rotation);
            }else if(IRbest < Grenze&&Icball == 1){
                motor(112,100,rotation);
            }else if(IRbest < Grenze&&Icball == 15){
                motor(67,100,rotation);
            }else{
            if(piread2 == false){
                //compass(gyro,buttonGpressed,minus,rotation,alterWinkel,addRot,pireads,PixyG,pixyG2,hatBall,torwart,accel);
                motor(0,0,10);
            }else{
                if (LED[44] > Schwellwerte[44] || LED[45] > Schwellwerte[45] || LED[34] > Schwellwerte[34] || LED[35] > Schwellwerte[35]) {
                    if(ballUndLinie){
                        if (wiIn == 0) {
                            //Serial.println("yes vorne");
                            motor(90, 100,rotation);
                        }  else if (richtung == -1) {
                            //Serial.println("yes nicht");
                            motor(90, 100,rotation);
                        } else if (wiIn < 0) {
                            // Serial.println("yes rechts");
                            motor(90-Abweichung, 70,rotation);
                        } else {
                            // Serial.println("yes links");
                            motor(90+Abweichung, 70,rotation);
                        }
                    }else{
                        motor(90, 170,rotation);
                    }
                }
                else {
                    if(ballUndLinie){
                        if (wiIn == 0) {
                            // Serial.println("no vorne");
                            motor(270, 40,rotation);
                        }  else if (richtung == -1) {
                            // Serial.println("no nicht");
                            motor(270, 40,rotation);
                        } else if (wiIn < 0) {
                            // Serial.println("no rechts");
                            motor(270+Abweichung, 40,rotation);
                        } else {
                            // Serial.println("no links");
                            motor(270-Abweichung, 40,rotation);
                        }
                    }else{
                        motor(270, 40,rotation);
                    }
                }
            }
            }
        }
    }
    // Serial.println(LED[17]);
}