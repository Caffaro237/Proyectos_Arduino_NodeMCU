//Proyecto realizado en Arduino Nano

/*
 * Prueba de Reloj Tiempo Real (RTC) y Modulo I2C para LCD 2x16 By: http://dinastiatecnologica.com
 * Conexion i2C :Arduino UNO  SCL-> A5   SDA->A4  VCC->5V  GND->GND
 * Conexion RTC :Arduino UNO    GND->GND VCC->5V SCL-> SCL  SDA->SDA los dos pines despues del ...12,13,GND,AREF,SDA,SCL
 * NOTA: se debe cargar dos veces este programa 1. Con la linea 9 = RTC.adjust(DateTime(__DATE__, __TIME__));
 *                                              2. Con la linea 9 Comentada = //RTC.adjust(DateTime(__DATE__, __TIME__));
*/

#include <Wire.h> 
#include "RTClib.h"

#define CANT 6

RTC_DS1307 RTC;

int r_diaSemana;
int led = 9;

int anio;
int mes;
int dia;
int hora;
int minuto;
int segundo;

int tiempo = 500;
int intensidad_led = 0;
int bandera = 0;
int j = 0;

//////////////////////////////// Horario 1 /////////////////////////
// Hora en la que suena el timbre escrito  h1=Hora, m1=Minutos
// Cuando no se programa ninguna hora se debe dejar escrito el numero 99

int hh_mm_ss[CANT][3] = {{2, 20, 0}, 
                         {99, 0, 0}, 
                         {99, 0, 0}, 
                         {99, 0, 0}, 
                         {99, 0, 0},
                         {99, 0, 0}};

////////////////////////////////// Void Setup() ///////////
void setup () 
{
  pinMode(led, OUTPUT);                    // Configura como salida el pin 7
   
  Wire.begin();                               
  RTC.begin();                                // Inicia la comunicaci¢n con el RTC
   
  //RTC.adjust(DateTime(__DATE__, __TIME__)); // Lee la fecha y hora del PC (Solo en la primera carga)
                                               // el anterior se usa solo en la configuracion inicial luego se pone como comentario
                                               // y se vuelve a cargar el programa sin esa linea.
  Serial.begin(9600);                         // Establece la velocidad de datos del puerto serie a 9600
   
}

////////////////////////////////// Void loop() ///////////
void loop()
{
  r_diaSemana = dia_de_semana();   //Llama a la funcion que calcula el dia de la semana y lo almacena en r_diaSemana
  
  horario();           // llama a la funcion que activa el horario 1
   
  //digitalWrite(led, LOW);     // apaga el timbre
  delay(1000);                    // La informacion se actualiza cada 1/2 seg.
}

//Funcion que activa el Timbre
void activar_led(int intensidad)
{
  for(j; j < intensidad; j++)
  {
    if(j > 255)
    {
      bandera = 1;
      j = 255;
      break;
    }
    
    analogWrite(led, j);
    delay(100);
  }

  if(!bandera)
  {
    j = intensidad;
  }
  
  Serial.print("LED Activo a una intensidad de: ");
  Serial.println(j);
}

//Calcula el dia de la Semana
int dia_de_semana()
{
  //Encuentar el dia de la semana de una fecha
  int n_dia;
  int r_dia;
  int n_mes;
  int t_mes;
  int n_anno;
  int d_anno;
  int t_siglo = 6;
  
  DateTime now = RTC.now(); //fecha y hora del RTC
  
  n_anno = (now.year() - 2000);
  d_anno = n_anno / 4;
  n_dia = now.day();
  n_mes = now.month();
  
  switch(n_mes) 
  {
    case 1:
      t_mes = 0;
      break;
        
    case 2:
      t_mes = 3;
      break;
        
    case 3:
      t_mes = 3;
      break;
        
    case 4:
      t_mes = 6;
      break;
        
    case 5:
      t_mes = 1;
      break;
        
    case 6:
      t_mes = 4;
      break;
        
    case 7:
      t_mes = 6;
      break;
        
    case 8:
      t_mes = 2;
      break;
        
    case 9:
      t_mes = 5;
      break;
        
    case 10:
      t_mes = 0;
      break;
        
    case 11:
      t_mes = 3;
      break;
        
    case 12:
      t_mes = 5;
      break;
        
    default: 
      t_mes = t_mes;
      break;
  }
  
  r_dia = n_dia + t_mes + n_anno + d_anno + t_siglo;
  r_dia = r_dia % 7;
  
  switch (r_dia) 
  {
    case 1:
      Serial.print("Lunes ");
      break;
        
    case 2:
      Serial.print("Martes ");
       break;
        
    case 3:
      Serial.print("Miecoles ");
      break;
        
    case 4:
      Serial.print("Jueves ");
      break;
        
    case 5:
      Serial.print("Viernes ");
      break;
        
    case 6:
      Serial.print("Sabado ");
      break;
        
    case 0:
      Serial.print("Domimgo ");
      break;
        
    default:
      Serial.print("");
      break;
  }
  
  anio = now.year();
  mes = now.month();
  dia = now.day();
  hora = now.hour();
  minuto = now.minute();
  segundo = now.second();
  
  informar_fecha_hora(anio, mes, dia, hora, minuto, segundo);
   
  return r_dia; 
}

/////////////////////Condicional del Horario 1  //////////////////////////////////
void horario()
{
  for(int i = 0; i < CANT; i++)
  {
    if((hora == hh_mm_ss[i][0]) && (minuto == hh_mm_ss[i][1]) && (segundo == hh_mm_ss[i][2]))
    {
      intensidad_led = intensidad_led + 100;
      activar_led(intensidad_led);
    }
  }
  
  if(bandera)
  {
    bandera = 0;
    j = 0;
    intensidad_led = 0;
  }
}

void titilar(int pin, int veces)
{
  for(int i = 0; i < veces; i++)
  {
    digitalWrite(pin, HIGH);
    delay(tiempo);
    digitalWrite(pin, LOW);
    delay(tiempo);
  }
}

void informar_fecha_hora(int aa, int mm, int dd, int h, int m, int s)
{
  Serial.print(aa, DEC);  //Año
  Serial.print('/');
  Serial.print(mm, DEC); //Mes
  Serial.print('/');
  Serial.print(dd, DEC);   //Dia
  Serial.print(' ');
  Serial.print(h, DEC);  //Horas
  Serial.print(':');
  Serial.print(m, DEC); //Minutos
  Serial.print(':');
  Serial.println(s, DEC); //Segundos
}
