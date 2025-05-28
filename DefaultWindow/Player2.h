#pragma once
#include "CPlayer.h"
#include "CKeyMgr.h"

enum PLAYERSTATE { PLAYER_IDLE, PLAYER_JUMP1, PLAYER_JUMP2, PLAYER_JUMP3, PLAYER_END };
class Player2 : public CPlayer
{
public:
    Player2();
    virtual ~Player2();

public:
    static Player2* Get_Instance()
    {
        if (!pInstance)
            pInstance = new Player2;

        return pInstance;
    }
    static void Destroy_Instance()
    {
        if (pInstance)
            Safe_Delete(pInstance);
    }

    void Set_Center(float _x, float _y)
    {
        m_vCenterHead.x = _x;
        m_vCenterHead.y = _y;
    }

    pair<float, float> Get_Center()
    {
        return { m_vCenterHead.x , m_vCenterHead.y };
    }

    PLAYERSTATE Get_State()
    {
        return m_eState;
    };

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

private:
    static Player2* pInstance;
    D3DXVECTOR3 m_vCenterHead;
    D3DXVECTOR3 m_vBodyPoint[11];
    D3DXVECTOR3 m_vRotAxis;

    float       m_fAngleX = 0.f;
    float       m_fAngleY = 0.f;
    float       m_fAngleZ = 0.f;
    float       m_fAngleA = 0.f;
    float       m_fSpeed = 0.f;   // 이동 속도

    bool        m_bFlip = false;    // 플립중인지
    bool        m_bShuvit = false;
    bool        m_bHardFlip = false;

    D3DXMATRIX  m_matWorld; // 최종 변환 행렬
    D3DXMATRIX  m_matBodyWorld; // 몸체 변환 행렬

    tagPolygon m_tHead;

    PLAYERSTATE m_eState = PLAYER_IDLE;

    float m_fJumpVelocity = 0.0f;
    float m_fGravity = 0.8f;
    float m_fGroundY = 400.0f;  // 지면 Y 좌표
    bool m_bOnGround = true;
};

