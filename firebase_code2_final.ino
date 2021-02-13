#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>
//#include <SoftwareSerial.h>

#define FIREBASE_HOST "rajatabhaiot.firebaseio.com"
#define WIFI_SSID "Redmi" // Change the name of your WIFI
#define WIFI_PASSWORD "12345678"  // Change the password of your WIFI
#define FIREBASE_AUTH "N2yBqLTr68SyCJvTUerfqyLA5IjAgKON5VbSjcGP"
int trigPin=5;//D1
int echoPin=4;//D2
int duration, dist, average,val;   
int aver[3];   //array for average
int in1=14;//D5
int in2=2;//D4
void setup() {       
    Serial.begin(115200);
    WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
 
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  
  
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  
  //Serial.begin(9600); 
   pinMode(LED_BUILTIN, OUTPUT);
} 

void measure() {  

 
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1;    //obtain distance
}
void loop() { 
  for (int i=0;i<=2;i++) {   //average distance
    measure();               
   aver[i]=dist;            
    delay(10);              //delay between measurements
  }
 dist=(aver[0]+aver[1]+aver[2])/3;
  
 String name=String(dist);
  Firebase.setString("Dist",name);
    if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  //Firebase.setFloat ("Humidity",h);
  delay(200);
  val=Firebase.getString("S2").toInt();
  if(val==0)
  {
    digitalWrite(in1,HIGH);
    digitalWrite(in2,HIGH);
    Serial.println("yo!!!!");
  }
  else if(val==1)
  {
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    Serial.println("yo2222!!!!");
  }
}
