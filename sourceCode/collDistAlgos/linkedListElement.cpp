#include "linkedListElement.h"

CLinkedListElement::CLinkedListElement()
{
    flag=false;
    front=false;
    back=false;
    previous=NULL;
    next=NULL;
}

CLinkedListElement::CLinkedListElement(const C3Vector& v)
{
    flag=false;
    front=false;
    back=false;
    point=v;
    previous=NULL;
    next=NULL;
}

CLinkedListElement::CLinkedListElement(const C3Vector& v,CLinkedListElement* insertAfterThis)
{
    flag=false;
    front=false;
    back=false;
    point=v;
    previous=insertAfterThis;
    next=insertAfterThis->next;
    if (next==NULL) // The list has length 1 (and will have length 2)
    {
        next=previous;
        insertAfterThis->next=this;
        insertAfterThis->previous=this;
    }
    else
    {
        insertAfterThis->next->previous=this;
        insertAfterThis->next=this;
    }
}

CLinkedListElement::~CLinkedListElement()
{
    if (previous!=NULL)
    {
        if (next!=previous)
        {   // There are more than 2 elements left.
            previous->next=next;
            next->previous=previous;
        }
        else
        {   // There are 2 elements left. We remove one of them
            previous->next=NULL;
            previous->previous=NULL;
        }
    }
}
