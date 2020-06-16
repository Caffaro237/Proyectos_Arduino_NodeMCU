#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "e05b08f4e7e542a9b40b46b885948aa6";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "FT MARTU04";
char pass[] = "01420289243";
int pinLector = 5; // Pin D1
int lector = LOW;
int contador = 0;
int pinRojo = 14;
int pinAzul = 0;


void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(pinLector, INPUT);
  pinMode(pinAzul, OUTPUT);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,60), 80);

  
  
}

void loop()
{
  lector = digitalRead(pinLector);
  if(lector == 0)
  {
    if(contador == 1)
    {
      digitalWrite(pinAzul, LOW);
      contador = 0;
    }
    Serial.println("Apagado");
  }
  else
  {
    digitalWrite(pinAzul, HIGH);
    Serial.println("Prendido");
    contador = 1;
  }
  delay(10);
  Blynk.run();
}
