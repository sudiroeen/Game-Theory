/*
  Copyright by:
  	Sudiro
	   [at] SudiroEEN@gmail.com
*/

#pragma once

#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace cv;

class GameTheory{
public:
	GameTheory(vector<Point2f> GainData, int row_, int col_);
	void optimize(int init_index);
private:
	void initParam();
	
private:
	int row, col;
	vector<Point2f> GD;
	Mat binGD;
	Mat* Player;

private:
	int vg = 100;
	int margin = 40;
	float lebarx = float(vg*col - 2*margin)/float(col);
	float lebary = float(vg*row - 2*margin)/float(row);

	Mat visBinGD;
	string window_name = "Game Theory";

private:
	int index_now, index_next;
	int player_id = 0;
	bool start = true;
	bool finish = false;
	Point point_now, point_next;
	inline void getMax(const Mat& matrix_, int& ind_max);
};
