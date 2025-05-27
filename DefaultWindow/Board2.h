#pragma once
#include "CObj.h"
#include "CKeyMgr.h"
class Board2 : public CObj
{
public:
	Board2();
	virtual ~Board2();

public:
    void Set_Center(float _x, float _y)
    {
        m_tBoard.m_vCenter.x = _x;
        m_tBoard.m_vCenter.x = _y;
    }
    pair<float, float> Get_Center()
    {
        return { m_tBoard.m_vCenter.x ,m_tBoard.m_vCenter.y };
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

    float       m_fAngleX = 0.f;
    float       m_fAngleY = 0.f;
    float       m_fAngleZ = 0.f;
    float       m_fSpeed = 0.f;   // 이동 속도

    bool        m_bFlip = false;    // 플립중인지
    bool        m_bShuvit = false;
    bool        m_bHardFlip = false;

    D3DXMATRIX  m_matWorld; // 최종 변환 행렬
    struct tagPolygon m_tBoard;
};

