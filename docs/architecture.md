# System Architecture

## 1. Overview

The Smart Energy Smart-Meter Pulse Counter & Analytics Agent follows a layered architecture consisting of a pulse generation layer, Linux kernel driver layer, and user-space analytics layer.

## 2. Architecture Flow

Virtual Pulse Generator
        |
        v
Linux Smart-Meter Device Driver
        |
        v
/dev/smartmeter
        |
        v
C++ Analytics Agent
        |
        +----> Energy Calculation
        |
        +----> Power Estimation
        |
        +----> High Power Detection
        |
        +----> CSV Data Logging

## 3. Components

### Pulse Generator

A C++ application that simulates electricity-meter pulses at configurable intervals.

Example:

1.0 second interval -> normal simulated load

0.5 second interval -> higher simulated load

### Linux Device Driver

The kernel module manages the smart-meter pulse counter and creates the device:

/dev/smartmeter

It supports:

- read operation
- write operation
- ioctl reset operation

### Analytics Agent

The C++ application reads the pulse count from the device driver and calculates:

- Energy consumption in kWh
- Estimated power in kW
- Power status

### Reset Utility

The reset utility communicates with the driver through ioctl and resets the pulse counter.

### CSV Logger

The analytics agent stores timestamped readings in:

data/energy_log.csv

## 4. Communication Model

User Space
    |
    | read/write/ioctl
    v
Kernel Space
    |
    v
Smart Meter Driver
    |
    v
Pulse Counter

This demonstrates communication between user-space applications and a Linux kernel module.

## 5. Energy Calculation

The simulated meter uses:

1000 pulses = 1 kWh

Therefore:

Energy = Pulse Count / 1000

## 6. Power Estimation

Power is estimated from the energy consumed during a measured time interval:

Power = Energy Difference × 3600 / Time in Seconds

## 7. Alert Mechanism

The system uses a configured power threshold of:

5 kW

If the calculated power exceeds this threshold, the analytics agent reports:

HIGH POWER ALERT

Otherwise:

NORMAL
