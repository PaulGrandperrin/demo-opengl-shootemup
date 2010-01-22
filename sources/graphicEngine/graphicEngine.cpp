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
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_EQUAL,255);
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

void graphicEngine::render(vector<instance> instances,camera cam,lightVec lv,float /*time*/) //TODO bien tt desactiver
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.eyex,cam.eyey,cam.eyez,cam.centerx,cam.centery,cam.centerz,cam.upx,cam.upy,cam.upz);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	/* activation des tableaux de sommets */
    glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// gestion de la lumière
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat position[] = { lv.x, lv.y, lv.z, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	float Al[4] = {lv.al.r, lv.al.g, lv.al.b, lv.al.a };
	glLightfv( GL_LIGHT0, GL_AMBIENT, Al );

	float Dl[4] = {lv.dl.r,lv.dl.g,lv.dl.b,lv.dl.a };
	glLightfv( GL_LIGHT0, GL_DIFFUSE, Dl );

	float Sl[4] = {lv.sl.r,lv.sl.g,lv.sl.b,lv.sl.a };
	glLightfv( GL_LIGHT0, GL_SPECULAR, Sl );
	
  
	for(unsigned int i=0; i<models.size();i++)
	{	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, models[i].ibo);
		glBindBuffer(GL_ARRAY_BUFFER, models[i].vbo);
		glBindTexture(GL_TEXTURE_2D, models[i].texture);
		glVertexPointer(3, GL_FLOAT, sizeof(float)*8, BUFFER_OFFSET(0));
		glNormalPointer( GL_FLOAT, sizeof(float)*8, (char*) NULL+sizeof(float)*3);
		glTexCoordPointer(2, GL_FLOAT, sizeof(float)*8, (char*) NULL+sizeof(float)*6);

		glUseProgram(models[i].shaders);
		
		for(unsigned int j=0;j<instances.size();j++)
		{
			if((unsigned int)instances[j].idModel==i+1) //TODO optimiser ça
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

	glDisable(GL_LIGHT0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
    
}


unsigned int graphicEngine::loadModel(string pathModel,string pathTexture)
{
	model m={0,0,0,0,0,0};
	unsigned int id=models.size();
	models.push_back(m);

	loadMeshe(id,pathModel.c_str());
	loadTexture(id,pathTexture.c_str());
	loadShaders(id,"shaders/vs.glsl","shaders/ps.glsl");
	return id+1;
}

void graphicEngine::unLoadModel(unsigned int/* id*/)
{
      //TODO à implémenter
}

void graphicEngine::loadMeshe (unsigned int id,const char* path)
{
    cout << "> Loading "<< path<<" ..." << flush;
    
    //on déclare les vecteurs contenant les données brutes contenus dans le fichier
    vector<v> vVect; //le vecteur contenant les donnees brutes de positions
    vector<vn> vnVect;//le vecteur contenant les donnees brutes de normales
    vector<vt> vtVect;//le vecteur contenant les donnees brutes de etxtures
    vector<vertex> fVect; //le vecteur contenant les donnees brutes des faces

    ifstream OBJFile ( path,ios::in ); //on ouvre le fichier en lecture seule
    if ( !OBJFile )
        exit(0);

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
    models[id].ibo=ibo;
    models[id].vbo=vbo;
    models[id].sizeofVbo=allVertex.size();
    models[id].sizeofIbo=fVect.size();
    
    free ( arrayIbo );
    free ( arrayVertex );
    
    cout << " OK\t\t"<<models[id].sizeofVbo << " vertex / "<< models[id].sizeofIbo/3<< " triangles"<<endl; //FIXME calcul faux
}

void graphicEngine::loadTexture ( unsigned int id,const char* path )
{
    cout << "> Loading "<<path<<" ..."<<flush;
    //Chargement de la texture
    ILuint ilTextId;
    GLuint glTextId;

    ilGenImages ( 1,&ilTextId );
    ilBindImage ( ilTextId );
    if ( !ilLoadImage ( path ) )
        exit ( 0 ); //FIXME utiliser exceptions
    if ( !ilConvertImage ( IL_RGBA,IL_UNSIGNED_BYTE ) )
        exit ( 0 );//FIXME utiliser exceptions

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

	models[id].texture= glTextId;
}

GLuint LoadShader ( GLenum type, const char *filename );

void graphicEngine::loadShaders(unsigned int id,const char* vsPath,const char* psPath)
{
	cout << "> Loading "<<vsPath<<" && " << psPath << " ..."<<flush;
	
	GLuint prog = 0;
    GLuint vs = 0, ps = 0;
    GLint link_status = GL_TRUE;
    GLint logsize = 0;
    char *log = NULL;


	vs = LoadShader ( GL_VERTEX_SHADER, vsPath );
	if ( vs == 0 )
		exit(0);

	ps = LoadShader ( GL_FRAGMENT_SHADER, psPath );
	if ( ps == 0 )
	{
		if ( glIsShader ( vs ) )
			glDeleteShader ( vs );
		exit(0);
	}

    /* creation du program */
    prog = glCreateProgram();

    /* on envoie nos shaders a notre program */
    if ( vs )
        glAttachShader ( prog, vs );
    if ( ps )
        glAttachShader ( prog, ps );

    /* on lie le tout */
    glLinkProgram ( prog );

	
    /* on verifie que tout s'est bien passe */
    glGetProgramiv ( prog, GL_LINK_STATUS, &link_status );
    if ( link_status != GL_TRUE )
    {
        glGetProgramiv ( prog, GL_INFO_LOG_LENGTH, &logsize );
        log = ( char* ) malloc ( logsize + 1 );
		
        glGetProgramInfoLog ( prog, logsize, &logsize, log );

        cout << endl<< "Erreur lors du linkage:"<< endl << log << endl;

        free ( log );
        glDeleteProgram ( prog );
        glDeleteShader ( vs );
        glDeleteShader ( ps );

        exit(0);
    }

    /* les shaders sont dans le program maintenant, on en a plus besoin */
    glDeleteShader ( vs );
    glDeleteShader ( ps );

	models[id].shaders=( unsigned int ) prog;
	
    cout << " OK\t\t" <<endl;
}

GLuint LoadShader ( GLenum type, const char *filename )
{
	GLuint shader = 0;
    GLsizei logsize = 0;
    GLint compile_status = GL_TRUE;
    char *log = NULL;

    // creation d'un shader de sommet
    shader = glCreateShader ( type );

    // chargement du code source

	ifstream file(filename,ios::in);
	string src,line;
	while(getline(file,line))
	{
		src+="\n"+line;
	}
	file.close();

	const char* strchar=src.c_str();
    // assignation du code source 
    glShaderSource ( shader, 1, ( const GLchar** ) &(strchar), NULL );


    // compilation du shader
    glCompileShader ( shader );

    // verification du succes de la compilation
    glGetShaderiv ( shader, GL_COMPILE_STATUS, &compile_status );
    if ( compile_status != GL_TRUE )
    {
        // erreur a la compilation recuperation du log d'erreur

        // on recupere la taille du message d'erreur
        glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &logsize );

        // on alloue un esapce memoire dans lequel OpenGL ecrira le message
        log = ( char * ) malloc ( logsize + 1 );

        glGetShaderInfoLog ( shader, logsize, &logsize, log );
		cout << endl << "Compilation de " << filename << " impossible : " <<endl << log << endl;

        // ne pas oublier de liberer la memoire et notre shader
        free ( log );
        glDeleteShader ( shader );

        return 0;
    }

    return shader;

}