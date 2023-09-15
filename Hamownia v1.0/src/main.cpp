#include "pinout.h"
//#include <Arduino.h> XD
#include "BluetoothSerial.h"
//#include "HX711.h" ???????????
#include <FS.h>
#include <SD.h>
 
BluetoothSerial SerialBT;


unsigned long currentMillis = 0;
unsigned long previousMillis = 0; 
unsigned long interval = 1000;

String informacja = "";



String odczyt_bt();
void kalibruj();
void uzbroj();
void abort();

void setup() {
  Serial.begin(9600);
  pinMode(przelacznik_pin, INPUT);
  pinMode(bezpiecznik_uzbrojenie_ledpin, OUTPUT);
  pinMode(bezpiecznik2_ledpin, OUTPUT);
  pinMode(zapalnik_pin, OUTPUT);

  SerialBT.begin("Hamownia");
  Serial.println("Gotowosc do parowania");
}

void loop() {

  if(digitalRead(przelacznik_pin)==HIGH){
    informacja = odczyt_bt();
    if(informacja == "kalibracja"){
      kalibruj();
    }
    if(informacja == "uzbrojenie"){
      digitalWrite(bezpiecznik_uzbrojenie_ledpin, HIGH);
      informacja = odczyt_bt();
      if(informacja == "teststart"){
        Serial.println("start testu");
      }
    }
  }
}

String odczyt_bt(){ //czy zwracanie całego stringa przez funckję jest optymalne wydajnościowo i czasowo?
  String odebrane = ""; //czy lepiej tworzyć za każdym razem zmienne czy pracować na globalach?
  //podobno nie jest to az tak wolne i jest git, mozna i tak
  char znak = 'a'; //jw
  while (SerialBT.available()) {
    znak = SerialBT.read();
    if ((znak != '\n')&&(znak != '\r')){
      odebrane += String(znak);
    }
    delay(20); //czy powinien tu być? dobre pytanie
  }
  return odebrane;
}

void abort(){

}

void kalibruj(){
  //jw
}

void uzbroj(){
  //jw
}