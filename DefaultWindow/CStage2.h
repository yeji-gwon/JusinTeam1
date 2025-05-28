#pragma once
#include "CScene.h"
#include "Player2.h"
#include "Board2.h"

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

private:
    Player2* pPlayer;
    PLAYERSTATE m_eCurState;
    PLAYERSTATE m_ePreState = PLAYER_IDLE;
    Board2* pBoard;
};