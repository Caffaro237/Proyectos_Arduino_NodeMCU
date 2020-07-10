#define PULSADOR 7

#define LED_R 4
#define LED_A 5
#define LED_V 6
#define CANT 4

int leds[CANT]={4, 5, 6};
int i = 0;

int estado_pulsador;
int estado_anterior_pulsador;

void setup()
{
  Serial.begin(9600);
  
  //Setea en salida a los leds
  pinMode(LED_V, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_R, OUTPUT);
  
  //Setea en entrada al boton
  pinMode(PULSADOR, INPUT);
  
}

void loop()
{
  estado_pulsador = digitalRead(PULSADOR);
  
  if(estado_pulsador != estado_anterior_pulsador) //Antirebote
  {
    if (estado_pulsador == LOW) //Entra si precionan el boton
    {
      switch(i) //Dependiendo en que posicion del array este, entra la opcion
      {
        case 0:
          digitalWrite(leds[i], HIGH);
            digitalWrite(leds[i + 1], LOW);
            digitalWrite(leds[i + 2], LOW);
            i++;
        
          Serial.println("VERDE");
        
            break;
        
        case 1:
          digitalWrite(leds[i], HIGH);
            digitalWrite(leds[i - 1], LOW);
            digitalWrite(leds[i + 1], LOW);
            i++;
        
          Serial.println("AMARILLO");
        
            break;
        
        case 2:
          digitalWrite(leds[i], HIGH);
            digitalWrite(leds[i - 1], LOW);
            digitalWrite(leds[i - 2], LOW);
            i++;
        
          Serial.println("ROJO");
        
            break;
        
        case 3:
          digitalWrite(leds[i], LOW);
            digitalWrite(leds[i - 1], LOW);
            digitalWrite(leds[i - 2], LOW);
            i = 0;
        
          Serial.println("APAGADO");
        
            break;
      }
    }
    
    estado_anterior_pulsador = estado_pulsador; //Antirebote
  }
  
  delay(10);
}
