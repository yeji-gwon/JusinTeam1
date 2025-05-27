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
    float       m_fSpeed = 0.f;   // �̵� �ӵ�
    
    bool        m_bFlip = false;    // �ø�������
    bool        m_bShuvit = false;
    bool        m_bHardFlip = false;

    D3DXMATRIX  m_matWorld; // ���� ��ȯ ���

    // 5�� ������
    tagPolygon m_tHead;        // �Ӹ� (�θ�)
    tagPolygon m_tBody;        // ����
    tagPolygon m_tLeftArm;     // ����
    tagPolygon m_tRightArm;    // ������
    tagPolygon m_tLeftLeg;     // �޴ٸ�
    tagPolygon m_tRightLeg;    // �����ٸ�

    // 5�� ���� ���
    D3DXMATRIX m_matWorldHead;      // �Ӹ� ���� ��� (����)
    D3DXMATRIX m_matWorldBody;      // ���� ���� ���
    D3DXMATRIX m_matWorldLeftArm;   // ���� ���� ���
    D3DXMATRIX m_matWorldRightArm;  // ������ ���� ���
    D3DXMATRIX m_matWorldLeftLeg;   // �޴ٸ� ���� ���
    D3DXMATRIX m_matWorldRightLeg;  // �����ٸ� ���� ���

    // �ڽĵ��� �θ� ���� ��� ��ġ
    D3DXVECTOR3 m_vRelativeBody;
    D3DXVECTOR3 m_vRelativeLeftArm;
    D3DXVECTOR3 m_vRelativeRightArm;
    D3DXVECTOR3 m_vRelativeLeftLeg;
    D3DXVECTOR3 m_vRelativeRightLeg;

    // �� ������ ȸ����
    float m_fAngleBody;
    float m_fAngleLeftArm;
    float m_fAngleRightArm;
    float m_fAngleLeftLeg;
    float m_fAngleRightLeg;
};

