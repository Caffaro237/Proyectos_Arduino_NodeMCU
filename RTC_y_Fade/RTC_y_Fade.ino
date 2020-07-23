#include <Wire.h> 
#include "RTClib.h"

#define CANT 6

RTC_DS1307 RTC;

int r_diaSemana;

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

int hh_mm_ss[CANT][3] = {{17, 31, 0}, 
                         {17, 31, 30}, 
                         {17, 32, 0}, 
                         {99, 0, 0}, 
                         {99, 0, 0},
                         {99, 0, 0}};

// Outputs
int redPin = 11;   // LED Rojo,   Pin D5
int grnPin = 10;  // LED Verde, Pin D4
int bluPin = 9;  // LED Azul,  Pin D3
int boton = 2;
int pote = A0;

// Color arrays
int black[3]  = { 0, 0, 0 };
int white[3]  = { 100, 100, 100 };
int red[3]    = { 100, 0, 0 };
int green[3]  = { 0, 100, 0 };
int blue[3]   = { 0, 0, 100 };
int yellow[3] = { 40, 95, 0 };
int dimWhite[3] = { 30, 30, 30 };
int violeta[3] = { 60, 0, 100 };
// etc.

// Inicializacion de colores
int redVal = black[0];
int grnVal = black[1];
int bluVal = black[2];

int wait = 1;
int hold = 0;
int DEBUG = 1;
int loopCount = 60;
int repeat = 3;
int l = 0;

int estado_boton;
int estado_fade = 0;
int anti_estado_boton = 0;
int valor_pote;
int bandera_fade = 0;

// Inicializacion de variables de colores
int prevR = redVal;
int prevG = grnVal;
int prevB = bluVal;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  pinMode(boton, INPUT);
  pinMode(pote, INPUT);

  Wire.begin();                               
  RTC.begin();                                // Inicia la comunicaci¢n con el RTC
   
  //RTC.adjust(DateTime(__DATE__, __TIME__)); // Lee la fecha y hora del PC (Solo en la primera carga)
                                               // el anterior se usa solo en la configuracion inicial luego se pone como comentario
                                               // y se vuelve a cargar el programa sin esa linea.
  Serial.begin(9600);                         // Establece la velocidad de datos del puerto serie a 9600
   
}

void loop()
{
  estado_fade = f_estado_fade(estado_fade);
  
  if(estado_fade)
  {
    //crossFade(white);
    crossFade(blue);
    crossFade(green);
    crossFade(red);
  }
  else
  {
    if(bandera_fade)
    {
      digitalWrite(redPin, LOW);
      digitalWrite(grnPin, LOW);
      digitalWrite(bluPin, LOW);

      bandera_fade = 0;
    }
  }
  
  r_diaSemana = dia_de_semana();   //Llama a la funcion que calcula el dia de la semana y lo almacena en r_diaSemana
  
  horario();
  
  delay(50);                    // La informacion se actualiza cada 1/2 seg.
}

int f_estado_fade(int estado_fade)
{
  estado_boton = digitalRead(boton);

  if(estado_boton != anti_estado_boton)
  {
    if(estado_boton)
    {
      delay(300);
      
      estado_fade = !estado_fade;
      
      Serial.println(estado_fade);
    }
    
    anti_estado_boton = estado_boton;
  }

  return estado_fade;
}

int calculateStep(int prevValue, int endValue) 
{
  int step = endValue - prevValue;
  if (step)
  {
    step = 1020/step;
  } 
  return step;
}


int calculateVal(int step, int val, int i) 
{
  if ((step) && i % step == 0) 
  {
    if (step > 0) 
    {
      val += 1;           
    } 
    else if (step < 0) 
    {
      val -= 1;
    } 
  }
  
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}


void crossFade(int color[3]) 
{
  // Conversor de 0 a 255
  int R = (color[0] * 255) / 100;
  int G = (color[1] * 255) / 100;
  int B = (color[2] * 255) / 100;

  int stepR = calculateStep(prevR, R);
  int stepG = calculateStep(prevG, G); 
  int stepB = calculateStep(prevB, B);

  for (int i = 0; i <= 1020; i++) 
  {
    estado_fade = f_estado_fade(estado_fade);

    valor_pote = analogRead(pote);

    wait = map(valor_pote, 0, 1023, 0, 10);

    bandera_fade = 1;
    
    if(!estado_fade)
    {
      break;
    }

    horario();
    
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);

    analogWrite(redPin, redVal);
    analogWrite(grnPin, grnVal);
    analogWrite(bluPin, bluVal);

    delay(wait);

    /*if (DEBUG) 
    {
      if (i == 0 or i % loopCount == 0)
      {
        Serial.print("Loop/RGB: #");
        Serial.print(i);
        Serial.print(" | ");
        Serial.print(redVal);
        Serial.print(" / ");
        Serial.print(grnVal);
        Serial.print(" / ");  
        Serial.print(bluVal); 
        Serial.print(" - Valor wait: "); 
        Serial.println(wait); 
      }
      DEBUG += 1;
    }*/
  }
  
  prevR = redVal; 
  prevG = grnVal; 
  prevB = bluVal;
  delay(hold);
}


void activar_led(int intensidad)
{
  for(l; l < intensidad; l++)
  {
    if(l > 255)
    {
      bandera = 1;
      l = 255;
      break;
    }
    
    analogWrite(redPin , l);
    analogWrite(grnPin , l);
    analogWrite(bluPin , l);
    delay(100);
  }

  if(!bandera)
  {
    j = intensidad;
  }
  
  Serial.print("LED Activo a una intensidad de: ");
  Serial.println(l);
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
    titilar(redPin, grnPin, bluPin, 5);
    bandera = 0;
    l = 0;
    intensidad_led = 0;
  }
}

void titilar(int rojo, int verde, int azul, int veces)
{
  for(int i = 0; i < veces; i++)
  {
    digitalWrite(rojo, HIGH);
    digitalWrite(verde, HIGH);
    digitalWrite(azul, HIGH);
    delay(tiempo);
    digitalWrite(rojo, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(azul, LOW);
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
