#include "pch.h"
#include "CStage4.h"
#include "CPlayer4.h"
#include "CKeyMgr.h"
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
}

int CStage4::Update()
{
	m_pPlayer->Update();
	CKeyMgr::Get_Instance()->Update();
	return 0;
}

void CStage4::Late_Update()
{
	m_pPlayer->Late_Update();

}

void CStage4::Render(HDC hDC)
{
	m_pPlayer->Render(hDC);

}

void CStage4::Release()
{
}