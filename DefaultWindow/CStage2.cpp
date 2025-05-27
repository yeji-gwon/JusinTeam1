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
	pPlayer = new Player2;
	pPlayer->Initialize();
	pBoard = new Board2;
	pBoard->Initialize();
	
}

int CStage2::Update()
{
	pPlayer->Update();
	pBoard->Update();
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


	pPlayer->Render(hDC);
	pBoard->Render(hDC);
}

void CStage2::Release()
{
	Safe_Delete(pPlayer);
	Safe_Delete(pBoard);
}
