#pragma once
#include "CScene.h"
#include "Player2.h"
#include "Board2.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "Obstacle2.h"

class CStage2 :
    public CScene
{
public:
    CStage2();
    virtual ~CStage2();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void SyncPlayer();
    int ObsMaker();

private:
    Player2* pPlayer;
    Board2* pBoard;
    PLAYERSTATE m_eCurState = PLAYER_IDLE;
    PLAYERSTATE m_ePreState = PLAYER_IDLE;

    vector<Obstacle2*>    m_ObsVector;  // 장애물 관리 리스트
    int iSeed = 1;    // Y좌표 

    float fS2Time = 15.f; // 스테이지2 남은시간
    float fTimeCount = 0.f; // 시간 체크용
    float fSpawnTime = 0.f; // 장애물 스폰 시간

};