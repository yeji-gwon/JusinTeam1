#pragma once
#include "CObj.h"
#include "CHead.h"
#include "CGameSystem4.h"

class CBody : public CObj
{
public:
	CBody();
	virtual ~CBody();

public:
	BTYPE Get_BType() { return m_ePlayerBType; }
	WTYPE Get_WType() { return m_ePlayerWType; }
	void Init_Angle();

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
	Poly<D3DXVECTOR3> Hand[2];
	Poly<D3DXVECTOR3> Leg[2];

	D3DMATRIX		LArmMatWorld;
	D3DMATRIX		RArmMatWorld;
	D3DMATRIX		BodyMatWorld;

	Poly<tagPolygon> WhiteFlag;
	Poly<tagPolygon> BlueFlag;

	float			m_fLAngle;
	float			m_fRAngle;

	BTYPE			m_ePlayerBType;
	WTYPE			m_ePlayerWType;
};

