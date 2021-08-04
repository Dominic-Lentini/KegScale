#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#ifndef STASSID
#define STASSID "Lentini_IoT2G"
#define STAPSK  "niftytomato964"
#endif


const char *ssid = STASSID;
const char *password = STAPSK;
const char *PARAM_INPUT_1 = "Tap1";
const char *PARAM_INPUT_2 = "Tap2";
const char *PARAM_INPUT_3 = "Tap3";
const char *PARAM_INPUT_4 = "Tap4";

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    Tap1: <input type="text" name="Tap1">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    Tap2: <input type="text" name="Tap2">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    Tap3: <input type="text" name="Tap3">
    <input type="submit" value="Submit">
  </form><br>
    <form action="/get">
    Tap4: <input type="text" name="Tap4">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = "1" + request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = "2" + request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
    }
    else if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage = "3" + request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
    }
    else if (request->hasParam(PARAM_INPUT_4)) {
      inputMessage = "4" + request->getParam(PARAM_INPUT_4)->value();
      inputParam = PARAM_INPUT_4;
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.print(inputMessage);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}
