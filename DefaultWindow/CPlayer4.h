#pragma once
#include "CObj.h"
class CPlayer4 : public CObj
{
public:
    CPlayer4();
    virtual ~CPlayer4();

public:
	void		Initialize() override;
	int			Update()override;
	void		Late_Update()override;
	void		Render(HDC hDC)override;
	void		Release()override;

private:
	tagPolygon	L_Head;
	tagPolygon	W_Head;

	tagPolygon	L_Body;
	tagPolygon	W_Body;

	tagPolygon	L_Arm;
	tagPolygon	W_Arm;

	tagPolygon	L_LHand;
	tagPolygon	W_LHand;

	tagPolygon	L_RHand;
	tagPolygon	W_RHand;
};

