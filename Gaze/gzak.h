#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;
void analyze(double** & lines, double** f, int c);
int getRelation(double** line0, int c1, double** line1, int c2);
double** moveLine(double** line, int s, int x, int y);

wstring s2w(string str);