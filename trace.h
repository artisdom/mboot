/*
 *------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------
 */

#ifndef __TRACE_H__
#define __TRACE_H__

#include "shell.h"

#define DEBUG_ENABLE		0

#if (DEBUG_ENABLE == 1)
#define TRACE_DEBUG(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;34mD: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__); ShellPrintf("\n\r");}
#define TRACE_DEBUG_WP(...)		{ShellPrintf(__VA_ARGS__);}
#define DEBUG_MSG(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;34mD: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__); ShellPrintf("\n\r");}
#define DEBUG_MSG_WP(...)	{ShellPutByte(0x1B); ShellPrintf("[1;1;34mD: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__);}

#define ASSERT(condition, ...)  { \
    if (!(condition)) { \
        ShellPrintf("ASSERT: "); \
        ShellPrintf(__VA_ARGS__); \
        while (1); \
    } \
}
#define SANITY_ERROR            "Sanity check failed at %s:%d\n\r"

/// Performs the same duty as the ASSERT() macro, except a default error
/// message is output if the condition is false.
/// \param condition  Condition to verify.
#define SANITY_CHECK(condition) ASSERT(condition, SANITY_ERROR, __FILE__, __LINE__)
		

#else
#define TRACE_DEBUG(...)		{ }
#define TRACE_DEBUG_WP(...)		{ShellPrintf(__VA_ARGS__);}
#define DEBUG_MSG(...)		{ }
#define DEBUG_MSG_WP(...)	{ }
#define ASSERT(...)
#define SANITY_CHECK(...)
#endif


#define PRINT_F(...)		{ShellPrintf(__VA_ARGS__);}
#define TRACE_MSG(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;34mI: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__); ShellPrintf("\n\r");}
#define TRACE_FIN(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;32mF: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__); ShellPrintf("\n\r");}
#define TRACE_WRN(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;33m!: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__); ShellPrintf("\n\r");}
#define TRACE_ERR(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;31mE: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__); ShellPrintf("\n\r");}



#define TRACE_ERROR(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;31mE: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__); ShellPrintf("\n\r");}
#define TRACE_INFO(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;34mI: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__); ShellPrintf("\n\r");}
#define TRACE_WARNING(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;33m!: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__); ShellPrintf("\n\r");}
#define TRACE_ERROR_WP(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;31mE: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__);}
#define TRACE_INFO_WP(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;34mI: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__);}
#define TRACE_WARNING_WP(...)		{ShellPutByte(0x1B); ShellPrintf("[1;1;33m!: "); ShellPutByte(0x1B); ShellPrintf("[m"); ShellPrintf(__VA_ARGS__);}

#endif /* __TRACE_H__ */
