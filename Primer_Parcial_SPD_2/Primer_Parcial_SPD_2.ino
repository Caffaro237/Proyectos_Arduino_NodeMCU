#define CANT 3

int leds[CANT] = {4, 5, 6};
int pull_up = 7;

int estado_pull_up;
int estado_anterior_pull_up = 0;

int i = 0;

void setup() 
{
  Serial.begin(9600);
  
  for(i; i < CANT; i++)
  {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(estado_pull_up, INPUT);

  i = 0;
}

void loop() 
{
  estado_pull_up = digitalRead(pull_up);

  if(estado_pull_up != estado_anterior_pull_up)
  {
    if(!estado_pull_up)
    {
      digitalWrite(leds[i], HIGH);
      digitalWrite(leds[i - 1], LOW);
      i = i + 1;
    }
    
    if(i == 4)
    {
      i = 0;
    }
    
    estado_anterior_pull_up = estado_pull_up;
  }
  delay(10);
}
