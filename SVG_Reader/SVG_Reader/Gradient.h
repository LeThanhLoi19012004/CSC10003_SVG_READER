#ifndef _GRADIENT_H_
#define _GRADIENT_H_
class stop {
	
public:
	color stopColor; //Stop color contains color and opacity
	float offset;	//Offset of the stop
};
class gradient {
private:
	int gradId;
	vector<stop> stopVct;
	//transform trans
public:
	vector<stop> getStopVct();
	int getGradId();
	void setStopVct(vector<stop>);
	void addStop(stop);
	void setGradId(int);


	gradient();
	gradient(const gradient&);

	gradient& operator = (const gradient&);
};
#endif
