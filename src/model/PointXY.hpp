#ifndef pointxy
#define pointxy
class PointXY {
	double x;
	double y;

public:
	PointXY(double x, double y) {
		this->x = x;
		this->y = y;
	}
	double getX() {
		return x;
	}
	double getY() {
		return y;;

	}

};

#endif