# Embedded-Calculator
Custom Calculator on NXP Microcontroller with 24 functionalities including scientific functions using Assembly Language (ARM)

The calculator can be used on a **Customized Embedded ARM Cortex LPC 1768 Kit**. The embedded C code can be used to compute a number of mathematical operations based on the input from the user using the keyboard on the kit. The input and output values are displayed on the LCD screen of the kit. 

The working of the **keyboard** is as follows:

The 4X4keyboard on the kit is used to provide the input and use the necessary computation to be done. By default, the keyboard will be in the "Without Shift" mode. Pressing "S" would enable the "With Shift" mode. The _"S" & "U"_ as well as the _"=" & "I"_ buttons perform teh same operation irrespective of whether Shift is enbaled or not.  

---------------------KEYBOARD---------------------

Without Shift   |    With Shift
				        |
7	  8	  9	  a   |	  ^	  f   h   s
4	  5	  6	  .	  |   c   t   <   F	
1	  2	  3	  -	  |   *   V   T   L
S 	0	  =	  +	  |   U   Y   I   /

a : Negative Input
S : Shift button
^ : Power
f : Fibonacci
h : sin hx
s : sin x
c : cos x
t : tan x
< : Sum of cubes
F : Factorial 
V : Inverse
T : Square Root
L : Log
U : Shift button
Y : Cube
I : Equals button

The LCD screen will also display error messages when the *input is improper* or when the output is *infinity*.

##The keyboard confiuration on the kit is as follows:
P1.23 to P1.26 MADE GPIO
    LPC_PINCON->PINSEL3 &= 0xF00FFFFF; //P2.10 t P2.13 made GPIO
    LPC_GPIO2->FIODIR |= 0x00003fff; //made output P2.10 to P2.13 (rows)
    LPC_GPIO1->FIODIR &= 0xF87FFFFF; //made input P1.23 to P1.26 (cols)


