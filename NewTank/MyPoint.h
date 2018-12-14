#pragma once
class CMyPoint
{
public:
    CMyPoint(int x = 0, int y = 0)
        :m_X(x), m_Y(y) 
    {
    };
    ~CMyPoint();

    /*÷ÿ‘ÿ=∫≈‘ÀÀ„∑˚*/
    CMyPoint &operator = (const CMyPoint &P)
    {
        m_X = P.m_X;
        m_Y = P.m_Y;

        return *this;
    }

    void SetX(int x);
    void SetY(int y);

    int GetX() { return m_X; }
    int GetY() { return m_Y; }
private:
    int m_X;
    int m_Y;
};

