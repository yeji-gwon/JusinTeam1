#pragma once
#include "CObj.h"
class Obstacle2 : public CObj
{
public:
	Obstacle2(int);
	virtual ~Obstacle2();

	pair<float, float> Get_Pos() { return { m_tInfo.vPos.x, m_tInfo.vPos.y }; };
	void Set_Dead() { m_bDead = true; };

public:
	 void		Initialize()override;
	 int		Update()override;
	 void		Late_Update()override;
	 void		Render(HDC hDC)override;
	 void		Release()override;

private:
	int iSeed;
	bool m_bDead = false;

};

