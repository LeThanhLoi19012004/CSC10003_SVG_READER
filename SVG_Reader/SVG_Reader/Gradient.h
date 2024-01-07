#ifndef _GRADIENT_H_
#define _GRADIENT_H_
class stop {
private:
	
public:
	color stopColor;
	float offset = 0;
	stop();
	stop(color, float);
};

class gradient {
protected:
	string strLine;
	int gradId;
	vector<stop> stopVct;
	vector<pair<string, vector<float>>> gradientTrans;
public:
	vector<stop> getStopVct();
	int getGradId();
	void setStopVct(vector<stop>);
	void addStop(stop);
	void setGradId(int);
	vector<pair<string, vector<float>>> getGradientTrans();
	void updateGradientTransform(string);
	virtual void updateElement();

	gradient();
	gradient(const gradient&);
	gradient& operator = (const gradient&);

	string getStrLine();
	void setStrLine(string);
	~gradient();
};

#endif