<div align="center">

# ESP32 WiFi RC Car

**Control a robot car from your phone browser — no app, no internet, no cloud.**

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue?logo=espressif)](https://www.espressif.com/)
[![Framework](https://img.shields.io/badge/Framework-Arduino-teal?logo=arduino)](https://www.arduino.cc/)
[![Status](https://img.shields.io/badge/Status-Complete-brightgreen)]()
[![License](https://img.shields.io/badge/License-MIT-orange)](LICENSE)

</div>

---

## What Is This?

A WiFi-controlled RC car I built using an ESP32 microcontroller. The ESP32 creates its own WiFi hotspot and serves a touch-friendly control page straight from its memory. Any phone or laptop on the same network can open the page and drive the car.

No app to install. No router needed. No cloud. Just power it on, connect, and go.

---

## How It Works

```
Phone / Laptop
     │
     │  connects to WiFi "ESP32_CAR"
     ▼
ESP32 (SoftAP) — 192.168.4.1
     │
     │  serves the HTML control page
     ▼
Browser (touch buttons)
     │
     │  HTTP GET  →  /forward  /left  /right  /backward  /stop
     ▼
ESP32 WebServer  →  rotateMotor()  →  L298N  →  DC Motors
```

1. ESP32 boots and starts a WiFi hotspot
2. Connect your phone to `ESP32_CAR`
3. Open `192.168.4.1` in the browser
4. Use the touch buttons to drive
5. Releasing a button automatically stops the motors

---

## Hardware

| Component | Qty |
|-----------|-----|
| ESP32 Dev Board (30-pin) | 1 |
| L298N Dual H-Bridge Module | 1 |
| DC Gear Motor | 2 |
| 7.4V LiPo / 18650 Cell Pack | 1 |
| Jumper wires + RC chassis | — |

---

## Pin Connections

| Signal | ESP32 GPIO |
|--------|-----------|
| Right Motor IN1 | 16 |
| Right Motor IN2 | 17 |
| Right Motor EN (PWM) | 22 |
| Left Motor IN1 | 18 |
| Left Motor IN2 | 19 |
| Left Motor EN (PWM) | 23 |

PWM: 1000 Hz, 8-bit resolution. Motor speed set to 200/255 during testing.

> Uses ESP32 Arduino Core v2.x — `ledcSetup()` and `ledcAttachPin()` API.

---

## Circuit Diagram

![Circuit Diagram](docs/circuit_phase1.svg)

Full wiring breakdown: [docs/wiring_phase1.md](docs/wiring_phase1.md)

---

## Build Photos & Demo

Build photos and video clips are in the [media](media/) folder.

---

## How to Flash

1. Install [Arduino IDE 2.x](https://www.arduino.cc/en/software)
2. Go to **File → Preferences** and paste this URL under Additional Board Manager URLs:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Open **Board Manager** and install **esp32 by Espressif Systems** (any v2.x version)
4. Select board: **ESP32 Dev Module**
5. Open `phase1_manual_wifi/phase1_manual_wifi.ino`
6. Hit Upload, then open Serial Monitor at **115200 baud**
7. Connect your phone to WiFi `ESP32_CAR`, password `12345678`
8. Open `192.168.4.1` in the browser

---

## Some Technical Notes

- Only uses built-in ESP32 libraries — `WiFi.h` and `WebServer.h`, nothing extra to install
- The entire web page (HTML + CSS + JS) lives inside the `.ino` file as a raw string literal and gets served directly from flash
- Motor speed is controlled using the ESP32's hardware LEDC PWM peripheral
- Turning works by running the two motors in opposite directions — full counter-rotation for tight turns
- Touch buttons use `ontouchstart` and `ontouchend` so the car stops the moment you lift your finger

---

## Planned Upgrades

A couple of things I want to add to this:

- **Obstacle avoidance** — add an HC-SR04 ultrasonic sensor and a manual/auto mode toggle. In auto mode the car drives on its own, detects walls or objects, reverses and turns away
- **Gesture control** — use an MPU-6050 IMU on a second ESP32 strapped to the wrist. Tilt your hand to control the car. No buttons needed

---

## Folder Structure

```
esp32-smartcar/
├── phase1_manual_wifi/
│   └── phase1_manual_wifi.ino
├── docs/
│   ├── circuit_phase1.svg
│   └── wiring_phase1.md
├── media/
│   ├── photos/
│   └── videos/
├── README.md
└── LICENSE
```

---

## License

MIT — see [LICENSE](LICENSE)

---

<div align="center">
Farhan · KUET CSE
</div>
