#include "Lib.h"
using namespace std;

void renderer::drawFigure(Graphics& graphics, group* root) {
	factoryfigure factory;
	for (figure* fig : root->getFigureArray()) {
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
			if (groups->getFigureArray().empty())
        return;
			drawFigure(graphics, groups);
			break;
		}
		default:
			break;
		}
	}
}

void renderer::renderItem(group* root, float antialiasingLevel, string imageName, float width, float height, HDC hdc) {
	Graphics graphics(hdc);
	drawFigure(graphics, root);
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
		textPosition = PointF(fig->getTextPos().getX() + fig->getDx() - fig->getFontSize() / 25, fig->getTextPos().getY() + fig->getDy() - fig->getFontSize() / 4);
		stringFormat.SetAlignment(StringAlignmentCenter);
		stringFormat.SetLineAlignment(StringAlignmentCenter);
	}
	else if (fig->getTextAnchor() == "end") {
		textPosition = PointF(fig->getTextPos().getX() + fig->getDx() + fig->getFontSize() / 6.5, fig->getTextPos().getY() + fig->getDy() + fig->getFontSize() / 2.8);
		stringFormat.SetAlignment(StringAlignmentFar);
		stringFormat.SetLineAlignment(StringAlignmentFar);
	}
	else {
		textPosition = PointF(fig->getTextPos().getX() + fig->getDx() - fig->getFontSize() / 7, fig->getTextPos().getY() + fig->getDy() - fig->getFontSize() / 1.2);
		stringFormat.SetAlignment(StringAlignmentNear);
		stringFormat.SetLineAlignment(StringAlignmentNear);
	}
	
	GraphicsPath path;
	if (fig->getFontStyle() == "italic")
		path.AddString(wContent.c_str(), -1, &WFF, FontStyleItalic, fig->getFontSize()/1.05, textPosition, &stringFormat);
	else if (fig->getFontStyle() == "bold")
		path.AddString(wContent.c_str(), -1, &WFF, FontStyleBold, fig->getFontSize()/1.05, textPosition, &stringFormat);
	else path.AddString(wContent.c_str(), -1, &WFF, FontStyleRegular, fig->getFontSize()/1.05, textPosition, &stringFormat);

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
	vector<pair<char, vector<float>>> vct = fig->getProp();
	FillMode fillMode;
	if (fig->getFillRule() == "evenodd")
		fillMode = FillModeAlternate;
	else fillMode = FillModeWinding;
	GraphicsPath path(fillMode);

	PointF P0;
	for (int i = 0; i < vct.size(); i++) {
		int numPoint = vct[i].second.size();
		if (vct[i].first == 'M' || vct[i].first == 'm') {
			path.StartFigure();
			if (numPoint == 4) {
				PointF P0 = PointF(vct[i].second[0], vct[i].second[1]);
				PointF P1 = PointF(vct[i].second[2], vct[i].second[3]);
				path.AddLine(P0, P1);
				P0 = P1;
			}
			else if (numPoint > 4) {
				int k = 0;
				vector <PointF> points(numPoint / 2);
				for (int j = 0; j < numPoint; j += 2)
					points[k++] = PointF(vct[i].second[j], vct[i].second[j + 1]);
				path.AddLines(points.data(), numPoint / 2);
				P0 = points[numPoint / 2 - 1];
			}
			else P0 = PointF(vct[i].second[0], vct[i].second[1]);
		}

		else if (vct[i].first == 'Q' || vct[i].first == 'q' || vct[i].first == 'T' || vct[i].first == 't') {
			int j = 0;
			while (numPoint > 3) {
				PointF P1 = PointF(vct[i].second[j + 0], vct[i].second[j + 1]);
				PointF P2 = PointF(vct[i].second[j + 2], vct[i].second[j + 3]);
				path.AddBezier(P0, P1, P2, P2);
				P0 = P2;
				numPoint -= 4;
				j += 4;
			}
		}

		else if (vct[i].first == 'C' || vct[i].first == 'c') {
			int j = 0;
			while (numPoint > 5) {
				PointF P1 = PointF(vct[i].second[j + 0], vct[i].second[j + 1]);
				PointF P2 = PointF(vct[i].second[j + 2], vct[i].second[j + 3]);
				PointF P3 = PointF(vct[i].second[j + 4], vct[i].second[j + 5]);
				path.AddBezier(P0, P1, P2, P3);
				P0 = P3;
				numPoint -= 6;
				j += 6;
			}
		}

		else if (vct[i].first == 'S' || vct[i].first == 's') {
			int j = 0;
			while (numPoint > 3) {
				PointF P1 = P0;
				if (i > 0) {
					if (vct[i - 1].first == 'C' || vct[i - 1].first == 'c' || vct[i - 1].first == 'S' || vct[i - 1].first == 's') {
						int n = vct[i - 1].second.size();
						if (n > 3) {
							float oldx2 = vct[i - 1].second[n - 4];
							float oldy2 = vct[i - 1].second[n - 3];
							float curx = vct[i - 1].second[n - 2];
							float cury = vct[i - 1].second[n - 1];
							P1 = PointF(2.f * curx - oldx2, 2.f * cury - oldy2);
						}
					}
				}
				PointF P2 = PointF(vct[i].second[j + 0], vct[i].second[j + 1]);
				PointF P3 = PointF(vct[i].second[j + 2], vct[i].second[j + 3]);
				path.AddBezier(P0, P1, P2, P3);
				P0 = P3;
				numPoint -= 4;
				j += 4;
			}
		}

		else if (vct[i].first == 'A' || vct[i].first == 'a') {
			int j = 0;
			while (numPoint > 6) {
				if (i > 0) {
					int n = vct[i - 1].second.size();
					if (n > 1) {
						float sx = vct[i - 1].second[n - 2];
						float sy = vct[i - 1].second[n - 1];
						float rx = vct[i].second[j + 0];
						float ry = vct[i].second[j + 1];
						float xAR = vct[i].second[j + 2];
						bool lAF = vct[i].second[j + 3];
						bool sF = vct[i].second[j + 4];
						float ex = vct[i].second[j + 5];
						float ey = vct[i].second[j + 6];

						float angle = xAR * 3.1415 / 180.f;
						float cosAngle = cos(angle);
						float sinAngle = sin(angle);

						float a = (sx - ex) / 2.f;
						float b = (sy - ey) / 2.f;

						float x1 = cosAngle * a + sinAngle * b;
						float y1 = -sinAngle * a + cosAngle * b;

						float checkR = (x1 * x1) / (rx * rx) + (y1 * y1) / (ry * ry);
						if (checkR > 1.f) {
							rx = sqrt(checkR) * rx;
							ry = sqrt(checkR) * ry;
						}

						float sign = (lAF == sF ? -1.f : 1.f);
						float num = abs(rx * rx * ry * ry - rx * rx * y1 * y1 - ry * ry * x1 * x1);
						float den = rx * rx * y1 * y1 + ry * ry * x1 * x1;

						float x2 = sign * sqrt(num / den) * rx * y1 / ry;
						float y2 = -sign * sqrt(num / den) * ry * x1 / rx;

						float x = cosAngle * x2 - sinAngle * y2 + ((sx + ex) / 2.f);
						float y = sinAngle * x2 + cosAngle * y2 + ((sy + ey) / 2.f);

						a = (x1 - x2) / rx;
						b = (y1 - y2) / ry;
						float c = (- x1 - x2) / rx;
						float d = (- y1 - y2) / ry;

						/*if (a < 0)
							sign = -1.f;
						else sign = 1.f;
						float startAngle = acos(a / sqrt(a * a + b * b));

						if (a * c + b * d < 0)
							sign = -1.f;
						else sign = 1.f;
						float dentaAngle = acos((a * c + b * d) / (sqrt(a * a + b * b) * sqrt(c * c + d * d)));*/

						float startAngle = atan2(b, a);
						float endAngle = atan2(d, c);
						float dentaAngle = endAngle - startAngle;

						if (sF && dentaAngle < 0)
							dentaAngle += 2.f * 3.1415;
						else if (!sF && dentaAngle > 0)
							dentaAngle -= 2.f * 3.1415;

						//dentaAngle = fmod(dentaAngle * 180.f / 3.1415, 360);

						/*if (!sF)
							dentaAngle - 360;
						else dentaAngle + 360;*/

						path.AddArc(x - rx, y - ry, 2.f * rx, 2.f * ry, fmod(startAngle * 180.f / 3.1415, 360), fmod(dentaAngle * 180.f / 3.1415, 360));
						P0 = PointF(ex, ey);
						numPoint -= 6;
						j += 6;
					}
				}
			}
		}
	
		else if (vct[i].first == 'L' || vct[i].first == 'H' || vct[i].first == 'V' || vct[i].first == 'l' || vct[i].first == 'h' || vct[i].first == 'v') {
			int j = 0;
			while (numPoint > 1) {
				PointF P1 = PointF(vct[i].second[j + 0], vct[i].second[j + 1]);
				path.AddLine(P0, P1);
				P0 = P1;
				numPoint -= 2;
				j += 2;
			}
		}

		else if (vct[i].first == 'Z' || vct[i].first == 'z')
			path.CloseFigure();
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