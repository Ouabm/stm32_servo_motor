# stm32_servo_motor
This exemple is a DEVS-based example running on an STM32H743ZI2 development board. It models a rotation of a servo motor.

## Features

- Implemented using the DEVS formalism with Cadmium
- Runs on STM32H743ZI2 using ARM toolchain

## Prerequisites

- STM32H743ZI2 development board connected via USB
- a servo motor FS90R or SG90
- Cadmium simulato installed
- ARM toolchain: `gcc-arm-none-eabi`

## Installation

1. **Install the ARM GCC toolchain**:

```bash
sudo apt install gcc-arm-none-eabi
```
## Wiring and Running :

1. **Wirning**:

### Servo motor(PWM)

| Signal | Servo motor Pin | STM32 Pin Example | Notes                                 |
|--------|-----------------|-------------------|---------------------------------------|
| VCC    | V+              | 5V                | Requires stable 5V supply             |
| GND    | GND             | GND               | Common ground                         |
| PWM    | out             | PA0               | PWM output                            |


2. **Running**:

```bash
git clone https://github.com/Ouabm/stm32_servo_motor.git
```
  then
```bash
cd stm32_servo_motor/
```
  then
```bash
./Build_stm32
```

