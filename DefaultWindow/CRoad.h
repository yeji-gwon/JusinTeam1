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
	//�߾Ӽ�
	tagLine m_Horizon;
	//����
	//����
};

