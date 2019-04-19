/*
 * 文件名: drawBurg.c
 * -------------
 * 调用图形库，画出一个简单的城堡.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "genlib.h"
#include "conio.h"

#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

/*
 * Constants
 * ---------
 * The following constants control the sizes of the
 * various elements in the display.
 */

#define AtticHeight        1.0

#define BoxWidth           1.0
#define BoxHeight          1.4

#define FenceWidth         (BoxWidth/6)

/* Function prototypes */

void DrawBurg(double x, double y);
void DrawFences(double x, double y);
void DrawBox(double x, double y, double width, double height);
void DrawTriangle(double x, double y, double base, double height);
void DrawGrid(double x, double y, double width, double height,
              int columns, int rows);

/* Main program */

void Main()
{
    double cx, cy;

    InitGraphics();
    cx = GetWindowWidth() / 2;
    cy = GetWindowHeight() / 2;
    DrawBurg(cx - BoxWidth * 2, cy - (BoxHeight + AtticHeight/2));
}

/*
 * Function: DrawBurg
 * Usage: DrawBurg(x, y);
 * -----------------------
 * This function draws a Burg diagram with the lower left corner
 * at (x, y).  This level of the function merely divides up
 * the work.
 */

void DrawBurg(double x, double y)
{
    DrawGrid(x, y, BoxWidth, BoxHeight, 4, 2);
    DrawTriangle(x, y + BoxHeight*2, BoxWidth, AtticHeight);
    DrawTriangle(x + BoxWidth*3, y + BoxHeight*2, BoxWidth, AtticHeight);
    DrawFences(x, y);
}


/*
 * Function: DrawFences
 * Usage: DrawFences(x, y);
 * -------------------------
 * This function draws all the fences for the burg,
 * taking advantage of the fact that the windows are all
 * arranged in a single line and keep the same distance.
 */

void DrawFences(double x, double y)
{
    int i;
    double xStart, yStart;

    xStart = x + BoxWidth;
    yStart = y + BoxHeight * 2;

    for (i = 0; i < 6; i++)
    {
        DrawBox(xStart + FenceWidth*2*i, yStart, FenceWidth, FenceWidth);
    }

}

/*
 * Function: DrawBox
 * Usage: DrawBox(x, y, width, height)
 * -----------------------------------
 * This function draws a rectangle of the given width and
 * height with its lower left corner at (x, y).
 */

void DrawBox(double x, double y, double width, double height)
{
    MovePen(x, y);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
}

/*
 * Function: DrawTriangle
 * Usage: DrawTriangle(x, y, base, height)
 * ---------------------------------------
 * This function draws an isosceles triangle (i.e., one with
 * two equal sides) with a horizontal base.  The coordinate of
 * the left endpoint of the base is (x, y), and the triangle
 * has the indicated base length and height.  If height is
 * positive, the triangle points upward.  If height is negative,
 * the triangle points downward.
 */

void DrawTriangle(double x, double y, double base, double height)
{
    MovePen(x, y);
    DrawLine(base, 0);
    DrawLine(-base / 2, height);
    DrawLine(-base / 2, -height);
}

/*
 * Function: DrawGrid
 * Usage: DrawGrid(x, y, width, height, columns, rows);
 * ----------------------------------------------------
 * DrawGrid draws rectangles arranged in a two-dimensional
 * grid.  As always, (x, y) specifies the lower left corner
 * of the figure.
 */

void DrawGrid(double x, double y, double width, double height,
              int columns, int rows)
{
    int i, j;

    for (i = 0; i < columns; i++) {
        for (j = 0; j < rows; j++) {
            DrawBox(x + i * width, y + j * height,
                    width, height);
        }
    }
}
