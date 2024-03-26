#include <Arduino.h>
#include <WiFi.h>

#include "Secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <iostream>
#include <string>

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC_PET_LED "PET_LED"
#define PET_LED_PIN 2

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
	client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
	client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC_PET_LED);

	Serial.println("AWS IoT Connected!");
}

void publishMessage() {
	StaticJsonDocument<200> doc;
	doc["time"] = millis();

	doc["sensor_a0"] = counter++;

	char jsonBuffer[512];
	serializeJson(doc, jsonBuffer); // print to client

	client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
	Serial.println("Publicado teste");
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

    // Compare the topic string with the expected topic
    if (type == "1") {
        Serial.println(topic + "\n" + type + "\nteste comparação");

		digitalWrite(PET_LED_PIN, HIGH);
		delay(1000);
		digitalWrite(PET_LED_PIN, LOW);
		delay(1000);
	}

	const char* message = doc["message"];
}

void setup() {
	Serial.begin(115200);

	pinMode(PET_LED_PIN, OUTPUT);

	digitalWrite(PET_LED_PIN, HIGH);
	delay(1000);
	digitalWrite(PET_LED_PIN, LOW);
	delay(1000);

	connectAWS();
}

void loop() {
	publishMessage();
	client.onMessage(messageHandler);
	client.loop();
	delay(5000);
}
