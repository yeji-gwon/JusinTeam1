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
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	CSceneMgr::Get_Instance()->Render(m_hDC); 
	CTimeMgr::Get_Instance()->Render(m_hDC);
}

void CMainGame::Release()
{
	CSceneMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
