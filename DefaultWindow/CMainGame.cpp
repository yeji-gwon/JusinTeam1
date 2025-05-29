#include "pch.h"
#include "CMainGame.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	CTimeMgr::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
	CTimeMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
	CTimeMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	HDC hBackDC = CreateCompatibleDC(m_hDC);
	HBITMAP hBackBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);

	Rectangle(hBackDC, 0, 0, WINCX, WINCY);

	CSceneMgr::Get_Instance()->Render(hBackDC);
	CTimeMgr::Get_Instance()->Render(hBackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

	SelectObject(hBackDC, hOldBitmap);
	DeleteObject(hBackBitmap);
	DeleteDC(hBackDC);
}

void CMainGame::Release()
{
	CSceneMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
