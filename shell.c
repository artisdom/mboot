/*
 * ------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------
 */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include "def.h"
#include "dbgu.h"
#include "shell.h"

U32
ShellPrintf(const char* format,...)
{
	S8 obuffer[256];
	U32 i=0, cnt;
	va_list ap;
	va_start(ap,format);
	cnt = vsprintf(obuffer,format,ap);
	while(i < cnt)
		ShellPutByte((S8)obuffer[i++]);
	va_end(ap);
	return cnt;
}

void
ShellAllClear(void)
{
	ShellPutByte(0x1b);
	ShellPrintf("c");
	ShellPutByte(0x1b);
	ShellPrintf("[m");
	ShellPutByte(0x1b);
	ShellPrintf("[2J\n\r\r\r\r\r\r\r");
}

void
ShellSendString(S8 *pt)
{
    while(*pt)
        ShellPutByte(*pt++);
}

void
ShellGetString(S8 *string)
{
    S8 *buf = string;
    S8 c;
    while((c = ShellGetByte())!='\r')
    {
        if(c=='\b')
        {
            if( (int)buf < (int)string )
            {
                ShellPrintf("\b \b");
                string--;
            }
        }
        else 
        {
            *string++ = c;
            ShellPutByte(c);
        }
    }
    *string='\0';
    ShellPutByte('\n');
}

S32
ShellGetIntNum(void)
{
    char str[30];
    char *string = str;
    int base     = 10;
    int minus    = 0;
    int result   = 0;
    int lastIndex;    
    int i;
    
    ShellGetString(string);
    
    if(string[0]=='-')
    {
        minus = 1;
        string++;
    }
    
    if(string[0]=='0' && (string[1]=='x' || string[1]=='X'))
    {
        base    = 16;
        string += 2;
    }
    
    lastIndex = strlen(string) - 1;
    
    if(lastIndex<0)
        return -1;
    
    if(string[lastIndex]=='h' || string[lastIndex]=='H' )
    {
        base = 16;
        string[lastIndex] = 0;
        lastIndex--;
    }

    if(base==10)
    {
        result = atoi(string);
        result = minus ? (-1*result):result;
    }
    else
    {
        for(i=0;i<=lastIndex;i++)
        {
            if(isalpha(string[i]))
            {
                if(isupper(string[i]))
                    result = (result<<4) + string[i] - 'A' + 10;
                else
                    result = (result<<4) + string[i] - 'a' + 10;
            }
            else
                result = (result<<4) + string[i] - '0';
        }
        result = minus ? (-1*result):result;
    }
    return result;
}

void
ShellPutByte(S8 c)
{
	DBGU_PutByte(c);
}

S8	
ShellGetByte(void)
{
	return DBGU_GetByte();
}

S8	
ShellGetKey(void)
{
	return DBGU_GetKey();
}
