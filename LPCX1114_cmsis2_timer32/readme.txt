LPCX1114_cmsis2_timer32
=======================
This project contains a LED flashing Timer32 example for the LPCXpresso
board mounted with an LPC1114 Cortex-M0 part.

When downloaded to the board and executed, LED2 will be illuminated.
The state of LED2 will then toggle regularly, timed using the LPC11xx's
32bit timer.

The project makes use of code from the following library projects:
- CMSISv2p00_LPC11xx : for CMSIS 2.00 files relevant to LPC11xx
- LPC11xx_cmsis2_Lib : for LPC11xx peripheral driver files

These two library projects must exist in the same workspace in order
for the project to successfully build.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.
