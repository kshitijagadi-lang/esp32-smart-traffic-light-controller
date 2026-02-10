# ESP32 Smart Traffic Light Controller 🚦

## Overview
This project implements a smart traffic light controller using the ESP32.
The system is designed using a Finite State Machine (FSM) and supports
interrupt-driven pedestrian requests and emergency override handling.

The project is fully simulated using Wokwi and demonstrates real-world
embedded systems concepts.

---

## Features
- Finite State Machine (FSM) based control logic
- Non-blocking timing using millis()
- Pedestrian button using hardware interrupt
- Emergency override with highest priority
- Clean and modular embedded design

---

## Hardware Components
- ESP32 Dev Module
- 3 LEDs (Red, Yellow, Green)
- 2 Push Buttons (Pedestrian & Emergency)
- Resistors (220Ω)

---

## Pin Configuration

| Component | GPIO |
|---------|------|
| Red LED | 25 |
| Yellow LED | 26 |
| Green LED | 27 |
| Pedestrian Button | 33 |
| Emergency Button | 32 |

---

## Working Principle
- Normal operation cycles through Red → Green → Yellow states
- Pedestrian button interrupts the Green state and safely switches to Red
- Emergency button immediately forces Red regardless of current state
- All timing is handled using non-blocking millis()

---

## Simulation
Wokwi Simulation Link:  
👉 (add link here)

---

## Future Improvements
- Countdown timer using 7-segment display
- RTC-based adaptive timing
- IoT dashboard integration
- Night mode operation

---

## Author
Kshitij Agadi
