#ifndef _LINEARGRADIENT_H_
#define _LINEARGRADIENT_H_

class lineargradient : public gradient {
private:
	point A, B;

public:
	point getA();
	point getB();

	void setA(point);
	void setB(point);

	void updateElement();

	lineargradient();
	lineargradient(const lineargradient&);
	lineargradient& operator = (const lineargradient&);
};

#endif
