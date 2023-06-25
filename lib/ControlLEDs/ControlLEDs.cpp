#include<ControlLEDs.h>
#include<Arduino.h>
#include<Lichtschranke.h>
#include<Defines.h>

#ifndef ButtonII
#define ButtonII 4
#endif

#ifndef ButtonI
#define ButtonI 5
#endif

//Control LEDs
#ifndef LEDIV
#define LEDIV 13
#endif
#ifndef LEDII
#define LEDII    17
#endif
#ifndef LEDIII
#define LEDIII  20
#endif
#ifndef LEDI
#define LEDI    37
#endif

void blink(uint8_t pin[],size_t s, int time){
  static unsigned long Tnext=time;
  static bool Znext=true;
  if(millis()>=Tnext){
    for(size_t i=0;i<s;i++){
      digitalWrite(pin[i],Znext);
    }
    Znext=!Znext;
    Tnext=millis()+time;
  }
}
void wave(uint8_t pin[],size_t s, int time){
  static size_t count=0;
  static unsigned long Tnext=time;
  if(millis()>=Tnext){
    count++;
    Tnext=millis()+time;
  }if(count>=s){count=0;}
  for(size_t i=0;i<s;i++){
    if(count==i){
      digitalWrite(pin[i],HIGH);
      
    }else{
      digitalWrite(pin[i],LOW);
    }
  }
}

void ControlLEDs(bool& buttonGpressed, double &richtung,double& IRbest, int& Icball, double& rotation,bool& minEinerDa, bool& irAutoCalibration, bool& IRsave, bool hBall, bool torwart) {
  //Einzelne Variablen überprüfen und dann die Pins schreiben
  if (digitalRead(ButtonI) == LOW) {
    buttonGpressed = true;
  }
  if (digitalRead(ButtonIV) == LOW) {
    irAutoCalibration=true;
    Serial.println("IR-Reset");
  }
  if(digitalRead(ButtonIII) == LOW){
    IRsave=true;
  }if(digitalRead(ButtonII)==LOW){
    digitalWrite(Schuss_FW,LOW);
    digitalWrite(Schuss_RW,HIGH);
    analogWrite(Schuss_PWM,255);
    delay(20);
    digitalWrite(Schuss_FW,HIGH);
    digitalWrite(Schuss_RW,LOW);
    analogWrite(Schuss_PWM,0);
  }
  // if (torwart) {
  //   digitalWrite(LEDII, HIGH);
  // } else {
  //   digitalWrite(LEDII, LOW);
  // }
  // if (minEinerDa) {
  //   digitalWrite(LEDIV, HIGH);
  // } else {
  //   digitalWrite(LEDIV, LOW);
  // }
  // if (hBall) {
  //   digitalWrite(LEDI, HIGH);
  // } else {
  //   digitalWrite(LEDI, LOW);
  // }
  // if (rotation <= 2.5 && rotation >= -2.5) {
  //   digitalWrite(LEDIII, HIGH);
  // } else {
  //   digitalWrite(LEDIII, LOW);
  // }
}