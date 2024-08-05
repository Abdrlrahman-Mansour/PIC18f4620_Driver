# PIC18F4620 MCU Implementation

---

### Overview


###### This project demonstrates the implementation of various peripherals and modules using the PIC18F4620 microcontroller. The project is organized into two main layers: the ECU (Electronic Control Unit) Layer and the MCAL (Microcontroller Abstraction Layer). Each layer contains multiple modules that provide functionality for different hardware components and communication protocols.

### Directory Structure
+ ECU_Layer
  + 7_segment
  + button
  + dc_motor
  + keypad
  + lcd
  + led
  + relay
+ MCAL_Layer
  + ADC
  + CCP
  + EEPROM
  + GPIO
  + I2C
  + interrupt
  + SPI
  + TIMER0
  + TIMER1
  + TIMER2
  + TIMER3
  + USART

***
 ### ECU Layer
 The ECU layer contains drivers for various hardware components used in embedded systems.

 + 7_segment: Driver for 7-segment displays.
  + button: Driver for push-button inputs.
  + dc_motor: Driver for DC motor control.
  + keypad: Driver for keypad input.
  + lcd: Driver for LCD display modules.
  + led: Driver for controlling LEDs.
  + relay: Driver for relay control.

