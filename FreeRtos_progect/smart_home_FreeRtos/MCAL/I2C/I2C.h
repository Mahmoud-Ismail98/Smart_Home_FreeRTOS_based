/*
 * I2C.h
 *
 * Created: 30/10/2023 12:30:28 م
 *  Author: mkora
 */ 


#ifndef I2C_H_
#define I2C_H_


#define  TWBR     *((volatile u8*)0x56)

#define  TWCR     *((volatile u8*)0x20)
#define  TWCR_TWINT    7
#define  TWCR_TWEA     6
#define  TWCR_TWSTA    5
#define  TWCR_TWSTO    4
#define  TWCR_TWWC     3
#define  TWCR_TWEN     2
#define  TWCR_TWIE     0


#define  TWSR     *((volatile u8*)0x21)
#define  TWSR_TWPS1     1
#define  TWSR_TWPS0     0

#define  TWDR	  *((volatile u8*)0x23)
#define  TWAR	  *((volatile u8*)0x22)
#define  TWAR_TWGCE	    0

#define TWI_TWBR			*((volatile u8*)0x20)
#define TWBR0				0
#define TWBR1				1
#define TWBR2				2
#define TWBR3				3
#define TWBR4				4
#define TWBR5				5
#define TWBR6				6
#define TWBR7				7

#define TWI_TWCR			*((volatile u8*)0x56)
#define TWIE				0
#define TWEN				2
#define TWWC				3
#define TWSTO				4
#define TWSTA				5
#define TWEA				6
#define TWINT				7

#define TWI_TWSR			*((volatile u8*)0x21)
#define TWPS0				0
#define TWPS1				1
#define TWS3				3
#define TWS4				4
#define TWS5				5
#define TWS6				6
#define TWS7				7

#define TWI_TWDR			*((volatile u8*)0x23)
#define TWD0				0
#define TWD1				1
#define TWD2				2
#define TWD3				3
#define TWD4				4
#define TWD5				5
#define TWD6				6
#define TWD7				7

#define TWI_TWAR			*((volatile u8*)0x22)
#define TWGCE				0
#define TWA0				1
#define TWA1				2
#define TWA2				3
#define TWA3				4
#define TWA4				5
#define TWA5				6
#define TWA6				7

#define START_ACK					0x08	/*start has been sent*/
#define REP_START_ACK				0x10	/*repeated start*/
#define SLAVE_ADD_AND_WR_ACK		0x18	/*master transmit (slave address + write request) ACK*/
#define SLAVE_ADD_AND_RD_ACK		0x40	/*master transmit (slave address + Read request) ACK*/
#define MSTR_WR_BYTE_ACK			0x28	/*Master transmit data ACK*/
#define MSTR_RD_BYTE_WITH_ACK		0x50	/*Master transmit data with ACK*/
#define MSTR_RD_BYTE_WITH_NACK		0x58	/*Master transmit data with not ack*/
#define SLAVE_ADD_RCVD_RD_REQ		0xA8	/*means that slave address is received with read request*/
#define SLAVE_ADD_RCVD_WR_REQ		0x60	/*means that slave address is received with write request*/
#define SLAVE_DATA_RECEIVED			0x80	/*means that a byte is received*/
#define SLAVE_BYTE_TRANSMITTED		0xB8	/*means that the writted byte is transmitted*/
 
typedef enum
{
	NoError,
	StartCondistionError,
	RepeatedStartError,
	SlaveAddressWithWriteError,
	SlaveAddressWithReadError,
	MasterWriteByteError,
	MasterReadByteError,
	MasterReadStrError
}TWI_ErrStatus;

/*pass 0 in the slave address argument if master will not be addressed*/
void TWI_voidMasterInit(u8 Copy_u8SlaveAddress);
void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);;
TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByt);


#endif /* I2C_H_ */