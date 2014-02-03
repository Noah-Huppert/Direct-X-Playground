#include "Entity.h"


//Contructors
Entity::Entity(){

}

Entity::Entity(float sX, float sY, float sZ, float sR, float sWidth, float sHeight){//Simple contructor
	Entity::position = { sX, sY, sZ };
	Entity::rotation = sR;
	Entity::width = sWidth;
	Entity::height = sHeight;
	Entity::calcVertices();


	float tempCenterX = 0;
	float tempCenterY = 0;

	for (UINT i = 0; i < Entity::vertices.size(); i++){
		tempCenterX += Entity::vertices.at(i).X;
		tempCenterY += Entity::vertices.at(i).Y;
	}

	tempCenterX = tempCenterX / Entity::vertices.size();
	tempCenterY = tempCenterY / Entity::vertices.size();

	Entity::centerPoint = { tempCenterX, tempCenterY, 0.0f };
}

Entity::Entity(float sX, float sY, float sZ, float sR, std::vector<VERTEX> sVertices){//Complex contructor
	Entity::position = { sX, sY, sZ };
	Entity::rotation = sR;
	Entity::vertices = sVertices;

	float tempCenterX = 0;
	float tempCenterY = 0;

	for (UINT i = 0; i < Entity::vertices.size(); i++){
		tempCenterX += Entity::vertices.at(i).X;
		tempCenterY += Entity::vertices.at(i).Y;
	}

	tempCenterX = tempCenterX / Entity::vertices.size();
	tempCenterY = tempCenterY / Entity::vertices.size();

	Entity::centerPoint = { tempCenterX, tempCenterY, 0.0f };
}


//Getters
VECTOR3 Entity::getPosition(){
	return Entity::position;
}

float Entity::getRotation(){
	return Entity::rotation;
}

std::vector<VERTEX> Entity::getVertices(){
	//Transformation
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

	//Rotation
	std::vector<VERTEX> rotationResults;
	for (int x = 0; x < transformResults.size(); x++){
		float dRotation = Entity::rotation * (M_PI / 180);//Turns into radiens
		VERTEX tempVertex = {
			cos(dRotation) * (transformResults.at(x).X - Entity::centerPoint.X) - sin(dRotation) * (transformResults.at(x).Y - Entity::centerPoint.Y) + Entity::centerPoint.X,
			sin(dRotation) * (transformResults.at(x).X - Entity::centerPoint.X) + cos(dRotation) * (transformResults.at(x).Y - Entity::centerPoint.Y) + Entity::centerPoint.Y,
			transformResults.at(x).Z,
			{
				Entity::vertices.at(x).COLOR[0],
				Entity::vertices.at(x).COLOR[1],
				Entity::vertices.at(x).COLOR[2],
				Entity::vertices.at(x).COLOR[3],
			}
		};
		rotationResults.push_back(tempVertex);
	}
	return rotationResults;
}

int Entity::getVerticesSize(){
	return  Entity::vertices.size()*sizeof(VERTEX);
}

int Entity::getVerticesCount(){
	return Entity::vertices.size();
}

float Entity::getWidth(){
	return Entity::width;
}

float Entity::getHeight(){
	return Entity::height;
}

float Entity::getPosX(){
	return Entity::position.X;
}

float Entity::getPosY(){
	return Entity::position.Y;
}

float Entity::getPosZ(){
	return Entity::position.Z;
}

float Entity::getVecX(int vIndex){
	return Entity::vertices.at(vIndex).X;
}

float Entity::getVecY(int vIndex){
	return Entity::vertices.at(vIndex).Y;
}

float Entity::getVecZ(int vIndex){
	return Entity::vertices.at(vIndex).Z;
}

float* Entity::getVecColor(int vIndex){
	return Entity::vertices.at(vIndex).COLOR;
}

VECTOR3 Entity::getCenterPoint(){
	return Entity::centerPoint;
}


//Setters
boolean Entity::setPosition(float sX, float sY, float sZ){
	Entity::position = { sX, sY, sZ };
	return true;
}

boolean Entity::setRotation(float sR){
	Entity::rotation = sR;
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

boolean Entity::setWidth(float sWidth){
	Entity::width = sWidth;
	Entity::vertices.clear();
	Entity::calcVertices();
	return true;
}

boolean Entity::setHeight(float sHeight){
	Entity::height = sHeight;
	Entity::vertices.clear();
	Entity::calcVertices();
	return true;
}

boolean Entity::setPosX(float sX){
	Entity::position.X = sX;
	return true;
}

boolean Entity::setPosY(float sY){
	Entity::position.Y = sY;
	return true;
}

boolean Entity::setPosZ(float sZ){
	Entity::position.Z = sZ;
	return true;
}

boolean Entity::setVecX(float sX, int vIndex){
	Entity::vertices.at(vIndex).X = sX;
	return true;
}

boolean Entity::setVecY(float sY, int vIndex){
	Entity::vertices.at(vIndex).Y = sY;
	return true;
}

boolean Entity::setVecZ(float sZ, int vIndex){
	Entity::vertices.at(vIndex).Z = sZ;
	return true;
}

boolean Entity::setVecColor(float sColor[4], int vIndex){
	Entity::vertices.at(vIndex).COLOR[1] = sColor[1];
	Entity::vertices.at(vIndex).COLOR[2] = sColor[2];
	Entity::vertices.at(vIndex).COLOR[3] = sColor[3];
	Entity::vertices.at(vIndex).COLOR[4] = sColor[4];
	return true;
}

boolean Entity::setCenterPoint(float sX, float sY, float sZ){
	Entity::centerPoint = { sX, sY, sZ };
	return true;
}



//Actions
boolean Entity::calcVertices(){
	Entity::vertices = {
		{ Entity::width - (Entity::width * 1.5f), Entity::height / 2, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ Entity::width / 2, Entity::height / 2, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ Entity::width / 2, Entity::height - (Entity::height * 1.5f), 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ Entity::width / 2, Entity::height - (Entity::height * 1.5f), 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ Entity::width - (Entity::width * 1.5f), Entity::height - (Entity::height * 1.5f), 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ Entity::width - (Entity::width * 1.5f), Entity::height / 2, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } }
	};
	return true;
}