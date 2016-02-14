void quit(GLFWwindow*);
GLuint LoadShaders(const char *, const char *);
struct VAO* create3DObject (GLenum, int, const GLfloat*, const GLfloat*, GLenum);
struct VAO* create3DTexturedObject (GLenum, int, const GLfloat*, const GLfloat*, GLuint, GLenum);
void draw3DObject (struct VAO*);
void draw3DTexturedObject (struct VAO*);
GLuint createTexture (const char*);
static void error_callback(int, const char*);
void reshapeWindow (GLFWwindow*, int, int);
GLFWwindow* initGLFW (int, int);

extern GLuint programID;
