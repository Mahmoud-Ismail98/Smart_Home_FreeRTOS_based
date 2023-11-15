/*
 * I2C.c
 *
 * Created: 30/10/2023 12:29:36 م
 *  Author: mkora
 */ 
#include "../../services/Bit_utils.h"
#include "../../services/Std_types.h"

#include "../../MCAL/port/include/port.h"
#include "../../MCAL/I2C/I2C.h"


void TWI_voidMasterInit(u8 Copy_u8SlaveAddress)
{
	/*enable acknowlge bit*/
	SET_BIT(TWI_TWCR, TWEA);
	/*initialize the node address*/
	if(Copy_u8SlaveAddress != 0)
	{
		TWI_TWAR = (Copy_u8SlaveAddress << 1);
	}
	/*Set clock frequancy to 400kbps*/
	/*Set TWBR to 2*/
	TWI_TWBR = 2;
	/*clear the 2 bits of TWPS*/
	CLR_BIT(TWI_TWSR, TWPS0);
	CLR_BIT(TWI_TWSR, TWPS1);

	/*enable TWI*/
	SET_BIT(TWI_TWCR, TWEN);
}

void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress)
{
	/*initialize the node address*/
	TWI_TWAR = (Copy_u8SlaveAddress << 1);

	/*enable acknowlge bit*/
	SET_BIT(TWI_TWCR, TWEA);
	/*enable TWI*/
	SET_BIT(TWI_TWCR, TWEN);
}

TWI_ErrStatus TWI_SendStartCondition(void)
{
	TWI_ErrStatus Local_ErrStatus = NoError;
	/*Send start Condition on the bus*/
	SET_BIT(TWI_TWCR, TWSTA);

	/*clear the interrupt flag to start operation*/
	SET_BIT(TWI_TWCR, TWINT);

	/*wait until the interrupt flag is raised again*/
	while((GET_BIT(TWI_TWCR, TWINT)) == 0);

	/*Check the operation status in the status register*/
	if((TWI_TWSR & 0xF8) != START_ACK)
	{
		Local_ErrStatus = StartCondistionError;
	}
	else
	{
	}

	return Local_ErrStatus;
}

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_ErrStatus = NoError;


	/*Set the slave address in the 7 msb in the data register*/
	TWI_TWDR = (Copy_u8SlaveAddress << 1);
	CLR_BIT(TWI_TWDR, 0); //for write request

	/*Clear the start condition bit*/
	CLR_BIT(TWI_TWCR, TWSTA);

	/*clear the interrupt flag to start operation*/
	SET_BIT(TWI_TWCR, TWINT);

	/*wait until the interrupt flag is raised again*/
	while((GET_BIT(TWI_TWCR, TWINT)) == 0);

	/*Check the operation status in the status register*/
	if((TWI_TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_ErrStatus = SlaveAddressWithWriteError;
	}
	return Local_ErrStatus;
}
TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte)
{
	TWI_ErrStatus Local_ErrStatus = NoError;
	/*Write the data byte */
	TWI_TWDR = Copy_u8DataByte;

	/*clear the interrupt flag to start operation*/
	SET_BIT(TWI_TWCR, TWINT);

	/*wait until the interrupt flag is raised again*/
	while((GET_BIT(TWI_TWCR, TWINT)) == 0);

	/*Check the operation status in the status register*/
	if((TWI_TWSR & 0xF8) != MSTR_WR_BYTE_ACK)
	{
		Local_ErrStatus = MasterWriteByteError;
	}

	return Local_ErrStatus;
}
