#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <GL/glut.h>
#include <cmath>

class Camera {
public:
    GLfloat cameraPosX;
    GLfloat cameraPosY;
    GLfloat cameraPosZ;
    GLfloat cameraYaw;
    GLfloat cameraPitch;

    // Constructor to initialize values
    Camera() : cameraPosX(-600.0), cameraPosY(20.0f), cameraPosZ(400.0), cameraYaw(260.0f), cameraPitch(0.0f) {
    }
};

#endif  /* CAMERA_HPP_ */