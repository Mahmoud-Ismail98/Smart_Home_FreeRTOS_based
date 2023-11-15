

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

//#include "../../services/Std_types.h"


#define PIN_INPUT  0
#define PIN_OUTPUT 1
#define EXT0_PIN	26
#define EXT1_PIN	27
#define EXT2_PIN	12

typedef enum
{
	INT_LOW_LEVEL,
	INT_ANY_LOGIC_CHANGE,
	INT_FALLING_EDGE,
	INT_RISING_EDGE
} enum_external_int_type_t;

typedef enum
{
	EXT_INT0=6,
	EXT_INT1=7,
	EXT_INT2=5,
} enum_extenal_int_n_t;

void Enable_EXT_INT(u8 X);

void Disable_EXT_INT(u8 X);

void extrnal_int_init(enum_extenal_int_n_t X,enum_external_int_type_t int_type,void (*PTR_TO_FUN)());
void Global_Interrupt_EnablE(void);
void Global_Interrupt_Disable(void);
#endif /* EXTERNAL_INTERRUPT_H_ */