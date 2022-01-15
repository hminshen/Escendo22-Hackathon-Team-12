#include <Adafruit_Sensor.h>
#include <WiFiEsp.h>        //Wifi Library
#include <Arduino_JSON.h>   //JSON Library to parse JSON files

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

/*For Wifi Stuff*/
//Networking constants
char ssid[] = "ILOVENTU";           // your network SSID (name)
char pass[] = "ireallyloventu!";       // your network password
char server[] = "192.168.31.241";   //IP Address
int status = WL_IDLE_STATUS;      // the Wifi radio's status
int port = 5000;                  //Port of Server
String response = "";             //Response from Server

// Initialize the Ethernet client object
WiFiEspClient client;

//declare LED pins
const int LED_B_PIN = 10; //pin for Blue LED
const int LED_G_PIN = 9; //pin for Green LED
const int LED_R_PIN = 8; //pin for Red LED

//declare button pin and state
const int buttonPin = 12;
int buttonState =0; 

//declaring a timer to keep track of the length of time after the person presses the button
unsigned long timer,curTime;
bool timing = false;

//declaring state of the table: 0 is vacant, 1 is going to leave soon, 2 is occupied
String occupied;
// Arbitary zone and table no.
String tableNo = "10";
String zone = "4";

//declare photoResistor pin 
const int photoResistorPin1 = 2, photoResistorPin2 = 3;
int photoResistorState1 =0, photoResistorState2=0;

//

void setup(){
  //initalise for LED
  pinMode(LED_B_PIN,OUTPUT); //sets LEDPIN to output
  pinMode(LED_G_PIN,OUTPUT); //sets LEDPIN to output
  pinMode(LED_R_PIN,OUTPUT); //sets LEDPIN to output

  //initalise for Button
  pinMode(buttonPin,INPUT); //sets ButtonPin to input

  //initalise for photoResistor
  pinMode(photoResistorPin1,INPUT); //sets photoResistor1 to output
  pinMode(photoResistorPin2,INPUT); //sets photoResistor2 to output

  analogWrite(LED_G_PIN ,255); //sets it to be vacant initially


  /*To connect to Wifi*/
  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  if (client.connect(server, port)) {
    Serial.println("Connected to server");
  }
}

void loop(){
  buttonState = digitalRead(buttonPin);
  photoResistorState1 = digitalRead(photoResistorPin1);
  photoResistorState2 = digitalRead(photoResistorPin2);
  curTime = millis();
 
  if(buttonState == 1 && !timing && (photoResistorState1 ==0 || photoResistorState2==0)){ //if button is being pressed & seat is occupied
     analogWrite(LED_G_PIN, 0);
     analogWrite(LED_R_PIN, 0);
     analogWrite(LED_B_PIN, 255);
     occupied = "1";
     timer = curTime;
     timing = true;
  }
  else if((photoResistorState1 ==0 || photoResistorState2==0)){ //if seat is occupied
    if (curTime - timer > 10000 && timing){ //if still occupied even after the timing has passed after pressing the button
      analogWrite(LED_R_PIN, 255);
      analogWrite(LED_B_PIN, 0);
      occupied = "2";
      timing = false;
    }
    else if(!timing){ //if someone occupies an empty table, make it occupied
      analogWrite(LED_G_PIN, 0);
      analogWrite(LED_R_PIN, 255);
      occupied = "2";
    }
  }
  else if (photoResistorState1 ==1 || photoResistorState2==1){ //if seat is now vacant
    analogWrite(LED_G_PIN, 255);
    analogWrite(LED_R_PIN, 0);
    analogWrite(LED_B_PIN, 0);
    timing = false;
    occupied = "0";
  }

  Serial.println(occupied);
  //POST Request to send Data
  sendData(tableNo, zone, occupied);
  delay(250);
}

/*For wifi addition*/
//Sending a HTTP POST Request
void sendData(String tableNo, String zone, String occupied) {
  // Creating JSON format
  String tableData = "\"Table Number\":" + tableNo;
  String zoneData = "\"Zone\":" + zone;
  String occupiedData = "\"Occupied\":" + occupied;
  String content = "{" + tableData + "," + zoneData + "," + occupiedData + "}";
  Serial.println(content);

  client.connect(server, port); //Connect to Server
  /*//HTTP Header*/
  client.println("POST /upload HTTP/1.1");
  client.println("Host: " + String(server) + ":" + port);
  client.println("Accept: */*");
  client.println("Content-Length: " + String(content.length()));
  client.println("Content-Type: application/json");
  client.println();

  //HTTP Content
  client.println(content);
  
  client.stop();  //Disconnect from Server
}
