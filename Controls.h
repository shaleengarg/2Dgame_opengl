void keyboard (GLFWwindow*, int, int, int, int);
void keyboardChar (GLFWwindow* , unsigned int);
void mouseButton (GLFWwindow*, int, int, int);
void CursorPosition (GLFWwindow*, double , double );
void Scroll (GLFWwindow*, double, double );

extern float triangle_rot_dir;
extern float rectangle_rot_dir;
extern bool triangle_rot_status;
extern bool rectangle_rot_status;
extern float camera_rotation_angle;
extern float rectangle_rotation;
extern float triangle_rotation;
extern bool AngleChangeFlag;
extern float Topzoom;
extern float Followzoom;
extern float Towerzoom;
extern bool HeliChange; // for click and change the angle
extern bool AdChange;
