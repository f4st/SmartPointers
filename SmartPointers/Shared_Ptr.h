//
//  Shared_Ptr.h
//  SmartPointers
//
//  Created by Mykola Farion on 8/14/13.
//  Copyright (c) 2013 Mykola Farion. All rights reserved.
//

#ifndef __SmartPointers__Shared_Ptr__
#define __SmartPointers__Shared_Ptr__

// NOTE mfarion,
// Confused with questions about implementation
// probably mislead smth about shared & weak pointers

#include <iostream>
 
struct refCounter
{
    int ref_count;
    int weak_count;
};

class Shared_Ptr
{
public:

    explicit Shared_Ptr(int* p = 0):ptr(p)
    {
        refCnt = new struct refCounter();
        refCnt->ref_count = 1;
        refCnt->weak_count = 0; //  why we need weak ????
    }
    
    Shared_Ptr(Shared_Ptr & sp2)
    {
        // Simple assign of sp2 that is given in constructor with increasing own
        // ref_count or need smth to add?
        ptr = sp2.ptr;
        refCnt = sp2.refCnt;
        refCnt->ref_count = refCnt->ref_count+1;
    }
    
    ~Shared_Ptr()
    {
        // Weak depends here???
        if(refCnt->ref_count == 1) {
            if(ptr != NULL)
                delete ptr;
            delete refCnt;
        } else {
            ptr = NULL;
            refCnt->ref_count = refCnt->ref_count-1;
        }
    }
    
    
    Shared_Ptr& operator = (Shared_Ptr& sp2)
    {
        if(ptr != sp2.ptr)
        {
            if(ptr != NULL)
            {
                if(refCnt->ref_count == 1)
                {
                    delete ptr;
                    delete refCnt;
                    ptr = NULL;
                    refCnt = NULL;
                } else {
                    refCnt->ref_count = refCnt->ref_count-1;
                }
            }
            
            ptr = sp2.ptr;
            refCnt = sp2.refCnt;
            sp2.refCnt->ref_count = sp2.refCnt->ref_count+1;
        }
        return *this;
    }
    
    void reset(int* p = 0)
    {
        if (p == 0) {
            delete ptr;
            delete refCnt;
            refCnt = NULL;
            ptr = NULL;
        } else {
            if(refCnt->ref_count == 1)
            {
                delete ptr;
                delete refCnt;
                ptr = NULL;
                refCnt = NULL;
            } else {
                refCnt->ref_count = refCnt->ref_count-1;
            }
            refCnt = new struct refCounter();
            ptr = p;
            refCnt->ref_count = 1;
            refCnt->weak_count = 0;
        }
    }
    
private:
    int* ptr; 
    refCounter* refCnt;
};


#endif /* defined(__SmartPointers__Shared_Ptr__) */
