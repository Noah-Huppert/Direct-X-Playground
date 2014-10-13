#include "Camera.h"

Camera::Camera(){

}


//Getters
std::vector<RenderController*> Camera::getRenderControllers(){
	return Camera::renderControllers;
}

VECTOR3 Camera::getPosition(){
	return Camera::position;
}

float Camera::getPosX(){
	return Camera::position.X;
}

float Camera::getPosY(){
	return Camera::position.Y;
}

float Camera::getPosZ(){
	return Camera::position.Z;
}


//Setters
boolean Camera::setRenderControllers(std::vector<RenderController*> sRenderController){
	Camera::renderControllers = sRenderController;
	return true;
}

boolean Camera::setPosition(float sX, float sY, float sZ){
	Camera::position = { sX, sY, sZ };
	for (UINT i = 0; i < Camera::renderControllers.size(); i++){
		Camera::renderControllers.at(i)->setPosition(Camera::position.X, Camera::position.Y, Camera::position.Z);
	}
	return true;
}

boolean Camera::setPosX(float sX){
	Camera::position.X = sX;
	for (UINT i = 0; i < Camera::renderControllers.size(); i++){
		Camera::renderControllers.at(i)->setPosition(Camera::position.X, Camera::position.Y, Camera::position.Z);
	}
	return true;
}

boolean Camera::setPosY(float sY){
	Camera::position.Y = sY;
	for (UINT i = 0; i < Camera::renderControllers.size(); i++){
		Camera::renderControllers.at(i)->setPosition(Camera::position.X, Camera::position.Y, Camera::position.Z);
	}
	return true;
}

boolean Camera::setPosZ(float sZ){
	Camera::position.Z = sZ;
	for (UINT i = 0; i < Camera::renderControllers.size(); i++){
		Camera::renderControllers.at(i)->setPosition(Camera::position.X, Camera::position.Y, Camera::position.Z);
	}
	return true;
}

boolean Camera::add(RenderController * sRenderController){
	boolean inVector = false;
	for (UINT i = 0; i < Camera::renderControllers.size(); i++){
		if (Camera::renderControllers.at(i) == sRenderController){
			inVector = true;
		}
	}
	
	if (inVector == false){
		Camera::renderControllers.push_back(sRenderController);
	}
	return true;
}

boolean Camera::remove(RenderController * sRenderController){
	std::vector<RenderController*> newRenderControllers;
	for (UINT i = 0; i < Camera::renderControllers.size(); i++){
		if (Camera::renderControllers.at(i) == sRenderController){

		}
		else{
			newRenderControllers.push_back(Camera::renderControllers.at(i));
		}
	}
	Camera::renderControllers = newRenderControllers;
	return true;
}


//Actions
boolean Camera::render(){
	for (UINT i = 0; i < Camera::renderControllers.size(); i++){
		RenderController * tempRenderController = Camera::renderControllers.at(i);
		tempRenderController->render();
	}
	return true;
}