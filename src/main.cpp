#include <Arduino.h>
#include <BlynkSimpleEsp8266.h>
#include "Credentials.h"

char auth[] = BLYNK_KEY;

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWORD;

int BUTTON_PIN = 0;
int CONTROL_PIN = 2;

int buttonState = HIGH;
int prevButtonState = HIGH;
int relayState = HIGH;

BLYNK_WRITE(V1)
        {
                relayState = param.asInt();
        };

int invertLogic(int value) {
    return LOW + HIGH - value;
}

void setup() {
    Serial.begin(115200);

    pinMode(CONTROL_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);

    digitalWrite(CONTROL_PIN, relayState);

    Blynk.begin(auth, ssid, pass);
    Blynk.syncAll();
}

void loop() {
    buttonState = digitalRead(BUTTON_PIN);
    Serial.println(buttonState);
    if (buttonState == LOW && prevButtonState != buttonState) {
        relayState = invertLogic(relayState);
    }
    prevButtonState = buttonState;

    digitalWrite(CONTROL_PIN, relayState);

    Blynk.virtualWrite(V1, relayState);
    Blynk.run();
}

