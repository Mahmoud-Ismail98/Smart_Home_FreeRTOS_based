 
#ifndef UART_LCFG_H_
#define UART_LCFG_H_

/******************* UART configuration*********************************/
#define  SPEED_MODE         NORMAL_SPEED
#define  CPU_F               _8_MHZ
#define  BUAD_RATE          BAUD_9600
#define  SYNCH_MODE         ASYNCH
#define  PARITY_MODE        NO_PARITY
#define  N_DATA_BITS        _8_DATA_BITS
#define  N_STOP_BITS        ONE_STOP_BIT


/********************speed mode*************************/
#define NORMAL_SPEED      0
#define DOUBLE_SPEED      1
#define TOTAL_SPEED_MODE  2
/********************cpu freqs***************************/
#define   _4_MHZ         0
#define   _8_MHZ         1
#define  _16_MHZ         2
#define  TOTAL_CPU_F     3
/*******************baud rate *****************************/
#define  BAUD_2400       0
#define  BAUD_4800       1
#define  BAUD_9600       2
#define  BAUD_14400      3
#define  BAUD_19200      4
#define  BAUD_28800      5
#define  TOTAL_BAUD_RATE 6
/*******************parity mode*************************/
#define NO_PARITY    0
#define EVEN_PARITY  1
#define ODD_PARITY   2
/*************** number of data bits********************/
#define  _5_DATA_BITS    5
#define  _6_DATA_BITS    6
#define  _7_DATA_BITS    7
#define  _8_DATA_BITS    8
#define  _9_DATA_BITS    9

/***************      sync mode*************************/
#define  SYNCH  0
#define  ASYNCH 1
/************    number of stop bits*****************/
#define  ONE_STOP_BIT   1
#define  TWO_STOP_BIT   2


/******************************************************************************/
/* USART Baud Rate Register Low */
#define UBRRL    (*(volatile unsigned char*)0x29)

/* USART Control and Status Register B */
#define UCSRB   (*(volatile unsigned char*)0x2A)

/* USART Control and Status Register A */
#define UCSRA    (*(volatile unsigned char*)0x2B)

/* USART I/O Data Register */
#define UDR       (*(volatile unsigned char*)0x2C)

/* USART Baud Rate Register High */
#define UBRRH    (*(volatile unsigned char*)0x40)

/* USART Control and Status Register C */
#define UCSRC     (*(volatile unsigned char*)0x40)

/* USART Register C */
#define    URSEL        6
#define    UPM1         5
#define    UPM0         4
#define    USBS         3
#define    UCSZ1        2
#define    UCSZ0        1
#define    UCPOL        0

/* USART Status Register A  */
#define    RXC          7
#define    TXC          6
#define    UDRE         5
#define    FE           4
#define    DOR          3
#define    UPE          2
#define    U2X          1
#define    MPCM         0
/* USART Control Register B  */
#define    RXCIE        7
#define    TXCIE        6
#define    UDRIE        5
#define    RXEN         4
#define    TXEN         3
#define    UCSZ         2
#define    UCSZ2        2
#define    RXB8         1
#define    TXB8         0
/******************************************************************************/
#endif /* UART_LCFG_H_ */