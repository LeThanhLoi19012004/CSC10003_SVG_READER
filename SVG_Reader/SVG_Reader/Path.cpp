#include "Lib.h"

Path::Path() :Figure() {}

Path::~Path() {}

void Path::updateProperty() {
	stringstream ss(line);
	string property, val, temp;

	while (ss >> property) {
		getline(ss, temp, '"');
		getline(ss, val, '"');
		if (property == "d") {
			if (val[0] != 'M' && val[0] != 'm')
				return;
			for (int i = 0; i < val.size(); i++) {
				if (isalpha(val[i])) {
					if (i + 1 < val.size() && val[i + 1] != ' ')
						val.insert(i + 1, " ");
					if (i - 1 > -1 && isdigit(val[i - 1]))
						val.insert(i, " ");
				}
				if (val[i] == ',')
					val[i] = ' ';
				if (val[i] == '-' && val[i - 1] != ' ')
					val.insert(i, " ");
			}

			for (int i = 0; i < val.size(); i++) {
				if (isalpha(val[i])) {
					int j = i + 1;
					while (!isalpha(val[j]) && j < val.size())
						j++;
					string pointStr = val.substr(i, j - i);

					/*string pointStr = "";
					pointStr += val[i];
					int j = i + 1;
					while (!isalpha(str[j]) && j < val.size()) {
						pointStr += val[j];
						j++;
					}*/

					pair<char, vector<Point>> pr;
					pr.first = pointStr[0];
					pointStr.erase(0, 2);

					stringstream ss(pointStr);
					if (pr.first == 'H' || pr.first == 'h' || pr.first == 'V' || pr.first == 'v') {
						string token;
						bool flag = false;
						while (ss >> token) {
							Point p;
							int n = vct[vct.size() - 1].second.size();

							if (pr.first == 'H' || pr.first == 'h') {
								p.setY(vct[vct.size() - 1].second[n - 1].getY());
								if (pr.first == 'H')
									p.setX(stof(token));
								else if (!flag) {
									p.setX(stof(token) + vct[vct.size() - 1].second[n - 1].getX());
									flag = true;
								}
								else p.setX(stof(token) + pr.second[pr.second.size() - 1].getX());
							}

							else if (pr.first == 'V' || pr.first == 'v') {
								p.setX(vct[vct.size() - 1].second[n - 1].getX());
								if (pr.first == 'V')
									p.setY(stof(token));
								else if (!flag) {
									p.setY(stof(token) + vct[vct.size() - 1].second[n - 1].getY());
									flag = true;
								}
								else p.setY(stof(token) + pr.second[pr.second.size() - 1].getY());
							}
							pr.second.push_back(p);
						}
						vct.push_back(pr);
					}

					else if (pr.first == 'Z' || pr.first == 'z') {
						pr.second.push_back(vct[0].second[0]);
						vct.push_back(pr);
					}

					else {
						string x = "", y = "";
						bool flag = false;
						while (ss >> x >> y) {
							int n = 0;
							if (vct.size() != 0)
								n = vct[vct.size() - 1].second.size();

							Point point;
							if (pr.first == 'M' || pr.first == 'L' || pr.first == 'C') {
								point.setX(stof(x));
								point.setY(stof(y));
							}
							else if (pr.first == 'm') {
								if (!flag) {
									if (vct.size() != 0) {
										point.setX(stof(x) + vct[vct.size() - 1].second[n - 1].getX());
										point.setY(stof(y) + vct[vct.size() - 1].second[n - 1].getY());
									}
									else {
										point.setX(stof(x));
										point.setY(stof(y));
									}
									flag = true;
								}
								else {
									int m = pr.second.size();
									point.setX(stof(x) + pr.second[m - 1].getX());
									point.setY(stof(y) + pr.second[m - 1].getY());
								}
							}
							else if (pr.first == 'l' || pr.first == 'c') {
								if (!flag) {
									point.setX(stof(x) + vct[vct.size() - 1].second[n - 1].getX());
									point.setY(stof(y) + vct[vct.size() - 1].second[n - 1].getY());
									flag = true;
								}
								else {
									int m = pr.second.size();
									point.setX(stof(x) + pr.second[m - 1].getX());
									point.setY(stof(y) + pr.second[m - 1].getY());
								}
							}
							pr.second.push_back(point);
						}
						vct.push_back(pr);
					}
				}
			}
		}
	}

	/*for (auto pair : vct) {
		cout << pair.first << ":";
		for (Point& point : pair.second) {
			cout << "(" << point.getX() << "," << point.getY() << ")" << " | ";
		}
		cout << "\n";
	}*/
}


//void Path::transformFigure() {
//	for (int i = 0; i < nVer; i++) {
//		float curX = this->Vers[i].getX();
//		float curY = this->Vers[i].getY();
//		for (auto p : transVct) {
//			if (p.first == "translate") {
//				this->Vers[i].setX(curX + p.second[0]);
//				this->Vers[i].setY(curY + p.second[1]);
//			}
//			if (p.first == "rotate") {
//				this->isRotate = true;
//
//				float A = cos(p.second[0] * Pi / 180.f);
//				float B = sin(p.second[0] * Pi / 180.f);
//				curX = (this->Vers[i].getX() * A - this->Vers[i].getY() * B);
//				curY = (this->Vers[i].getX() * B + this->Vers[i].getY() * A);
//				this->Vers[i].setX(curX);
//				this->Vers[i].setY(curY);
//			}
//			if (p.first == "scale") {
//				curX = this->Vers[i].getX();
//				curY = this->Vers[i].getY();
//				if (p.second.size() == 1) {
//					float scl = p.second[0];
//					this->Vers[i].setX(curX * scl);
//					this->Vers[i].setY(curY * scl);
//				}
//				else {
//					float sclX = p.second[0];
//					float sclY = p.second[1];
//
//					this->Vers[i].setX(curX * sclX);
//					this->Vers[i].setY(curY * sclY);
//
//				}
//			}
//		}
//
//	}
//}

vector<pair<char, vector<Point>>> Path::getProp() {
	return this->vct;
}