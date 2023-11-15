/*Guard File*/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/*  Unsigned Type  */

typedef unsigned char       u8;
typedef unsigned short int  u16;
typedef unsigned long int   u32;
typedef unsigned long long  u64;


/* Signed Type */

typedef signed char         s8;
typedef signed short int    s16;
typedef signed long int     s32;
typedef signed long long    s64;



/*  Unsigned Type  */

typedef unsigned char*       pu8;
typedef unsigned short int*  pu16;
typedef unsigned long int*   pu32;
typedef unsigned long long*  pu64;



/* define the pointer to NULL */
#define NULL ((void *)0)


typedef enum {
	ERROR_FREE,
	PIN_NUMBER_ERROR,
	PIN_DIR_ERROR,
	PORT_ERROR,
	PIN_MODE_ERROR
	}PIN_ERROR_TYPES;

#define OK 1
#define NOK 0
#endif