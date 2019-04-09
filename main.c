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

#define BS    8     // 退格
#define HT    9     // TAB
#define CR    13    // 回车是 \r
#define ESC   27

#define MAXLEN 75

static char   text[MAXLEN + 5];     // 输入的字符串缓冲区
static int    textlen = 0;          // 输入的字符串长度
static double startX, startY;       // 字符串的起始位置
static double cursorX, cursorY;     // 光标位置


void CharEventProcess(char c);

void Main()
{
    SetWindowTitle("Input area");
    SetWindowSize(7.0, 1.0);
    InitGraphics();

    registerCharEvent(CharEventProcess);/*注册字符消息回调函数*/

    SetPenColor("Red");
    SetPenSize(1);

    cursorX = startX = GetWindowWidth() / 12;
    cursorY = startY = GetWindowHeight() / 2;
    MovePen(startX, startY);

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
        if (textlen == 0) break;
        text[--textlen] = '\0';
        MovePen(startX, startY);
        DisplayClear();
        DrawTextString(text);
        break;
    default:
        if (textlen > MAXLEN) break;  // 输入超过最大长度则不接受
        str[0] = c;
        text[textlen++] = c;
        text[textlen] = '\0';
        DrawTextString(str);         // 输出当前字符，且输出位置相应后移
        break;
    }
}
