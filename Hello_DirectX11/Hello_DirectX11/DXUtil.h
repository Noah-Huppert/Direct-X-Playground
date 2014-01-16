#pragma once
#include <d3d11.h>
#include <DirectXColors.h>
#include "DXERR\dxerr.h"

#pragma comment(lib, "d3d11.lib")


#ifdef _DEBUG
#ifndef HR
#define HR(x){ \
	HRESULT hr = x; \
	if (FAILED(hr)){ \
		DXTraceW(__FILEW__, __LINE__, hr, L#x, TRUE); \
	} \
}
#endif
#ifndef HR
#define HR(x) x;
#endif
#endif

namespace Memory{
	template <class T> void SafeDelete(T& t){//Safely delete vars, avoid trying to delete something that doesnt exist
		if (t){
			delete t;
			t = nullptr;
		}
	}

	template <class T> void SafeDeleteArr(T& t){//Safely delete vars, avoid trying to delete something that doesnt exist
		if (t){
			delete[] t;
			t = nullptr;
		}
	}

	template <class T> void SafeRelease(T& t){//Safely release vars, avoid trying to release something that doesnt exist
		if (t){
			t->Release();
			t = nullptr;
		}
	}
}