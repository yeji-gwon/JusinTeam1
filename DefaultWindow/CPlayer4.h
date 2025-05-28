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
	CObj*	pHead;
	CObj*	pBody;
};

