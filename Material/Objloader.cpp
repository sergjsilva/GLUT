#include "objloader.h"
#include<GL/freeglut.h>

Face::Face(int num, int f1, int f2, int f3, int t1, int t2, int t3, int mat_)
{
    facenum=num;
    vertices[0]=f1;
    vertices[1]=f2;
    vertices[2]=f3;
    texcoord[0]=t1;
    texcoord[1]=t2;
    texcoord[2]=t3;
    texcoord[3]=0;
    mat=mat_;
    quad=false;// é um triângulo
}
//Face::Face(int num, int f1, int f2, int f3, int f4)
Face::Face(int num, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int mat_)
{
    facenum=num;
    vertices[0]=f1;
    vertices[1]=f2;
    vertices[2]=f3;
    vertices[3]=f4;
    texcoord[0]=t1;
    texcoord[1]=t2;
    texcoord[2]=t3;
    texcoord[3]=t4;
    mat=mat_;
    quad=true;// é um quadrado
}

Material::Material(string na,float a_,float n,float ni2,float* d,float* a,float* s,int i,int t)
{
    name=na;
    alpha=a_;
    ni=ni2;
    ns=n;
    dif[0]=d[0];
    dif[1]=d[1];
    dif[2]=d[2];

    amb[0]=a[0];
    amb[1]=a[1];
    amb[2]=a[2];

    spec[0]=s[0];
    spec[1]=s[1];
    spec[2]=s[2];

    illum=i;
    texture=t;
}

TexCoord::TexCoord(float a, float b)
{
    u=a;
    v=b;
}


objloader::objloader()
{

}

objloader::~objloader()
{

}

void objloader::clean()
{
    linhas.clear();
    vertice.clear();
	normal.clear();
	faces.clear();
	materials.clear();
	textureCoordinate.clear();
	lists.clear();

}


string objloader::getName(string s)
{
    stringstream saved;
	saved<<s;
	string aux, myName;
    saved>>aux>>myName;
    return myName;
}

int objloader::getMaterialIndex(string s)
{
    int index;
    string materialName;
    materialName=getName(s);
    for(unsigned int i=0;i<materials.size();i++)
    {
        if(materialName.compare(materials[i].name)==0)
        {
            //currentMat=i;
            index=i;
            break;
        }

    }
	return index;
}




Coord3d objloader::getVertex(string s)
{
	stringstream saved;
	saved<<s;
	char c;
	float x,y,z;
	saved>>c>>x>>y>>z;
	Coord3d tmp=Coord3d(x,y,z);
	return tmp;
}

Coord3d objloader::getNormal(string s)
{
	stringstream saved;
	saved<<s;
	string c;
	float x,y,z;
	saved>>c>>x>>y>>z;
	Coord3d tmp=Coord3d(x,y,z);
	return tmp;
}


float objloader::getFloat(string s)
{
    stringstream saved;
	saved<<s;
	string c;
	float x;
	saved>>c>>x;

	return x;
}

Face objloader::getFace_type1(string s, bool isQuad)
{
	int a,b,c,d;
	int n;

	if(isQuad)
	{
		Face f=Face(0,0,0,0,0,0,0,0,0,0);//f.quad será true
		sscanf(s.c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&n,&b,&n,&c,&n,&d,&n);
		f.facenum=n;
		f.vertices[0]=a;
		f.vertices[1]=b;
		f.vertices[2]=c;
		f.vertices[3]=d;
		return f;
	}
	else
	{
		Face f=Face(0,0,0,0,0,0,0,0);// f.quad sera false
		sscanf(s.c_str(),"f %d//%d %d//%d %d//%d",&a,&n,&b,&n,&c,&n);
		//f.quad=false;
		f.facenum=n;
		f.vertices[0]=a;
		f.vertices[1]=b;
		f.vertices[2]=c;
		return f;
	}


}

Face objloader::getFace_type2(string s, bool isQuad, int myMaterial)
{
	int a,b,c,d;
	//int n;
    int vnorm;
    int vtex[4];
	if(isQuad)
	{
		Face f=Face(-1,0,0,0,0,0,0,0,0,myMaterial);
		// Apenas preciso do Vertice/TexCoord não preciso do 3º componente que é a normal do vértice
		sscanf(s.c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",&a,&vtex[0],&vnorm,
                                                                &b,&vtex[1],&vnorm,
                                                                &c,&vtex[2],&vnorm,
                                                                &d,&vtex[3],&vnorm);
		//f.quad=true;
		f.vertices[0]=a;
		f.vertices[1]=b;
		f.vertices[2]=c;
		f.vertices[3]=d;
		f.texcoord[0]=vtex[0];
		f.texcoord[1]=vtex[1];
		f.texcoord[2]=vtex[2];
		f.texcoord[3]=vtex[3];

		return f;
	}
	else
	{
		Face f=Face(-1,0,0,0,0,0,0,myMaterial);
		sscanf(s.c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",&a,&vtex[0],&vnorm,
                                                        &b,&vtex[1],&vnorm,
                                                        &c,&vtex[2],&vnorm);
		//f.quad=false;
        f.vertices[0]=a;
		f.vertices[1]=b;
		f.vertices[2]=c;
		f.texcoord[0]=vtex[0];
		f.texcoord[1]=vtex[1];
		f.texcoord[2]=vtex[2];

		return f;
	}


}

Face objloader::getFace_type3(string s, bool isQuad, int myMaterial)
{
	int a,b,c,d;

    if(isQuad)
	{
		Face f=Face(-1,0,0,0,0,0,0,0,0,myMaterial);
		// Apenas preciso do Vertice/TexCoord não preciso do 3º componente que é a normal do vértice
		sscanf(s.c_str(),"f %d %d %d %d",&a,&b,&c,&d);

		//f.quad=true;
		f.vertices[0]=a;
		f.vertices[1]=b;
		f.vertices[2]=c;
		f.vertices[3]=d;

		return f;
	}
	else
	{
		Face f=Face(-1,0,0,0,0,0,0,myMaterial);
		sscanf(s.c_str(),"f %d %d %d",&a,&b,&c);

		//f.quad=false;
		f.vertices[0]=a;
		f.vertices[1]=b;
		f.vertices[2]=c;

		return f;
	}
}




int objloader::carrega(const char* nomeArq)
{

	ifstream arq;

	int currentMaterial=0;

	arq.open(nomeArq);
	if(!arq.is_open())
		cout<<"Erro ao abrir o arquivo!"<<endl;


	while(arq.good())
	{
		string linha;
		getline(arq,linha);
		linhas.push_back(linha);
	}

	for(unsigned int i=0;i<linhas.size();i++)
	{
		if(linhas[i][0]=='#')
			continue;
		else if(linhas[i][0]=='v' && (linhas[i])[1]==' ')
		{
			vertice.push_back(getVertex(linhas[i]));
		}else if((linhas[i][0]=='v') && (linhas[i][1]=='n'))
		{
			normal.push_back(getNormal(linhas[i]));
		}else if(linhas[i][0]=='f')
		{
			//int a,b,c,d,e;
			if(count(linhas[i].begin(),linhas[i].end(),' ')==4)
			{
			    if(linhas[i].find("//")!=string::npos)//npos=not found
                {
                    faces.push_back(getFace_type1(linhas[i],true));
                }else if(linhas[i].find("/")!=string::npos)
                {
                    faces.push_back(getFace_type2(linhas[i],true, currentMaterial));
                }else
                {
                    faces.push_back(getFace_type3(linhas[i],true, currentMaterial));
                }


			}else
			{
				if(linhas[i].find("//")!=string::npos)//npos=not found
                {
                    faces.push_back(getFace_type1(linhas[i],false));
                }else if(linhas[i].find("/")!=string::npos)
                {
                    faces.push_back(getFace_type2(linhas[i],false, currentMaterial));
                }else
                {
                    faces.push_back(getFace_type3(linhas[i],false, currentMaterial));
                }

			}
		}else if((linhas[i][0]=='u') && (linhas[i][1]=='s') && (linhas[i][2]=='e'))
		{
            currentMaterial=getMaterialIndex(linhas[i]);
		}else if((linhas[i][0]=='m') && (linhas[i][1]=='t') && (linhas[i][2]=='l'))
		{
            string nome;
            nome=getName(linhas[i]);
            loadMaterials(nome);
		}else if((linhas[i][0]=='v') && (linhas[i][1]=='t'))
		{
            float u,v;
            sscanf(linhas[i].c_str(),"vt %f %f",&u,&v);
            TexCoord m=TexCoord(u,1-v);
            textureCoordinate.push_back(m);
            istexture=true;
		}

	}

    if(materials.size()==0)
    {
        ismaterial=false;
    }
    else
    {
        ismaterial=true;
    }



	//Desenha
	int num;
	num=glGenLists(1);
	glNewList(num,GL_COMPILE);
    int last=-1;//guarda o indice do ultimo material utilizado
    for(unsigned int i=0;i<faces.size();i++)
    {
        if(last!=faces[i].mat && ismaterial)
        {
            float diffuse[]={materials[faces[i].mat].dif[0],materials[faces[i].mat].dif[1],materials[faces[i].mat].dif[2],1};
            float ambient[]={materials[faces[i].mat].amb[0],materials[faces[i].mat].amb[1],materials[faces[i].mat].amb[2],1};
            float specular[]={materials[faces[i].mat].spec[0],materials[faces[i].mat].spec[1],materials[faces[i].mat].spec[2],1};
            glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
            glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
            glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
            glMaterialf(GL_FRONT,GL_SHININESS,materials[faces[i].mat].ns);
            last=faces[i].mat;
            if(materials[faces[i].mat].texture==-1)// não há textura
                glDisable(GL_TEXTURE_2D);
            else
            {
                glEnable(GL_TEXTURE);
                glBindTexture(GL_TEXTURE_2D,materials[faces[i].mat].texture);
            }
        }
        if(faces[i].quad)
        {
            glBegin(GL_QUADS);
            glNormal3f(normal[faces[i].facenum-1].x,normal[faces[i].facenum-1].y,normal[faces[i].facenum-1].z);
            glVertex3f(vertice[faces[i].vertices[0]-1].x,vertice[faces[i].vertices[0]-1].y,vertice[faces[i].vertices[0]-1].z);
            glVertex3f(vertice[faces[i].vertices[1]-1].x,vertice[faces[i].vertices[1]-1].y,vertice[faces[i].vertices[1]-1].z);
            glVertex3f(vertice[faces[i].vertices[2]-1].x,vertice[faces[i].vertices[2]-1].y,vertice[faces[i].vertices[2]-1].z);
            glVertex3f(vertice[faces[i].vertices[3]-1].x,vertice[faces[i].vertices[3]-1].y,vertice[faces[i].vertices[3]-1].z);
            glEnd();
        }else{
            glBegin(GL_TRIANGLES);
            glNormal3f(normal[faces[i].facenum-1].x,normal[faces[i].facenum-1].y,normal[faces[i].facenum-1].z);
            glVertex3f(vertice[faces[i].vertices[0]-1].x,vertice[faces[i].vertices[0]-1].y,vertice[faces[i].vertices[0]-1].z);
            glVertex3f(vertice[faces[i].vertices[1]-1].x,vertice[faces[i].vertices[1]-1].y,vertice[faces[i].vertices[1]-1].z);
            glVertex3f(vertice[faces[i].vertices[2]-1].x,vertice[faces[i].vertices[2]-1].y,vertice[faces[i].vertices[2]-1].z);

            glEnd();
        }
    }
	glEndList();
    lists.push_back(num);
	// Apagar o vetor
	clean();
	return num;
}


void objloader::loadMaterials(string s)
{
    ifstream arq;
    string myfile="C:\\Users\\Sergio\\Documents\\DLL\\CODEBLOCK\\GLUT\\Material\\"+s;

	arq.open(myfile.c_str());
	if(!arq.is_open())
	{
		cout<<"Erro ao abrir o arquivo!"<<endl;
        clean();
	}

    ismaterial=true;
    vector<string> fileLines;
    while(arq.good())
	{
		string linha;
		getline(arq,linha);
		fileLines.push_back(linha);
	}

     string matName="";
     string matFileName="";
     float matAlpha, matNs, matNi;
     float matDif[3], matAmb[3], matSpec[3];
     int matIllum;// nao usaremos. Apenas carregaremos.
     int matTexture;
     bool hasMaterial=false;

    for(unsigned int i=0;i<fileLines.size();i++)
    {
        if(fileLines[i][0]=='#')
            continue;
        if((fileLines[i][0]=='n')&&(fileLines[i][1]=='e')&&(fileLines[i][2]=='w'))
        {
            if(hasMaterial)
            {
                if(matFileName.compare("")!=0)
                {
                    Material m=Material(matName,matAlpha,matNs,matNi,matDif,matAmb,matSpec,matIllum,matTexture);
                    materials.push_back(m);
                    matFileName="";
                }else
                {
                    Material m=Material(matName,matAlpha,matNs,matNi,matDif,matAmb,matSpec,matIllum,-1);
                    materials.push_back(m);
                }
            }
            hasMaterial=false;
            matName=getName(fileLines[i]);
        }else if((fileLines[i][0]=='d')&&(fileLines[i][1]==' '))
             {
                 hasMaterial=true; // sim tenho algo
                 sscanf(fileLines[i].c_str(),"d %f",&matAlpha);
                 //matAlpha=getFloat(fileLines[i]);
             }
        else if((fileLines[i][0]=='i')&&(fileLines[i][1]=='l'))
             {
                 hasMaterial=true; // sim tenho algo
                 sscanf(fileLines[i].c_str(),"illum %d",&matIllum);
                 //matAlpha=getFloat(fileLines[i]);
             }
        else if((fileLines[i][0]=='N')&&(fileLines[i][1]=='s'))
             {
                 hasMaterial=true; // sim tenho algo
                 matNs=getFloat(fileLines[i]);
             }
        else if((fileLines[i][0]=='N')&&(fileLines[i][1]=='i'))
             {
                 hasMaterial=true; // sim tenho algo
                 matNi=getFloat(fileLines[i]);
             }
         else if((fileLines[i][0]=='K')&&(fileLines[i][1]=='a'))
            {
                hasMaterial=true; // sim tenho algo
                sscanf(fileLines[i].c_str(),"Ka %f %f %f",&matAmb[0],&matAmb[1],&matAmb[2]);
            }
          else if((fileLines[i][0]=='K')&&(fileLines[i][1]=='d'))
            {
                hasMaterial=true; // sim tenho algo
                sscanf(fileLines[i].c_str(),"Kd %f %f %f",&matDif[0],&matDif[1],&matDif[2]);
            }
        else if((fileLines[i][0]=='K')&&(fileLines[i][1]=='s'))
            {
                hasMaterial=true; // sim tenho algo
                sscanf(fileLines[i].c_str(),"Ks %f %f %f",&matSpec[0],&matSpec[1],&matSpec[2]);
            }
        else if((fileLines[i][0]=='m')&&(fileLines[i][1]=='a'))
            {
                hasMaterial=true; // sim tenho algo
                matFileName=getName(fileLines[i]);
                matTexture=loadTexture(matFileName);
            }

        }//for Loop
        if(hasMaterial)// se tiver material
        {
            if(matFileName.compare("")!=0)
            {
                Material m=Material(matName,matAlpha,matNs,matNi,matDif,matAmb,matSpec,matIllum,matTexture);
                materials.push_back(m);
            }else
                {
                    Material m=Material(matName,matAlpha,matNs,matNi,matDif,matAmb,matSpec,matIllum,-1);
                    materials.push_back(m);
                }
        }

    }//end function


int objloader::loadTexture(string s){
	unsigned int id;
	Image* image = loadBMP(s.c_str());
	glGenTextures(1, &id); //Quero  gerar 1 textura e armazenarei na variável id
	glBindTexture(GL_TEXTURE_2D, id); //
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 level of texture
				 GL_RGB,                       //Format to store
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because we choose stor in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.push_back(id);
    delete image;
	return id; //Returns the id of the texture
}





