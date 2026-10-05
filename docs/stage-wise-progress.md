# Stage-Wise Project Progress & Evidence

## Stage 1 – Project Introduction

### Objective
Develop a Smart Energy Smart-Meter Pulse Counter and Analytics Agent using C/C++, Linux and Linux Device Driver concepts.

### Problem
Traditional energy meters provide cumulative readings but do not demonstrate how pulse-based energy measurement can interact with a software system at the operating-system level.

### Proposed Solution
The project simulates a smart energy meter using a Linux device driver. Virtual pulses are generated from a C++ application, counted by the kernel driver, and analyzed by a C++ analytics agent.

### Expected Outcome
- Pulse counting through a Linux device driver
- Energy calculation
- Power estimation
- High-power alert
- CSV data logging
- User-space and kernel-space communication

### Status
Completed.

---

## Stage 2 – Requirements & Development Plan

### Functional Requirements
- Generate virtual meter pulses
- Count pulses using the Linux device driver
- Read pulse count from `/dev/smartmeter`
- Reset the counter using ioctl
- Calculate energy consumption
- Estimate power consumption
- Detect high-power conditions
- Display monitoring information
- Store readings in CSV format

### Non-Functional Requirements
- Linux-based implementation
- C for kernel driver development
- C++ for user-space applications
- Simple and maintainable code
- Reliable pulse counting
- Git-based version control
- Proper project documentation

### Meter Specification
- 1000 pulses = 1 kWh
- Power is estimated using pulse intervals
- High-power threshold = 5 kW

### Status
Completed.

---

## Stage 3 – System Design & Architecture

### Architecture

```text
Virtual Pulse Generator
          |
          v
Linux Device Driver
          |
          v
/dev/smartmeter
          |
          v
C++ Analytics Agent
          |
     +----+----+
     |         |
     v         v
 Energy      Power
Calculation  Calculation
     |         |
     +----+----+
          |
          v
    Alert Detection
          |
          v
     CSV Logging

## Stage 4 – Initial Implementation & Prototype

### Objective
Implement the core components of the Smart Energy Smart-Meter system and develop a working prototype.

### Linux Device Driver Implementation
The Linux kernel module was developed in C with the following functionality:

- Registered a virtual smart-meter device.
- Created the `/dev/smartmeter` device node.
- Implemented device read operation.
- Implemented device write operation.
- Maintained the pulse counter using `atomic64_t`.
- Implemented an ioctl command for resetting the pulse counter.
- Added kernel logging using `pr_info()` and `pr_err()`.

### User-Space Applications

#### 1. Pulse Generator
A C++ application was developed to simulate meter pulses.

Functions:
- Generates virtual energy-meter pulses.
- Sends pulses to `/dev/smartmeter`.
- Supports configurable pulse intervals.
- Simulates different energy consumption levels.

Example:

```text
1 pulse/second  → approximately 3.6 kW
1 pulse/0.5 sec → approximately 7.2 kW

---

## Stage 5 – Testing, Integration & Improvement

### Objective
Test the individual components and the complete integrated system, identify issues, fix them, and verify reliable operation.

### Unit and Component Testing

The following components were tested independently:

- Linux device driver
- `/dev/smartmeter` device
- Pulse counter
- Pulse generator
- Analytics agent
- Reset utility
- CSV logging

### Integration Testing

The complete data flow was tested:

```text
Pulse Generator
       ↓
Linux Device Driver
       ↓
/dev/smartmeter
       ↓
Analytics Agent
       ↓
Energy/Power Calculation
       ↓
Alert Detection
       ↓
CSV Logging

# Stage 6 – Final Implementation & Presentation

### Objective
Finalize the Smart Energy Smart-Meter system, complete the documentation, verify the final implementation and prepare the project for demonstration and evaluation.

### Final System

The completed system consists of:

```text
+-------------------------+
|   C++ Pulse Generator   |
+-----------+-------------+
            |
            v
+-------------------------+
|  Linux Device Driver    |
|   smart_meter.ko        |
+-----------+-------------+
            |
            v
+-------------------------+
|    /dev/smartmeter      |
+-----------+-------------+
            |
            v
+-------------------------+
|   C++ Analytics Agent   |
+-----------+-------------+
            |
      +-----+-----+
      |           |
      v           v
 Energy        Power
Calculation   Estimation
      |           |
      +-----+-----+
            |
            v
+-------------------------+
|   High Power Detection  |
+-----------+-------------+
            |
            v
+-------------------------+
|      CSV Logging        |
+-------------------------+
