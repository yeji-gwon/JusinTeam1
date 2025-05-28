#include "pch.h"
#include "CStage3.h"
#include "CKeyMgr.h"
#include "CObj.h"
#include "CSki.h"
#include "CSlope.h"
CStage3::CStage3()
	:m_pSki(nullptr)
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	m_pSki = new CSki;
	m_pSki->Initialize();
	m_pSlope = new CSlope;
	m_pSlope->Initialize();

	static_cast<CSlope*>(m_pSlope)->Set_Target(static_cast<CSki*>(m_pSki));
}

int CStage3::Update()
{
	CKeyMgr::Get_Instance()->Update();
	m_pSki->Update();
	m_pSlope->Update();
	return 0;
}

void CStage3::Late_Update()
{
	m_pSki->Late_Update();
	m_pSlope->Late_Update();
}

void CStage3::Render(HDC hDC)
{
	m_pSlope->Render(hDC);
	m_pSki->Render(hDC);
}

void CStage3::Release()
{
	Safe_Delete<CObj*>(m_pSki);
	Safe_Delete<CObj*>(m_pSlope);
}
