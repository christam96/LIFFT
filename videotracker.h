/*
 * File: videotracker.cpp
 * Project: LIFFT - CS3307 Assignment Stage #3
 * Date: November 9th 2018
 * Group Members: Taebum Kim, Marisa Mathura, Christopher Tam, Justin Wang, Samuel Wong *
 *
*/

/// Temporary design pattern - will create class in later iterations of code

#ifndef VIDEOTRACKER_H
#define VIDEOTRACKER_H

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <ctype.h>

/// function used by main() to determine position of mouse click
static void mouse_click( int event, int x, int y, int , void* );

/// main function
int main();


#endif
