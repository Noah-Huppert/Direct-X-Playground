#include "DXApp.h"

class TestApp : public DXApp{//Create new app object
public://Define all functions
	TestApp(HINSTANCE hInstance);//Contructor, input is handle to activity
	~TestApp();//Destructor

	bool Init() override;//Defines init function
	void Update(float dt) override;//Defines Update function, input is delta time, time used for animations and physics
	void Render(float dt) override;//Defines Render function, input is delta time, time used for animations and physics
};

TestApp::TestApp(HINSTANCE hInstance) : DXApp(hInstance){//Custom contructor
	
}

TestApp::~TestApp(){//Custom destructor

}

bool TestApp::Init(){//Custom init function
	if (!DXApp::Init()){//If init fails exit program
		return false;
	}

	return true;
}

void TestApp::Update(float dt){//Custom update function
	//Nothing here yet, game logic would go here
}

void TestApp::Render(float dt){//Custom render function
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);//Clear background to blue

	HR(m_pSwapChain->Present(0, 0));//Display background(From buffer)
}

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd){//Aplication entry point
	TestApp tApp(hInstance);//Defines testapp

	if (!tApp.Init()){//If init fails exit app
		return 1;
	}
	return tApp.Run();//Else run main loop
}