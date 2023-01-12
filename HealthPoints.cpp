#include "HealthPoints.h"

HealthPoints::HealthPoints(const int maxHealth) {
  if (maxHealth <= 0) {
    // Throwing the object revcieved by the deault constructor !
    HealthPoints::InvalidArgument e;
    throw e;
  }
  m_maxPoints = maxHealth;
  m_points = m_maxPoints;
}

HealthPoints &HealthPoints::operator-=(int t1) {
  m_points -= t1;
  if (m_points > m_maxPoints) {
    m_points = m_maxPoints;
  }
  if (m_points < 0) {
    m_points = 0;
  }
  return *this;
}
HealthPoints &HealthPoints::operator+=(int t1) {
  // Much more elegant
  if (m_points + t1 < m_maxPoints) {
    *this -= (-t1);
  } else {
    m_points = m_maxPoints;
  }

  return *this;
}

// conversion opertor into int

bool operator==(const HealthPoints &t1, const HealthPoints &t2) {
  return (t1.m_points == t2.m_points);
}

bool operator<(const HealthPoints &t1, const HealthPoints &t2) {
  return t1.m_points < t2.m_points;
}

bool operator!=(const HealthPoints &t1, const HealthPoints &t2) {
  return !(t1 == t2);
}

bool operator<=(const HealthPoints &t1, const HealthPoints &t2) {
  return ((t1 < t2) || t1 == t2);
}
bool operator>=(const HealthPoints &t1, const HealthPoints &t2) {
  return !(t1 < t2);
}
bool operator>(const HealthPoints &t1, const HealthPoints &t2) {
  return (t1 >= t2) && (t1 != t2);
}
bool operator>(const HealthPoints &hp, const int &num) {
  return hp.m_points > num;
}

std::ostream &operator<<(std::ostream &os, const HealthPoints &t1) {
  os << t1.m_points << '(' << t1.m_maxPoints << ')';
  return os;
}

HealthPoints operator-(const HealthPoints hp1, const int pointsRemove) {
  HealthPoints result(hp1);
  result -= pointsRemove;
  return result;
}
HealthPoints operator+(const HealthPoints &hp1, const int addPoints) {
  HealthPoints result(hp1);
  result += addPoints;
  return result;
}
HealthPoints operator+(const int addPoints, const HealthPoints &hp1) {
  HealthPoints result(hp1);
  result += addPoints;
  return result;
}
