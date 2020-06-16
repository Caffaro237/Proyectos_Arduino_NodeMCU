/*#include <SoftwareSerial.h>
SoftwareSerial BT1(10, 11); // RX | TX

void setup()
  { pinMode(8, OUTPUT);        // Al poner en HIGH forzaremos el modo AT
    pinMode(9, OUTPUT);        // cuando se alimente de aqui
    digitalWrite(9, HIGH);
    delay (500) ;              // Espera antes de encender el modulo
    Serial.begin(115200);
    Serial.println("Levantando el modulo HC-05");
    digitalWrite (8, HIGH);    //Enciende el modulo
    Serial.println("Esperando comandos AT:");
    BT1.begin(38400);
  }
 
void loop()
  {  if (BT1.available())
           Serial.write(BT1.read());
     if (Serial.available())
        BT1.write(Serial.read());
  }*/


#include <SoftwareSerial.h>
SoftwareSerial BT1(10,11); // RX, TX recordar que se cruzan

void setup()
   {
       Serial.begin(9600);
       Serial.println("Enter AT commands:");
       BT1.begin(9600);
   }

void loop()
   {
       if (BT1.available())
           Serial.write(BT1.read());
       
       if (Serial.available())
          {  String S = GetLine();
             BT1.println(S); // Si no está respondiendo el Bluetooth quitar salto de linea osea, cambiar por BT1.print(S);
             Serial.println("---> " + S);
          }
}

String GetLine()
   {   String S = "" ;
       if (Serial.available())
          {    char c = Serial.read(); ;
                while (c != '\n')            //Hasta que el caracter sea intro
                  {     S = S + c ;
                        delay(25) ;
                        c = Serial.read();
                  }
                return( S ) ;
          }
   }
