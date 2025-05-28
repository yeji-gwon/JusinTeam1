#pragma once
#include <random>

class CRandom
{
public:
    // ���� ���� ����
    static int GetInt(int min, int max)
    {
        static std::mt19937 rng(Seed());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    // �Ǽ� ���� ����
    static float GetFloat(float min, float max)
    {
        static std::mt19937 rng(Seed());
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }
private:
    static unsigned int Seed()
    {
        static std::random_device rd;
        return rd(); // �� ���ึ�� �ٸ� seed ��ȯ
    }
};

