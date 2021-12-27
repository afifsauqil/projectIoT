 /* Program Indikator Suhu DHT11 dengan LED dibuat oleh XIII-SIJA */

#include "DHT.h"            //Library DHT
#define DHTPIN 5            //Inisialisasi DHT pada pin D5
#define DHTTYPE DHT22       //Inisialisasi tipe DHT
#include <Adafruit_Sensor.h>

DHT dht (DHTPIN,DHTTYPE);   //Mengenalkan pin dan tipe DHT

float t;  //Variabel penampung nilai suhu

int LEDM = 2;   //LED merah pada pin D2
int LEDK = 3;   //LED kuning pada pin D3
int LEDH = 4;   //LED hijau pada pin D4
const int pinBuzzer = 12;

void setup() {
  Serial.begin(9600);     //Mulai komunikasi serial
  dht.begin();            //Mulai DHT
  pinMode(LEDM, OUTPUT);  //Setting LED sebagai output
  pinMode(LEDK, OUTPUT);
  pinMode(LEDH, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  t = dht.readTemperature();    //Baca suhu

  Serial.print("Suhu : ");
  Serial.print(t);              //Tampilkan suhu
  Serial.println(" *C");
  
  if (t <= 24){                 //Jika suhu <= 20*C, maka
    digitalWrite(LEDM, LOW); 
    digitalWrite(LEDK, LOW);
    digitalWrite(LEDH, HIGH);   //LED biru menyala
    digitalWrite(pinBuzzer, HIGH);
    delay(1000);
    digitalWrite(pinBuzzer, LOW);
    delay(3000);
  }
//  else if (t <= 30){            //Jika suhu <= 30*C, maka
//    digitalWrite(LEDM, LOW);
//    digitalWrite(LEDK, HIGH);   //LED putih menyala
//    digitalWrite(LEDH, LOW);
//  }
  else if (t > 24){             //Jika suhu > 21*C, maka
    digitalWrite(LEDM, HIGH);   //LED merah menyala
    digitalWrite(LEDK, LOW);
    digitalWrite(LEDH, LOW);
    digitalWrite(pinBuzzer, HIGH);
    delay(200);
    digitalWrite(pinBuzzer, LOW);
    delay(200);
  }

  delay(1000);                  //Jeda pembacaan 1000ms
}
