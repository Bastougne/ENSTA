//
//  key_value_pair.hpp
//  Examen IN204
//
//  Created by Kazem Ammar on 13/11/2021.
//

#ifndef key_value_pair_hpp
#define key_value_pair_hpp

#include <stdio.h>
#include <iostream>


template<class keyT , class valueT>
class key_value_pair
{
private:
    keyT key;
    valueT value;
public:
    key_value_pair() : key(0.0), value("Empty"){}
    key_value_pair(keyT theKey, valueT theValue) : key(theKey), value(theValue) {}
    key_value_pair(const key_value_pair& anotherPair) : key(anotherPair.key), value(anotherPair.value) {}
    
    keyT getKey() const
    {
        return key;
    }
    
    valueT getValue() const
    {
        return value;
    }
    
    void setValue(const std::string& Valeur)
    {
        value=Valeur;
    }
    
    bool operator == (const key_value_pair& Objet) const
    {
        if(key==Objet.key && value==Objet.value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool operator != (const key_value_pair& Objet) const
    {
        if(key!=Objet.key || value!=Objet.value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool operator < (const key_value_pair& Objet) const
    {
        if(key < Objet.key)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool operator <= (const key_value_pair& Objet) const
    {
        if(key <= Objet.key)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool operator > (const key_value_pair& Objet) const
    {
        if(key > Objet.key)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool operator >= (const key_value_pair& Objet) const
    {
        if(key >= Objet.key)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    
    template<class charT, class traits>
    friend std::ostream& operator << (std::ostream& aStream, const key_value_pair<keyT, valueT>&  thePair);
};

template<class keyT , class valueT>
inline std::ostream& operator << (std::ostream& aStream, const key_value_pair<keyT, valueT>& thePair)
{
    aStream<< thePair.getKey() <<" => "<< thePair.getValue() << std::endl;
    return aStream;
}

template<class keyT , class valueT>
class key_defined_value : public key_value_pair<keyT, valueT>
{
private:
    bool is_void;
public:
    key_defined_value() : key_value_pair<keyT, valueT>(), is_void(true){}
    key_defined_value(keyT theKey, valueT theValue, bool theis_void) : key_value_pair<keyT, valueT>(theKey,theValue),is_void(theis_void)  {}
    key_defined_value(const key_defined_value& anotherPair) :  key_value_pair<keyT, valueT>(anotherPair.key, anotherPair.value), is_void(anotherPair.is_void){}
};
#endif /* key_value_pair_hpp */
