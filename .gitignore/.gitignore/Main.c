



#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "time.h"


#define LCDPORT                  GPIO_PORTB_BASE
#define LCDPORTENABLE    SYSCTL_PERIPH_GPIOB
#define RS                               GPIO_PIN_0
#define E                                GPIO_PIN_1
#define D4                               GPIO_PIN_4
#define D5                               GPIO_PIN_5
#define D6                               GPIO_PIN_6
#define D7                               GPIO_PIN_7


void Lcd_Komut(unsigned char);  //Lcd ye komut göndermeye yarar
void Lcd_Temizle(void);                 //Lcd ekranını temizler
void Lcd_Puts(char*);                   //String ifade yazdırır
void Lcd_Goto(int,char);               //Kursorü istenilen yere gönderir
void Lcd_init(void);                    //Lcd başlangıç ayarları
void Lcd_Putch(unsigned char);  //Tek karekter yazdırır


void init_port_E() {
   volatile unsigned long tmp; // bu degisken gecikme yapmak icin gerekli
   SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;   // 1) E portunun osilatörünü etkinlestir
   tmp = SYSCTL_RCGCGPIO_R;    	// allow time for clock to start
   GPIO_PORTE_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port E
   GPIO_PORTE_CR_R = 0x3F;         // allow changes to PE5-0 //PE5-0 degisikliklerine izin ver
                                   // only PE0 needs to be unlocked, other bits can't be locked
    			 // Sadece PE0 kilidinin açilmasi gerekir, diger bitler kilitlenemez
   GPIO_PORTE_AMSEL_R = 0x00;    	// 3) disable analog on PE //PE'de analog devre disi birak
   GPIO_PORTE_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PE4-0
   GPIO_PORTE_DIR_R = 0x00;      	// 5) PE4,PE5 in, PE3-0 out
   GPIO_PORTE_AFSEL_R = 0x00;    	// 6) disable alt funct on PE7-0
   GPIO_PORTE_PUR_R = 0x00;      	// enable pull-up on PE5 and PE4
   	   	   	   	   	 //PE4 ve PE5'te pull up'i etkinlestir ( BUTON IÇIN)
   GPIO_PORTE_DEN_R = 0x3F;      	// 7) enable digital I/O on PE5-0 // portE 5-0 giris çikis  etkinlerstir.
   }
void init_port_D() {
   volatile unsigned long tmp; // bu degisken gecikme yapmak icin gerekli
   SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;   // 1) E portunun osilatörünü etkinlestir
   tmp = SYSCTL_RCGCGPIO_R;    	// allow time for clock to start
   GPIO_PORTD_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port E
   GPIO_PORTD_CR_R = 0x4F;         // allow changes to PE5-0 //PE5-0 degisikliklerine izin ver
                                   // only PE0 needs to be unlocked, other bits can't be locked
    			 // Sadece PE0 kilidinin açilmasi gerekir, diger bitler kilitlenemez
   GPIO_PORTD_AMSEL_R = 0x00;    	// 3) disable analog on PE //PE'de analog devre disi birak
   GPIO_PORTD_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PE4-0
   GPIO_PORTD_DIR_R = 0xBF;      	// 5) PE4,PE5 in, PE3-0 out
   GPIO_PORTD_AFSEL_R = 0x00;    	// 6) disable alt funct on PE7-0
   GPIO_PORTD_PUR_R = 0x00;      	// enable pull-up on PE5 and PE4
   	   	   	   	   	 //PE4 ve PE5'te pull up'i etkinlestir ( BUTON IÇIN)
   GPIO_PORTD_DEN_R = 0x40;      	// 7) enable digital I/O on PE5-0 // portE 5-0 giris çikis  etkinlerstir.
   }



int main(void) {

	init_port_E();// surekli islem_1 ve islem_2'yi yap
	init_port_D();
	SysCtlClockSet(
				   SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
				   | SYSCTL_OSC_MAIN);

				   Lcd_init();


Lcd_Goto(2,4);
	Lcd_Puts("0");
	Lcd_Goto(2,5);
		Lcd_Puts("0");
		Lcd_Goto(2,6);
			Lcd_Puts(".");
			Lcd_Goto(2,7);
				Lcd_Puts("0");
				Lcd_Goto(2,8);
					Lcd_Puts("0");

					int sayac=0;
					    int sayac2=0;
					    int sayac3=0;
					    int sayac4=0;
					    char buffer[20];
					    char buffer2[20];
					    char buffer3[20];
					    char buffer4[20];
                        char nokta=' ';

						volatile unsigned long delay1;
						volatile unsigned long delay2;
						volatile unsigned long delay3;
						volatile unsigned long delay4;
						volatile unsigned long delay5;
                        int bayrak=0;


						while(1){

						int buton1=GPIO_PORTE_DATA_R & 0b00001;
					    int buton2=GPIO_PORTE_DATA_R & 0b00010;
					    int buton3=GPIO_PORTE_DATA_R & 0b00100;
						int buton4=GPIO_PORTE_DATA_R & 0b01000;
						int buton6=GPIO_PORTD_DATA_R & 0b1000000;
						int buton5=GPIO_PORTE_DATA_R & 0b100000;
					    int buton7=GPIO_PORTE_DATA_R & 0b10000;

						if ( buton1 !=0)
						{
                            bayrak=1;
							Lcd_Temizle();
							sayac++;

							SysCtlDelay(3000);
							if(sayac<10)
							{



								Lcd_Goto(1,1);
								Lcd_Puts("Buton1");


								Lcd_Goto(2,1);
								itoa(sayac,buffer,10);
								Lcd_Puts(buffer);
								Lcd_Goto(2,2);
								Lcd_Puts(buffer2);
								Lcd_Goto(2,3);
								Lcd_Putch(nokta);
								Lcd_Goto(2,4);
								Lcd_Puts(buffer3);
								Lcd_Goto(2,5);
								Lcd_Puts(buffer4);
								for (delay1 = 0 ; delay1 < 800000 ; delay1++);


							}
							else if(sayac==10){
								sayac=0;
								Lcd_Goto(1,1);
								Lcd_Puts("Buton1");
								Lcd_Goto(2,1);
								itoa(sayac,buffer,10);
								Lcd_Puts(buffer);
								Lcd_Goto(2,2);
								Lcd_Puts(buffer2);
								Lcd_Goto(2,3);
								Lcd_Putch(nokta);
								Lcd_Goto(2,4);
								Lcd_Puts(buffer3);
								Lcd_Goto(2,5);
								Lcd_Puts(buffer4);
								for (delay1 = 0 ; delay1 < 800000 ; delay1++);
							}
							if(buton1==0){
											Lcd_Goto(2,1);
											itoa(sayac,buffer,10);
											Lcd_Puts(buffer);
											Lcd_Goto(2,2);
											Lcd_Puts(buffer2);
											Lcd_Goto(2,3);
											Lcd_Putch(nokta);
											Lcd_Goto(2,4);
											Lcd_Puts(buffer3);
											Lcd_Goto(2,5);
											Lcd_Puts(buffer4);
											break;

										}


						}

						if ( buton2 !=0)
							{
							bayrak=1;
								Lcd_Temizle();
								sayac2++;

								SysCtlDelay(3000);
								if(sayac2<10)
								{


									Lcd_Goto(1,1);
									Lcd_Puts("Buton2");

									Lcd_Goto(2,1);
									Lcd_Puts(buffer);
									Lcd_Goto(2,2);
									itoa(sayac2,buffer2,10);
									Lcd_Puts(buffer2);
									Lcd_Goto(2,3);
									Lcd_Putch(nokta);
									Lcd_Goto(2,4);
									Lcd_Puts(buffer3);
									Lcd_Goto(2,5);
									Lcd_Puts(buffer4);
									for (delay2 = 0 ; delay2 < 800000 ; delay2++);


								}
								else if(sayac2==10){
									sayac2=0;
									Lcd_Goto(1,1);
									Lcd_Puts("Buton2");
									Lcd_Goto(2,1);
									Lcd_Puts(buffer);
									Lcd_Goto(2,2);
									itoa(sayac2,buffer2,10);
									Lcd_Puts(buffer2);
									Lcd_Goto(2,3);
									Lcd_Putch(nokta);
									Lcd_Goto(2,4);
									Lcd_Puts(buffer3);
									Lcd_Goto(2,5);
									Lcd_Puts(buffer4);
									for (delay2= 0 ; delay2 < 800000 ; delay2++);
								}
								if(buton2==0){
									Lcd_Goto(2,1);
									Lcd_Puts(buffer);
									Lcd_Goto(2,2);
									itoa(sayac2,buffer2,10);
									Lcd_Puts(buffer2);
									Lcd_Goto(2,3);
									Lcd_Putch(nokta);
									Lcd_Goto(2,4);
									Lcd_Puts(buffer3);
									Lcd_Goto(2,5);
									Lcd_Puts(buffer4);
									break;

								}

							}

						if ( buton3 !=0)
								{
							bayrak=1;
									Lcd_Temizle();
									sayac3++;

									SysCtlDelay(3000);
									if(sayac3<10)
									{


										Lcd_Goto(1,1);
										Lcd_Puts("Buton3");
										Lcd_Goto(2,1);
										Lcd_Puts(buffer);
										Lcd_Goto(2,2);
										Lcd_Puts(buffer2);
										Lcd_Goto(2,3);
										Lcd_Putch(nokta);
										Lcd_Goto(2,4);
										itoa(sayac3,buffer3,10);
										Lcd_Puts(buffer3);
										Lcd_Goto(2,5);
										Lcd_Puts(buffer4);
										for (delay3 = 0 ; delay3 < 800000 ; delay3++);


									}
									else if(sayac3==10){
										sayac3=0;
										Lcd_Goto(1,1);
										Lcd_Puts("Buton3");
										Lcd_Goto(2,1);
										Lcd_Puts(buffer);
										Lcd_Goto(2,2);
										Lcd_Puts(buffer2);
										Lcd_Goto(2,3);
										Lcd_Putch(nokta);
										Lcd_Goto(2,4);
										itoa(sayac3,buffer3,10);
										Lcd_Puts(buffer3);
										Lcd_Goto(2,5);
										Lcd_Puts(buffer4);
										for (delay3= 0 ; delay3 < 800000 ; delay3++);
									}
									if(buton3==0){
										Lcd_Goto(2,1);
										Lcd_Puts(buffer);
										Lcd_Goto(2,2);
										Lcd_Puts(buffer2);
										Lcd_Goto(2,3);
										Lcd_Putch(nokta);
										Lcd_Goto(2,4);
										itoa(sayac3,buffer3,10);
										Lcd_Puts(buffer3);
										Lcd_Goto(2,5);
										Lcd_Puts(buffer4);
										break;

									}

								}
						if ( buton4 !=0)
								{
							bayrak=1;
									Lcd_Temizle();
									sayac4++;

									SysCtlDelay(3000);
									if(sayac4<10)
									{


										Lcd_Goto(1,1);
										Lcd_Puts("Buton4");
										Lcd_Goto(2,1);
										Lcd_Puts(buffer);
										Lcd_Goto(2,2);
										Lcd_Puts(buffer2);
										Lcd_Goto(2,3);
										Lcd_Putch(nokta);
										Lcd_Goto(2,4);
										Lcd_Puts(buffer3);

										Lcd_Goto(2,5);
										itoa(sayac4,buffer4,10);
										Lcd_Puts(buffer4);
										for (delay4 = 0 ; delay4 < 800000 ; delay4++);


									}
									else if(sayac4==10){
										sayac4=0;
										Lcd_Goto(1,1);
										Lcd_Puts("Buton4");
										Lcd_Goto(2,1);
										Lcd_Puts(buffer);
										Lcd_Goto(2,2);
										Lcd_Puts(buffer2);
										Lcd_Goto(2,3);
										Lcd_Putch(nokta);
										Lcd_Goto(2,4);
										Lcd_Puts(buffer3);
										Lcd_Goto(2,5);
										itoa(sayac4,buffer4,10);
										Lcd_Puts(buffer4);
										for (delay4= 0 ; delay4 < 800000 ; delay4++);
									}
									if(buton4==0){
										Lcd_Goto(2,1);
										Lcd_Puts(buffer);
										Lcd_Goto(2,2);
										Lcd_Puts(buffer2);
										Lcd_Goto(2,3);
										Lcd_Putch(nokta);
										Lcd_Goto(2,4);
										Lcd_Puts(buffer3);
										Lcd_Goto(2,5);
										itoa(sayac4,buffer4,10);
										Lcd_Puts(buffer4);
										break;

									}

								}
						if(buton5!=0){
							bayrak=1;
							nokta='.';
							Lcd_Goto(2,3);
							Lcd_Putch(nokta);
							SysCtlDelay(20000000);
							if(buton5==0 && bayrak!=0){
								sayac=0;
								sayac2=0;
								sayac3=0;
								sayac4=0;
								Lcd_Goto(2,1);
								itoa(sayac,buffer,10);
								Lcd_Puts(buffer);
								Lcd_Goto(2,2);
								itoa(sayac2,buffer2,10);
							Lcd_Puts(buffer2);
							Lcd_Goto(2,3);
							Lcd_Putch(nokta);
							Lcd_Goto(2,4);
							itoa(sayac3,buffer3,10);
							Lcd_Puts(buffer3);
							Lcd_Goto(2,5);
							itoa(sayac4,buffer4,10);
							Lcd_Puts(buffer4);
							}

						}
						if(buton6!=0){
							bayrak=1;
							sayac=0;
							sayac2=0;
							sayac3=0;
							sayac4=0;
							Lcd_Goto(2,1);
							itoa(sayac,buffer,10);
							Lcd_Puts(buffer);
							Lcd_Goto(2,2);
							itoa(sayac2,buffer2,10);
							Lcd_Puts(buffer2);
							Lcd_Goto(2,3);
							Lcd_Putch(nokta);
							Lcd_Goto(2,4);
							itoa(sayac3,buffer3,10);
							Lcd_Puts(buffer3);
							Lcd_Goto(2,5);
							itoa(sayac4,buffer4,10);
							Lcd_Puts(buffer4);
						}

                    if(buton7!=0){
                    	bayrak=1;
                    	break;
                    }
                  /*  if(buton1==0 && buton2==0 && buton3==0 && buton4==0 && buton5==0 && buton6==0 && buton7==0 && bayrak !=0){
                    	SysCtlDelay(50000000);
                    	if((buton1!=0 || buton2!=0 || buton3!=0 || buton4!=0 || buton5!=0 || buton6!=0 || buton7!=0 )&& bayrak !=0){
                    	continue;
                    	}
                    	else
                    		break;
                    }*/

						}
                        Lcd_Temizle();
int s,s2,s3,s4;
char n[20];
char n2[20];
char n3[20];
char n4[20];
char p[20];
char p2[20];
char p3[20];
char p4[20];
char p5[20];
char p6[20];
char p7[20];
char p8[20];
char p9[20];

s=atoi(buffer);
s2=atoi(buffer2);
s3=atoi(buffer3);
s4=atoi(buffer4);
if(s==0 && s2==0 && s3==0 && s4==0){
	Lcd_Goto(1,1);
	Lcd_Puts("giris yok");
}
else{
int yirmilik=0,onluk=0,beslik=0,birlik=0,
			yarimlik=0,ceyreklik=0,metelik=0,delik=0,kurusluk=0;

	if(s%2==0){
		yirmilik=s/2;

	}
	if(s%2==1){
		yirmilik=s/2;
		onluk++;
	}
	if(s2%5==0){
			beslik=s/5;
		}
		if((s2%5)<5){
			birlik=s2%5;
			beslik=s2/5;
		}
		if(s3>=5){
				yarimlik=s3/5;

				if((s3-5)*10>=25){
					ceyreklik++;
					if(((s3-5)*10)-25>=15){
						metelik++;
						delik++;
						kurusluk+=((s3-5)*10)-25-15;
					}
					else if(((s3-5)*10)-25<15 && ((s3-5)*10)-25>=10){
						metelik++;
						kurusluk+=((s3-5)*10)-25-10;
					}
					else if(((s3-5)*10)-25<10 && ((s3-5)*10)-25>=5){
						delik++;
						kurusluk+=((s3-5)*10)-25-5;
					}
					else{
						kurusluk+=((s3-5)*10)-25;
					}
				}
				else{
					metelik+=s3-5;
				}
			}
			if(s3<5){
				if(s3==4 || s3==3 || (s3==2 && s4==5)){
					ceyreklik++;
				}
				else{
					metelik+=s3;
				}
			}
			if(s4>=5){
				delik+=s4/5;
				kurusluk+=s4-5;
			}
			if(s4<5){
				kurusluk+=s4;
			}

	char tut[20];
	char tut2[20];
	char tut3[20];
	char tut4[20];
	itoa(yirmilik,p,10);
	Lcd_Goto(2,1);
	Lcd_Puts(p);
	Lcd_Goto(2,3);
	Lcd_Puts("yirmilik");
	s=s-(yirmilik*2);
	itoa(s,tut,10);
	Lcd_Goto(1,12);
	Lcd_Puts(tut);
	Lcd_Goto(1,13);
		Lcd_Puts(buffer2);
		Lcd_Goto(1,14);
		Lcd_Puts(".");
		Lcd_Goto(1,15);
			Lcd_Puts(buffer3);
			Lcd_Goto(1,16);
				Lcd_Puts(buffer4);
	SysCtlDelay(30000000);
	Lcd_Temizle();
	itoa(onluk,p2,10);
		Lcd_Goto(2,1);
		Lcd_Puts(p2);
		Lcd_Goto(2,3);
		Lcd_Puts("onluk");
		s=s-onluk;
			itoa(s,tut2,10);
			Lcd_Goto(1,12);
			Lcd_Puts(tut2);
			Lcd_Goto(1,13);
				Lcd_Puts(buffer2);
				Lcd_Goto(1,14);
				Lcd_Puts(".");
				Lcd_Goto(1,15);
					Lcd_Puts(buffer3);
					Lcd_Goto(1,16);
						Lcd_Puts(buffer4);
		SysCtlDelay(30000000);
		Lcd_Temizle();
		itoa(beslik,p3,10);
			Lcd_Goto(2,1);
			Lcd_Puts(p3);
			Lcd_Goto(2,3);
			Lcd_Puts("beslik");
			s2=s2-(beslik*5);
			Lcd_Goto(1,12);
			Lcd_Puts("0");
				itoa(s2,tut2,10);
				Lcd_Goto(1,13);
				Lcd_Puts(tut2);
				Lcd_Goto(1,14);
				Lcd_Puts(".");
				Lcd_Goto(1,15);
					Lcd_Puts(buffer3);
					Lcd_Goto(1,16);
						Lcd_Puts(buffer4);
			SysCtlDelay(30000000);
			Lcd_Temizle();
			itoa(birlik,p4,10);
				Lcd_Goto(2,1);
				Lcd_Puts(p4);
				Lcd_Goto(2,3);
				Lcd_Puts("birlik");
				s2=s2-birlik;
							Lcd_Goto(1,12);
							Lcd_Puts("0");
								itoa(s2,tut2,10);
								Lcd_Goto(1,13);
								Lcd_Puts(tut2);
								Lcd_Goto(1,14);
								Lcd_Puts(".");
								Lcd_Goto(1,15);
									Lcd_Puts(buffer3);
									Lcd_Goto(1,16);
										Lcd_Puts(buffer4);
				SysCtlDelay(30000000);
				Lcd_Temizle();
				itoa(yarimlik,p5,10);
					Lcd_Goto(2,1);
					Lcd_Puts(p5);
					Lcd_Goto(2,3);
					Lcd_Puts("yarimlik");
					s3=s3-(yarimlik*5);
								Lcd_Goto(1,12);
								Lcd_Puts("0");
								Lcd_Goto(1,13);
								Lcd_Puts("0");
								Lcd_Goto(1,14);
								Lcd_Puts(".");
									itoa(s3,tut3,10);
									Lcd_Goto(1,15);
									Lcd_Puts(tut3);
									Lcd_Goto(1,16);
									Lcd_Puts(buffer4);
					SysCtlDelay(30000000);
					Lcd_Temizle();
					itoa(ceyreklik,p6,10);
						Lcd_Goto(2,1);
						Lcd_Puts(p6);
						Lcd_Goto(2,3);
						Lcd_Puts("ceyreklik");
						int toplam=0;
						toplam=(s3*10)+s4;
						int yeni=toplam-(ceyreklik*25);
						s3=yeni/10;
						s4=yeni%10;
						char tut5[10];
						itoa(s4,tut5,10);
						Lcd_Goto(1,12);
										Lcd_Puts("0");
										Lcd_Goto(1,13);
										Lcd_Puts("0");
										Lcd_Goto(1,14);
										Lcd_Puts(".");
										itoa(s3,tut3,10);
										Lcd_Goto(1,15);
										Lcd_Puts(tut3);
										Lcd_Goto(1,16);
										Lcd_Puts(tut5);
						SysCtlDelay(30000000);
						Lcd_Temizle();
						itoa(metelik,p7,10);
							Lcd_Goto(2,1);
							Lcd_Puts(p7);
							Lcd_Goto(2,3);
							Lcd_Puts("metelik");
							s3=s3-metelik;
											Lcd_Goto(1,12);
											Lcd_Puts("0");
											Lcd_Goto(1,13);
											Lcd_Puts("0");
											Lcd_Goto(1,14);
											Lcd_Puts(".");
											itoa(s3,tut3,10);
											Lcd_Goto(1,15);
											Lcd_Puts(tut3);
											Lcd_Goto(1,16);
										    Lcd_Puts(tut5);
							SysCtlDelay(30000000);
							Lcd_Temizle();
							itoa(delik,p8,10);
								Lcd_Goto(2,1);
								Lcd_Puts(p8);
								Lcd_Goto(2,3);
								Lcd_Puts("delik");
								s4=s4-(delik*5);
											Lcd_Goto(1,12);
											Lcd_Puts("0");
											Lcd_Goto(1,13);
											Lcd_Puts("0");
											Lcd_Goto(1,14);
											Lcd_Puts(".");
											Lcd_Goto(1,15);
											Lcd_Puts("0");
											itoa(s4,tut4,10);
											Lcd_Goto(1,16);
											Lcd_Puts(tut4);


								SysCtlDelay(30000000);
								Lcd_Temizle();
								itoa(kurusluk,p9,10);
									Lcd_Goto(2,1);
									Lcd_Puts(p9);
									Lcd_Goto(2,3);
									Lcd_Puts("kurusluk");
									s4=s4-kurusluk;
												Lcd_Goto(1,12);
												Lcd_Puts("0");
												Lcd_Goto(1,13);
												Lcd_Puts("0");
												Lcd_Goto(1,14);
												Lcd_Puts(".");
												Lcd_Goto(1,15);
												Lcd_Puts("0");
												itoa(s4,tut4,10);
												Lcd_Goto(1,16);
												Lcd_Puts(tut4);
									SysCtlDelay(30000000);

}
}


void Lcd_init() {

        SysCtlPeripheralEnable(LCDPORTENABLE);
        GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, RS,  0x00 );

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x20 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        Lcd_Komut(0x28);
        Lcd_Komut(0xC0);
        Lcd_Komut(0x06);
        Lcd_Komut(0x80);
        Lcd_Komut(0x28);
        Lcd_Komut(0x0f);
        Lcd_Temizle();

}
void Lcd_Komut(unsigned char c) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

}

void Lcd_Putch(unsigned char d) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

}
void Lcd_Goto(int x, char y){

        if(x==1)
                Lcd_Komut(0x80+((y-1)%16));
        else
                Lcd_Komut(0xC0+((y-1)%16));
}

void Lcd_Temizle(void){
        Lcd_Komut(0x01);
        SysCtlDelay(10);
}

void Lcd_Puts( char* s){

        while(*s)
                Lcd_Putch(*s++);
}
