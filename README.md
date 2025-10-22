# ECE4760 Final Project — RP2040 VGA + Menu System

**Course:** ECE4760 Embedded Microcontrollers (Cornell Universitt)  
**Authors:** Gabriel Seger (@segergabriel) & Sebastian Clavijo  
**Platform:** Raspberry Pi Pico (RP2040)  
**Language:** C (CMake + pico-sdk)

> For a longer non-technical overview and results, see **[REPORT.md](./REPORT.md)**.

---

## Overview

This project implements a **VGA graphics pipeline** on the RP2040, a modular **menu system**, and demo modules (e.g., a simple game). Timing-critical VGA signals are generated with **PIO** state machines (HSYNC, VSYNC, RGB), while application logic (menu, demos, sensor/BT helpers) runs on the M0+ cores.

---

## 🗂 Repository Structure


```
├─ CMakeLists.txt                          # pico-sdk CMake project
├─ main.c                                  # System init; PIO + graphics setup; enters menu
├─ menu.c / menu.h                         # On-screen menu, command routing to demos/features
├─ vga_graphics.c / vga_graphics.h         # VGA drawing primitives (pixels, lines, text)
├─ glcdfont.c                              # Bitmap font used by text renderer
├─ tic_tac_toe.c / tic_tac_toe.h           # Simple demo/game launched from menu (if enabled)
├─ sensor.c / sensor.h                     # Optional: sensor helpers & visualizations
├─ bluetooth.c / bluetooth.h               # Optional: serial/Bluetooth helper utilities
├─ pt_cornell_rp2040_v1.h                  # Protothreads utilities for timing/cooperative tasks
├─ hsync.pio                               # PIO program for HSYNC timing
├─ vsync.pio                               # PIO program for VSYNC timing
└─ rgb.pio                                 # PIO program for RGB pixel timing/output
```


## 🖥️ Hardware & Pinout (VGA)

This design uses **three PIO programs**: HSYNC, VSYNC, and RGB. Connect RP2040 GPIOs to a VGA connector (typically via resistor ladder DAC for RGB). Ensure common ground between the Pico and VGA.

## Build

**Prerequisites**

- Install the **pico-sdk** and set `PICO_SDK_PATH` in your environment.
- Install **CMake** and an ARM toolchain (e.g., `gcc-arm-none-eabi`).
- macOS/Linux/Windows are all supported by pico-sdk.

**Build**

```bash
# From the repository root
mkdir build && cd build
cmake ..
make -j
```

## Running

Power the Pico and connect the VGA monitor.
On boot you should see the menu render.
Interact via on-board/user buttons, or Serial/Bluetooth commands (open a serial terminal at the configured baud).
From the menu you can launch demos, sensor viewers, or any additional features you’ve enabled.

## Module Details

main.c — Clock/PIO init, graphics init, menu init, and main loop.

menu.c / menu.h — On-screen menu, user navigation, and dispatch to feature entry points.

vga_graphics.c / vga_graphics.h — Core drawing API: putpixel, lines, rectangles, text; wraps PIO timing.

glcdfont.c — 5×7 (or similar) bitmap font used by text routines.

tic_tac_toe.c / tic_tac_toe.h — Minimal demo showing drawing & input via the menu.

sensor.c / sensor.h (optional) — Read/display sensor data; stub or wire up to your hardware.

bluetooth.c / bluetooth.h (optional) — Helper utilities for serial/BLE bridges.

pt_cornell_rp2040_v1.h — Lightweight cooperative protothreads utilities.

hsync.pio / vsync.pio / rgb.pio — PIO programs that generate VGA timing and pixel output.



## Credits

Authors: Gabriel Seger & Sebastian Clavijo

Course: Cornell ECE4760 — Embedded Microcontrollers

Thanks: Prof. Hunter Adams and course staff; classmates for feedback and lab support
