#pragma once

#include "meshCalcConfig.h"
#include "3Vector.h"

class CLinkedListElement  
{
public:
    CLinkedListElement();
    CLinkedListElement(const C3Vector& v);
    CLinkedListElement(const C3Vector& v,CLinkedListElement* insertAfterThis);
    virtual ~CLinkedListElement();
    
    CLinkedListElement* previous;
    CLinkedListElement* next;
    bool flag;
    bool front;
    bool back;
    C3Vector point;
};
