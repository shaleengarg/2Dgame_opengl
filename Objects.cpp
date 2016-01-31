#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "Main.h"
#include "Untouchable.h"
#include "Controls.h"

#define MAX_CUBES 1000
using namespace std;

struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;
    GLuint TextureBuffer;
    GLuint TextureID;

    GLenum PrimitiveMode; // GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY and GL_TRIANGLES_ADJACENCY
    GLenum FillMode; // GL_FILL, GL_LINE
    int NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint MatrixID; // For use with normal shader
    GLuint TexMatrixID; // For use with texture shader
};
struct GLMatrices Matrices;

typedef struct cub{
    float x;
    float y;
    float z;
    float length;
    float height;
    float width;
    GLuint textureID;
    VAO *cube;
}Cubes;

Cubes Cube[MAX_CUBES];
Cubes Human;

VAO *triangle, *rectangle, *X, *Y, *Z;

void createTriangle ()
{
    /* ONLY vertices between the bounds specified in glm::ortho will be visible on screen */

    /* Define vertex array as used in glBegin (GL_TRIANGLES) */
    static const GLfloat vertex_buffer_data [] = {
        0, 1,0, // vertex 0
        -1,-1,0, // vertex 1
        1,-1,0, // vertex 2
    };

    static const GLfloat color_buffer_data [] = {
        1,0,0, // color 0
        0,1,0, // color 1
        0,0,1, // color 2
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    triangle = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_LINE);
}

// Creates the rectangle object used in this sample code
void createRectangle (GLuint textureID)
{
    // GL3 accepts only Triangles. Quads are not supported
    static const GLfloat vertex_buffer_data [] = {
        -1.2,-1,0, // vertex 1
        1.2,-1,0, // vertex 2
        1.2, 1,0, // vertex 3

        1.2, 1,0, // vertex 3
        -1.2, 1,0, // vertex 4
        -1.2,-1,0  // vertex 1
    };

    static const GLfloat color_buffer_data [] = {
        1,0,0, // color 1
        0,0,1, // color 2
        0,1,0, // color 3

        0,1,0, // color 3
        0.3,0.3,0.3, // color 4
        1,0,0  // color 1
    };

    // Texture coordinates start with (0,0) at top left of the image to (1,1) at bot right
    static const GLfloat texture_buffer_data [] = {
        0,1, // TexCoord 1 - bot left
        1,1, // TexCoord 2 - bot right
        1,0, // TexCoord 3 - top right

        1,0, // TexCoord 3 - top right
        0,0, // TexCoord 4 - top left
        0,1  // TexCoord 1 - bot left
    };

    // create3DTexturedObject creates and returns a handle to a VAO that can be used later
    rectangle = create3DTexturedObject(GL_TRIANGLES, 6, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);
}

void createX()
{
    static const GLfloat vertex_buffer_data [] ={
        -500, 0,0,
        500,0,0
    };
    static const GLfloat color_buffer_data [] = {
        1, 0, 0,
        1, 0, 0,
    };
    X = create3DObject(GL_LINES, 2, vertex_buffer_data, color_buffer_data, GL_LINE);
}

void createY()
{
    static const GLfloat vertex_buffer_data [] ={
        0, -500,0,
        0,500,0
    };
    static const GLfloat color_buffer_data [] = {
        0, 1, 0,
        0, 1, 0,
    };
    Y = create3DObject(GL_LINES, 2, vertex_buffer_data, color_buffer_data, GL_LINE);
}

void createZ()
{
    static const GLfloat vertex_buffer_data [] ={
        0, 0, -500,
        0,0,500
    };
    static const GLfloat color_buffer_data [] = {
        0, 0, 1,
        0, 0, 1,
    };
    Z = create3DObject(GL_LINES, 2, vertex_buffer_data, color_buffer_data, GL_LINE);
}

void createCube(float x)
{
    static const GLfloat vertex_buffer_data [] ={
        -x/2,-x/2,-x/2, // triangle 1 : begin
        -x/2,-x/2, x/2,
        -x/2, x/2, x/2, // triangle 1 : end

        x/2, x/2,-x/2, // triangle 2 : begin
        -x/2,-x/2,-x/2,
        -x/2, x/2,-x/2, // triangle 2 : end

        x/2,-x/2, x/2,
        -x/2,-x/2,-x/2,
        x/2,-x/2,-x/2,

        x/2, x/2,-x/2,
        x/2,-x/2,-x/2,
        -x/2,-x/2,-x/2,

        -x/2,-x/2,-x/2,
        -x/2, x/2, x/2,
        -x/2, x/2,-x/2,

        x/2,-x/2, x/2,
        -x/2,-x/2, x/2,
        -x/2,-x/2,-x/2,

        -x/2, x/2, x/2,
        -x/2,-x/2, x/2,
        x/2,-x/2, x/2,

        x/2, x/2, x/2,
        x/2,-x/2,-x/2,
        x/2, x/2,-x/2,

        x/2,-x/2,-x/2,
        x/2, x/2, x/2,
        x/2,-x/2, x/2,

        x/2, x/2, x/2,
        x/2, x/2,-x/2,
        -x/2, x/2,-x/2,

        x/2, x/2, x/2,
        -x/2, x/2,-x/2,
        -x/2, x/2, x/2,

        x/2, x/2, x/2,
        -x/2, x/2, x/2,
        x/2,-x/2, x/2
    };

    static const GLfloat color_buffer_data [] ={
        0.583f,  0.771f,  0.014f,

        0.609f,  0.115f,  0.436f,

        0.327f,  0.483f,  0.844f,

        0.822f,  0.569f,  0.201f,

        0.435f,  0.602f,  0.223f,

        0.310f,  0.747f,  0.185f,

        0.597f,  0.770f,  0.761f,

        0.559f,  0.436f,  0.730f,

        0.359f,  0.583f,  0.152f,

        0.483f,  0.596f,  0.789f,

        0.559f,  0.861f,  0.639f,

        0.195f,  0.548f,  0.859f,

        0.014f,  0.184f,  0.576f,

        0.771f,  0.328f,  0.970f,

        0.406f,  0.615f,  0.116f,

        0.676f,  0.977f,  0.133f,

        0.971f,  0.572f,  0.833f,

        0.140f,  0.616f,  0.489f,

        0.997f,  0.513f,  0.064f,

        0.945f,  0.719f,  0.592f,

        0.543f,  0.021f,  0.978f,

        0.279f,  0.317f,  0.505f,

        0.167f,  0.620f,  0.077f,

        0.347f,  0.857f,  0.137f,

        0.055f,  0.953f,  0.042f,

        0.714f,  0.505f,  0.345f,

        0.783f,  0.290f,  0.734f,

        0.722f,  0.645f,  0.174f,

        0.302f,  0.455f,  0.848f,

        0.225f,  0.587f,  0.040f,

        0.517f,  0.713f,  0.338f,

        0.053f,  0.959f,  0.120f,

        0.393f,  0.621f,  0.362f,

        0.673f,  0.211f,  0.457f,

        0.820f,  0.883f,  0.371f,

        0.982f,  0.099f,  0.879f
    };


}

void createCubes(int Cube_no, float x, float y, float z, float length, float width, float height, GLuint textureID)
{
    Cube[Cube_no].length = length;
    Cube[Cube_no].width = width;
    Cube[Cube_no].height = height;
    Cube[Cube_no].x = x; 
    Cube[Cube_no].y = y; 
    Cube[Cube_no].z = z; 
    Cube[Cube_no].textureID = textureID;

    static const GLfloat vertex_buffer_data [] ={
        //left face
        -length/2,height/2,width/2, // vertex 1
        -length/2,-height/2,width/2, // vertex 2
        -length/2,-height/2,-width/2, // vertex 3

        -length/2,height/2,width/2, // vertex 1
        -length/2,-height/2,-width/2, // vertex 3
        -length/2,height/2,-width/2, //vertex 4

        //front face
        -length/2,height/2,width/2, // vertex 1
        length/2,height/2,width/2, // vertex 5
        -length/2,-height/2,width/2, // vertex 2

        length/2,height/2,width/2, // vertex 5
        -length/2,-height/2,width/2, // vertex 2
        length/2,-height/2,width/2, //vertex 6

        //top face
        -length/2,height/2,width/2, // vertex 1
        length/2,height/2,width/2, // vertex 5
        -length/2,height/2,-width/2, //vertex 4

        length/2,height/2,width/2, // vertex 5
        -length/2,height/2,-width/2, //vertex 4
        length/2,height/2,-width/2, // vertex 7

        //right face
        length/2,height/2,width/2, // vertex 5
        length/2,-height/2,width/2, //vertex 6
        length/2,height/2,-width/2, // vertex 7

        length/2,-height/2,width/2, //vertex 6
        length/2,height/2,-width/2, // vertex 7
        length/2,-height/2,-width/2, //vertex 8

        //Back face
        -length/2,-height/2,-width/2, // vertex 3
        -length/2,height/2,-width/2, //vertex 4
        length/2,height/2,-width/2, // vertex 7

        -length/2,-height/2,-width/2, // vertex 3
        length/2,-height/2,-width/2, //vertex 8
        length/2,height/2,-width/2, // vertex 7

        //Bottom face
        -length/2,-height/2,-width/2, // vertex 3
        length/2,-height/2,-width/2, //vertex 8
        length/2,-height/2,width/2, //vertex 6

        -length/2,-height/2,-width/2, // vertex 3
        -length/2,-height/2,width/2, // vertex 2
        length/2,-height/2,width/2 //vertex 6
    };
    static const GLfloat color_buffer_data [] ={
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };
    static const GLfloat texture_buffer_data [] ={
        0,1, 
        1,1, 
        1,0, 

        0,1,  
        1,0, 
        0,0, 

        1,1, 
        0,1, 
        1,0, 

        0,1,  
        1,0, 
        0,0, 

        1,1, 
        0,1, 
        1,0, 

        0,1,  
        1,0, 
        0,0, 

        1,1, 
        0,1, 
        1,0, 

        0,1,  
        1,0, 
        0,0, 

        1,1, 
        0,1, 
        1,0, 

        0,1,  
        1,0, 
        0,0, 

        1,1, 
        0,1, 
        1,0, 

        0,1,  
        1,0, 
        0,0, 
    };
    Cube[Cube_no].cube  = create3DTexturedObject(GL_TRIANGLES, 36, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);
}

void createHuman()
{
    Human.length = 2;
    Human.width = 2;
    Human.height =4;
    Human.x = 18;
    Human.y = 18;
    Human.z = 20;
    int length, width, height;
    length = Human.length;
    width = Human.height ;
    height = Human.width;

    static const GLfloat vertex_buffer_data [] ={
        //left face
        -length/2,height/2,width/2, // vertex 1
        -length/2,-height/2,width/2, // vertex 2
        -length/2,-height/2,-width/2, // vertex 3

        -length/2,height/2,width/2, // vertex 1
        -length/2,-height/2,-width/2, // vertex 3
        -length/2,height/2,-width/2, //vertex 4

        //front face
        -length/2,height/2,width/2, // vertex 1
        length/2,height/2,width/2, // vertex 5
        -length/2,-height/2,width/2, // vertex 2

        length/2,height/2,width/2, // vertex 5
        -length/2,-height/2,width/2, // vertex 2
        length/2,-height/2,width/2, //vertex 6

        //top face
        -length/2,height/2,width/2, // vertex 1
        length/2,height/2,width/2, // vertex 5
        -length/2,height/2,-width/2, //vertex 4

        length/2,height/2,width/2, // vertex 5
        -length/2,height/2,-width/2, //vertex 4
        length/2,height/2,-width/2, // vertex 7

        //right face
        length/2,height/2,width/2, // vertex 5
        length/2,-height/2,width/2, //vertex 6
        length/2,height/2,-width/2, // vertex 7

        length/2,-height/2,width/2, //vertex 6
        length/2,height/2,-width/2, // vertex 7
        length/2,-height/2,-width/2, //vertex 8

        //Back face
        -length/2,-height/2,-width/2, // vertex 3
        -length/2,height/2,-width/2, //vertex 4
        length/2,height/2,-width/2, // vertex 7

        -length/2,-height/2,-width/2, // vertex 3
        length/2,-height/2,-width/2, //vertex 8
        length/2,height/2,-width/2, // vertex 7

        //Bottom face
        -length/2,-height/2,-width/2, // vertex 3
        length/2,-height/2,-width/2, //vertex 8
        length/2,-height/2,width/2, //vertex 6

        -length/2,-height/2,-width/2, // vertex 3
        -length/2,-height/2,width/2, // vertex 2
        length/2,-height/2,width/2 //vertex 6
    };

    static const GLfloat color_buffer_data [] ={
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
    };
    //Removed Texture for Simplicity
    Human.cube = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
}
