#include <SPI.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "Network Name"; // your network SSID (name)
char pass[] = "Network Pass"; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0; // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // Initialize IMU
  if (!IMU.begin()) {
    Serial.println("LSM6DS3 sensor error!");
    while (1);
  }

  // Wait for serial port to connect
  while (!Serial) {
    delay(100);
  }

  // Check WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the WiFi firmware");
  }

  // Attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();
  printWifiStatus();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    //Serial.println("New client connected");

    // Get current WiFi status
    String ssid = WiFi.SSID();
    IPAddress ip = WiFi.localIP();
    int rssi = WiFi.RSSI();

    // Read IMU data
    float ax, ay, az;
    float gx, gy, gz;
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);

    // Send HTML response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println("Refresh: 5"); // Refresh page every 5 seconds
    client.println();
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>Arduino Nano 33 IoT Sensor Data</title>");
    client.println("<style>");
    client.println("body { font-family: Arial, sans-serif; padding: 20px; }");
    client.println("h1 { color: #2c3e50; }");
    client.println("table { width: 100%; border-collapse: collapse; margin: 10px 0; }");
    client.println("th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }");
    client.println("th { background-color: #f2f2f2; }");
    client.println("tr:nth-child(even) { background-color: #f9f9f9; }");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>Arduino Nano 33 IoT Sensor Data</h1>");
    client.println("<div style='margin-bottom: 20px;'>");
    client.println("<h2>WiFi Status</h2>");
    client.println("<table>");
    client.println("<tr><th>Parameter</th><th>Value</th></tr>");
    client.println("<tr><td>Network SSID</td><td>" + ssid + "</td></tr>");
    client.println("<tr><td>IP Address</td><td>" + ip.toString() + "</td></tr>");
    client.println("<tr><td>Signal Strength</td><td>" + String(rssi) + " dBm</td></tr>");
    client.println("</table>");
    client.println("</div>");

    client.println("<div style='margin-bottom: 20px;'>");
    client.println("<h2>IMU Sensor Data</h2>");
    client.println("<table>");
    client.println("<tr><th>Parameter</th><th>Value</th></tr>");
    client.println("<tr><td>Acceleration (m/s²)</td><td>x: " + String(ax) + ", y: " + String(ay) + ", z: " + String(az) + "</td></tr>");
    client.println("<tr><td>Gyroscope (deg/s)</td><td>x: " + String(gx) + ", y: " + String(gy) + ", z: " + String(gz) + "</td></tr>");
    client.println("</table>");
    client.println("</div>");

    client.println("<p>Refresh this page to see updated sensor data (every 5 seconds)</p>");
    client.println("</body>");
    client.println("</html>");

    client.stop();
    //Serial.println("Client disconnected");
  }
  delay(1);
}

void printWifiStatus() {
  // Print WiFi status to Serial
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
