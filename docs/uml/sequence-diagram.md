# Sequence Diagram – Smart Meter Monitoring

```text
Pulse Generator      Smart Meter Driver      Analytics Agent      CSV File
      |                      |                      |                 |
      |                      |                      |                 |
      |---- Write Pulse ---->|                      |                 |
      |                      |                      |                 |
      |                      |<---- Read Count ----|                 |
      |                      |                      |                 |
      |                      |---- Pulse Count --->|                 |
      |                      |                      |                 |
      |                      |                      | Calculate Energy|
      |                      |                      | Calculate Power |
      |                      |                      |                 |
      |                      |                      |---- Write ------>|
      |                      |                      |                 |
      |                      |                      |<--- Stored -----|
      |                      |                      |                 |
      |                      |                      |                 |
Reset Counter       Smart Meter Driver
      |                      |
      |------ ioctl -------->|
      |                      |
      |                      | Reset pulse_count
      |                      |
      |<------ success ------|
      |                      |
