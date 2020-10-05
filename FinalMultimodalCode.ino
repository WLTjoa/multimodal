#include <ESP32Servo.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

static const int outerservoPin = 16; //printed G14 on the board
static const int innerservoPin = 17; //printed G14 on the board

Servo innerServo;
Servo outerServo;

int vMotorPin = 18;
bool ended = false;
String text, from_name;
int person = 0;
int msgsent = 0;


// Initialize Wifi connection to the router
char ssid[] = "XXXX";     // your network SSID (name)
char password[] = "XXXXXXXXXXXXXXXXXX"; // your network key

// Initialize Telegram BOT
#define BOTtoken "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;

void handleNewMessages(int numNewMessages) {
//  Serial.println("handleNewMessages");
//  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;

    if (from_name == "Wan"){
      person = 1;
    }
    if (from_name == "Emma"){
      person = 2;
    }
    if (from_name == "Wei Lin"){
      person = 3;
    }

    if (text == "/love") {
        bot.sendChatAction(chat_id, "typing");
        delay(100);
        bot.sendMessage(chat_id, "Received love!");
        Serial.println("lof from " + from_name);
        msgsent = 1;
    }

    if (text == "/happy") {
        bot.sendChatAction(chat_id, "typing");
        delay(200);
        bot.sendMessage(chat_id, "Smile! :D");
        Serial.println("happy from " + from_name);
        msgsent = 2;
    }

    if (text == "/angry") {
        bot.sendChatAction(chat_id, "typing");
        delay(200);
        bot.sendMessage(chat_id, "Anger sent!! >:(");
        Serial.println("angry from " + from_name);
        msgsent = 3;
    }

    if (text == "/emergency") {
        bot.sendChatAction(chat_id, "typing");
        delay(200);
        bot.sendMessage(chat_id, "Called for help!!");
        Serial.println("emergency from " + from_name);
        msgsent = 4;
    }

    if (text == "/home") {
        bot.sendChatAction(chat_id, "typing");
        delay(200);
        bot.sendMessage(chat_id, "Welcome Home!!");
        Serial.println("home from " + from_name);
        msgsent = 5;
    }
    
    if (text == "/start") {
      String welcome = "Welcome to Feel My Message, " + from_name + ".\n";
      welcome += "Here is a list of commands for you to use :D\n\n";
      welcome += "/love - send love 💕 \n/happy - send happiness ☺ \n/angry - send anger 😡 \n/emergency - send sos 🆘 \n/home - send I’m at home 🏠";
      bot.sendMessage(chat_id, welcome);
    }
  }
}


void setup() {

  pinMode(vMotorPin, OUTPUT);
  innerServo.attach(innerservoPin);
  outerServo.attach(outerservoPin);
  
  Serial.begin(115200);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void stopturning(){
   innerServo.write(93);
}

void vibrate(){
   delay(50);
   digitalWrite(vMotorPin, HIGH);
   delay(500);
   digitalWrite(vMotorPin, LOW);
}

void msg1(){
   innerServo.write(70);
   delay(640);
   innerServo.write(93);
   vibrate();
   delay(5000);
   innerServo.write(110);
   delay(750);
   stopturning();
}

void msg2(){
   innerServo.write(70);
   delay(1000);
   innerServo.write(93);
   vibrate();
   delay(5000);
   innerServo.write(110);
   delay(1150);
   stopturning();
}

void msg3(){
   innerServo.write(70);
   delay(1550);
   innerServo.write(93);
   vibrate();
   delay(5000);
   innerServo.write(110);
   delay(1700);
   stopturning();
}

void msg4(){
   innerServo.write(110);
   delay(1280);
   innerServo.write(93);
   vibrate();
   delay(5000);
   innerServo.write(70);
   delay(1010);
   stopturning();
}

void msg5(){
   innerServo.write(110);
   delay(750);
   innerServo.write(93);
   vibrate();
   delay(5000);
   innerServo.write(70);
   delay(620);
   stopturning();
}

void sendmsg(){
  if(msgsent == 1){
    if (ended == false){
      Serial.println("msg1");
      msg1();
      msgsent = 0;
    }
  }

  if(msgsent == 2){
    if (ended == false){
      Serial.println("msg2");
      msg2();
      msgsent = 0;
    }
  }

  if(msgsent == 3){
    if (ended == false){
      Serial.println("msg3");
      msg3();
      msgsent = 0;
    }
  }

  if(msgsent == 4){
    if (ended == false){
      Serial.println("msg4");
      msg4();
      msgsent = 0;
    }
  }

  if(msgsent == 5){
    if (ended == false){
      Serial.println("msg5");
      msg5();
      msgsent = 0;
    }
  }
}

void per1(){
}

void per2(){
   outerServo.write(180);
   delay(270);
   outerServo.write(93);
}

void per2back(){
   outerServo.write(0);
   delay(270);
   outerServo.write(93);
}

void per3(){
   outerServo.write(0);
   delay(250);
   outerServo.write(93);
}

void per3back(){
   outerServo.write(180);
   delay(260);
   outerServo.write(93);
}


void loop() {   
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
//      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
  if(person == 1){
    if (ended == false){
      Serial.println("per1");
      per1();
      sendmsg();
      person = 99;
    }
  }

  if(person == 2){
    if (ended == false){
      Serial.println("per2");
      per2();
      person = 99;
      sendmsg();
      per2back();
    }
  }

  if(person == 3){
    if (ended == false){
      Serial.println("per3");
      per3();
      person = 99;
      sendmsg();
      per3back();
    }
  }


}
