#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

constexpr int btn_left = 35;
constexpr int btn_mid = 25;
constexpr int btn_right = 33;
constexpr int led = 32;
constexpr int motor = 26;

int led_state = 0;
int motor_state = LOW;

constexpr auto ssid = "JJD2";
constexpr auto password = "0987654321";

AsyncWebServer server(80);

void setup() {
  pinMode(btn_left, INPUT_PULLDOWN);
  pinMode(btn_mid, INPUT_PULLDOWN);
  pinMode(btn_right, INPUT_PULLDOWN);
  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);

  Serial.begin(9600);
  SPIFFS.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {}
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(SPIFFS, "/index.html" , "text/html");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(SPIFFS, "/style.css" , "text/css");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(SPIFFS, "/script.js" , "text/javascript");
  });

  server.on("/buttons", HTTP_GET, [](AsyncWebServerRequest *req){
    String resp = String(digitalRead(btn_left)) + "/" + String(digitalRead(btn_mid)) + "/" + String(digitalRead(btn_right));
    req->send(200, "text/plain", resp);
  }); 

  server.on("/motor_on", HTTP_GET, [](AsyncWebServerRequest *req){
    int number_of_params = req->params();
    Serial.println("params = " + String(number_of_params));
    for (int i=0; i<number_of_params; i++) {
      auto p = req->getParam(i);
      Serial.println("par" + String(i) + ": " + String(p->name()) + " = " + String(p->value()));
    }
    digitalWrite(motor, HIGH);
    req->send(200);
  });

  server.on("/motor_off", HTTP_GET, [](AsyncWebServerRequest *req){
    int number_of_params = req->params();
    Serial.println("params = " + String(number_of_params));
    for (int i=0; i<number_of_params; i++) {
      auto p = req->getParam(i);
      Serial.println("par" + String(i) + ": " + String(p->name()) + " = " + String(p->value()));
    }
    digitalWrite(motor, LOW);
    req->send(200);
  });

  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *req){
    led_state ^= 0;
    digitalWrite(led, led_state);
    req->send(200);
  });

  server.begin();

}

void loop() {
  
  /*
  auto state_left = digitalRead(btn_left);
  auto state_mid = digitalRead(btn_mid);
  auto state_right = digitalRead(btn_right);

  Serial.println("left = " + String(state_left) + " mid = " + String(state_mid) + " right = " + String(state_right));
  delay(2000);*/
}