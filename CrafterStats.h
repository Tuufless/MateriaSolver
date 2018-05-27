#ifndef CRAFTER_STATS_H
#define CRAFTER_STATS_H

class Stats
{
public:
	Stats(int craftsmanship, int control, int CP) : craftsmanship(craftsmanship), control(control), cp(CP) {
	}

	Stats operator+(const Stats& rhs) const {
		return Stats(craftsmanship + rhs.craftsmanship, control + rhs.control, cp + rhs.cp);
	}

	Stats operator-(const Stats& rhs) const {
		return Stats(craftsmanship - rhs.craftsmanship, control - rhs.control, cp - rhs.cp);
	}

	Stats& operator+=(const Stats& rhs) {
		craftsmanship += rhs.craftsmanship;
		control += rhs.control;
		cp += rhs.cp;
		return *this;
	}

	int craftsmanship;
	int control;
	int cp;
};

Stats operator*(const int lhs, const Stats& rhs) {
	return Stats(lhs * rhs.craftsmanship, lhs * rhs.control, lhs* rhs.cp);
}

#endif