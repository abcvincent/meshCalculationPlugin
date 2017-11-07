#include "kdTreeNode.h"
#include <cstddef>

CKdTreeNode::CKdTreeNode()
{
    childNodes[0]=NULL;
    childNodes[1]=NULL;
    pointSet=false;
    fakePoint=false;
}

/*
CKdTreeNode::CKdTreeNode(const std::vector<float>& relPoints,float cellSize,float thisBoxSize,const C3Vector boxCenter,const std::vector<unsigned char>& theColorOrColors,bool individualPointColors,const std::vector<unsigned int>& theTagOrTags)
{
    // the points are relative to the parent reference frame, which is aligned with this one (i.e. just a shift)
    float thisHalfBoxSizeAugmented=thisBoxSize*0.50001f;
    nonEmpty=false;

    if (thisBoxSize<cellSize*1.1f)
    { // we arrived at the leaf
        childNodes=NULL;
        for (size_t i=0;i<relPoints.size()/3;i++)
        {
            C3Vector pt(&relPoints[3*i]);
            pt-=boxCenter;
            if ( (fabs(pt(0))<thisHalfBoxSizeAugmented)&&(fabs(pt(1))<thisHalfBoxSizeAugmented)&&(fabs(pt(2))<thisHalfBoxSizeAugmented) )
            {
                nonEmpty=true;
                if (individualPointColors)
                {
                    color[0]=theColorOrColors[3*i+0];
                    color[1]=theColorOrColors[3*i+1];
                    color[2]=theColorOrColors[3*i+2];
                    tag=theTagOrTags[i];
                }
                else
                {
                    color[0]=theColorOrColors[0];
                    color[1]=theColorOrColors[1];
                    color[2]=theColorOrColors[2];
                    tag=theTagOrTags[0];
                }
            }
        }
    }
    else
    { // we have to continue exploring
        std::vector<float> childPts;
        std::vector<unsigned char> childPtColors;
        std::vector<unsigned int> childPtTags;
        for (size_t i=0;i<relPoints.size()/3;i++)
        {
            C3Vector pt(&relPoints[3*i]);
            pt-=boxCenter;
            if ( (fabs(pt(0))<thisHalfBoxSizeAugmented)&&(fabs(pt(1))<thisHalfBoxSizeAugmented)&&(fabs(pt(2))<thisHalfBoxSizeAugmented) )
            {
                childPts.push_back(pt(0));
                childPts.push_back(pt(1));
                childPts.push_back(pt(2));
                if (individualPointColors)
                {
                    childPtColors.push_back(theColorOrColors[3*i+0]);
                    childPtColors.push_back(theColorOrColors[3*i+1]);
                    childPtColors.push_back(theColorOrColors[3*i+2]);
                    childPtTags.push_back(theTagOrTags[i]);
                }
            }
        }

        if (childPts.size()>0)
        {
            if (!individualPointColors)
            {
                childPtColors.push_back(theColorOrColors[0]);
                childPtColors.push_back(theColorOrColors[1]);
                childPtColors.push_back(theColorOrColors[2]);
                childPtTags.push_back(theTagOrTags[0]);
            }
            childNodes=new CKdTreeNode* [8];
            for (size_t i=0;i<8;i++)
                childNodes[i]=new CKdTreeNode(childPts,cellSize,thisBoxSize*0.5,childNodeTraversalShifts[i]*thisBoxSize,childPtColors,individualPointColors,childPtTags);
        }
        else
        { // we stop exploration. We are not in a leaf node, but we don't have any points in this node anymore
            childNodes=NULL;
        }
    }
}
    */

void CKdTreeNode::invalidateTooClosePoints(std::vector<SKDPoint>& allPoints,const std::vector<int>& pointIndices,float distTolerance,int axis,int& invalidateCnt)
{
    if (!pointSet)
        return;
    std::vector<int> lowerPointIndices;
    std::vector<int> higherPointIndices;
    float distTolSquared=distTolerance*distTolerance;
    for (size_t i=0;i<pointIndices.size();i++)
    {
        if (allPoints[pointIndices[i]].valid)
        {
            C3Vector dv=allPoints[pointIndices[i]].point-point;
            float dd=pow(dv(0),2.0)+pow(dv(1),2.0)+pow(dv(2),2.0);
            if ( (dd<distTolSquared)&&(!fakePoint) )
            {
                allPoints[pointIndices[i]].valid=false; // that point is too close
                invalidateCnt++;
            }
            else
            {
                if (dv(axis)>0)
                {
                    higherPointIndices.push_back(pointIndices[i]);
                    if (dv(axis)<distTolerance)
                        lowerPointIndices.push_back(pointIndices[i]);
                }
                else
                {
                    lowerPointIndices.push_back(pointIndices[i]);
                    if (dv(axis)>-distTolerance)
                        higherPointIndices.push_back(pointIndices[i]);
                }
            }
        }
    }
    axis++;
    if (axis==3)
        axis=0;
    if ( (childNodes[0]!=NULL)&&(lowerPointIndices.size()>0) )
        childNodes[0]->invalidateTooClosePoints(allPoints,lowerPointIndices,distTolerance,axis,invalidateCnt);
    if ( (childNodes[1]!=NULL)&&(higherPointIndices.size()>0) )
        childNodes[1]->invalidateTooClosePoints(allPoints,higherPointIndices,distTolerance,axis,invalidateCnt);
}

void CKdTreeNode::insertPointsIntoEmptyNode(std::vector<SKDPoint>& allPoints,const std::vector<int>& pointIndices,float distTolerance,int axis)
{
    // We take the first point that is valid, then remove it:
    for (size_t i=0;i<pointIndices.size();i++)
    {
        if (allPoints[pointIndices[i]].valid)
        {
            allPoints[pointIndices[i]].valid=false;
            point=allPoints[pointIndices[i]].point;
            color[0]=allPoints[pointIndices[i]].color[0];
            color[1]=allPoints[pointIndices[i]].color[1];
            color[2]=allPoints[pointIndices[i]].color[2];
            pointSet=true;
            fakePoint=allPoints[pointIndices[i]].fake;
            break;
        }
    }
    if (!pointSet)
        return;

    float distTolSquared=distTolerance*distTolerance;
    std::vector<int> lowerPointIndices;
    std::vector<int> higherPointIndices;
    for (size_t i=0;i<pointIndices.size();i++)
    {
        if (allPoints[pointIndices[i]].valid)
        {
            C3Vector v(allPoints[pointIndices[i]].point);
            C3Vector dv(v-point);
            float dd=pow(dv(0),2.0)+pow(dv(1),2.0)+pow(dv(2),2.0);
            if ( (dd>distTolSquared)||fakePoint )
            {
                if (dv(axis)<0.0)
                    lowerPointIndices.push_back(pointIndices[i]);
                else
                    higherPointIndices.push_back(pointIndices[i]);
            }
        }
    }
    axis++;
    if (axis==3)
        axis=0;
    if (higherPointIndices.size()>0)
    {
        childNodes[1]=new CKdTreeNode();
        childNodes[1]->insertPointsIntoEmptyNode(allPoints,higherPointIndices,distTolerance,axis);
    }
    if (lowerPointIndices.size()>0)
    {
        int invalidateCnt=0;
        if (childNodes[1]!=NULL)
            childNodes[1]->invalidateTooClosePoints(allPoints,lowerPointIndices,distTolerance,axis,invalidateCnt);
        if (lowerPointIndices.size()-invalidateCnt>0)
        {
            childNodes[0]=new CKdTreeNode();
            childNodes[0]->insertPointsIntoEmptyNode(allPoints,lowerPointIndices,distTolerance,axis);
        }
    }
}

void CKdTreeNode::getAllPointsAndColors(std::vector<float>& pts,std::vector<unsigned char>& cols)
{
    if (pointSet)
    {
        if (!fakePoint)
        {
            pts.push_back(point(0));
            pts.push_back(point(1));
            pts.push_back(point(2));
            cols.push_back(color[0]);
            cols.push_back(color[1]);
            cols.push_back(color[2]);
        }
        if (childNodes[0]!=NULL)
            childNodes[0]->getAllPointsAndColors(pts,cols);
        if (childNodes[1]!=NULL)
            childNodes[1]->getAllPointsAndColors(pts,cols);
    }
}

CKdTreeNode::~CKdTreeNode()
{
    if (childNodes[0]!=NULL)
        delete childNodes[0];
    if (childNodes[1]!=NULL)
        delete childNodes[1];
}

