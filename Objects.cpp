#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <math.h>

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
    bool move;
    bool direction;
    float vx;
    float vy;
    float vz;
    float radius;
}Cubes;

typedef struct S{
    float x;
    float y; 
    float z;
    float radius;
    float vx;
    float vy;
    float vz;
    bool direction;
    VAO *sphere;
    GLuint textureID;

}Sphere;

Cubes Cube[MAX_CUBES];
Sphere Human;

VAO *triangle, *rectangle, *X, *Y, *Z;


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
/*
   int Collision(Cubes A, Cubes B)
   {
   bool CX = A.x + A.radius >= B.x && B.x + B.radius >= A.x;
   bool CY = A.y + A.radius >= B.y && B.y + B.radius >= A.y;
   bool CZ = A.z + A.radius >= B.z && B.z + B.radius >= A.z;

   bool CX = A->x + A->radius >= B->x && B->x + B->radius >= A->x;
   bool CY = A->y + A->radius >= B->y && B->y + B->radius >= A->y;
   bool CZ = A->z + A->radius >= B->z && B->z + B->radius >= A->z;

   return CX && CY && CZ;
   }
   */

void createCubes(int Cube_no, float x, float y, float z, float length, float width, float height, GLuint textureID)
{
    Cube[Cube_no].length = length;
    Cube[Cube_no].width = width;
    Cube[Cube_no].height = height;
    Cube[Cube_no].x = x; 
    Cube[Cube_no].y = y; 
    Cube[Cube_no].z = z; 
    Cube[Cube_no].textureID = textureID;
    if(Cube_no!= 0)
    {
        if(Cube_no%5 == 0)
        {
            int N = rand()%2;
            Cube[Cube_no].move = 1; 
            Cube[Cube_no].direction = N;
        }
    }

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

float DEG2RAD(float x)
{
    float a;
    a = x *M_PI/180;
    return a;
}

void createHuman()
{
    Human.radius = 2;
    Human.x = 0;
    Human.y = 0;
    Human.z = MAP_CUBE_SIZE-2;
    Human.direction = 1;
    GLfloat vertex_buffer_data [204410];
    GLfloat color_buffer_data[204410];
    int i, j, k=0;
    for(j=-90; j < 91; j++)
    {
        for(i = -180; i < 181; i++)
        {
            vertex_buffer_data[k] = Human.radius*cos(DEG2RAD(i))*cos(DEG2RAD(j));
            color_buffer_data[k] = 1;
            k++;
            vertex_buffer_data[k] = Human.radius*sin(DEG2RAD(i))*cos(DEG2RAD(j));
            color_buffer_data[k] = 0;
            k++;
            vertex_buffer_data[k] = Human.radius*sin(DEG2RAD(j));
            color_buffer_data[k] = 0;
            k++;
        }
    }
    Human.sphere = create3DObject(GL_TRIANGLE_FAN, 64800, vertex_buffer_data, color_buffer_data, GL_FILL);
}
