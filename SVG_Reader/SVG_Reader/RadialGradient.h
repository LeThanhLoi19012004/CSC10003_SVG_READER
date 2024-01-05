#ifndef _RADIALGRADIENT_H_
#define _RADIALGRADIENT_H_

class radialgradient:public gradient {
private:
	float cx, cy, r, fx, fy;
public:
	float getCx();
	float getCy();
	float getR();
	float getFx();
	float getFy();

	radialgradient();
	radialgradient(const radialgradient&);
	radialgradient& operator = (const radialgradient&);
};

#endif
