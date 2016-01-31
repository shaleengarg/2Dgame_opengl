#define MAX_MAP 1000

void reshapeWindow (GLFWwindow*, int, int);
static void error_callback(int, const char*);
void draw ();
GLFWwindow* initGLFW (int, int);
void initGL (GLFWwindow*, int, int);
int main (int, char**);


extern float triangle_rot_dir;
extern float rectangle_rot_dir;
extern bool triangle_rot_status;
extern bool rectangle_rot_status;
extern float camera_rotation_angle;
extern float rectangle_rotation;
extern float triangle_rotation;
extern GLuint programID,  textureProgramID;
extern int MAP[MAX_MAP];
