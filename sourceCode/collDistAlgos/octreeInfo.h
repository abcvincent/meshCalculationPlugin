#pragma once

#include "meshCalcConfig.h"
#include <vector>
#include "octreeNode.h"
#include "pointCloudInfo.h"
#include "3Vector.h"
#include "collInfo.h"

class COctreeInfo : public COctreeNode
{
    friend class CPointCloudInfo;
public:
    COctreeInfo();
    // Following creates an octree based on points:
    COctreeInfo(const float* relPoints,int ptCnt,float cellSize,const unsigned char* theColorOrColors,bool individualPointColors,const unsigned int* theTagOrTags);

    virtual ~COctreeInfo();

    static COctreeInfo* createOctreeFromShape(const C4X4Matrix& octreePCTM,CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& collnodePCTM,float cellSize,const unsigned char theColor[3],unsigned int theTag);
    static COctreeInfo* createOctreeFromOctree(const C4X4Matrix& octreePCTM,COctreeInfo* octree2Info,const C4X4Matrix& octree2PCTM,float cellSize,const unsigned char theColor[3],unsigned int theTag);

    void insertPoints(const float* relPoints,int ptCnt,const unsigned char* theColorOrColors,bool individualPointColors,const unsigned int* theTagOrTags);
    void insertShape(const C4X4Matrix& octreePCTM,CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& collnodePCTM,bool noNeedToExtend,const unsigned char theColor[3],unsigned int theTag);
    void insertOctree(const C4X4Matrix& octreePCTM,COctreeInfo* octree2Info,const C4X4Matrix& octree2PCTM,bool noNeedToExtend,const unsigned char theColor[3],unsigned int theTag);

    bool removeVoxelsFromPoints(const float* relPoints,int ptCnt);
    bool removeVoxelsFromShape(const C4X4Matrix& octreePCTM,CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& collnodePCTM);
    bool removeVoxelsFromOctree(const C4X4Matrix& octreePCTM,COctreeInfo* octree2Info,const C4X4Matrix& octree2PCTM);

    bool checkCollisionWithShape(const C4X4Matrix& octreePCTM,CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& collnodePCTM);
    bool checkCollisionWithOctree(const C4X4Matrix& octreePCTM,COctreeInfo* octree2Info,const C4X4Matrix& octree2PCTM);
    bool checkCollisionWithSinglePoint(const C4X4Matrix& octreePCTM,const C3Vector& absPoint,unsigned int* theTag,unsigned long long int* location);
    bool checkCollisionWithSeveralPoints(const C4X4Matrix& octreePCTM,const float* absPoints,int ptCnt);
    bool checkCollisionWithPointCloud(const C4X4Matrix& octreePCTM,CPointCloudInfo* pointCloudInfo,const C4X4Matrix& pointCloudPCTM);

    bool getDistanceToShapeIfSmaller(CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& octreePCTM,const C4X4Matrix& collNodePCTM,float ray[7],long long int& thisCacheValue,int& otherCacheValue);
    bool getDistanceToPointIfSmaller(const C4X4Matrix& octreePCTM,const C3Vector& absPoint,float ray[7],long long int& cacheValue);
    bool getDistanceToOctreeIfSmaller(const COctreeInfo* otherOctree,const C4X4Matrix& thisOctreePCTM,const C4X4Matrix& otherOctreePCTM,float ray[7],long long int& thisCacheValue,long long int& otherCacheValue,bool weHaveSomeCoherency);
    bool getDistanceToPointCloudIfSmaller(const CPointCloudInfo* pointCloudInfo,const C4X4Matrix& octreePCTM,const C4X4Matrix& pointCloudPCTM,float ray[7],long long int& thisCacheValue,long long int& otherCacheValue);
    bool getCellFromCache(const C4X4Matrix& octreePCTM,const long long int cacheValue,float& cellSize,C4X4Matrix& cellRetToThisM);

    bool getRayProxSensorDistanceIfSmaller(const C4X4Matrix& octreePCTM,float& dist,const C3Vector& lp,const C3Vector& lvFar,float cosAngle,C3Vector& detectPoint,bool fast,bool frontFace,bool backFace,C3Vector& triNormalNotNormalized,void* theOcclusionCheckCallback);
    bool getProxSensorDistanceIfSmaller(const C4X4Matrix& octreePCTM,float& dist,const float* planes,int planesSize,const float* planesOutside,int planesOutsideSize,float cosAngle,C3Vector& detectPoint,bool fast,bool frontFace,bool backFace,C3Vector& triNormalNotNormalized,void* theOcclusionCheckCallback);

    COctreeInfo* copyYourself();
    void scale(float factor);
    unsigned char* getSerializationData(int& dataSize);
    void buildFromSerializationData(const unsigned char* data);

    void getOctreeVoxels(std::vector<float>& voxelPositionsAndColors);
    float* getOctreeVoxels(int& voxelCnt);
    void getOctreeCubeCorners(std::vector<float>& vertices);
    float* getOctreeDebugCorners(int& cubeCnt);

protected:
    float _boxSize;
    float _cellSize;
    C3Vector _boxPosition;
};
