#pragma once
#include "CObj.h"
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
private:
    void RenderHand(HDC hDC, tagPolygon poly);
    void RenderArm(HDC hDC, tagPolygon poly);
private:
    tagPolygon m_tLeftHand;
    tagPolygon m_tRightHand;

    D3DXVECTOR3 m_tLeftArm[4];
    D3DXVECTOR3 m_tRightArm[4];
};

