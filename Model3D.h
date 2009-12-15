#include <string>
#include <GL/glew.h>

using namespace std;

class Model3D
{
  public:
    Model3D();
    Model3D(string path);
    bool load(string path);
    void render();
    
  private:
    int loadTexture ( char* imagePath );
    
    GLuint ibo,vbo,texture;
    int sizeofIbo,sizeofVbo;
};