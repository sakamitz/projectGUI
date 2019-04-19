/*
 * 文件名: drawKochSnow.c
 * -------------
 * 利用新定义的DrawPolarLine函数画出分形图案
 *
 * 使用方法：
 *      输入迭代阶数 n;
 *      输入初始三角形边长 length.
 */

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>

#define PI 3.1415926

double length;

static void DrawPolarLine(double r, double theta)
{
    double radians;

    radians = theta / 180 * PI;
    DrawLine(r * cos(radians), r * sin(radians));
}

void drawKochSnow();

void Main()
{
    int n;
    InitGraphics();
    SetPenColor("Blue");
    SetPenSize(1);

    InitConsole();
    printf("Enter n: ");
    n = GetInteger();
    printf("Enter length: ");
    length = GetReal();
    FreeConsole();

    MovePen(GetWindowWidth()/2.0 - length/2.0,
            GetWindowHeight()/2 - length/2.0*tan(30.0/180.0*PI));

    length = length / pow(3.0, (float)n);

    drawKochSnow(n, 60);
    drawKochSnow(n, -60);
    drawKochSnow(n, 180);
}

void drawKochSnow(int n, int theta)
{
    if (n == 0)
    {
        DrawPolarLine(length, theta);
    }
    else
    {
        drawKochSnow(n-1, theta);
        drawKochSnow(n-1, theta + 60);
        drawKochSnow(n-1, theta - 60);
        drawKochSnow(n-1, theta);
    }
}
