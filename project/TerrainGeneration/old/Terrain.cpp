#include "Terrain.hpp"
#include <iostream>

#define FNL_IMPL
#include "FastNoise.h"

fnl_state noise = fnlCreateState();

void generateTerrain(){

	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			terrain[x][y][0] = float(x) * MAP_SCALE;
			terrain[x][y][1] = -float(y) * MAP_SCALE;
			terrain[x][y][2] = (float)fnlGetNoise2D(&noise, x, y);
		}
	}

}

void CleanUp()
{
	free(landTexture1);
	free(landTexture2);
    free(landTexture3);
}

void init(void) {
    // Setup 3D view
    std::cout << "test" << "\n";
    glMatrixMode(GL_PROJECTION);
    gluPerspective(
        60.0,  // field of view in degree
        1.0,   // aspect ratio
        1.0,   // Z near
        1500.0   // Z far
    );
    glMatrixMode(GL_MODELVIEW);


    //side view -->
    gluLookAt(-400.0, -middle, 300.0, middle, -256.0, 0.0, 0.0, 0.0, 1.0);



    //above top down view --> gluLookAt(middle, -middle, 800.0, middle, -middle, 0.0,  0.0, 1.0, 0.0);

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

	//glEnable( GL_TEXTURE_2D );


    for (int z = 0; z < MAP_Y - 1; z++)
    {

        for (int x = 0; x < MAP_X - 1; x++)
        {
            GLuint textureID;
            if (terrain[x][z][2] < 130)
                textureID = land1;  // Use Texture1 for height under 150
            else
                textureID = land2;
            glBindTexture(GL_TEXTURE_2D, textureID);
        	glBegin(GL_TRIANGLE_STRIP);
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

}






void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);

	render();

	glFlush();

	glutSwapBuffers();
}


int main(int argc, char **argv) {
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("3D Terrain");
	init();
	glutDisplayFunc(display);

	glutMainLoop();
}



