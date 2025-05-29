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
	for (auto i = m_ObsVector.begin(); i != m_ObsVector.end();)
	{
		int bDead = (*i)->Update();
		if (bDead)
		{
			i = m_ObsVector.erase(i);  // erase()는 다음 유효한 반복자를 반환
		}
		else
		{
			++i;  // 삭제되지 않은 경우에만 증가
		}
	}
	fS2Time -= CTimeMgr::Get_Instance()->Get_Delta();
	fSpawnTime += CTimeMgr::Get_Instance()->Get_Delta();
	pPlayer->Update();
	pBoard->Update();
	SyncPlayer();

	if (fSpawnTime>1.f)
	{
		fSpawnTime = 0.f;
		iSeed = ObsMaker();
		Obstacle2* ObsTemp = new Obstacle2(iSeed);
		ObsTemp->Initialize();
		m_ObsVector.push_back(ObsTemp);
		ObsTemp = nullptr;
		
	}
	
	if (fS2Time <= 0.f)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	}
	return 0;
}

void CStage2::Late_Update()
{
	pPlayer->Late_Update();
	pBoard->Late_Update();

	if (pPlayer->Get_State() == PLAYER_IDLE)
	{
		for (auto i = m_ObsVector.begin(); i != m_ObsVector.end(); i++)
		{
			float fDist = fabsf(pPlayer->Get_Center().first + 10 - (*i)->Get_Info().vPos.x);
			if (fDist < 20.f)
			{
				pPlayer->Set_Hp(1);
				(*i)->Set_Dead();
			}
		}
	}



}

void CStage2::Render(HDC hDC)
{
	for (auto i = m_ObsVector.begin(); i != m_ObsVector.end(); i++)
	{
		(*i)->Render(hDC);
	}

	TCHAR	szText[128];
	swprintf_s(szText, L"스테이지 2");
	TextOut(hDC, 10, 10, szText, lstrlen(szText));
	swprintf_s(szText, L"남은 시간 : %2.2f", fS2Time);
	TextOut(hDC, 300, 10, szText, lstrlen(szText));
	swprintf_s(szText, L"체력 : %3d", pPlayer->Get_Hp());
	TextOut(hDC, 600, 10, szText, lstrlen(szText));

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

// 랜덤으로 장애물 Y좌표를 만듭니다
int CStage2::ObsMaker()
{
	int iRandom = rand() % 3 + 1;
	return iRandom;
}
