/**
* This source code ("the Software") is provided by Bridgetek Pte Ltd
* ("Bridgetek") subject to the licence terms set out
*   http://brtchip.com/BRTSourceCodeLicenseAgreement/ ("the Licence Terms").
* You must read the Licence Terms before downloading or using the Software.
* By installing or using the Software you agree to the Licence Terms. If you
* do not agree to the Licence Terms then do not download or use the Software.
*
* Without prejudice to the Licence Terms, here is a summary of some of the key
* terms of the Licence Terms (and in the event of any conflict between this
* summary and the Licence Terms then the text of the Licence Terms will
* prevail).
*
* The Software is provided "as is".
* There are no warranties (or similar) in relation to the quality of the
* Software. You use it at your own risk.
* The Software should not be used in, or for, any medical device, system or
* appliance. There are exclusions of Bridgetek liability for certain types of loss
* such as: special loss or damage; incidental loss or damage; indirect or
* consequential loss or damage; loss of income; loss of business; loss of
* profits; loss of revenue; loss of contracts; business interruption; loss of
* the use of money or anticipated savings; loss of information; loss of
* opportunity; loss of goodwill or reputation; and/or loss of, damage to or
* corruption of data.
* There is a monetary cap on Bridgetek's liability.
* The Software may have subsequently been amended by another user and then
* distributed by that other user ("Adapted Software").  If so that user may
* have additional licence terms that apply to those amendments. However, Bridgetek
* has no liability in relation to those amendments.
*/

#ifndef _FT_DATATYPES_H_
#define _FT_DATATYPES_H_
//#include <cmsis_os.h>
#define FT_FALSE           (0)
#define FT_TRUE            (1)

typedef unsigned char ft_uint8_t;
typedef char ft_char8_t;
typedef signed char ft_schar8_t;
typedef unsigned char ft_uchar8_t;
typedef int  ft_int16_t;
typedef unsigned short ft_uint16_t;
typedef unsigned long ft_uint32_t;
typedef long ft_int32_t;
typedef void ft_void_t;
typedef char ft_bool_t;
typedef double ft_double_t;
typedef long long ft_int64_t;
typedef unsigned long long ft_uint64_t;
//typedef Bool ft_bool_t;

#define ft_prog_uchar8_t  ft_uchar8_t
#define ft_prog_char8_t   ft_char8_t
#define ft_prog_uint16_t  ft_uint16_t


//typedef prog_uchar  ft_prog_uchar8_t;
//typedef prog_char   ft_prog_char8_t;
//typedef prog_uint16_t ft_prog_uint16_t;

#define ft_delay(x) Delay_ms(x)
#define min(X,Y) ((X) < (Y) ?  (X) : (Y))
#define max(X,Y) ((X) > (Y) ?  (X) : (Y))
//#define FT_PROGMEM PROGMEM
//#define ft_pgm_read_byte_near pgm_read_byte_near
//#define ft_pgm_read_byte pgm_read_byte
//#define ft_pgm_read_word pgm_read_word
//#define ft_random(x)		(random(x))

//#define TRUE     (1)
//#define FALSE    (0)


#if (defined(MSVC_FT800EMU) || defined(ESD_SIMULATION))


#define FT_FALSE           (0)
#define FT_TRUE            (1)

/* Inclusion of datatypes from MSVC */

typedef char ft_char8_t;
typedef signed char ft_schar8_t;
typedef unsigned char ft_uchar8_t;
typedef ft_uchar8_t ft_uint8_t;
typedef short  ft_int16_t;
typedef unsigned short ft_uint16_t;
typedef unsigned int ft_uint32_t;
typedef int ft_int32_t;
typedef void ft_void_t;
typedef long long ft_int64_t;
typedef unsigned long long ft_uint64_t;
typedef float ft_float_t;
typedef double ft_double_t;
typedef _Bool ft_bool_t;

#define FT_BYTE_SIZE (1)
#define FT_SHORT_SIZE (2)
#define FT_WORD_SIZE (4)
#define FT_DWORD_SIZE (8)

#define FT_NUMBITS_IN_BYTE (1*8)
#define FT_NUMBITS_IN_SHORT (2*8)
#define FT_NUMBITS_IN_WORD (4*8)
#define FT_NUMBITS_IN_DWORD (8*8)

#define ft_prog_uchar8_t  ft_uchar8_t
#define ft_prog_char8_t   ft_char8_t
#define ft_prog_uint16_t  ft_uint16_t


#define ft_random(x)		(rand() % (x))
#define ft_millis()         GetTickCount()

#define ft_pgm_read_byte_near(x)   (*(x))
#define ft_pgm_read_byte(x)        (*(x))

#define ft_strcpy_P     strcpy
#define ft_strlen_P     strlen

#define ft_delay(x) Ft_Gpu_Hal_Sleep(x)
#define FT_DBGPRINT(x)  ESD_print(x)
#define FT_PROGMEM

#define ft_pgm_read_byte_near(x)   (*(x))
#define ft_pgm_read_byte(x)        (*(x))

#define ft_pgm_read_word(addr)   (*(ft_int16_t*)(addr))

#ifdef _MSC_VER
#ifndef FT8XXEMU_INTTYPES_DEFINED_BASE
#define FT8XXEMU_INTTYPES_DEFINED_BASE
typedef unsigned __int8 uint8_t;
typedef signed __int8 int8_t;
typedef unsigned __int16 uint16_t;
typedef signed __int16 int16_t;
typedef unsigned __int32 uint32_t;
typedef signed __int32 int32_t;
typedef unsigned __int64 uint64_t;
typedef signed __int64 int64_t;
#endif
#else
#include <stdint.h>
#include <stdlib.h>
#endif
#ifndef FT8XXEMU_INTTYPES_DEFINED_COLOR
#define FT8XXEMU_INTTYPES_DEFINED_COLOR
typedef uint32_t argb8888;
#endif

#ifdef WIN32
#	define FT8XXEMU_FORCE_INLINE __forceinline
#else
#	define FT8XXEMU_FORCE_INLINE inline __attribute__((always_inline))
#endif

#ifndef FT8XXEMU_INTTYPES_DEFINED_FORCEINLINE
#define FT8XXEMU_INTTYPES_DEFINED_FORCEINLINE
#ifdef _MSC_VER
#	define FT8XXEMU_FORCE_INLINE __forceinline
#else
#	define FT8XXEMU_FORCE_INLINE inline __attribute__((always_inline))
#endif
#endif


#elif (defined(MSVC_PLATFORM))


#define FT_FALSE           (0)
#define FT_TRUE            (1)

/* Inclusion of datatypes from MSVC */
typedef char ft_char8_t;
typedef signed char ft_schar8_t;
typedef unsigned char ft_uchar8_t;
typedef ft_uchar8_t ft_uint8_t;
typedef short  ft_int16_t;
typedef unsigned short ft_uint16_t;
typedef unsigned int ft_uint32_t;
typedef int ft_int32_t;
typedef void ft_void_t;
typedef long long ft_int64_t;
typedef unsigned long long ft_uint64_t;
typedef float ft_float_t;
typedef double ft_double_t;
typedef _Bool ft_bool_t;

#define FT_BYTE_SIZE (1)
#define FT_SHORT_SIZE (2)
#define FT_WORD_SIZE (4)
#define FT_DWORD_SIZE (8)

#define FT_NUMBITS_IN_BYTE (1*8)
#define FT_NUMBITS_IN_SHORT (2*8)
#define FT_NUMBITS_IN_WORD (4*8)
#define FT_NUMBITS_IN_DWORD (8*8)

#define ft_prog_uchar8_t  ft_uchar8_t
#define ft_prog_char8_t   ft_char8_t
#define ft_prog_uint16_t  ft_uint16_t

#define ft_random(x)		(rand() % (x))
#define ft_millis()         GetTickCount()

#define ft_pgm_read_byte_near(x)   (*(x))
#define ft_pgm_read_byte(x)        (*(x))

#define ft_strcpy_P     strcpy
#define ft_strlen_P     strlen

#define ft_delay(x) Ft_Gpu_Hal_Sleep(x)
#define FT_DBGPRINT(x)  ESD_print(x)
#define FT_PROGMEM

#define ft_pgm_read_byte_near(x)   (*(x))
#define ft_pgm_read_byte(x)        (*(x))

#define ft_pgm_read_word(addr)   (*(ft_int16_t*)(addr))


#elif (defined(FT900_PLATFORM))


#define FT_FALSE           (0)
#define FT_TRUE            (1)

typedef char				ft_char8_t;
typedef signed char 		ft_schar8_t;
typedef unsigned char 		ft_uchar8_t;

typedef ft_uchar8_t 		ft_uint8_t;
typedef ft_uchar8_t 		byte;
typedef short  				ft_int16_t;
typedef unsigned short 		ft_uint16_t;
typedef unsigned int 		ft_uint32_t;
typedef int 				ft_int32_t;
typedef void 				ft_void_t;
typedef long long 			ft_int64_t;
typedef unsigned long long 	ft_uint64_t;
typedef float 				ft_float_t;
typedef double 				ft_double_t;
typedef _Bool 				ft_bool_t;


typedef volatile unsigned char 	ft_vuint8_t;
typedef volatile unsigned short ft_vuint16;
typedef volatile unsigned long 	ft_vuint32;

typedef volatile char 	ft_vint8;
typedef volatile short 	ft_vint16;
typedef volatile long 	ft_vint32;

#define ft_delay(x) Ft_Gpu_Hal_Sleep(x)
#define FT_DBGPRINT(x)  ESD_print(x)
#define ft_random(x)	rand() % x
#define min(X,Y) ((X) < (Y) ?  (X) : (Y))
#define max(X,Y) ((X) > (Y) ?  (X) : (Y))

#define ft_prog_uchar8_t  ft_uchar8_t __flash__ const
#define ft_prog_char8_t   ft_char8_t __flash__ const
#define ft_prog_uint16_t  ft_uint16_t __flash__ const

#define FT_PROGMEM __flash__
#define ft_pgm_read_byte_near(x)   (*((ft_prog_uchar8_t *)(x)))
#define ft_pgm_read_byte(x)        (*((ft_prog_uchar8_t *)(x)))
#define ft_pgm_read_word(addr)   (*((ft_prog_uint16_t *)(addr)))
#define TRUE     (1)


#endif


#endif /*_FT_DATATYPES_H_*/

/* Nothing beyond this*/
