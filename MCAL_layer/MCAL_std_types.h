/* 
 * File:   MCAL_std_types.h
 * Author: laphouse
 *
 * Created on June 27, 2024, 10:46 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/*section :     Includes    */
#include "std_libararies.h"
#include "Compiler.h"





/*section :     Macro Function Declarations    */


/*section :     Data Type Declarations    */
typedef unsigned long    uint32;
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef signed long      sint32;
typedef signed char     sint8;
typedef signed short    sint16;

typedef uint8   Std_ReturnType ;


/*section :     Macros Declarations    */
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00


#define E_OK        (Std_ReturnType)0x01
#define E_NOT_OK    (Std_ReturnType)0x00

/*section :      Function Declarations    */


#endif	/* MCAL_STD_TYPES_H */

