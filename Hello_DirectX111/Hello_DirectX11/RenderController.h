#ifndef RENDERCONTROLLER_DEF
#define RENDERCONTROLLER_DEF
#include "DXUtil.h"
#include "Entity.h"

class RenderController{
public:
	RenderController();//Contructor

	//Getters
	std::vector<Entity> getEntities();
	std::vector<VERTEX> getVertices();
	int getSize();
	int getCount();

	//Setters
	boolean setEntities(std::vector<Entity> sEntities);
	boolean setVertices(std::vector<VERTEX> sVertices);
	boolean add(Entity sEntity);
	boolean remove(Entity sEntity);

private:
	std::vector<Entity> entities;
	std::vector<VERTEX> vertices;
};
#endif