//#include "Lib.h"
//void Renderer::drawFigure(vector<Figure*> figures, sf::RenderWindow& window) {
//	FactoryFigure factory;
//	for (Figure* fig : figures) {
//		int num = factory.getFigureId()[fig->getName()];
//
//		switch (num)
//		{
//		case 1:
//		{
//			Rectangle* rect = dynamic_cast<Rectangle*>(fig);
//			drawRectangle(window, rect);
//			break;
//		}
//		case 2: case 3: {
//			Ellipse* ellipse = dynamic_cast<Ellipse*>(fig);
//			drawEllipse(window, ellipse);
//			break;
//		}
//		case 4:
//		{
//			Line* line = dynamic_cast<Line*>(fig);
//			drawLine(window, line);
//			break;
//		}
//		case 5: {
//			Polyline* polyline = dynamic_cast<Polyline*>(fig);
//			drawPolyline(window, polyline);
//			break;
//		}
//		case 6: {
//			Polygon* polygon = dynamic_cast<Polygon*>(fig);
//			drawPolygon(window, polygon);
//			break;
//		}
//		case 7: {
//			Text* text = dynamic_cast<Text*> (fig);
//			drawText(window, text);
//			break;
//		}
//		case 9: {
//			Path* path = dynamic_cast<Path*>(fig);
//			drawPath(window, path);
//			break;
//		}
//		default:
//			break;
//		}
//	}
//
//}
//
//void Renderer::canvasControl(sf::RenderWindow& window, sf::View& view, const float zoomAmount, const float panSpeed) {
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
//		view.zoom(1.f / zoomAmount);
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
//		view.zoom(1.02f);
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//		view.move(-panSpeed, 0);
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//		view.move(panSpeed, 0);
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//		view.move(0, -panSpeed);
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//		view.move(0, panSpeed);
//}
//
//void Renderer::renderItem(vector<Figure*> figures, float antialiasingLevel, string imageName, float width, float height) {
//	sf::ContextSettings settings;
//	settings.antialiasingLevel = antialiasingLevel;
//	width = sf::VideoMode::getDesktopMode().width;
//	height = sf::VideoMode::getDesktopMode().height;
//
//	sf::Vector2i screen(width, height);
//	sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), imageName, sf::Style::Default, settings);
//	sf::View view(sf::FloatRect(-1.f, -1.f, width, height));
//
//	window.setFramerateLimit(60);
//	const float zoomAmount{ 1.02f };
//	const float panSpeed = 10.0f;
//
//	while (window.isOpen()) {
//		sf::Event event;
//		while (window.pollEvent(event)) {
//			switch (event.type) {
//			case sf::Event::Closed: {
//				window.close();
//				break;
//			}
//			}
//		}
//		canvasControl(window, view, zoomAmount, panSpeed);
//		window.setView(view);
//
//		/*for (auto x : figures)
//			x->Draw(window);*/
//		drawFigure(figures, window);
//
//		//drawGroup(groupArr,window);
//		window.display();
//		window.clear(sf::Color::White);
//	}
//}
//
//void Renderer::drawRectangle(sf::RenderWindow& window, Rectangle* fig) {
//	/*sf::RectangleShape rect;
//
//	rect.setSize(sf::Vector2f(fig->getWidth(), fig->getHeight()));
//	rect.setPosition(fig->getRoot().getX(), fig->getRoot().getY());*/
//	sf::ConvexShape rect;
//	rect.setPointCount(4);
//
//	float x = 0, y = 0;
//	if (!fig->getisRotate()) {
//		x = fig->getRoot().getX();
//		y = fig->getRoot().getY();
//		rect.setPoint(0, sf::Vector2f(x, y));
//		rect.setPoint(1, sf::Vector2f(x + fig->getWidth(), y));
//		rect.setPoint(2, sf::Vector2f(x + fig->getWidth(), y + fig->getHeight()));
//		rect.setPoint(3, sf::Vector2f(x, y + fig->getHeight()));
//	}
//	else {
//		x = fig->getRoot().getX();
//		y = fig->getRoot().getY();
//		int pos = -1;
//		for (int i = 0; i < fig->getTransVct().size(); i++) {
//			if (fig->getTransVct()[i].first == "rotate") {
//				pos = i;
//				break;
//			}
//		}
//		float A = cos(fig->getTransVct()[pos].second[0] * Pi / 180.f);
//		float B = sin(fig->getTransVct()[pos].second[0] * Pi / 180.f);
//
//		rect.setPoint(0, sf::Vector2f(x * A - y * B, x * B + y * A));
//		rect.setPoint(1, sf::Vector2f((x + fig->getWidth()) * A - y * B, (x + fig->getWidth()) * B + y * A));
//		rect.setPoint(2, sf::Vector2f((x + fig->getWidth()) * A - (y + fig->getHeight()) * B, (x + fig->getWidth()) * B + (y + fig->getHeight()) * A));
//		rect.setPoint(3, sf::Vector2f(x * A - (y + fig->getHeight()) * B, (y + fig->getHeight()) * A + x * B));
//
//	}
//	if (fig->getColor().r != -1) {
//		if (fig->getColor().opacity >= 0)
//			rect.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b, fig->getColor().opacity * MAX));
//		else rect.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b));
//	}
//	else rect.setFillColor(sf::Color::Transparent);
//
//	sf::ConvexShape strokeRect = rect;
//	float tmp = fig->getStroke().getStrokeWidth() / 2.f;
//
//	if (fig->getStroke().getStrokeColor().r != -1) {
//		if (fig->getStroke().getStrokeColor().opacity >= 0) {
//			rect.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b, fig->getStroke().getStrokeColor().opacity * MAX));
//			rect.setOutlineThickness(-tmp);
//
//			strokeRect.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b, fig->getStroke().getStrokeColor().opacity * MAX));
//			strokeRect.setOutlineThickness(tmp);
//		}
//		else {
//			rect.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b));
//			rect.setOutlineThickness(-tmp);
//
//			strokeRect.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b));
//			strokeRect.setOutlineThickness(tmp);
//		}
//	}
//	else rect.setOutlineColor(sf::Color::Transparent);
//
//	window.draw(strokeRect);
//	window.draw(rect);
//}
//
//void Renderer::drawEllipse(sf::RenderWindow& window, Ellipse* fig) {
//	unsigned short pointNum = 72; //72 is the golden distribution of points to form ellipse
//
//	sf::ConvexShape ellipse;
//	ellipse.setPointCount(pointNum);
//
//	for (unsigned short i = 0; i < pointNum; i++) {
//		float radian = (360 / pointNum * i) / (180 / Pi);
//		float x = cos(radian) * fig->getRx();
//		float y = sin(radian) * fig->getRy();
//
//		if (fig->getisRotate()) {
//			int pos = -1;
//			for (int i = 0; i < fig->getTransVct().size(); i++) {
//				if (fig->getTransVct()[i].first == "rotate") {
//					pos = i;
//					break;
//				}
//			}
//			float A = cos(fig->getTransVct()[pos].second[0] * Pi / 180.f);
//			float B = sin(fig->getTransVct()[pos].second[0] * Pi / 180.f);
//			float newX = x * A - y * B;
//			float newY = x * B + y * A;
//			x = newX;
//			y = newY;
//		}
//
//		ellipse.setPoint(i, sf::Vector2f(x, y));
//	}
//
//	if (fig->getColor().r != -1) {
//		if (fig->getColor().opacity >= 0)
//			ellipse.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b, fig->getColor().opacity * MAX));
//		else ellipse.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b));
//	}
//	else ellipse.setFillColor(sf::Color::Transparent);
//
//	sf::ConvexShape strokeEllipse = ellipse;
//	float tmp = fig->getStroke().getStrokeWidth() / 2.f;
//
//	if (fig->getStroke().getStrokeColor().r != -1) {
//		if (fig->getStroke().getStrokeColor().opacity >= 0) {
//			ellipse.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b, fig->getStroke().getStrokeColor().opacity * MAX));
//			ellipse.setOutlineThickness(-tmp);
//
//			strokeEllipse.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b, fig->getStroke().getStrokeColor().opacity * MAX));
//			strokeEllipse.setOutlineThickness(tmp);
//		}
//		else {
//			ellipse.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b));
//			ellipse.setOutlineThickness(-tmp);
//
//			strokeEllipse.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b));
//			strokeEllipse.setOutlineThickness(tmp);
//		}
//	}
//	else ellipse.setOutlineColor(sf::Color::Transparent);
//
//
//	ellipse.setPosition(fig->getCenter().getX(), fig->getCenter().getY());
//	strokeEllipse.setPosition(fig->getCenter().getX(), fig->getCenter().getY());
//
//	window.draw(strokeEllipse);
//	window.draw(ellipse);
//}
//
//void Renderer::drawLine(sf::RenderWindow& window, Line* fig) {
//	sf::ConvexShape line;
//	line.setPointCount(4);
//
//	if (fig->getisRotate()) {
//		float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
//		x1 = fig->getP1().getX();
//		y1 = fig->getP1().getY();
//		x2 = fig->getP2().getX();
//		y2 = fig->getP2().getY();
//		int pos = -1;
//		for (int i = 0; i < fig->getTransVct().size(); i++) {
//			if (fig->getTransVct()[i].first == "rotate") {
//				pos = i;
//				break;
//			}
//		}
//		float A = cos(fig->getTransVct()[pos].second[0] * Pi / 180.f);
//		float B = sin(fig->getTransVct()[pos].second[0] * Pi / 180.f);
//
//		line.setPoint(0, sf::Vector2f(x1 * A - y1 * B, x1 * B + y1 * A));
//		line.setPoint(1, sf::Vector2f(x1 * A - y1 * B, x1 * B + y1 * A));
//		line.setPoint(2, sf::Vector2f(x2 * A - y2 * B, x2 * B + y2 * A));
//		line.setPoint(3, sf::Vector2f(x2 * A - y2 * B, x2 * B + y2 * A));
//	}
//	else {
//		line.setPoint(0, sf::Vector2f(fig->getP1().getX(), fig->getP1().getY()));
//		line.setPoint(1, sf::Vector2f(fig->getP1().getX(), fig->getP1().getY()));
//		line.setPoint(2, sf::Vector2f(fig->getP2().getX(), fig->getP2().getY()));
//		line.setPoint(3, sf::Vector2f(fig->getP2().getX(), fig->getP2().getY()));
//	}
//
//	sf::ConvexShape strokeLine = line;
//	float tmp = fig->getStroke().getStrokeWidth() / 4.f;
//
//	if (fig->getStroke().getStrokeColor().r != -1) {
//		if (fig->getStroke().getStrokeColor().opacity >= 0) {
//			line.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b, fig->getStroke().getStrokeColor().opacity * MAX));
//			line.setOutlineThickness(-tmp);
//
//			strokeLine.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b, fig->getStroke().getStrokeColor().opacity * MAX));
//			strokeLine.setOutlineThickness(tmp);
//		}
//		else {
//			line.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b));
//			line.setOutlineThickness(-tmp);
//
//			strokeLine.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b));
//			strokeLine.setOutlineThickness(tmp);
//		}
//	}
//	else line.setOutlineColor(sf::Color::Transparent);
//
//	window.draw(strokeLine);
//	window.draw(line);
//}
//
//void Renderer::drawPolyline(sf::RenderWindow& window, Polyline* fig) {
//	Point end = fig->getVers()[fig->getNVer() - 1];
//	Point start = fig->getVers()[0];
//
//	vector<Point> totalArray; //Contain point and itersect
//	vector<Point> intersectArray;
//	totalArray.push_back(fig->getVers()[0]); //Push back the first element of the vertices
//
//	for (int i = 1; i < fig->getNVer(); i++) {
//		Point P1 = fig->getVers()[i - 1];
//		Point P2 = fig->getVers()[i];
//		Point intersect;
//
//		float delta = (P1.getX() - P2.getX()) * (start.getY() - end.getY()) - (P1.getY() - P2.getY()) * (start.getX() - end.getX());
//		if (abs(delta) >= 0.1f) {
//			intersect.setX(
//				((P1.getX() * P2.getY() - P1.getY() * P2.getX()) * (start.getX() - end.getX()) - (P1.getX() - P2.getX()) * (start.getX() * end.getY() - start.getY() * end.getX())) * 1.f
//				/ delta);
//
//			intersect.setY(
//				((P1.getX() * P2.getY() - P1.getY() * P2.getX()) * (start.getY() - end.getY()) - (P1.getY() - P2.getY()) * (start.getX() * end.getY() - start.getY() * end.getX())) * 1.f
//				/ delta);
//			intersect.setIntersect(true);
//
//			if (intersectArray.empty()) {
//				totalArray.push_back(intersect);
//				intersectArray.push_back(intersect);
//			}
//			else {
//				bool flag = false;
//				for (auto point : intersectArray) {
//					if (point == intersect) {
//						flag = true;
//						break;
//					}
//				}
//				if (!flag) {
//					intersectArray.push_back(intersect);
//					totalArray.push_back(intersect);
//				}
//			}
//		}
//		totalArray.push_back(fig->getVers()[i]);
//	}
//	int pos = -1;
//
//	for (int i = 0; i < totalArray.size(); i++) {
//		if (totalArray[i].getIntersect()) {
//			pos = i;
//			break;
//		}
//	}
//
//	int cnt = 0;
//	for (int i = pos + 1; i < totalArray.size(); i++) {
//		if (totalArray[i].getIntersect()) {
//			cnt = cnt + 2;
//			//Process
//			sf::ConvexShape polyline;
//			polyline.setPointCount(cnt);
//
//			for (int k = 0; k < cnt; k++)
//				polyline.setPoint(k, sf::Vector2f(totalArray[k + pos].getX(), totalArray[k + pos].getY()));
//
//			if (fig->getColor().r != -1) {
//				if (fig->getColor().opacity >= 0)
//					polyline.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b, fig->getColor().opacity * MAX));
//				else polyline.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b));
//			}
//			else {
//				if (fig->getColor().opacity >= 0)
//					polyline.setFillColor(sf::Color(0, 0, 0, fig->getColor().opacity * MAX));
//				else polyline.setFillColor(sf::Color::Transparent);
//			}
//			window.draw(polyline);
//			pos = i;
//			cnt = 0;
//		}
//		else ++cnt;
//	}
//
//	//Making the outline of the shape
//	for (int i = 0; i < fig->getNVer() - 1; i++) {
//		sf::Vector2f startPoint(fig->getVers()[i].getX(), fig->getVers()[i].getY());
//		sf::Vector2f endPoint(fig->getVers()[i + 1].getX(), fig->getVers()[i + 1].getY());
//		sf::RectangleShape line;
//		line.setSize(sf::Vector2f(hypot(endPoint.x - startPoint.x, endPoint.y - startPoint.y), fig->getStroke().getStrokeWidth()));
//		line.setPosition(startPoint);
//		line.setOrigin(fig->getStroke().getStrokeWidth() / 2.f, fig->getStroke().getStrokeWidth() / 2.f);
//		line.setRotation(atan2(endPoint.y - startPoint.y, endPoint.x - startPoint.x) * 180.f / Pi);
//		if (fig->getStroke().getStrokeColor().r != -1) {
//			if (fig->getStroke().getStrokeColor().opacity >= 0)
//				line.setFillColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b, fig->getStroke().getStrokeColor().opacity * MAX));
//			else line.setFillColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b));
//		}
//		else line.setFillColor(sf::Color::Transparent);
//
//		window.draw(line);
//	}
//}
//
//void Renderer::drawPolygon(sf::RenderWindow& window, Polygon* fig) {
//	sf::ConvexShape polygon;
//	polygon.setPointCount(fig->getNVer());
//
//	for (int i = 0; i < fig->getNVer(); i++)
//		polygon.setPoint(i, sf::Vector2f(fig->getVers()[i].getX(), fig->getVers()[i].getY()));
//
//	if (fig->getColor().r != -1) {
//		if (fig->getColor().opacity >= 0)
//			polygon.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b, fig->getColor().opacity * MAX));
//		else polygon.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b));
//	}
//	else polygon.setFillColor(sf::Color::Transparent);
//
//	sf::ConvexShape strokePolygon = polygon;
//	float tmp = fig->getStroke().getStrokeWidth() / 2.f;
//
//	if (fig->getStroke().getStrokeColor().r != -1) {
//		if (fig->getStroke().getStrokeColor().opacity >= 0) {
//			polygon.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b, fig->getStroke().getStrokeColor().opacity * MAX));
//			polygon.setOutlineThickness(-tmp);
//
//			strokePolygon.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b, fig->getStroke().getStrokeColor().opacity * MAX));
//			strokePolygon.setOutlineThickness(tmp);
//		}
//		else {
//			polygon.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b));
//			polygon.setOutlineThickness(-tmp);
//
//			strokePolygon.setOutlineColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b));
//			strokePolygon.setOutlineThickness(tmp);
//		}
//	}
//	else polygon.setOutlineColor(sf::Color::Transparent);
//
//	window.draw(strokePolygon);
//	window.draw(polygon);
//}
//
//void Renderer::drawText(sf::RenderWindow& window, Text* fig) {
//	sf::Text text;
//	sf::Font font;
//
//	if (!font.loadFromFile("times new roman.ttf"))
//		return;
//
//	text.setFont(font);
//	text.setString(fig->getContent());
//	text.setCharacterSize(fig->getFontSize());
//	text.setPosition(fig->getTextPos().getX(), fig->getTextPos().getY() - fig->getFontSize() - 1.f);
//
//	if (fig->getisRotate()) {
//		int pos = -1;
//		for (int i = 0; i < fig->getTransVct().size(); i++) {
//			if (fig->getTransVct()[i].first == "rotate") {
//				pos = i;
//				break;
//			}
//		}
//		float R = fig->getTransVct()[pos].second[0];
//		text.rotate(R);
//	}
//
//	if (fig->getColor().r != -1)
//		text.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b));
//	else text.setFillColor(sf::Color::Transparent);
//
//	window.draw(text);
//}
//
//void Renderer::drawPath(sf::RenderWindow& window, Path* fig) {
//	vector<pair<char, vector<Point>>> vct = fig->getProp();
//	int numPoint = -1;
//	for (auto x : vct) {
//		if (x.first == 'C' || x.first == 'c')
//			numPoint += 201;
//		else numPoint += x.second.size();
//	}
//
//	sf::ConvexShape C;
//	C.setPointCount(numPoint);
//
//	int k = 0;
//	for (int i = 1; i < vct.size(); i++) {
//		Point P0 = vct[i - 1].second[vct[i - 1].second.size() - 1];
//		pair<char, vector<Point>> x = vct[i];
//		if (x.first == 'C' || x.first == 'c') {
//			Point P1 = x.second[0];
//			Point P2 = x.second[1];
//			Point P3 = x.second[2];
//
//			for (float t = 0.0; t <= 1.0; t += 0.005) {
//				float X = (1.0 - t) * (1.0 - t) * (1.0 - t) * P0.getX() + 3.0 * (1.0 - t) * (1.0 - t) * t * P1.getX() + 3.0 * (1.0 - t) * t * t * P2.getX() + t * t * t * P3.getX();
//				float Y = (1.0 - t) * (1.0 - t) * (1.0 - t) * P0.getY() + 3.0 * (1.0 - t) * (1.0 - t) * t * P1.getY() + 3.0 * (1.0 - t) * t * t * P2.getY() + t * t * t * P3.getY();
//				//cout << X << " " << Y << endl;
//				C.setPoint(k, sf::Vector2f(X, Y));
//				++k;
//			}
//		}
//		if (x.first == 'L' || x.first == 'l') {
//			Point P1 = x.second[0];
//			C.setPoint(k, sf::Vector2f(P1.getX(), P1.getY()));
//			++k;
//		}
//	}
//	if (fig->getColor().r != -1) {
//		if (fig->getColor().opacity >= 0)
//			C.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b, fig->getColor().opacity * MAX));
//		else C.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b));
//	}
//	else {
//		if (fig->getColor().opacity >= 0)
//			C.setFillColor(sf::Color(0, 0, 0, fig->getColor().opacity * MAX));
//		else C.setFillColor(sf::Color::Transparent);
//	}
//
//
//	window.draw(C);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	/*if (x.first == 'C' || x.first == 'c') {
//		Point P0 = vct[i - 1].second[vct[i - 1].second.size() - 1];
//		Point P1 = x.second[0];
//		Point P2 = x.second[1];
//		Point P3 = x.second[2];
//
//		sf::ConvexShape C;
//		C.setPointCount(201);
//
//		int k = 0;
//		for (float t = 0.0; t <= 1.0; t += 0.005) {
//			float X = (1.0 - t) * (1.0 - t) * (1.0 - t) * P0.getX() + 3.0 * (1.0 - t) * (1.0 - t) * t * P1.getX() + 3.0 * (1.0 - t) * t * t * P2.getX() + t * t * t * P3.getX();
//			float Y = (1.0 - t) * (1.0 - t) * (1.0 - t) * P0.getY() + 3.0 * (1.0 - t) * (1.0 - t) * t * P1.getY() + 3.0 * (1.0 - t) * t * t * P2.getY() + t * t * t * P3.getY();
//			C.setPoint(k, sf::Vector2f(X, Y));
//			++k;
//		}
//
//		if (fig->getColor().r != -1) {
//			if (fig->getColor().opacity >= 0)
//				C.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b, fig->getColor().opacity * MAX));
//			else C.setFillColor(sf::Color(fig->getColor().r, fig->getColor().g, fig->getColor().b));
//		}
//		else {
//			if (fig->getColor().opacity >= 0)
//				C.setFillColor(sf::Color(0, 0, 0, fig->getColor().opacity * MAX));
//			else C.setFillColor(sf::Color::Transparent);
//		}
//
//		window.draw(C);
//
//
//
//		for (int i = 1; i < 202; i++) {
//			float X = (1.0 - i * 0.005) * (1.0 - i * 0.005) * (1.0 - i * 0.005) * P0.getX() + 3.0 * (1.0 - i * 0.005) * (1.0 - i * 0.005) * (i * 0.005) * P1.getX() + 3.0 * (1.0 - i * 0.005) * (i * 0.005) * (i * 0.005) * P2.getX() + (i * 0.005) * (i * 0.005) * (i * 0.005) * P3.getX();
//			float Y = (1.0 - i * 0.005) * (1.0 - i * 0.005) * (1.0 - i * 0.005) * P0.getY() + 3.0 * (1.0 - i * 0.005) * (1.0 - i * 0.005) * (i * 0.005) * P1.getY() + 3.0 * (1.0 - i * 0.005) * (i * 0.005) * (i * 0.005) * P2.getY() + (i * 0.005) * (i * 0.005) * (i * 0.005) * P3.getY();
//			int j = i + 1;
//			float Z = (1.0 - j * 0.005) * (1.0 - j * 0.005) * (1.0 - j * 0.005) * P0.getX() + 3.0 * (1.0 - j * 0.005) * (1.0 - j * 0.005) * (j * 0.005) * P1.getX() + 3.0 * (1.0 - j * 0.005) * (j * 0.005) * (j * 0.005) * P2.getX() + (j * 0.005) * (j * 0.005) * (j * 0.005) * P3.getX();
//			float T = (1.0 - j * 0.005) * (1.0 - j * 0.005) * (1.0 - j * 0.005) * P0.getY() + 3.0 * (1.0 - j * 0.005) * (1.0 - j * 0.005) * (j * 0.005) * P1.getY() + 3.0 * (1.0 - j * 0.005) * (j * 0.005) * (j * 0.005) * P2.getY() + (j * 0.005) * (j * 0.005) * (j * 0.005) * P3.getY();
//			sf::Vector2f startPoint(X, Y);
//			sf::Vector2f endPoint(Z, T);
//			sf::RectangleShape StrokeC;
//			StrokeC.setSize(sf::Vector2f(hypot(endPoint.x - startPoint.x, endPoint.y - startPoint.y), fig->getStroke().getStrokeWidth()));
//			StrokeC.setPosition(startPoint);
//			StrokeC.setOrigin(fig->getStroke().getStrokeWidth() / 2.f, fig->getStroke().getStrokeWidth() / 2.f);
//			StrokeC.setRotation(atan2(endPoint.y - startPoint.y, endPoint.x - startPoint.x) * 180.f / Pi);
//			if (fig->getStroke().getStrokeColor().r != -1) {
//				if (fig->getStroke().getStrokeColor().opacity >= 0)
//					StrokeC.setFillColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b, fig->getStroke().getStrokeColor().opacity * MAX));
//				else StrokeC.setFillColor(sf::Color(fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b));
//			}
//			else StrokeC.setFillColor(sf::Color::Transparent);
//
//			window.draw(StrokeC);
//		}
//	}*/
//
//}