/*
   Pushsafer.ino
   Pushsafer.com sketch by Appzer.de Kevin Siml 2018-07-04
   Send pushsafer.com messages from the arduino
*/

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE,0xAC,0xBF,0xEF,0xFE,0xAA};

// pushsafer settings
String privatekey = "your20characterPrivateKey";

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
  pushsafer("It works!!!","Test","1","1","1","#FF0000","https://www.pushsafer.com","Open Pushsafer","0","2","60","6000","1","a");  
  delay(60000); 
}

byte pushsafer(char *pushsafermessage, char *pushsafertitle, char *pssound, char *psvibration, char *psicon, char *pscolor, char *psurl, char *psurltitle, char *pstime2live, char *pspriority, char *psretry, char *psexpire, char *psconfirm, char *psanswer, char *psansweroptions, char *psanswerforce, char *psdevice)
{
  String title = pushsafertitle;
  String message = pushsafermessage;
  String device = psdevice;
  String sound = pssound;
  String vibration = psvibration;
  String icon = psicon;
  String color = pscolor;
  String url = psurl;
  String urltitle = psurltitle;
  String time2live = pstime2live;
  String priority = pspriority;
  String retry = psretry;
  String expire = psexpire;
  String confirm = psconfirm;
  String answer = psanswer;
  String answeroptions = psansweroptions;
  String answerforce = psanswerforce;

  length = 51 + message.length() + title.length() + sound.length() + vibration.length() + icon.length() + color.length() + url.length() + urltitle.length() + time2live.length() + retry.length() + expire.length() + confirm.length() + answer.length() + answeroptions.length() + answerforce.length() + device.length() + privatekey.length();

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
    client.print("&c=");
    client.print(color);
    client.print("&u=");
    client.print(url);
    client.print("&ut=");
    client.print(urltitle);
    client.print("&l=");
    client.print(time2live);
    client.print("&pr=");
    client.print(priority);
    client.print("&re=");
    client.print(retry);
    client.print("&ex=");
    client.print(expire);
    client.print("&cr=");
    client.print(confirm);     
    client.print("&a=");
    client.print(answer);
    client.print("&ao=");
    client.print(answeroptions);
    client.print("&af=");
    client.print(answerforce);
    client.print("&d=");
    client.print(device);

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
