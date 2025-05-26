#pragma once
#include "CObj.h"
class CScreen : public CObj
{
public:
	CScreen();
	~CScreen();
public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vScale;
	D3DXVECTOR3 LT;
	D3DXVECTOR3 RT;
	D3DXVECTOR3 RB;
	D3DXVECTOR3 LB;

};

