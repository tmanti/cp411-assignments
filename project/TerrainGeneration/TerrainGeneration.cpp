#include <GL/glut.h>
#include <windows.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>
#include <stdlib.h>

//compile g++ *.cpp *.hpp *.h -lopengl32 -lglu32 -lfreeglut -o terrain.exe

#define FNL_IMPL
#include "FastNoise.h"//perlin noise implementation found here: https://github.com/Auburn/FastNoiseLite/tree/master/C

#include "Textures.hpp"
#include "World.hpp"
#include "Chunk.hpp"
#include "Camera.hpp"

const int windowWidth = 1000;
const int windowHeight = 800;

char* rockTexturePath = "textures/rock.bmp";
char* grassTexturePath = "textures/grass.bmp";
char* snowTexturePath = "textures/snow.bmp";

int world_seed = 110;
int render_distance = 3;

World world = World(110, render_distance);
Camera camera;

bool mouseClicking = false;
int lastMouseX = 0;
int lastMouseY = 0;

void renderScene();
void reshape(int width, int height);
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);
void keyHandler(unsigned char key, int x, int y);
bool LoadTextures();
void mainMenu(GLint option);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D Terrain Demo");

    // Set up OpenGL options (optional)
    glMatrixMode(GL_PROJECTION);
    gluPerspective(
        90.0,  // field of view in degree
        1.0,   // aspect ratio
        1.0,   // Z near
        3000.0   // Z far
    );
    glMatrixMode(GL_MODELVIEW);

    //gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);

    // Load textures
    LoadTextures();

    // Set GLUT callback functions
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);

    glutDisplayFunc(renderScene);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutKeyboardFunc(keyHandler);

    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Regenerate With Random Seed", 1);
    glutAddMenuEntry("Quit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // Enter GLUT event processing loop

    glutMainLoop();

    return 0;
}

bool LoadTextures(){
    rockTexture = LoadBitmapFile(rockTexturePath, &rockInfo);
    if (!rockTexture)
        return false;

    // generate the first land texture as a mipmap
    glGenTextures(1, &rock_id);
    glBindTexture(GL_TEXTURE_2D, rock_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, rockInfo.biHeight, rockInfo.biWidth, GL_RGB, GL_UNSIGNED_BYTE, rockTexture);

    // load the second land texture data
    grassTexture = LoadBitmapFile(grassTexturePath, &grassInfo);
    if (!grassTexture)
        return false;

    // generate the second land texture as a mipmap
    glGenTextures(1, &grass_id);
    glBindTexture(GL_TEXTURE_2D, grass_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, grassInfo.biHeight, grassInfo.biWidth, GL_RGB, GL_UNSIGNED_BYTE, grassTexture);


    snowTexture = LoadBitmapFile("stone.bmp", &snowInfo);
       if (!snowTexture)
           return false;

       // generate the second land texture as a mipmap
       glGenTextures(1, &snow_id);
       glBindTexture(GL_TEXTURE_2D, snow_id);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
       gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, snowInfo.biHeight, snowInfo.biWidth, GL_RGB, GL_UNSIGNED_BYTE, snowTexture);
}

// Function to render a single chunk with texture mapping
void renderChunk(Chunk chunk) {
    glEnable(GL_TEXTURE_2D);

    //std::cout << chunk.getWorldPos()[0] << chunk.getWorldPos()[1] << "|" << chunk.start_x << "|" << chunk.start_y << "\n";

    for (int i = 0; i < CHUNKSIZE; ++i) {
        for (int j = 0; j < CHUNKSIZE; ++j) {
            // Bind the appropriate texture based on the terrain height
            GLfloat height = chunk.getHeightRel(i, j);
            GLuint textureID;

            if (height < 0.5) {
                textureID = grass_id;
            } else if (height < 0.7) {
                textureID = rock_id;
            } else {
                textureID = snow_id;
            }

            glBindTexture(GL_TEXTURE_2D, textureID);

            // Draw a quad with texture coordinates
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            //glColor3f(1, 0, 0);
            glVertex3f(chunk.start_x + i, chunk.start_y + j, height*20);

            glTexCoord2f(1.0f, 0.0f);
            //glColor3f(1, 0, 0);
            glVertex3f(chunk.start_x + i + 1, chunk.start_y + j, chunk.getHeightRel(i + 1, j)*20);

            glTexCoord2f(1.0f, 1.0f);
            //glColor3f(1, 0, 0);
            glVertex3f(chunk.start_x + i + 1, chunk.start_y + j + 1, chunk.getHeightRel(i + 1, j + 1)*20);

            glTexCoord2f(0.0f, 1.0f);
            //glColor3f(1, 0, 0);
            glVertex3f(chunk.start_x + i, chunk.start_y + j + 1, chunk.getHeightRel(i, j + 1)*20);
            glEnd();
        }
    }

    glDisable(GL_TEXTURE_2D);
}

// Function to update the camera based on user input
void updateCamera() {
    // Move camera based on WASD keys
    // Limit the pitch to avoid flipping the camera
    camera.cameraPitch = fmin(fmax(camera.cameraPitch, -1.5f), 1.5f);

    //std::cout << camera.cameraPitch << "\n";

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

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int MIN_HEIGHT = 40;

void keyHandler(unsigned char key, int x, int y){
    if (key =='w') {
        camera.cameraPosX += 1 * sin(camera.cameraYaw);
        camera.cameraPosY += 1 * cos(camera.cameraYaw);
        camera.cameraPosZ = MAX(camera.cameraPosZ + 1 * sin(camera.cameraPitch), MIN_HEIGHT);
    }
    if (key == 's') {
        camera.cameraPosX -= 1 * sin(camera.cameraYaw);
        camera.cameraPosY -= 1 * cos(camera.cameraYaw);
        camera.cameraPosZ = MAX(camera.cameraPosZ-1 * sin(camera.cameraPitch), MIN_HEIGHT);
    }
    if(key == ' '){
        camera.cameraPosZ += 1;
    }
    int new_world_x = camera.cameraPosX/CHUNKSIZE;
    int new_world_y = camera.cameraPosY/CHUNKSIZE;
    if(new_world_x - world.world_x == 1){
        world.LoadChunks(East);
    } else if(new_world_x - world.world_x == -1){
        world.LoadChunks(West); 
    }        
    if(new_world_y - world.world_y == 1){
        world.LoadChunks(South);
    } else if(new_world_y - world.world_y == -1){
        world.LoadChunks(North); 
    }
    glutPostRedisplay();
}

void renderScene() {
    // Clear the framebuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);

    // Update camera/view matrix based on user input
    updateCamera();

    // Render terrain with appropriate texture based on height
    glColor3f(0.5, 0.5, 0.5);  // Set a default color (adjust as needed)
    std::vector<Chunk> loaded = world.getLoadedChunks();
    for (int i = 0; i < loaded.size(); i++) {
        renderChunk(loaded[i]);
    }

    glCullFace(GL_BACK); 

    glutSwapBuffers();
}

void reshape(int width, int height) {
    // Update viewport and perspective projection matrix
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(width) / height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void rand_seed(){
    srand(time(NULL));   // Initialization, should only be called once.
    world_seed = rand();
    world = World(world_seed, render_distance);
}

void mainMenu(GLint option){
    switch(option){
        case 1:
            camera.ResetToDefaults();
            rand_seed();
            break;
        case 2:
            exit(0);
            break;
    }
    glutPostRedisplay();
}