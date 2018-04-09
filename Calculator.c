#include <lpc17xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define RS_CTRL 0x08000000
#define EN_CTRL 0x10000000
#define DT_CTRL 0x07800000

//LCD Functions
void lcd_init(void);
void wr_cn(void);
void clr_all(void);
void clr_disponly(void);
void delay_lcd(unsigned int);
void lcd_com(void);
void wr_dn(void);
void lcd_data(void);
void clear_ports(void);
void lcd_puts(unsigned char*);

//Initialize keyboard
void keyboard_init(void);

//Evaluate numerics
void evaluate(char *, char , char*);
void dec2hex(unsigned int);
void dec2binary(unsigned int);
int facto(unsigned int n);
int fibo(unsigned int n);
int sumofcube(unsigned int n);

/*

---------------------KEYBOARD---------------------

Without Shift 	|	With Shift
				|
7	8	9	a   |	^	f   h   s
4	5	6	.	|   c   t   <   F	
1	2	3	-	|   *   V   T   L
S 	0	=	+	|   U   Y   I   /

a : Negative Input
S : Shift
^ : Power
f : Fibonacci
h : sin hx
s : sin 
c : cos 
t : tan 
< : Sum of cubes
F : Factorial 
V : Inverse
T : Square Root
L : Log
U : x SHIFT x
Y : Cube
I : x EQUAL x
*/


unsigned char SCAN_CODE[16] = { 0x11, 0x21, 0x41, 0x81, 0x12, 0x22, 0x42, 0x82, 0x14, 0x24, 0x44, 0x84, 0x18, 0x28, 0x48, 0x88 };
unsigned char ASCII_CODE[16] = { '7', '8', '9', 'a', '4', '5', '6', '.', '1', '2', '3', '-', 'S', '0', '=', '+' };
unsigned char ASCII_CODE_mode1[16] = { '^', 'f', 'h', 's', 'c', 't', '<', 'F', '*', 'V', 'T', 'L', 'U', 'Y', 'I', '/' };
unsigned char ASCII_CODE_mode2[16]=  {0};
// power, left shift, right shift, sin, cos, tan, mod, dec2binary, decimal2bcd
unsigned int i = 0,neg_flag=0,inf_flag=0;
unsigned int opr = 0, higher1 = 0,higher2=0;
float num1 = 0.0, num2 = 0.0, res = 0;        
int flagnum = 0;
unsigned char col, row, var, flag, key, *ptr;
unsigned long int var1, temp, temp3;
char hexadecimalnum[100];
void scan(void);
unsigned char msg[], inmsg[] = { 'I', 'n', 'p', 'u', 't',' ','i', 'm', 'p', 'r', 'o', 'p', 'e', 'r' };
//unsigned char infinity_msg[]={'I','N','F','I','N','I','T','Y'};
extern unsigned long int temp1, temp2;
unsigned long int temp1 = 0, temp2 = 0;
unsigned char op1[16], op2[16];
int pflag1=0, pflag2=0;
int count = 0;

int main(void)
{
    unsigned int i;

    SystemInit();
    SystemCoreClockUpdate();
	
    lcd_init();
	
    temp1 = 0x80;
    lcd_com();

    delay_lcd(30000);

    keyboard_init();

    while (1) {
        while (1) {
            for (row = 1; row < 5; row++) {
                if (row == 1)
                    var1 = 0x00000400;
                else if (row == 2)
                    var1 = 0x00000800;
                else if (row == 3)
                    var1 = 0x00001000;
                else if (row == 4)
                    var1 = 0x00002000;

                temp = var1;

                LPC_GPIO2->FIOCLR = 0x00003Cff;
                LPC_GPIO2->FIOSET = var1;

                flag = 0;
                scan();
            }
            break;
        }

        for (i = 0; i < 16; i++) {
				
            if (key == SCAN_CODE[i]) {
                key = ASCII_CODE[i];

                if (key == 'S') {
                    if (higher1 == 0)
                        higher1 = 1; 
										else 
											higher1 = 0;
										
										for (i=0;i<100000;i++);
										break;
                }
                else if (key == '=') {
                    evaluate((char *)op1, opr, (char *)op2);
                    num1 = 0;
                    num2 = 0;
                    flagnum = 0;
                    count = 0;
                    opr = 0;
                    break;
                }
                else if (higher1 == 1) {
										if(key=='R')
											if (higher2 == 0)
                        higher2 = 1; 
										else 
										{
											higher2 = 0;
										}
										
			
										if(key != 'S')
										{
										flagnum=1;
										
										}
										else 
											break;
											
										key = ASCII_CODE_mode1[i];
                    opr = ASCII_CODE_mode1[i];
			
											
											higher1=0;
                }
								else if(higher2 == 1)
								{
									
								}
                else if (isdigit(key) || key=='.' || key=='a')
				{
                    if (flagnum == 0) 
										{
											if(key=='a')
												pflag1=1;
											else
                        strcat((char *)op1, &key);
                    }
                    else
										{
											if(key=='a')
												pflag1=1;
											else
                        strcat((char *)op2, &key);
										}
                }
                else {
									if (higher1 == 0) {
                        opr = ASCII_CODE[i];

												// break;
									}
										flagnum = 1;
                }
                if (!(key == '=' || key == 'S')) 
									{
                    msg[count] = key;
                    clr_disponly();
                    lcd_puts(&msg[0]);
                    count++;
                    if (count == 15) {
                        clr_all();
                        clr_disponly();
                    }
                    delay_lcd(90000);
                    break;
                }
            }
        }
    }
}
unsigned char str[] = "";

void evaluate(char *op1, char opr, char *op2)
{
	  temp1 = 0xC0;
    lcd_com();
    delay_lcd(30000);
	
	num1 = atof(op1);
	num2= atof(op2);
  if(pflag1==1)
		num1*=-1;
	if(pflag2==1)
		num2*=-1;
	
    if (opr == '+') {
        res = num1 + num2;
    }
    if (opr == '-') {
        res = num1 - num2;
    }
    if (opr == '/') {
				if(num2==0)
				{
						neg_flag=1;
						lcd_puts(&inmsg[0]);
				}
      else
				res = num1 / num2;
    }
    if (opr == '*') {
        res = num1 * num2;
    }
    //  '^', 'f', 'h', 's', 'c', 't', '<', 'H', '1', '2', '3', '-', '*', '0', '=', '+' };
    if (opr == '^') {
        res = pow(num1,num2);
    }
    if (opr == 'f') {
        if(num1 <=0)
                {
                    neg_flag=1;
                    lcd_puts(&inmsg[0]);
                }
      else   res =fibo(num1);
      return;
    }
    if (opr == 'h') {
       res = sinh(num1);
    }
    if (opr == 's') {
        res = sin(num1);
    }
    if (opr == 'c') {
        res = cos(num1);
    }if (opr == 't') {
      res = tan(num1);
    }if (opr == '<') {
         if(num1 <=0)
                {
                    neg_flag=1;
                    lcd_puts(&inmsg[0]);
                }
        res = sumofcube(num1);
        return;
    }
    /*if (opr == 'I') {
			if(num1==0)
				{
						neg_flag=1;
						lcd_puts(&inmsg[0]);
				}
				else
				{
        res=1/num1;
				}
    } */
    if (opr == 'F') {
			if(num1 <=0)
				{
					neg_flag=1;
					lcd_puts(&inmsg[0]);
				}
       else res=facto(num1);
        return;
    }
		
		if (opr == 'V') {
			if(num1==0)
				{
						neg_flag=1;
						lcd_puts(&inmsg[0]);
				}
				else
				{
        res=1/num1;
				}
		}
		
		if(opr == 'T') {
			if(num1<=0)
				{
					neg_flag=1;
					lcd_puts(&inmsg[0]);
				}
				else
			res=sqrt(num1);
			return;
		}
		if (opr == 'L') {
				if(num1<=0)
				{
					neg_flag=1;
					lcd_puts(&inmsg[0]);
				}
			else	
			 res=log(num1);
			return;
		}
		
		if(opr =='Y')
		{
			res=num1*num1*num1;
			return;
		}
		
		

		if(neg_flag==0)
		{
    temp1 = 0xC0;
    lcd_com();
    delay_lcd(30000);
    sprintf(str, "Result: %f", res);
    lcd_puts(&str[0]);
		}
}
/*void dec2binary(unsigned int xx){
long num, decimal_num, remainder, base = 1, binary = 0, no_of_1s = 0;
decimal_num = xx;
while (num > 0)
   {
       remainder = num % 2;
         To count no.of 1s 
       if (remainder == 1)
       {
           no_of_1s++;
       }
       binary = binary + remainder * base;
       num = num / 2;
       base = base * 10;
   }

       temp1 = 0xC0;
       lcd_com();
       delay_lcd(30000);
       sprintf(str, "Result: %d", (int) binary);
       lcd_puts(&str[0]);
} */
int sumofcube(unsigned int n)
{
    int temp,sum=0;
    while(n!=0)
    {
        temp=n%10;
        sum+=(temp*temp*temp);
        n=n/10;
    }
    return sum;
}
int fibo(unsigned int n)
{
    if(n<=1)
        return n;
    return fibo(n-1)+fibo(n-2);
}
int facto(unsigned int n)
{
	if(n<=1)
		return 1;
	return n*facto(n-1);
}
/*void dec2hex(unsigned int xx){
  long quotient, remainder;
   int j = 0, k=0;
   i=0;

	
   quotient = (long) xx;

   while (quotient != 0)
   {
       remainder = quotient % 16;
       if (remainder < 10)
           hexadecimalnum[j++] = 48 + remainder;
       else
           hexadecimalnum[j++] = 55 + remainder;
       quotient = quotient / 16;
   }


					temp1 = 0xC0;
          lcd_com();
          delay_lcd(30000);
          sprintf(str, "Res234ult: ");
	   lcd_puts(&str[0]);

   // display integer into character
   for (i = j; i >= 0; i--) {
    str[8+k++] = hexadecimalnum[i];
  }
	str [8+k] = '\0';
   lcd_puts(&str[0]);
} */
void scan(void)
{
    unsigned long temp3;

    temp3 = LPC_GPIO1->FIOPIN;
    temp3 &= 0x07800000;
    if (temp3 != 0x00000000) {
        for (i = 0; i < 500; i++)
            ;
        temp3 = LPC_GPIO1->FIOPIN;
        temp3 &= 0x07800000;
        if (temp3 != 0x00000000) {
            flag = 1;
            temp3 >>= 19;
            temp >>= 10;
            key = temp3 | temp;
        }
    }
}

void keyboard_init()
{
    LPC_PINCON->PINSEL3 &= 0xFFC03FFF; //P1.23 to P1.26 MADE GPIO
    LPC_PINCON->PINSEL3 &= 0xF00FFFFF; //P2.10 t P2.13 made GPIO
    LPC_GPIO2->FIODIR |= 0x00003fff; //made output P2.10 to P2.13 (rows)
    LPC_GPIO1->FIODIR &= 0xF87FFFFF; //made input P1.23 to P1.26 (cols)
}
void lcd_init()
{
    LPC_PINCON->PINSEL1 &= 0xFC003FFF;
    LPC_GPIO0->FIODIR |= DT_CTRL;
    LPC_GPIO0->FIODIR |= RS_CTRL;
    LPC_GPIO0->FIODIR |= EN_CTRL;
    clear_ports();
    delay_lcd(32000);

    temp2 = 0x30 << 19; // return home
    wr_cn();
    delay_lcd(30000);

    temp2 = 0x30 << 19;
    wr_cn();
    delay_lcd(30000);

    temp2 = 0x30 << 19;
    wr_cn();
    delay_lcd(30000);

    temp2 = 0x20 << 19; // return home
    wr_cn();
    delay_lcd(30000);

    temp1 = 0x2A;
    lcd_com(); // function set
    delay_lcd(30000);

    temp1 = 0x0C; // display onpff
    lcd_com();
    delay_lcd(30000);

    temp1 = 0x06; // entry mode set
    lcd_com();
    delay_lcd(30000);

    temp1 = 0x01; // clear display
    lcd_com();
    delay_lcd(10000);

    temp1 = 0x80; // set dd ram address to 80
    lcd_com();
    delay_lcd(30000);
    return;
}

void lcd_com(void)
{
    temp2 = temp1 & 0xf0;
    temp2 = temp2 << 19;
    wr_cn();
    temp2 = temp1 & 0x0f;
    temp2 = temp2 << 23;
    wr_cn();
    delay_lcd(30000);
    return;
}

void wr_cn(void)
{
    clear_ports();
    LPC_GPIO0->FIOPIN = temp2;
    LPC_GPIO0->FIOCLR = RS_CTRL;
    LPC_GPIO0->FIOSET = EN_CTRL;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
    return;
}

void lcd_data(void)
{
    temp2 = temp1 & 0xf0;
    temp2 = temp2 << 19;
    wr_dn();
    temp2 = temp1 & 0x0f;
    temp2 = temp2 << 23;
    wr_dn();
    delay_lcd(30000);
    return;
}

void wr_dn(void)
{
    clear_ports();
    LPC_GPIO0->FIOPIN = temp2;
    LPC_GPIO0->FIOSET = RS_CTRL;
    LPC_GPIO0->FIOSET = EN_CTRL;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
    return;
}

void delay_lcd(unsigned int delay_time)
{
    unsigned int t;
    for(t=0;t<delay_time;t++);
    return;
}

void clr_all(void)
{
    flagnum = 0;

    num1 = 0;
    num2 = 0;
    opr = 0;
    count = 0;
    memset(msg, 0, 255);
    return;
}
void clr_disponly(void)
{

    temp1 = 0x01;
    lcd_com();
    delay_lcd(10000);
    return;
}
void clear_ports(void)
{
    LPC_GPIO0->FIOCLR = DT_CTRL;
    LPC_GPIO0->FIOCLR = RS_CTRL;
    LPC_GPIO0->FIOCLR = EN_CTRL;
    return;
}

void lcd_puts(unsigned char* buf1)
{
    i = 0;
    while (buf1[i] != '\0') {
        temp1 = buf1[i];
        lcd_data();
        i++;
        if (i == 16) {
            break;
        }
    }
    return;
}
