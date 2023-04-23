#include <myPixy.h>
#include <Pixy2I2C.h>

// [[deprecated]] double Pixy(Pixy2I2C& pixy,bool& piread){
//   constexpr size_t s=500;
//   static double pixywinkel = -1;
//   static unsigned long time=0;
//   static double buf[s];     //das Glätten hier ist falschrum… (in der Forschleife fürs Verschieben)
//   pixy.ccc.getBlocks();       //pixy auslesen

//   if (pixy.ccc.numBlocks){
//     if(millis()>=time){
//       piread = true;          //Kamera sieht was

//       //int16_t farbe = pixy.ccc.blocks[0].m_signature;
//       int16_t TorX = (pixy.ccc.blocks[0].m_x) - 158 ;
//       int16_t TorY = 208 - (pixy.ccc.blocks[0].m_y);
//       /*uint16_t TorHoehe = pixy.ccc.blocks[0].m_height;
//         uint16_t TorBreite = pixy.ccc.blocks[0].m_width;*/

//       const int UrX = 0;
//       const int UrY = 0;

//       int VekTorX = UrX - TorX;
//       int VekTorY = UrY - TorY;
//       pixywinkel = atan2(VekTorY,- VekTorX) * 180/PI; //berechnen des Winkels
//       pixywinkel = abs(pixywinkel);         //Betrag
//       for(int i=1;i<s;i++){               //diese Forschleife muss andersrum gemacht werden
//         buf[i]=buf[i-1];
//       }
//       buf[0]=pixywinkel;
//       pixywinkel=0;
//       for(int i=0;i<s;i++){
//         pixywinkel+=buf[i]/s;
//       }
//       // Serial.println(farbe);
//       time=millis()+50;
//     }
//   }
//   else {
//     time=millis();
//     for(int i=0;i<s;i++){               //resetten der Buffer-Werte
//       buf[i]=0;
//     }
//     piread = false;
//   }
//   return 90-pixywinkel;
// }

double Pixy(Pixy2I2C& pixy,bool& piread) {
  constexpr size_t s=50;
  static double pixywinkel = -1;
  static unsigned long time=0;
  static double buf[s];       //das Glätten
  pixy.ccc.getBlocks();       //pixy auslesen

  if (pixy.ccc.numBlocks){
    if(millis()>=time){
      piread = true;          //Kamera sieht was

      //int16_t farbe = pixy.ccc.blocks[0].m_signature;
      int16_t TorX = (pixy.ccc.blocks[0].m_x) - 158 ;
      int16_t TorY = 208 - (pixy.ccc.blocks[0].m_y);
      /*uint16_t TorHoehe = pixy.ccc.blocks[0].m_height;
        uint16_t TorBreite = pixy.ccc.blocks[0].m_width;*/

      const int UrX = 0;
      const int UrY = 0;

      int VekTorX = UrX - TorX;
      int VekTorY = UrY - TorY;
      pixywinkel = atan2(VekTorY,- VekTorX) * 180/PI; //berechnen des Winkels
      pixywinkel = abs(pixywinkel);         //Betrag
      for(int i=s-1;i>0;i--){
        buf[i]=buf[i-1];
      }
      buf[0]=pixywinkel;
      pixywinkel=0;
      for(int i=0;i<s;i++){
        pixywinkel+=buf[i]/s;
      }
      // Serial.println(farbe);
      time=millis()+50;
    }
  }
  else {
    time=millis();
    for(int i=0;i<s;i++){               //resetten der Buffer-Werte
      buf[i]=0;
    }
    piread = false;
  }
  return 90-pixywinkel;
}