#include "RenderController.h"

//Contructor
RenderController::RenderController(){

}


//Getters
std::vector<Entity> RenderController::getEntities(){
	return RenderController::entities;
}

std::vector<VERTEX> RenderController::getVertices(){
	RenderController::vertices.clear();
	for (UINT i = 0; i < RenderController::entities.size(); i++){
		std::vector<VERTEX> tempVertices = RenderController::entities.at(i).getVertices();
		RenderController::vertices.insert(RenderController::vertices.end(), tempVertices.begin(), tempVertices.end());
	}
	return RenderController::vertices;
}

int RenderController::getSize(){
	return RenderController::vertices.size()*sizeof(VERTEX);
}

int RenderController::getCount(){
	return RenderController::vertices.size();
}

//Setters
boolean RenderController::setEntities(std::vector<Entity> sEntities){
	RenderController::entities = sEntities;
	return true;
}

boolean RenderController::setVertices(std::vector<VERTEX> sVertices){
	RenderController::vertices = sVertices;
	return true;
}

boolean RenderController::add(Entity sEntity){
	RenderController::entities.push_back(sEntity);
	return true;
}

boolean RenderController::remove(Entity sEntity){
	std::vector<Entity> newEntities;
	for (UINT i = 0; i < RenderController::entities.size(); i++){
		if (&RenderController::entities.at(i) == &sEntity){
			//Do nothing
		}
		else{
			newEntities.push_back(RenderController::entities.at(i));
		}
	}
	RenderController::entities = newEntities;
	return true;
}