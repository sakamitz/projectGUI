/*
 * 文件名: main.c
 * -------------
 * 选择各个项目进行演示
 *
 * 项目内容：
 *      1. 画城堡.
 *      2. 画出给定的几何图案.
 *      3. 绘画程序，支持橡皮擦，以及 13 种颜色选择.
 *      4. 简单输入程序.
 *      5. 绘制 Koch 分形雪花.
 */

#define Demo_ID 1

#if Demo_ID == 1
#include "src/drawBurg.c"

#elif Demo_ID == 2
#include "src/drawPattern.c"

#elif Demo_ID == 3
#include "src/painter.c"

#elif Demo_ID == 4
#include "src/textInput.c"

#elif Demo_ID == 5
#include "src/drawKochSnow.c"

#endif

