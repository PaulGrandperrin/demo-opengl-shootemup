
/* NOTE
Format des fichiers .obg
Le moteur étant basique, il faut exporter les models en suivant quelques
règles précises.
Sous blender 2.49:
-Context: As you want
-Output Options: Pas Apply Modifiers, Rotate X90, Copy Images
-Export: Pas Edges, Triangulate, Materials, UVs, Normals, pas HQ, Pas Polygroups, Pas nurbs
-Blender Object as OBJ: Pas Objects, Pas Groups, Pas Material groups, Keep Vertex Order

Les .mtl sont pas encore gérés donc pas de propriétés d'eclairage phong.

A peu près tout les formats de texture sont supportés: jpg, png, bnp.
Le cannal alpha est pas encore supporté.
Le sens de la texture n'est pas le même que celui de Blender, il faut donc faire un flip verticale.
*/

/* TODO
-éclairage blinn phong
-lampe , lumiere parallele , (spot)
-normal map
-models annimés par keyframe
-afficher du texte a l'ecran
-effet motion-blur
-effet glow ( lueur diffuse)
-effet HDR (dur)
-coronas ( point très lumineux)
-shadow volumes ( monster dur)
*/

#include <vector>
#include <string>

using namespace std;

#include "instance.h"

struct camera
{
  float eyex,eyey,eyez;
  float centerx,centery,centerz;
  float upx,upy,upz;
};

class graphicEngine
{
  public:
    graphicEngine();
    ~graphicEngine();
    void init();
    
    void resize(int width,int height);
    
    //renvoie 0 si echec sinon renvoie l'id du model
    int loadModel(string pathModel,string pathTexture);
    void unLoadModel(int id);
    
    void render(vector<instance> instances, camera cam,float time);
    
  private:
    int loadTexture ( char* path );
    
    struct model
    {
      unsigned int ibo,vbo,texture;
      int sizeofIbo,sizeofVbo;
    };
    vector<model> models;
    
    int width,height;
};