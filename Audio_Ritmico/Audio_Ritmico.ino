//Proyecto para Arduino NANO

int mic = 13; //Pin D10
int led = 2; //Pin D12
int tiempo = 100;
int lector_mic = LOW;

void setup()
{
  pinMode(mic, INPUT);
  pinMode(led, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  lector_mic = digitalRead(mic);
  
  if(lector_mic)
  {
    digitalWrite(led, HIGH);
    delay(tiempo);
  }
  else
  {
    digitalWrite(led, LOW);
    delay(tiempo);
  }
  
  
}
