<div align="center">

# 🚗 ESP32 WiFi RC Car

**Control a real robot car from your phone browser — no app, no internet, no cloud.**  
*Built on ESP32 · L298N Motor Driver · Embedded Web Server*

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue?logo=espressif)](https://www.espressif.com/)
[![Framework](https://img.shields.io/badge/Framework-Arduino-teal?logo=arduino)](https://www.arduino.cc/)
[![Status](https://img.shields.io/badge/Status-Complete-brightgreen)]()
[![License](https://img.shields.io/badge/License-MIT-orange)](LICENSE)

</div>

---

## 📌 What Is This?

This is a **WiFi-controlled RC car** built from scratch using an ESP32 microcontroller. The ESP32 creates its own WiFi hotspot and serves a mobile-responsive touch control page directly from its flash memory. Any phone or laptop can connect and drive the car — instantly, with zero setup.

No app install. No router. No internet. Just power it on, connect to the WiFi, and drive.

> Built as a personal embedded systems project by **Farhan**, 2nd-year CSE student at KUET.

---

## ⚡ How It Works

```
Phone / Laptop
     │
     │  connects to WiFi: "ESP32_CAR"
     ▼
ESP32 (SoftAP Mode)  ←──────────────────────────┐
192.168.4.1                                      │
     │                                           │
     │  serves HTML/CSS/JS control page          │
     ▼                                           │
Browser UI (touch buttons)                       │
     │                                           │
     │  HTTP GET /forward, /left, /stop …        │
     └────────────────────────────────────────── ┘
     │
     ▼
WebServer routes → rotateMotor() → L298N PWM → DC Motors
```

1. ESP32 boots and creates a WiFi hotspot (`ESP32_CAR`)
2. User connects their phone to that network
3. Browser opens `192.168.4.1` — the car's control page loads instantly
4. Touch buttons fire HTTP GET requests to the ESP32
5. ESP32 drives the motors via the L298N H-bridge using hardware PWM

---

## 🔌 Pin Assignment

| Signal | ESP32 GPIO |
|--------|-----------|
| Right Motor IN1 | 16 |
| Right Motor IN2 | 17 |
| Right Motor EN (PWM) | 22 |
| Left Motor IN1 | 18 |
| Left Motor IN2 | 19 |
| Left Motor EN (PWM) | 23 |

> PWM: 1000 Hz · 8-bit resolution · `MAX_MOTOR_SPEED = 200` (out of 255)  
> ESP32 Arduino Core: **v2.x** — uses `ledcSetup()` / `ledcAttachPin()` API

---

## 📐 Circuit Diagram

![Phase 1 Circuit Diagram](docs/circuit_phase1.svg)

Full wiring details with power architecture → [`docs/wiring_phase1.md`](docs/wiring_phase1.md)

---

## 🛠️ Hardware

| Component | Qty | Notes |
|-----------|-----|-------|
| ESP32 Dev Board (30-pin) | 1 | Main MCU |
| L298N Dual H-Bridge Module | 1 | Motor driver |
| DC Gear Motor | 2 | Differential drive |
| 7.4V LiPo / 18650 Cell Pack | 1 | Main power supply |
| Jumper wires + RC chassis | — | Standard chassis kit |

---

## 🚀 Flash & Run

1. Install [Arduino IDE 2.x](https://www.arduino.cc/en/software)
2. Add ESP32 board support URL in Preferences:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Board Manager → install **esp32 by Espressif Systems** (v2.x)
4. Select board: **ESP32 Dev Module**
5. Open `phase1_manual_wifi/phase1_manual_wifi.ino`
6. Upload → open Serial Monitor at **115200 baud**
7. Connect your phone to WiFi: `ESP32_CAR` / password: `12345678`
8. Open browser → `192.168.4.1` → drive!

---

## 🧩 Technical Highlights

- **Zero external libraries** — only built-in ESP32 Arduino core (`WiFi.h`, `WebServer.h`)
- **Entire web UI embedded in firmware** — served from flash using `R"rawliteral(...)"` string
- **Hardware PWM via LEDC peripheral** — smooth, jitter-free motor speed control
- **Touch-event driven UI** — `ontouchstart` / `ontouchend` for instant response with auto-stop on finger lift
- **Differential drive turns** — counter-rotation on opposite motors for tight zero-radius turns
- **Completely offline operation** — no router, no internet, no external server

---

## 📸 Build Photos & Videos

> See [`media/photos/`](media/photos/) and [`media/videos/`](media/videos/) for real build photos and demo videos.

---

## 🔮 Future Upgrades

This project is being developed in phases. Planned upgrades include:

- **Obstacle Avoidance** — HC-SR04 ultrasonic sensor + Auto/Manual mode toggle in web UI. In Auto mode the car detects and avoids obstacles independently using a non-blocking `millis()`-based state machine
- **Hand Gesture Control** — MPU-6050 IMU on a second ESP32 worn on the wrist reads pitch/roll and sends motor commands over WiFi. A third "Gesture" mode in the web UI activates this

---

## 📁 Repository Structure

```
esp32-smartcar/
├── phase1_manual_wifi/
│   └── phase1_manual_wifi.ino   ← firmware (upload this)
├── docs/
│   ├── circuit_phase1.svg       ← circuit diagram
│   └── wiring_phase1.md         ← full wiring guide
├── media/
│   ├── photos/                  ← add build photos here
│   └── videos/                  ← add demo videos here
├── README.md
└── LICENSE
```

---

## 📄 License

MIT License — see [LICENSE](LICENSE)

---

<div align="center">
Made with ☕ and solder by <strong>Farhan</strong> · KUET CSE
</div>
