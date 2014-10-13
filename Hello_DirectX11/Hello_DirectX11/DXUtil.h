#ifndef DXUTIL_DEF
#define DXUTIL_DEF
//Windows includes
#include <windows.h>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

//DirectX includes
#include <d3d.h>//Basic directX
#include <d3d9.h>
#include <d3d11.h>//Basic directX 3d
#include <DirectXColors.h>//Preset colors
#include <d3d9types.h>
#include <d3dcompiler.h>
#include "DXERR\dxerr.h"

//DirectX Libary
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

using namespace std;
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

//Data structs
struct VECTOR3
{
	float X;
	float Y;
	float Z;
};

struct VERTEX//Vertex struct
{
	float X;
	float Y;
	float Z;//Position
	float COLOR[4];//Color, replaces D3DXCOLOR which was just a float array with 4 entries

	VERTEX translate(VECTOR3 t){
		VERTEX v = { VERTEX::X + t.X, VERTEX::Y + t.Y, VERTEX::Z + t.Z, { VERTEX::COLOR[1], VERTEX::COLOR[2], VERTEX::COLOR[3], VERTEX::COLOR[4] } };
		return v;
	};
};

struct DEFAULT
{
	float X = 0;
	float Y = 0;
	float Z = 0;
};
#endif
