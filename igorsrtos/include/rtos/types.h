/*
 * types.h
 *
 *  Created on: Jul 23, 2019
 *      Author: igor
 */

#ifndef IGORSRTOS_INCLUDE_TYPES_H_
#define IGORSRTOS_INCLUDE_TYPES_H_
#ifdef __cplusplus
extern "C" {
#endif

/* inside system use only these types */
typedef unsigned char u8;
typedef signed char i8;
typedef unsigned short u16;
typedef signed short i16;
typedef unsigned int u32;
typedef signed int i32;
typedef unsigned long uptr;
typedef signed long iptr;
typedef unsigned long long u64;
typedef signed long long i64;
typedef signed int ssize;
typedef signed long ptrdiff;
typedef enum {
	FALSE = 0,
	TRUE = 1
} BOOL;

#ifndef NULL
#define NULL (void*)0
#endif

#ifdef PRIVATE
#undef PRIVATE
#endif
#define PRIVATE static
/* attributes */
#ifndef WEAK
#define WEAK __attribute__((weak))
#endif

/* definitions */
#define RTOS_FAILURE (int)(-1)
#define RTOS_SUCCESS (int)(0)





#ifdef __cplusplus
}
#endif
#endif /* IGORSRTOS_INCLUDE_TYPES_H_ */
