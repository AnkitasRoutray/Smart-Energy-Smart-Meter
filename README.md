# Smart Energy Smart-Meter Pulse Counter & Analytics Agent

## 1. Project Overview

The Smart Energy Smart-Meter Pulse Counter & Analytics Agent is a Linux-based smart energy monitoring system developed using C and C++.

The system simulates electricity meter pulses, captures them using a Linux character device driver, calculates energy consumption and estimated power, detects high-power conditions, and stores readings in CSV format.

## 2. Objectives

- Implement a Linux device driver for pulse counting.
- Create a virtual smart-meter pulse generator.
- Calculate energy consumption from meter pulses.
- Estimate power consumption from pulse intervals.
- Detect high-power conditions.
- Store energy readings in CSV format.
- Demonstrate Linux device-driver and user-space communication.

## 3. Technology Used

- Linux / Ubuntu
- C
- C++
- Linux Kernel Module
- Linux Device Driver
- Makefile
- Git / GitHub
- CSV Data Logging

## 4. System Architecture

Virtual Pulse Generator
        |
        v
Linux Smart-Meter Driver
        |
        v
/dev/smartmeter
        |
        v
C++ Analytics Agent
        |
        +------> Energy Calculation
        |
        +------> Power Estimation
        |
        +------> High Power Alert
        |
        +------> CSV Logging

## 5. Meter Specification

The project uses the following simulated meter constant:

1000 pulses = 1 kWh

Therefore:

Energy (kWh) = Pulse Count / 1000

Power is estimated using the change in energy over the elapsed time.

## 6. Project Structure

smart-meter/
|
|-- driver/
|   |-- smart_meter.c
|   |-- Makefile
|
|-- app/
|   |-- pulse_generator.cpp
|   |-- analytics.cpp
|   |-- reset_counter.cpp
|
|-- include/
|   |-- smartmeter_ioctl.h
|
|-- data/
|
|-- docs/
|
|-- scripts/
|
|-- Makefile
|-- .gitignore
|-- README.md

## 7. Main Components

### Linux Device Driver

The kernel module creates:

/dev/smartmeter

It maintains the pulse counter and provides read, write and ioctl operations.

### Pulse Generator

The C++ pulse generator simulates electricity meter pulses.

Example:

sudo ./app/pulse_generator 1.0

This generates one pulse every second.

### Analytics Agent

The analytics application reads the pulse count and calculates:

- Total energy
- Estimated power
- Power status
- Timestamp

### Reset Utility

The reset utility uses ioctl to reset the meter counter.

Example:

sudo ./app/reset_counter

## 8. Build

From the project root:

make

To clean the project:

make clean

## 9. Driver Setup

Build the project:

make

Load the driver:

sudo insmod driver/smart_meter.ko

Check the device:

ls -l /dev/smartmeter

## 10. Running the System

Reset the meter:

sudo ./app/reset_counter

Start the pulse generator:

sudo ./app/pulse_generator 1.0

In another terminal start analytics:

sudo ./app/analytics

## 11. High Power Demonstration

The pulse generator supports configurable pulse intervals.

Normal load:

sudo ./app/pulse_generator 1.0

Higher load:

sudo ./app/pulse_generator 0.5

The analytics agent compares the estimated power with the configured 5 kW limit.

If the limit is exceeded:

HIGH POWER ALERT!

## 12. Data Logging

Energy readings are stored in:

data/energy_log.csv

The CSV contains:

Time,Pulses,Energy_kWh,Power_kW,Status

## 13. Linux Device Driver Concepts Demonstrated

- Linux Kernel Module
- Character/Misc Device
- Device Registration
- File Operations
- read()
- write()
- ioctl()
- User-space / Kernel-space communication
- Atomic variables
- Device node
- Kernel logging

## 14. Future Improvements

- Real electricity meter sensor integration
- Hardware pulse input using GPIO
- Web-based monitoring dashboard
- Database integration
- Advanced anomaly detection
- Multiple appliance monitoring

## 15. Project Outcome

The project demonstrates a complete Linux-based smart-meter simulation pipeline from pulse generation and kernel-level device handling to energy analytics, alert generation and data logging.
