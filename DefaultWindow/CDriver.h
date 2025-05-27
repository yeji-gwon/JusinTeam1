#pragma once
#include "CObj.h"

struct tagArm {
    D3DXVECTOR3 m_vCorner[4]; // ���� ��ǥ �簢��
    D3DXVECTOR3 m_vScale;     // ũ��
    D3DXVECTOR3 m_vRotate;    // Z�� ȸ�� (Yaw�� �ʿ���)
    D3DXVECTOR3 m_vPos;       // ��ġ (�߽�)
};


class CDriver :
    public CObj
{
public:
    CDriver();
    ~CDriver();
public:
    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    void Set_CenterLeft(D3DXVECTOR3 left);
    void Set_CenterRight(D3DXVECTOR3 right);
    void Get_Rotate(D3DXVECTOR3 Rot);
private:
    void RenderHand(HDC hDC, tagPolygon poly,bool left);
    void RenderArm(HDC hDC, tagArm& arm, const D3DXMATRIX& matParent);

private:
    tagPolygon m_tLeftHand;
    tagPolygon m_tRightHand;

    tagArm m_tLeftArm;
    tagArm m_tRightArm;
};

