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
	Entity t2Entity;
	Entity t3Entity;
};

HelloDX11::HelloDX11(HINSTANCE hInstance) : DXApp(hInstance){//Custom contructor

}

HelloDX11::~HelloDX11(){//Custom destructor

}

bool HelloDX11::Init(){//Custom init function
	if (!DXApp::Init()){//If init fails exit program
		return false;
	}

	rController = RenderController(m_pDevice, m_pImmediateContext, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	tEntity = Entity({ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f);
	t2Entity = Entity({ 0.5f, 0.5f, 0.0f }, 0.5f, 0.5f);
	t3Entity = Entity({ -0.5f, -0.5f, 0.0f }, 0.5f, 0.5f);

	rController.add(tEntity);
	rController.add(t2Entity);
	rController.add(t3Entity);

	return true;
}

void HelloDX11::Update(float dt){//Custom update function
	tEntity.setPosition({ 1.0f, 1.0f, 0.0f });//Not working
}

void HelloDX11::Render(float dt){//Custom render function
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);//Clear background to blue

	rController.render();

	HR(m_pSwapChain->Present(0, 0));//Display background(From buffer)
}

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd){//Aplication entry point
	HelloDX11 tApp(hInstance);//Defines testapp

	if (!tApp.Init()){//If init fails exit app
		return 1;
	}
	
	return tApp.Run();//Else run main loop
}