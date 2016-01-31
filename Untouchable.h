void quit(GLFWwindow*);
GLuint LoadShaders(const char *, const char *);
struct VAO* create3DObject (GLenum, int, const GLfloat*, const GLfloat*, GLenum);
struct VAO* create3DTexturedObject (GLenum, int, const GLfloat*, const GLfloat*, GLuint, GLenum);
void draw3DObject (struct VAO*);
void draw3DTexturedObject (struct VAO*);
GLuint createTexture (const char*);

extern GLuint programID;