#ifndef _LIB_H_
#define _LIB_H_

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

#include "framework.h"
#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#include "Color.h"
#include "Point.h"
#include "Gradient.h"
#include "LinearGradient.h"
#include "RadialGradient.h"
#include "Figure.h"
#include "Group.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Polyline.h"
#include "Line.h"
#include "Text.h"
#include "Path.h"
#include "FactoryFigure.h"
#include "Viewbox.h"
#include "Parser.h"
#include "Renderer.h"
#include "Image.h"

#endif 