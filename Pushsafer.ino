/*
   Pushsafer.com sketch by Appzer.de Kevin Siml 2016-08-08
   Send pushsafer.com messages from the arduino
*/

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE,0xAC,0xBF,0xEF,0xFE,0xAA};

// pushsafer settings
char privatekey[] = "your20characterPrivateKey";

int length;

EthernetClient client;

void setup()
{
  Serial.begin(9600);
  Serial.print(F("Starting ethernet..."));
  if(!Ethernet.begin(mac)) Serial.println("failed");
  else Serial.println(Ethernet.localIP());

  delay(5000);
  Serial.println("Ready");
}

void loop()
{
  pushsafer("It works!!!","Test",1,1,1,"a");  
  delay(60000); 
}

byte pushsafer(char *pushsafermessage, char *pushsafertitle, int sound, int vibration, int icon, char *psdevice)
{
  String title = pushsafertitle;
  String message = pushsafermessage;
  String device = psdevice;

  length = 41 + message.length() + title.length() + sound.length() + vibration.length() + icon.length() + device.length() + privatekey.length();

  if(client.connect("pushsafer.com",80))
  {
    client.println("POST /api HTTP/1.1");
    client.println("Host: https://www.pushsafer.com");
    client.println("Connection: close\r\nContent-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.print(length);
    client.println("\r\n");;
    client.print("k=");
    client.print(privatekey);
    client.print("&m=");
    client.print(message);
    client.print("&t=");
    client.print(title);	
    client.print("&s=");
    client.print(sound);
    client.print("&v=");
    client.print(vibration);	
    client.print("&i=");
    client.print(icon);
    client.print("&d=");
    client.print(device);	
    client.print("&retry=60");
    client.print("&expire=3600");
    while(client.connected())  
    {
      while(client.available())
      {
        char ch = client.read();
        Serial.write(ch);
      }
    }
    client.stop();
  }  
}
