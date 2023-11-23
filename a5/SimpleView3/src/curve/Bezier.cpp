#include "Bezier.hpp"


extern GLint winWidth, winHeight;

Bezier::Bezier() {
	reset();
}

void Bezier::reset() {
	nCtrlPts = 0;
	nPts = 26;
}

/*  Compute binomial coefficients C[n] for given value of n, output in GLint C[] */
void Bezier::binomialCoeffs(GLint n, GLint C[]) {
     for (GLint k = 0; k <= n; k++) {
        // Compute C(n, k) = n! / (k! * (n-k)!)
        C[k] = 1;
        for (GLint j = n; j >= k + 1; j--) {
            C[k] *= j;
        }
        for (GLint j = n - k; j >= 2; j--) {
            C[k] /= j;
        }
    }
}

/*  Compute Bezier point at u, and output in Point *bezPt */
void Bezier::computeBezPt(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt)
{
	GLint n = nCtrlPts - 1; // Degree of the Bezier curve

    bezPt->x = bezPt->y = bezPt->z = 0.0;

    for (GLint i = 0; i < nCtrlPts; i++) {
        GLfloat bez = C[i] * pow(u, i) * pow(1.0 - u, n - i);
        bezPt->x += ctrlPts[i].x * bez;
        bezPt->y += ctrlPts[i].y * bez;
        bezPt->z += ctrlPts[i].z * bez;
    }
}

/*  Compute both Bezier point and tangent at u, and output in Point bezPt and Vector bezTan respectively*/
void Bezier::computeBezPtTan(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt, Vector *bezTan)
{
// your code
	GLint n = nCtrlPts - 1; // Degree of the Bezier curve

    bezPt->x = bezPt->y = bezPt->z = 0.0;
    bezTan->x = bezTan->y = bezTan->z = 0.0;

    for (GLint i = 0; i < nCtrlPts; i++) {
        GLfloat bez = C[i] * pow(u, i) * pow(1.0 - u, n - i);
        bezPt->x += ctrlPts[i].x * bez;
        bezPt->y += ctrlPts[i].y * bez;
        bezPt->z += ctrlPts[i].z * bez;
    }

    for (GLint i = 0; i < nCtrlPts - 1; i++) {
        GLfloat blend = C[i] * (i - n * u) * pow(u, i - 1) * pow(1.0 - u, n - i);
        bezTan->x += ctrlPts[i + 1].x * blend;
        bezTan->y += ctrlPts[i + 1].y * blend;
        bezTan->z += ctrlPts[i + 1].z * blend;
    }
}


/* call to compute the sequence of points on Bezier curve for drawing Bezier curve */
void Bezier::computeBezCurvePts() {
	GLfloat u = 0;
	GLint C[nCtrlPts];
	binomialCoeffs(nCtrlPts-1, C);
	for (int k = 0; k < nPts; k++) {
		u = GLfloat(k) / GLfloat(nPts-1);
		computeBezPt(u, nCtrlPts, ctrlPts, C, &Pts[k]);
	}
}


/* call to compute the sequence of points and tangents on Bezier curve for mesh of rotating Bezier curve */
void Bezier::computeBezPtsTan(GLint npts, Point pts[], Vector tangents[]) {
	GLfloat u = 0;
	GLint C[nCtrlPts];
	binomialCoeffs(nCtrlPts-1, C);
	for (int k = 0; k < npts; k++) {
		u = GLfloat(k) / GLfloat(npts-1);
		computeBezPtTan(u, nCtrlPts, ctrlPts, C, &pts[k],  &tangents[k]);
	}
}


void Bezier::drawCPts() {
	glPointSize(3.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < nCtrlPts; i++) {
		glVertex2f(ctrlPts[i].x, ctrlPts[i].y);
	}
	glEnd();
}

/* display Control points in 2D view */
void Bezier::displayCPts() {
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
}

/* display Control points and curve in 2D view */
void Bezier::display() {
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
	drawCurve();
}

