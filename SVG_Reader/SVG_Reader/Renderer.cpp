#include "Lib.h"
using namespace std;

void renderer::drawFigure(vector<figure*> figures, HDC hdc) {
	Graphics graphics(hdc);
	factoryfigure factory;
	for (figure* fig : figures) {
		int num = factory.getFigureId()[fig->getName()];

		switch (num)
		{
		case 1:
		{
			rectangle* rect = dynamic_cast<rectangle*>(fig);
			drawRectangle(graphics, rect);
			break;
		}
		case 2: case 3: {
			ellipse* ellipses = dynamic_cast<ellipse*>(fig);
			drawEllipse(graphics, ellipses);
			break;
		}
		case 4:
		{
			line* lines = dynamic_cast<line*>(fig);
			drawLine(graphics, lines);
			break;
		}
		case 5: {
			polyline* polylines = dynamic_cast<polyline*>(fig);
			drawPolyline(graphics, polylines);
			break;
		}
		case 6: {
			polygon* polygons = dynamic_cast<polygon*>(fig);
			drawPolygon(graphics, polygons);
			break;
		}
		case 7: {
			text* texts = dynamic_cast<text*> (fig);
			drawText(graphics, texts);
			break;
		}
		/*case 8: {
			path* paths = dynamic_cast<path*>(fig);
			drawPath(graphics, paths);
			break;
		}*/
		default:
			break;
		}
	}
}

void renderer::renderItem(vector<figure*> figures, float antialiasingLevel, string imageName, float width, float height, HDC hdc) {
	drawFigure(figures, hdc);
}

void renderer::drawRectangle(Graphics& graphics, rectangle* fig) {
	Pen penRectangle(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	SolidBrush fillRectangle(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	
	graphics.FillRectangle(&fillRectangle, fig->getRoot().getX(), fig->getRoot().getY(), fig->getWidth(), fig->getHeight());
	graphics.DrawRectangle(&penRectangle, fig->getRoot().getX(), fig->getRoot().getY(), fig->getWidth(), fig->getHeight());
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
}

void renderer::drawEllipse(Graphics& graphics, ellipse* fig) {
	Pen penEllipse(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	SolidBrush fillEllipse(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	
	graphics.FillEllipse(&fillEllipse, fig->getCenter().getX() - fig->getRx(), fig->getCenter().getY() - fig->getRy(), 2.0 * fig->getRx(), 2.0 * fig->getRy());
	graphics.DrawEllipse(&penEllipse, fig->getCenter().getX() - fig->getRx(), fig->getCenter().getY() - fig->getRy(), 2.0 * fig->getRx(), 2.0 * fig->getRy());
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
}

void renderer::drawLine(Graphics& graphics, line* fig) {
	Pen penLine(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	
	graphics.DrawLine(&penLine, fig->getP1().getX(), fig->getP1().getY(), fig->getP2().getX(), fig->getP2().getY());
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
}

void renderer::drawPolygon(Graphics& graphics, polygon* fig) {
	Pen penPolygon(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	SolidBrush fillPolygon(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	
	int numPoint = fig->getVers().size();
	PointF* p = new PointF[numPoint];
	for (int i = 0; i < numPoint; i++)
		p[i] = PointF(fig->getVers()[i].getX(), fig->getVers()[i].getY());
	
	graphics.FillPolygon(&fillPolygon, p, numPoint, FillModeWinding);
	graphics.DrawPolygon(&penPolygon, p, numPoint);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	
	delete[] p;
}

void renderer::drawPolyline(Graphics& graphics, polyline* fig) {
	Pen penPolyline(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	SolidBrush fillPolyline(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	
	int numPoint = fig->getVers().size();
	PointF* p = new PointF[numPoint];
	for (int i = 0; i < numPoint; i++)
		p[i] = PointF(fig->getVers()[i].getX(), fig->getVers()[i].getY());
	
	graphics.FillPolygon(&fillPolyline, p, numPoint, FillModeWinding);
	graphics.DrawLines(&penPolyline, p, numPoint);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	
	delete[] p;
}

void renderer::drawText(Graphics& graphics, text* fig) {
	wstring_convert<codecvt_utf8<wchar_t>> converter;
	wstring wContent = converter.from_bytes(fig->getContent());
	wstring wFontFamily = converter.from_bytes(fig->getFontFamily());
	FontFamily WFF = wFontFamily.c_str();

	PointF textPosition;
	StringFormat stringFormat;
	if (fig->getTextAnchor() == "start") {
		textPosition = PointF(fig->getTextPos().getX() + fig->getDx(), fig->getTextPos().getY() + fig->getDy() - fig->getFontSize());
		stringFormat.SetAlignment(StringAlignmentNear);
		stringFormat.SetLineAlignment(StringAlignmentNear);
	}
	else if (fig->getTextAnchor() == "middle") {
		textPosition = PointF(fig->getTextPos().getX() + fig->getDx() - fig->getFontSize() / 20.f, fig->getTextPos().getY() + fig->getDy() - fig->getFontSize() / 20.f);
		stringFormat.SetAlignment(StringAlignmentCenter);
		stringFormat.SetLineAlignment(StringAlignmentCenter);
	}
	else if (fig->getTextAnchor() == "end") {
		textPosition = PointF(fig->getTextPos().getX() + fig->getDx() - fig->getFontSize(), fig->getTextPos().getY() + fig->getDy() - fig->getFontSize());
		stringFormat.SetAlignment(StringAlignmentFar);
		stringFormat.SetLineAlignment(StringAlignmentFar);
	}
	else {
		textPosition = PointF(fig->getTextPos().getX() + fig->getDx() - fig->getFontSize(), fig->getTextPos().getY() + fig->getDy() - fig->getFontSize());
		stringFormat.SetAlignment(StringAlignmentNear);
		stringFormat.SetLineAlignment(StringAlignmentNear);
	}
	
	GraphicsPath path;
	if (fig->getFontStyle() == "italic")
		path.AddString(wContent.c_str(), -1, &WFF, FontStyleItalic, fig->getFontSize(), textPosition, &stringFormat);
	else if (fig->getFontStyle() == "bold")
		path.AddString(wContent.c_str(), -1, &WFF, FontStyleBold, fig->getFontSize(), textPosition, &stringFormat);
	else path.AddString(wContent.c_str(), -1, &WFF, FontStyleRegular, fig->getFontSize(), textPosition, &stringFormat);

	SolidBrush fillText(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	Pen penText(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	graphics.FillPath(&fillText, &path);
	graphics.DrawPath(&penText, &path);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
}

//void renderer::drawPath(Graphics& graphics, path* fig) {
//
//}