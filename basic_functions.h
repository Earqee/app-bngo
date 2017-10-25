#ifndef BASIC_FUNCTIONS_H
#define BASIC_FUNCTIONS_H

inline double getAngle(double x1, double y1, double x2 = 0, double y2 = 0)
{
	return atan2(y1-y2, x1-x2);
}
inline double deg_to_rad(double angle)
{
	return (PI*angle)/180;
}

#endif