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
    
    float       m_fAngleX = 0.f;
    float       m_fAngleY = 0.f;
    float       m_fAngleZ = 0.f;
    float       m_fSpeed = 0.f;   // 이동 속도
    
    bool        m_bFlip = false;    // 플립중인지
    bool        m_bShuvit = false;
    bool        m_bHardFlip = false;

    D3DXMATRIX  m_matWorld; // 최종 변환 행렬

    // 5개 폴리곤
    tagPolygon m_tHead;        // 머리 (부모)
    tagPolygon m_tBody;        // 몸통
    tagPolygon m_tLeftArm;     // 왼팔
    tagPolygon m_tRightArm;    // 오른팔
    tagPolygon m_tLeftLeg;     // 왼다리
    tagPolygon m_tRightLeg;    // 오른다리

    // 5개 월드 행렬
    D3DXMATRIX m_matWorldHead;      // 머리 월드 행렬 (기준)
    D3DXMATRIX m_matWorldBody;      // 몸통 월드 행렬
    D3DXMATRIX m_matWorldLeftArm;   // 왼팔 월드 행렬
    D3DXMATRIX m_matWorldRightArm;  // 오른팔 월드 행렬
    D3DXMATRIX m_matWorldLeftLeg;   // 왼다리 월드 행렬
    D3DXMATRIX m_matWorldRightLeg;  // 오른다리 월드 행렬

    // 자식들의 부모 기준 상대 위치
    D3DXVECTOR3 m_vRelativeBody;
    D3DXVECTOR3 m_vRelativeLeftArm;
    D3DXVECTOR3 m_vRelativeRightArm;
    D3DXVECTOR3 m_vRelativeLeftLeg;
    D3DXVECTOR3 m_vRelativeRightLeg;

    // 각 부위별 회전각
    float m_fAngleBody;
    float m_fAngleLeftArm;
    float m_fAngleRightArm;
    float m_fAngleLeftLeg;
    float m_fAngleRightLeg;
};

