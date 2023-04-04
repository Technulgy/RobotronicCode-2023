#include<IR2.h>
#include<Arduino.h>
#include<PID_v1.h>

#ifndef S0          //Multiplexer Unten
#define S0 17
#endif
#ifndef S1
#define S1 16
#endif
#ifndef S2
#define S2 15
#endif
#ifndef S3
#define S3 14
#endif

#ifndef AM1
#define AM1 A17     //analog Multiplexer Oben
#endif


int lesenMultiplexerOben(int s0, int s1, int s2, int s3) {           //Verkürzung Auslesen
  digitalWrite(S0, s3);
  digitalWrite(S1, s2);
  digitalWrite(S2, s1);
  digitalWrite(S3, s0);
  return analogRead(AM1);
}
void IRsens(int* IR, double& IRbest, int& Icball, double& richtung,double &entfSet, double &wiIn, PID &wiPID, int* minWert, bool& irAutoCalibration) {
  if(!irAutoCalibration){
    static double AnfahrtsRadius=13;                                   //Achtung: auch bei der IR Kalibration ändern!
    static double BallWegRadius=75;
    entfSet=AnfahrtsRadius;
    /* static int min=1023;
    int gelesen=lesenMultiplexerOben(0,0,1,0);
    if(min>gelesen){
      min=gelesen;
      Serial.println(gelesen);
    } */
    if(minWert[0]==1023){//414|417|416|417|414|414|425|420|418|418|416|418|417|417|412|422|;
      IR[0] = map(lesenMultiplexerOben(0, 0, 0, 0), 414 , 1023, 0, 100);   //alle IRs auslesen und mappen
      IR[1] = map(lesenMultiplexerOben(0, 0, 0, 1), 417 , 1023, 0, 100);
      IR[2] = map(lesenMultiplexerOben(0, 0, 1, 0), 416 , 1023, 0, 100);
      IR[3] = map(lesenMultiplexerOben(0, 0, 1, 1), 417 , 1023, 0, 100);
      IR[4] = map(lesenMultiplexerOben(0, 1, 0, 0), 414 , 1023, 0, 100);
      IR[5] = map(lesenMultiplexerOben(0, 1, 0, 1), 414 , 1023, 0, 100);
      IR[6] = map(lesenMultiplexerOben(0, 1, 1, 0), 425 , 1023, 0, 100);
      IR[7] = map(lesenMultiplexerOben(0, 1, 1, 1), 420 , 1023, 0, 100);
      IR[8] = map(lesenMultiplexerOben(1, 0, 0, 0), 418 , 1023, 0, 100);
      IR[9] = map(lesenMultiplexerOben(1, 0, 0, 1), 418 , 1023, 0, 100);
      IR[10] = map(lesenMultiplexerOben(1, 0, 1, 0),416 , 1023, 0, 100);
      IR[11] = map(lesenMultiplexerOben(1, 0, 1, 1),418 , 1023, 0, 100);
      IR[12] = map(lesenMultiplexerOben(1, 1, 0, 0),417 , 1023, 0, 100);
      IR[13] = map(lesenMultiplexerOben(1, 1, 0, 1),417 , 1023, 0, 100);
      IR[14] = map(lesenMultiplexerOben(1, 1, 1, 0),412 , 1023, 0, 100);
      IR[15] = map(lesenMultiplexerOben(1, 1, 1, 1),422 , 1023, 0, 100);
    }else{
      IR[0] = map(lesenMultiplexerOben(0, 0, 0, 0), minWert[0], 1023, 0, 100);   //alle IRs auslesen und mappen
      IR[1] = map(lesenMultiplexerOben(0, 0, 0, 1), minWert[1], 1023, 0, 100);
      IR[2] = map(lesenMultiplexerOben(0, 0, 1, 0), minWert[2], 1023, 0, 100);
      IR[3] = map(lesenMultiplexerOben(0, 0, 1, 1), minWert[3], 1023, 0, 100);
      IR[4] = map(lesenMultiplexerOben(0, 1, 0, 0), minWert[4], 1023, 0, 100);
      IR[5] = map(lesenMultiplexerOben(0, 1, 0, 1), minWert[5], 1023, 0, 100);
      IR[6] = map(lesenMultiplexerOben(0, 1, 1, 0), minWert[6], 1023, 0, 100);
      IR[7] = map(lesenMultiplexerOben(0, 1, 1, 1), minWert[7], 1023, 0, 100);
      IR[8] = map(lesenMultiplexerOben(1, 0, 0, 0), minWert[8], 1023, 0, 100);
      IR[9] = map(lesenMultiplexerOben(1, 0, 0, 1), minWert[9], 1023, 0, 100);
      IR[10] = map(lesenMultiplexerOben(1, 0, 1, 0), minWert[10], 1023, 0, 100);
      IR[11] = map(lesenMultiplexerOben(1, 0, 1, 1), minWert[11], 1023, 0, 100);
      IR[12] = map(lesenMultiplexerOben(1, 1, 0, 0), minWert[12], 1023, 0, 100);
      IR[13] = map(lesenMultiplexerOben(1, 1, 0, 1), minWert[13], 1023, 0, 100);
      IR[14] = map(lesenMultiplexerOben(1, 1, 1, 0), minWert[14], 1023, 0, 100);
      IR[15] = map(lesenMultiplexerOben(1, 1, 1, 1), minWert[15], 1023, 0, 100);
    }
    IRbest = 90;                                                        //bestimmen des niedrigsten, gemessenen Wertes und Speichern des Index in Icball
    for (int i = 0; i < 16; i++) {
      if (IR[i] < IRbest) {
        IRbest = IR[i];
        Icball = i;
      }
    }
    double WinkelBall=90-22.5*Icball;                                   //Berechnen des Winkels zum Ball
    if(WinkelBall<=0){                                                  //auf Wertebereich 0-360 verschieben
      WinkelBall+=360;
    }
    wiIn=WinkelBall-90;                                                 //Winkel berechnen, sodass der Vorzeichen-Wechsel hinten beim Roboter liegt
    //Serial.println(WinkelBall);
    if(wiIn>180){
      wiIn-=360;
    }
    //Serial.println(wiIn);
    if(IRbest>BallWegRadius){                                           //Wenn er den Ball nicht sieht
      richtung=-1;
      return;
    }
    if(WinkelBall<0){
      WinkelBall+=360;
    }
    if(Icball==0&&IRbest<=AnfahrtsRadius+3){                            //Ball vor dem Roboter
      richtung=90;                                                      //nach vorne fahren
      return;                                                           //damit die Werte nicht noch überschrieben werden
      //Serial.println("vor");
    }
    if(IRbest<AnfahrtsRadius){                                          //Wenn der Roboter im Anfahrtskreis steht
      richtung=270;                                                     //nach hinten fahren
      return;
    }
    if(Icball<=8){                                                      //Ball rechts vom Roboter
      richtung=WinkelBall-(asin((double)AnfahrtsRadius/IRbest))*180/PI; //auf der unteren Tangente fahren
      wiPID.SetControllerDirection(DIRECT);
    }else{                                                              //Ball links vom Roboter
      richtung=WinkelBall+(asin((double)AnfahrtsRadius/IRbest))*180/PI; //auf der unteren Tangente fahren
      wiPID.SetControllerDirection(REVERSE);
    }
    if(richtung<0){                                                     //auf Wertebereich 0-360 verscheiben
      richtung+=360;
    }
    if(richtung>360){
      richtung-=360;
    }
  }else{
    irAutoCal(minWert);
    for(int i=0;i<16;i++){
      Serial.print(minWert[i]);
      Serial.print("|");
    }
    Serial.println(";");
  }
}

void irAutoCal(int* minWert){
  if(minWert[0]>lesenMultiplexerOben(0, 0, 0, 0)){minWert[0]=lesenMultiplexerOben(0, 0, 0, 0);}
  if(minWert[1]>lesenMultiplexerOben(0, 0, 0, 1)){minWert[1]=lesenMultiplexerOben(0, 0, 0, 1);}
  if(minWert[2]>lesenMultiplexerOben(0, 0, 1, 0)){minWert[2]=lesenMultiplexerOben(0, 0, 1, 0);}
  if(minWert[3]>lesenMultiplexerOben(0, 0, 1, 1)){minWert[3]=lesenMultiplexerOben(0, 0, 1, 1);}
  if(minWert[4]>lesenMultiplexerOben(0, 1, 0, 0)){minWert[4]=lesenMultiplexerOben(0, 1, 0, 0);}
  if(minWert[5]>lesenMultiplexerOben(0, 1, 0, 1)){minWert[5]=lesenMultiplexerOben(0, 1, 0, 1);}
  if(minWert[6]>lesenMultiplexerOben(0, 1, 1, 0)){minWert[6]=lesenMultiplexerOben(0, 1, 1, 0);}
  if(minWert[7]>lesenMultiplexerOben(0, 1, 1, 1)){minWert[7]=lesenMultiplexerOben(0, 1, 1, 1);}
  if(minWert[8]>lesenMultiplexerOben(1, 0, 0, 0)){minWert[8]=lesenMultiplexerOben(1, 0, 0, 0);}
  if(minWert[9]>lesenMultiplexerOben(1, 0, 0, 1)){minWert[9]=lesenMultiplexerOben(1, 0, 0, 1);}
  if(minWert[10]>lesenMultiplexerOben(1, 0, 1, 0)){minWert[10]=lesenMultiplexerOben(1, 0, 1, 0);}
  if(minWert[11]>lesenMultiplexerOben(1, 0, 1, 1)){minWert[11]=lesenMultiplexerOben(1, 0, 1, 1);}
  if(minWert[12]>lesenMultiplexerOben(1, 1, 0, 0)){minWert[12]=lesenMultiplexerOben(1, 1, 0, 0);}
  if(minWert[13]>lesenMultiplexerOben(1, 1, 0, 1)){minWert[13]=lesenMultiplexerOben(1, 1, 0, 1);}
  if(minWert[14]>lesenMultiplexerOben(1, 1, 1, 0)){minWert[14]=lesenMultiplexerOben(1, 1, 1, 0);}
  if(minWert[15]>lesenMultiplexerOben(1, 1, 1, 1)){minWert[15]=lesenMultiplexerOben(1, 1, 1, 1);}
}