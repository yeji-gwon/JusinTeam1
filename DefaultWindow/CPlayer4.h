#pragma once
#include "CObj.h"
#include "CBody.h"
class CPlayer4 : public CObj
{
public:
    CPlayer4();
    virtual ~CPlayer4();

public:
	BTYPE		Get_BType() { return dynamic_cast<CBody*>(pBody)->Get_BType(); };
	WTYPE		Get_WType() { return dynamic_cast<CBody*>(pBody)->Get_WType(); };
	void		Init_Type();
public:
	void		Initialize() override;
	int			Update()override;
	void		Late_Update()override;
	void		Render(HDC hDC)override;
	void		Release()override;

private:
	CObj*	pHead;
	CObj*	pBody;
};

