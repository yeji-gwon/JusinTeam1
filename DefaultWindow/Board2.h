#pragma once
#include "CObj.h"
#include "CKeyMgr.h"
class Board2 : public CObj
{
public:
    Board2();
    virtual ~Board2();

public:
    static Board2* Get_Instance()
    {
        if (!pInstance)
            pInstance = new Board2;

        return pInstance;
    }
    static void Destroy_Instance()
    {
        if (pInstance)
            Safe_Delete(pInstance);
    }

    pair<float, float> Get_Center()
    {
        return { m_tBoard.m_vCenter.x, m_tBoard.m_vCenter.y };
    }

    pair<float, float> Get_Scale()
    {
        return { m_tBoard.m_vScale.x, m_tBoard.m_vScale.y };
    }
public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Update_Matrix();

private:
    void    Key_Input();


private:
    static Board2* pInstance;
    float       m_fAngleX = 0.f;
    float       m_fAngleY = 0.f;
    float       m_fAngleZ = 0.f;
    float       m_fSpeed = 0.f;   // 이동 속도

    bool        m_bFlip = false;    // 플립중인지
    bool        m_bShuvit = false;
    bool        m_bHardFlip = false;

    struct tagPolygon m_tBoard;
    D3DXMATRIX  m_matWorld; // 최종 변환 행렬
    
    struct tagPolygon m_tWheel[2];
    D3DXMATRIX  m_matWorldWheel[2];
};

