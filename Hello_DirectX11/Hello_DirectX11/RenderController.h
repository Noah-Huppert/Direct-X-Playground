#ifndef RENDERCONTROLLER_DEF
#define RENDERCONTROLLER_DEF
#include "DXUtil.h"
#include "Entity.h"

class RenderController{
public:
	RenderController();//Def constructor
	RenderController(ID3D11Device * sDevice, ID3D11DeviceContext * context, D3D11_PRIMITIVE_TOPOLOGY sPrimitive, float sAspectRatio);//Contructor

	//Getters
	std::vector<Entity*> getEntities();
	std::vector<VERTEX> getVertices();
	VECTOR3 getPosition();
	int getSize();
	int getCount();

	//Setters
	boolean setEntities(std::vector<Entity*> sEntities);
	boolean setVertices(std::vector<VERTEX> sVertices);
	boolean setPosition(float sX, float sY, float sZ);
	boolean add(Entity * sEntity);
	boolean remove(Entity * sEntity);

	//Actions
	boolean render();

private:
	std::vector<Entity*> entities;
	std::vector<VERTEX> vertices;
	VECTOR3 position;
	float aspectRatio;
	ID3D11Device * device;
	ID3D11DeviceContext * context;
	D3D11_PRIMITIVE_TOPOLOGY primitive;

	D3D11_BUFFER_DESC bd;//Vertex buffer description
	ID3D11Buffer *pVBuffer;//Vertex buffer for copying over to graphics card
	D3D11_MAPPED_SUBRESOURCE ms;//Mapped resource

	UINT stride;//Size of VERTEX struct
	UINT offset;//Sets the number of bytes into a VERTEX to start rendering
};
#endif