#include <ESP8266WiFi.h>

const char* ssid = "FT MARTU04";
const char* password = "01420289243";
IPAddress ip(192,168,1,60);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
int ledPin = 13; //Lo conectamos a D7
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(100);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  server.begin();
}

void loop()
{
  String request;
  int valor;
  WiFiClient client;
  
  client = server.available();
  if(!client)
  {
    return;
  }
  
  Serial.println("Nuevo Cliente");
  while(!client.available())
  {
    delay(10);
  }

  request = client.readStringUntil('\r');
  client.flush();

  valor = digitalRead(ledPin);
  
  if(request.indexOf("/LED=ON") != -1)
  {
    Serial.println("Encendido");
    digitalWrite(ledPin, HIGH);
    valor = HIGH;
  }
  if(request.indexOf("/LED=OFF") != -1)
  {
    Serial.println("Apagado");
    digitalWrite(ledPin, LOW);
    valor = LOW;
  }
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<head>");
  client.println("<title>");
  client.print("Luz Cuarto");
  client.print("</title>");
  client.println("</head>");

  client.println("<body bgcolor = #0000ff text = #ffffff>");
  client.println("<center>");
  client.println("<font face = Arial>");
  client.print("<h1>");
  client.print("La luz esta:");
  client.println("</h1>");
  client.println("</body>");
  
  
  if(valor == HIGH)
  {
    client.print("<h1>");
    client.print("ENCENDIDA");
    client.print("</h1>");
    client.println("<br>");
    client.println("<a href=\"/LED=OFF\"\"><button>Apagar</button></a>");
  }
  else
  {
    if(valor == LOW)
    {
      client.print("<h1>");
      client.print("APAGADA");
      client.print("</h1>");
      client.println("<br>");
      client.println("<a href=\"/LED=ON\"\"><button class=btn btn-primary btn-lg>Encender</button></a>");
    }
  }
  client.println("</font>");
  client.println("</center>");
  client.print("</html>");
  
  delay(10);
}
