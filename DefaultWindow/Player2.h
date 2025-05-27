#pragma once
#include "CPlayer.h"
#include "CKeyMgr.h"

enum PLAYERSTATE {PLAYER_IDLE, PLAYER_JUMP1, PLAYER_JUMP2, PLAYER_JUMP3, PLAYER_END};
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
    void Update_State();
    void Update_Jump();
    void Update_Matrix();
    void Update_Direction();
    

private:
    D3DXVECTOR3 m_vCenterHead;
    D3DXVECTOR3 m_vBodyPoint[11];
    
    float       m_fAngleX = 0.f;
    float       m_fAngleY = 0.f;
    float       m_fAngleZ = 0.f;
    float       m_fSpeed = 0.f;   // �̵� �ӵ�

    bool        m_bFlip = false;    // �ø�������
    bool        m_bShuvit = false;
    bool        m_bHardFlip = false;

    D3DXMATRIX  m_matWorld; // ���� ��ȯ ���
    D3DXMATRIX  m_matBodyWorld; // ��ü ��ȯ ���

    tagPolygon m_tHead;

    PLAYERSTATE m_eState = PLAYER_IDLE;

    float m_fJumpVelocity = 0.0f;
    float m_fGravity = 0.8f;
    float m_fGroundY = 400.0f;  // ���� Y ��ǥ
    bool m_bOnGround = true;
};

