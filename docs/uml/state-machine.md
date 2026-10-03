# State Machine Diagram – Smart Meter

```text
                 +----------+
                 |  STOPPED |
                 +----+-----+
                      |
                 Driver loaded
                      |
                      v
                 +----------+
                 |  READY   |
                 +----+-----+
                      |
                 Pulse received
                      |
                      v
                 +----------+
                 | COUNTING |
                 +----+-----+
                      |
                 Reading requested
                      |
                      v
                 +----------+
                 | ANALYZING|
                 +----+-----+
                      |
                Calculate power
                      |
              +-------+-------+
              |               |
          <= 5 kW          > 5 kW
              |               |
              v               v
        +-----------+   +--------------+
        |  NORMAL   |   | HIGH POWER   |
        +-----------+   |    ALERT     |
        +-----+-----+   +------+-------+
              |                |
              +-------+--------+
                      |
                 Continue monitoring
                      |
                      v
                 +----------+
                 | COUNTING |
                 +----------+

Reset
  |
  v
READY
