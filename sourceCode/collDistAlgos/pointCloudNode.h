#pragma once

#include "meshCalcConfig.h"
#include <vector>
#include "3Vector.h"
#include "4X4Matrix.h"
#include "collInfo.h"

struct SIndexShift {
    int index1;
    C3Vector shift1;
    int index2;
    C3Vector shift2;
    bool operator< (const SIndexShift& m) const {return false;}
};

const C3Vector childNodeTraversalShifts[8]={
    C3Vector(-0.25f,-0.25f,-0.25f),
    C3Vector(+0.25f,-0.25f,-0.25f),
    C3Vector(-0.25f,+0.25f,-0.25f),
    C3Vector(+0.25f,+0.25f,-0.25f),
    C3Vector(-0.25f,-0.25f,+0.25f),
    C3Vector(+0.25f,-0.25f,+0.25f),
    C3Vector(-0.25f,+0.25f,+0.25f),
    C3Vector(+0.25f,+0.25f,+0.25f)
};

class COctreeNode;

class CPointCloudNode
{
    friend class COctreeNode;
public:
    CPointCloudNode();
    CPointCloudNode(const std::vector<float>& pointsRelToParentBox,std::vector<bool>& usedPoints,std::vector<int>& usedPointsIndices,float maxCellSize,int maxPointCountInCell,float boxSize,const C3Vector& boxCenter,const std::vector<unsigned char>& theColorOrColors,bool individualPointColors);
    virtual ~CPointCloudNode();

    void insertPoints(const std::vector<float>& pointsRelToParentBox,std::vector<bool>& usedPoints,std::vector<int>& usedPointsIndices,float maxCellSize,int maxPointCountInCell,float boxSize,const C3Vector& boxCenter,const std::vector<unsigned char>& theColorOrColors,bool individualPointColors);
    bool removePoints(const std::vector<float>& pointsRelToParentBox,float boxSize,const C3Vector& boxCenter,float distTolerance,int& removedCnt);
    bool removeOctree(const C4X4Matrix& pointCloudInfoCTM,const COctreeNode* octreeNode,const C4X4Matrix& octreeInfoCTM,float thisBoxSize,const C3Vector& totShift,float otherBoxSize,const C3Vector& octreeTotShift,int& removedCnt);
    void tagPointsAsDuplicate(const std::vector<float>& pointsRelToParentBox,const std::vector<int>& duplicateFlagIndices,std::vector<bool>& duplicateFlags,float boxSize,const C3Vector& boxCenter,float distTolerance);

    bool intersectPoints(const std::vector<float>& pointsRelToParentBox,float boxSize,const C3Vector& boxCenter,float distTolerance);

    bool getDistanceToShapeIfSmaller(CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& pcInfoCTM,const C4X4Matrix& collnodePCTM,float thisBoxSize,const C3Vector& totShift,long long int& thisCacheValue,long long int thisCachePos,int& otherCacheValue,C3Vector& detectPt1,C3Vector& detectPt2,float& dist);
    bool getDistanceToPointIfSmaller(const C3Vector& pointRelToPointCloudCenter,float boxSize,const C3Vector& boxPosRelToPointCloudCenter,float& dist,long long int& cacheValue,long long int cachePos,C3Vector& detectedPointRelToPointCloudCenter);
    bool getDistanceToPointCloudIfSmaller(const CPointCloudNode* otherNode,const C4X4Matrix& m1,const C4X4Matrix& m2,const C3Vector& totShift1,const C3Vector& totShift2,float box1Size,float box2Size,long long int& cache1Value,long long int cache1Pos,long long int& cache2Value,long long int cache2Pos,C3Vector& detectPt1,C3Vector& detectPt2,float& dist);
    float* getPointsFromCache(const C3Vector& totShift,float boxSize,long long int cacheValue,int& ptCnt,C3Vector& totalShift_ret);

    bool getProxSensorDistanceIfSmaller(const C4X4Matrix& pointCloudM,const C3Vector& totShift,float boxSize,float& dist,const float* planes,int planesSize,const float* planesOutside,int planesOutsideSize,C3Vector& detectPoint,bool fast,void* theOcclusionCheckCallback);


    CPointCloudNode* copyYourself();
    void scaleYourself(float scalingFactor);
    void getSerializationData(std::vector<unsigned char>& data);
    void buildFromSerializationData(const unsigned char* data,int& ptr);
    void buildFromSerializationDataOLD(const unsigned char* data,int& ptr);
    int getNonEmptyCellCount();
    void getOctreeDebugCorners(std::vector<float>& data,float parentBoundingBoxSize,const C3Vector& boxCenter);
    void getPointData(std::vector<float>& data,float parentBoundingBoxSize,const C3Vector& boxCenter);
    void getPartialPointData(float ratio,std::vector<float>& data,float parentBoundingBoxSize,const C3Vector& boxCenter);

    static void addFloatToData(std::vector<unsigned char>& data,float d);
    static void addIntToData(std::vector<unsigned char>& data,int d);
    static float getFloatFromData(const unsigned char* data,int& ptr);
    static int getIntFromData(const unsigned char* data,int& ptr);

    // Variables that need to be serialized and copied:
    CPointCloudNode** childNodes;
    std::vector<float> points;
    std::vector<unsigned char> colors;
};
