#include "gzak.h"
void analyze(double** & lines, double** f, int c) {
		lines = new double* [c];
		for (int i = 0; i < c; i++)
				lines[i] = new double[4];
		for (int i = 0; i < c; i++) {
				if (i < c - 1) {
						lines[i][0] = (f[i][1] - f[i + 1][1]) / (f[i][0] - f[i + 1][0]);
						lines[i][1] = f[i][1] - (f[i + 1][1] - f[i][1]) / (f[i + 1][0] - f[i][0]) * f[i][0];
						lines[i][2] = f[i][0];
						lines[i][3] = f[i + 1][0];
				}
				else {
						lines[i][0] = (f[i][1] - f[0][1]) / (f[i][0] - f[0][0]);
						lines[i][1] = f[i][1] - (f[0][1] - f[i][1]) / (f[0][0] - f[i][0]) * f[i][0];
						lines[i][2] = f[i][0];
						lines[i][3] = f[0][0];
				};
		};
}
int getRelation(double** line0,int c1, double** line1, int c2) {
		
		int r = 0;
		for (int i = 0; i < c1; i++) {
				for (int j = 0; j < c2; j++) {
						double xS = (line0[i][1] - line1[j][1]) / (line1[j][0] - line0[i][0]);
						double x1 = line0[i][2], x1_ = line0[i][3];
						double x2 = line1[j][2], x2_ = line1[j][3];
						if ((xS<x1 && xS>x1_) || (xS<x1_ && xS>x1))
								if ((xS<x2 && xS>x2_) || (xS<x2_ && xS>x2))
										r++;
				}
		}
		delete* line0;
		delete* line1;
		return r;
};
double** moveLine(double** line, int s,int x,int y) {
		double** l = new double* [s];
		for (int i = 0; i < s; i++) {
				l[i] = new double[4];
				l[i][1] = line[i][1] - line[i][0] * x;
				l[i][1] = line[i][1] + y;
				l[i][2] = line[i][2] + x;
				l[i][3] = line[i][3] + x;
		}
		return l;
}

wstring s2w(string str)
{
    wstring result;
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    TCHAR* buffer = new TCHAR[len + 1];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0'; 
    result.append(buffer);
    delete[] buffer;
    return result;
}
