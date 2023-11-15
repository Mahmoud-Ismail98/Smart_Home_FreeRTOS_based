/*****************************************************************************/
/*****************************************************************************/
/**********************    Layer  : MCAL                **********************/
/**********************    SWD    : SPI                 **********************/
/**********************    Version: 1.0                 **********************/
/*****************************************************************************/
/*****************************************************************************/
#ifndef SPI_H
#define SPI_H

#define SPI_INTERRUPT_ENABLE        1
#define SPI_INTERRUPT_DISABLE       2

#define IDLE_HIGH                   1
#define IDLE_LOW                    2

#define SAMPLE_FIRST                1
#define SETUP_FIRST                 2

#define FOSC_DIV_BY4                        0
#define FOSC_DIV_BY16                       1
#define FOSC_DIV_BY64                       2
#define FOSC_DIV_BY128                      3
#define FOSC_DIV_BY2                        4
#define FOSC_DIV_BY8                        5
#define FOSC_DIV_BY32                       6


void SPI_voidMasterInit();

void SPI_voidSlaveInit();
u8 SPI_u8transceiveDataSynch(u8 Copy_u8Data);
void SPI_enuErrorStateSetCallBackFunc(void (*ptrCallBackFunc)(void));

u8 SPI_u8CheckCollision();

#endif
