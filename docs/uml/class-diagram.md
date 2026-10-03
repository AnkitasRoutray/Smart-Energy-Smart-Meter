# Class Diagram – Smart Energy Smart-Meter

```text
+---------------------------+
|      PulseGenerator       |
+---------------------------+
| - device                  |
| - interval                |
+---------------------------+
| + generatePulse()         |
| + run()                   |
+-------------+-------------+
              |
              | writes pulse
              v
+---------------------------+
|     SmartMeterDriver      |
+---------------------------+
| - pulse_count             |
+---------------------------+
| + read()                  |
| + write()                 |
| + ioctl()                 |
| + init()                  |
| + exit()                  |
+-------------+-------------+
              |
              | pulse data
              v
+---------------------------+
|      AnalyticsAgent       |
+---------------------------+
| - previous_pulses         |
| - previous_time           |
| - power_limit             |
+---------------------------+
| + readPulses()            |
| + calculateEnergy()       |
| + calculatePower()        |
| + checkAlert()            |
| + logData()               |
+---------------------------+

+---------------------------+
|      ResetCounter         |
+---------------------------+
| + reset()                 |
+-------------+-------------+
              |
              | ioctl()
              v
       SmartMeterDriver
