#include "Lib.h"
using namespace std;

void renderer::drawFigure(Graphics& graphics, vector<figure*> figures) {
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
		case 8: {
			path* paths = dynamic_cast<path*>(fig);
			drawPath(graphics, paths);
			break;
		}
		case 9: {
			group* groups = dynamic_cast<group*>(fig);
			drawGroup(graphics, groups);
			break;
		}
		default:
			break;
		}
	}
}

void renderer::renderItem(vector<figure*> figures, float antialiasingLevel, string imageName, float width, float height, HDC hdc) {
	Graphics graphics(hdc);
	drawFigure(graphics, figures);
}

void renderer::drawRectangle(Graphics& graphics, rectangle* fig) {
	GraphicsState save = graphics.Save();
	Pen penRectangle(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	SolidBrush fillRectangle(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	vector<pair<string, vector<float>>> transVct = fig->getTransVct();
		
	for (auto trans : transVct) {
		float x = 0.0f;
		if (!trans.second.empty())
			x = trans.second[0];
		float y = x;
		if (trans.second.size() == 2)
			y = trans.second[1];
		if (trans.first == "translate")
			graphics.TranslateTransform(x, y);
		else if (trans.first == "rotate")
			graphics.RotateTransform(x);
		else graphics.ScaleTransform(x, y);
	}
	
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.FillRectangle(&fillRectangle, fig->getRoot().getX(), fig->getRoot().getY(), fig->getWidth(), fig->getHeight());
	graphics.DrawRectangle(&penRectangle, fig->getRoot().getX(), fig->getRoot().getY(), fig->getWidth(), fig->getHeight());
	graphics.Restore(save);	
}

void renderer::drawEllipse(Graphics& graphics, ellipse* fig) {
	GraphicsState save = graphics.Save();
	Pen penEllipse(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	SolidBrush fillEllipse(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	vector<pair<string, vector<float>>> transVct = fig->getTransVct();

	for (auto trans : transVct) {
		float x = 0.0f;
		if (!trans.second.empty())
			x = trans.second[0];
		float y = x;
		if (trans.second.size() == 2)
			y = trans.second[1];
		if (trans.first == "translate")
			graphics.TranslateTransform(x, y);
		else if (trans.first == "rotate")
			graphics.RotateTransform(x);
		else graphics.ScaleTransform(x, y);
	}

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.FillEllipse(&fillEllipse, fig->getCenter().getX() - fig->getRx(), fig->getCenter().getY() - fig->getRy(), 2.0 * fig->getRx(), 2.0 * fig->getRy());
	graphics.DrawEllipse(&penEllipse, fig->getCenter().getX() - fig->getRx(), fig->getCenter().getY() - fig->getRy(), 2.0 * fig->getRx(), 2.0 * fig->getRy());
	graphics.Restore(save);
}

void renderer::drawLine(Graphics& graphics, line* fig) {
	GraphicsState save = graphics.Save();
	Pen penLine(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	vector<pair<string, vector<float>>> transVct = fig->getTransVct();

	for (auto trans : transVct) {
		float x = 0.0f;
		if (!trans.second.empty())
			x = trans.second[0];
		float y = x;
		if (trans.second.size() == 2)
			y = trans.second[1];
		if (trans.first == "translate")
			graphics.TranslateTransform(x, y);
		else if (trans.first == "rotate")
			graphics.RotateTransform(x);
		else graphics.ScaleTransform(x, y);
	}

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.DrawLine(&penLine, fig->getP1().getX(), fig->getP1().getY(), fig->getP2().getX(), fig->getP2().getY());
	graphics.Restore(save);
}

void renderer::drawPolygon(Graphics& graphics, polygon* fig) {
	GraphicsState save = graphics.Save();
	Pen penPolygon(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	SolidBrush fillPolygon(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	vector<pair<string, vector<float>>> transVct = fig->getTransVct();

	for (auto trans : transVct) {
		float x = 0.0f;
		if (!trans.second.empty())
			x = trans.second[0];
		float y = x;
		if (trans.second.size() == 2)
			y = trans.second[1];
		if (trans.first == "translate")
			graphics.TranslateTransform(x, y);
		else if (trans.first == "rotate")
			graphics.RotateTransform(x);
		else graphics.ScaleTransform(x, y);
	}

	int numPoint = fig->getVers().size();
	PointF* p = new PointF[numPoint];
	for (int i = 0; i < numPoint; i++)
		p[i] = PointF(fig->getVers()[i].getX(), fig->getVers()[i].getY());
	
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.FillPolygon(&fillPolygon, p, numPoint, FillModeWinding);
	graphics.DrawPolygon(&penPolygon, p, numPoint);
	graphics.Restore(save);
	delete[] p;
}

void renderer::drawPolyline(Graphics& graphics, polyline* fig) {
	GraphicsState save = graphics.Save();
	Pen penPolyline(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	SolidBrush fillPolyline(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	vector<pair<string, vector<float>>> transVct = fig->getTransVct();

	for (auto trans : transVct) {
		float x = 0.0f;
		if (!trans.second.empty())
			x = trans.second[0];
		float y = x;
		if (trans.second.size() == 2)
			y = trans.second[1];
		if (trans.first == "translate")
			graphics.TranslateTransform(x, y);
		else if (trans.first == "rotate")
			graphics.RotateTransform(x);
		else graphics.ScaleTransform(x, y);
	}

	int numPoint = fig->getVers().size();
	PointF* p = new PointF[numPoint];
	for (int i = 0; i < numPoint; i++)
		p[i] = PointF(fig->getVers()[i].getX(), fig->getVers()[i].getY());
	
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.FillPolygon(&fillPolyline, p, numPoint, FillModeWinding);
	graphics.DrawLines(&penPolyline, p, numPoint);
	graphics.Restore(save);
	delete[] p;
}

void renderer::drawText(Graphics& graphics, text* fig) {
	GraphicsState save = graphics.Save();
	wstring_convert<codecvt_utf8<wchar_t>> converter;
	wstring wContent = converter.from_bytes(fig->getContent());
	wstring wFontFamily = converter.from_bytes(fig->getFontFamily());
	FontFamily WFF = wFontFamily.c_str();

	PointF textPosition;
	StringFormat stringFormat;
	if (fig->getTextAnchor() == "middle") {
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
		textPosition = PointF(fig->getTextPos().getX() + fig->getDx() - fig->getFontSize() / 5.0f, fig->getTextPos().getY() + fig->getDy() - fig->getFontSize() / 1.1f);
		stringFormat.SetAlignment(StringAlignmentNear);
		stringFormat.SetLineAlignment(StringAlignmentNear);
	}
	
	GraphicsPath path;
	if (fig->getFontStyle() == "italic")
		path.AddString(wContent.c_str(), -1, &WFF, FontStyleItalic, fig->getFontSize(), textPosition, &stringFormat);
	else if (fig->getFontStyle() == "bold")
		path.AddString(wContent.c_str(), -1, &WFF, FontStyleBold, fig->getFontSize(), textPosition, &stringFormat);
	else path.AddString(wContent.c_str(), -1, &WFF, FontStyleRegular, fig->getFontSize(), textPosition, &stringFormat);

	Pen penText(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	SolidBrush fillText(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	vector<pair<string, vector<float>>> transVct = fig->getTransVct();

	for (auto trans : transVct) {
		float x = 0.0f;
		if (!trans.second.empty())
			x = trans.second[0];
		float y = x;
		if (trans.second.size() == 2)
			y = trans.second[1];
		if (trans.first == "translate")
			graphics.TranslateTransform(x, y);
		else if (trans.first == "rotate")
			graphics.RotateTransform(x);
		else graphics.ScaleTransform(x, y);
	}

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.FillPath(&fillText, &path);
	graphics.DrawPath(&penText, &path);
	graphics.Restore(save);
}

void renderer::drawPath(Graphics& graphics, path* fig) {
	GraphicsState save = graphics.Save();
	vector<pair<char, vector<point>>> vct = fig->getProp();
	GraphicsPath path;
	int numPoint = vct[0].second.size();
	if (numPoint != 0) {
		vector <Point> points(numPoint);
		for (int i = 0; i < numPoint; i++)
			points[i] = Point(vct[0].second[i].getX(), vct[0].second[i].getY());
		path.AddLines(points.data(), numPoint);
	}
	for (int i = 1; i < vct.size(); i++) {
		numPoint = vct[i].second.size();
		if (vct[i].first == 'C' || vct[i].first == 'c') {
				point Pt0 = vct[i - 1].second[vct[i - 1].second.size() - 1];
				Point P0 = Point(Pt0.getX(), Pt0.getY());
				point Pt1 = vct[i].second[0];
				Point P1 = Point(Pt1.getX(), Pt1.getY());
				point Pt2 = vct[i].second[1];
				Point P2 = Point(Pt2.getX(), Pt2.getY());
				point Pt3 = vct[i].second[2];
				Point P3 = Point(Pt3.getX(), Pt3.getY());
				path.AddBezier(P0, P1, P2, P3);	
		}
		else if (vct[i].first == 'Z' || vct[i].first == 'z') {
			point Pt0 = vct[i].second[0];
			Point P0 = Point(Pt0.getX(), Pt0.getY());
			point Pt1 = vct[0].second[0];
			Point P1 = Point(Pt1.getX(), Pt1.getY());
			path.AddLine(P0, P1);
			
			/*if (i == vct.size() - 1)
				open = false;
			else {
				SolidBrush fillPath(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
				Pen penPath(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
				graphics.FillPath(&fillPath, &path);
				graphics.DrawPath(&penPath, &path);
				graphics.SetSmoothingMode(SmoothingModeAntiAlias);
			}*/
		}
		else {
			vector <Point> points(numPoint);
			for (int j = 0; j < numPoint; j++)
				points[j] = Point(vct[i].second[j].getX(), vct[i].second[j].getY());
			path.AddLines(points.data(), numPoint);
		}
	}

	Pen penPath(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth());
	SolidBrush fillPath(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	vector<pair<string, vector<float>>> transVct = fig->getTransVct();

	for (auto trans : transVct) {
		float x = 0.0f;
		if (!trans.second.empty())
			x = trans.second[0];
		float y = x;
		if (trans.second.size() == 2)
			y = trans.second[1];
		if (trans.first == "translate")
			graphics.TranslateTransform(x, y);
		else if (trans.first == "rotate")
			graphics.RotateTransform(x);
		else graphics.ScaleTransform(x, y);
	}

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.FillPath(&fillPath, &path);
	graphics.DrawPath(&penPath, &path);
	graphics.Restore(save);
}

void renderer::drawGroup(Graphics& graphics, group* fig) {
	if (!fig->getFigureArray().empty())
		drawFigure(graphics, fig->getFigureArray());
	//...
}