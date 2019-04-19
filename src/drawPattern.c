/*
 * 文件名: drawPattern.c
 * -------------
 * 利用增加了角度支持的图形库画出指定图形.
 * 增强模块位置：lib/enhancedGUI.h
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

#include "enhancedGUI.h"

#define EdgeOfRhombus  1.5
#define EdgeOfHexagon  (2 * EdgeOfRhombus)

double cx, cy;  // 中心位置

void drawPattern();
void drawRhombus(double edge);
void drawHexagon(double edge);

void Main()
{
    InitGraphics();

    SetPenColor("Magenta");
    drawPattern();
}

void drawPattern()
{
    cx = GetWindowWidth() / 2;
    cy = GetWindowHeight() / 2;

    MovePen(cx, cy);
    SetCurrentAngle(30.0);  // 从右边第一个画起

    int i;
    for (i = 0; i < 18; i++)
    {
        drawRhombus(EdgeOfRhombus);
        turn(-20.0);
    }

    SetCurrentAngle(90.0);
    for (i = 0; i < 3; i++)
    {
        drawHexagon(EdgeOfHexagon);
        turn(-20);
    }
}

/*
 * 函数: drawRhombus
 * 用法: drawRhombus(edge);
 * ------------------------
 * 以当前方向为始边，沿顺时针画一个边长为 edge 的菱形
 */
void drawRhombus(double edge)
{
    forward(edge);

    turn(-60);
    forward(edge);

    turn(-120);
    forward(edge);

    turn(-60);
    forward(edge);

    turn(-120);    // 恢复原方向
}

/*
 * 函数: drawHexagon
 * 用法: drawHexagon(edge);
 * ------------------------
 * 以当前点为中心，沿顺时针画一个边长为 edge 的正六边形
 */
void drawHexagon(double edge)
{
    move(edge);
    turn(-60);

    int i;
    for (i = 0; i < 6; i++)
    {
        turn(-60);
        forward(edge);
    }

    turn(60);
    move(-edge);    // 恢复原点和原方向
}