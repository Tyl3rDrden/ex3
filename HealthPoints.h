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
        int getPoints() const;
        //proper get function
        HealthPoints(int maxHealth = DEFAULTMAX);
        //conversion operator into int 
        operator int() const;
        //Conversion operator into bools
        //as requested overloaded operators
        HealthPoints& operator+=(const HealthPoints& t1);
        HealthPoints& operator-=(const HealthPoints& t1);
        //Technically i did not need to use friend but i'm curious!!
        //Don't judge me!
        friend bool operator<=(const HealthPoints& t1, const HealthPoints& t2);
        friend bool operator>=(const HealthPoints& t1, const HealthPoints& t2);
        friend bool operator==(const HealthPoints& t1, const HealthPoints& t2);
        friend bool operator!=(const HealthPoints& t1, const HealthPoints& t2);
        //I'll implmemnt these with the ones up top given the
        //special case that the operators are equal
        friend bool operator<(const HealthPoints& t1, const HealthPoints& t2);
        friend bool operator>(const HealthPoints& t1, const HealthPoints& t2);
        friend std::ostream& operator<<(std::ostream& os, const HealthPoints& t1);
        //wow i have a lot of friends !!!!
        //I'm popular!

};

//treated as a non member function
HealthPoints operator+(const HealthPoints& x, const HealthPoints& y);
HealthPoints operator-(const HealthPoints& x, const HealthPoints& y);

//
HealthPoints operator+(const HealthPoints& x, const int& y);
HealthPoints operator+(const int& y, const HealthPoints& x);


HealthPoints operator-(const HealthPoints& x, const int& y);
HealthPoints operator-(const int& y, const HealthPoints& x);
//chatGTB IS SCARY GOOD !

//Input/Output Operators

std::ostream& operator<<(std::ostream& os, const HealthPoints& t1);

#endif

