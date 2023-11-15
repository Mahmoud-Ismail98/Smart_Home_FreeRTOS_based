#ifndef ADC_H_
#define ADC_H_


typedef enum{
	ADC_ERROR_FREE,
	ADC_ERROR_CHANNEL
}ADC_ERROR_STATE;

void ADC_voidInit(void);
ADC_ERROR_STATE ADC_read(u8 ADC_CHANEL,u16 *loc_AdcVal);
void ADC_Disable(void);
void ADC_AScyn(void);
void ADC_InteruptDisable(void);
void ADC_SetCallBack(void (* copy_ptrfun)(u16 var));
void ADC_AScyn(void);

#define ADC_CH0		0b00000
#define ADC_CH1		0b00001
#define ADC_CH2		0b00010
#define ADC_CH3		0b00011
#define ADC_CH4		0b00100
#define ADC_CH5		0b00101
#define ADC_CH6		0b00110
#define ADC_CH7		0b00111


#endif