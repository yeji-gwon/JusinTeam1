#pragma once
#include "CObj.h"
#include "BoogiDefine.h"
#include "CTimeMgr.h"

using namespace Boogi;

class CSki;
class CSlope :
	public CObj
{
public:
	CSlope();
	virtual ~CSlope() override;

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Set_Target(CSki* target);

private:

	CSki* m_pTarget;
	tagSlope m_Slope;
};
