#ifndef _RENDERER_H_
#define _RENDERER_H_

class Renderer {
public:
	void canvasControl(sf::RenderWindow&, sf::View&, const float, const float);
	void renderItem(vector<Figure*>, float, string, float, float);
};

#endif