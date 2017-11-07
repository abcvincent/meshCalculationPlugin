#pragma once

#include "meshCalcConfig.h"
#include <vector>
#include "3Vector.h"
#include "collInfo.h"
#include "pointCloudNode.h"

class COctreeNode
{
public:
    COctreeNode();
    COctreeNode(const std::vector<float>& relPoints,float cellSize,float thisBoxSize,const C3Vector boxCenter,const std::vector<unsigned char>& theColorOrColors,bool individualPointColors,const std::vector<unsigned int>& theTagOrTags);

    virtual ~COctreeNode();
    COctreeNode* copyYourself();

    void insertPoints(const std::vector<float>& relPoints,float cellSize,float thisBoxSize,const C3Vector boxCenter,const std::vector<unsigned char>& theColorOrColors,bool individualPointColors,const std::vector<unsigned int>& theTagOrTags);

    bool insertShape(const C4X4Matrix& octreeInfoCTM,CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& collInfoCTM,float cellSize,float thisBoxSize,const C3Vector boxCenter,const unsigned char theColor[3],const unsigned int theTag);
    static COctreeNode* insertShapeForNonExistingNode(const C4X4Matrix& octreeInfoCTM,CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& collInfoCTM,float cellSize,float thisBoxSize,const C3Vector boxCenter,const unsigned char theColor[3],const unsigned int theTag);

    bool insertOctree(const C4X4Matrix& octreeInfoCTM,const COctreeNode* octree2Node,const C4X4Matrix& octree2InfoCTM,float cellSize,float thisBoxSize,const C3Vector boxCenter,float otherBoxSize,const C3Vector octree2NodeBoxCenter,const unsigned char theColor[3],const unsigned int theTag);
    static COctreeNode* insertOctreeForNonExistingNode(const C4X4Matrix& octreeInfoCTM,const COctreeNode* octree2Node,const C4X4Matrix& octree2InfoCTM,float cellSize,float thisBoxSize,const C3Vector boxCenter,float otherBoxSize,const C3Vector octree2NodeBoxCenter,const unsigned char theColor[3],const unsigned int theTag);

    bool removeVoxelsFromPoints(const std::vector<float>& relPoints,float thisBoxSize,const C3Vector boxCenter);
    bool removeVoxelsFromShape(const C4X4Matrix& octreeInfoCTM,CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& collInfoCTM,float thisBoxSize,const C3Vector boxCenter);
    bool removeVoxelsFromOctree(const C4X4Matrix& octreeInfoCTM,const COctreeNode* octree2Node,const C4X4Matrix& octree2InfoCTM,float thisBoxSize,const C3Vector boxCenter,float otherBoxSize,const C3Vector octree2NodeBoxCenter);

    bool checkCollisionWithShape(const C4X4Matrix& octreeInfoCTM,CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& collInfoCTM,float cellSize,float thisBoxSize,const C3Vector boxCenter);
    bool checkCollisionWithOctree(const C4X4Matrix& octreeInfoCTM,const COctreeNode* octree2Node,const C4X4Matrix& octree2InfoCTM,float cellSize,float thisBoxSize,const C3Vector boxCenter,float otherBoxSize,const C3Vector octree2NodeBoxCenter);
    bool checkCollisionWithSinglePoint(const C3Vector& relPoint,float thisBoxSize,unsigned int* theTag,long long int thisLocation,long long int* location);
    bool checkCollisionWithSeveralPoints(const std::vector<float>& pointsRelToParentBox,const C3Vector& thisBoxPosRelToParentBox,float thisBoxSize);
    bool checkCollisionWithPointCloud(const C4X4Matrix& octreeInfoCTM,const CPointCloudNode* pointCloudNode,const C4X4Matrix& pointCloudInfoCTM,float cellSize,float thisBoxSize,const C3Vector boxCenter,float otherBoxSize,const C3Vector pointCloudNodeBoxCenter);

    bool getDistanceToShapeIfSmaller(CCollNode* collNode,CCollInfo* collInfo,const C4X4Matrix& octreeInfoCTM,const C4X4Matrix& collnodePCTM,float thisBoxSize,const C3Vector& totShift,long long int& thisCacheValue,long long int thisCachePos,int& otherCacheValue,C3Vector& detectPt1,C3Vector& detectPt2,float& dist);
    bool getDistanceToPointIfSmaller(const C3Vector& pointRelToOctreeCenter,float boxSize,const C3Vector& boxPosRelToOctreeCenter,float& dist,long long int& cacheValue,long long int cachePos,C3Vector& detectedPointRelToOctreeCenter);
    bool getDistanceToOctreeIfSmaller(const COctreeNode* otherNode,const C4X4Matrix& m1,const C4X4Matrix& m2,const C3Vector& totShift1,const C3Vector& totShift2,float box1Size,float box2Size,long long int& cache1Value,long long int cache1Pos,long long int& cache2Value,long long int cache2Pos,C3Vector& detectPt1,C3Vector& detectPt2,bool usesSpheres,float& dist,bool useApproximateDistCalc);
    bool getDistanceToPointCloudIfSmaller(const CPointCloudNode* otherNode,const C4X4Matrix& m1,const C4X4Matrix& m2,const C3Vector& totShift1,const C3Vector& totShift2,float box1Size,float box2Size,long long int& cache1Value,long long int cache1Pos,long long int& cache2Value,long long int cache2Pos,C3Vector& detectPt1,C3Vector& detectPt2,float& dist);
    bool getCellFromCache(const C3Vector& totShift,float boxSize,long long int cacheValue,C3Vector& totalShift_ret);

    bool getRayProxSensorDistanceIfSmaller(const C4X4Matrix& octreeM,const C3Vector& totShift,float boxSize,float& dist,const C3Vector& lp,const C3Vector& lvFar,float cosAngle,C3Vector& detectPoint,bool fast,bool frontFace,bool backFace,C3Vector& triNormalNotNormalized,void* theOcclusionCheckCallback);
    bool getProxSensorDistanceIfSmaller(const C4X4Matrix& octreeM,const C3Vector& totShift,float boxSize,float& dist,const float* planes,int planesSize,const float* planesOutside,int planesOutsideSize,float cosAngle,C3Vector& detectPoint,bool fast,bool frontFace,bool backFace,C3Vector& triNormalNotNormalized,void* theOcclusionCheckCallback);

    void getSerializationData(std::vector<unsigned char>& data);
    void buildFromSerializationData(const unsigned char* data,int& ptr);
    void buildFromSerializationData_OLD(const unsigned char* data,int& ptr);
    void buildFromSerializationData_OLD2(const unsigned char* data,int& ptr);

    void getOctreeVoxels(std::vector<float>& data,float parentBoundingBoxSize,const C3Vector& boxCenter);
    void getOctreeCubeCorners(std::vector<float>& data,float parentBoundingBoxSize,const C3Vector& boxCenter);
    void getOctreeDebugCorners(std::vector<float>& data,float parentBoundingBoxSize,const C3Vector& boxCenter);

    static void addFloatToData(std::vector<unsigned char>& data,float d);
    static void addIntToData(std::vector<unsigned char>& data,int d);
    static float getFloatFromData(const unsigned char* data,int& ptr);
    static int getIntFromData(const unsigned char* data,int& ptr);

    // Variables that need to be serialized and copied:
    COctreeNode** childNodes;
    unsigned char nonEmpty;
    unsigned char color[3];
    unsigned int tag;
};
