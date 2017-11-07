#pragma once

#include "meshCalcConfig.h"
#include <vector>
#include "3Vector.h"

struct SKDPoint {
    C3Vector point;
    unsigned char color[3];
    bool valid;
    bool fake;
};

class CKdTreeNode
{
public:
    CKdTreeNode();
//  CKdTreeNode(const std::vector<float>& relPoints,float cellSize,float thisBoxSize,const C3Vector boxCenter,const std::vector<unsigned char>& theColorOrColors,bool individualPointColors,const std::vector<unsigned int>& theTagOrTags);

    virtual ~CKdTreeNode();

    void invalidateTooClosePoints(std::vector<SKDPoint>& allPoints,const std::vector<int>& pointIndices,float distTolerance,int axis,int& invalidateCnt);
    void insertPointsIntoEmptyNode(std::vector<SKDPoint>& allPoints,const std::vector<int>& pointIndices,float distTolerance,int axis);
    void getAllPointsAndColors(std::vector<float>& pts,std::vector<unsigned char>& cols);

    // Variables that need to be serialized and copied:
    CKdTreeNode* childNodes[2];
    C3Vector point;
    unsigned char color[3];
    bool pointSet;
    bool fakePoint;
};
