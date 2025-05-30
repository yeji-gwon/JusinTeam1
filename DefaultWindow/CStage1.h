#pragma once
#include "CScene.h"
#include "CArcher.h"

class CStage1 :
    public CScene
{
public:
    CStage1();
    virtual ~CStage1();

public:
    void            Initialize() override;
    int             Update() override;
    void            Late_Update() override;
    void            Render(HDC hDC) override;
    void            Release() override;

private:
    CObj*           m_pArcher;
    CObj*           m_pBow;
    CObj*           m_pTarget;

    vector<CObj*>   m_vecArrow;
};