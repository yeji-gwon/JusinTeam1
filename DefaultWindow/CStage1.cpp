#include "pch.h"
#include "CStage1.h"
#include "CKeyMgr.h"
#include "CArrow.h"

CStage1::CStage1() : m_pArcher(nullptr), m_pBow(nullptr)
{
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	m_vecArrow.reserve(10);

	if (!m_pArcher)
	{
		m_pArcher = new CArcher;
		m_pArcher->Initialize();
	}

	if (!m_pBow)
	{
		m_pBow = new CBow;
		m_pBow->Initialize();
	}

	dynamic_cast<CArcher*>(m_pArcher)->Set_Bow(m_pBow);
	dynamic_cast<CArcher*>(m_pArcher)->Set_VecArrow(&m_vecArrow);
}

int CStage1::Update()
{
	CKeyMgr::Get_Instance()->Update();

	m_pArcher->Update();
	m_pBow->Update();

	for (auto pArrow : m_vecArrow)
		pArrow->Update();

	return 0;
}

void CStage1::Late_Update()
{
	CKeyMgr::Get_Instance()->Late_Update();

	m_pArcher->Late_Update();
	m_pBow->Late_Update();

	for (auto pArrow : m_vecArrow)
		pArrow->Late_Update();
}

void CStage1::Render(HDC hDC)
{
	m_pArcher->Render(hDC);
	m_pBow->Render(hDC);

	for (auto pArrow : m_vecArrow)
		pArrow->Render(hDC);

	TCHAR	szText[32];
	swprintf_s(szText, L"스테이지 1");
	TextOut(hDC, 10, 10, szText, lstrlen(szText));
}

void CStage1::Release()
{
	CKeyMgr::Destroy_Instance();

	m_pArcher->Release();
	m_pBow->Release();

	for_each(m_vecArrow.begin(), m_vecArrow.end(), Safe_Delete<CObj*>);
	m_vecArrow.clear();
	m_vecArrow.shrink_to_fit();
}