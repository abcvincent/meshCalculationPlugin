#pragma once

#include "meshCalcConfig.h"
#include <vector>
#include "kdTreeNode.h"
#include "3Vector.h"

class CKdTreeInfo : public CKdTreeNode
{
public:
    CKdTreeInfo(const float* pts,int ptCnt,const unsigned char* theColorOrColors,bool individualPointColors,float distTolerance);
    virtual ~CKdTreeInfo();

protected:
};
