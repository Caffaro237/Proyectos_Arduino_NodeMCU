#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Codigo de autenticacion de BLynk
char auth[] = "e05b08f4e7e542a9b40b46b885948aa6";

//Configuracion Wifi
char ssid[] = "FT MARTU04";
char pass[] = "01420289243";

//Salidas
int pin_rojo = 14;   // LED Rojo,   Pin D5
int pin_verde = 2;  // LED Verde, Pin D4
int pin_azul = 0;  // LED Azul,  Pin D3
inr pin_inicio = 

//Arrays colores
int negro[3]  = { 0, 0, 0 };
int blanco[3]  = { 100, 100, 100 };
int rojo[3]    = { 100, 0, 0 };
int verde[3]  = { 0, 100, 0 };
int azul[3]   = { 0, 0, 100 };
int amarillo[3] = { 40, 95, 0 };
int dim_blanco[3] = { 30, 30, 30 };

//Inicializacion de colores
int valor_rojo = negro[0];
int valor_verde = negro[1];
int valor_azul = negro[2];

int wait = 10;
int hold = 0;
int DEBUG = 1;
int contador_loop = 60;
int repetir = 999999999;
int j = 0;

//Variables extras
int pin_lector = 5; // Pin D1
int lector = LOW;
int contador = 0;

//Inicializacion de variables de colores
int prev_rojo = valor_rojo;
int prev_verde = valor_verde;
int prev_azul = valor_azul;


void setup()
{
  pinMode(pin_lector, INPUT);
  pinMode(pin_rojo, OUTPUT);
  pinMode(pin_verde, OUTPUT);
  pinMode(pin_azul, OUTPUT);

  if(DEBUG)
  {
    Serial.begin(9600);
  }


  Blynk.begin(auth, ssid, pass);
  //Se puede especificar un servidor
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,60), 80);
}

void loop()
{
  lector = digitalRead(pin_lector);

  if(!lector)
  {
    if(contador)
    {
      digitalWrite(pin_rojo, LOW);
      digitalWrite(pin_verde, LOW);
      digitalWrite(pin_azul, LOW);

      contador = 0;

      Serial.println("Apagado");
    }
  }
  else
  {
    crossFade(rojo);
    crossFade(verde);
    crossFade(azul);
    crossFade(amarillo);

    if (repetir)
    {
      j += 1;
      Serial.println(j);
      if (j >= repetir)
      {
        contador = 1;
        exit(j);
      }
    }

    Serial.println("Prendido");

    contador = 1;
  }

  delay(10);

  Blynk.run();
}

int calculateStep(int valor_previo, int valor_final)
{
  int step = valor_final - valor_previo;

  if (step)
  {
    step = 1020/step;
  }
  return step;
}


int calculateVal(int step, int valor, int i)
{
  if ((step) && i % step == 0)
  {
    if (step > 0)
    {
      valor += 1;
    }
    else if (step < 0)
    {
      valor -= 1;
    }
  }

  if (valor > 255)
  {
    valor = 255;
  }
  else if (valor < 0)
  {
    valor = 0;
  }
  return valor;
}

void crossFade(int color[3])
{
  // Conversor de 0 a 255
  int rojo = (color[0] * 255) / 100;
  int verde = (color[1] * 255) / 100;
  int azul = (color[2] * 255) / 100;

  int step_rojo = calculateStep(prev_rojo, rojo);
  int step_verde = calculateStep(prev_verde, verde);
  int step_azul = calculateStep(prev_azul, azul);

  for (int i = 0; i <= 1020; i++)
  {
    valor_rojo = calculateVal(step_rojo, valor_rojo, i);
    valor_verde = calculateVal(step_verde, valor_verde, i);
    valor_azul = calculateVal(step_azul, valor_azul, i);

    analogWrite(pin_rojo, valor_rojo);
    analogWrite(pin_verde, valor_verde);
    analogWrite(pin_azul, valor_azul);

    delay(wait);

    if (DEBUG)
    {
      lector = digitalRead(pin_lector);

      Blynk.run();

      if (!lector)
      {
        exit(j);
      }

      if (i == 0 or i % contador_loop == 0)
      {
        Serial.print("Loop/RGB: #");
        Serial.print(i);
        Serial.print(" | ");
        Serial.print(valor_rojo);
        Serial.print(" / ");
        Serial.print(valor_verde);
        Serial.print(" / ");
        Serial.println(valor_azul);
      }

      DEBUG += 1;
    }
  }

  prev_rojo = valor_rojo;
  prev_verde = valor_verde;
  prev_azul = valor_azul;

  delay(hold);
}
