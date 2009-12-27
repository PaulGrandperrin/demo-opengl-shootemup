#include "graphicEngine.h"


#include <IL/il.h>
#include <GL/glew.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <algorithm>

#define BUFFER_OFFSET(a) ((char*)NULL + (a)) //HACK un gros cast de ouf dingue très pratique

//Quelques définitions de structures
struct v 		//vecteur position 3D
{
    float x,y,z;
};
struct vn		//vecteur normal 3D
{
    float x,y,z;
};
struct vt		//vecteur coordonnée de texture 2D
{
    float x,y;
};
struct vertex		//vertex=identifiant(vecteur position+vecteur normal+vecteur coordonnée de texture)
{
    unsigned int vId,vnId,vtId;
};
struct vertexf		//je sais plus TODO
{
    int vertexId;
    v vV;
    vn vVn;
    vt vVt;
};

struct vertexFinal	//la non plus TODO
{
    v vV;
    vn vVn;
    vt vVt;
};

bool vertexEgal ( const vertexf & a,const vertexFinal & b )
{
    return
        a.vV.x==b.vV.x && a.vV.y==b.vV.y && a.vV.z==b.vV.z &&
        a.vVn.x==b.vVn.x && a.vVn.y==b.vVn.y && a.vVn.z==b.vVn.z &&
        a.vVt.x==b.vVt.x && a.vVt.y==b.vVt.y;
}

bool vertexfLess ( const vertexf &a, const vertexf &b ) //c'est jolie hein, ca fait une sorte de tour de Pise
{
    if ( a.vV.x<b.vV.x )
        return true;
    else if ( a.vV.x>b.vV.x )
        return false;
    else
        if ( a.vV.y<b.vV.y )
            return true;
        else if ( a.vV.y>b.vV.y )
            return false;
        else
            if ( a.vV.z<b.vV.z )
                return true;
            else if ( a.vV.z>b.vV.z )
                return false;
            else
                if ( a.vVn.x<b.vVn.x )
                    return true;
                else if ( a.vVn.x>b.vVn.x )
                    return false;
                else
                    if ( a.vVn.y<b.vVn.y )
                        return true;
                    else if ( a.vVn.y>b.vVn.y )
                        return false;
                    else
                        if ( a.vVn.z<b.vVn.z )
                            return true;
                        else if ( a.vVn.z>b.vVn.z )
                            return false;
                        else
                            if ( a.vVt.x<b.vVt.x )
                                return true;
                            else if ( a.vVt.x>b.vVt.x )
                                return false;
                            else
                                if ( a.vVt.y<b.vVt.y )
                                    return true;
                                else
                                    return false;
}


graphicEngine::graphicEngine()
{  
}

graphicEngine::~graphicEngine()
{
      //TODO
}

void graphicEngine::init()
{
  glewInit(); 	//chargement des adresses des pointeurs de fonction des extentions d'openGL
  ilInit();  	//initialisation de devIL
  
  glClearColor ( 1,1,1,0 );
  glEnable (GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  cout << "openGL initialized"<<endl;
}

void graphicEngine::resize(int width,int height)
{
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45,width/(float)height,0.1,100); 
  this->width=width;
  this->height=height;
}

void graphicEngine::render(vector<instance> instances,camera cam,float time)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.eyex,cam.eyey,cam.eyez,cam.centerx,cam.centery,cam.centerz,cam.upx,cam.upy,cam.upz);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	/* activation des tableaux de sommets */
        glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
  
	for(unsigned int i=0; i<models.size();i++)
	{	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, models[i].ibo);
		glBindBuffer(GL_ARRAY_BUFFER, models[i].vbo);
		glBindTexture(GL_TEXTURE_2D, models[i].texture);
		glVertexPointer(3, GL_FLOAT, sizeof(float)*8, BUFFER_OFFSET(0));
		glNormalPointer( GL_FLOAT, sizeof(float)*8, (char*) NULL+sizeof(float)*3);
		glTexCoordPointer(2, GL_FLOAT, sizeof(float)*8, (char*) NULL+sizeof(float)*6);
	
		
		for(unsigned int j=0;j<instances.size();j++)
		{
			if(instances[j].idModel==i+1) //TODO optimiser ça
			{
				glPushMatrix();
				glTranslatef(instances[j].x,instances[j].y,instances[j].z);
				glRotatef(instances[j].ax,1,0,0); //TODO à optimiser
				glRotatef(instances[j].ay,0,1,0);
				glRotatef(instances[j].az,0,0,1);
				glScalef(instances[j].sx,instances[j].sy,instances[j].sz);
				
				glDrawElements(GL_TRIANGLES, models[i].sizeofIbo, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
				glPopMatrix();
			}
		}
	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
    
}


int graphicEngine::loadModel(string pathModel,string pathTexture)
{
    cout << "> Loading "<< pathModel<<" ..." << flush;
    
    //on déclare les vecteurs contenant les données brutes contenus dans le fichier
    vector<v> vVect; //le vecteur contenant les donnees brutes de positions
    vector<vn> vnVect;//le vecteur contenant les donnees brutes de normales
    vector<vt> vtVect;//le vecteur contenant les donnees brutes de etxtures
    vector<vertex> fVect; //le vecteur contenant les donnees brutes des faces

    ifstream OBJFile ( pathModel.c_str(),ios::in ); //on ouvre le fichier en lecture seule
    if ( !OBJFile )
        return 0;

    string buffer,key;
    while ( getline ( OBJFile,buffer ) ) //tant qu'on peut lire une ligne
    {
        istringstream line ( buffer );
        key="";
        line >> key;

        if ( key=="v" )
        {
            v vTemp;
            line >> vTemp.x >> vTemp.y >> vTemp.z;
            vVect.push_back ( vTemp );
        }
        else if ( key=="vn" )
        {
            vn vnTemp;
            line >> vnTemp.x >> vnTemp.y >> vnTemp.z;
            vnVect.push_back ( vnTemp );
        }
        else if ( key=="vt" )
        {
            vt vtTemp;
            line >> vtTemp.x >> vtTemp.y;
            vtVect.push_back ( vtTemp );
        }
        else if ( key=="g" )
        {
            //TODO a implémenter ou pas
        }
        else if ( key=="f" )
        {
            vertex fTemp;
            string vertex;
            int lim;

            for ( int i=0;i<3;i++ )
            {
                line >> vertex;


                lim=vertex.find_first_of ( '/' );
                fTemp.vId=atoi ( vertex.substr ( 0,lim ).c_str() );
                vertex=vertex.substr ( lim+1,vertex.length()-lim-1 );

                lim=vertex.find_first_of ( '/' );
                if ( lim!=0 )
                {
                    fTemp.vtId=atoi ( vertex.substr ( 0,lim ).c_str() );
                }
                else
                {
                    fTemp.vtId=0;
                }
                vertex=vertex.substr ( lim+1,vertex.length()-lim-1 );

                lim=vertex.find_first_of ( '/' );
                if ( lim!=0 )
                {
                    fTemp.vnId=atoi ( vertex.substr ( 0,lim ).c_str() );
                }
                else
                {
                    fTemp.vnId=0;
                }
                vertex=vertex.substr ( lim+1,vertex.length()-lim-1 );

                fVect.push_back ( fTemp );
            }

        }
        //sinon on ignore la ligne
    }
    OBJFile.close();
    //On a fini de charger les données du fichier
    //Maintenant, faut organiser les données de maniere optimale pour les utiliser avec des VBO et IBO.

    //On va d'abors construire tout les vertex possibles
    vector<vertexf> allVertex;
    for ( unsigned int i=0;i<fVect.size();i++ )
    {
        vertexf vertexfTemp;
        vertexfTemp.vertexId=i;
        vertexfTemp.vV=vVect[fVect[i].vId-1];
        vertexfTemp.vVn=vnVect[fVect[i].vnId-1];

        if ( fVect[i].vtId != 0 )
            vertexfTemp.vVt=vtVect[fVect[i].vtId-1];
        else
        {
            vertexfTemp.vVt.x=0;
            vertexfTemp.vVt.y=0;
        }

        allVertex.push_back ( vertexfTemp );
    }

    //On va trier ce vecteur pour virer les doublons

    sort ( allVertex.begin(),allVertex.end(),vertexfLess );

    //On peut dore et deja cree le vecteur d'ibo final pour opengl

    unsigned int *arrayIbo= ( unsigned int* ) malloc ( fVect.size() *sizeof ( unsigned int ) );

    //On creer le vecteur des vertex finaux sans doublons

    vector<vertexFinal> vectFinal;
    vertexFinal finalTemp;

    finalTemp.vV=allVertex[0].vV;
    finalTemp.vVn=allVertex[0].vVn;
    finalTemp.vVt=allVertex[0].vVt;

    vectFinal.push_back ( finalTemp );

    arrayIbo[allVertex[0].vertexId]=0;

    for ( unsigned int i=1; i< allVertex.size();i++ )
    {
        if ( !vertexEgal ( allVertex[i],finalTemp ) )
        {
            finalTemp.vV=allVertex[i].vV;
            finalTemp.vVn=allVertex[i].vVn;
            finalTemp.vVt=allVertex[i].vVt;
            vectFinal.push_back ( finalTemp );
        }
        arrayIbo[allVertex[i].vertexId]=vectFinal.size()-1;
    }

    //maintenant, on peut remplir le vbo

    float* arrayVertex= ( float* ) malloc ( allVertex.size() * ( 3+3+2 ) *sizeof ( float ) );

    //NOTE on rempli le vbo avec des données alignés sur 32bits(8octets) pour optimiser les accès mémoire du GPU
    for ( unsigned int i=0;i<vectFinal.size();i++ )
    {
        arrayVertex[i*8]=vectFinal[i].vV.x;
        arrayVertex[i*8+1]=vectFinal[i].vV.y;
        arrayVertex[i*8+2]=vectFinal[i].vV.z;
        arrayVertex[i*8+3]=vectFinal[i].vVn.x;
        arrayVertex[i*8+4]=vectFinal[i].vVn.y;
        arrayVertex[i*8+5]=vectFinal[i].vVn.z;
        arrayVertex[i*8+6]=vectFinal[i].vVt.x;
        arrayVertex[i*8+7]=vectFinal[i].vVt.y;
    }

    //Et on bind
    GLuint vbo;
    
    glGenBuffers ( 1, &vbo );

    glBindBuffer ( GL_ARRAY_BUFFER, vbo );

    glBufferData ( GL_ARRAY_BUFFER,
                   allVertex.size() * ( 3+3+2 ) *sizeof ( float ),
                   NULL,
                   GL_STATIC_DRAW );                           // TODO à remplacer en STREAM lorque les models seront annimés

    glBufferSubData ( GL_ARRAY_BUFFER,
                      0,
                      allVertex.size() * ( 3+3+2 ) *sizeof ( float ),
                      arrayVertex );


    glBindBuffer ( GL_ARRAY_BUFFER, 0 );
    
    //Puis l'ibo
    GLuint ibo;
    glGenBuffers ( 1,&ibo );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER,ibo );
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER,fVect.size() *sizeof ( unsigned int ),NULL,GL_STATIC_DRAW );
    glBufferSubData ( GL_ELEMENT_ARRAY_BUFFER,0,fVect.size() *sizeof ( unsigned int ),arrayIbo );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER,0 );


    //On enregistre les données
    model m;
    m.ibo=ibo;
    m.vbo=vbo;
    m.sizeofVbo=allVertex.size();
    m.sizeofIbo=fVect.size();
    
    free ( arrayIbo );
    free ( arrayVertex );
    
    cout << " OK\t\t"<<m.sizeofVbo << " vertex / "<< m.sizeofIbo/3<< " triangles"<<endl;
    
    
    m.texture= ( GLuint ) loadTexture ( ( char* ) pathTexture.c_str() ); //TODO trouver le chemin automatiquement
    
    models.push_back(m);
    
    return models.size();
}

void graphicEngine::unLoadModel(int id)
{
      //TODO à implémenter
}

int graphicEngine::loadTexture ( char* imagePath )
{
    cout << "> Loading "<<imagePath<<" ..."<<flush;
    //Chargement de la texture
    ILuint ilTextId;
    GLuint glTextId;

    ilGenImages ( 1,&ilTextId );
    ilBindImage ( ilTextId );
    if ( !ilLoadImage ( imagePath ) )
        exit ( 007 ); //FIXME utiliser exceptions
    if ( !ilConvertImage ( IL_RGBA,IL_UNSIGNED_BYTE ) )
        exit ( 007 );//FIXME utiliser exceptions

    glGenTextures ( 1,&glTextId );
    glBindTexture ( GL_TEXTURE_2D,glTextId );

    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexImage2D (
        GL_TEXTURE_2D,
        0,
        ilGetInteger ( IL_IMAGE_BPP ),
        ilGetInteger ( IL_IMAGE_WIDTH ),
        ilGetInteger ( IL_IMAGE_HEIGHT ),
        0,
        ilGetInteger ( IL_IMAGE_FORMAT ),
        GL_UNSIGNED_BYTE,
        ilGetData()
    );

    
    cout << " OK\t\t" <<ilGetInteger ( IL_IMAGE_WIDTH )<<"x"<<ilGetInteger ( IL_IMAGE_HEIGHT )<<" pixels"<<endl;
    ilDeleteImages ( 1, &ilTextId );
    return glTextId;
}


  /*
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	
	GLfloat ambientLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 1, 1, 1, 1.0f };
	GLfloat position[] = { 10.0f, -10.0f, 0.0f, 1.0f };
	
	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	float mcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
	glFrontFace(GL_CCW);
	
	*/