#include "pch.h"
#include <math.h> /* sin, cos, pow */
#include "matemathical_functions.h"

/* parabola */
float f1(float x) {
	return 1 - 5 * x + 3 * pow(x, 2);
}

/* cosinusoide */
float f2(float x) {
	return 0.5 + cos(2 * x); // lavora in rad
}

/* esponenziale */
float f3(float x) {
	return 2 + exp(25 * x);
}

/* bisettrice */
float f4(float x) {
	return x;
}

/* parabola con due radici */
float f5(float x) {
	return 2 * pow(x, 2) - 3 * x + 0.5;
}

/* costante */
float f6(float x) {
	return 3;
}

/* sinusoide */
float f7(float x) {
	return sin(x); // lavora in rad
}
