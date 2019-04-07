/*
 * 文件名: enhancedGUI.h
 * -------------
 * 为 libgraphics 增加角度支持.
 *
 * PS: 我觉得不应把 currentAngle 定义为全局变量，
 *     所以我留了两个外部接口来操作：
 *     void   SetCurrentAngle(double newAngle)
 *     double GetCurrentAngle()
 */

#ifndef _ENHANCED_GUI
#define _ENHANCED_GUI

#define PI 3.1415926

/* 当前角度，初始值为0，表示坐标轴的横轴方向（正东）*/
static double currentAngle;

/*
 * 函数: SetCurrentAngle
 * 用法: SetCurrentAngle(newAngle);
 * ------------------------
 * 设置当前角度
 */
void SetCurrentAngle(double newAngle);

/*
 * 函数: GetCurrentAngle
 * 用法: GetCurrentAngle();
 * ------------------------
 * 取得当前角度
 */
double GetCurrentAngle();

/*
 * 函数: toRAD
 * 用法: toRAD(angle);
 * ------------------------
 * 将角度制转换为弧度制
 */
double toRAD(double angle);

/*
 * 函数: forward
 * 用法: forward(distance);
 * ------------------------
 * 沿当前方向画线，长度为distance，当distance为负数时后退
 */
void forward(double distance);

/*
 * 函数: turn
 * 用法: turn(angle);
 * ------------------------
 * 顺时针旋转角度angle，角度单位为DEG，当angle为负数时逆时针旋转
 */
void turn (double angle);

/*
 * 函数: move
 * 用法: move(distance);
 * ------------------------
 * 沿当前方向移动笔（不画线），长度为distance，当distance为负数时后退
 */
void move(double distance);

#endif