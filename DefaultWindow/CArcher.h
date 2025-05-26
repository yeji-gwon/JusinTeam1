#pragma once
#include "CObj.h"

class CArcher :
    public CObj
{
public:
    CArcher();
    virtual ~CArcher();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    D3DXVECTOR3     m_vBodyP[4];
    D3DXVECTOR3     m_vBodyQ[4];
};