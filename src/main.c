#include "bsp/bsp.h"

int main(void)
{
	char pantallaInicio[valor1] = "Bienvenido al Menú | Ingrese alguno de los siguientes N°";
	char pantalla0[valor2] = "\n\n 1. Obtener valor ADC | 2. Prueba de Leds | 3. Estado de SW"
					   	  " | 0. Para volver atrás en cualquier pantalla";
	char pantalla1[valor3] = "\n\n 1. Obtener binario | 2. Obtener decimal | 3. Obtener Volt | 0. Para volver";
	char pantalla2[valor4] = "\n\n 1. Toggle Led R | 2. Toggle Led V | 3. Toggle Led N | 4. Toggle Led A | 0. Para volver";
	char pantalla3[valor5] = "\n\n 1. SW1 | 2.SW2 | 3.SW3 | 4.SW4 | 0. Para volver";
	char pantalla11[valor6] = "\n\n Valor ADC: ";
	char pantalla111[valor7];
	char pantalla112[valor8];
	char pantalla122[valor9];
	char pantalla211[valor10] = "\n\n Led R On";
	char pantalla212[valor11] = "\n\n Led R Off";
	char pantalla213[valor10] = "\n\n Led V On";
	char pantalla214[valor11] = "\n\n Led V Off";
	char pantalla215[valor10] = "\n\n Led N On";
	char pantalla216[valor11] = "\n\n Led N Off";
	char pantalla217[valor10] = "\n\n Led A On";
	char pantalla218[valor11] = "\n\n Led A Off";
	char pantalla31[valor8] = "\n\n SW";
	char pantalla311[valor8];

	uint8_t menu = 0, pantalla = 0, binario[13], cuentaBinario = 0;
	uint16_t valorADC = 0, togglear[4] = {0,0,0,0};
	float valorADCVolt = 0;

	BSP_Init();
	TransmitData(pantallaInicio,valor1);
	TransmitData(pantalla0,valor2);

	while (1)
	{
		menu = ReceiveData();
		switch(pantalla)
		{
			case 0:
					switch(menu)
					{
						case '1':
								pantalla = 1;
								TransmitData(pantalla1,valor3);
								break;
						case '2':
								pantalla = 2;
								TransmitData(pantalla2,valor4);
								break;
						case '3':
								pantalla = 3;
								TransmitData(pantalla3,valor5);
								break;
						default:
								break;
					}
					break;
			case 1:
					valorADC = BSP_ADC_GetValue();
					switch(menu)
					{
						case '0':
								pantalla = 0;
								TransmitData(pantalla0,valor2);
								break;
						case '1':
								pantalla = 11;
								TransmitData(pantalla11,valor6);
								for(cuentaBinario=1;cuentaBinario<=12;cuentaBinario++)
								{
									binario[cuentaBinario] = valorADC%2;
									valorADC /= 2;
								}
								for(cuentaBinario=12;cuentaBinario>=1;cuentaBinario--)
								{
									sprintf(pantalla111,"%ud",binario[cuentaBinario]);
									TransmitData(pantalla111,1);
								}
								break;
						case '2':
								pantalla = 11;
								TransmitData(pantalla11,valor6);
								sprintf(pantalla112,"%d",valorADC);
								if(valorADC<100)
									TransmitData(pantalla112,3);
								else
									TransmitData(pantalla112,5);
								break;
						case '3':
								pantalla = 11;
								TransmitData(pantalla11,valor6);
								valorADCVolt = (float)(3.3 * valorADC)/4095;
								sprintf(pantalla122," %.2fV",valorADCVolt);
								TransmitData(pantalla122,6);
								break;
						default:
								break;
					}
					break;
			case 2:
					switch(menu)
					{
						case '0':
								pantalla = 0;
								TransmitData(pantalla0,valor2);
								break;
						case '1':
								pantalla = 21;
								if(togglear[0] == 0)
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_0, GPIO_PIN_SET);
									togglear[0] = 1;
									TransmitData(pantalla211,valor10);
								}
								else
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_0, GPIO_PIN_RESET);
									togglear[0] = 0;
									TransmitData(pantalla212,valor11);
								}
								break;
						case '2':
								pantalla = 21;
								if(togglear[1] == 0)
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_1, GPIO_PIN_SET);
									togglear[1] = 1;
									TransmitData(pantalla213,valor10);
								}
								else
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_1, GPIO_PIN_RESET);
									togglear[1] = 0;
									TransmitData(pantalla214,valor11);
								}
								break;
						case '3':
								pantalla = 21;
								if(togglear[2] == 0)
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_2, GPIO_PIN_SET);
									togglear[2] = 1;
									TransmitData(pantalla215,valor10);
								}
								else
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_2, GPIO_PIN_RESET);
									togglear[2] = 0;
									TransmitData(pantalla216,valor11);
								}
								break;
						case '4':
								pantalla = 21;
								if(togglear[3] == 0)
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_3, GPIO_PIN_SET);
									togglear[3] = 1;
									TransmitData(pantalla217,valor10);
								}
								else
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_3, GPIO_PIN_RESET);
									togglear[3] = 0;
									TransmitData(pantalla218,valor11);
								}
								break;
						default:
								break;
					}
					break;
			case 3:
					switch(menu)
					{
						case '0':
								pantalla = 0;
								TransmitData(pantalla0,valor2);
								break;
						case '1':
								pantalla = 31;
								TransmitData(pantalla31,valor8);
								sprintf(pantalla311,"1: %d",BSP_SW_GetState(0));
								TransmitData(pantalla311,valor8);
								break;
						case '2':
								pantalla = 31;
								TransmitData(pantalla31,valor8);
								sprintf(pantalla311,"2: %d",BSP_SW_GetState(1));
								TransmitData(pantalla311,valor8);
								break;
						case '3':
								pantalla = 31;
								TransmitData(pantalla31,valor8);
								sprintf(pantalla311,"3: %d",BSP_SW_GetState(2));
								TransmitData(pantalla311,valor8);
								break;
						case '4':
								pantalla = 31;
								TransmitData(pantalla31,valor8);
								sprintf(pantalla311,"4: %d",BSP_SW_GetState(3));
								TransmitData(pantalla311,valor8);
								break;
						default:
								break;
					}
					break;
			case 11:
					switch(menu)
					{
						case '0':
								pantalla = 1;
								TransmitData(pantalla1,valor3);
								break;
						default:
								break;
					}
					break;
			case 21:
					switch(menu)
					{
						case '0':
								pantalla = 2;
								TransmitData(pantalla2,valor4);
								break;
						default:
								break;
					}
					break;
			case 31:
					switch(menu)
					{
						case '0':
								pantalla = 3;
								TransmitData(pantalla3,valor5);
								break;
						default:
								break;
					}
					break;
			default:
					break;
		}
	}
}
