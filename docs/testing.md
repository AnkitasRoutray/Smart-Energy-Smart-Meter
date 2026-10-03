# Testing and Validation

## Test 1: Driver Loading

Command:

sudo insmod driver/smart_meter.ko

Expected Result:

The smart-meter kernel module loads successfully.

Status: PASS

## Test 2: Device Creation

Command:

ls -l /dev/smartmeter

Expected Result:

The device node /dev/smartmeter exists.

Status: PASS

## Test 3: Pulse Counting

Command:

echo 10 | sudo tee /dev/smartmeter

Then:

cat /dev/smartmeter

Expected Result:

10

Status: PASS

## Test 4: Counter Reset

Command:

sudo ./app/reset_counter

Then:

cat /dev/smartmeter

Expected Result:

0

Status: PASS

## Test 5: Pulse Generation

Command:

sudo ./app/pulse_generator 1.0

Expected Result:

One pulse is generated approximately every second.

Status: PASS

## Test 6: Energy Calculation

The analytics agent converts pulse count into energy using:

Energy = Pulses / 1000

Example:

100 pulses = 0.100 kWh

Status: PASS

## Test 7: Power Estimation

The analytics agent calculates estimated power using pulse intervals.

At approximately one pulse per second:

Power ≈ 3.6 kW

Status: PASS

## Test 8: High Power Alert

Command:

sudo ./app/pulse_generator 0.5

Expected Result:

The simulated load increases and the analytics agent can report:

HIGH POWER ALERT

Status: PASS

## Test 9: CSV Logging

The analytics agent stores readings in:

data/energy_log.csv

Expected Result:

Timestamp, pulse count, energy, power and status are recorded.

Status: PASS

## Test 10: Complete System

The pulse generator, Linux device driver and analytics agent operate together.

Status: PASS
