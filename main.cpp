#include "GameTheory.hpp"

int main(int argc, char** argv){
	const String keys = "{init_index_ | 0 | random initialization}";
	CommandLineParser parser(argc, argv, keys);

	vector<Point2f> gain_data_{
		Point2f(1,5), Point2f(4,8), Point2f(2,6), Point2f(9,3), Point2f(2,9),
		Point2f(2,6), Point2f(4,4), Point2f(2,7), Point2f(3,3), Point2f(9,0),
		Point2f(5,4), Point2f(1,3), Point2f(5,4), Point2f(5,9), Point2f(6,2),
		Point2f(1,1), Point2f(3,6), Point2f(2,1), Point2f(3,5), Point2f(7,3),
		Point2f(3,9), Point2f(6,3), Point2f(4,5), Point2f(8,2), Point2f(1,4)
	};

	GameTheory GT(gain_data_, 5, 5);
	int init_index_ = parser.get<int>("init_index_");
	GT.optimize(init_index_);

	return 0;
}
