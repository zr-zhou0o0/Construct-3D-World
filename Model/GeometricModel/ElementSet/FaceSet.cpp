/*************************************************************************
【文件名】                 FaceSet.cpp
【功能模块和目的】         面集类定义
【开发者及日期】           周子睿 2024/8/7
【更改记录】               无
*************************************************************************/

#include <algorithm>
#include <limits.h>
#include <numeric>
#include"../Point/Point.hpp"
#include"../Element/Face.hpp"

#include"../PointSet/PointSet.hpp"
#include"ElementSet.hpp"

#include "FaceSet.hpp"

using namespace std;

/*************************************************************************
【函数名称】       FaceSet::FaceSet
【函数功能】       构造函数，初始化面集类
【入口参数】       std::shared_ptr<PointSet> pPointSet
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
FaceSet::FaceSet(std::shared_ptr<PointSet> pPointSet) : 
ElementSet<3>(pPointSet), m_pPointSet(pPointSet) {}

/*************************************************************************
【函数名称】       FaceSet::FaceSet
【函数功能】       构造函数，初始化面集类
【入口参数】       std::shared_ptr<PointSet> pPointSet, 
                   std::vector<std::array<unsigned int, 3>>& NewFaceSet
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
FaceSet::FaceSet(std::shared_ptr<PointSet> pPointSet, 
    const std::vector<std::array<unsigned int, 3>>& NewFaceSet) : 
    ElementSet<3>(pPointSet), m_FaceSet(NewFaceSet), 
    m_pPointSet(pPointSet) {
}

/*************************************************************************
【函数名称】       FaceSet拷贝构造函数
【函数功能】       创建FaceSet对象
【参数】           const FaceSet& Source
【返回值】         无
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
FaceSet::FaceSet(const FaceSet& Source) : 
ElementSet<3>(Source), m_FaceSet(Source.m_FaceSet), 
m_pPointSet(Source.m_pPointSet) {
}

/*************************************************************************
【函数名称】       FaceSet赋值运算符重载
【函数功能】       创建FaceSet对象
【参数】           const FaceSet& Source
【返回值】         FaceSet
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
FaceSet& FaceSet::operator=(const FaceSet& Source)
{
    if (this != &Source) {
        ElementSet<3>::operator=(Source);
        m_FaceSet = Source.m_FaceSet;
        m_pPointSet = Source.m_pPointSet;
    }
    return *this;
}

/*************************************************************************
【函数名称】       FaceSet::GetElementSet
【函数功能】       获取面集
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<std::array<unsigned int, 3>> 面集
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
std::vector<std::array<unsigned int, 3>> FaceSet::GetElementSet() const {
    return m_FaceSet;
}

/*************************************************************************
【函数名称】       FaceSet::GetElement
【函数功能】       获取指定索引的面
【入口参数】       const unsigned int uIndex
【出口参数】       无
【返回值】         std::vector<std::array<unsigned int, 3>> 面
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
std::vector<std::array<unsigned int, 3>> FaceSet::GetElement(
    unsigned int uIndex) const {
    if (uIndex != UINT_MAX 
        && static_cast<size_t>(uIndex) < (m_FaceSet.size())) {
        return { m_FaceSet[uIndex] };
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       FaceSet::GetElementSetIndex
【函数功能】       获取面集索引
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<unsigned int> 面集索引
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
std::vector<unsigned int> FaceSet::GetElementSetIndex() const {
    std::vector<unsigned int> FaceSetIndex(GetTotalCount());
    std::iota(FaceSetIndex.begin(), FaceSetIndex.end(), 0);
    return FaceSetIndex;
}

/*************************************************************************
【函数名称】       FaceSet::FindElement
【函数功能】       查找面
【入口参数】       const Element<3>& NewFace
【出口参数】       无
【返回值】         unsigned int 面的索引
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
unsigned int FaceSet::FindElement(const Element<3>& NewFace) const {
    const Face* AFace = dynamic_cast<const Face*>(&NewFace);
    if (!AFace) {
        throw ExceptionTypeMismatch();
    }
    else if (!AFace->IsValid()) {
        throw ExceptionCoincidentPoints();
    }
    else {
        for (unsigned int i = 0; i < m_FaceSet.size(); ++i) {
            if (AFace->IsSame
            (Face({ m_pPointSet->GetPointByIndex(m_FaceSet[i][0]),
                m_pPointSet->GetPointByIndex(m_FaceSet[i][1]),
                m_pPointSet->GetPointByIndex(m_FaceSet[i][2]) }))) {
                return i;  // 返回第一个重复的 AFace 的索引
            }
        }
    }
    return UINT_MAX;  // 如果没有找到重复的 face，返回 UINT_MAX
}

/*************************************************************************
【函数名称】       FaceSet::Delete
【函数功能】       删除面（通过索引）
【入口参数】       const unsigned int uIndex
【出口参数】       无
【返回值】         bool 删除是否成功
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
bool FaceSet::Delete(const unsigned int uIndex) {
    if (uIndex != UINT_MAX && uIndex < m_FaceSet.size()) {
        m_FaceSet.erase(m_FaceSet.begin() + uIndex);
        return true;
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       FaceSet::Delete
【函数功能】       删除面（通过点索引）
【入口参数】       const std::array<unsigned int, 3>& PointIndex
【出口参数】       无
【返回值】         bool 删除是否成功
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
bool FaceSet::Delete(const std::array<unsigned int, 3>& PointIndex) {
    auto AFace = std::find(m_FaceSet.begin(), m_FaceSet.end(), PointIndex);
    if (AFace != m_FaceSet.end()) {
        m_FaceSet.erase(AFace);
        return true;
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       FaceSet::Add
【函数功能】       添加面（通过面对象）
【入口参数】       const Element<3>& NewElement
【出口参数】       无
【返回值】         unsigned int 新面索引
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
unsigned int FaceSet::Add(const Element<3>& NewElement) {
    const Face* AFace = dynamic_cast<const Face*>(&NewElement);
    if (!AFace) {
        throw ExceptionTypeMismatch();
    }
    else if (!AFace->IsValid()) {
        throw ExceptionCoincidentPoints();
    }
    else {
        const auto& Points = AFace->GetPoints();
        unsigned int uIndex1 = m_pPointSet->AddPoint(Points[0]);
        unsigned int uIndex2 = m_pPointSet->AddPoint(Points[1]);
        unsigned int uIndex3 = m_pPointSet->AddPoint(Points[2]);
        if (this->FindElement(NewElement) == UINT_MAX) {
            m_FaceSet.push_back({ uIndex1, uIndex2, uIndex3 });
            return m_FaceSet.size() - 1;
        }
        else {
            throw ExceptionDuplicateFace();
        }
    }
    //return this->FindElement(NewElement);
}

/*************************************************************************
【函数名称】       FaceSet::Add
【函数功能】       添加面（通过点索引数组）
【入口参数】       const std::array<unsigned int, 3>& uIndex
【出口参数】       无
【返回值】         unsigned int 新面索引
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
unsigned int FaceSet::Add(const std::array<unsigned int, 3>& uIndex) {
    Point Point1 = m_pPointSet->GetPointByIndex(uIndex[0]);
    Point Point2 = m_pPointSet->GetPointByIndex(uIndex[1]);
    Point Point3 = m_pPointSet->GetPointByIndex(uIndex[2]);
    return Add(Face({ Point1, Point2, Point3 }));
}

/*************************************************************************
【函数名称】       FaceSet::Add
【函数功能】       添加面（通过点对象数组）
【入口参数】       const std::array<Point, 3>& Points
【出口参数】       无
【返回值】         unsigned int 新面索引
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
unsigned int FaceSet::Add(const std::array<Point, 3>& Points) {
    return Add(Face({ Points[0], Points[1], Points[2] }));
}

/*************************************************************************
【函数名称】       FaceSet::Add
【函数功能】       添加面（通过坐标数组）
【入口参数】       const std::vector<std::array<double, 3>>& Coordinates
【出口参数】       无
【返回值】         unsigned int 新面索引
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
unsigned int FaceSet::Add(
    const std::vector<std::array<double, 3>>& Coordinates) {
    if (Coordinates.size() < 3) {
        throw ExceptionMissingParams();
    }
    else if (Coordinates.size() > 3) {
        throw ExceptionExcessParams();
    }
    else {
        Point Point1({ Coordinates[0] });
        Point Point2({ Coordinates[1] });
        Point Point3({ Coordinates[2] });
        return Add(Face({ Point1, Point2, Point3 }));
    }
}

/*************************************************************************
【函数名称】       FaceSet::Modify
【函数功能】       修改面
【入口参数】       unsigned int uElementIndex, unsigned int uPointIndex, 
                   const Point& NewPoint
【出口参数】       无
【返回值】         bool 修改是否成功
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
bool FaceSet::Modify(unsigned int uElementIndex, unsigned int uPointIndex, 
    const Point& NewPoint) {
    if (uElementIndex != UINT_MAX 
        && uElementIndex < m_FaceSet.size() && uPointIndex < 3) {
        std::array<Point, 3> NewFaceCoords;
        for (unsigned int i = 0; i < 3; ++i) {
            if (i == uPointIndex) {
                NewFaceCoords[i] = NewPoint;
            }
            else {
                NewFaceCoords[i] = m_pPointSet->GetPointByIndex(
                    GetElementSet()[uElementIndex][i]);
            }
        }
        Face NewFace(NewFaceCoords);
        unsigned int uNewIndex = m_pPointSet->AddPoint(NewPoint);
        if (FindElement(NewFace) != UINT_MAX) {
            throw ExceptionDuplicateFace();
        }
        else {
            m_FaceSet[uElementIndex][uPointIndex] = uNewIndex;
            return true;
        }
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       FaceSet::Modify
【函数功能】       修改面（通过坐标）
【入口参数】       unsigned int uElementIndex, unsigned int uPointIndex, 
                   const std::array<double, 3>& Coordinates
【出口参数】       无
【返回值】         bool 修改是否成功
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
bool FaceSet::Modify(unsigned int uElementIndex, unsigned int uPointIndex, 
    const std::array<double, 3>& Coordinates) {
    return Modify(uElementIndex, uPointIndex, Point({ Coordinates }));
}

/*************************************************************************
【函数名称】       FaceSet::GetPointsInElement
【函数功能】       获取面中的点
【入口参数】       const unsigned int uElementIndex
【出口参数】       无
【返回值】         std::array<unsigned int, 3> 点索引数组
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
std::array<unsigned int, 3> FaceSet::GetPointsInElement(
    const unsigned int uElementIndex) const {
    if (uElementIndex >= m_FaceSet.size() || uElementIndex == UINT_MAX) {
        throw ExceptionInvalidIndex();
    }
    return { GetElementSet()[uElementIndex][0], 
             GetElementSet()[uElementIndex][1], 
             GetElementSet()[uElementIndex][2] };
}

/*************************************************************************
【函数名称】       FaceSet::GetTotalCount
【函数功能】       获取面总数
【入口参数】       无
【出口参数】       无
【返回值】         unsigned int 面总数
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
unsigned int FaceSet::GetTotalCount() const {
    return static_cast<unsigned int>(m_FaceSet.size());
}

/*************************************************************************
【函数名称】       FaceSet::GetTotalLength
【函数功能】       获取面总长度
【入口参数】       无
【出口参数】       无
【返回值】         double 面总长度
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
double FaceSet::GetTotalLength() const {
    double rTotalLength = 0.0;
    for (const auto& AFace : m_FaceSet) {
        Point Point1 = m_pPointSet->GetPointByIndex(AFace[0]);
        Point Point2 = m_pPointSet->GetPointByIndex(AFace[1]);
        Point Point3 = m_pPointSet->GetPointByIndex(AFace[2]);
        Face SelectFace({ Point1,Point2,Point3 });
        rTotalLength += SelectFace.GetLength();
    }
    return rTotalLength;
}

/*************************************************************************
【函数名称】       FaceSet::GetTotalArea
【函数功能】       获取面总面积
【入口参数】       无
【出口参数】       无
【返回值】         double 面总面积
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
double FaceSet::GetTotalArea() const {
    double rTotalArea = 0.0;
    for (const auto& AFace : m_FaceSet) {
        Point Point1 = m_pPointSet->GetPointByIndex(AFace[0]);
        Point Point2 = m_pPointSet->GetPointByIndex(AFace[1]);
        Point Point3 = m_pPointSet->GetPointByIndex(AFace[2]);
        Face SelectFace({ Point1, Point2, Point3 });
        rTotalArea += SelectFace.GetArea();
    }
    return rTotalArea;
}

/*************************************************************************
【函数名称】       FaceSet::GetFaceAreas
【函数功能】       获取所有面的面积
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<double> 面积数组
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
std::vector<double> FaceSet::GetFaceAreas() const {
    std::vector<double> FaceAreas;
    for (const auto& AFace : m_FaceSet) {
        Point Point1 = m_pPointSet->GetPointByIndex(AFace[0]);
        Point Point2 = m_pPointSet->GetPointByIndex(AFace[1]);
        Point Point3 = m_pPointSet->GetPointByIndex(AFace[2]);
        Face SelectFace({ Point1, Point2, Point3 });
        FaceAreas.push_back(SelectFace.GetArea());
    }
    return FaceAreas;
}

/*************************************************************************
【函数名称】       FaceSet::ExceptionDuplicateFace::ExceptionDuplicateFace
【函数功能】       重复面异常构造函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
FaceSet::ExceptionDuplicateFace::ExceptionDuplicateFace()
: std::invalid_argument("Duplicate Face.") {
}

/*************************************************************************
【函数名称】       FaceSet::ClearElementSet
【函数功能】       清空面集
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/7
【更改记录】       无
*************************************************************************/
void FaceSet::ClearElementSet() {
    m_FaceSet.clear();
}



