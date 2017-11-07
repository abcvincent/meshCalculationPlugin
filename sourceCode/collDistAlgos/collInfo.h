#pragma once

#include "meshCalcConfig.h"
#include <vector>
#include "collNode.h"

class CCollInfo  
{
public:
    CCollInfo();
    CCollInfo(const float* cumulMeshVertices,int cumulMeshVerticesSize,const int* cumulMeshIndices,int cumulMeshIndicesSize,float maxTriSize,float theEdgeAngle,int maxTriCount);
    virtual ~CCollInfo();

    CCollInfo* copyYourself();
    void scale(float factor);
    bool isSimilar(const float* cumulMeshVertices,int cumulMeshVerticesSize,const int* cumulMeshIndices,int cumulMeshIndicesSize,float maxTriSize,float theEdgeAngle,int maxTriCount);
    unsigned char* getSerializationData(int& dataSize);
    void buildFromSerializationData(const unsigned char* data,const float* cumulMeshVertices,int cumulMeshVerticesSize,const int* cumulMeshIndices,int cumulMeshIndicesSize);
    bool getCutMesh(const C7Vector* tr,float** vertices,int* verticesSize,int** indices,int* indicesSize,int options);

    bool getCalcTriangleAt(C3Vector& a0,C3Vector& a1,C3Vector& a2,int ind);
    bool getCalcTriangleAt(float a0[3],float a1[3],float a2[3],int ind);
    float getCalcTriangleSurface(int ind);
    float getCalcPolygonSurface(int ind);

    CCollNode* collNode;
    std::vector<float> calcVertices;
    std::vector<int> calcIndices;
    std::vector<int> calcSegments;
    std::vector<std::vector<int> > calcPolygons;
    std::vector<float> cumulVertices;
    std::vector<int> cumulIndices;
    float maxTriangleSize;
    float edgeAngle;
    int maxTriangleCount;

private:
    void pushFloat(std::vector<unsigned char>& data,float value);
    void pushInt(std::vector<unsigned char>& data,int value);
    float readFloat(const unsigned char* data);
    int readInt(const unsigned char* data);
};
