/*
 * 文件名: painter.c
 * -------------
 * 简单的画图程序，支持橡皮擦功能，以及 13 种颜色选择.
 *
 * 使用方法：
 *      鼠标左键按住：画图
 *      鼠标右键单击：切换画图/橡皮擦模式
 *      鼠标滚轮滑动：切换画笔颜色
 */

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

static char prompt[]     = "Left: draw, Right: erase, Scroll: select color.";
static char indicatorT[] = "Color: %s, Erase mode: %s";
static double labelX, labelY;
static double xIndicator, yIndicator;

static bool eraseMode = FALSE;
static int currentColor = 0;
const  int MaxColors    = 13;
static char* colors[]   =
{
    "Black",
    "Dark Gray",
    "Gray",
    "Light Gray",
    "Brown",
    "Red",
    "Orange",
    "Yellow",
    "Green",
    "Blue",
    "Violet",
    "Magenta",
    "Cyan"
};

void MouseEventProcess(int x, int y, int button, int event);
void ToggleEraseMode(bool statu);
void drawTexts();

void Main()
{
    InitGraphics();

    registerMouseEvent(MouseEventProcess);

    SetPenColor(colors[currentColor]);
    SetPenSize(1);

    labelX = (GetWindowWidth() - TextStringWidth(prompt)) / 2;
    labelY = GetWindowHeight() - 2*GetFontHeight();
    yIndicator = GetWindowHeight() - 3*GetFontHeight();
    drawTexts();


}

void ToggleEraseMode(bool statu)
{
    if (TRUE == statu)
    {
        SetPenColor("White");
        SetPenSize(1000);
    }
    else
    {
        SetPenColor(colors[currentColor]);
        SetPenSize(1);
    }
}

void drawTexts()
{
    char indicator[100];

    SetPenSize(1);
    SetPenColor("White");
    drawRectangle(labelX, yIndicator-0.02, TextStringWidth(prompt), 2*GetFontHeight(), TRUE);

    SetPenColor(colors[currentColor]);
    sprintf(indicator, indicatorT, colors[currentColor], eraseMode?"On":"Off");
    xIndicator = (GetWindowWidth() - TextStringWidth(indicator)) / 2;

    drawLabel(labelX, labelY, prompt);
    drawLabel(xIndicator, yIndicator, indicator);

    ToggleEraseMode(eraseMode);
}

void MouseEventProcess(int x, int y, int button, int event)
{
    static bool isDraw    = FALSE;
    static double omx, omy;
    double mx, my;

    mx = ScaleXInches(x);/*pixels --> inches*/
    my = ScaleYInches(y);/*pixels --> inches*/

    switch (event) {
    case BUTTON_DOWN:
        if (button == LEFT_BUTTON)
        {
            isDraw = TRUE;
            omx = mx;
            omy = my;
        }
        break;
    case BUTTON_UP:
        if (button == LEFT_BUTTON)
        {
            isDraw = FALSE;
        }
        else if (button == RIGHT_BUTTON)
        {
            eraseMode = !eraseMode;
            ToggleEraseMode(eraseMode);
            drawTexts();
        }
        break;
    case ROLL_UP:
        currentColor = (currentColor + 1) % MaxColors;
        SetPenColor(colors[currentColor]);
        drawTexts();
        break;
    case ROLL_DOWN:
        currentColor--;
        if (currentColor < 0) currentColor += MaxColors;
        SetPenColor(colors[currentColor]);
        drawTexts();
        break;
    case BUTTON_DOUBLECLICK:
        DisplayClear();
        drawTexts();
        break;
    case MOUSEMOVE:
        if (isDraw)
        {
            MovePen(omx, omy);
            DrawLine(mx - omx, my - omy);
            omx = mx;
            omy = my;
            if (eraseMode)
            {
                ToggleEraseMode(FALSE);
                drawTexts();
                ToggleEraseMode(TRUE);
            }
        }
        break;
    }
}
