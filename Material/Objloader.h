#pragma once

#include<cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "imageloader.h"

using namespace std;

struct Coord3d{
	float x,y,z;
	Coord3d(float x_, float y_, float z_)
	{
		x=x_;
		y=y_;
		z=z_;
	}
};

struct Face{
	int facenum;
	bool quad; // topologia eh Quad ou Triângulo?
	int vertices[4];
	int texcoord[4];
	int mat;
	Face(int num, int f1, int f2, int f3, int t1, int t2, int t3, int mat_);
	Face(int num, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int mat_);
};

struct Material{
 string name;
 float alpha, ns, ni;
 float dif[3], amb[3], spec[3];
 int illum;// nao usaremos. Apenas carregaremos.
 int texture;
 Material(string na,float a_,float n,float ni2,float* d,float* a,float* s,int i,int t);
 };

struct TexCoord{
    float u,v;
    TexCoord(float a, float b);
};



class objloader{

    vector<string> linhas;//linhas do arquivo
	vector<Coord3d> vertice;
	vector<Coord3d> normal;
	vector<Face> faces;
	vector<Material> materials;
	vector<unsigned int> texture;
	vector<TexCoord> textureCoordinate;
	vector<unsigned int> lists;
	bool ismaterial, isnormals, istexture;


	unsigned int loadtexture(const char* filename);
	int getMaterialIndex(string s);
	void loadMaterials(string s);// vai preencher a lista materials . S=nome do arquivo .mtl
	string getName(string s);
    float getFloat(string s);
	int loadTexture(string s);
	void clean();
/*********************************************************/
    Coord3d getVertex(string s);
    Coord3d getNormal(string s);
    Face getFace_type1(string s, bool isQuad);
    Face getFace_type2(string s, bool isQuad,int myMaterial);
    Face getFace_type3(string s, bool isQuad,int myMaterial);
    int carregaObjeto(const char* nomeArq);
    int loadTexture(Image* image);


public:
    objloader();
    ~objloader();
    int load(const char* filename);
    int carrega(const char* nomeArq);

};



