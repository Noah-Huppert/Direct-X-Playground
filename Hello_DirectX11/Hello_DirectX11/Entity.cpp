#include "DXApp.h";

class Entity{
public:
	Entity(VECTOR3 sPosition, VERTEX sVertices[] = NULL){
		Entity::position = sPosition;
		if (!sVertices){
			VERTEX vertices[] = { sPosition };
		}
		else{
			
		}
	};

	//Getters
	VECTOR3 getPosition(){
		return Entity::position;
	};

	//Setters
	void setPosition(VECTOR3 newPosition){
		Entity::position = newPosition;
	};

protected:
	VECTOR3 position;//Entity location

	/*
	Entity::vertices[] = {
		{ -0.5f, 0.5f, 0.0f, { 0.0f, 0.0f, 0.0f, 0.0f } },
		{ 0.5f, 0.5f, 0.0f, { 0.0f, 0.0f, 0.0f, 0.0f } },
		{ 0.5f, -0.5f, 0.0f, { 0.0f, 0.0f, 0.0f, 0.0f } },
		{ 0.5f, -0.5f, 0.0f, { 0.0f, 0.0f, 0.0f, 0.0f } },
		{ -0.5f, -0.5f, 0.0f, { 0.0f, 0.0f, 0.0f, 0.0f } },
		{ -0.5f, 0.5f, 0.0f, { 0.0f, 0.0f, 0.0f, 0.0f } }
	};
	*/
};