#include "pch.h"
#include "CMenu.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

CMenu::CMenu()
{
}

CMenu::~CMenu()
{
	Release();
}

void CMenu::Initialize()
{
}

int CMenu::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE1);
	else if (CKeyMgr::Get_Instance()->Key_Down('2'))
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2);
	else if (CKeyMgr::Get_Instance()->Key_Down('3'))
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE3);
	else if (CKeyMgr::Get_Instance()->Key_Down('4'))
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE4);

	CKeyMgr::Get_Instance()->Update();

	return 0;
}

void CMenu::Late_Update()
{
	CKeyMgr::Get_Instance()->Late_Update();
}

void CMenu::Render(HDC hDC)
{
	TCHAR	szText[128];
	swprintf_s(szText, L"쥬신 155기 체육관" );
	TextOut(hDC, 320, 200, szText, lstrlen(szText));
	swprintf_s(szText, L"1. 양궁");
	TextOut(hDC, 320, 280, szText, lstrlen(szText));
	swprintf_s(szText, L"2. 스케이트 보드");
	TextOut(hDC, 320, 320, szText, lstrlen(szText));
	swprintf_s(szText, L"3. 스키");
	TextOut(hDC, 320, 360, szText, lstrlen(szText));
	swprintf_s(szText, L"4. 청기 백기");
	TextOut(hDC, 320, 400, szText, lstrlen(szText));
}

void CMenu::Release()
{
	CKeyMgr::Get_Instance()->Destroy_Instance();
}