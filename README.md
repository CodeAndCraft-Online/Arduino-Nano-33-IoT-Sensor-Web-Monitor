# Arduino Nano 33 IoT Sensor Web Monitor

A simple web server project that displays real-time sensor data and WiFi status from the Arduino Nano 33 IoT over Wi-Fi.

## Features

- 🌐 Real-time web interface accessible via browser
- 📊 Shows 3-axis acceleration and 3-axis gyroscope data
- 📶 Displays current WiFi connection status (SSID, IP, signal strength)
- ⚡ Automatic page refresh (every 5 seconds)
- 💡 Responsive design for mobile and desktop
- ✅ Works with Arduino Nano 33 IoT

## Hardware Requirements

- Arduino Nano 33 IoT (v1.0 or later)
- Any WiFi network (WPA/WPA2/WEP)

## Installation & Setup

### 1. Install Required Libraries
1. Open Arduino IDE
2. Go to `Sketch > Include Library > Manage Libraries...`
3. Install:
   - **WiFiNINA** (by WiFiNINA)
   - **Arduino_LSM6DS3** (by Arduino)

### 2. Configure Network Settings

```
// Replace with your actual WiFi credentials
char ssid[] = "YourWiFiName";
char pass[] = "YourWiFiPassword";
```

### 3. Upload to Arduino
1. Select `Arduino Nano 33 IoT` from the board menu
2. Upload the sketch to your board
3. The board will connect to WiFi and start the web server

## How to Access the Web Interface

1. Open a browser on your computer or phone
2. Go to: `http://<your-arduino-ip>`
   - *Example:* `http://192.168.1.100`
3. You'll see a live web page with sensor data

## Sample Output

```
WiFi Status:
- Network SSID: "xxxxxx"
- IP Address: 192.168.42.100
- Signal Strength: 85 dBm

IMU Sensor Data:
- Acceleration (m/s²): x: 0.23, y: -0.11, z: 0.87
- Gyroscope (deg/s): x: 0.42, y: 1.75, z: -0.31
```

## Technical Details

| Component | Description |
|-----------|-------------|
| **Sensor** | LSM6DS3 3D accelerometer + gyroscope |
| **WiFi** | WiFiNINA (v1.1.0+) |
| **Web Server** | HTTP 1.1 with automatic refresh |
| **Data Update Rate** | Every 5 seconds |
| **Target Device** | Arduino Nano 33 IoT |

## Troubleshooting

| Issue | Solution |
|-------|----------|
| "Connection failed" | Check WiFi password and network name |
| No web page | Verify IP address (use `WiFi.localIP()` in Serial Monitor) |
| Data not updating | Check sensor initialization (use Serial Monitor for errors) |
| Slow response | Ensure WiFi is connected properly |

## Contributing

Contributions are welcome! Please follow these steps:
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to your branch (`git push origin feature/AmazingFeature`)
5. Create a new Pull Request

