//Proyecto hecho para Arduino Nano

// Incluimos librería
#include <DHT.h>
 
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 13

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int pin_ventilador_fuerte = 3;
int pin_ventilador_bajo = 4;
int pin_rojo = 11;
int pin_verde = 10;
int pin_azul = 9;

int temperatura_minima = 23;
int temperatura_maxima = 24;
int valor = 0;
int bandera_contador = 0;
int tiempo = 500;

void setup() 
{
  pinMode(pin_ventilador_fuerte, OUTPUT);
  pinMode(pin_ventilador_bajo, OUTPUT);
  pinMode(pin_rojo, OUTPUT);
  pinMode(pin_verde, OUTPUT);
  pinMode(pin_azul, OUTPUT);
  
  Serial.begin(9600);
  
  dht.begin();
}

void loop() 
{
  int h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
    delay(1000);
  }
  
  if(t >= temperatura_minima && t <= temperatura_maxima)
  {
    digitalWrite(pin_ventilador_fuerte, LOW);
    
    delay(tiempo);
    
    digitalWrite(pin_ventilador_bajo, HIGH);
    
    mostrar_valor(t);
    Serial.println("Prendido Bajo");
    
    analogWrite(pin_azul, valor);
  }
  else if(t >= temperatura_maxima)
  {
    digitalWrite(pin_ventilador_bajo, LOW);
   
    delay(tiempo);
    
    digitalWrite(pin_ventilador_fuerte, HIGH);

    mostrar_valor(t);
    Serial.println("Prendido Fuerte");
    
    analogWrite(pin_rojo, valor);
  }
  else
  {
    digitalWrite(pin_ventilador_bajo, LOW);
    digitalWrite(pin_ventilador_fuerte, LOW);

    //valor = fade_led(valor);

    mostrar_valor(t);
    Serial.println("Apagado");
    delay(tiempo);
    //Serial.println(valor);

    analogWrite(pin_verde, valor);
  }
  
  delay(10);
}

void mostrar_valor(float t)
{
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C - Ventilador ");
}
int fade_led(int valor)
{
  if(valor >= 0 && valor < 256 && !bandera_contador)
  {
    valor = valor + 1;
    
    if(valor == 255)
    {
      bandera_contador = 1;
    }
  }
  else
  {
    valor = valor - 1;

    if(!valor)
    {
      bandera_contador = 0;
    }
  }

  return valor;
}
