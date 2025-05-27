#pragma once
#include "CObj.h"
#include "BoogiDefine.h"
class CRoad :
	public CObj
{
public:
	CRoad();
	~CRoad();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void RenderHorizon(HDC hDC);
private:
	//중앙선
	tagLine m_Horizon;
	//지평선
	//도로
};

