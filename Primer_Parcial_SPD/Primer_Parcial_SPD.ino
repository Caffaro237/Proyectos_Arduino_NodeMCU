#define CANT 5

int leds[CANT]={2, 3, 4, 5, 6};
int pull_up = 7;
int pull_down = 8;

int estado_pull_up;
int estado_pull_down;

int estado_anterior_pull_up;
int estado_anterior_pull_down;

int i;
int j = 2; //Funciona como un contador
int flag = 0;

void setup()
{
  pinMode(pull_up, INPUT);
  pinMode(pull_down, INPUT);
  
  for(i = 0; i < CANT; i++) 
  {
    pinMode(leds[i], OUTPUT); 
  }
}

void loop()
{
  if(flag == 0)
  {
    digitalWrite(leds[j], HIGH);
    flag = 1;
  }
  
  boton_down();
  boton_up();
 
  delay(10);
}

void boton_up()
{
  estado_pull_up = digitalRead(pull_up);

  if(estado_pull_up != estado_anterior_pull_up)
  {
    if (estado_pull_up == LOW)//pullUp lee low cuando lo presionaron
    {
      if(j == 0)
      {
        digitalWrite(leds[j], LOW);
        delay(100);
        digitalWrite(leds[j], HIGH);
      }
      else 
      {
        digitalWrite(leds[j], LOW);
        j = j - 1;
        digitalWrite(leds[j], HIGH);
      }     
    }
  }
  
  estado_anterior_pull_up = estado_pull_up;
}

void boton_down()
{
  estado_pull_down=digitalRead(pull_down);
  
  if(estado_pull_down != estado_anterior_pull_down)
  {
    if (estado_pull_down == HIGH)//pull_down lee high cuando lo presionaron
    {
      if(j == 4)
      {
        digitalWrite(leds[j], LOW);
        delay(100);
        digitalWrite(leds[j], HIGH);
      }
      else
      {
        digitalWrite(leds[j], LOW);
        j = j + 1;
        digitalWrite(leds[j], HIGH);
      }
    }
    
    estado_anterior_pull_down = estado_pull_down;
  }
}
