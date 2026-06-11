# Phase 2 — Wiring Guide: HC-SR04 Ultrasonic Sensor

> 🔄 **Status: In Progress** — Pin assignments to be confirmed before firmware is written.

## Planned Additions

| Component | New Pins | Notes |
|-----------|----------|-------|
| HC-SR04 TRIG | TBD | Digital output from ESP32 |
| HC-SR04 ECHO | TBD | Digital input to ESP32 — use voltage divider (5V→3.3V) |
| HC-SR04 VCC | 5V | From L298N 5V output or separate regulator |
| HC-SR04 GND | GND | Common ground |

> ⚠️ The HC-SR04 ECHO pin outputs 5V logic. Use a 1kΩ/2kΩ voltage divider to protect the ESP32's 3.3V GPIO.

## Voltage Divider for ECHO Pin

```
HC-SR04 ECHO ──[ 1kΩ ]──┬──▶ ESP32 GPIO (ECHO)
                         │
                       [ 2kΩ ]
                         │
                        GND
```

## All Other Wiring

Identical to Phase 1. See [wiring_phase1.md](wiring_phase1.md).
