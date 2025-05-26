#include "pch.h"
#include "CStage1.h"

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
}

int CStage1::Update()
{
    return 0;
}

void CStage1::Late_Update()
{
}

void CStage1::Render(HDC hDC)
{
	TCHAR	szText[32];
	swprintf_s(szText, L"스테이지 1");
	TextOut(hDC, 10, 10, szText, lstrlen(szText));
}

void CStage1::Release()
{
}