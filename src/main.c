#include "bsp/bsp.h"

int main(void)
{
	char pantallaInicio[58] = "Bienvenido al Menú | Ingrese alguno de los siguientes N°";
	char pantalla0[109] = " ||| 1. Obtener valor ADC | 2. Prueba de Leds | 3. Estado de SW"
					   	  " | 0. Para volver atrás en cualquier pantalla";
	char pantalla1[79] = " ||| 1. Obtener binario | 2. Obtener decimal | 3. Obtener Volt | 0. Para volver";
	char pantalla2[92] = " ||| 1. Toggle Led R | 2. Toggle Led V | 3. Toggle Led N | 4. Toggle Led A | 0. Para volver";
	char pantalla3[53] = " ||| 1. SW1 | 2.SW2 | 3.SW3 | 4.SW4 | 0. Para volver";
	char pantalla11[17] = " ||| Valor ADC: ";
	char pantalla111[2];
	char pantalla112[5];
	char pantalla122[6];
	char pantalla211[14] = " ||| Led R On";
	char pantalla212[15] = " ||| Led R Off";
	char pantalla213[14] = " ||| Led V On";
	char pantalla214[15] = " ||| Led V Off";
	char pantalla215[14] = " ||| Led N On";
	char pantalla216[15] = " ||| Led N Off";
	char pantalla217[14] = " ||| Led A On";
	char pantalla218[15] = " ||| Led A Off";
	char pantalla31[8] = " ||| SW";
	char pantalla311[5];

	uint8_t menu = 0, pantalla = 0, binario[13], cuentaBinario = 0;
	uint16_t valorADC = 0, togglear[4] = {0,0,0,0};
	float valorADCVolt = 0;

	BSP_Init();
	TransmitData(pantallaInicio,58);
	TransmitData(pantalla0,109);

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
								TransmitData(pantalla1,79);
								break;
						case '2':
								pantalla = 2;
								TransmitData(pantalla2,92);
								break;
						case '3':
								pantalla = 3;
								TransmitData(pantalla3,53);
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
								TransmitData(pantalla0,109);
								break;
						case '1':
								pantalla = 11;
								TransmitData(pantalla11,17);
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
								TransmitData(pantalla11,17);
								sprintf(pantalla112,"%d",valorADC);
								if(valorADC<100)
									TransmitData(pantalla112,3);
								else
									TransmitData(pantalla112,5);
								break;
						case '3':
								pantalla = 11;
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
								TransmitData(pantalla0,109);
								break;
						case '1':
								pantalla = 21;
								if(togglear[0] == 0)
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_0, GPIO_PIN_SET);
									togglear[0] = 1;
									TransmitData(pantalla211,14);
								}
								else
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_0, GPIO_PIN_RESET);
									togglear[0] = 0;
									TransmitData(pantalla212,14);
								}
								break;
						case '2':
								pantalla = 21;
								if(togglear[1] == 0)
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_1, GPIO_PIN_SET);
									togglear[1] = 1;
									TransmitData(pantalla213,14);
								}
								else
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_1, GPIO_PIN_RESET);
									togglear[1] = 0;
									TransmitData(pantalla214,14);
								}
								break;
						case '3':
								pantalla = 21;
								if(togglear[2] == 0)
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_2, GPIO_PIN_SET);
									togglear[2] = 1;
									TransmitData(pantalla215,14);
								}
								else
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_2, GPIO_PIN_RESET);
									togglear[2] = 0;
									TransmitData(pantalla216,14);
								}
								break;
						case '4':
								pantalla = 21;
								if(togglear[3] == 0)
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_3, GPIO_PIN_SET);
									togglear[3] = 1;
									TransmitData(pantalla217,14);
								}
								else
								{
									HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_3, GPIO_PIN_RESET);
									togglear[3] = 0;
									TransmitData(pantalla218,14);
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
								TransmitData(pantalla0,109);
								break;
						case '1':
								pantalla = 31;
								TransmitData(pantalla31,8);
								sprintf(pantalla311,"1: %d",BSP_SW_GetState(0));
								TransmitData(pantalla311,5);
								break;
						case '2':
								pantalla = 31;
								TransmitData(pantalla31,8);
								sprintf(pantalla311,"2: %d",BSP_SW_GetState(1));
								TransmitData(pantalla311,5);
								break;
						case '3':
								pantalla = 31;
								TransmitData(pantalla31,8);
								sprintf(pantalla311,"3: %d",BSP_SW_GetState(2));
								TransmitData(pantalla311,5);
								break;
						case '4':
								pantalla = 31;
								TransmitData(pantalla31,8);
								sprintf(pantalla311,"4: %d",BSP_SW_GetState(3));
								TransmitData(pantalla311,5);
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
								TransmitData(pantalla1,79);
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
								TransmitData(pantalla2,92);
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
								TransmitData(pantalla3,53);
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
