#include <Arduino.h>
#include <WiFi.h>
#include "Secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <iostream>
#include <string>
#include <Stepper.h>

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub/teste"
#define S_GET_FOOD_TOPIC "get_food"
#define P_SET_FOOD_TOPIC "set_food"
#define S_GET_DRINK_TOPIC "get_drink"
#define P_SET_DRINK_TOPIC "set_drink"
#define LED_PIN_5 0 //bebida
#define LED_PIN_4 4 //comida
#define LED_PIN_3 23 //comida
#define LED_PIN_2 2 //comida
#define BUTTON_1 15 //BOTÃO TESTE

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

const int stepsPerRevolution = 2048;

Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

int counter = 0;

const char* ssid = "uaifai-brum";
const char* password = "bemvindoaocesar";

void messageHandler(String &topic, String &payload);

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

void connectAWS()
{
	WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

	Serial.println("Connecting to Wi-Fi");

	while (WiFi.status() != WL_CONNECTED){
		delay(500);
		Serial.print(".");
	}

	// Configure WiFiClientSecure to use the AWS IoT device credentials
	net.setCACert(AWS_CERT_CA);
	net.setCertificate(AWS_CERT_CRT);
	net.setPrivateKey(AWS_CERT_PRIVATE);

	// Connect to the MQTT broker on the AWS endpoint we defined earlier
	client.begin(AWS_IOT_ENDPOINT, 8883, net);

	// Create a message handler
	client.onMessage(messageHandler);

	Serial.print("Connecting to AWS IOT");

	while (!client.connect(THINGNAME)) {
		Serial.print(".");
		delay(100);
	}

	if(!client.connected()){
		Serial.println("AWS IoT Timeout!");
		return;
	}

	// Subscribe to a topic
	client.subscribe(S_GET_FOOD_TOPIC);
	client.subscribe(S_GET_DRINK_TOPIC);

	Serial.println("AWS IoT Connected!");
}

void get_food(String &type) {
	int led;

	if (type == "2") {
		led = LED_PIN_2;
	} else if (type == "3") {
		led = LED_PIN_3;
	} else if (type == "4") {
		led = LED_PIN_4;
	}

	digitalWrite(led, HIGH);
	delay(1000);
	digitalWrite(led, LOW);
	delay(1000);

	// write code to spin engine (check angle)
}

void get_drink(String &type) {
	int led = LED_PIN_5;

	Serial.println(led);
	digitalWrite(led, HIGH);
	delay(1000);
	digitalWrite(led, LOW);
	delay(1000);

	// write code to release valve (check time)
}

void publishMessage() {
	StaticJsonDocument<200> doc;
	doc["time"] = millis();

	doc["sensor_a0"] = counter++;

	char jsonBuffer[512];
	serializeJson(doc, jsonBuffer); // print to client

	client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(String &topic, String &payload) {
	StaticJsonDocument<200> doc;

	DeserializationError error = deserializeJson(doc, payload);

    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }

	String type = doc["type"].as<String>();

	Serial.println(topic);

	if (topic == S_GET_FOOD_TOPIC) {
		get_food(type);
	} else if (topic == S_GET_DRINK_TOPIC){
		get_drink(type);
	}

	const char* message = doc["message"];
}

void setup() {
	Serial.begin(115200);

	myStepper.setSpeed(5);


	pinMode(LED_PIN_2, OUTPUT);
	pinMode(LED_PIN_3, OUTPUT);
	pinMode(LED_PIN_4, OUTPUT);
	pinMode(LED_PIN_5, OUTPUT);
	pinMode(BUTTON_1, INPUT_PULLUP);

	digitalWrite(LED_PIN_5, HIGH);
	delay(1000);
	digitalWrite(LED_PIN_5, LOW);
	delay(1000);

	connectAWS();
}

void set_food(char * food_type) {
	StaticJsonDocument<200> doc;

	doc["type"] = food_type;

	char jsonBuffer[512];

	serializeJson(doc, jsonBuffer); // print to client
    client.publish(P_SET_FOOD_TOPIC, jsonBuffer);

    delay(1000); // Debouncing delay
}

void loop() {
	client.onMessage(messageHandler);
	client.loop();

	int button_1 = !digitalRead(BUTTON_1);

	myStepper.step(stepsPerRevolution);

  	if (button_1 == HIGH) {
		set_food("1");
	}

	delay(2000);
}
