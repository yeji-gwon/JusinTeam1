#pragma once

#define WINCX		800
#define WINCY		600

#define PI			3.141592f

#define PURE		= 0

extern HWND g_hWnd;

enum SCENEID { SC_MENU, SC_STAGE1, SC_STAGE2, SC_STAGE3, SC_STAGE4, SC_END };

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

typedef struct tagInfo
{
	D3DXVECTOR3			vPos;	
	
	D3DXVECTOR3			vDir;		
	D3DXVECTOR3			vLook;

	D3DXVECTOR3			vNormal;	
	D3DXMATRIX			matWorld;
}INFO;

static D3DXVECTOR3		Get_Mouse()
{
	POINT pt{ };
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
}