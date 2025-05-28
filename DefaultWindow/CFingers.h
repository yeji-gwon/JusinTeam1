#pragma once
#include "CObj.h"

class CFingers : public CObj
{
public:
	CFingers();
	virtual ~CFingers();

public:
	void		Initialize() override;
	int			Update() override;
	void		Late_Update() override;
	void		Render(HDC hDC) override;
	void		Release() override;

private:
	std::unordered_map<string, CObj*> m_mapFingers;
};

