#ifndef _PARSER_H_
#define _PARSER_H_
// Khai báo lớp viewbox
class viewbox {
private:
    float viewX, viewY, viewWidth, viewHeight;
    float portWidth, portHeight;
    string preservedForm, preservedMode;

public:
    // Các phương thức getter và setter cho các thuộc tính
    float getViewX() const { return viewX; }
    float getViewY() const { return viewY; }
    float getViewWidth() const { return viewWidth; }
    float getViewHeight() const { return viewHeight; }
    float getPortWidth() const { return portWidth; }
    float getPortHeight() const { return portHeight; }
    const string& getPreservedForm() const { return preservedForm; }
    const string& getPreservedMode() const { return preservedMode; }

    void setViewX(float value) { viewX = value; }
    void setViewY(float value) { viewY = value; }
    void setViewWidth(float value) { viewWidth = value; }
    void setViewHeight(float value) { viewHeight = value; }
    void setPortWidth(float value) { portWidth = value; }
    void setPortHeight(float value) { portHeight = value; }
    void setPreservedForm(const string& value) { preservedForm = value; }
    void setPreservedMode(const string& value) { preservedMode = value; }
};
class parser {
private:
	unordered_map<string, color> colorMap;
	void processColor(string, string, color&);
	void loadColorMap();
	void processProperty(string, string, string, figure*&);
	//void parseGroupStr(string&);
public:
	void parseItem(group*, string, viewbox&);
};

#endif