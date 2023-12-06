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

    void ResetToDefaults(){
        cameraPosX = 8;
        cameraPosY = 8;
        cameraPosZ = 40;
    }

    // Constructor to initialize values
    Camera() : cameraPosX(8), cameraPosY(8), cameraPosZ(45.0f), cameraYaw(0.0f), cameraPitch(-0.32f) {
    }
};

#endif  /* CAMERA_HPP_ */