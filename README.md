# EMG-Based Prosthetic Arm Control System

## Overview

This project presents a low-cost EMG-based prosthetic arm control system developed using a custom biopotential signal acquisition module, Arduino Nano, and 3D-printed mechanical components.

The system detects muscle activity through electromyography (EMG) signals and translates user muscle contractions into prosthetic hand movements. A custom-designed EXG acquisition circuit amplifies and conditions EMG signals, while an Arduino Nano performs signal processing and servo motor control.

The project aims to demonstrate an affordable and accessible prosthetic control solution for educational, research, and assistive technology applications.

---

## Related Project

This project utilizes a custom biopotential signal acquisition module developed in a separate repository:

**Biopotential Signal Acquisition EXG**

The EXG module was independently developed through reverse engineering, schematic redesign, PCB development, SMD assembly, and hardware validation. It serves as the analog front-end responsible for acquiring and conditioning EMG signals used for prosthetic hand control.

Repository:

[https://github.com/YOUR_USERNAME/biopotential-signal-acquisition-exg](https://github.com/rizaaria/Biopotential-Signal-Acquisition-EXG)

## Motivation

Commercial myoelectric prosthetic systems are often expensive and difficult to access in developing regions.

This project explores a low-cost alternative by combining:

- Custom EMG acquisition hardware
- Open-source embedded development
- 3D printed prosthetic structures
- Affordable electronic components

to create a functional muscle-controlled prosthetic prototype.

---

## Features

- Real-time EMG signal acquisition
- EMG envelope detection
- Muscle contraction recognition
- Open/close prosthetic hand control
- Smooth servo movement
- Custom EXG hardware
- Custom PCB design
- 3D printed prosthetic structure
- Portable battery-powered operation

---

## Hardware Components

| Component | Quantity |
|------------|----------|
| Arduino Nano | 1 |
| Custom EXG Module | 1 |
| Servo Motor | 1 |
| LiPo Battery 3.7V | 1 |
| MT3608 Step-Up Converter | 1 |
| EMG Electrodes | 3 |
| Custom PCB | 1 |
| 3D Printed Prosthetic Hand | 1 |

---

## Signal Processing Pipeline

```text
Raw EMG Signal
       │
       ▼
Bandpass Filtering
       │
       ▼
Rectification
       │
       ▼
Envelope Detection
       │
       ▼
Threshold Detection
       │
       ▼
Servo Control
```

---

## Control Logic

The prosthetic hand operates using a threshold-based control strategy.

### Muscle Contraction

When the EMG envelope exceeds the activation threshold:

```text
EMG Envelope > 30
       ↓
Hand Close
```

### Muscle Relaxation

When the EMG envelope falls below the relaxation threshold:

```text
EMG Envelope < 10
       ↓
Hand Open
```

To reduce sudden movements, servo transitions are smoothed using incremental angle updates.

---

## Custom Hardware Development

The project includes independent development of:

- Schematic design
- PCB layout design
- PCB fabrication
- SMD assembly
- Hardware testing
- EMG validation

The EMG acquisition module was developed based on knowledge gained from studying open-source EXG platforms and adapted for prosthetic control applications.

---

## Mechanical Design

The prosthetic hand was designed for additive manufacturing using 3D printing technology.

Design considerations:

- Low-cost fabrication
- Lightweight structure
- Easy assembly

---

## Results

The developed system successfully demonstrated:

- EMG signal acquisition
- Real-time muscle activity detection
- Prosthetic hand opening and closing
- Stable servo actuation
- Portable operation using battery power

---

## License

This project is intended for educational and research purposes.
