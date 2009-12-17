#include "Model3D.h"

#include <iostream>
#include <IL/il.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <QtGui>
#include <math.h>
#include <algorithm>

#define BUFFER_OFFSET(a) ((char*)NULL + (a))

//Quelques définitions de structures
struct v
{
    float x,y,z;
};
struct vn
{
    float x,y,z;
};
struct vt
{
    float x,y;
};
struct vertex
{
    unsigned int vId,vnId,vtId;
};
struct vertexf
{
    int vertexId;
    v vV;
    vn vVn;
    vt vVt;
};

struct vertexFinal
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


Model3D::Model3D()
{  
  glewInit();
}

Model3D::Model3D(string path)
{
    Model3D();
    load(path);

}

bool Model3D::load(string path)
{
  cout << path << endl;
  glewInit();
    vector<v> vVect; //le vecteur contenant les donnees brutes de positions
    vector<vn> vnVect;//le vecteur contenant les donnees brutes de normales
    vector<vt> vtVect;//le vecteur contenant les donnees brutes de etxtures
    vector<vertex> fVect; //le vecteur contenant les donnees brutes des faces

    ifstream OBJFile ( path.c_str(),ios::in ); //on ouvre le fichier en lecture
    if ( !OBJFile )
        return false;

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
            //a implémenter
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
    }
    OBJFile.close();
    
    //On a fini de charger les donn�es du fichier
    //Maintenant, faut organiser les donn�es de maniere optimale pour les utiliser avec des VBO et IBO.

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

    //maintenant, on peut remplir les vbo

    float* arrayVertex= ( float* ) malloc ( allVertex.size() * ( 3+3+2 ) *sizeof ( float ) );


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


    glGenBuffers ( 1, &vbo );

    glBindBuffer ( GL_ARRAY_BUFFER, vbo );

    
    glBufferData ( GL_ARRAY_BUFFER,
                   allVertex.size() * ( 3+3+2 ) *sizeof ( float ),
                   NULL,
                   GL_STATIC_DRAW );                           // à remplacer en STREAM

    glBufferSubData ( GL_ARRAY_BUFFER,
                      0,
                      allVertex.size() * ( 3+3+2 ) *sizeof ( float ),
                      arrayVertex );


    glBindBuffer ( GL_ARRAY_BUFFER, 0 );
    
    //Puis l'ibo


    glGenBuffers ( 1,&ibo );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER,ibo );
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER,fVect.size() *sizeof ( unsigned int ),NULL,GL_STATIC_DRAW );
    glBufferSubData ( GL_ELEMENT_ARRAY_BUFFER,0,fVect.size() *sizeof ( unsigned int ),arrayIbo );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER,0 );


    //On enregistre qlq données
    sizeofVbo=allVertex.size();
    sizeofIbo=fVect.size();
    texture= ( GLuint ) loadTexture ( ( char* ) "textures/demon.png" );

    cout << "Nb Vertex: " << allVertex.size() << endl;
    cout << "Nb Triangles: " << fVect.size() /3 << endl;
    
    
    free ( arrayIbo );
    free ( arrayVertex );

    return true;
}


void Model3D::render()
{
	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	     

	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexPointer(3, GL_FLOAT, sizeof(float)*8, BUFFER_OFFSET(0));
	glNormalPointer( GL_FLOAT, sizeof(float)*8, (char*) NULL+sizeof(float)*3);
        glTexCoordPointer(2, GL_FLOAT, sizeof(float)*8, (char*) NULL+sizeof(float)*6);
          
        /* activation des tableaux de sommets */
        glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
       
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, sizeofIbo, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        /* desactivation des tableaux de sommet */
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
    
        
    //glFlush();
  
  
  
}


int Model3D::loadTexture ( char* imagePath )
{
  ilInit();
    //Chargement de la texture
    ILuint ilTextId;
    GLuint glTextId;

    ilGenImages ( 1,&ilTextId );
    ilBindImage ( ilTextId );
    if ( !ilLoadImage ( imagePath ) )
        exit ( 11 );
    if ( !ilConvertImage ( IL_RGBA,IL_UNSIGNED_BYTE ) )
        exit ( 11 );

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

    ilDeleteImages ( 1, &ilTextId );


    return glTextId;
}
