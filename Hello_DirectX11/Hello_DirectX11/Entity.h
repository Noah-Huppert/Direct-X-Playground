#ifndef ENTITY_DEF
#define ENTITY_DEF
#include "DXUtil.h"

class DXUtil;
#include "DXUtil.h"

class Entity{
public:
	Entity();//Def contructor
	Entity(VECTOR3 sPosition, float sWidth, float sHeight);//Simple square contructor
	Entity(VECTOR3 sPosition, std::vector<VERTEX> sVertices);//Complex constructor

	//Getters
	VECTOR3 getPosition();
	std::vector<VERTEX> getVertices();
	int getVerticesSize();
	int getVerticesCount();

	//Setters
	virtual boolean setPosition(VECTOR3 sPosition);
	virtual boolean setVertices(std::vector<VERTEX> sVertices);\
	virtual boolean setVertex(VERTEX sVertex, int sIndex);


private:
	VECTOR3 position;
	std::vector<VERTEX> vertices;
};
#endif