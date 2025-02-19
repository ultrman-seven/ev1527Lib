#ifndef D3078212_B5E9_4D7A_824A_F7A124F239C9
#define D3078212_B5E9_4D7A_824A_F7A124F239C9

#ifdef __C51__

#define evU32_t unsigned long
#define evU16_t unsigned int
#define evU8_t unsigned char

#define evS32_t long
#define evS16_t int
#define evS8_t char

#else
#include "stdint.h"

#define evU32_t uint32_t
#define evU16_t uint16_t
#define evU8_t uint8_t

#define evS32_t int32_t
#define evS16_t int16_t
#define evS8_t int8_t
#endif

#define evU32_c const evU32_t
#define evU16_c const evU16_t
#define evU8_c const evU8_t

#define evS32_c const evS32_t
#define evS16_c const evS16_t
#define evS8_c const evS8_t

#endif /* D3078212_B5E9_4D7A_824A_F7A124F239C9 */
