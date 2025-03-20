#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Firebase credentials
#define FIREBASE_HOST "YOUR_FIREBASE_URL.firebaseio.com"
#define FIREBASE_AUTH "YOUR_FIREBASE_SECRET_KEY"

// WiFi credentials
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

FirebaseData firebaseData;
WiFiClient client;

void setup() {
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected!");

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);

    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
}

void loop() {
    if (Firebase.getInt(firebaseData, "/home/light1")) {
        int state = firebaseData.intData();
        digitalWrite(D1, state);
    }

    if (Firebase.getInt(firebaseData, "/home/fan1")) {
        int state = firebaseData.intData();
        digitalWrite(D2, state);
    }

    delay(1000);
}
