#include "Terrain_kbk.hpp"
#include <iostream>

#include "Camera.hpp"
Camera camera;

bool mouseClicking = false;
int lastMouseX = 0;
int lastMouseY = 0;

//g++ Terrain_kbk.hpp Terrain_kbk.cpp Camera.hpp -lopengl32 -lglu32 -lfreeglut -lglew32 -o terrain.exe

void updateCamera();

void generateTerrain(){

	for (int z = 0; z < MAP_Z; z++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			terrain[x][z][0] = float(x) * MAP_SCALE;
			terrain[x][z][1] = -float(z) * MAP_SCALE;
			terrain[x][z][2] = (float)imageData[(z * MAP_Z + x) * 3];
		}
	}

}

void CleanUp()
{
	free(imageData);
	free(landTexture1);
	free(landTexture2);
}

void init(void) {
    // Setup 3D view
    glMatrixMode(GL_PROJECTION);
    gluPerspective(
        60.0,  // field of view in degree
        1.0,   // aspect ratio
        1.0,   // Z near
        1500.0   // Z far
    );
    glMatrixMode(GL_MODELVIEW);


    //side view -->
    //gluLookAt(-600.0, -middle-100, 400.0, middle+100, -256.0, 0.0, 0.0, 0.0, 1.0);



    //above top down view -->gluLookAt(middle, -middle, 800.0, middle, -middle, 0.0,  0.0, 1.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    imageData = LoadBitmapFile("terrain2.bmp", &bitmapInfoHeader);
    glEnable(GL_TEXTURE_2D);
    generateTerrain();
    LoadTextures();




    // Set the polygon mode to wireframe
    //glPolygonMode(GL_FRONT, GL_LINE);
    //glPolygonMode(GL_BACK, GL_LINE);
}



void render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	glEnable( GL_TEXTURE_2D );

    updateCamera();

    glBindTexture(GL_TEXTURE_2D, land2);

    for (int z = 0; z < MAP_Z - 1; z++)
    {
    	glBegin(GL_TRIANGLE_STRIP);

        for (int x = 0; x < MAP_X - 1; x++)
        {
            GLuint textureID;


            // for each vertex, we calculate
            // the grayscale shade color,
            // we set the texture coordinate,
            // and we draw the vertex.

            // draw vertex 0
        	glTexCoord2f(0.0f, 0.0f);
        	glColor3f(terrain[x][z][2] / 255.0f, terrain[x][z][2] / 255.0f, terrain[x][z][2] / 255.0f);
            glVertex3f(terrain[x][z][0],
                       terrain[x][z][1], terrain[x][z][2]);

            // draw vertex 1
            glTexCoord2f(1.0f, 0.0f);
            glColor3f(terrain[x][z][2] / 255.0f, terrain[x][z][2] / 255.0f, terrain[x][z][2] / 255.0f);
            glVertex3f(terrain[x+1][z][0], terrain[x+1][z][1],
                       terrain[x+1][z][2]);

            // draw vertex 2
            glTexCoord2f(0.0f, 1.0f);
            glColor3f(terrain[x][z][2] / 255.0f, terrain[x][z][2] / 255.0f, terrain[x][z][2] / 255.0f);
            glVertex3f(terrain[x][z+1][0], terrain[x][z+1][1],
                       terrain[x][z+1][2]);

            // draw vertex 3
            glTexCoord2f(1.0f, 1.0f);
            glColor3f(terrain[x][z][2] / 255.0f, terrain[x][z][2] / 255.0f, terrain[x][z][2] / 255.0f);
            glVertex3f(terrain[x+1][z+1][0],
                       terrain[x+1][z+1][1],
                       terrain[x+1][z+1][2]);
        }
        glEnd();
    }


    	glEnable(GL_BLEND);

    	// enable read-only depth buffer
    	glDepthMask(GL_FALSE);

    	// set the blend function to what we use for transparency
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    	// set back to normal depth buffer mode (writable)
    	glDepthMask(GL_TRUE);

    	// disable blending
    	glDisable(GL_BLEND);

    	glFlush();

        water();
        snow();
        rock();

}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);

	render();

	glFlush();

	glutSwapBuffers();
}

// Function to update the camera based on user input
void updateCamera() {
    // Move camera based on WASD keys
    // Limit the pitch to avoid flipping the camera
    camera.cameraPitch = fmin(fmax(camera.cameraPitch, -1.5f), 1.5f);

    // Set the camera perspective
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        camera.cameraPosX, camera.cameraPosY, camera.cameraPosZ,
        camera.cameraPosX + 10.0f * sin(camera.cameraYaw) * cos(camera.cameraPitch),
        camera.cameraPosY + 10.0f * cos(camera.cameraYaw) * cos(camera.cameraPitch),
        camera.cameraPosZ + 10.0f * sin(camera.cameraPitch),
        0.0f, 0.0f, 1.0f
    );
}

// Function to handle mouse click and drag
void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseClicking = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            mouseClicking = false;
        }
    }
}

// Function to handle mouse drag
void motionFunc(int x, int y) {
    if (mouseClicking) {
        camera.cameraYaw += 0.005f * (lastMouseX - x);
        camera.cameraPitch += 0.005f * (y - lastMouseY);

        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

void keyHandler(unsigned char key, int x, int y){
    if (key =='w') {
        camera.cameraPosX += 5 * sin(camera.cameraYaw);
        camera.cameraPosY += 5 * cos(camera.cameraYaw);
        camera.cameraPosZ += 5 * sin(camera.cameraPitch);
    }
    if (key == 's') {
        camera.cameraPosX -= 5 * sin(camera.cameraYaw);
        camera.cameraPosY -= 5 * cos(camera.cameraYaw);
        camera.cameraPosZ -= 5 * sin(camera.cameraPitch);
    }
    glutPostRedisplay();
}




int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("3D Terrain");
	init();

	glutDisplayFunc(display);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutKeyboardFunc(keyHandler);

	glutMainLoop();
}



