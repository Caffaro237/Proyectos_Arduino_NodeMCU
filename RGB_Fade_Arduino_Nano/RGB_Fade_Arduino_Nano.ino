//Proyecto para NodeMCU y Aplicacion Blynk

//Salidas
int pin_rojo = 9;   //LED Rojo,   Pin D5
int pin_verde = 10;  //LED Verde, Pin D4
int pin_azul = 11;  //LED Azul,  Pin D3
int boton = 2;
int pote = A0;

//Arrays colores
int negro[3]  = { 0, 0, 0 };
int blanco[3]  = { 100, 100, 100 };
int rojo[3]    = { 100, 0, 0 };
int verde[3]  = { 0, 100, 0 };
int azul[3]   = { 0, 0, 100 };
int amarillo[3] = { 40, 95, 0 };
int dim_blanco[3] = { 30, 30, 30 };
int violeta[3] = { 60, 0, 100 };
int naranja[3] = { 100, 35, 0 };
int rosa[3] = { 100, 0, 40 };

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
int pin_color_fade = 2; //Pin D2
int color_fade = LOW;
int bandera_color_fade = 0;
int i = 0;

//Inicializacion de variables de colores
int prev_rojo = valor_rojo;
int prev_verde = valor_verde;
int prev_azul = valor_azul;

int estado_boton;
int estado_fade = 0;
int anti_estado_boton = 0;
int valor_pote;
int bandera_fade = 0;


void setup()
{
  pinMode(pin_rojo, OUTPUT);
  pinMode(pin_verde, OUTPUT);
  pinMode(pin_azul, OUTPUT);
  pinMode(pote, INPUT);

  Serial.begin(9600);
}

void loop()
{
  estado_fade = f_estado_fade(estado_fade);
  
  if(estado_fade)
  {
    //crossFade(white);
    cross_fade(azul);
    cross_fade(verde);
    cross_fade(rojo);
  }
  else
  {
    digitalWrite(pin_rojo, LOW);
    digitalWrite(pin_verde, LOW);
    digitalWrite(pin_azul, LOW);
  }
  
  delay(100);
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

int calcular_step(int valor_previo, int valor_final)
{
  int step = valor_final - valor_previo;

  if(step)
  {
    step = 1020 / step;
  }
  
  return step;
}

int calcular_valor(int step, int valor, int i)
{
  if((step) && i % step == 0)
  {
    if(step > 0)
    {
      valor = valor + 1;
    }
    else if(step < 0)
    {
      valor = valor - 1;
    }
  }

  if(valor > 255)
  {
    valor = 255;
  }
  else if(valor < 0)
  {
    valor = 0;
  }
  return valor;
}

void cross_fade(int color[3])
{
  // Conversor de 0 a 255
  int rojo = (color[0] * 255) / 100;
  int verde = (color[1] * 255) / 100;
  int azul = (color[2] * 255) / 100;

  int step_rojo = calcular_step(prev_rojo, rojo);
  int step_verde = calcular_step(prev_verde, verde);
  int step_azul = calcular_step(prev_azul, azul);

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
    
    valor_rojo = calcular_valor(step_rojo, valor_rojo, i);
    valor_verde = calcular_valor(step_verde, valor_verde, i);
    valor_azul = calcular_valor(step_azul, valor_azul, i);

    analogWrite(pin_rojo, valor_rojo);
    analogWrite(pin_verde, valor_verde);
    analogWrite(pin_azul, valor_azul);

    delay(wait);

    /*if(DEBUG)
    {
      if(i == 0 or i % contador_loop == 0)
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

      DEBUG = DEBUG + 1;
    }*/
  }

  prev_rojo = valor_rojo;
  prev_verde = valor_verde;
  prev_azul = valor_azul;

  delay(hold);
}
