#ifndef HEALTHPOINTSH
#define HEALPOINTSH HEALTHPOINTS_H

#include <iostream>

#define DEAD 0
#define DEFAULTMAX 100


class HealthPoints
{
    private: 
        int m_points;
        int m_maxPoints; // check if needed const
    public:
        class InvalidArgument 
        {
            //Creating an empty constructor so i can throw it as an argument
        };
        //proper get function
        HealthPoints(int maxHealth = DEFAULTMAX);
        //Default Conctructor

        HealthPoints(const HealthPoints& healthPointsCopy):
        m_points(healthPointsCopy.m_points),
        m_maxPoints(healthPointsCopy.m_maxPoints){};
        //Copy C`tor


        //as requested overloaded operators
        HealthPoints& operator+=(int t1);
        HealthPoints& operator-=(int t1);
        //I'll implmemnt these with the ones up top given the
        //special case that the operators are equal



        //All of the above don't need friend need to delete!
        friend std::ostream& operator<<(std::ostream& os, const HealthPoints& t1);
        //wow i have a lot of friends !!!!
        //I'm popular!
        friend HealthPoints operator-(const HealthPoints hp1, const int pointsRemove);
        friend bool operator==(const HealthPoints& t1, const HealthPoints& t2);
        friend bool operator<(const HealthPoints& t1, const HealthPoints& t2);
        ~HealthPoints() = default;

};


bool operator<(const HealthPoints& t1, const HealthPoints& t2);
bool operator>(const HealthPoints& t1, const HealthPoints& t2);

bool operator>(const HealthPoints& t1, const int& num);


bool operator<=(const HealthPoints& t1, const HealthPoints& t2);
bool operator>=(const HealthPoints& t1, const HealthPoints& t2);
bool operator==(const HealthPoints& t1, const HealthPoints& t2);
bool operator!=(const HealthPoints& t1, const HealthPoints& t2);

//treated as a non member function
//HealthPoints operator+(const HealthPoints& x, const HealthPoints& y);
//HealthPoints operator-(const HealthPoints& x, const HealthPoints& y);

//
//HealthPoints operator+(const int& y, const HealthPoints& x);


//HealthPoints operator-(const HealthPoints& x, const int& y);
//HealthPoints operator-(const int& y, const HealthPoints& x);
//chatGTB IS SCARY GOOD !

//Input/Output Operators





std::ostream& operator<<(std::ostream& os, const HealthPoints& t1);


HealthPoints operator-(const HealthPoints hp1, const int pointsRemove);

HealthPoints operator+(const HealthPoints hp1, const int addPoints);

HealthPoints operator+(const int addPoints, const HealthPoints hp1);


#endif

