/*
 * 文件名: enhancedGUI.c
 * -------------
 * 实现 enhancedGUI.h 中定义的用户接口
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

#include <math.h>
#include "enhancedGUI.h"

/* 当前角度，初始值为0，表示坐标轴的横轴方向（正东）*/
static double currentAngle = 0;

void SetCurrentAngle(double newAngle)
{
    currentAngle = newAngle;
}

double GetCurrentAngle()
{
    return currentAngle;
}

double toRAD(double angle)
{
    return PI*angle / 180; // PI在 enhancedGUI.h 中定义
}

void forward(double distance)
{
    double dx = distance * cos(toRAD(currentAngle)); // 数学函数使用弧度制
    double dy = distance * sin(toRAD(currentAngle));

    DrawLine(dx, dy);
}

void turn (double angle)
{
    currentAngle += angle;
}

void move(double distance)
{
    double dx = distance * cos(toRAD(currentAngle));
    double dy = distance * sin(toRAD(currentAngle));

    MovePen(GetCurrentX() + dx, GetCurrentY() + dy);
}
