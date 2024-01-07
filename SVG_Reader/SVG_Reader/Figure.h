#ifndef _FIGURE_H_
#define _FIGURE_H_

class figure {
protected:
    string fig, text_name, line_str;
    vector<pair<string, vector<float>>> transVct;

    stroke strk;
    color fill;
    gradient* grad;

public:
    figure();
    virtual ~figure();
    virtual void updateProperty();

    string getName();
    string getTextName();
    stroke getStroke();
    color getColor();
    vector<pair<string, vector<float>>> getTransVct();
    gradient* getGrad();

    void setGrad(gradient*);
    void setName(string);
    void setTextName(string);
    void setLine(string);
    void setStroke(stroke);
    void setColor(color);

    void updateTransformVct(string);
    void convertGradient(gradient*);
};

#endif