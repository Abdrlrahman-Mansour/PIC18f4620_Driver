# PIC18F4620 MCU Implementation

---

### Overview


###### This project demonstrates the implementation of various peripherals and modules using the PIC18F4620 microcontroller. The project is organized into two main layers: the ECU (Electronic Control Unit) Layer and the MCAL (Microcontroller Abstraction Layer). Each layer contains multiple modules that provide functionality for different hardware components and communication protocols.
---
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
___


 ### ECU Layer
 The ECU layer contains drivers for various hardware components used in embedded systems.

 + 7_segment: Driver for 7-segment displays.
  + button: Driver for push-button inputs.
  + dc_motor: Driver for DC motor control.
  + keypad: Driver for keypad input.
  + lcd: Driver for LCD display modules.
  + led: Driver for controlling LEDs.
  + relay: Driver for relay control.
***
 ### MCAL Layer
The MCAL layer provides abstraction for the microcontroller's hardware peripherals. This layer allows easy access and control of the microcontroller's built-in functionalities.

  + ADC: Analog-to-Digital Converter driver.
  + CCP: Capture/Compare/PWM driver.
  + EEPROM: Driver for internal EEPROM memory.
  + GPIO: General Purpose Input/Output driver.
  + I2C: Inter-Integrated Circuit communication driver.
  + interrupt: Driver for handling interrupts.
  + SPI: Serial Peripheral Interface communication driver.
  + TIMER0: Timer0 module driver.
  + TIMER1: Timer1 module driver.
  + TIMER2: Timer2 module driver.
  + TIMER3: Timer3 module driver.
  + USART: Universal Synchronous/Asynchronous Receiver/Transmitter driver.
  ----
