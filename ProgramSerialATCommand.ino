/*coding AT command
 * Sample AT commands in link https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
 * try sending AT command through Serial. Sample below
 * 
 * AT
 * AT+RST
 * AT+GMR
 * AT+CWJAP?
 * AT+CWLAP
 * 
 * try changing the BAUD rate
 * double check the Port used:  - Tools -> Port: -> COMxxxx
 */
 
#include <SoftwareSerial.h>

const byte rxPin = 3;                               // Rx pin
const byte txPin = 2;                               // Tx pin

String ssid="new_frontiers";
String password="";

SoftwareSerial esp8266(rxPin,txPin);

void esp8266Reset(int t)
{
  esp8266.println("AT+RST");
  delay(t);
  if(esp8266.find(":"))
  {
    Serial.println("Reset Done!");
  } 
  else
  {
    Serial.println("RESET FAILED!");
  }
}

void esp8266ConnectToWiFi(String ssid, String password)
{
  String cmd = "AT+CWJAP=\"";
  cmd += ssid;
  cmd += "\",\"";
  cmd += password;
  cmd += "\"";
  esp8266.println(cmd);
  delay(5000);
  if (esp8266.find("OK"))
  {
    Serial.println("CONNECTED TO: \"" + ssid + "\" NETWORK\n");
  }
  else
  {
    Serial.println("DID NOT CONNECT TO WiFi NETWORK!!!");
  }
}

//void esp8266CheckWiFiStatus()
//{
//  String st="";
//  esp8266.println("AT+CWJAP?");
//  delay(100);  
//  if (esp8266.find("OK") || esp8266.find(":")) 
//  {    
//    Serial.print("CONNECTED TO WiFi NETWORK: ");
//    if(esp8266.find("OK") || esp8266.find(":")){
//      st = esp8266.readString();
//    }
//    Serial.println(st);
//  }
//  else
//  {    
//    Serial.println("NOT CONNECTED TO WiFi NETWORK");
//  }
//}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);  
  esp8266.begin(115200);  // set the data rate for the SoftwareSerial port
  while (!esp8266);
  Serial.println("Starting setup\n");
  Serial.print("Resetting esp module "); 
  esp8266Reset(5000);
  Serial.println("Connecting to: " + ssid);  
  esp8266ConnectToWiFi(ssid,password);
//  Serial.println("Checking WiFi status.... ");
//  esp8266CheckWiFiStatus();

  Serial.println("SETUP DONE");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (esp8266.available()) {
    Serial.write(esp8266.read());
  }
  if (Serial.available()) {
    esp8266.write(Serial.read());
  }

}
