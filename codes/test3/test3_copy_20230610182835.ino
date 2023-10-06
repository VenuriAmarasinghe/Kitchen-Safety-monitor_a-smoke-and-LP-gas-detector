/*#include <WiFi.h>
/*#include "wifi_save.h"
#include <HTTPClient.h>
#include <UrlEncode.h>*/

//const char* ssid ="Jackfrost";
//const char* password = "Venuri123";

// +international_country_code + phone number
// Portugal +351, example: +351912345678
//String phoneNumber = "+94710475232";
//String apiKey = "3574812";
int cam_en=5;
int Buzzer = 32;        // used for ESP32
int Gas_analog = 34;    // used for ESP32
int Gas_6=33;   // used for ESP32
int message_sent=0;
int led=15;
int countsmoke=0;
int countno=0;
int count_cam=0;
//int error=0;

/*WiFiClient client;

void sendMessage(String message){
  //int error=0;
  WiFiClient client;
  if (!client.connect("api.callmebot.com", 80)) {
    Serial.println("Connection failed");
    return;
  }

  // Data to send with HTTP POST
  String url = "/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: api.callmebot.com\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: " + url.length() + "\r\n" +
               "Connection: close\r\n\r\n" +
               url);
  
  // Wait for response
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  
  // Read the response
  String response = "";
  while(client.available()) {
    response += (char)client.read();
  }

  // Check if message was sent successfully
  if (response.indexOf("Message sent successfully") != -1){
    Serial.println("Message sent successfully");
  }
  else{
    //error=1;
    Serial.println("Error sending the message");
    Serial.print("HTTP response: ");
    Serial.println(response);
  }
  return;
}


void connect_wifi(){
  
    if (wifi_set_main())
    {
        Serial.println("Connect WIFI SUCCESS");
    }
    else
    {
        Serial.println("Connect WIFI FAULT");
    }
  sendMessage("Hi venuri, from smoke detector pcb test");
  Serial.println(WiFi.localIP());
}*/

void setup() {
  Serial.begin(115200);
  //connect_wifi();
  delay(1000);
  pinMode(Buzzer, OUTPUT);
  pinMode(cam_en, OUTPUT); 

  pinMode(Gas_analog, INPUT);
  pinMode(Gas_6, INPUT); 
  pinMode(led, OUTPUT);   
  digitalWrite(cam_en,HIGH);
  digitalWrite(led,HIGH);
  
  Serial.print("led ON");
  delay(29500);
  Serial.print("led off");
  digitalWrite(Buzzer,HIGH);
  delay(500);
  
  digitalWrite(led,LOW);
  digitalWrite(Buzzer,LOW);
  //message_sent=0;
  //error=0;
}

void loop() {
  int gassensorAnalog = analogRead(Gas_analog);
  int gassensor6 = digitalRead(Gas_6);

  Serial.print("Gas Sensor: ");
  Serial.print(gassensorAnalog);
  Serial.print("\t");
  //Serial.print("Gas Class: ");
  //Serial.print(gassensorDigital);
  Serial.print("\t");
  Serial.print("\t");
  
  
  if (gassensorAnalog > 650 /*or gassensor6>950*/ ) {
    Serial.println("Gas");
    countsmoke=countsmoke+1;
    delay(1000);
    if (countsmoke>3){
      
    countno=0;
    digitalWrite (Buzzer, HIGH) ; //send tone
    //digitalWrite (cam_en, HIGH) ; 

    //if (message_sent==0){
     //sendMessage("Smoke detected in your kitchen");
     digitalWrite(cam_en,LOW);
     count_cam=count_cam+1000;
     digitalWrite(led,HIGH);
     Serial.print("led on loop");
    }
     // message_sent=1;
    //}
    //delay(15000);
    //digitalWrite (Buzzer, LOW) ;  //no tone
  }
 

 else if  (gassensorAnalog < 550 /*or gassensor6<850*/){
      countno=countno+1;
      delay(1000);
      if (countno>3){
       Serial.println("No Gas");
       countsmoke=0; 
      if (count_cam>70000){
      digitalWrite (cam_en, HIGH) ; 
      count_cam=0;
      }
      digitalWrite (led, LOW) ;
      digitalWrite (Buzzer, LOW) ;
      }
      
    //if (message_sent==1){
     // message_sent=0;
     //sendMessage("No smoke");
      

      
    }
    
 
 
}
