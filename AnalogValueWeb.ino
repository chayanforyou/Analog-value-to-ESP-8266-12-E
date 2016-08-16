#include <ESP8266WiFi.h>

const char* ssid = "your ssid";
const char* password = "your password";

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 100;           // interval at which to blink (milliseconds)

int sensorValue = 0;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  //Start the server
  server.begin();
  Serial.println("Server started");

  //Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait unlil the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  Serial.println("Client disconnected");
  Serial.println("");

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    sensorValue = analogRead(A0);
  }

  String webpage = "<head><meta http-equiv=""refresh"" content=""3""></head>";
  webpage += "<h1>Sensor Value</h1><h2>";
  webpage += String(sensorValue);
  webpage += "</h2>";
  client.println(webpage);

}
