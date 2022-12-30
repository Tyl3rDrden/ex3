#include "HealthPoints.h"


HealthPoints::HealthPoints(int maxHealth)
{
    if(maxHealth <= 0)
    {
        //Throwing the object revcieved by the deault constructor !
        throw HealthPoints::InvalidArgument();
    }
    m_maxPoints = maxHealth;
    m_points = m_maxPoints;
}



HealthPoints& HealthPoints::operator+=(const HealthPoints& t1)
{
    if(m_points + t1.getPoints() >= m_maxPoints)
    {
        m_points = m_maxPoints;
    }
    else
    {
        m_points += t1.getPoints();
    }
    return *this;

}
HealthPoints& HealthPoints::operator-=(const HealthPoints& t1)
{
    if(m_points - t1.getPoints() <= DEAD)
    {
        m_points = DEAD;

    }
    else
    {
        m_points -= t1.getPoints();
    }
    return *this;
}

int HealthPoints::getPoints() const
{
    return m_points;
}

HealthPoints operator+(const HealthPoints& x, const HealthPoints& y)
{
    return HealthPoints((x.getPoints() + y.getPoints()));
}

HealthPoints::operator int() const
{
    return m_points;
}
//conversion opertor into int

bool operator==(const HealthPoints& t1, const HealthPoints& t2)
{
    return t1.getPoints() == t2.getPoints();
}
bool operator!=(const HealthPoints& t1, const HealthPoints& t2)
{
    return t1.getPoints() != t2.getPoints();
}
bool operator<=(const HealthPoints& t1, const HealthPoints& t2)
{
    return t1.getPoints() <= t2.getPoints();
}
bool operator>=(const HealthPoints& t1, const HealthPoints& t2)
{
    return t1.getPoints() >= t2.getPoints();
}
bool operator<(const HealthPoints& t1, const HealthPoints& t2)
{
    return t1.getPoints() < t2.getPoints();
}
bool operator>(const HealthPoints& t1, const HealthPoints& t2)
{
    return t1.getPoints() > t2.getPoints();
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& t1)
{
    os<< t1.getPoints()<<'(' << t1.m_maxPoints << ')';
    return os;
}
HealthPoints operator-(const HealthPoints& x, const int& y)
{
    return HealthPoints(x.getPoints() - y);
}

//No bugS!
HealthPoints operator-(const int& y, const HealthPoints& x)
{
    return x - y;
}

HealthPoints operator+(const HealthPoints& x, const int& y)
{
    return HealthPoints(x.getPoints() + y);
}
HealthPoints operator+(const int& y, const HealthPoints& x)
{
    return x +y;
}

