#pragma once
#include "CObj.h"

struct tagArm {
    D3DXVECTOR3 m_vCorner[4]; // 로컬 좌표 사각형
    D3DXVECTOR3 m_vScale;     // 크기
    D3DXVECTOR3 m_vRotate;    // Z축 회전 (Yaw만 필요함)
    D3DXVECTOR3 m_vPos;       // 위치 (중심)
};


class CDriver :
    public CObj
{
public:
    CDriver();
    ~CDriver();
public:
    // CObj을(를) 통해 상속됨
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

