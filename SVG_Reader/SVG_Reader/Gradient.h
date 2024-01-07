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
	string getStrLine();
	vector<pair<string, vector<float>>> getGradientTrans();

	void setStopVct(vector<stop>);
	void setStrLine(string);
	void setGradId(int);

	void addStop(stop);
	void updateGradientTransform(string);
	virtual void updateElement();

	gradient();
	gradient(const gradient&);
	gradient& operator =(const gradient&);
	~gradient();
};

#endif