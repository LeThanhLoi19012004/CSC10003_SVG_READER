#ifndef _LIB_H_
#define _LIB_H_

// Standard C++ libraries
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <stack>
#include <locale>
#include <codecvt>

// Windows libraries
#include "framework.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib, "Gdiplus.lib")

// Rapidxml
#include "rapidxml.hpp"

// Namespace declarations
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;

// SVG headers
#include "Color.h"
#include "Figure.h"
#include "Group.h"
#include "Point.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Polyline.h"
#include "Line.h"
#include "Text.h"
#include "Path.h"
#include "FactoryFigure.h"
#include "Parser.h"
#include "Renderer.h"
#include "Image.h"
#include "Program.h"

#endif