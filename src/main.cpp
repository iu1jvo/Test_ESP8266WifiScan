#include <Arduino.h>
#include "ESP8266WiFi.h"

#define LED_PIN 2

bool ScanComplete = false;
int numWifiFound = 0;

void Complete(int par) 
{
  ScanComplete = true;
  numWifiFound = par;

}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,LOW);
  
}

void loop() 
{
  static int step = 0;
  // put your main code here, to run repeatedly:

  switch (step)  
  {
    case 0:
      Serial.print("Scanning networks");
      WiFi.scanNetworksAsync(Complete);
      step++;
      break;

    case 1:
      while (!ScanComplete) 
      {
        /* code */
        delay(250);
        digitalWrite(LED_PIN,HIGH);
        Serial.print(".");
        delay(250);
        digitalWrite(LED_PIN,LOW);
        Serial.print(".");
      }
      Serial.println();

      if (numWifiFound != 0) 
      {
        Serial.printf("%d network(s) found\n", numWifiFound);
        for (int i = 0; i < numWifiFound; i++)
        {
          Serial.printf("%d: %s, Ch:%d (%ddBm) %s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "");
        }      
      }
      else
      {
        Serial.println("No WiFi found");
      }
      step++;
      
      break;

    case 2:
      digitalWrite(LED_PIN,LOW);
      delay(2000);
      digitalWrite(LED_PIN,HIGH);
      delay(2000);
      break;

    default:
      break;
  }

  

}