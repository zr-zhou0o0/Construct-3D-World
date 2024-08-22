/*************************************************************************
【文件名】                 LineSet.cpp
【功能模块和目的】         线集类定义
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <vector>
#include <array>
#include <cmath>
#include <iostream>
#include <limits.h>
#include <stdexcept>
#include <memory>
#include <numeric>

#include "../Point/Point.hpp"
#include "../Element/Line.hpp"
#include "../PointSet/PointSet.hpp"
#include "ElementSet.hpp"
#include "LineSet.hpp"

using namespace std;

/*************************************************************************
【函数名称】       LineSet
【函数功能】       构造函数，初始化线集类
【入口参数】       std::shared_ptr<PointSet> pPointSet
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
LineSet::LineSet(std::shared_ptr<PointSet> pPointSet) : 
ElementSet<2>(pPointSet), m_pPointSet(pPointSet) {
}

/*************************************************************************
【函数名称】       LineSet
【函数功能】       构造函数，初始化线集类，带线段集合参数
【入口参数】       std::shared_ptr<PointSet> pPointSet, 
                   const std::vector<std::array<unsigned int, 2>>& NewLineSet
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
LineSet::LineSet(std::shared_ptr<PointSet> pPointSet, 
    const std::vector<std::array<unsigned int, 2>>& NewLineSet) : 
    ElementSet<2>(pPointSet), m_LineSet(NewLineSet), 
    m_pPointSet(pPointSet) {
}

/*************************************************************************
【函数名称】       LineSet拷贝构造函数
【函数功能】       创建LineSet对象
【参数】           const LineSet& Source
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
LineSet::LineSet(const LineSet& Source) : 
ElementSet<2>(Source), m_LineSet(Source.m_LineSet),
m_pPointSet(Source.m_pPointSet) {
}

/*************************************************************************
【函数名称】       LineSet赋值运算符重载
【函数功能】       创建LineSet对象
【参数】           const LineSet& Source
【返回值】         LineSet
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
LineSet& LineSet::operator=(const LineSet& Source)
{
    if (this != &Source) {
        ElementSet<2>::operator=(Source);
        m_LineSet = Source.m_LineSet;
        m_pPointSet = Source.m_pPointSet;
    }
    return *this;
}

/*************************************************************************
【函数名称】       GetElementSet
【函数功能】       获取线段集合
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<std::array<unsigned int, 2>> 线段集合
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::vector<std::array<unsigned int, 2>> LineSet::GetElementSet() const {
    return m_LineSet;
}

/*************************************************************************
【函数名称】       GetElement
【函数功能】       获取指定索引的线段
【入口参数】       const unsigned int uIndex
【出口参数】       无
【返回值】         std::vector<std::array<unsigned int, 2>> 指定索引的线段
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::vector<std::array<unsigned int, 2>> LineSet::GetElement(
    unsigned int uIndex) const {
    if (uIndex != UINT_MAX 
        && static_cast<size_t>(uIndex) < (m_LineSet.size())) {
        return { m_LineSet[uIndex] };
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       GetElementSetIndex
【函数功能】       获取线段集合的索引
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<unsigned int> 线段集合的索引
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::vector<unsigned int> LineSet::GetElementSetIndex() const {
    std::vector<unsigned int> LineSetIndex(GetTotalCount());
    std::iota(LineSetIndex.begin(), LineSetIndex.end(), 0);
    return LineSetIndex;
}

/*************************************************************************
【函数名称】       FindElement
【函数功能】       查找线段
【入口参数】       const Element<2>& NewLine
【出口参数】       无
【返回值】         unsigned int 线段索引，如果没有找到返回 UINT_MAX
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int LineSet::FindElement(const Element<2>& NewLine)const {
    const Line* ALine = dynamic_cast<const Line*>(&NewLine);
    if (!ALine) {
        throw ExceptionTypeMismatch();
    }
    else if (!ALine->IsValid()) {
        throw ExceptionCoincidentPoints();
    }
    else {
        for (unsigned int i = 0; i < m_LineSet.size(); ++i) {
            if (ALine->IsSame
                (Line({ m_pPointSet->GetPointByIndex(m_LineSet[i][0]),
                        m_pPointSet->GetPointByIndex(m_LineSet[i][1]) }))) {
                return i;  // 返回第一个重复的 ALine 的索引
            }
        }
    }
    return UINT_MAX;  // 如果没有找到重复的 line，返回 UINT_MAX
}

/*************************************************************************
【函数名称】       Delete
【函数功能】       删除线段（通过索引）
【入口参数】       const unsigned int uIndex
【出口参数】       无
【返回值】         bool 删除是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool LineSet::Delete(const unsigned int uIndex) {
    if (uIndex != UINT_MAX 
        && static_cast<size_t>(uIndex) < (m_LineSet.size())) {
        m_LineSet.erase(m_LineSet.begin() + uIndex);
        return true;
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       Delete
【函数功能】       删除线段（通过点索引）
【入口参数】       const std::array<unsigned int, 2>& PointIndex
【出口参数】       无
【返回值】         bool 删除是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool LineSet::Delete(const std::array<unsigned int, 2>& PointIndex) {
    auto ALine = std::find(m_LineSet.begin(), m_LineSet.end(), PointIndex);
    if (ALine != m_LineSet.end()) {
        m_LineSet.erase(ALine);
        return true;
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       Add
【函数功能】       添加线段（通过线段对象）
【入口参数】       const Element<2>& NewElement
【出口参数】       无
【返回值】         unsigned int 新线段的索引
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int LineSet::Add(const Element<2>& NewElement) {
    const Line* ALine = dynamic_cast<const Line*>(&NewElement);
    if (!ALine) {
        throw ExceptionTypeMismatch();
    }
    else if (!ALine->IsValid()) {
        throw ExceptionCoincidentPoints();
    }
    else {
        const auto& Points = ALine->GetPoints();
        unsigned int uIndex1 = m_pPointSet->AddPoint(Points[0]);
        unsigned int uIndex2 = m_pPointSet->AddPoint(Points[1]);
        if (this->FindElement(NewElement) == UINT_MAX) {
            m_LineSet.push_back({ uIndex1, uIndex2 });
            return m_LineSet.size() - 1;
        }
        else {
            throw ExceptionDuplicateLine();
        }
    }
}

/*************************************************************************
【函数名称】       Add
【函数功能】       添加线段（通过点索引数组）
【入口参数】       const std::array<unsigned int, 2>& uIndex
【出口参数】       无
【返回值】         unsigned int 新线段的索引
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int LineSet::Add(const std::array<unsigned int, 2>& Index) {
    Point Point1 = m_pPointSet->GetPointByIndex(Index[0]);
    Point Point2 = m_pPointSet->GetPointByIndex(Index[1]);
    return Add(Line({ Point1, Point2 }));
}

/*************************************************************************
【函数名称】       Add
【函数功能】       添加线段（通过点对象数组）
【入口参数】       const std::array<Point, 2>& Points
【出口参数】       无
【返回值】         unsigned int 新线段的索引
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int LineSet::Add(const std::array<Point, 2>& Points) {
    return Add(Line({ Points[0], Points[1] }));
}

/*************************************************************************
【函数名称】       Add
【函数功能】       添加线段（通过坐标数组）
【入口参数】       const std::vector<std::array<double, 3>>& Coordinates
【出口参数】       无
【返回值】         unsigned int 新线段的索引
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int LineSet::Add(
    const std::vector<std::array<double, 3>>& Coordinates) {
    if (Coordinates.size() < 2) {
        throw ExceptionMissingParams();
    }
    else if (Coordinates.size() > 2) {
        throw ExceptionExcessParams();
    }
    else {
        Point Point1({ Coordinates[0] });
        Point Point2({ Coordinates[1] });
        return Add(Line({ Point1, Point2 }));
    }
}

/*************************************************************************
【函数名称】       Modify
【函数功能】       修改线段
【入口参数】       unsigned int uElementIndex, unsigned int uPointIndex, 
                   const Point& NewPoint
【出口参数】       无
【返回值】         bool 修改是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool LineSet::Modify(unsigned int uElementIndex, unsigned int uPointIndex, 
    const Point& NewPoint) {
    if (uElementIndex != UINT_MAX 
        && uElementIndex < static_cast<unsigned int>(m_LineSet.size()) 
        && (uPointIndex == 0 || uPointIndex == 1)) {
        Point RemainPoint;
        std::array<Point, 2> NewLineCoords;
        if (uPointIndex == 0) {
            RemainPoint = m_pPointSet->GetPointByIndex(
                GetElementSet()[uElementIndex][1]);
            NewLineCoords = { NewPoint, RemainPoint };
        }
        else {
            RemainPoint = m_pPointSet->GetPointByIndex(
                GetElementSet()[uElementIndex][0]);
            NewLineCoords = { RemainPoint, NewPoint };
        }

        if (RemainPoint.IsSame(NewPoint)) {
            throw ExceptionCoincidentPoints();
        }
        else {
            unsigned int uIndex = m_pPointSet->AddPoint(NewPoint);
            Line NewLine(NewLineCoords);
            if (FindElement(NewLine) != UINT_MAX) {
                throw ExceptionDuplicateLine();
            }
            else {
                m_LineSet[uElementIndex][uPointIndex] = uIndex;
                return true;
            }
        }
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       Modify
【函数功能】       修改线段（通过坐标）
【入口参数】       unsigned int iElementIndex, unsigned int iPointIndex, 
                   const std::array<double, 3>& Coordinates
【出口参数】       无
【返回值】         bool 修改是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool LineSet::Modify(unsigned int iElementIndex, unsigned int iPointIndex, 
    const std::array<double, 3>& rCoordinates) {
    return Modify(iElementIndex, iPointIndex, Point({ rCoordinates }));
}

/*************************************************************************
【函数名称】       GetPointsInElement
【函数功能】       获取线段中的点
【入口参数】       const unsigned int uElementIndex
【出口参数】       无
【返回值】         std::array<unsigned int, 2> 线段中的点
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::array<unsigned int, 2> LineSet::GetPointsInElement(
    const unsigned int uElementIndex) const {
    if (uElementIndex >= m_LineSet.size() || uElementIndex == UINT_MAX) {
        throw ExceptionInvalidIndex();
    }
    return { GetElementSet()[uElementIndex][0], 
             GetElementSet()[uElementIndex][1] };
}

/*************************************************************************
【函数名称】       GetTotalCount
【函数功能】       获取线段总数
【入口参数】       无
【出口参数】       无
【返回值】         unsigned int 线段总数
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int LineSet::GetTotalCount() const {
    return static_cast<unsigned int>(m_LineSet.size());
}

/*************************************************************************
【函数名称】       GetTotalLength
【函数功能】       获取线段总长度
【入口参数】       无
【出口参数】       无
【返回值】         double 线段总长度
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
double LineSet::GetTotalLength() const {
    double rTotalLength = 0.0;
    for (const auto& ALine : m_LineSet) {
        Point Point1 = m_pPointSet->GetPointByIndex(ALine[0]);
        Point Point2 = m_pPointSet->GetPointByIndex(ALine[1]);
        Line SelectLine({ Point1, Point2 });
        rTotalLength += SelectLine.GetLength();
    }
    return rTotalLength;
}

/*************************************************************************
【函数名称】       GetTotalArea
【函数功能】       获取线段总面积（未定义）
【入口参数】       无
【出口参数】       无
【返回值】         double 线段总面积（未定义）
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
double LineSet::GetTotalArea() const {
    throw ExceptionUndefinedArea();
}

/*************************************************************************
【函数名称】       GetLineLengths
【函数功能】       获取所有线段的长度
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<double> 所有线段的长度
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::vector<double> LineSet::GetLineLengths() const {
    std::vector<double> LineLegnths;
    for (const auto& ALine : m_LineSet) {
        Point Point1 = m_pPointSet->GetPointByIndex(ALine[0]);
        Point Point2 = m_pPointSet->GetPointByIndex(ALine[1]);
        Line SelectLine({ Point1, Point2 });
        LineLegnths.push_back(SelectLine.GetLength());
    }
    return LineLegnths;
}

/*************************************************************************
【函数名称】       ClearElementSet
【函数功能】       清空线段集合
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
void LineSet::ClearElementSet() {
    m_LineSet.clear();
}

/*************************************************************************
【函数名称】       ExceptionDuplicateLine
【函数功能】       重复线段异常类构造函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
LineSet::ExceptionDuplicateLine::ExceptionDuplicateLine()
: invalid_argument("Duplicate Line.") {
}

/*************************************************************************
【函数名称】       ExceptionUndefinedArea
【函数功能】       未定义面积异常类构造函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
LineSet::ExceptionUndefinedArea::ExceptionUndefinedArea()
: logic_error("Undefined Area.") {
}




