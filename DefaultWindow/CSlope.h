#pragma once
#include "CObj.h"
#include "BoogiDefine.h"

using namespace Boogi;

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

public:
};
