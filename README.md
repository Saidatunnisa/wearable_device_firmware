# Smart Wearable Firmware & Sensor Simulator (Embedded C)

## 📌 Overview
An end-to-end **Embedded C Firmware Engine** designed for smart wearable devices (such as fitness bands and health trackers). This software emulates multi-axis accelerometer motion patterns and optical pulse (PPG) sensor readings, processing raw signal data using real-time DSP algorithms.

---

## 🛠 Key Features
- **Hardware Emulation:** Simulates 3-axis accelerometer dynamics (m/s²) and heart rate metrics (BPM) without physical sensors.
- **Peak-Detection Step Counter:** Implements threshold logic to detect vertical acceleration spikes (>10.3 m/s²) representing footsteps.
- **Efficient Memory Footprint:** Uses single-precision floating-point arithmetic (`float`) suitable for low-power microcontrollers (STM32 / ESP32 / ATmega).

---

## 📊 Sample Output
```text
===========================================
   WEARABLE FIRMWARE EMULATOR (PURE C)    
===========================================

[Cycle 01] Accel Z: 9.97 m/s^2 | Heart Rate: 72 bpm | Total Steps: 0
[Cycle 04] Accel Z: 10.38 m/s^2 | Heart Rate: 75 bpm | Total Steps: 1
[Cycle 10] Accel Z: 10.54 m/s^2 | Heart Rate: 79 bpm | Total Steps: 7

[SYS] Simulation Complete. Total detected steps: 7
