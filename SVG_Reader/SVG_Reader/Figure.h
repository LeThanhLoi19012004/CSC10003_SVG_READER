#ifndef _FIGURE_H_
#define _FIGURE_H_

class figure {
protected:
    string fig, text_name, line_str;
    stroke strk;
    color fill;
    vector<pair<string, vector<float>>> transVct; // Transformation

public:
    figure();
    virtual ~figure();

    string getName();
    string getTextName();
    stroke getStroke();
    color getColor();
    vector<pair<string, vector<float>>> getTransVct();

    void setName(string);
    void setTextName(string);
    void setLine(string);
    void setStroke(stroke);
    void setColor(color);

    virtual void updateProperty();
    void updateTransformVct(string);
    virtual void transformFigure();
};

#endif