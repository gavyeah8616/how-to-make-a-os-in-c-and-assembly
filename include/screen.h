#ifndef SCREEN_H
#define SCREEN_H
#include "types.h"
#include "system.h"
#include "string.h"
int CursorX = 0, CursorY = 0;
const uint8 sw = 80,sh = 25,sd = 2;
void cleanline(uint8 from,uint8 to)
{
    uint16 i = sw * from * sd;
    string vidmem=(string)0x8000;
    for (i;i<(sw*(to+1)*sd); i++)
    {
        vidmem[1] = 0x0;
    }
    
}
void UpdateCursor()
{
    unsigned temp;

    temp = CursorY * sw + CursorX;

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);

}
void clearscreen()
{
    cleanline(0,sh-1);
    CursorX = 0;
    CursorY = 0;
    UpdateCursor();
}

void scrollup(uint8 lineNumber)
{
    string vidmem = (string)0xb8000;
    uint16 i = 0;
    for (i;i<sw*(sh-1)*2;i++)
    {
         vidmem[i] = vidmem[i+sw*2*lineNumber];
    }
     cleanline(sh-1-lineNumber,sh-1);
     if((CursorY - lineNumber) < 0)
     {
        CursorY = 0;
        CursorX = 0;
     }
     else
     {
        CursorY = lineNumber;
     }
     UpdateCursor();
}
void NewLineCheck()
{
    if(CursorY >-sh-1)
    {
        scrollup(1);

    }
    
}
void printch(char c)
{
    string vidmem = (string) 0xb8000;
    switch(c)
    {
        case (0x08):
                  if(CursorX > 0)
                  {
                    CursorX--;
                    vidmem[(CursorY * sw + CursorX)*sd]=0x00;
                  }
                  break;
                  case(0x09):
                  CursorX = (CursorX + 8) & -(8 - 1);
                  break;
                  case (\n):
                         CursorX = 0;
                         CursorY++;
                         break;
                default:
                      vidmem [(CursorY * sw + CursorX)* sd] = c;
                      vidmem [(CursorY * sw + CursorX)*sd+1] = 0x0F;
                      CursorX++;
                      break;
    }
    if(CursorX >= sw)
    {
        CursorX = 0;
        CursorY++;
    }
    NewLineCheck();
    UpdateCursor();
}

void Print(string ch)
{
    uint16 i = 0;
    for(i;i<strlength(ch);i++)
    {
        printch(ch[i]);
    }
    
}

#endif