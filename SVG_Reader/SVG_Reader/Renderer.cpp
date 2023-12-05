#include "Lib.h"

void renderer::drawFigure(vector<figure*> figures, HDC hdc) {
	factoryfigure factory;
	for (figure* fig : figures) {
		int num = factory.getFigureId()[fig->getName()];

		switch (num)
		{
		case 1:
		{
			rectangle* rect = dynamic_cast<rectangle*>(fig);
			drawRectangle(rect, hdc);
			break;
		}
		/*case 2: case 3: {
			ellipse* ellipses = dynamic_cast<ellipse*>(fig);
			drawEllipse(hdc, ellipses);
			break;
		}
		case 4:
		{
			line* lines = dynamic_cast<line*>(fig);
			drawLine(hdc, lines);
			break;
		}
		case 5: {
			polyline* polylines = dynamic_cast<polyline*>(fig);
			drawPolyline(hdc, polylines);
			break;
		}
		case 6: {
			polygon* polygons = dynamic_cast<polygon*>(fig);
			drawPolygon(hdc, polygons);
			break;
		}
		case 7: {
			text* texts = dynamic_cast<text*> (fig);
			drawText(hdc, texts);
			break;
		}
		case 8: {
			path* paths = dynamic_cast<path*>(fig);
			drawPath(hdc, paths);
			break;
		}*/
		default:
			break;
		}
	}
}

void renderer::renderItem(vector<figure*> figures, group_array groupArr , float antialiasingLevel, string imageName, float width, float height, HDC hdc) {
	/*sf::ContextSettings settings;
	settings.antialiasingLevel = antialiasingLevel;
	width = sf::VideoMode::getDesktopMode().width;
	height = sf::VideoMode::getDesktopMode().height;

	sf::Vector2i screen(width, height);
	sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), imageName, sf::Style::Default, settings);
	sf::View view(sf::FloatRect(-1.f, -1.f, width, height));

	window.setFramerateLimit(60);
	const float zoomAmount{ 1.02f };
	const float panSpeed = 10.0f;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
				break;
			}
			}
		}
		canvasControl(window, view, zoomAmount, panSpeed);
		window.setView(view);*/

		/*for (auto x : figures)
			x->Draw(window);*/
	
	drawFigure(figures, hdc); 

		//drawGroup(groupArr,window);
		//window.display();
		//window.clear(sf::Color::White);
	//}
}

void renderer::drawRectangle(rectangle* fig, HDC hdc) {
	Graphics graphics(hdc);
	Pen      penRectangle(Color(fig->getStroke().getStrokeColor().opacity * 255, fig->getStroke().getStrokeColor().r, fig->getStroke().getStrokeColor().g, fig->getStroke().getStrokeColor().b), fig->getStroke().getStrokeWidth()); //black color
	SolidBrush fillRectangle(Color(fig->getColor().opacity * 255, fig->getColor().r, fig->getColor().g, fig->getColor().b));
	graphics.FillRectangle(&fillRectangle, fig->getRoot().getX(), fig->getRoot().getY(), fig->getWidth(), fig->getHeight());
	graphics.DrawRectangle(&penRectangle, fig->getRoot().getX(), fig->getRoot().getY(), fig->getWidth(), fig->getHeight());
}