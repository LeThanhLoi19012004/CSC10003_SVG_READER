#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

class rectangle : public figure {
private:
	point root;
	float width, height;

public:
	rectangle();
	~rectangle();

	point getRoot();
	float getWidth();
	float getHeight();

	void setRoot(point);
	void setWidth(float);
	void setHeight(float);

	void updateProperty();
};

#endif
