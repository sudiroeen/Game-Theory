/*
  Copyright by:
  	Sudiro
	   [at] SudiroEEN@gmail.com
*/

#include "GameTheory.hpp"

GameTheory::GameTheory(vector<Point2f> GainData, int row_, int col_)
		   : GD(GainData), row(row_), col(col_), Player(new Mat[2])
{
	initParam();
}

inline void GameTheory::getMax(const Mat& matrix_, int& ind_max){
	double minval, maxval;
	Point minloc, maxloc;

	minMaxLoc(matrix_, &minval, &maxval, &minloc, &maxloc);
	if(matrix_.rows > matrix_.cols)
		ind_max = maxloc.y;
	else
		ind_max = maxloc.x;
}

void GameTheory::initParam(){
	binGD = Mat::zeros(row, col, CV_8UC1);

	for(int np=0; np<2; np++)
		Player[np] = Mat::zeros(row, col, CV_32FC1);

	visBinGD = Mat(vg*row, vg*col, CV_8UC3, Scalar::all(255));

	char todo = 'a';
	for(int c=0; c<col; c++){
		stringstream ss2;
		ss2 << todo << 2;
		todo ++;
		putText(visBinGD, ss2.str(), Point2f(margin+lebarx/2+c*lebarx-20, (margin >> 1)), FONT_HERSHEY_DUPLEX, 0.8, Scalar(0,143,143), 1);
	}

	todo = 'a';
	for(int r=0; r<row; r++){
		stringstream ss1;
		ss1 << todo << 1;
		todo ++;
		putText(visBinGD, ss1.str(), Point2f((margin >> 1) - 15, margin+lebary/2+r*lebary+10), FONT_HERSHEY_DUPLEX, 0.8, Scalar(0,143,143), 1);

		for(int c=0; c<col; c++){
			Player[0].at<float>(r,c) = GD[r*col+c].x;
			Player[1].at<float>(r,c) = GD[r*col+c].y;

			Point2f tl_ = Point2f(margin+c*lebarx, margin+r*lebary);
			Point2f br_ = Point2f(margin+(c+1)*lebarx, margin+(r+1)*lebary);
			rectangle(visBinGD, tl_, br_, Scalar(255,0,0), 2);

			stringstream ss;
			ss << GD[r*col+c].x << "," << GD[r*col+c].y;
			putText(visBinGD, ss.str(), Point2f(margin+lebarx/2+c*lebarx-20, margin+lebary/2+r*lebary+10), FONT_HERSHEY_DUPLEX, 1.0, Scalar::all(0), 1);
		}
	}
}

void GameTheory::optimize(int init_index){
	if(init_index > max(row-1, col-1)){
		cout << "init_index > " << max(row-1, col-1) << endl;
		exit(-1);
	}else if(init_index < 0){
		cout << "init_index must be real number!" << endl;
		exit(-1);
	}

	index_now = init_index;
	int langkah = 0;
	while(true){
		stringstream ssl;
		ssl << langkah;

		if(! player_id){
			getMax(Player[player_id+1].row(index_now), index_next);
			if(binGD.at<uchar>(index_now, index_next))
				finish = true;
			else
				binGD.at<uchar>(index_now, index_next) = uchar(1);

			player_id = 1;
			point_next = Point(index_next, index_now);
		}else{
			getMax(Player[player_id-1].col(index_now), index_next);
			if(binGD.at<uchar>(index_next, index_now))
				finish = true;
			else
				binGD.at<uchar>(index_next, index_now) = uchar(1);

			player_id = 0;
			point_next = Point(index_now, index_next);
		}

		if(finish)
			circle(visBinGD, Point(margin + lebarx/2.0 + point_next.x*lebarx, margin + lebary/2.0 + point_next.y*lebary),
							 10, Scalar(0,255,150), 2);

		
		if(start){
			point_now = Point(index_next, index_now);
			start = false;
			putText(visBinGD, ssl.str(), Point(margin + lebarx/2.0 + point_now.x*lebarx - 30, margin + lebary/2.0 + point_now.y*lebary - 30), FONT_HERSHEY_DUPLEX, 0.4, Scalar(0, 0, 255), 1);
		}else{
			arrowedLine(visBinGD, Point(margin + lebarx/2.0 + point_now.x*lebarx, margin + lebary/2.0 + point_now.y*lebary),
								  Point(margin + lebarx/2.0 + point_next.x*lebarx, margin + lebary/2.0 + point_next.y*lebary), 
					              Scalar(0,0,255), 2);
			putText(visBinGD, ssl.str(), Point(margin + lebarx/2.0 + point_now.x*lebarx - 30, margin + lebary/2.0 + point_now.y*lebary - 30), FONT_HERSHEY_DUPLEX, 0.4, Scalar(0, 0, 255), 1);
			point_now = point_next;
		}

		if(finish)
			break;

		index_now = index_next;
		langkah ++;
		imshow(window_name, visBinGD);
		waitKey(500);
	}

	while(true){
		imshow(window_name, visBinGD);
		if(waitKey(1) == 27)
			break;
	}
}
