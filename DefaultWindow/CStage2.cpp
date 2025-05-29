#include "pch.h"
#include "CStage2.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	pPlayer = Player2::Get_Instance();
	pPlayer->Initialize();
	pBoard = Board2::Get_Instance();
	pBoard->Initialize();

}

int CStage2::Update()
{
	
	pPlayer->Update();
	pBoard->Update();
	SyncPlayer();
	
	return 0;
}

void CStage2::Late_Update()
{
	pPlayer->Late_Update();
	pBoard->Late_Update();
}

void CStage2::Render(HDC hDC)
{
	TCHAR	szText[128];
	swprintf_s(szText, L"스테이지 2");
	TextOut(hDC, 10, 10, szText, lstrlen(szText));

	pBoard->Render(hDC);
	pPlayer->Render(hDC);

}

void CStage2::Release()
{
	pPlayer->Destroy_Instance();
	pBoard->Destroy_Instance();
}

void CStage2::SyncPlayer()
{
	m_eCurState = pPlayer->Get_State();
	pair<float, float> fCenter = pBoard->Get_Center();
	pair<float, float> fScale = pBoard->Get_Scale();


	float fBoardLineY = fCenter.second - (fScale.second / 2.f);
	float fHeight = 5.f * 20.f;
	switch (m_eCurState)
	{
	case PLAYER_IDLE:
		pPlayer->Set_Center(fCenter.first + 40.f, fBoardLineY - fHeight);
		break;
	default:
		pPlayer->Set_Center(fCenter.first, pPlayer->Get_Center().second);
		break;
	}
}
