# ECE4760 Final Project — RP2040 VGA + Menu System

**Course:** ECE4760 Embedded Microcontrollers (Cornell)  
**Authors:** Gabriel Seger (@segergabriel) & Sebastian [Last name]  
**Platform:** Raspberry Pi Pico (RP2040)  
**Language:** C (CMake + pico-sdk)

> For a non-technical overview and results, see **[REPORT.md](./REPORT.md)**.

---

## 📌 Overview

This project implements a **VGA graphics pipeline** on the RP2040, a modular **menu system**, and demo modules (e.g., a simple game). Timing-critical VGA signals are generated with **PIO** state machines (HSYNC, VSYNC, RGB), while application logic (menu, demos, sensor/BT helpers) runs on the M0+ cores.

---

## 🗂 Repository Structure

> File names below reflect the typical layout used in this project. If any item isn’t present in your clone, remove that bullet; if you add new modules, list them here.

├─ CMakeLists.txt # pico-sdk CMake project
├─ main.c # System init; PIO + graphics setup; enters menu
├─ menu.c / menu.h # On-screen menu, command routing to demos/features
├─ vga_graphics.c / vga_graphics.h
│ # VGA drawing primitives (pixels, lines, text)
├─ glcdfont.c # Bitmap font used by text renderer
├─ tic_tac_toe.c / tic_tac_toe.h
│ # Simple demo/game launched from menu (if enabled)
├─ sensor.c / sensor.h # Optional: sensor helpers & visualizations
├─ bluetooth.c / bluetooth.h # Optional: serial/Bluetooth helper utilities
├─ pt_cornell_rp2040_v1.h # Protothreads utilities for timing/cooperative tasks
├─ hsync.pio # PIO program for HSYNC timing
├─ vsync.pio # PIO program for VSYNC timing
└─ rgb.pio # PIO program for RGB pixel timing/output


---

## 🖥️ Hardware & Pinout (VGA)

This design uses **three PIO programs**: HSYNC, VSYNC, and RGB. Connect RP2040 GPIOs to a VGA connector (typically via resistor ladder DAC for RGB). Ensure common ground between the Pico and VGA.

**Pin Mapping (update to match your wiring):**

| Signal | GPIO | Notes |
|-------:|:----:|------|
| HSYNC  | XX   | PIO SM for HSYNC pulse timing |
| VSYNC  | XX   | PIO SM for VSYNC pulse timing |
| R bits | XX.. | Resistor ladder to VGA R |
| G bits | XX.. | Resistor ladder to VGA G |
| B bits | XX.. | Resistor ladder to VGA B |

> Edit `vga_graphics.h/.c` to match your actual pins and RGB bit widths.

---

## Build & Flash

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

Flash

Hold BOOTSEL on the Pico and connect USB.

A mass-storage drive appears.

Drag-and-drop the generated .uf2 (in build/) onto that drive.

## Running

Power the Pico and connect the VGA monitor.

On boot you should see the menu render.

Interact via:

On-board/user buttons (if you wired inputs), or

Serial/Bluetooth commands (open a serial terminal at the configured baud).

From the menu you can launch demos (e.g., tic_tac_toe), sensor viewers, or any additional features you’ve enabled.

## Module Details

main.c — Clock/PIO init, graphics init, menu init, and main loop.

menu.c / menu.h — On-screen menu, user navigation, and dispatch to feature entry points.

vga_graphics.c / vga_graphics.h — Core drawing API: putpixel, lines, rectangles, text; wraps PIO timing.

glcdfont.c — 5×7 (or similar) bitmap font used by text routines.

tic_tac_toe.c / tic_tac_toe.h — Minimal demo showing drawing & input via the menu.

sensor.c / sensor.h (optional) — Read/display sensor data; stub or wire up to your hardware.

bluetooth.c / bluetooth.h (optional) — Helper utilities for serial/BLE bridges (e.g., HC-05).

pt_cornell_rp2040_v1.h — Lightweight cooperative protothreads utilities (commonly used in ECE4760).

hsync.pio / vsync.pio / rgb.pio — PIO programs that generate VGA timing and pixel output.

## Troubleshooting

No video: double-check pin mapping and resistor ladder wiring. Try a known-good VGA monitor/cable.

Rolling/unstable image: verify HSYNC/VSYNC timings and PIO clock setup; confirm monitor mode.

Input not working: confirm GPIO pulls and wiring; for serial, verify COM port and baud rate.

Performance hitches: use protothreads/timers for periodic work; avoid heavy work in tight pixel loops.

## Credits

Authors: Gabriel Seger & Sebastian [Last name]

Course: Cornell ECE4760 — Embedded Microcontrollers

Thanks: Prof. Hunter Adams and course staff; classmates for feedback and lab support
