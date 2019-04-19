#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include <stdbool.h>

#define BS    8     // 退格
#define HT    9     // TAB
#define CR    13    // 回车是 \r
#define ESC   27

#define TIMER_BLINK  1      // 光标闪烁定时器编号
#define INTERVAL     500    // 500毫秒

#define MAXLEN       75     // 限制用户输入的最大长度

#define BACKWARD     true   // shiftText 指示

static char   text[MAXLEN + 5];     // 输入的字符串缓冲区
static int    textlen = 0;          // 输入的字符串长度
static int    textpos = 0;          // 当前光标在字符串中位置
static double startX, startY;       // 字符串的起始位置
static double cursorX, cursorY;     // 光标位置


void CharEventProcess       (char c);
void TimerEventProcess      (int timerID);
void KeyboardEventProcess   (int key, int event);
void PrintText              (bool cursorOn);
void insertChar             (char c);
void removeChar             ();

void Main()
{
    SetWindowTitle("Input area");
    SetWindowSize(7.0, 1.0);
    InitGraphics();

    registerCharEvent(CharEventProcess);
    registerTimerEvent(TimerEventProcess);
    registerKeyboardEvent(KeyboardEventProcess);

    SetPenColor("Red");
    SetPenSize(1);

    cursorX = startX = GetWindowWidth() / 12;
    cursorY = startY = GetWindowHeight() / 2;
    MovePen(startX, startY);

    startTimer(TIMER_BLINK, INTERVAL);

}

void CharEventProcess(char c)
{
    static char str[2] = {'\0', '\0'};

    switch (c) {
    case ESC:
    case HT:
        break;
    case CR:
        InitConsole();
        printf("Your input: %s\n", text);
        break;
    case BS:
        if (textlen == 0 || textpos == 0) break;
        str[0] = text[textpos];
        cursorX -= TextStringWidth(str);
        removeChar();
        textlen--;
        textpos--;
        PrintText(false);
        break;
    default:
        if (textlen > MAXLEN) break;  // 输入超过最大长度则不接受
        str[0] = c;
        cursorX += TextStringWidth(str);
        textlen++;
        insertChar(c);
        textpos++;
        PrintText(false);
        break;
    }
}

void TimerEventProcess(int timerID)
{
    static bool cursorOn = false;

    PrintText(cursorOn);
    cursorOn = !cursorOn;
}

void KeyboardEventProcess(int key, int event)
{
    if (event != KEY_DOWN)
        return;

    char str[2] = {'\0', '\0'};
    switch(key)
    {
        case VK_LEFT:
            if (textpos > 0)
            {
                textpos--;
                str[0] = text[textpos];
                cursorX -= TextStringWidth(str);
            }
            break;
        case VK_RIGHT:
            if (textpos < textlen)
            {
                str[0] = text[textpos];
                cursorX += TextStringWidth(str);
                textpos++;
            }
            break;
        default:
            break;
    }
}

void PrintText(bool cursorOn)
{
    DisplayClear();
    MovePen(startX, startY);

    if (cursorOn == false)
        DrawTextString(text);
    else
    {
        char str[2] = {'\0', '\0'};
        str[0] = text[textpos];
        text[textpos] = '\0';
        DrawTextString(text);    // 光标位置前的字符串

        text[textpos] = str[0];
        DrawTextString("_");
        MovePen(cursorX, cursorY);
        DrawTextString(text+textpos);
    }
}

void insertChar(char c)
{
    int i;
    for (i = textlen; i > textpos; i--)
    {
        text[i] = text[i-1];
    }
    text[textpos] = c;
}

void removeChar()
{
    int i;
    for (i = textpos; i < textlen; i++)
    {
        text[i] = text[i+1];
    }
}

void shiftText(bool backward)
{
    int i;
    if (backward)
    {
        for (i = textpos; i < textlen; i++)
        {
            text[i] = text[i+1];
        }
    }
    else
    {
        for (i = textlen; i > textpos; i--)
        {
            text[i] = text[i-1];
        }
    }
}