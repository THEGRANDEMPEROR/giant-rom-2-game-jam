/*===========================
=Graphics.h/.cpp			=
=by Tyler van Gastel		=
=latest update 11/23/2015	=
=Direct X frame work		=
=============================*/

#pragma once

#pragma comment(lib, "winmm.lib")

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "ResourceDefines.h"
#include "RenVector.h"
#define MAX_LIGHTS 20
class Graphics {
private:
	//window stuff
	HWND m_hWnd;
	HINSTANCE m_hInts;

	//DX stuff
	IDirect3D9* m_pD3DObject;
	IDirect3DDevice9* m_pD3DDevice;
	D3DCAPS9 m_D3DCaps;
	
	//font handler
	ID3DXFont* m_pD3DFont;
	//2D object handler
	ID3DXSprite* m_pD3DSprite;
	//lines
	LPD3DXLINE m_pD3DLine;

	D3DLIGHT9 _lights[MAX_LIGHTS];

	//
	int _width;
	int _height;
	float _aspectRatio;

	int _fontH;
	int _fontW;
	//
	bool _vSync;
	bool _fullScreen;
	bool _lost;

	RenVector ren;

	camera cam;
public:
	Graphics();
	~Graphics();
	void init(HWND hWnd,HINSTANCE hInst, bool bWindowed);
	bool restart(HWND hWnd,HINSTANCE hInst);
	void shutdown();
	void setLight(int num,D3DLIGHT9& light,bool active);
	D3DLIGHT9* getLight(int num);
	void render();
	void addRender(renInfo& info);
	bool isLost();
	int getHeight() {return _height;}
	int getWidth() {return _width;}
	void setResolution(int height, int width);
	void setTextSize(int height, int width);
	void loadImage(LPCSTR FileName,UINT Width,UINT Height,UINT MipLevels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,DWORD Filter,DWORD MipFilter,D3DCOLOR ColorKey,D3DXIMAGE_INFO *SrcInfo,PALETTEENTRY *pPalette,LPDIRECT3DTEXTURE9 *Tex);
	void loadImage(LPCSTR FileName,imageAsset* asset);
	void loadXModel(LPCSTR FileName, modelAsset* asset);
	void createCube(LPCSTR FileName, cubeAsset* asset);
	void createCube(cubeAsset* asset, float top, float bottom, float front, float back, float left, float right);
	void updateCam(const camera* a_cam);
};