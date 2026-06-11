# Phase 3 — Wiring Guide: MPU-6050 Gesture Transmitter

> 📅 **Status: Planned**

## Architecture

```
  [Wrist Unit]                         [Car Unit]
  ESP32 #2                             ESP32 #1
  + MPU-6050                           (Phase 2 firmware + Gesture mode)
       │                                      │
       │  WiFi HTTP GET /gesture?p=X&r=Y      │
       └──────────────────────────────────────┘
```

## Gesture Transmitter (Wrist ESP32 #2) → MPU-6050

| ESP32 GPIO | MPU-6050 Pin | Function |
|-----------|--------------|----------|
| GPIO 21 | SDA | I2C data |
| GPIO 22 | SCL | I2C clock |
| 3.3V | VCC | Power |
| GND | GND | Ground |

> Library: **MPU6050 by Electronic Cats** (install via Arduino Library Manager)

## Gesture → Motor Command Mapping (Planned)

| Gesture | Pitch/Roll | Command |
|---------|-----------|---------|
| Tilt forward | Pitch > +15° | Forward |
| Tilt backward | Pitch < -15° | Backward |
| Tilt left | Roll < -15° | Left |
| Tilt right | Roll > +15° | Right |
| Flat/level | < ±15° | Stop |

## Car Receiver Additions

- New HTTP route: `/gesture?pitch=X&roll=Y`
- Web UI gains a third **Gesture** mode toggle
- All existing Phase 2 wiring remains unchanged
