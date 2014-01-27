#include "RenderController.h"

//Contructors
RenderController::RenderController(){

}

RenderController::RenderController(ID3D11Device * sDevice, ID3D11DeviceContext * sContext, D3D11_PRIMITIVE_TOPOLOGY sPrimitive){
	RenderController::device = sDevice;
	RenderController::context = sContext;
	RenderController::primitive = sPrimitive;

	RenderController::stride = sizeof(VERTEX);//Size of VERTEX
	RenderController::offset = 0;//Offset in which we start reading VERTEX bytes
}


//Getters
std::vector<Entity> RenderController::getEntities(){
	return RenderController::entities;
}

std::vector<VERTEX> RenderController::getVertices(){
	std::vector<VERTEX> newVertices;
	for (UINT i = 0; i < RenderController::entities.size(); i++){
		std::vector<VERTEX> tempVertices = RenderController::entities.at(i).getVertices();
		newVertices.insert(newVertices.end(), tempVertices.begin(), tempVertices.end());
	}
	
	RenderController::vertices = newVertices;

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
	sEntity.setID(RenderController::entities.size() + 1);
	RenderController::getVertices();
	return true;
}

boolean RenderController::remove(Entity sEntity){
	std::vector<Entity> newEntities;
	for (UINT i = 0; i < RenderController::entities.size(); i++){
		if (RenderController::entities.at(i).getID() == sEntity.getID()){
			sEntity.setID(-1);
		}
		else{
			newEntities.push_back(RenderController::entities.at(i));
		}
	}
	RenderController::entities = newEntities;
	return true;
}


//Actions
boolean RenderController::render(){

	//Vertex buffer description
	ZeroMemory(&(RenderController::bd), sizeof(RenderController::bd));//Reserve memory for Vertex buffer description
	bd.Usage = D3D11_USAGE_DYNAMIC;//Write access, access by CPU and GPU
	bd.ByteWidth = sizeof(VERTEX)* RenderController::getCount();//Size of vertex struct * 3(x3 b/c x,y,z)
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;//Use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//Allow CPU to write buffer

	RenderController::device->CreateBuffer(&(RenderController::bd), NULL, &(RenderController::pVBuffer));//Create vertex buffer

	//Actual rendering

	RenderController::context->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &(RenderController::ms));//Map the buffer, pVBuffer is the buffer and ms is where we will put the buffer
	memcpy(RenderController::ms.pData, &(RenderController::getVertices()[0]), RenderController::getSize());//Copy data to mapped buffer
	RenderController::context->Unmap(pVBuffer, NULL);//Unmap buffer, allowing GPU to use buffer

	RenderController::context->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);//Tells GPU which vertices to read
	RenderController::context->IASetPrimitiveTopology(RenderController::primitive);//Tells the GPU what type of geomitry to render(Points, Line segments, line, triangle, triangle strip).
	RenderController::context->Draw(RenderController::getCount(), 0);//Draw 3 vertices  and start at vertice 0

	RenderController::pVBuffer->Release();//Ensure that there arn't more than one vertex buffers being built up per tick
	return true;
}