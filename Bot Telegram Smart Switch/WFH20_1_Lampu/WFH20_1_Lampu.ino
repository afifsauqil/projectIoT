#include "CTBot.h"
CTBot myBot;
CTBotReplyKeyboard Tbl;

#define Lampu D1

 bool TampilkanTombol;
              
 String ssid = "Home Sweet Home"; //nama SSID WIFI 
 String pass = "HALLOGUYS"; //Password WIFI
 String token = "2105032379:AAFLtggDdCeQVAstROafATtFktceSrJEWEo"; // Token dari Bot Father

void setup() {
  
Serial.begin(115200);                           
	Serial.println("Memulai Koneksi...");

	 myBot.wifiConnect(ssid, pass);       
	  myBot.setTelegramToken(token);      

    if (myBot.testConnection())   
	      Serial.println("\nKoneksi Ke Telegram BOT Berhasil!"); 
	  else 
	      Serial.println("\nTidak Terkoneksi Ke Telegram BOT"); 
	
	      pinMode(Lampu, OUTPUT);  
           
	      digitalWrite(Lampu, HIGH);      

           Tbl.addButton("Lampu ON");
           Tbl.addButton("Lampu OFF");
           Tbl.enableResize();
           TampilkanTombol = false;
           
}

void loop() {
TBMessage msg;

	if (myBot.getNewMessage(msg)) {                                                           
    if (msg.text.equalsIgnoreCase("/start")) {                                         
          myBot.sendMessage(msg.sender.id, "Visit to my github account!\nhttps://github.com/afifsauqil/");
          myBot.sendMessage(msg.sender.id, "By Afif, Bima, Haydar XIII-SIJA.");
          myBot.sendMessage(msg.sender.id, "Halo...\nWelcome to Smart Switched Bot.\n\nGunakan tombol dibawah untuk mengontrol lampu 👇", Tbl);
          Serial.println("\nUser memulai Bot \n");
          TampilkanTombol = true;
    } else if (msg.text.equalsIgnoreCase("Lampu OFF")) {
          digitalWrite(Lampu, LOW);
          myBot.sendMessage(msg.sender.id, "💡 Lampu Telah Dimatikan");
          Serial.println("\nUser mematikan Lampu\n");
      } else if (msg.text.equalsIgnoreCase("Lampu ON")) {
          digitalWrite(Lampu, HIGH);
          myBot.sendMessage(msg.sender.id, "💡 Lampu Telah Dinyalakan");
          Serial.println("\nUser menyalakan Lampu\n");
      }  else {   
			        myBot.sendMessage(msg.sender.id, "⛔️ ERROR: Perintah tidak dikenal?!\n\nGunakan tombol dibawah untuk mengontrol lampu 👇", Tbl);
              Serial.println("\nUser mengirim perintah yang tidak dikenal\n");
		    }
	   }
	delay(500);
}
