# Phase 1 — Wiring Guide: ESP32 + L298N + DC Motors

## Overview

In Phase 1 the ESP32 talks directly to an L298N dual H-bridge motor driver module. No sensor wiring is needed yet.

---

## Power Architecture

```
18650 / LiPo Pack (7.4V)
        │
        ├─── L298N VIN (motor power)
        │         └── L298N 5V output ──▶ ESP32 VIN (regulated 5V)
        │
        └─── Common GND ──▶ L298N GND + ESP32 GND (shared ground!)
```

> ⚠️ **Always connect common ground** between L298N and ESP32 or motor direction will be unreliable.

---

## ESP32 → L298N Connections

| ESP32 GPIO | L298N Pin | Function |
|-----------|-----------|----------|
| GPIO 16 | IN1 | Right motor direction A |
| GPIO 17 | IN2 | Right motor direction B |
| GPIO 22 | ENA | Right motor PWM speed |
| GPIO 18 | IN3 | Left motor direction A |
| GPIO 19 | IN4 | Left motor direction B |
| GPIO 23 | ENB | Left motor PWM speed |
| GND | GND | Common ground |

> Remove the ENA and ENB jumpers on the L298N board — these pins are now driven by ESP32 PWM.

---

## L298N → Motors

| L298N Terminal | Connection |
|----------------|------------|
| OUT1 | Right motor terminal A |
| OUT2 | Right motor terminal B |
| OUT3 | Left motor terminal A |
| OUT4 | Left motor terminal B |

> If your car drives backward when it should go forward, swap OUT1↔OUT2 or OUT3↔OUT4 for that motor.

---

## Motor Direction Logic Table

| IN1 | IN2 | Motor |
|-----|-----|-------|
| HIGH | LOW | Forward |
| LOW | HIGH | Reverse |
| LOW | LOW | Coast/Stop |

---

## Notes

- The L298N onboard 5V regulator can power the ESP32 if the input voltage is 7–12V.
- If using a 5V power bank, connect directly to ESP32 5V pin and power motors from a separate supply.
- PWM frequency is 1000 Hz with 8-bit resolution. `MAX_MOTOR_SPEED = 200` out of 255 to protect motors during development.
