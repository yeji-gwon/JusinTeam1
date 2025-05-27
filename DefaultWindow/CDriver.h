#pragma once
#include "CObj.h"
#include "BoogiDefine.h"

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
    void RenderArm(HDC hDC, tagRect& arm, const D3DXMATRIX& matParent);

private:
    tagPolygon m_tLeftHand;
    tagPolygon m_tRightHand;

    tagRect m_tLeftArm;
    tagRect m_tRightArm;
};

