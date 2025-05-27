#include "pch.h"
#include "CPlayer4.h"
#include "CHead.h"
#include "CBody.h"
CPlayer4::CPlayer4()
{
}

CPlayer4::~CPlayer4()
{
}

void CPlayer4::Initialize()
{
    pHead = new CHead;
    pHead->Initialize();

    pBody = new CBody;
    pBody->Initialize();
}

int CPlayer4::Update()
{
    pHead->Update();
    pBody->Update();
    return 0;
}

void CPlayer4::Late_Update()
{
    pHead->Late_Update();
    pBody->Late_Update();
}

void CPlayer4::Render(HDC hDC)
{
    pHead->Render(hDC);
    pBody->Render(hDC);
}

void CPlayer4::Release()
{
}
