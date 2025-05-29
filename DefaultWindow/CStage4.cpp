#include "pch.h"
#include "CStage4.h"
#include "CPlayer4.h"
#include "CKeyMgr.h"
#include "CGameSystem4.h"

CStage4::CStage4()
{
}

CStage4::~CStage4()
{
	Release();
}

void CStage4::Initialize()
{
	m_pPlayer = new CPlayer4;
	m_pPlayer->Initialize();

	m_pGameSystem = new CGameSystem4;
	m_pGameSystem->Initialize();
}

int CStage4::Update()
{
	m_pPlayer->Update();
	m_pGameSystem->Update();
	CKeyMgr::Get_Instance()->Update();
	return 0;
}

void CStage4::Late_Update()
{
	m_pPlayer->Late_Update();
	m_pGameSystem->Late_Update();

	dynamic_cast<CGameSystem4*> (m_pGameSystem)->Get_PlayerType(
		dynamic_cast<CPlayer4*>(m_pPlayer)->Get_BType(),
		dynamic_cast<CPlayer4*>(m_pPlayer)->Get_WType());

	if (dynamic_cast<CGameSystem4*> (m_pGameSystem)->Get_ResultTime() < 0)
	{
		dynamic_cast<CPlayer4*>(m_pPlayer)->Init_Type();
	}
}

void CStage4::Render(HDC hDC)
{
	m_pPlayer->Render(hDC);
	m_pGameSystem->Render(hDC);
}

void CStage4::Release()
{
}