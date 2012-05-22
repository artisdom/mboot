/*
 *------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------
 */

#ifndef __SHELL_H__
#define __SHELL_H__

#include "def.h"

#define SHELL_INF(...)		{ShellPrintf(__VA_ARGS__); ShellPrintf("\n\r");}
#define SHELL_DATA(...)		{ShellPrintf(__VA_ARGS__);}
#define SHELL_EMPTY()		{ShellPrintf("\n\r");}
#define SHELL_BNNER()		{ShellPrintf("==========================================\n\r");}

void ShellAllClear(void);

U32 ShellPrintf(const char* format,...);
void ShellSendString(S8 *pt);
void ShellGetString(S8 *string);
S32 ShellGetIntNum(void);

void ShellPutByte(S8 c);
S8 ShellGetByte(void);
S8 ShellGetKey(void);

#endif /* __SHELL_H__ */
