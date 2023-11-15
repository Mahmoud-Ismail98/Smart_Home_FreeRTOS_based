/*****************************************************************************/
/*****************************************************************************/
/**********************    Layer  : MCAL                **********************/
/**********************    SWD    : SPI                 **********************/
/**********************    Version: 1.0                 **********************/
/*****************************************************************************/
/*****************************************************************************/

#include "../../../services/Bit_utils.h"
#include "../../../services/Std_types.h"

#include "../../../MCAL/SPI/includes/SPI_prv.h"
#include "../../../MCAL/SPI/includes/SPI_cfg.h"
#include "../../../MCAL/SPI/includes/SPI.h"

void (*SPI_COMPLETE_OPERATION_ISR_POINTER)() = NULL;

void SPI_voidMasterInit(){
    #if SPI_INTERRUPT_STATE == SPI_INTERRUPT_ENABLE
        SET_BIT(SPCR, SPCR_SPIE);
    #elif SPI_INTERRUPT_STATE == SPI_INTERRUPT_DISABLE
        CLR_BIT(SPCR, SPCR_SPIE);
    #endif

    #if SPI_CLOCK_POLARITY == IDLE_HIGH
        SET_BIT(SPCR, SPCR_CPOL);
    #elif SPI_CLOCK_POLARITY == IDLE_LOW
        CLR_BIT(SPCR, SPCR_CPOL);
    #endif

    #if SPI_CLOCK_PHASE == SAMPLE_FIRST
        CLR_BIT(SPCR, SPCR_CPHA);
    #elif SPI_CLOCK_PHASE == SETUP_FIRST
        SET_BIT(SPCR, SPCR_CPHA);
    #endif


    #if SPI_CLOCK_FREQ   == FOSC_DIV_BY4
        CLR_BIT(SPCR, SPCR_SPR0);
        CLR_BIT(SPCR, SPCR_SPR1);
        CLR_BIT(SPSR, SPSR_SPI2X);
    #elif SPI_CLOCK_FREQ == FOSC_DIV_BY16
        SET_BIT(SPCR, SPCR_SPR0);
        CLR_BIT(SPCR, SPCR_SPR1);
        CLR_BIT(SPSR, SPSR_SPI2X);
    #elif SPI_CLOCK_FREQ == FOSC_DIV_BY64
        CLR_BIT(SPCR, SPCR_SPR0);
        SET_BIT(SPCR, SPCR_SPR1);
        CLR_BIT(SPSR, SPSR_SPI2X);
    #elif SPI_CLOCK_FREQ == FOSC_DIV_BY128
        SET_BIT(SPCR, SPCR_SPR0);
        SET_BIT(SPCR, SPCR_SPR1);
        CLR_BIT(SPSR, SPSR_SPI2X);
    #elif SPI_CLOCK_FREQ == FOSC_DIV_BY2
        CLR_BIT(SPCR, SPCR_SPR0);
        CLR_BIT(SPCR, SPCR_SPR1);
        SET_BIT(SPSR, SPSR_SPI2X);
    #elif SPI_CLOCK_FREQ == FOSC_DIV_BY8
        SET_BIT(SPCR, SPCR_SPR0);
        CLR_BIT(SPCR, SPCR_SPR1);
        SET_BIT(SPSR, SPSR_SPI2X);
    #elif SPI_CLOCK_FREQ == FOSC_DIV_BY32
        CLR_BIT(SPCR, SPCR_SPR0);
        SET_BIT(SPCR, SPCR_SPR1);
        SET_BIT(SPSR, SPSR_SPI2X);
    #endif

    /*Init as master*/
    SET_BIT(SPCR, SPCR_MSTR);
    /*Enable SPI*/
    SET_BIT(SPCR, SPCR_SPE);
}

void SPI_voidSlaveInit(){
    /*Init as Slave*/
    CLR_BIT(SPCR, SPCR_MSTR);
    /*Enable SPI*/
    SET_BIT(SPCR, SPCR_SPE);
}
u8 SPI_u8transceiveDataSynch(u8 Copy_u8Data)
{
	    SPDR = Copy_u8Data;
	    /*Polling tell data is sent*/
	    while(GET_BIT(SPSR,SPSR_SPIF) == 0);
	    SET_BIT(SPSR,SPSR_SPIF);
	    return SPDR;
}
void SPI_u8SendDataAsych(u8 Copy_u8Data){
    SET_BIT(SPCR, SPCR_SPIE);
    SPDR = Copy_u8Data;
}

u8 SPI_u8CheckCollision(){
    return GET_BIT(SPSR, SPSR_WCOL);
}



void SPI_enuErrorStateSetCallBackFunc(void (*ptrCallBackFunc)(void)){
  //  tenuErrorStatus Local_u8ErrorState = no_error;
        SPI_COMPLETE_OPERATION_ISR_POINTER = ptrCallBackFunc;
}

void __vector_12(void) __attribute__((signal));
void __vector_12(void){
    if (SPI_COMPLETE_OPERATION_ISR_POINTER != NULL){
        SPI_COMPLETE_OPERATION_ISR_POINTER();
    }
}
