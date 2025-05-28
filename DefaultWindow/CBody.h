#pragma once
#include "CObj.h"
#include "CHead.h"
//template <typename T>
//struct Poly
//{
//	T	WPoly;
//	T	LPoly;
//	D3DXMATRIX	matWorld;
//};

class CBody : public CObj
{
public:
	CBody();
	virtual ~CBody();

public:
	void		Initialize() override;
	int			Update()override;
	void		Late_Update()override;
	void		Render(HDC hDC)override;
	void		Release()override;

private:
	void		Key_Input();

private:
	Poly<tagPolygon> Body;
	Poly<D3DXVECTOR3> Arm[2];
	Poly<D3DXVECTOR3> Leg[2];

	Poly<tagPolygon> WhiteFlag;
	Poly<tagPolygon> BlueFlag;

	float			m_fLAngle;
	float			m_fRAngle;
};

