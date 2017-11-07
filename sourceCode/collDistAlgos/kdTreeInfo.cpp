#include "kdTreeInfo.h"
#include <cstddef>

CKdTreeInfo::CKdTreeInfo(const float* pts,int ptCnt,const unsigned char* theColorOrColors,bool individualPointColors,float distTolerance)
{
    // Place points and colors in a new vector, containing also point validity
    std::vector<int> thePointIndices;
    std::vector<SKDPoint> allPoints;
    C3Vector maxV;
    C3Vector minV;
    for (int i=0;i<ptCnt;i++)
    {
        SKDPoint kdpt;
        kdpt.point=C3Vector(pts+3*i);
        if (i==0)
        {
            maxV=kdpt.point;
            minV=kdpt.point;
        }
        else
        {
            maxV.keepMax(kdpt.point);
            minV.keepMin(kdpt.point);
        }
        if (individualPointColors)
        {
            kdpt.color[0]=theColorOrColors[3*i+0];
            kdpt.color[1]=theColorOrColors[3*i+1];
            kdpt.color[2]=theColorOrColors[3*i+2];
        }
        else
        {
            kdpt.color[0]=theColorOrColors[0];
            kdpt.color[1]=theColorOrColors[1];
            kdpt.color[2]=theColorOrColors[2];
        }
        kdpt.valid=true;
        kdpt.fake=false;
        allPoints.push_back(kdpt);
        thePointIndices.push_back(i);
    }

    // Order the points more "randomly", using Durstfeld's Method:
    for (int i=0;i<ptCnt-1;i++)
    {
        size_t r=size_t(float(rand())*float(ptCnt-2-i)/float(RAND_MAX));
        int last=thePointIndices[ptCnt-1-i];
        thePointIndices[ptCnt-1-i]=thePointIndices[r];
        thePointIndices[r]=last;
    }

    // We now insert 7 fake points that are computed to be in the middle x, y and z (median x,y and z would be too expensive):
    SKDPoint kdpt;
    kdpt.point=(minV+maxV)*0.5;
    kdpt.valid=true;
    kdpt.fake=true;
    for (size_t i=0;i<7;i++)
    {
        thePointIndices.insert(thePointIndices.begin(),1,thePointIndices.size());
        allPoints.push_back(kdpt);
    }

    // We take the first point in the random list, then remove it:
    point=allPoints[thePointIndices[0]].point;
    color[0]=allPoints[thePointIndices[0]].color[0];
    color[1]=allPoints[thePointIndices[0]].color[1];
    color[2]=allPoints[thePointIndices[0]].color[2];
    pointSet=true;
    fakePoint=allPoints[thePointIndices[0]].fake;
    allPoints[thePointIndices[0]].valid=false;

    float distTolSquared=distTolerance*distTolerance;
    std::vector<int> lowerPointIndices;
    std::vector<int> higherPointIndices;
    for (size_t i=0;i<thePointIndices.size();i++)
    {
        C3Vector v(allPoints[thePointIndices[i]].point);
        C3Vector dv(v-point);
        float dd=pow(dv(0),2.0)+pow(dv(1),2.0)+pow(dv(2),2.0);
        if (dd>distTolSquared)
        {
            if (dv(0)<0.0)
                lowerPointIndices.push_back(thePointIndices[i]);
            else
                higherPointIndices.push_back(thePointIndices[i]);
        }
    }
    if (higherPointIndices.size()>0)
    {
        childNodes[1]=new CKdTreeNode();
        childNodes[1]->insertPointsIntoEmptyNode(allPoints,higherPointIndices,distTolerance,1);
    }
    if (lowerPointIndices.size()>0)
    {
        int invalidateCnt=0;
        if (childNodes[1]!=NULL)
            childNodes[1]->invalidateTooClosePoints(allPoints,lowerPointIndices,distTolerance,1,invalidateCnt);
        if (lowerPointIndices.size()-invalidateCnt>0)
        {
            childNodes[0]=new CKdTreeNode();
            childNodes[0]->insertPointsIntoEmptyNode(allPoints,lowerPointIndices,distTolerance,1);
        }
    }
}

CKdTreeInfo::~CKdTreeInfo()
{
}

