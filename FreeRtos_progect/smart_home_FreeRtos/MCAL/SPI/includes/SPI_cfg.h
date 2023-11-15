/*****************************************************************************/
/*****************************************************************************/
/**********************    Layer  : MCAL                **********************/
/**********************    SWD    : SPI                 **********************/
/**********************    Version: 1.0                 **********************/
/*****************************************************************************/
/*****************************************************************************/
#ifndef SPI_CFG_H
#define SPI_CFG_H

/**
 * Options : 
 * SPI_INTERRUPT_ENABLE
 * SPI_INTERRUPT_DISABLE
 */
#define SPI_INTERRUPT_STATE         SPI_INTERRUPT_DISABLE 

/**
 * Options : 
 * IDLE_HIGH
 * IDLE_LOW
 */
#define SPI_CLOCK_POLARITY          IDLE_HIGH
 
/**
 * Options : 
 * SAMPLE_FIRST
 * SETUP_FIRST
 */
#define SPI_CLOCK_PHASE          SAMPLE_FIRST

/**
 * Options : 
 * FOSC_DIV_BY4
 * FOSC_DIV_BY16
 * FOSC_DIV_BY64
 * FOSC_DIV_BY128
 * FOSC_DIV_BY2
 * FOSC_DIV_BY8
 * FOSC_DIV_BY32
 */
#define SPI_CLOCK_FREQ          FOSC_DIV_BY64

#endif
