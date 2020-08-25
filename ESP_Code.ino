// Telegram bot library by Brian: https://github.com/sponsors/witnessmenow/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

char ssid[] = "XXXXXXXXXX";     // your network SSID (name)
char password[] = "XXXXXXXXXX"; // your network key

// Initialize Telegram BOT
#define BOTtoken "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 500;
unsigned long lastTimeBotRan;

int D1Status = 0;
int D2Status = 0;
int D3Status = 0;
int D4Status = 0;
int D5Status = 0;
int D6Status = 0;
int D7Status = 0;
int D8Status = 0;
int A0val = 0;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/D1ON") {
      digitalWrite(5,HIGH);
      D1Status = 1;
      bot.sendMessage(chat_id, "D1 is HIGH", "");
    }

    if (text == "/D1OFF") {
      D1Status = 0;
      digitalWrite(5, LOW);
      bot.sendMessage(chat_id, "D1 is LOW", "");
    }

    if (text == "/D2ON") {
      digitalWrite(4,HIGH);
      D2Status = 1;
      bot.sendMessage(chat_id, "D2 is HIGH", "");
    }

    if (text == "/D2OFF") {
      D2Status = 0;
      digitalWrite(4, LOW);
      bot.sendMessage(chat_id, "D2 is LOW", "");
    }

    if (text == "/D3ON") {
      digitalWrite(0,HIGH);
      D3Status = 1;
      bot.sendMessage(chat_id, "D3 is HIGH", "");
    }

    if (text == "/D3OFF") {
      D3Status = 0;
      digitalWrite(0, LOW);
      bot.sendMessage(chat_id, "D3 is LOW", "");
    }
    
    if (text == "/D4ON") {
      digitalWrite(2,HIGH);
      D4Status = 1;
      bot.sendMessage(chat_id, "D4 is HIGH", "");
    }

    if (text == "/D4OFF") {
      D4Status = 0;
      digitalWrite(2, LOW);
      bot.sendMessage(chat_id, "D4 is LOW", "");
    }
    
    if (text == "/D5ON") {
      digitalWrite(14,HIGH);
      D5Status = 1;
      bot.sendMessage(chat_id, "D5 is HIGH", "");
    }

    if (text == "/D5OFF") {
      D5Status = 0;
      digitalWrite(14, LOW);
      bot.sendMessage(chat_id, "D5 is LOW", "");
    }
    
    if (text == "/D6ON") {
      digitalWrite(12,HIGH);
      D6Status = 1;
      bot.sendMessage(chat_id, "D6 is HIGH", "");
    }

    if (text == "/D6OFF") {
      D6Status = 0;
      digitalWrite(12, LOW);
      bot.sendMessage(chat_id, "D6 is LOW", "");
    }
    
    if (text == "/D7ON") {
      digitalWrite(13,HIGH);
      D7Status = 1;
      bot.sendMessage(chat_id, "D7 is HIGH", "");
    }

    if (text == "/D7OFF") {
      D7Status = 0;
      digitalWrite(13, LOW);
      bot.sendMessage(chat_id, "D7 is LOW", "");
    }
    
    if (text == "/D8ON") {
      digitalWrite(15,HIGH);
      D8Status = 1;
      bot.sendMessage(chat_id, "D8 is HIGH", "");
    }

    if (text == "/D8OFF") {
      D8Status = 0;
      digitalWrite(15, LOW);
      bot.sendMessage(chat_id, "D8 is LOW", "");
    }
    
    if (text == "/A0") {
      String mess = "Sensor Val: ";
      mess += analogRead(A0);
      bot.sendMessage(chat_id, mess, "");
    }
    
    if (text == "/status") {
      if(D8Status){
        bot.sendMessage(chat_id, "D8 is HIGH", "");
      } else {
        bot.sendMessage(chat_id, "D8 is LOW", "");
      }
    }

    if (text == "/start") {
      String welcome = "ESP8266 controller, " + from_name + ".\n";
      welcome += "/D1ON : to switch the D1 pin HIGH\n";
      welcome += "/D1OFF : to switch the D1 pin LOW\n";
      welcome += "/D2ON : to switch the D2 pin HIGH\n";
      welcome += "/D2OFF : to switch the D2 pin LOW\n";
      welcome += "/D3ON : to switch the D3 pin HIGH\n";
      welcome += "/D3OFF : to switch the D3 pin LOW\n";
      welcome += "/D4ON : to switch the D4 pin HIGH\n";
      welcome += "/D4OFF : to switch the D4 pin LOW\n";
      welcome += "/D5ON : to switch the D5 pin HIGH\n";
      welcome += "/D5OFF : to switch the D5 pin LOW\n";
      welcome += "/D6ON : to switch the D6 pin HIGH\n";
      welcome += "/D6OFF : to switch the D6 pin LOW\n";
      welcome += "/D7ON : to switch the D7 pin HIGH\n";
      welcome += "/D7OFF : to switch the D7 pin LOW\n";
      welcome += "/D8ON : to switch the D8 pin HIGH\n";
      welcome += "/D8OFF : to switch the D8 pin LOW\n";
      welcome += "/A0 : Returns status of Analog input pin\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


void setup() {
  Serial.begin(115200);

  client.setInsecure();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(14, OUTPUT);
  delay(10);
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    lastTimeBotRan = millis();
  }
}
