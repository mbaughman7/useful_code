#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "MY HOME SSID";
const char* password = "MY WIFI PASSWORD";


WebServer server(80);

// Route handler for the homepage
void handleRoot() {
  String html = "<html><body><h1>Hello from ESP32!</h1>";
  html += "<p>Sensor Value: <span id='sensorValue'></span></p>";
  html += "<script>setInterval(function() {";
  html += "var xhr = new XMLHttpRequest();";
  html += "xhr.onreadystatechange = function() {";
  html += "if (this.readyState === 4 && this.status === 200) {";
  html += "document.getElementById('sensorValue').innerHTML = this.responseText;";
  html += "}";
  html += "};";
  html += "xhr.open('GET', '/sensor', true);";
  html += "xhr.send();";
  html += "}, 1000);</script>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}


// Route handler for the sensor data page
void handleSensorData() {
  int sensorValue = analogRead(36);
  server.send(200, "text/plain", String(sensorValue));
}

void handleAction() {
  server.send(200, "text/html", "<html><body><h1 style='font-size: 10em;'>KNOCK KNOCK</h1></br><h3>who is there</h3></body></html>");
}

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print the ESP32's IP address
  Serial.println(WiFi.localIP());

  // Set up the web server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/sensor", HTTP_GET, handleSensorData);
  server.on("/data", HTTP_GET, handleAction);


  // Start the web server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();
}
