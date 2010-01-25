
/** NOTE
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
Le sens de la texture n'est pas le même que celui de Blender, il faut donc faire un flip horizontal.
*/

/** TODO
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

#include <pthread.h>

using namespace std;

#include "../utilities.h"

#define POSTFX_NOTHING 0
#define POSTFX_BLUR 1
#define POSTFX_WATER 2
#define POSTFX_FAKEHDR 4
#define POSTFX_BLACKWHITE 8
#define POSTFX_CELLSHADING 16

struct camera
{
	float eyex,eyey,eyez;
	float centerx,centery,centerz;
	float upx,upy,upz;
};

struct color
{
	float r,g,b,a;
};

struct lightVec
{
	float x,y,z;
	color al,dl,sl;
};

class graphicEngine
{
public:
	graphicEngine();
	~graphicEngine();
	void init();

	void resize(int width,int height);

	//renvoie 0 si echec sinon renvoie l'id du model
	unsigned int loadModel(string pathModel,string pathTexture);
	void unLoadModel(unsigned int id);

	void render(vector<instance> inst, camera cam,vector<instance> instMenu, camera camMenu,lightVec lv,int postFX, float time);
	/** NOTE
	* Le temp donné à render est le temp écoulé depuis le lancement du jeu,
	* pas le temp inter-frame.
	*/
private:
	void loadMeshe (unsigned int id,const char* path);
	void loadTexture ( unsigned int id,const char* path );
	void loadShaders(unsigned int *ids,const char* vsPath, const char* psPath);
	void draw(vector<instance> inst, camera cam,unsigned int shader,lightVec lv,float time);
	
	struct model
	{
	unsigned int ibo,vbo,texture,shaders;
	int sizeofIbo,sizeofVbo;
	};
	vector<model> models;

	unsigned int fbo,textFbo,rbo;
	int widthW,heightW,heightV, widthV;

	unsigned int sceneShader,postFXBlur,postFXWater,postFXFakeHDR, postFXBlackWhite,postFXCellShading, postFXNothing;

	unsigned int shadWaterParam;
	
	pthread_mutex_t mutex;
};
