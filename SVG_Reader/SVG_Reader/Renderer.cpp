#include "Lib.h"
#define Pi 3.14159265358979323846
#define Kappa 0.551915024494
#define Pakka 1.5707963267948966
using namespace std;

void renderer::renderFigure(Graphics& graphics, group* root) {
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
			renderFigure(graphics, groups);
			break;
		}
		default:
			break;
		}
	}
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
	ofstream ofs("test.txt", ios::out);
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
			gradient* grad = fig->getGrad();
			if (grad == NULL) {
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
			else {
				path.StartFigure();
				int j = 0;
				while (numPoint > 1) {
					PointF P1 = PointF(vct[i].second[j + 0], vct[i].second[j + 1]);
					path.AddLine(P0, P1);
					P0 = P1;
					numPoint -= 2;
					j += 2;
				}
			}
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
						double sx = P0.X;
						double sy = P0.Y;
						double rx = vct[i].second[j + 0];
						double ry = vct[i].second[j + 1];
						double xAR = vct[i].second[j + 2];
						bool lAF = vct[i].second[j + 3];
						bool sF = vct[i].second[j + 4];
						double ex = vct[i].second[j + 5];
						double ey = vct[i].second[j + 6];
						double angle = xAR * Pi / 180.f;
						double cosAngle = cos(angle);
						double sinAngle = sin(angle);

						double a = (sx - ex) / 2.f;
						double b = (sy - ey) / 2.f;

						double x1 = cosAngle * a + sinAngle * b;
						double y1 = -sinAngle * a + cosAngle * b;

						rx = abs(rx);
						ry = abs(ry);

						double lambda = (x1 * x1) / (rx * rx) + (y1 * y1) / (ry * ry);
						if (lambda > 1.f) {
							rx *= sqrt(lambda);
							ry *= sqrt(lambda);
						}

						double sign = (lAF == sF ? -1.f : 1.f);
						double num = rx * rx * ry * ry - rx * rx * y1 * y1 - ry * ry * x1 * x1;
						double den = rx * rx * y1 * y1 + ry * ry * x1 * x1;
						if (num < 0)
							num = 0;

						double x2 = sign * sqrt(num / den) * rx * y1 / ry;
						double y2 = -sign * sqrt(num / den) * ry * x1 / rx;

						double x = cosAngle * x2 - sinAngle * y2 + ((sx + ex) / 2.f);
						double y = sinAngle * x2 + cosAngle * y2 + ((sy + ey) / 2.f);

						a = (x1 - x2) / rx;
						b = (y1 - y2) / ry;
						double c = (-x1 - x2) / rx;
						double d = (-y1 - y2) / ry;

						if (b < 0)
							sign = -1.f;
						else sign = 1.f;
						double temp = a / sqrt(a * a + b * b);
						if (temp < -1.f)
							temp = -1.f;
						else if (temp > 1.f)
							temp = 1.f;
						double startAngle = sign * acos(temp);

						if (a * d - b * c < 0)
							sign = -1.f;
						else sign = 1.f;
						temp = (a * c + b * d) / (sqrt(a * a + b * b) * sqrt(c * c + d * d));
						if (temp < -1.f)
							temp = -1.f;
						else if (temp > 1.f)
							temp = 1.f;
						double dentaAngle = sign * acos(temp);

						if (sF == 0 && dentaAngle > 0)
							dentaAngle -= (2.f * Pi);
						else if (sF == 1 && dentaAngle < 0)
							dentaAngle += (2.f * Pi);

						double ratio = abs(dentaAngle) / (Pi / 2.f);
						if (abs(1.f - ratio) < 0.0000001)
							ratio = 1.f;
						int segments = max(static_cast<int>(ceil(ratio)), 1);
						dentaAngle /= segments;

						vector<vector<vector<double>>> curves;
						vector<vector<double>> curve;
						for (int t = 0; t < segments; t++) {
							double kappa = (dentaAngle == Pakka) ? Kappa : (dentaAngle == -Pakka) ? -Kappa : 4.f / 3.f * tan(dentaAngle / 4.f);
							double x3 = cos(startAngle);
							double y3 = sin(startAngle);
							double x4 = cos(startAngle + dentaAngle);
							double y4 = sin(startAngle + dentaAngle);
							curve.push_back({ x3 - y3 * kappa, y3 + x3 * kappa });
							curve.push_back({ x4 + y4 * kappa, y4 - x4 * kappa });
							curve.push_back({ x4, y4 });
							curves.push_back(curve);
							curve.clear();
							startAngle += dentaAngle;
						}

						for (auto& cur : curves) {
							auto mapped_curve_0 = { (cosAngle * cur[0][0] * rx - sinAngle * cur[0][1] * ry) + x,(sinAngle * cur[0][0] * rx + cosAngle * cur[0][1] * ry) + y };
							auto mapped_curve_1 = { (cosAngle * cur[1][0] * rx - sinAngle * cur[1][1] * ry) + x,(sinAngle * cur[1][0] * rx + cosAngle * cur[1][1] * ry) + y };
							auto mapped_curve_2 = { (cosAngle * cur[2][0] * rx - sinAngle * cur[2][1] * ry) + x,(sinAngle * cur[2][0] * rx + cosAngle * cur[2][1] * ry) + y };
							cur = { mapped_curve_0, mapped_curve_1, mapped_curve_2 };

							for (size_t i = 0; i < cur.size(); i += 3) {
								if (i + 2 < cur.size()) {
									PointF P1(cur[i][0], cur[i][1]);
									PointF P2(cur[i + 1][0], cur[i + 1][1]);
									PointF P3(cur[i + 2][0], cur[i + 2][1]);
									path.AddBezier(P0, P1, P2, P3);
									P0 = P3;
								}
							}
						}

						P0 = PointF(ex, ey);
						numPoint -= 7;
						j += 7;
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

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	gradient* grad = fig->getGrad();

	if (grad == NULL) {
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
	else {
		int type = grad->getGradId();
		if (type == 1) {
			lineargradient* linear = dynamic_cast<lineargradient*>(grad);
			PointF p1 = PointF(linear->getA().getX(), linear->getA().getY());
			PointF p2 = PointF(linear->getB().getX(), linear->getB().getY());

			vector<stop> ColorOffset = linear->getStopVct();
			int size = ColorOffset.size();
			if (ColorOffset[0].offset != 0) {
				color first = ColorOffset[0].stopColor;
				float offset = ColorOffset[0].offset;
				color zero{ first.r * (1 - offset), first.g * (1 - offset), first.b * (1 - offset), first.opacity * (1 - offset) };
				ColorOffset.insert(ColorOffset.begin(), stop(zero, 0));
				size++;
			}

			if (ColorOffset[size - 1].offset != 1) {
				color last = ColorOffset[size - 1].stopColor;
				float offset = ColorOffset[size - 1].offset;
				color one{ last.r * (1 / offset), last.g * (1 / offset), last.b * (1 / offset), last.opacity * (1 / offset) };
				ColorOffset.push_back(stop(one, 1));
				size++;
			}

			float* points = new float[size];
			Color* colors = new Color[size];
			for (int k = 0; k < size; k++) {
				points[k] = ColorOffset[k].offset;
				colors[k] = Color(ColorOffset[k].stopColor.opacity * 255, ColorOffset[k].stopColor.r, ColorOffset[k].stopColor.g, ColorOffset[k].stopColor.b);
			}

			LinearGradientBrush fillPath(p1, p2, colors[0], colors[size - 1]);

			vector<pair<string, vector<float>>> gradientTrans = linear->getGradientTrans();
			for (int k = 0; k < gradientTrans.size(); k++) {
				if (gradientTrans[k].first == "translate") {
					fillPath.TranslateTransform(gradientTrans[k].second[0], gradientTrans[k].second[1]);
				}
				else if (gradientTrans[k].first == "rotate") {
					fillPath.RotateTransform(gradientTrans[k].second[0]);
				}
				else if (gradientTrans[k].first == "scale") {
					fillPath.ScaleTransform(gradientTrans[k].second[0], gradientTrans[k].second[1]);
				}
				else if (gradientTrans[k].first == "matrix") {
					Matrix matrix(
						gradientTrans[k].second[0], gradientTrans[k].second[1], gradientTrans[k].second[2],
						gradientTrans[k].second[3], gradientTrans[k].second[4], gradientTrans[k].second[5]
					);
					fillPath.SetTransform(&matrix);
				}
			}

			fillPath.SetWrapMode(WrapModeTileFlipXY);
			fillPath.SetInterpolationColors(colors, points, size);
			graphics.FillPath(&fillPath, &path);
			delete[] colors;
			delete[] points;
		}

		else if (type == 2) {
			radialgradient* radial = dynamic_cast<radialgradient*>(grad);
			float cx = radial->getCx();
			float cy = radial->getCy();
			float r = radial->getR();
			vector<stop> ColorOffset = radial->getStopVct();
			int size = ColorOffset.size();

			GraphicsPath pathE;
			pathE.AddEllipse(RectF(cx - r, cy - r, r * 2, r * 2));
			PathGradientBrush fillPath(&pathE);

			if (ColorOffset[0].offset != 0) {
				color first = ColorOffset[0].stopColor;
				float offset = ColorOffset[0].offset;
				color zero{ first.r * (1 - offset), first.g * (1 - offset), first.b * (1 - offset), first.opacity * (1 - offset) };
				ColorOffset.insert(ColorOffset.begin(), stop(zero, 0));
				size++;
			}

			if (ColorOffset[size - 1].offset != 1) {
				color last = ColorOffset[size - 1].stopColor;
				float offset = ColorOffset[size - 1].offset;
				color one{ last.r * (1 / offset), last.g * (1 / offset), last.b * (1 / offset), last.opacity * (1 / offset) };
				ColorOffset.push_back(stop(one, 1));
				size++;
			}

			float* points = new float[size];
			Color* colors = new Color[size];
			for (int k = 0; k < size; k++) {
				points[k] = 1 - ColorOffset[size - k - 1].offset;
				colors[k] = Color(ColorOffset[size - k - 1].stopColor.opacity * 255, ColorOffset[size - k - 1].stopColor.r, ColorOffset[size - k - 1].stopColor.g, ColorOffset[size - k - 1].stopColor.b);
			}

			vector<pair<string, vector<float>>> gradientTrans = radial->getGradientTrans();
			for (int k = 0; k < gradientTrans.size(); ++k) {
				if (gradientTrans[k].first == "translate") {
					fillPath.TranslateTransform(gradientTrans[k].second[0], gradientTrans[k].second[1]);
				}
				else if (gradientTrans[k].first == "rotate") {
					fillPath.RotateTransform(gradientTrans[k].second[0]);
				}
				else if (gradientTrans[k].first == "scale") {
					fillPath.ScaleTransform(gradientTrans[k].second[0], gradientTrans[k].second[1]);
				}
				else if (gradientTrans[k].first == "matrix") {
					Matrix matrix(
						gradientTrans[k].second[0], gradientTrans[k].second[1], gradientTrans[k].second[2],
						gradientTrans[k].second[3], gradientTrans[k].second[4], gradientTrans[k].second[5]
					);
					fillPath.SetTransform(&matrix);
					pathE.Transform(&matrix);
				}
			}

			Color it = Color(
				radial->getStopVct()[radial->getStopVct().size() - 1].stopColor.opacity * 255,
				radial->getStopVct()[radial->getStopVct().size() - 1].stopColor.r,
				radial->getStopVct()[radial->getStopVct().size() - 1].stopColor.g,
				radial->getStopVct()[radial->getStopVct().size() - 1].stopColor.b);

			SolidBrush solidBrush(it);
			Region region(&path);
			region.Exclude(&pathE);

			fillPath.SetInterpolationColors(colors, points, size);

			graphics.FillPath(&fillPath, &path);
			graphics.FillRegion(&solidBrush, &region);
			delete[] colors;
			delete[] points;
		}

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
			else if (trans.first == "scale")
				graphics.ScaleTransform(x, y);
			else if (trans.first == "matrix") {
				Matrix matrix(
					trans.second[0], trans.second[1], trans.second[2],
					trans.second[3], trans.second[4], trans.second[5]
				);
				graphics.SetTransform(&matrix);
			}
		}
		graphics.Restore(save);
	}
}