#include "Lib.h"

path::path() : figure() {
	strokeLineJoin = "miter";
	strokeLineCap = "butt";
	fillRule = "nonzero";
}

path::~path() {}

void path::updateProperty() {
	ofstream ofs("test.txt", ios::out);
	stringstream ss(line_str);
	string property, val, temp;

	while (ss >> property) {
		getline(ss, temp, '"');
		getline(ss, val, '"');
		if (property == "stroke-linejoin")
			this->strokeLineJoin = val;
		else if (property == "stroke-linecap")
			this->strokeLineCap = val;
		else if (property == "d") {
			if (val[0] != 'M' && val[0] != 'm')
				return;
			for (int i = 0; i < val.size(); i++) {
				if (isalpha(val[i]) && val[i] != 'e') {
					if (i + 1 < val.size() && val[i + 1] != ' ')
						val.insert(i + 1, " ");
					if (i - 1 > -1 && isdigit(val[i - 1]))
						val.insert(i, " ");
				}
				if (val[i] == ',')
					val[i] = ' ';
				if (val[i] == '-' && val[i - 1] != ' ' && val[i - 1] != 'e')
					val.insert(i, " ");
			}

			for (int i = 0; i < val.size(); i++) {
				if (val[i] == '.') {
					int j = i + 1;
					for (j; j < val.size(); j++)
						if (val[j] == '.')
							break;
					int t = i + 1;
					for (t; t < j; ++t)
						if (val[t] == ' ')
							break;
					if (t == j) {
						val.insert(j, " ");
						i = j + 1;
					}
				}
			}

			for (int i = 0; i < val.size(); i++) {
				if (isalpha(val[i]) && val[i] != 'e') {
					int j = i + 1;
					while ((!isalpha(val[j]) || val[j] == 'e') && j < val.size())
						j++;
					string pointStr = val.substr(i, j - i);
					pair<char, vector<float>> pr;
					pr.first = pointStr[0];
					pointStr.erase(0, 2);

					stringstream ss(pointStr);

					if (pr.first == 'm') {
						bool first = true;
						string x = "", y = "";
						while (ss >> x >> y) {
							if (first) {
								int n = vct.size();
								if (n > 0) {
									int m = vct[n - 1].second.size();
									if (m > 1) {
										pr.second.push_back(stof(x) + vct[n - 1].second[m - 2]);
										pr.second.push_back(stof(y) + vct[n - 1].second[m - 1]);
									}
								}
								else {
									pr.second.push_back(stof(x));
									pr.second.push_back(stof(y));
								}
								first = false;
							}
							else {
								int n = pr.second.size();
								if (n > 1) {
									pr.second.push_back(stof(x) + pr.second[n - 2]);
									pr.second.push_back(stof(y) + pr.second[n - 1]);
								}
							}
						}
						vct.push_back(pr);
					}

					else if (pr.first == 'l') {
						bool first = true;
						string x = "", y = "";
						while (ss >> x >> y) {
							if (first) {
								int n = vct.size();
								if (n > 0) {
									int m = vct[n - 1].second.size();
									if (m > 1) {
										pr.second.push_back(stof(x) + vct[n - 1].second[m - 2]);
										pr.second.push_back(stof(y) + vct[n - 1].second[m - 1]);
										first = false;
									}
								}
							}
							else {
								int n = pr.second.size();
								if (n > 1) {
									pr.second.push_back(stof(x) + pr.second[n - 2]);
									pr.second.push_back(stof(y) + pr.second[n - 1]);
								}
							}
						}
						vct.push_back(pr);
					}

					else if (pr.first == 'H') {
						string x = "";
						while (ss >> x) {
							pr.second.push_back(stof(x));
							int n = vct.size();
							if (n > 0) {
								int m = vct[n - 1].second.size();
								if (m > 1)
									pr.second.push_back(vct[n - 1].second[m - 1]);
							}
						}
						vct.push_back(pr);
					}

					else if (pr.first == 'h') {
						bool first = true;
						string x = "";
						while (ss >> x) {
							if (first) {
								int n = vct.size();
								if (n > 0) {
									int m = vct[n - 1].second.size();
									if (m > 1) {
										pr.second.push_back(stof(x) + vct[n - 1].second[m - 2]);
										pr.second.push_back(vct[n - 1].second[m - 1]);
										first = false;
									}
								}
							}
							else {
								int n = pr.second.size();
								if (n > 1) {
									pr.second.push_back(stof(x) + pr.second[n - 2]);
									pr.second.push_back(pr.second[n - 1]);
								}
							}
						}
						vct.push_back(pr);
					}

					else if (pr.first == 'V') {
						string y = "";
						while (ss >> y) {
							int n = vct.size();
							if (n > 0) {
								int m = vct[n - 1].second.size();
								if (m > 1)
									pr.second.push_back(vct[n - 1].second[m - 2]);
							}
							pr.second.push_back(stof(y));
						}
						vct.push_back(pr);
					}

					else if (pr.first == 'v') {
						bool first = true;
						string y = "";
						while (ss >> y) {
							if (first) {
								int n = vct.size();
								if (n > 0) {
									int m = vct[n - 1].second.size();
									if (m > 1) {
										pr.second.push_back(vct[n - 1].second[m - 2]);
										pr.second.push_back(stof(y) + vct[n - 1].second[m - 1]);
										first = false;
									}
								}
							}
							else {
								int n = pr.second.size();
								if (n > 1) {
									pr.second.push_back(pr.second[n - 2]);
									pr.second.push_back(stof(y) + pr.second[n - 1]);
								}
							}
						}
						vct.push_back(pr);
					}

					else if (pr.first == 'T' || pr.first == 't') {
						bool first = true;
						string x = "", y = "";
						while (ss >> x >> y) {
							if (first) {
								int n = vct.size();
								if (n > 0) {
									int m = vct[n - 1].second.size();
									if (vct[n - 1].first == 'Q' || vct[n - 1].first == 'q' || vct[n - 1].first == 'T' || vct[n - 1].first == 't') {
										if (m > 3) {
											float oldx2 = vct[n - 1].second[m - 4];
											float oldy2 = vct[n - 1].second[m - 3];
											float curx = vct[n - 1].second[m - 2];
											float cury = vct[n - 1].second[m - 1];
											pr.second.push_back(2.f * curx - oldx2);
											pr.second.push_back(2.f * cury - oldy2);
										}
									}
									else {
										if (m > 1) {
											pr.second.push_back(vct[n - 1].second[m - 2]);
											pr.second.push_back(vct[n - 1].second[m - 1]);
										}
									}

									if (pr.first == 'T') {
										pr.second.push_back(stof(x));
										pr.second.push_back(stof(y));
									}
									else if (m > 1) {
										pr.second.push_back(stof(x) + vct[n - 1].second[m - 2]);
										pr.second.push_back(stof(y) + vct[n - 1].second[m - 1]);
									}
									first = false;
								}
							}
							else {
								int n = pr.second.size();
								if (n > 3) {
									float oldx2 = pr.second[n - 4];
									float oldy2 = pr.second[n - 3];
									float curx = pr.second[n - 2];
									float cury = pr.second[n - 1];
									pr.second.push_back(2.f * curx - oldx2);
									pr.second.push_back(2.f * cury - oldy2);
								}

								if (pr.first == 'T') {
									pr.second.push_back(stof(x));
									pr.second.push_back(stof(y));
								}
								else {
									pr.second.push_back(stof(x) + pr.second[n - 2]);
									pr.second.push_back(stof(y) + pr.second[n - 1]);
								}
							}
						}
						vct.push_back(pr);
					}

					else if (pr.first == 'c') {
						bool first = true;
						string x1 = "", y1 = "", x2 = "", y2 = "", x3 = "", y3 = "";
						while (ss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
							if (first) {
								int n = vct.size();
								if (n > 0) {
									int m = vct[n - 1].second.size();
									if (m > 1) {
										pr.second.push_back(stof(x1) + vct[n - 1].second[m - 2]);
										pr.second.push_back(stof(y1) + vct[n - 1].second[m - 1]);
										pr.second.push_back(stof(x2) + vct[n - 1].second[m - 2]);
										pr.second.push_back(stof(y2) + vct[n - 1].second[m - 1]);
										pr.second.push_back(stof(x3) + vct[n - 1].second[m - 2]);
										pr.second.push_back(stof(y3) + vct[n - 1].second[m - 1]);
										first = false;
									}
								}
							}
							else {
								int n = pr.second.size();
								if (n > 1) {
									pr.second.push_back(stof(x1) + pr.second[n - 2]);
									pr.second.push_back(stof(y1) + pr.second[n - 1]);
									pr.second.push_back(stof(x2) + pr.second[n - 2]);
									pr.second.push_back(stof(y2) + pr.second[n - 1]);
									pr.second.push_back(stof(x3) + pr.second[n - 2]);
									pr.second.push_back(stof(y3) + pr.second[n - 1]);
								}
							}
						}
						vct.push_back(pr);
					}

					else if (pr.first == 's' || pr.first == 'q') {
						bool first = true;
						string x1 = "", y1 = "", x2 = "", y2 = "";
						while (ss >> x1 >> y1 >> x2 >> y2) {
							if (first) {
								int n = vct.size();
								if (n > 0) {
									int m = vct[n - 1].second.size();
									if (m > 1) {
										pr.second.push_back(stof(x1) + vct[n - 1].second[m - 2]);
										pr.second.push_back(stof(y1) + vct[n - 1].second[m - 1]);
										pr.second.push_back(stof(x2) + vct[n - 1].second[m - 2]);
										pr.second.push_back(stof(y2) + vct[n - 1].second[m - 1]);
										first = false;
									}
								}
							}
							else {
								int n = pr.second.size();
								if (n > 1) {
									pr.second.push_back(stof(x1) + pr.second[n - 2]);
									pr.second.push_back(stof(y1) + pr.second[n - 1]);
									pr.second.push_back(stof(x2) + pr.second[n - 2]);
									pr.second.push_back(stof(y2) + pr.second[n - 1]);
								}
							}
						}
						vct.push_back(pr);
					}

					else if (pr.first == 'a') {
						bool first = true;
						string rx = "", ry = "", xAR = "0", lAF = "", sF = "", x = "", y = "";
						// xAR <=> x_axis_rotation, lAF <=> large_arc_flag, sF <=> sweep_flag
						while (ss >> rx >> ry >> xAR >> lAF >> sF >> x >> y) {
							if (first) {
								int n = vct.size();
								if (n > 0) {
									int m = vct[n - 1].second.size();
									if (m > 1) {
										pr.second.push_back(stof(rx));
										pr.second.push_back(stof(ry));
										pr.second.push_back(stof(xAR));
										pr.second.push_back(stof(lAF));
										pr.second.push_back(stof(sF));
										pr.second.push_back(stof(x) + vct[n - 1].second[m - 2]);
										pr.second.push_back(stof(y) + vct[n - 1].second[m - 1]);
										first = false;
									}
								}
							}
							else {
								int n = pr.second.size();
								if (n > 1) {
									pr.second.push_back(stof(rx));
									pr.second.push_back(stof(ry));
									pr.second.push_back(stof(xAR));
									pr.second.push_back(stof(lAF));
									pr.second.push_back(stof(sF));
									pr.second.push_back(stof(x) + pr.second[n - 2]);
									pr.second.push_back(stof(y) + pr.second[n - 1]);
								}
							}
						}
						vct.push_back(pr);
					}

					else if (pr.first == 'Z' || pr.first == 'z') {
						int n = vct.size();
						if (n > 0) {
							int m = vct[n - 1].second.size();
							if (m > 1) {
								pr.second.push_back(vct[n - 1].second[m - 2]);							
								pr.second.push_back(vct[n - 1].second[m - 1]);
							}
						}
						vct.push_back(pr);
					}

					else { // M, L, C, S, Q, A
						string token;
						while (ss >> token)
							pr.second.push_back(stof(token));
						vct.push_back(pr);
					}
				}
			}
		}
	}
}

string path::getStrokeLineJoin() {
	return this->strokeLineJoin;
}

string path::getStrokeLineCap() {
	return this->strokeLineCap;
}

string path::getFillRule() {
	return this->fillRule;
}

void path::setFillRule(string fillRule) {
	this->fillRule = fillRule;
}

void path:: setStrokeLineJoin(string linejoin) {
	this->strokeLineJoin = linejoin;
}

void path:: setStrokeLineCap(string linecap) {
	this->strokeLineCap = linecap;
}

void path:: setVct(vector<pair<char, vector<float>>> vct) {
	this->vct = vct;
}

vector<pair<char, vector<float>>> path::getProp() {
	return this->vct;
}