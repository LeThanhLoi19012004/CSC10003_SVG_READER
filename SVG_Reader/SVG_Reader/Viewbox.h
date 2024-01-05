#ifndef _VIEWBOX_H_
#define _VIEWBOX_H_

class viewbox {
private:
    float viewX, viewY, viewWidth, viewHeight;
    float portWidth, portHeight;
    string preservedForm, preservedMode;

public:
    float getViewX() const;
    float getViewY() const;
    float getViewWidth() const;
    float getViewHeight() const;
    float getPortWidth() const;
    float getPortHeight() const;
    const string& getPreservedForm() const;
    const string& getPreservedMode() const;

    void setViewX(float);
    void setViewY(float);
    void setViewWidth(float);
    void setViewHeight(float);
    void setPortWidth(float);
    void setPortHeight(float);
    void setPreservedForm(const string&);
    void setPreservedMode(const string&);
};

#endif