
### SMARTLAB GUARDIAN: SECURE AND AUTOMATED LABORATORY CONTROL SYSTEM

## 1. Project Overview

SmartLab Guardian is an embedded-based laboratory security and automation system developed using the LPC2148 ARM7 microcontroller. The system provides password-based authentication, RTC-based laboratory access control, infrared remote-based device operation, and emergency interrupt handling.

The main objective is to improve laboratory security, automate device control, and restrict laboratory operations according to predefined working hours.

## 2. Key Features

- **Password Authentication:** Provides keypad-based password verification before accessing the system.
- **RTC-Based Access Control:** Allows laboratory operation only during configured working hours.
- **IR Remote Control:** Uses a TSOP receiver to decode RC5 infrared signals and control devices remotely.
- **Device Automation:** Controls two LEDs and a buzzer based on received commands.
- **Keypad Interface:** Allows users to enter passwords and configure system settings.
- **LCD Display:** Displays authentication messages, device status, time, date, and system information.
- **External Interrupt Handling:** Supports emergency interrupt events and corresponding system responses.
- **Configuration Menu:** Allows modification of RTC time, date, and laboratory operating schedule.

## 3. Hardware Requirements

- LPC2148 ARM7 Development Board
- 16x2 LCD Display
- 4x4 Matrix Keypad
- TSOP Infrared Receiver
- IR Remote Control
- LEDs
- Buzzer
- External Interrupt Switches
- Power Supply

## 4. Software Requirements

- Embedded C
- Keil µVision IDE
- Flash Magic
- LPC2148 Device Support
- ARM7 Toolchain

## 5. Technologies Used

- ARM7 Architecture
- GPIO Interfacing
- Real-Time Clock (RTC)
- UART / Embedded Peripheral Concepts
- External Interrupts
- Matrix Keypad Interfacing
- LCD Interfacing
- Infrared RC5 Protocol

## 6. System Working

1. The microcontroller initialises the LCD, keypad, LEDs, RTC, and external interrupts.
2. The user enters the password through the keypad.
3. After successful authentication, the system checks the configured laboratory operating time.
4. If the laboratory is open, the system enables device-control operations.
5. The TSOP receiver receives infrared signals from the remote and decodes the RC5 commands.
6. Based on the received commands, the system controls the connected output devices.
7. The configuration menu allows authorised users to modify time, date, and laboratory schedules.
8. External interrupts handle emergency events.
9. When laboratory hours expire, the system switches off the LEDs and restricts normal device operation.

## 7. Project Structure

| File | Description |
|---|---|
| pmain.c | Main application control |
| pLCD.c | LCD driver implementation |
| pkeypad.c | Keypad scanning and input |
| ppassword_check.c | Password authentication |
| pdevice_control.c | LED and buzzer control |
| prtc.c | RTC operations |
| rtc_time_date1.c | Time, date and schedule editing |
| pmenu.c | Configuration menu |
| pexternalswitches.c | External interrupt handling |
| tsop_rc5_delay_main1.c | TSOP receiver and RC5 decoding |
| pdelay.c | Software delay functions |
| Header files | Declarations, macros and hardware configurations |


## Hardware Setup
The prototype is implemented on an ARM7 development board with an LCD, matrix keypad, TSOP receiver and connected output devices.

<img width="1152" height="648" alt="WhatsApp Image 2026-11-24 at 11 38 06 PM" src="https://github.com/user-attachments/assets/bee8b5d0-4ac7-4521-b807-6c9e6fb4a414" />


## Demonstration Screenshots

### 1. Password Authentication
The LCD prompts the user to enter the access password. Entered digits are masked on the display.

<img width="1156" height="867" alt="WhatsApp Image 2026-11-24 at 11 38 07 PM" src="https://github.com/user-attachments/assets/8b4aaa77-ce8f-4212-a0ad-aa4446f94aa9" />


### 2. Date Configuration
The configuration menu includes options for editing the date and other RTC settings.

<img width="867" height="1156" alt="WhatsApp Image 2026-11-24 at 11 38 14 PM" src="https://github.com/user-attachments/assets/67560ec2-ffc2-4dae-8f19-34d9f9a19f4d" />


### 3. Laboratory Schedule Configuration
The menu provides options to configure the laboratory ON time and OFF time.

<img width="867" height="1156" alt="WhatsApp Image 2026-11-24 at 11 38 05 PM" src="https://github.com/user-attachments/assets/ffb76148-6272-4195-9fc5-ae360c0d1c7a" />


### 4. Main Configuration Menu
The user can select time, date, laboratory schedule settings, or exit the menu.

<img width="1156" height="867" alt="WhatsApp Image 2026-11-24 at 11 38 06 PM" src="https://github.com/user-attachments/assets/9c043427-825f-40e3-83da-fe55e28171a5" />


## 8. Advantages

- Improves laboratory security.
- Provides controlled access to laboratory devices.
- Reduces unnecessary power consumption.
- Supports remote device operation.
- Provides configurable laboratory operating hours.
- Integrates multiple embedded peripherals into one system.

## 9. Future Enhancements

- Biometric authentication.
- IoT-based remote monitoring.
- Mobile application integration.
- Cloud-based laboratory activity logging.
- Real-time alerts and notifications.
- Individual device usage monitoring.

## 10. Conclusion

SmartLab Guardian demonstrates the integration of ARM7 microcontroller peripherals to develop a laboratory security and automation system. By combining authentication, RTC scheduling, infrared communication, device control, and interrupt handling, the project provides a structured approach to laboratory access management and automation.

---

**Project Name:** SmartLab Guardian  
**Microcontroller:** LPC2148 (ARM7)  
**Programming Language:** Embedded C  
**Development Environment:** Keil µVision
