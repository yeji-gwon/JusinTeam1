#include "pch.h"
#include "CSceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_pScene(nullptr), m_eCurScene(SC_MENU), m_ePreScene(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_MENU:
			m_pScene = new CMenu;
			break;
		case SC_STAGE1:
			m_pScene = new CStage1;
			break;
		case SC_STAGE2:
			m_pScene = new CStage2;
			break;
		case SC_STAGE3:
			m_pScene = new CStage3;
			break;
		case SC_STAGE4:
			m_pScene = new CStage4;
			break;
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

int CSceneMgr::Update()
{
	if (m_pScene)
		m_pScene->Update();

	return 0;
}

void CSceneMgr::Late_Update()
{
	if (m_pScene)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	if (m_pScene)
		m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete<CScene*>(m_pScene);
}