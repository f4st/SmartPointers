//
//  main.cpp
//  SmartPointers
//
//  Created by Mykola Farion on 8/13/13.
//  Copyright (c) 2013 Mykola Farion. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <memory.h>
#include "Shared_Ptr.h"
#include <boost/shared_ptr.hpp>
//#include <boost/weak_ptr.hpp>
//#include <boost/scoped_ptr.hpp>

char gibberish[][80] =
{
    "Yesterday i was working so hard, i need vacation today",
    "I hope it will be better tomorrow",
    "I promise you, i'll be there in 5 minutes",
};

class Person
{
public:
    Person(char* n = 0,int num = 0):counter(0)
    {
        age = num;
        strcpy(name,n);
    }
    void talkGibberish()
    {
        std::cout<< "Hi, i'm "<<name<<" and i'm "<<age<<std::endl;
        std::cout<< gibberish[rand()%3] << std::endl;
        
    }
    int counter;
private:
    char name[20];
    int age;
};


int main(int argc, const char * argv[])
{

    boost::shared_ptr<Person> spobj1; 
    
    {
        boost::shared_ptr<Person> spobj2( new Person("Luke", 33) ); 
        
        spobj2->counter ++;
        spobj2->talkGibberish(); 
        
        Person & robj = *spobj2; 
        Person * pobj = spobj2.get(); 
        
        if ( spobj2 ) { 
            std::cout << "Pointer refernce on object on address " << spobj2.get() << std::endl;
        }
        
        spobj1 = spobj2;
    } 
    
    spobj1->talkGibberish(); 
    
    spobj1.reset();
    return 0;
}

