Schematic changes between PCB Rev 1 and PCB Rev 2

1) The MCO2 signal cannot drive the ethernet reference clock (ETH_REFCLK)
   because the internal PLLs are affected by excessive jitter. An external
   oscillator has been implemented:
   - Removed XT1, R8, R33, C4, C5 and C14
   - Added U14 and C84

2) The port PH1 has been connected to the ~ETH_RST signal and the new signal
   ETH_SLV has been connected to port PB2. An indipendent power-on circuit has
   been added to allow the KSZ8893MBL to power-up without the microcontroller
   intervention.
   - Added C85, D5, R149, R150 and R151

3) The ethernet protection networks DZ1 and DZ2 have been removed because they
   could cause distortion to the signals.
   - Removed DZ1, DZ2, R49, R52.

4) The I2C bus that drives the Ethernet PHY and the MEMS has been separated
   from the I2C bus that drives the E2PROM memory. Now the E2PROM memory is
   controlled by I2C3
   - Removed TP8
   - Added R152 and R153
