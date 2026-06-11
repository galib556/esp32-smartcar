# Wiring Guide — ESP32 + L298N + DC Motors

## Power

```
7.4V Battery Pack
      │
      ├──▶ L298N VIN  (drives the motors)
      │         │
      │         └── L298N 5V OUT ──▶ ESP32 VIN  (powers the ESP32)
      │
      └──▶ Common GND ──▶ L298N GND + ESP32 GND
```

Both the L298N and ESP32 must share the same ground. If you skip this, the motor directions will be wrong or the car won't respond at all.

---

## ESP32 to L298N

| ESP32 GPIO | L298N Pin | What it does |
|-----------|-----------|--------------|
| GPIO 16 | IN1 | Right motor direction |
| GPIO 17 | IN2 | Right motor direction |
| GPIO 22 | ENA | Right motor speed (PWM) |
| GPIO 18 | IN3 | Left motor direction |
| GPIO 19 | IN4 | Left motor direction |
| GPIO 23 | ENB | Left motor speed (PWM) |
| GND | GND | Common ground |

**Important:** Remove the ENA and ENB jumpers from the L298N board. Those jumpers keep the motors at full speed permanently — pulling them out lets the ESP32 control speed via PWM.

---

## L298N to Motors

| L298N Terminal | Motor |
|----------------|-------|
| OUT1 | Right motor wire A |
| OUT2 | Right motor wire B |
| OUT3 | Left motor wire A |
| OUT4 | Left motor wire B |

If a motor spins the wrong way, just swap its two wires (OUT1↔OUT2 or OUT3↔OUT4).

---

## Motor Direction Logic

| IN1 | IN2 | Result |
|-----|-----|--------|
| HIGH | LOW | Forward |
| LOW | HIGH | Reverse |
| LOW | LOW | Stop |

---

## Notes

- The L298N's onboard regulator outputs a clean 5V that can directly power the ESP32 through its VIN pin, as long as battery voltage is between 7–12V.
- PWM runs at 1000 Hz, 8-bit resolution. Speed is set to 200 out of 255 — enough headroom to avoid stalling motors on the first run.
