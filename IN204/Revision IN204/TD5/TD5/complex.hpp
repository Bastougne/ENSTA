//
//  complex.hpp
//  TD5
//
//  Created by Kazem Ammar on 13/11/2021.
//

#ifndef complex_hpp
#define complex_hpp

#include <stdio.h>
#include <iostream>
#include <math.h>

class Complex
{
private:
    double mRealPart;
    double mImaginaryPart;
public:
    Complex(){};
    Complex(float nombreReal, float nombreImaginaire) : mRealPart(nombreReal), mImaginaryPart(nombreImaginaire) {}
    Complex(float nombreReal) : mRealPart(nombreReal), mImaginaryPart(0.0) {}
    Complex(double nombreReal) : mRealPart(nombreReal), mImaginaryPart(0.0) {}
    Complex(int nombreReal) : mRealPart((double)nombreReal), mImaginaryPart(0.0) {}
    Complex(unsigned int nombreReal) : mRealPart((double)nombreReal), mImaginaryPart(0.0) {}
    
    void print() const
    {
        std::cout<< mRealPart << "+I" << mImaginaryPart <<std::endl;
    }
    
    static Complex from_real_imaginary(double theRealPart, double theImaginaryPart)
    {
        Complex result;
        result.mRealPart = theRealPart;
        result.mImaginaryPart = theImaginaryPart;
        return result;
    }
    static Complex from_polar(double theRho, double theTheta)
    {
        return Complex(
           theRho* cos(theTheta),
           theRho* sin(theTheta));
    }
    
    friend Complex operator * (int, const Complex&);
    friend Complex operator * (double, const Complex&);
    friend Complex operator * (const Complex&, int);
    friend Complex operator * (const Complex&, double);
    
    Complex operator + (const Complex& aRightValue) const
    {
        Complex Result(*this);
        Result.mRealPart = Result.mRealPart + aRightValue.mRealPart;
        return Result;
    }
    
    Complex operator - (const Complex& aRightValue) const
    {
        Complex Result(*this);
        Result.mRealPart = Result.mRealPart - aRightValue.mRealPart;
        return Result;
    }
    
    friend Complex operator + (double aLeftValue, const Complex& aRightValue);
    friend Complex operator - (double aLeftValue, const Complex& aRightValue);
    
    
    // (a + i.b) x (a' + i.b') = (aa' – bb') + i (ab' + ba')
    Complex operator * (const Complex& aRightValue) const
    {
        Complex Result(*this);
        Result.mRealPart = Result.mRealPart*aRightValue.mRealPart - Result.mImaginaryPart*aRightValue.mImaginaryPart;
        Result.mImaginaryPart = Result.mRealPart*aRightValue.mImaginaryPart + Result.mImaginaryPart*aRightValue.mRealPart;
        return Result;
    }
    
    ~Complex(){}
    
    friend std::ostream& operator <<(std::ostream&, const Complex& aValue);
};

inline std::ostream& operator <<(std::ostream& os, const Complex& aValue)
{
    os<<aValue.mRealPart<< " + i " << aValue.mImaginaryPart<<std::endl;
    return os;
}

inline Complex operator + (double aLeftValue, const Complex& aRightValue)
{
    return Complex(aLeftValue + aRightValue.mRealPart, aRightValue.mImaginaryPart);
}

inline Complex operator - (double aLeftValue, const Complex& aRightValue)
{
    return Complex(aLeftValue - aRightValue.mRealPart, aRightValue.mImaginaryPart);
}

inline Complex operator * (int theLeftValue, const Complex& theRightValue)
{
    return Complex(theLeftValue * theRightValue.mRealPart, theLeftValue * theRightValue.mImaginaryPart);
}
inline Complex operator * (const Complex& theLeftValue, int theRightValue)
{
    return Complex(theLeftValue.mRealPart * theRightValue, theLeftValue.mImaginaryPart * theRightValue);
}
inline Complex operator * (double theLeftValue, const Complex& theRightValue)
{
    return Complex(theLeftValue * theRightValue.mRealPart, theLeftValue * theRightValue.mImaginaryPart);
}
inline Complex operator * (const Complex& theLeftValue, double theRightValue)
{
    return Complex(theLeftValue.mRealPart * theRightValue, theLeftValue.mImaginaryPart * theRightValue);
}



#endif /* complex_hpp */
