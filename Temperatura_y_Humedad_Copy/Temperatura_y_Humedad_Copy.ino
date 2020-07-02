//Proyecto hecho para Arduino Nano

#include "DHT.h"

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int a_1 = 2;
int b_1 = 3;
int c_1 = 4;
int d_1 = 5;
int e_1 = 6;
int f_1 = 7;
int g_1 = 8;

int a_2 = 9;
int b_2 = 10;
int c_2 = 12;
int d_2 = 11;
int e_2 = A0;
int f_2 = A1;
int g_2 = A2;
 
int d, u;//Unidad y decena del display1
int uu, dd;//Unidad y decena del display2
 
void setup() 
{
  Serial.begin(9600); 
  
  dht.begin();
}

void loop() 
{
  int t = dht.readTemperature();
  
  Serial.print("Temperatura: ");  //Se imprimen las variables
  Serial.println(t);  //Quitar comentarios si desea imprimir la temperatura
 
  int temp = analogRead(A4);
  temp = map(temp, 0, 1023, 28, 40);
  
  Serial.print("La temperatura de encendido del ventilador es: "); 
  Serial.println(temp);
  
  //Temperatura de encendido del ventilador
  //Con el este procedimiento logramos separar la temperatura de disparo
  
  u = temp % 10;//unidad
  d = (temp - u)/10;//decena
  display1(d);
  display2(u);// se muestran la unidad y decena en el respectivo display
  
  delay(1000);// luego de 3 segundos se muestran los datos registrados por el sensor
  
  //Temperatura registrada por el sensor
  //Se realiza el mismo procedimiento para separar la temperatura registrada por el sensor
  
  uu = t % 10;//unidad
  dd = (t - uu)/10;//decena
  display1(dd);
  display2(uu);//se muestran la unidad y decena en el respectivo display
 

  /*for(int i = 0; i < 10; i++)
  {
    display1(i);
    display2(i);

    delay(1000);
  }*/
  
  delay(100);
}

void display1(int d1) //Se establecen los parámetros para el display1
{
  switch(d1) //Utilizamos un switch para automatizar el proceso
  {
    case 0:
      digitalWrite(a_1, HIGH);
      digitalWrite(b_1, HIGH);
      digitalWrite(c_1, HIGH);
      digitalWrite(d_1, HIGH);
      digitalWrite(e_1, HIGH);
      digitalWrite(f_1, HIGH);
      digitalWrite(g_1, LOW);
      break;
   
    case 1:
      digitalWrite(a_1, LOW);
      digitalWrite(b_1, HIGH);
      digitalWrite(c_1, HIGH);
      digitalWrite(d_1, LOW);
      digitalWrite(e_1, LOW);
      digitalWrite(f_1, LOW);
      digitalWrite(g_1, LOW);
      break;
   
    case 2:
      digitalWrite(a_1, HIGH);
      digitalWrite(b_1, HIGH);
      digitalWrite(c_1, LOW);
      digitalWrite(d_1, HIGH);
      digitalWrite(e_1, HIGH);
      digitalWrite(f_1, LOW);
      digitalWrite(g_1, HIGH);
      break;
   
    case 3:
      digitalWrite(a_1, HIGH);
      digitalWrite(b_1, HIGH);
      digitalWrite(c_1, HIGH);
      digitalWrite(d_1, HIGH);
      digitalWrite(e_1, LOW);
      digitalWrite(f_1, LOW);
      digitalWrite(g_1, HIGH);
      break;
   
    case 4:
      digitalWrite(a_1, LOW);
      digitalWrite(b_1, HIGH);
      digitalWrite(c_1, HIGH);
      digitalWrite(d_1, LOW);
      digitalWrite(e_1, LOW);
      digitalWrite(f_1, HIGH);
      digitalWrite(g_1, HIGH);
      break;
   
    case 5:
      digitalWrite(a_1, HIGH);
      digitalWrite(b_1, LOW);
      digitalWrite(c_1, HIGH);
      digitalWrite(d_1, HIGH);
      digitalWrite(e_1, LOW);
      digitalWrite(f_1, HIGH);
      digitalWrite(g_1, HIGH);
      break;
   
    case 6:
      digitalWrite(a_1, HIGH);
      digitalWrite(b_1, LOW);
      digitalWrite(c_1, HIGH);
      digitalWrite(d_1, HIGH);
      digitalWrite(e_1, HIGH);
      digitalWrite(f_1, HIGH);
      digitalWrite(g_1, HIGH);
      break;
   
    case 7:
      digitalWrite(a_1, HIGH);
      digitalWrite(b_1, HIGH);
      digitalWrite(c_1, HIGH);
      digitalWrite(d_1, LOW);
      digitalWrite(e_1, LOW);
      digitalWrite(f_1, LOW);
      digitalWrite(g_1, LOW);
      break;
   
    case 8:
      digitalWrite(a_1, HIGH);
      digitalWrite(b_1, HIGH);
      digitalWrite(c_1, HIGH);
      digitalWrite(d_1, HIGH);
      digitalWrite(e_1, HIGH);
      digitalWrite(f_1, HIGH);
      digitalWrite(g_1, HIGH);
      break;
   
    case 9:
      digitalWrite(a_1, HIGH);
      digitalWrite(b_1, HIGH);
      digitalWrite(c_1, HIGH);
      digitalWrite(d_1, LOW);
      digitalWrite(e_1, LOW);
      digitalWrite(f_1, HIGH);
      digitalWrite(g_1, HIGH);
      break;
  }
}
 
void display2 (int d2) //Se establecen los parámetros para el display2
{
  switch(d2) //Utilizamos un switch para automatizar el proceso
  {
    case 0:
      digitalWrite(a_2, HIGH);
      digitalWrite(b_2, HIGH);
      digitalWrite(c_2, HIGH);
      digitalWrite(d_2, HIGH);
      analogWrite(e_2, 128);
      analogWrite(f_2, 128);
      analogWrite(g_2, 0);
      break;
   
    case 1:
      digitalWrite(a_2, LOW);
      digitalWrite(b_2, HIGH);
      digitalWrite(c_2, HIGH);
      digitalWrite(d_2, LOW);
      analogWrite(e_2, 0);
      analogWrite(f_2, 0);
      analogWrite(g_2, 0);
      break;
   
    case 2:
      digitalWrite(a_2, HIGH);
      digitalWrite(b_2, HIGH);
      digitalWrite(c_2, LOW);
      digitalWrite(d_2, HIGH);
      analogWrite(e_2, 128);
      analogWrite(f_2, 0);
      analogWrite(g_2, 128);
      break;
   
    case 3:
      digitalWrite(a_2, HIGH);
      digitalWrite(b_2, HIGH);
      digitalWrite(c_2, HIGH);
      digitalWrite(d_2, HIGH);
      analogWrite(e_2, 0);
      analogWrite(f_2, 0);
      analogWrite(g_2, 128);
      break;
   
    case 4:
      digitalWrite(a_2, LOW);
      digitalWrite(b_2, HIGH);
      digitalWrite(c_2, HIGH);
      digitalWrite(d_2, LOW);
      analogWrite(e_2, 0);
      analogWrite(f_2, 128);
      analogWrite(g_2, 128);
      break;
   
    case 5:
      digitalWrite(a_2, HIGH);
      digitalWrite(b_2, LOW);
      digitalWrite(c_2, HIGH);
      digitalWrite(d_2, HIGH);
      analogWrite(e_2, 0);
      analogWrite(f_2, 128);
      analogWrite(g_2, 128);
      break;
   
    case 6:
      digitalWrite(a_2, HIGH);
      digitalWrite(b_2, LOW);
      digitalWrite(c_2, HIGH);
      digitalWrite(d_2, HIGH);
      analogWrite(e_2, 128);
      analogWrite(f_2, 128);
      analogWrite(g_2, 128);
      break;
   
    case 7:
      digitalWrite(a_2, HIGH);
      digitalWrite(b_2, HIGH);
      digitalWrite(c_2, HIGH);
      digitalWrite(d_2, LOW);
      analogWrite(e_2, 0);
      analogWrite(f_2, 0);
      analogWrite(g_2, 0);
      break;
   
    case 8:
      digitalWrite(a_2, HIGH);
      digitalWrite(b_2, HIGH);
      digitalWrite(c_2, HIGH);
      digitalWrite(d_2, HIGH);
      analogWrite(e_2, 128);
      analogWrite(f_2, 128);
      analogWrite(g_2, 128);
      break;
   
    case 9:
      digitalWrite(a_2, HIGH);
      digitalWrite(b_2, HIGH);
      digitalWrite(c_2, HIGH);
      digitalWrite(d_2, LOW);
      analogWrite(e_2, 0);
      analogWrite(f_2, 128);
      analogWrite(g_2, 128);
      break;
  }
}
