#include "pch.h"
#include "CStage4.h"
#include "CFingers.h"
CStage4::CStage4()
{
}

CStage4::~CStage4()
{
	Release();
}

void CStage4::Initialize()
{
	m_pFingers = new CFingers;
	m_pFingers->Initialize();
}

int CStage4::Update()
{
	m_pFingers->Update();

	return 0;
}

void CStage4::Late_Update()
{
	m_pFingers->Late_Update();

}

void CStage4::Render(HDC hDC)
{
	m_pFingers->Render(hDC);

}

void CStage4::Release()
{
}