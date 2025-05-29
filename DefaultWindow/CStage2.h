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

    vector<Obstacle2*>    m_ObsVector;  // ��ֹ� ���� ����Ʈ
    int iSeed = 1;    // Y��ǥ 

    float fS2Time = 15.f; // ��������2 �����ð�
    float fTimeCount = 0.f; // �ð� üũ��
    float fSpawnTime = 0.f; // ��ֹ� ���� �ð�

};