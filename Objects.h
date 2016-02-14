#define MAX_CUBES 1000
void createTriangle ();
void createRectangle (GLuint);
void createX();
void createY();
void createZ();
void createCubes(int, float, float, float, float, float, float, GLuint);
void createHuman();

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


typedef struct Cub{
    float x;
    float y;
    float z;
    float length;
    float height;
    float width;
    GLuint textureID;
    VAO* cube;
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

extern Cubes Cube[MAX_CUBES];
extern Sphere Human;

extern GLMatrices Matrices;

extern VAO *triangle, *rectangle, *X, *Y, *Z;
