#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b) {
	return b == 0 ? a : gcd(b, a % b);
}

typedef struct Rat {
	bool operator==(const Rat& r) const {
		if (this->numerator == r.numerator &&
				this->denominator == r.denominator &&
				this->isPositive == r.isPositive) {
			return true;
		}

		return false;
	}

	bool operator!=(const Rat& r) const {
		return !((*this) == r);
	}

	bool operator<(const Rat& r) const {
		unsigned long long leftNumerator = this->numerator * r.denominator;
		unsigned long long rNumerator = r.numerator * this->denominator;
		
		if (this->isPositive && !r.isPositive) {
			return false;
		}

		if (!this->isPositive && r.isPositive) {
			return true;
		}

		if (this->isPositive && r.isPositive) {
			return leftNumerator < rNumerator;
		} else {
			return leftNumerator > rNumerator;
		}
	}

	bool operator>(const Rat& r) const {
		return r < (*this);
	}

	bool operator<=(const Rat& r) const {
		return !((*this) > r);
	}

	bool operator>=( const Rat& r) const {
		return !((*this) < r);
	}

	Rat operator+(const Rat& r) const {
		unsigned long long thisNumerator = this->numerator * r.denominator;
		unsigned long long rightNumerator = r.numerator * this->denominator;

		Rat rat;

		if (this->isPositive && r.isPositive) {
			rat.numerator = thisNumerator + rightNumerator;
			rat.isPositive = true;
		} else if (!this->isPositive && r.isPositive) {
			if (thisNumerator > rightNumerator) {
				rat.numerator = thisNumerator - rightNumerator;
				rat.isPositive = false;
			} else {
				rat.numerator = rightNumerator - thisNumerator;
				rat.isPositive = true;
			}
		} else if (this->isPositive && !r.isPositive) {
			if (thisNumerator < rightNumerator) {
				rat.numerator = rightNumerator - thisNumerator;
				rat.isPositive = false;
			} else {
				rat.numerator = thisNumerator - rightNumerator;
				rat.isPositive = true;
			}
		} else {
			rat.numerator = rightNumerator + thisNumerator;
			rat.isPositive = false;
		}

		rat.denominator = this->denominator * r.denominator;
		rat.normalize();
		return rat;
	}

	Rat operator*(const Rat& r) const {
		Rat rat;
		rat.numerator = this->numerator * r.numerator;
		rat.denominator = this->denominator * r.denominator;
		rat.isPositive = true;

		if (!this->isPositive) {
			rat.isPositive = !rat.isPositive;
		}

		if (!r.isPositive) {
			rat.isPositive = !rat.isPositive;
		}

		rat.normalize();
		return rat;
	}

	Rat operator/(const Rat& r) const {
		Rat rat;
		rat.numerator = this->numerator * r.denominator;
		rat.denominator = this->denominator * r.numerator;
		rat.isPositive = true;

		if (!this->isPositive) {
			rat.isPositive = !rat.isPositive;
		}

		if (!r.isPositive) {
			rat.isPositive = !rat.isPositive;
		}

		rat.normalize();
		return rat;
	}

	Rat operator-() const {
		Rat rat;
		rat.numerator = this->numerator;
		rat.denominator = this->denominator;
		rat.isPositive = !this->isPositive;
		rat.normalize();
		return rat;
	}

	Rat operator-(const Rat& r) const {
		return (*this) + (-r);
	}

	void operator=(const int number) {
		this->isPositive = true;

		if (number < 0) {
			this->isPositive = false;
		}

		this->numerator = number;
		this->denominator = 1;
	}

	void normalize() {
		unsigned long long divideBy = gcd(this->numerator, this->denominator);
		if (divideBy > 1) {
			this->numerator = this->numerator / divideBy;
			this->denominator = this->denominator / divideBy;
		}

		if (this->numerator == 0) {
			this->denominator = 1;
			this->isPositive = true;
		}
	}

	double toDouble() {
		double sign = 1.0;
		if (!this->isPositive) {
			sign = -1.0;
		}

		return sign * (((double)this->numerator)/((double)this->denominator));
	}

	// ostream& operator<<(ostream& os) {
	// 	if (this->isPositive) {
	// 		os << this->numerator << "/" << this->denominator;
	// 	} else {
	// 		os << "-" << this->numerator << "/" << this->denominator;
	// 	}

	// 	return os;
	// }

	string toFractionString() {
		string s;
		stringstream strStream;

		if (this->isPositive) {
			strStream << this->numerator << "/" << this->denominator;
		} else {
			strStream << "-" << this->numerator << "/" << this->denominator;
		}
		
		return strStream.str();
	}

	unsigned long long numerator;
	unsigned long long denominator;
	bool isPositive;
} Rat;

long long myPow(double num, int exponent) {
	for (long i = 1; i < exponent; i++) {
		num = num * num;
	}
	return (long)num;
}

Rat newRat(long long numerator, long long denominator) {
	bool isPositive = true;
	if (numerator < 0) {
		isPositive = !isPositive;
		numerator = numerator * -1;
	}

	if (denominator < 0) {
		isPositive = !isPositive;
		denominator = denominator * -1;
	}

	Rat newRat;
	newRat.isPositive = isPositive;
	newRat.numerator = (unsigned long long)numerator;
	newRat.denominator = (unsigned long long)denominator;
	return newRat;
}

Rat newRatFromDouble(double number, int accuracy) {
	long long denominator = myPow(10, accuracy);
	return newRat((long long)(number * denominator), denominator);
}

Rat newRatFromInt(int number) {
	return newRat((long long)number, 1);
}

typedef struct Line {
	Rat startX;
	Rat startY;
	Rat endX;
	Rat endY;
} Line;

bool testIntersection(Line lineA, Line lineB) {
	Rat x0 = lineA.startX;
	Rat y0 = lineA.startY;
	Rat x1 = lineA.endX;
	Rat y1 = lineA.endY;

	Rat x2 = lineB.startX;
	Rat y2 = lineB.startY;
	Rat x3 = lineB.endX;
	Rat y3 = lineB.endY;

	Rat aTop = ((x3-x2)*(y0-y2)-((y3-y2)*(x0-x2)));
	Rat aBottom = ((y3-y2)*(x1-x0)-((x3-x2)*(y1-y0)));
	Rat bTop = ((x1-x0)*(y0-y2)-((y1-y0)*(x0-x2)));
	Rat bBottom = ((y3-y2)*(x1-x0)-((x3-x2)*(y1-y0)));

	Rat a = aTop/aBottom;
	Rat b = bTop/bBottom;

	if ((newRat(0, 1) <= a) && (newRat(1, 1) >= a) && (newRat(0, 1) <= b) && (newRat(1, 1) >= b)) {
		return true;
	}

	return false;
}

int main() {
	// ifstream inputFile("")

	// int startX, startY, endX, endY, timeTaken;
	// inputFile >> startX >> startY >> endX >> endY >> timeTaken;

	Line lineA;
	lineA.startX = 0;
	lineA.startY = 0;
	lineA.endX = 2;
	lineA.endY = 2;

	Line lineB;
	lineB.startX = 0;
	lineB.startY = 2;
	lineB.endX = 4;
	lineB.endY = 0;

	cout << "compare" << endl;
	cout << testIntersection(lineA, lineB) << endl;
	cout << (newRat(1, 10) + newRat(2, 10)).toFractionString() << endl;
	
	double a = 0.1;
	double b = 0.2;
	cout << a + b << endl;
}