#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

class Rectangle :public Figure {
private:
	Point root;
	float width, height;
public:
	Rectangle();
	~Rectangle();

	// Update Rectangle Element
	void updateDiffElement();

	// Setter and Getter
	Point getRoot();
	float getWidth();
	float getHeight();

	void setRoot(Point);
	void setWidth(float);
	void setHeight(float);

	// Draw function
	void Draw(sf::RenderWindow&);
};

#endif