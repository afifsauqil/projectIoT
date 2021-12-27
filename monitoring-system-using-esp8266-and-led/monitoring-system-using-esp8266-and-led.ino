// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>
#include "DHT.h"                //Library DHT
#define DHTPIN D5             //Inisialisasi DHT pada pin D5
#define DHTTYPE DHT22           //Inisialisasi tipe DHT
//#include <Adafruit_Sensor.h>    //Library Adafruit Sensor

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "ASUS"
#define REMOTEXY_WIFI_PASSWORD "1234567809"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "b0b872ddfb536a8d0b9b5e13a02d991e"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,15,0,79,0,13,25,1,
  67,4,19,71,18,10,2,26,11,68,
  49,2,20,59,39,8,78,83,117,104,
  117,32,83,101,114,118,101,114,32,68,
  97,108,97,109,32,194,176,67,0,129,
  0,37,72,10,9,2,194,176,67,0,
  129,0,4,7,55,6,2,115,101,110,
  115,111,114,32,115,117,104,117,32,115,
  101,114,118,101,114,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  char text_t[11];  // string UTF8 end zero 
  float onlineGraph_t;

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop) 

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

DHT dht (DHTPIN,DHTTYPE);   //Mengenalkan pin dan tipe DHT
float t;                    //Variabel penampung nilai suhu

int LEDM = D1;   //LED pin D1
int LEDH = D0;   //LED pin D3
const int pinBuzzer = D6;

void setup() 
{
  RemoteXY_Init (); 
  
  Serial.begin(9600);             //Mulai komunikasi serial
  pinMode(LEDM, OUTPUT);
  pinMode(LEDH, OUTPUT);
  dht.begin();                    //Mulai DHT
  pinMode(pinBuzzer, OUTPUT);
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  
    t = dht.readTemperature();    //Baca suhu

  dtostrf(t, 0, 1, RemoteXY.text_t);
  RemoteXY.onlineGraph_t = t;
  
  Serial.print("Suhu : ");
  Serial.print(t);              //Tampilkan suhu
  Serial.println(" °C");

  if (t <= 28){                 //Jika suhu <= 20*C, maka
    digitalWrite(LEDM, LOW); 
    digitalWrite(LEDH, HIGH);   //LED biru menyala
    //digitalWrite(pinBuzzer, HIGH);
    //delay(200);
    //digitalWrite(pinBuzzer, LOW);
    //delay(300);
  }
    else if (t > 28){             //Jika suhu > 21*C, maka
    digitalWrite(LEDM, HIGH);   //LED merah menyala
    digitalWrite(LEDH, LOW);
    digitalWrite(pinBuzzer, HIGH);
    delay(1000);
    digitalWrite(pinBuzzer, LOW);
    delay(200);
  }

  delay(700);
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}
