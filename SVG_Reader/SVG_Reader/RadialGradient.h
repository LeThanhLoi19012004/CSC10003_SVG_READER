#ifndef _RADIALGRADIENT_H_
#define _RADIALGRADIENT_H_

class radialgradient : public gradient {
private:
	float cx, cy, r, fx, fy;
	bool isLink;

public:
	float getCx();
	float getCy();
	float getR();
	float getFx();
	float getFy();

	void updateElement();

	radialgradient();
	radialgradient(const radialgradient&);
	radialgradient& operator = (const radialgradient&);

	bool getIsLink();
	void setIsLink(bool);
};

#endif
