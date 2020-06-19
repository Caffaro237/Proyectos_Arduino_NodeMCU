int led = 9;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  fade_in(led, 5000);
  fade_out(led, 5000);
  
  delay(10);
}


void fade_in(int pin, int tiempo)
{
  tiempo = tiempo / 256;
  
  for(int i = 0; i < 256; i++)
  {
    mostrar_tension(i);
    analogWrite(pin, i);
    delay(tiempo);
  }
}

void fade_out(int pin, int tiempo)
{
  tiempo = tiempo / 256;
  
  for(int i = 255; i >= 0; i--)
  {
    mostrar_tension(i);
    analogWrite(pin, i);
    delay(tiempo);
  }
}

void mostrar_tension(int i)
{
  float tension;
  
  Serial.print("Valor: ");
  Serial.print(i);
  Serial.print("  Tension: ");
  tension = i * .0195;
  Serial.print(tension);
  Serial.println("V");
}
