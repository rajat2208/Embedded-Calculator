# Embedded-Calculator
Custom Calculator on NXP Microcontroller with 24 functionalities including scientific functions using Assembly Language (ARM)

The calculator can be used on a **Customized Embedded ARM Cortex LPC 1768 Kit**. The embedded C code can be used to compute a number of mathematical operations based on the input from the user using the keyboard on the kit. The input and output values are displayed on the LCD screen of the kit. 

The working of the **keyboard** is as follows:</br>

The 4X4 keyboard on the kit is used to provide the input and use the necessary computation to be done. By default, the keyboard will be in the "Without Shift" mode. Pressing "S" would enable the "With Shift" mode. The _"S" & "U"_ as well as the _"=" & "I"_ buttons perform teh same operation irrespective of whether Shift is enbaled or not.</br></br>  


-----------------------------KEYBOARD-----------------------------</br>

Without Shift&nbsp;&nbsp;&nbsp;&nbsp;   	|&nbsp;&nbsp;&nbsp;&nbsp;    		With Shift</br>
				|</br>
7&nbsp;&nbsp;&nbsp;&nbsp;	8&nbsp;&nbsp;&nbsp;&nbsp;	9&nbsp;&nbsp;&nbsp;&nbsp;	a&nbsp;&nbsp;&nbsp;&nbsp;	|&nbsp;&nbsp;&nbsp;&nbsp;   	^&nbsp;&nbsp;&nbsp;&nbsp;	f&nbsp;&nbsp;&nbsp;&nbsp; 	h&nbsp;&nbsp;&nbsp;&nbsp;   	s</br>
4	5	6	.	|   	c   	t   	<   	F</br>	
1	2	3	-	|   	*   	V   	T   	L</br>
S	0	=	+	|	U   	Y   	I   	/</br>
</br>
</br>
a : Negative Input</br>
S : Shift button</br>
^ : Power</br>
f : Fibonacci</br>
h : sin hx</br>
s : sin x</br>
c : cos x</br>
t : tan x</br>
< : Sum of cubes</br>
F : Factorial </br>
V : Inverse</br>
T : Square Root</br>
L : Log</br>
U : Shift button</br>
Y : Cube</br>
I : Equals button</br>

The LCD screen will also display error messages when the *input is improper* or when the output is *infinity*.</br>

*The keyboard confiuration on the kit is as follows:</br>
	P1.23 to P1.26 made GPIO</br>
    	P2.10 t P2.13 made GPIO</br>
    	P2.10 to P2.13 made output(rows)</br>
    	P1.23 to P1.26 made input(cols)</br>


