#ifndef CAMERA_DEF
#define CAMERA_DEF
#include "DXUtil.h"
#include "RenderController.h"

class Camera{
public:
	Camera();
	
	//Getters
	std::vector<RenderController*> getRenderControllers();
	VECTOR3 getPosition();
	float getPosX();
	float getPosY();
	float getPosZ();


	//Setters
	boolean setRenderControllers(std::vector<RenderController*> sRenderControllers);
	boolean setPosition(float sX, float sY, float sZ);
	boolean setPosX(float sX);
	boolean setPosY(float sY);
	boolean setPosZ(float sZ);
	boolean add(RenderController * sRenderController);
	boolean remove(RenderController * sRenderController);


	//Actions
	boolean render();

private:
	std::vector<RenderController*> renderControllers;
	VECTOR3 position;
};
#endif