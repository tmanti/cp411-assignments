#include "RBM.hpp"
#include <cmath>

#define Pi 3.141592653589793238462643

RBM::RBM() {
	reset();
}

RBM::~RBM() {
}

void RBM::reset() {
	R = 360;
	S = 5;
	T = 25;
	row = R / 5 + 1;
	col = T + 1;
}

// generate the mesh point and normal of rotation surface

Vector RotateVector(const Vector& v, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    float newX = v.x * cosA - v.y * sinA;
    float newY = v.x * sinA + v.y * cosA;
    float newZ = v.z;

    return Vector(newX, newY, newZ);
}

Point RotatePoint(const Point& p, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);

	Point pnt = Point();

    pnt.x = p.x * cosA - p.y * sinA;
    pnt.y = p.x * sinA + p.y * cosA;
    pnt.z = p.z;

    return pnt;
}

void RBM::RotateCurve() {
	Point pts[col];
    Vector tangents[col];
	// your code
	// 1. call curve->computeBezPtTan function to fill up pts and tangents
	// 2. rotate curve to generate surface mesh point and normal data and store in Pts and Normal.

	curve->computeBezPtsTan(col, pts, tangents);

    // Now rotate the curve and generate surface mesh point and normal data
	float angle_step = S * Pi / 180; // Rotate by S degrees
    float cosA = cos(angle_step);
    float sinA = sin(angle_step);

    for (int i = 0; i < T; i++) {
        for (int j = 0; j < curve->nCtrlPts; j++) {
			Point pnt = Point();
            pnt.x = curve->ctrlPts[j].x * cos(angle_step) - curve->ctrlPts[j].y * sin(angle_step);
            pnt.y = curve->ctrlPts[j].x * sin(angle_step) + curve->ctrlPts[j].y * cos(angle_step);
            pnt.z = curve->ctrlPts[j].z;
            curve->ctrlPts[j] = pnt;
        }

		 for (int x = 0; x < T; x++) {
            // Assuming you have a RotateVector function in your Vector class
            Vector rotatedNormal = RotateVector(tangents[x], angle_step * i);
            Normal[i][x] = rotatedNormal;

            // Assuming you have a RotatePoint function in your Point class
            Point rotatedPoint = RotatePoint(pts[x], angle_step * i);
            Pts[i][x] = rotatedPoint;
        }

    }
}


void RBM::setRotationCurve(Bezier *curve1)
{
	curve = curve1;
}
