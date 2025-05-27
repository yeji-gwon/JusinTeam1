#pragma once
#include "CObj.h"
class CRoad :
    public CObj
{
public:
    CRoad();
    ~CRoad();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    //중앙선
    //지평선
    //도로
};

