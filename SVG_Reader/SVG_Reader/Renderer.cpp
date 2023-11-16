#include "Lib.h"

void Renderer::canvasControl(sf::RenderWindow& window, sf::View& view, const float zoomAmount, const float panSpeed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		view.zoom(1.f / zoomAmount);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		view.zoom(1.02f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		view.move(panSpeed, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		view.move(-panSpeed, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		view.move(0, panSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		view.move(0, -panSpeed);
}

void Renderer::renderItem(vector<Figure*> figures, float antialiasingLevel, string imageName, float width, float height) {
	sf::ContextSettings settings;
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
		window.setView(view);

		for (auto x : figures)
			x->Draw(window);

		window.display();
		window.clear(sf::Color::White);
	}
}