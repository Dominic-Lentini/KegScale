#include <HX711_ADC.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

HX711_ADC scale1(4,5);
HX711_ADC scale2(6,7);
HX711_ADC scale3(8,9);
HX711_ADC scale4(10,11);
LiquidCrystal_I2C lcd2(0x26,16,2);
LiquidCrystal_I2C lcd1(0x27,16,2);
SoftwareSerial ESPserial(3,2);
char tapn;
float i1a,i2a,i3a,i4a;
float i1b = 0;
float i2b = 0;
float i3b = 0;
float i4b = 0;
String Tap1= "N/A    ";
String Tap2= "N/A    ";
String Tap3= "N/A    ";
String Tap4= "N/A    ";

bool t = true;
void refreshLCD1();
void refreshLCD2();


void setup() {
Serial.begin(9600);
Serial.println("Test");
ESPserial.begin(9600);
lcd1.init();
lcd2.init();
lcd1.backlight();
lcd2.backlight();
lcd1.clear();
lcd2.clear();
lcd1.setCursor(0,0);
lcd2.setCursor(0,0);
scale1.begin();
scale2.begin();
scale3.begin();
scale4.begin();
scale1.setCalFactor(23.0);
scale2.setCalFactor(22.45);
scale3.setCalFactor(23.0);
scale4.setCalFactor(23.0);
scale1.start(2000,t);
scale2.start(2000,t);
scale3.start(2000,t);
scale4.start(2000,t);

refreshLCD1();
refreshLCD2();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(ESPserial.available()){
    tapn = ESPserial.read();
    Serial.write("Tap number determined: ");
    Serial.println(tapn);
    delay(5);
    while(ESPserial.available()){
      if(tapn == '1'){
        for(int i=0;i<8;i++){
          Tap1[i] = ' ';
        }
        for(int i=0;i<8;i++){
          if(ESPserial.available()){
          Tap1[i]=ESPserial.read();
          Serial.write(Tap1[i]);
          delay(5);         
          }
          else{
            Tap1[i] = ' ';
            delay(5);
          }
          
        }
        Serial.write("Tap 1 set ");
        Serial.println(Tap1);
        refreshLCD1(); 
      }
      if(tapn == '2'){
        for(int i=0;i<8;i++){
          Tap2[i] = ' ';
        }
        for(int i=0;i<8;i++){
          if(ESPserial.available()){
          Tap2[i]=ESPserial.read();
          Serial.write(Tap2[i]);
          delay(5);         
          }
          else{
            Tap2[i] = ' ';
            delay(5);
          }
        }
        Serial.write("Tap 2 set ");
        Serial.println(Tap2);
        refreshLCD1();     
      }
      if(tapn == '3'){
        for(int i=0;i<8;i++){
          Tap3[i] = ' ';
        }
        for(int i=0;i<8;i++){
          if(ESPserial.available()){
          Tap3[i]=ESPserial.read();
          Serial.write(Tap3[i]);
          delay(5);         
          }
          else{
            Tap3[i] = ' ';
            delay(5);
          }
        }
        Serial.write("Tap 3 set ");
        Serial.println(Tap3);
        refreshLCD2();     
      }
      if(tapn == '4'){
        for(int i=0;i<8;i++){
          Tap4[i] = ' ';
        }
        for(int i=0;i<8;i++){
          if(ESPserial.available()){
          Tap4[i]=ESPserial.read();
          Serial.write(Tap4[i]);
          delay(5);         
          }
          else{
            Tap4[i] = ' ';
            delay(5);
          }
        }
        Serial.write("Tap 4 set ");
        Serial.println(Tap4); 
        refreshLCD2();               
      }
      while(ESPserial.available()){
      ESPserial.read();
      }
    }
  }

  if(scale1.update()){
    i1a = scale1.getData();
    if(i1b<i1a-28 || i1b>i1a+28){
      i1b=i1a;
      refreshLCD1();
    }
  }
  if(scale2.update()){
    i2a = scale2.getData();
    if(i2b<i2a-28 || i2b>i2a+28){
      i2b=i2a;
      refreshLCD1();
    }
  }
  if(scale3.update()){
    i3a = scale3.getData();
    if(i3b<i3a-28 || i3b>i3a+28){
      i3b=i3a;
      refreshLCD2();
    }
  }
  if(scale4.update()){
    i4a = scale4.getData();
    if(i4b<i4a-28 || i4b>i4a+28){
      i4b=i4a;
      refreshLCD2();
    }
  }
  
}

void refreshLCD1(){
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print(Tap1);
      lcd1.setCursor(8,0);
      lcd1.print(Tap2);
      lcd1.setCursor(10,1);
      lcd1.print((int)((i2b/28.35)-128));
      lcd1.print("oz");
      lcd1.setCursor(0,1);
      lcd1.print((int)(i1b/28.35)-128);
      lcd1.print("oz");
}

void refreshLCD2(){
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print(Tap3);
      lcd2.setCursor(8,0);
      lcd2.print(Tap4);
      lcd2.setCursor(10,1);
      lcd2.print((int)((i4b/28.35)-122));
      lcd2.print("oz");
      lcd2.setCursor(0,1);
      lcd2.print((int)(i3b/28.35)-128);
      lcd2.print("oz");
}
