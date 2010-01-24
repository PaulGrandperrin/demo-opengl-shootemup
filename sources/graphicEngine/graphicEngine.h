
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
-éclairage blinn phong ( presque fini)
-lampe , lumiere parallele , (spot)
-texture alpha (baleze)
-afficher du texte a l'ecran

-normal map
-effet motion-blur
-effet glow ( lueur diffuse)
-models annimés par keyframe
-effet HDR (dur)
-coronas ( point très lumineux)
-shadow volumes ( monster dur)
*/

#include <vector>
#include <string>

using namespace std;

#include "../utilities.h"


class graphicEngine
{
  public:
    graphicEngine();
    ~graphicEngine();
//     void init();
    
    void resize(int width,int height);
    
    //renvoie 0 si echec sinon renvoie l'id du model
    unsigned int loadModel(string pathModel,string pathTexture);
    void unLoadModel(unsigned int id);
    
    void render(vector<instance> instances, camera cam,lightVec lv, float time);
    
  private:
	void loadMeshe (unsigned int id,const char* path);
    void loadTexture ( unsigned int id,const char* path );
	void loadShaders( unsigned int id,const char* vsPath, const char* psPath);
    
    struct model
    {
      unsigned int ibo,vbo,texture,shaders;
      int sizeofIbo,sizeofVbo;
    };
    vector<model> models;
    
    int width,height;
};