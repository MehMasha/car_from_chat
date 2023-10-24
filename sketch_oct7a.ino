#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
 
Servo servo;

// Replace with your network credentials
const char* ssid = "Giga";         
const char* password = "govnozalupa";
// const int RS = 4, EN = 0, d4 = 12 , d5 = 13, d6 = 15, d7 = 3;

// LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "<head><meta http-equiv=\"refresh\" content=\"0.5\" /></head>"; //For the Web Server
String page2="";  //For updating Status of motor 1
String page3="";  //For updating status of motor 2
String page4="";
int buzz = 0;
unsigned long prevMillis = 0;
void setup(void)
{
  // lcd.print("hello, world!");
  // lcd.setCursor(0, 1);
  // lcd.print("text3");
  //the HTML of the web page
  page = page + "<center><h1>Motor Control Web Server</h1><body><p><a href=\"Forward\"><button>Forward</button></a><p><a href=\"Backward\"><button>Backward</button></a></p><p><a href =\"Left\"><button>Left</button></a>&nbsp;<a href=\"Stop\"><button>Stop</button></a><a href=\"Right\"><button>Right</button></a></p></body></center>";
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);   // inputs for motor 1
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);    // inputs for motor 2 
  pinMode(D8,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);  // For status of WiFi connection
  delay(1000);
  Serial.begin(9600);     
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN,HIGH);     // when connected turns high
  Serial.println("");
  Serial.print("Connected to ");   
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());   //provides IP address
  server.on("/", [](){
    server.send(200, "text/html", page+page2+page3+page4);
  });
  server.on("/Forward", Forward);
  server.on("/Backward", Backward);
  server.on("/Left", Left);
  server.on("/Right", Right);
  server.on("/Buzz", Buzz);
  // server.on("/BlinkLeftOn", BlinkLeftOn);
  // server.on("/BlinkLeftOff", BlinkLeftOff);
  // server.on("/BlinkRightOn", BlinkRightOn);
  // server.on("/BlinkRightOff", BlinkRightOff);
  server.on("/Turn", Turn);
  server.on("/Buzz", Buzz);

  server.on("/Stop",[](){                              // turns all the motor input pins low
   page2="<center><p> motor 1 Status : Off</p></center>";
   page3="<center><p> motor 2 Status : off</p></center>";
  server.send(200,"text/html",page+page2+page3+page4);
    digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
    digitalWrite(D7,LOW);
    digitalWrite(D8,LOW);
    delay(200);
  });
  server.begin();
  Serial.println("Web server started!");
  // lcd.begin(16, 2);
  servo.attach(D1);
  servo.write(0);
}
void loop(void)
{  
    server.handleClient();

    // if (buzz == 1){
    //   unsigned long currentMillis = millis();
    //   if (currentMillis - prevMillis > 500) {
    //     noTone(D4);
    //     buzz = 0;
    //   } 
    // }

}

  void Turn()
  {
    servo.write(server.arg(0).toInt());
    server.send(200,"text/html", page+page2+page3+page4);
    
  }



  void BlinkLeftOn()
  {
    digitalWrite(D3,HIGH);
    server.send(200,"text/html", page+page2+page3+page4);
    
  }
  void BlinkLeftOff()
  {
    digitalWrite(D3,LOW);
    server.send(200,"text/html", page+page2+page3+page4);
    
  }

  void BlinkRightOn()
  {
    digitalWrite(D2,HIGH);
    server.send(200,"text/html", page+page2+page3+page4);
    
  }
  void BlinkRightOff()
  {
    digitalWrite(D2,LOW);
    server.send(200,"text/html", page+page2+page3+page4);
    
  }

  void Stop() 
  {
    digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
    digitalWrite(D7,LOW);
    digitalWrite(D8,LOW);
    server.send(200,"text/html", page+page2+page3+page4);
    
  }

 void Forward() 
 {
    digitalWrite(D5,HIGH);
    digitalWrite(D6,LOW);
    digitalWrite(D7,HIGH);
    digitalWrite(D8,LOW);
    page2="<center><p> motor 1 Status : Forward </p></center>";
    page4="<center><p>Moving forward by " + server.arg(0) + " </p></center>";
    server.send(200,"text/html", page+page2+page3+page4);
    delay(100);
    Stop();
  }

  void Buzz()
  {
      prevMillis = millis();
      buzz = 1;
      tone(D4, 500);
  }

  void Left()
  {
    page3="<center><p> motor 2 Status : Left</p></center>";
        page4="<center><p>Moving left by " + server.arg(0) + " </p></center>";
    server.send(200,"text/html",page+page2+page3+page4);
    digitalWrite(D7,HIGH);
    digitalWrite(D8,LOW);
    digitalWrite(D6,HIGH);
    digitalWrite(D5,LOW);
    delay(80);
    Stop();
  }
  void Right()
   { 
    page3="<center><p> motor 2 Status : Right</p></center>";
        page4="<center><p>Moving right by " + server.arg(0) + " </p></center>";
    server.send(200,"text/html",page+page2+page3+page4);
    digitalWrite(D8,HIGH);
    digitalWrite(D7,LOW);
    digitalWrite(D5,HIGH);
    digitalWrite(D6,LOW);
    delay(80);
    Stop();
  }
   void Backward()
  {
    page2="<center><p> motor 1 Status : Backward</p></center>";
        page4="<center><p>Moving backward by " + server.arg(0) + " </p></center>";
    server.send(200, "text/html", page+page2+page3+page4);
    digitalWrite(D6, HIGH);
    digitalWrite(D5,LOW);
    digitalWrite(D8, HIGH);
    digitalWrite(D7,LOW);
    // lcd.setCursor(0, 1);
    //   // lcd.print(server.arg(0));
    //   // lcd.print(server.arg(0).c_str());
    // lcd.clear();
    // lcd.print(server.arg(0));
    delay(100); 
    Stop();
  }

  // void Name()
  // {

  //     lcd.setCursor(0, 1);
  //     // lcd.print(server.arg(0));
  //     // lcd.print(server.arg(0).c_str());
  //     lcd.clear();
  //     lcd.print(server.arg(0));
  //     Serial.print(server.arg(0));

  //     server.send(200, "text/plain", "eee");
  // }