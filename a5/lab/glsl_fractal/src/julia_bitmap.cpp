//#include <iostream>
//#include <GL/glut.h>
//#include "glsl/bitmap.h"
//
//#define DIM 512
//
//int width = DIM;
//int height = DIM;
//
//Bitmap bitmap(DIM, DIM);
//
//struct cuComplex {
//    float   r;
//    float   i;
//    cuComplex( float a, float b ) : r(a), i(b)  {}
//    float magnitude2( void ) { return r * r + i * i; }
//    cuComplex operator*(const cuComplex& a) {
//        return cuComplex(r*a.r - i*a.i, i*a.r + r*a.i);
//    }
//    cuComplex operator+(const cuComplex& a) {
//        return cuComplex(r+a.r, i+a.i);
//    }
//};
//
//int julia( int x, int y ) {
//    const float scale = 1.5;
//    float jx = scale * (float)(DIM/2 - x)/(DIM/2);
//    float jy = scale * (float)(DIM/2 - y)/(DIM/2);
//
//    cuComplex c(-0.8, 0.156);
//    cuComplex a(jx, jy);
//
//    int i = 0;
//    for (i=0; i<200; i++) {
//        a = a * a + c;
//        if (a.magnitude2() > 1000)
//            return 0;
//    }
//
//    return 1;
//}
//
//void setJuliaBitmap( unsigned char *ptr ){
//    for (int y=0; y<DIM; y++) {
//        for (int x=0; x<DIM; x++) {
//            int offset = x + y * DIM;
//            int juliaValue = julia( x, y );
//            ptr[offset*4 + 0] = 255 * juliaValue;
//            ptr[offset*4 + 1] = 0;
//            ptr[offset*4 + 2] = 0;
//            ptr[offset*4 + 3] = 255;
//        }
//    }
// }
//
//void display() {
//	 bitmap.render();
//}
//
//int main(int argc, char** argv ) {
//	setJuliaBitmap(bitmap.get_ptr());
//    glutInit(&argc, argv);
//    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
//    glutInitWindowSize(width, height);
//    glutCreateWindow( "Julia set" );
//    glutDisplayFunc(display);
//    glutMainLoop();
//
//}
