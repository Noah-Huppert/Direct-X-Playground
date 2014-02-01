#ifndef ENTITY_DEF
#define ENTITY_DEF
#include "DXUtil.h"

class DXUtil;
#include "DXUtil.h"

class Entity{
public:
	Entity();//Def contructor
	Entity(float sX, float sY, float sZ, float sWidth, float sHeight);//Simple square contructor
	Entity(float sX, float sY, float sZ, std::vector<VERTEX> sVertices);//Complex constructor

	//Getters
	VECTOR3 getPosition();
	std::vector<VERTEX> getVertices();
	int getVerticesSize();
	int getVerticesCount();
	float getWidth();
	float getHeight();
	float getPosX();
	float getPosY();
	float getPosZ();
	float getVecX(int vIndex);
	float getVecY(int vIndex);
	float getVecZ(int vIndex);
	float* getVecColor(int vIndex);

	//Setters
	virtual boolean setPosition(VECTOR3 sPosition);
	virtual boolean setVertices(std::vector<VERTEX> sVertices);\
	virtual boolean setVertex(VERTEX sVertex, int sIndex);
	boolean setWidth(float sWidth);
	boolean setHeight(float sHeight);
	boolean setPosX(float sX);
	boolean setPosY(float sY);
	boolean setPosZ(float sZ);
	boolean setVecX(float sX, int vIndex);
	boolean setVecY(float sY, int vIndex);
	boolean setVecZ(float sZ, int vIndex);
	boolean setVecColor(float sColor[4], int vIndex);


private:
	VECTOR3 position;
	std::vector<VERTEX> vertices;
	float width;
	float height;
};
#endif