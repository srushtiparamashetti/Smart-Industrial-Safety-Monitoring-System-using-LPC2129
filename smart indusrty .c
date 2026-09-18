#include <LPC21xx.H>
#include"header.h"
#include <stdio.h>

#define c  ((IOPIN0>>14)&1)
#define c1 ((IOPIN0>>15)&1)
#define Green 1<<17
#define Red 1<<18


int main(){
unsigned int a_value=0;
float vout=0,temp=0;
char a[20];

IODIR0=3<<17;
lcd_init();
uart_init(9600);
adc_init();

	while(1){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
			uart_str("\r\r--:Tempurature:--\r\n");
			a_value=adc_read(1);
			vout=(a_value*3.3)/1023;
			temp=(vout-0.5)/0.01;		 	
			sprintf(a,"temp:%.2f\r\n",temp);
			uart_str(a);
			lcd_str("Temp:");
			lcd_int(temp);
			//============ FIR =================
			if(c==0){
			 	sprintf(a,"fire=YES\r\n");
				uart_str(a);
			}
			else{
				sprintf(a,"fire=No\r\n");
			  	uart_str(a);
			}
			//============ PIR =================
			if(c1==1){
				sprintf(a,"Worker:Yes\r\n");
				uart_str(a);
			}
			else{
				sprintf(a,"Worker:No\r\n");
				uart_str(a);
			}
			//============ STATUS =================
			lcd_cmd(0xc0);
			if((c1==1) || (c==0)){
				sprintf(a,"Status:Danger\r\nLED status:Red\r\n");
				uart_str(a);
				IOSET0=Green;
				IOCLR0=Red;
				lcd_str("Status:Danger");
			}
			else{
				sprintf(a,"Status:SAFE\r\nLED status:Green\r\n");
				uart_str(a);
				IOSET0=Red;
				IOCLR0=Green;
				lcd_str("Status:SAFE");
			}
			delay_ms(1000);		
	}
}
