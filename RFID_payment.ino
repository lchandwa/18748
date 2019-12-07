#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "101A"
#define WIFI_PASSWORD "Martand#29"
#define FIREBASE_HOST "sronlineorder.firebaseio.com"
#define FIREBASE_AUTH "itJoWoStdvVALQATa4sQ8zbyUwYla6kUJd7KEmCY"
/*
 *  Created by TheCircuit
*/

#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

#include <SPI.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  wifiConnect();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if(WiFi.status() != WL_CONNECTED)
  {
     wifiConnect();
  }
  delay(10);
 
  Firebase.setString("rfidKey/"+content.substring(1), "Scanned");
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(5000);
  /*if (content.substring(1) == "54 BD 38 6D") //change UID of the card that you want to give access
  {
    Serial.println(" Access Granted ");
    Serial.println(" Welcome Mr.Circuit ");
    delay(1000);
    Serial.println(" Have FUN ");
    Serial.println();
    statuss = 1;
  }
  
  else   {
    Serial.println(" Access Denied ");
    delay(3000);
  }*/
}
void wifiConnect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID); Serial.println(" ...");

  int teller = 0;
  while (WiFi.status() != WL_CONNECTED)
  {                                       // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++teller); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}
