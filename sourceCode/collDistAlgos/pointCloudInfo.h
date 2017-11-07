#pragma once

#include "meshCalcConfig.h"
#include <vector>
#include "pointCloudNode.h"
#include "3Vector.h"
#include "4X4Matrix.h"
#include "collInfo.h"

class COctreeInfo;

class CPointCloudInfo : public CPointCloudNode
{
    friend class COctreeInfo;
public:
    CPointCloudInfo();
    CPointCloudInfo(const float* relPoints,int ptCnt,float maxCellSize,int maxPtsInCell,const unsigned char* theColorOrColors,bool individualPointColors,float distTolerance);
    virtual ~CPointCloudInfo();

    void insertPoints(const float* relPoints,int ptCnt,const unsigned char* theColorOrColors,bool individualPointColors);
    void insertPointsWithDuplicateTolerance(const float* relPoints,int ptCnt,const unsigned char* theColorOrColors,bool individualPointColors,float distTolerance);
    bool removePoints(const float* relPoints,int ptCnt,float distTolerance,int& removedCnt);
    bool removeOctree(const C4X4Matrix& pointCloudPCTM,COctreeInfo* octreeInfo,const C4X4Matrix& octreePCTM,int& removedCnt);
    bool intersectPoints(const float* relPoints,int ptCnt,float distTolerance);

    bool getDistanceToShapeIfSmaller(CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& pcPCTM,const C4X4Matrix& collNodePCTM,float ray[7],long long int& thisCacheValue,int& otherCacheValue);
    bool getDistanceToPointIfSmaller(const C4X4Matrix& pointCloudPCTM,const C3Vector& absPoint,float ray[7],long long int& cacheValue);
    bool getDistanceToPointCloudIfSmaller(const CPointCloudInfo* otherPc,const C4X4Matrix& thisPcPCTM,const C4X4Matrix& otherPcPCTM,float ray[7],long long int& thisCacheValue,long long int& otherCacheValue);
    float* getPointsFromCache(const C4X4Matrix& pointCloudPCTM,const long long int cacheValue,int& ptCnt,C4X4Matrix& ptsRetToThisM);

    bool getProxSensorDistanceIfSmaller(const C4X4Matrix& pointCloudPCTM,float& dist,const float* planes,int planesSize,const float* planesOutside,int planesOutsideSize,C3Vector& detectPoint,bool fast,void* theOcclusionCheckCallback);

    CPointCloudInfo* copyYourself();
    void scale(float factor);
    unsigned char* getSerializationData(int& dataSize);
    void buildFromSerializationData(const unsigned char* data);
    int getNonEmptyCellCount();
    float* getOctreeDebugCorners(int& cubeCnt);
    void getPointData(std::vector<float>& pointPositionsAndColors);
    float* getPointData(int& pointCnt);
    void getPartialPointData(std::vector<float>& pointPositionsAndColors,float ratio);
    float* getPartialPointData(int& pointCnt,float ratio);

protected:
    float _boxSize;
    float _maxCellSize;
    int _maxPointCntInCell;
    C3Vector _boxPosition;
};
