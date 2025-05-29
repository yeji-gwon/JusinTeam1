#pragma once
#include "CObj.h"

template <typename T>
struct Poly
{
	T	WPoly;
	T	LPoly;
	D3DXMATRIX	matWorld;
};

class CHead : public CObj
{
public:
	CHead();
	virtual ~CHead();

public:
	void		Initialize() override;
	int			Update()override;
	void		Late_Update()override;
	void		Render(HDC hDC)override;
	void		Release()override;

private:
	Poly<tagPolygon>	Head;
	Poly<D3DXVECTOR3>	Eyes[2];
	Poly<D3DXVECTOR3>	Mouth[3];
};

