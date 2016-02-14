#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "Objects.h"
#include "Untouchable.h"
#include "Controls.h"
#define MAX_MAP 1000
#define MAP_CUBE_SIZE 10
#define MAX_DISP 4

using namespace std;
GLuint programID,  textureProgramID;
float triangle_rot_dir = 1;
float rectangle_rot_dir = -1;
bool triangle_rot_status = true;
bool rectangle_rot_status = true;
float camera_rotation_angle = 90;
float rectangle_rotation = 0;
float triangle_rotation = 0;
int MAP[MAX_MAP];
int No_cubes;

bool TopView = false;
bool TowerView = false;
bool AdventurerView = false;
bool FollowView = true;
bool HelicopterView = false;
float AdventureViewAngle = -1;
float Roh = 20;
float Theta = 45;
float Phi = 45;


void draw ()
{
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    //  Don't change unless you are sure!!
    static float c = 0;
    //c++;
    //Matrices.view = glm::lookAt(glm::vec3(1,0,3), glm::vec3(0,0,0), glm::vec3(sinf(c*M_PI/180.0),3*cosf(c*M_PI/180.0),0)); // Fixed camera for 2D (ortho) in XY plane
    if(TowerView == true)
    {
        Matrices.view = glm::lookAt(glm::vec3(Towerzoom, Towerzoom, Towerzoom), glm::vec3(Human.x, Human.y, Human.z), glm::vec3(0, 0, 1)); // Fixed camera for 2D (ortho) in XY plane
    }
    else if(TopView == true)
    {
        Matrices.view = glm::lookAt(glm::vec3(Human.x, Human.y-1, Human.z+Topzoom), glm::vec3(Human.x, Human.y, Human.z), glm::vec3(0,0,1)); // Fixed camera for 2D (ortho) in XY plane
        //cout << Human.x << " " << Human.y << " " << Human.z << endl;
    }
    else if(FollowView == true)
    {
        Matrices.view = glm::lookAt(glm::vec3(Human.x, Human.y-5 + Followzoom, Human.z+5+Followzoom), glm::vec3(Human.x, Human.y, Human.z), glm::vec3(0,0,1));
    }
    else if(AdventurerView == true)
    {
        Matrices.view = glm::lookAt(glm::vec3(Human.x, Human.y+1, Human.z+3), glm::vec3(Human.x+AdventureViewAngle, Human.y+10, Human.z), glm::vec3(0,0,1));
    }
    else if(HelicopterView == true)
    {
        float X, Y, Z;
        X = (Roh * cos(Theta*M_PI/180)*sin(Phi*M_PI/180)) + Human.x;
        Y = (Roh * sin(Theta*M_PI/180)*sin(Phi*M_PI/180)) + Human.y;
        Z = Roh *cos(Phi*M_PI/180);
        //cout << X << " " << Y << " " << Z << endl;
        Matrices.view = glm::lookAt(glm::vec3(X, Y, Z), glm::vec3(Human.x, Human.y, Human.z), glm::vec3(0,0,1));
        // Helicopter view to be implemented
    }
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;	// MVP = Projection * View * Model

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateX = glm::translate (glm::vec3(0.0f, 0.0f, 0.0f)); // glTranslatef
    //glm::mat4 rotateTriangle = glm::rotate((float)(triangle_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
    glm::mat4 XTransform = translateX ; //* rotateTriangle;
    Matrices.model *= XTransform;
    MVP = VP * Matrices.model; // MVP = p * V * M
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(X);


    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateY = glm::translate (glm::vec3(0.0f, 0.0f, 0.0f)); // glTranslatef
    //glm::mat4 rotateTriangle = glm::rotate((float)(triangle_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
    glm::mat4 YTransform = translateY ; //* rotateTriangle;
    Matrices.model *= YTransform;
    MVP = VP * Matrices.model; // MVP = p * V * M
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(Y);


    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateZ = glm::translate (glm::vec3(0.0f, 0.0f, 0.0f)); // glTranslatef
    //glm::mat4 rotateTriangle = glm::rotate((float)(triangle_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
    glm::mat4 ZTransform = translateZ ; //* rotateTriangle;
    Matrices.model *= ZTransform;
    MVP = VP * Matrices.model; // MVP = p * V * M
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(Z);

    // Render with texture shaders now
    glUseProgram(textureProgramID);

    // Pop matrix to undo transformations till last push matrix instead of recomputing model matrix
    // glPopMatrix ();
    /*
       Matrices.model = glm::mat4(1.0f);
       glm::mat4 translateRectangle = glm::translate (glm::vec3(2, 0, 0));        // glTranslatef
       glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
       Matrices.model *= (translateRectangle * rotateRectangle);
       MVP = VP * Matrices.model;
       glUniformMatrix4fv(Matrices.TexMatrixID, 1, GL_FALSE, &MVP[0][0]);
       glUniform1i(glGetUniformLocation(textureProgramID, "texSampler"), 0);
       draw3DTexturedObject(rectangle);
       */
    // Increment angles

    int i =0;
    glm::mat4 translateCubes;
    for (i=0; i < No_cubes; i++)
    {
        Matrices.model = glm::mat4(1.0f);
        if(Cube[i].move == true)
        {
            if(Cube[i].direction == 1)  // MOVE UP
            {
                Cube[i].z += 0.2;
                if(Cube[i].z >= MAX_DISP)
                    Cube[i].direction = 0;
            }
            else                       // MOVE DOWN
            {
                Cube[i].z -= 0.2;
                if(Cube[i].z <= -MAX_DISP)
                    Cube[i].direction = 1;
            }
        }
        translateCubes = glm::translate (glm::vec3(Cube[i].x, Cube[i].y, Cube[i].z));
        Matrices.model *= translateCubes;
        MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.TexMatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniform1i(glGetUniformLocation(textureProgramID, "texSampler"), 0);
        draw3DTexturedObject(Cube[i].cube);
    }

    //HUMAN IN MAKING

    glUseProgram (programID);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateHuman = glm::translate (glm::vec3(Human.x, Human.y, Human.z)); // glTranslatef
    glm::mat4 HumanTransform = translateHuman ; //* rotateTriangle;
    Matrices.model *= HumanTransform;
    MVP = VP * Matrices.model; // MVP = p * V * M
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(Human.sphere);

    //Checking collision with ground and objects
    for(i=0; i < No_cubes; i++)
    {
        //Collision using clamp
                
    }
}

void initGL (GLFWwindow* window, int width, int height)
{
    // Load Textures
    // Enable Texture0 as current texture memory
    glActiveTexture(GL_TEXTURE0);
    // load an image file directly as a new OpenGL texture
    // GLuint texID = SOIL_load_OGL_texture ("beach.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS); // Buggy for OpenGL3
    GLuint textureID = createTexture("1.jpg");
    // check for an error during the load process
    if(textureID == 0 )
        cout << "SOIL loading error: '" << SOIL_last_result() << "'" << endl;

    // Create and compile our GLSL program from the texture shaders
    textureProgramID = LoadShaders( "TextureRender.vert", "TextureRender.frag" );
    // Get a handle for our "MVP" uniform
    Matrices.TexMatrixID = glGetUniformLocation(textureProgramID, "MVP");


    createX();
    createY();
    createZ();
    createHuman();
    //For the MAP

    int i=-1, j=0, index =0; 
    static const char filename [] = "MAP.txt";
    FILE *Map_file = fopen(filename , "r");
    No_cubes = -1;
    if(Map_file != NULL)
    {
        char line[128];
        while(fgets(line, sizeof line, Map_file) != NULL)
        {
            i = 0;
            index =0;
            while(line[index] != '\0')
            {
                if(line[index] != '0')
                {
                    No_cubes += 1;
                    Cube[No_cubes].x = i*MAP_CUBE_SIZE;
                    Cube[No_cubes].y = j*MAP_CUBE_SIZE;
                    Cube[No_cubes].z = (int)(line[index] - '0');
                    createCubes(No_cubes, Cube[No_cubes].x, Cube[No_cubes].y, Cube[No_cubes].z, MAP_CUBE_SIZE, MAP_CUBE_SIZE, MAP_CUBE_SIZE, textureID);
                }
                i += 1;        
                index += 1;
            }
            j += 1;
        }
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "Sample_GL3.vert", "Sample_GL3.frag" );
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (0.0f, 0.0f, 0.0f, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

}

int main (int argc, char** argv)
{
    int width = 700;
    int height = 700;
    srand(time(NULL));

    GLFWwindow* window = initGLFW(width, height);

    initGL (window, width, height);

    double last_update_time = glfwGetTime(), current_time;

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {

        // OpenGL Draw commands
        draw();

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        glfwPollEvents();

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 0.5) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
