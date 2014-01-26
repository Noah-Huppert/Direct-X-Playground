#include "DXApp.h"

class HelloDX11 : public DXApp{//Create new app object
public://Define all functions
	HelloDX11(HINSTANCE hInstance);//Contructor, input is handle to activity
	~HelloDX11();//Destructor

	bool Init() override;//Defines init function
	void Update(float dt) override;//Defines Update function, input is delta time, time used for animations and physics
	void Render(float dt) override;//Defines Render function, input is delta time, time used for animations and physics

private:
	RenderController rController;
	Entity tEntity;
};

HelloDX11::HelloDX11(HINSTANCE hInstance) : DXApp(hInstance){//Custom contructor
	rController = RenderController();
	tEntity = Entity({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f);

	rController.add(tEntity);
}

HelloDX11::~HelloDX11(){//Custom destructor

}

bool HelloDX11::Init(){//Custom init function
	if (!DXApp::Init()){//If init fails exit program
		return false;
	}

	return true;
}

void HelloDX11::Update(float dt){//Custom update function
	//Nothing here yet, game logic would go here
}

void HelloDX11::Render(float dt){//Custom render function
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);//Clear background to blue

	//Actual rendering
	stride = sizeof(VERTEX);//Size of VERTEX
	offset = 0;//Offset in which we start reading VERTEX bytes


	m_pImmediateContext->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);//Map the buffer, pVBuffer is the buffer and ms is where we will put the buffer
	memcpy(ms.pData, &(rController.getVertices()[0]), rController.getSize());//Copy data to mapped buffer
	m_pImmediateContext->Unmap(pVBuffer, NULL);//Unmap buffer, allowing GPU to use buffer

	m_pImmediateContext->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);//Tells GPU which vertices to read
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//Tells the GPU what type of geomitry to render(Points, Line segments, line, triangle, triangle strip).
	m_pImmediateContext->Draw(rController.getCount(), 0);//Draw 3 vertices  and start at vertice 0
	

	HR(m_pSwapChain->Present(0, 0));//Display background(From buffer)
}

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd){//Aplication entry point
	HelloDX11 tApp(hInstance);//Defines testapp

	if (!tApp.Init()){//If init fails exit app
		return 1;
	}
	
	return tApp.Run();//Else run main loop
}