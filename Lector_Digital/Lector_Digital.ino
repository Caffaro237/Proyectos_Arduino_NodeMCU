int pin_led = 9;
int pin_lector = 6;

int lector = 0;
int lector_pote = 0;
int lector_transistor = 0;

void setup()
{
  pinMode(pin_led, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  lector_pote = analogRead(A4);
  lector_transistor = analogRead(A2);

  for(int i = 0; i < 255; i++)
  {
    lector_transistor = analogRead(A2);
    
    analogWrite(pin_led, i);
  
    Serial.print(" VALOR LED: ");
    Serial.print(i);
    
    /*Serial.print(" VALOR POTE: ");
    Serial.print(lector_pote);*/
    
    Serial.print(" VALOR LECTOR TRANSISTOR: ");
    Serial.println(lector_transistor);
    
    delay(50);
  }
  
  /*analogWrite(pin_led, lector_pote);
  
  Serial.print(" VALOR LED: ");
  Serial.print(lector_pote);
  
  Serial.print(" VALOR POTE: ");
  Serial.print(lector_pote);
  
  Serial.print(" VALOR LECTOR TRANSISTOR: ");
  Serial.println(lector_transistor);*/
  
  delay(200);
}
