//Proyecto para Arduino Nano

//Salidas
int led_rojo = 9;   //LED Rojo,   Pin D9
int led_verde = 10;  //LED Verde, Pin D10
int led_azul = 11;  //LED Azul,  Pin D11
 
void setup() 
{
  pinMode(led_rojo, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_azul, OUTPUT);
  
  Serial.begin(9600);      
}
 
void loop() 
{
  int numero_1 = random(0,256);
  int numero_2 = random(0,256);
  int numero_3 = random(0,256);
  
  analogWrite(led_rojo, numero_1);
  analogWrite(led_verde, numero_2);
  analogWrite(led_azul, numero_3);

  Serial.print("RGB: ");
  Serial.print(numero_1);
  Serial.print(" / ");
  Serial.print(numero_2);
  Serial.print(" / ");  
  Serial.println(numero_3); 
 
  delay(500);
}
