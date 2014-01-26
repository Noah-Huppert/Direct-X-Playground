#include "Entity.h"


//Contructors
Entity::Entity(){

}

Entity::Entity(VECTOR3 sPosition, float sWidth, float sHeight){//Simple contructor
	Entity::position = sPosition;
	Entity::vertices = {
		{ sHeight - (sHeight * 1.5f), sWidth / 2, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ sHeight / 2, sWidth / 2, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ sHeight / 2, sWidth - (sWidth * 1.5f), 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ sHeight / 2, sWidth - (sWidth * 1.5f), 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ sHeight - (sHeight * 1.5f), sWidth - (sWidth * 1.5f), 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ sHeight - (sHeight * 1.5f), sWidth / 2, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } }
	};
}

Entity::Entity(VECTOR3 sPosition, std::vector<VERTEX> sVertices){//Complex contructor
	Entity::position = sPosition;
	Entity::vertices = sVertices;
}


//Getters
VECTOR3 Entity::getPosition(){
	return Entity::position;
}

std::vector<VERTEX> Entity::getVertices(){
	std::vector<VERTEX> transformResults;
	for (int i = 0; i < Entity::vertices.size(); i++){
		VERTEX tempVertex = {
			Entity::vertices.at(i).X + Entity::position.X,
			Entity::vertices.at(i).Y + Entity::position.Y,
			Entity::vertices.at(i).Z + Entity::position.Z,
			{
				Entity::vertices.at(i).COLOR[0],
				Entity::vertices.at(i).COLOR[1],
				Entity::vertices.at(i).COLOR[2],
				Entity::vertices.at(i).COLOR[3],
			}
		};
		transformResults.push_back(tempVertex);
	}
	return transformResults;
}

int Entity::getVerticesSize(){
	return  Entity::vertices.size()*sizeof(VERTEX);
}

int Entity::getVerticesCount(){
	return Entity::vertices.size();
}


//Setters
boolean Entity::setPosition(VECTOR3 sPosition){
	Entity::position = sPosition;
	return true;
}

boolean Entity::setVertices(std::vector<VERTEX> sVertices){
	Entity::vertices = sVertices;
	return true;
}

boolean Entity::setVertex(VERTEX sVertex, int sIndex){
	Entity::vertices.at(sIndex) = sVertex;
	return true;
}