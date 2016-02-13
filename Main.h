#define MAX_MAP 1000
#define MAP_CUBE_SIZE 10

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
extern bool TopView;
extern bool TowerView;
extern bool AdventurerView;
extern bool FollowView;
extern bool HelicopterView;
extern float AdventureViewAngle;
extern float Roh;
extern float Theta;
extern float Phi;
