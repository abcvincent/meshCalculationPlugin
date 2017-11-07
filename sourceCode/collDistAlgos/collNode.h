#pragma once

#include "meshCalcConfig.h"
#include "3Vector.h"
#include "4X4Matrix.h"
#include <vector>

class CCollNode  
{
public:
    CCollNode();
    CCollNode(const std::vector<float>& vertices,const std::vector<int>& triangles,const std::vector<int>& tIndex,const std::vector<int>& segments,const std::vector<int>& sIndex,int triNumberInBox);
    virtual ~CCollNode();
    CCollNode* copyYourself();

    void getSerializationData(std::vector<unsigned char>& data);
    void buildFromSerializationData(const unsigned char* data,int& ptr);

    static C4X4Matrix divideElements(C3Vector& s,const std::vector<float>& vertices,const std::vector<int>& triangles,const std::vector<int>& tIndex,const std::vector<int>& segments,const std::vector<int>& sIndex,
        std::vector<int>& tIndexLeft,std::vector<int>& sIndexLeft,
        std::vector<int>& tIndexRight,std::vector<int>& sIndexRight);

    float getFloatFromData(const unsigned char* data,int& ptr);
    int getIntFromData(const unsigned char* data,int& ptr);
    unsigned short getWordFromData(const unsigned char* data,int& ptr);

    void addFloatToData(std::vector<unsigned char>& data,float d);
    void addIntToData(std::vector<unsigned char>& data,int d);
    void addWordToData(std::vector<unsigned char>& data,unsigned short d);

    void scaleYourself(float scalingFactor);

    void populateWithSegments(const std::vector<float>& vertices,const std::vector<int>& segments,const std::vector<int>& sIndex);

    // Variables that need to be serialized and copied:
    CCollNode* leftCollNode;
    CCollNode* rightCollNode;
    C3Vector size;
    C4X4Matrix transformMatrix;
    std::vector<int>* leafTriangles;
    std::vector<int>* leafSegments;
    std::vector<int>* leafPolygons;
    unsigned short numberOfTrianglesInBox;
};
