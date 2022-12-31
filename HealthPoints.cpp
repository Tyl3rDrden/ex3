#include "HealthPoints.h"


HealthPoints::HealthPoints(const int maxHealth)
{
    if(maxHealth <= 0)
    {
        //Throwing the object revcieved by the deault constructor !
        HealthPoints::InvalidArgument e;
        throw e;
    }
    m_maxPoints = maxHealth;
    m_points = m_maxPoints;
}



HealthPoints& HealthPoints::operator+=(const HealthPoints& t1)
{
    if(m_points + int(t1) >= m_maxPoints)
    {
        m_points = m_maxPoints;
    }
    else
    {
        m_points += int(t1);
    }
    return *this;

}
HealthPoints& HealthPoints::operator-=(const HealthPoints& t1)
{
    if(m_points - int(t1) <= DEAD)
    {
        m_points = DEAD;

    }
    else
    {
        m_points -= int(t1);
    }
    return *this;
}

/*HealthPoints operator+(const HealthPoints& x, const HealthPoints& y)
{
    int result = int(x) + int(y);
    if(result >= x.m_maxPoints)
    {
        return HealthPoints(x.m_maxPoints);
    }
    else
    {
        HealthPoints temp(int(x) + int(y), x.m_maxPoints);
        return temp;


    }
}*/

HealthPoints::operator int() const
{
    return m_points;
}
//conversion opertor into int

bool operator==(const HealthPoints& t1, const HealthPoints& t2)
{
    return int(t1) == int(t2);
}
bool operator!=(const HealthPoints& t1, const HealthPoints& t2)
{
    return int(t1) != int(t2);
}
bool operator<=(const HealthPoints& t1, const HealthPoints& t2)
{
    return int(t1) <= int(t2);
}
bool operator>=(const HealthPoints& t1, const HealthPoints& t2)
{
    return int(t1) >= int(t2);
}
bool operator<(const HealthPoints& t1, const HealthPoints& t2)
{
    return int(t1) < int(t2);
}
bool operator>(const HealthPoints& t1, const HealthPoints& t2)
{
    return int(t1) > int(t2);
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& t1)
{
    os<< int(t1)<<'(' << t1.m_maxPoints << ')';
    return os;
}

//All of the non-member operators need to access maxhealth therefor they need to
//be friend

HealthPoints operator-(const HealthPoints& x, const int& y)
{
    int result = int(x) -y;
    if(result >= 0)
    {
        HealthPoints temp = HealthPoints(x.m_maxPoints);
        temp -= x.m_maxPoints;
        temp += result;
        return temp;
    }
    else
    {
        HealthPoints temp = HealthPoints(x.m_maxPoints);
        temp -= x.m_maxPoints;
        return temp;
    }
}

//No bugS!
HealthPoints operator-(const int& y, const HealthPoints& x)
{
    int result = y -int(x);
    if(result >= 0)
    {
        HealthPoints temp = HealthPoints(x.m_maxPoints);
        temp -= x.m_maxPoints;
        temp += result;
        return temp;
    }
    else
    {
        HealthPoints temp = HealthPoints(x.m_maxPoints);
        temp -= x.m_maxPoints;
        return temp;
    }
}

HealthPoints operator+(const HealthPoints& x, const int& y)
{
    int result = int(x) +y;
    if(result >= x.m_maxPoints)
    {
        return (HealthPoints(x.m_maxPoints));
    }
    else
    {
        HealthPoints temp = HealthPoints(x.m_maxPoints);
        temp -= x.m_maxPoints;
        temp += result;
        return temp;
    }
}
HealthPoints operator+(const int& y, const HealthPoints& x)
{
    int result = int(x) + y;
    if(result >= x.m_maxPoints)
    {
        return (HealthPoints(x.m_maxPoints));
    }
    else
    {
        HealthPoints temp = HealthPoints(x.m_maxPoints);
        temp -= x.m_maxPoints;
        temp += result;
        return temp;
    }
}

