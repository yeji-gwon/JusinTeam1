#pragma once
#include "CPlayer.h"
#include "CKeyMgr.h"

class Player2 : public CPlayer
{
public:
	Player2();
	virtual ~Player2();

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Key_Input();
    void Update_Matrix();
    void Update_Direction();

private:
    D3DXVECTOR3 m_vCenterHead;
    D3DXVECTOR3 m_vTopBody;
    D3DXVECTOR3 m_vBottomBody;
    D3DXVECTOR3 m_vLeftFoot;
    D3DXVECTOR3 m_vRightFoot;
    
    float       m_fAngleX = 0.f;
    float       m_fAngleY = 0.f;
    float       m_fAngleZ = 0.f;
    float       m_fSpeed = 0.f;   // 이동 속도
    
    bool        m_bFlip = false;    // 플립중인지
    bool        m_bShuvit = false;
    bool        m_bHardFlip = false;

    D3DXMATRIX  m_matWorld; // 최종 변환 행렬
    struct tagPolygon m_tHead;
};

