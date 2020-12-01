# Ethernet Motor Supervisors based on cortex m4 : EMS4

Author: Giorgio Zini

## Main characteristics

Microcontroller based module for managing several communication channels in motor-control application.
Features:
- Microcontroller STM32F407VGT6: Arm-M4, 168MHz, 1MB FLASH, 192KB SRAM, 100 pin TQFP
- Ethernet: 10/100BASE+T, dual port physical switch/hub
- CAN bus 2.0B: 2 channel
- SPI bus: 6 channel
- Accelerometer LIS331DLH, Gyroscope L3G4200D
- Power supply: 9VDC-56VDC

## Revisions

Sch_Rev	PCB_Rev	BOM_Rev
0	0	A	Feb. 1, 2012.	First release.

1	1	B	May 22, 2012.	Corrected ~EXTIRQn routing error.
					The PCB solder paste stencil is unchanged.
                                        NOTE: PCB release 1 has never been produced.

2	2	A	Oct.26, 2012.	Added an external 50MHz oscillator to the microcontroller
                                        OSC_IN signal and to the ETH_REFCLK signal.
                                        Assigned peripheral I2C3 to the ethernet physical.
                                        The following ports have changed:
                                        - PH0 now is the HSE oscillator input (50MHz).
                                        - PH1 now is ~ETH_RST output (GPIO). The firmware should
                                          pulse ~ETH_RST at least 10ms low to initialize the
                                          ethernet physical.
                                        - PB2 now is ETH_SLV output (GPIO). The firmware should set
                                          ETH_SLV high before pulling ~ETH_RST high to initialize
                                          the ethernet physical as an I2C-bus slave.
                                        - Port PA8 now is I2C3_SCL (function MCO1 not possible)
                                        - Port PA9 now is I2C3_SDA (function MCO2 not possible)
                                        If the microcontroller fails to initialize the ethernet
                                        physical as an I2C slave, it powers up as a master and it
                                        links to the ethernet bus with the default configuration.

                                        ATTENTION: All modules with PCB rev. 0 were updated with an
                                        external 50MHz oscillator connected to PH0 port, but the
                                        ~ETH_RST signal is still driven by PB2 port and the ethernet
                                        physical is still linked to the I2C1 peripheral.
                                        The firmware can tell the PCB revision by reading the serial
                                        number of the module: beginning with s/n 1111 all the
                                        modules use PCB rev. 2.

3	2	A	Mar.14, 2013	Corrected R147/R148 schematics values. Now they are:
					R147: do not mount
					R148: 0R/0402 (jumper)
                                        This errata/corrige does not impact on the firmware and
                                        usage of the module
