
#define PERIPH_BASE					(0x40000000UL)//UL = Unsigned Long. Donde 0x40000000 es la dirección de memoria donde
                                      //inician todos los periféricos
#define AHB1PERIPH_OFFSET			(0x00020000UL)//Desplazamiento hacia la posición de memoria donde está ubicado
												//el bus AHB1(Advanced High Performance) (Bus Avanzado de alto Rendimiento)
#define AHB1PERIPH_BASE				(PERIPH_BASE + AHB1PERIPH_OFFSET)// Esto es 0x40000000UL + 0x00020000UL = 0x40020000UL.
																	// Primera posicion de memoria donde se ubica el bus AHB1
#define GPIOA_OFFSET				(0x0000)//Desplazamiento hacia la posicion de memoria que conecta el bus AHB1 con
											//el periferico GPIOA
#define GPIOA_BASE					(AHB1PERIPH_BASE + GPIOA_OFFSET)//Posicion de memoria donde esta ubicado el bus AHB1 que
																//conecta al periférico GPIOA
#define RCC_OFFSET					(0x3800UL)//Desplazamiento hacia la posicion de memoria que conecta el bus AHB1 con
											//el periferico RCC
#define RCC_BASE					(AHB1PERIPH_BASE + RCC_OFFSET)//Posicion de memoria donde esta ubicado el bus AHB1 que
																//conecta al periférico RCC
#define AHB1EN_R_OFFSET				(0x30UL)//Desplazamiento en la posicion de memoria para llegar al periferico RCC
										//que configur sus registros
#define RCC_AHB1EN_R				(*(volatile unsigned int*)(RCC_BASE + AHB1EN_R_OFFSET))//Posicion de memoria donde esta ubicado el registro RCC
#define GPIOAEN						(1U<<0)//Donde 1U<<0 significa poner un uno en la posicion cero. bitU<<n.
											//Donde bit = estado del bit 1/0. << "poner en". n = posicion.
											//Habilitacion del del reoj para el puerto A
#define	MODER_R_OFFSET				(0x00UL)//Desplazamiento en la posicion de memoria pa llegar al periferico MODER
#define GPIOA_MODE_R				(*(volatile unsigned int*)(GPIOA_BASE + MODER_R_OFFSET))//Posicion de memoria donde esta ubicado el registro MODER
#define OD_R_OFFSET					(0x14UL)//Desplazamiento en la posicion de memoria para llegar al periferico ODR
										//que configur sus registros
#define GPIOA_OD_R					(*(volatile unsigned int*)(GPIOA_BASE + OD_R_OFFSET))//Posicion de memoria donde esta ubicado el registro ODR
#define PIN5						(1U<<5)//Poner un uno en la posicion 5
#define LED_PIN						PIN5

/*
 * Nota se utiliiza el apuntador *(volatile unsigned int*) para que el compilador apunte ala
 * dirección de memoria especificada por el registro. Ejemplo RCC_AHB1EN_R=(*(volatile unsigned int*)(RCC_BASE + HB1EN_R_OFFSET)) apuenta a la
 * dirección de memoria correspondite añ registro RCC_AHB1EN_R.
*/
/*
(1U<<10)//poner un uno en la posicion dies
&=~(1U<<11)///poner un cero en la posicion once
*/
int main(void){
//PASOA
	//1. Habilitar el acceso a reloj al GPIOA
	RCC_AHB1EN_R |= GPIOAEN;//Habilitacion del del reoj para el puerto A. Donde |= es una operacion or, permitiendo que
							//solo se modifique el bit requerido. En este caso el bit GPIOAEN. Si se quiere establecer un bit
							// a cero se usa &=~
	//2. Configurar el PIN 5 como salida
	GPIOA_MODE_R |= (1U<<10);//poner un uno en la posicion dies
	GPIOA_MODE_R &=~ (1U<<11);//poner un cero en la posicion once
	while(1){
		//3. Setear el pin 5 en alto
		//GPIOA_OD_R |= LED_PIN;
		//4. Alternar
		GPIOA_OD_R ^= LED_PIN;// Donde ^= significa alternancia
		for(int i=0;i<900000;i++){}
	}

}
