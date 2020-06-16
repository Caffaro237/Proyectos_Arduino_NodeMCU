// Outputs
int redPin = 14;   // LED Rojo,   Pin D5
int grnPin = 2;  // LED Verde, Pin D4
int bluPin = 0;  // LED Azul,  Pin D3

// Color arrays
int black[3]  = { 0, 0, 0 };
int white[3]  = { 100, 100, 100 };
int red[3]    = { 100, 0, 0 };
int green[3]  = { 0, 100, 0 };
int blue[3]   = { 0, 0, 100 };
int yellow[3] = { 40, 95, 0 };
int dimWhite[3] = { 30, 30, 30 };
// etc.

// Inicializacion de colores
int redVal = black[0];
int grnVal = black[1];
int bluVal = black[2];

int wait = 10;
int hold = 0;
int DEBUG = 1;
int loopCount = 60;
int repeat = 3;
int j = 0;

// Inicializacion de variables de colores
int prevR = redVal;
int prevG = grnVal;
int prevB = bluVal;

// Configuracion de salida
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);   
  pinMode(bluPin, OUTPUT); 

  if (DEBUG) 
  {
    Serial.begin(9600);
  }
}


void loop()
{
  crossFade(red);
  crossFade(green);
  crossFade(blue);
  crossFade(yellow);

  if (repeat) 
  {
    j += 1;
    if (j >= repeat) 
    {
      exit(j);
    }
  }
}

int calculateStep(int prevValue, int endValue) 
{
  int step = endValue - prevValue;
  if (step)
  {
    step = 1020/step;
  } 
  return step;
}


int calculateVal(int step, int val, int i) 
{
  if ((step) && i % step == 0) 
  {
    if (step > 0) 
    {
      val += 1;           
    } 
    else if (step < 0) 
    {
      val -= 1;
    } 
  }
  
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}


void crossFade(int color[3]) 
{
  // Conversor de 0 a 255
  int R = (color[0] * 255) / 100;
  int G = (color[1] * 255) / 100;
  int B = (color[2] * 255) / 100;

  int stepR = calculateStep(prevR, R);
  int stepG = calculateStep(prevG, G); 
  int stepB = calculateStep(prevB, B);

  for (int i = 0; i <= 1020; i++) 
  {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);

    analogWrite(redPin, redVal);
    analogWrite(grnPin, grnVal);
    analogWrite(bluPin, bluVal);

    delay(wait);

    if (DEBUG) 
    {
      if (i == 0 or i % loopCount == 0)
      {
        Serial.print("Loop/RGB: #");
        Serial.print(i);
        Serial.print(" | ");
        Serial.print(redVal);
        Serial.print(" / ");
        Serial.print(grnVal);
        Serial.print(" / ");  
        Serial.println(bluVal); 
      }
      DEBUG += 1;
    }
  }
  
  prevR = redVal; 
  prevG = grnVal; 
  prevB = bluVal;
  delay(hold);
}
