#include "pch.h"
#include "CScene.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

bool CScene::ReturnToMenu()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_BACK))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return true;
	}
		 
	return false;
}