#include "pch.h"
#include "CStage3.h"
#include "CKeyMgr.h"
#include "CObj.h"
#include "CSki.h"
#include "CSlope.h"
CStage3::CStage3()
	:m_pSki(nullptr), trigger(nullptr)
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
	trigger= static_cast<CSki*>(m_pSki)->Get_Count();
}

int CStage3::Update()
{
	if (*trigger < 5) {
		CKeyMgr::Get_Instance()->Update();
		m_pSki->Update();
		m_pSlope->Update();
	}
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

	if (*trigger >= 5) {
		TCHAR szAngle[64];
		_stprintf_s(szAngle, _T("GAME WIN"));
		TextOut(hDC, WINCX/2, WINCY/2, szAngle, lstrlen(szAngle));
	}
}

void CStage3::Release()
{
	Safe_Delete<CObj*>(m_pSki);
	Safe_Delete<CObj*>(m_pSlope);
}
