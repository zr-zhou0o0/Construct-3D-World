/*************************************************************************
【文件名】                 PointSet.cpp
【功能模块和目的】         三维点集类定义
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <vector>
#include <array>
#include <limits.h>
#include <stdexcept>
#include <numeric>

#include "PointSet.hpp"
#include "../Point/Point.hpp"

using namespace std;

/*************************************************************************
【函数名称】       PointSet构造函数
【函数功能】       创建一个空的PointSet对象
【参数】           无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
PointSet::PointSet() : m_PointSet() {}

/*************************************************************************
【函数名称】       PointSet构造函数
【函数功能】       使用给定的点集创建PointSet对象
【参数】           NewPointSet（输入参数）：初始点集
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
PointSet::PointSet(const std::vector<std::array<double, 3>>& NewPointSet) : 
m_PointSet(NewPointSet) {}

/*************************************************************************
【函数名称】       PointSet拷贝构造函数
【函数功能】       创建PointSet对象
【参数】           const PointSet& Source
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
PointSet::PointSet(const PointSet& Source) {
    m_PointSet = Source.m_PointSet;
}

/*************************************************************************
【函数名称】       PointSet赋值运算符重载
【函数功能】       创建PointSet对象
【参数】           const PointSet& Source
【返回值】         PointSet
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
PointSet& PointSet::operator=(const PointSet& Source) {
    if (this != &Source) {
        m_PointSet = Source.m_PointSet;
    }
    return *this;
}

/*************************************************************************
【函数名称】       ~PointSet
【函数功能】       PointSet析构函数
【参数】           无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
PointSet::~PointSet() {}

/*************************************************************************
【函数名称】       SetPointSet
【函数功能】       向现有点集添加新的点
【参数】           NewPointSet（输入参数）：要添加的新点集
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
void PointSet::SetPointSet(
    const std::vector<std::array<double, 3>>& NewPointSet) {
    m_PointSet.insert(
        m_PointSet.end(), NewPointSet.begin(), NewPointSet.end());
}

/*************************************************************************
【函数名称】       GetPointSet
【函数功能】       获取当前点集
【参数】           无
【返回值】         返回当前点集的副本
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::vector<std::array<double, 3>> PointSet::GetPointSet() const {
    return m_PointSet;
}

/*************************************************************************
【函数名称】       GetPointSetIndex
【函数功能】       获取点集的索引
【参数】           无
【返回值】         返回一个包含所有点索引的向量
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::vector<unsigned int> PointSet::GetPointSetIndex()const {
    std::vector<unsigned int> PointSetIndex(GetTotalPointCount());
    std::iota(PointSetIndex.begin(), PointSetIndex.end(), 0);
    return PointSetIndex;
}

/*************************************************************************
【函数名称】       AddPoint
【函数功能】       向点集添加新点
【参数】           NewPoint（输入参数）：要添加的新点
【返回值】         返回新添加点的索引
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int PointSet::AddPoint(const Point& NewPoint) {
    return AddPoint(NewPoint, m_PointSet.size());
}

/*************************************************************************
【函数名称】       AddPoint
【函数功能】       向点集添加新点坐标
【参数】           rCoordinates（输入参数）：要添加的新点坐标
【返回值】         返回新添加点的索引
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int PointSet::AddPoint(const array<double, 3>& NewCoords) {
    return AddPoint(Point({ NewCoords }));
}

/*************************************************************************
【函数名称】       AddPoint
【函数功能】       在指定索引处向点集添加新点
【参数】           NewPoint（输入参数）：要添加的新点
                   uIndex（输入参数）：指定的索引位置
【返回值】         返回新添加点的索引，如果点已存在则返回原索引
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int PointSet::AddPoint(const Point& NewPoint, unsigned int uIndex) {
    if (uIndex == UINT_MAX 
        || static_cast<size_t>(uIndex) > m_PointSet.size()) {
        throw ExceptionInvalidIndex();
    }
    else {
        if (FindPoint(NewPoint) == UINT_MAX) {
            std::array<double, 3> coords = { 
                NewPoint.GetCoordinates()[0][0], 
                NewPoint.GetCoordinates()[0][1], 
                NewPoint.GetCoordinates()[0][2] };
            m_PointSet.insert(m_PointSet.begin() + uIndex, coords);
            return uIndex;
        }
        else {
            return FindPoint(NewPoint);
        }
    }
}

/*************************************************************************
【函数名称】       DeletePoint
【函数功能】       删除指定索引的点
【参数】           uIndex（输入参数）：要删除的点的索引
【返回值】         如果成功删除返回true，否则抛出异常
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool PointSet::DeletePoint(unsigned int uIndex) {
    if (uIndex == UINT_MAX 
        || static_cast<size_t>(uIndex) >= m_PointSet.size()) {
        throw ExceptionInvalidIndex();
    }
    else {
        m_PointSet.erase(m_PointSet.begin() + uIndex);
        return true;
    }
}

/*************************************************************************
【函数名称】       FindPoint
【函数功能】       查找指定点在点集中的索引
【参数】           NewPoint（输入参数）：要查找的点
【返回值】         如果找到返回索引，否则返回UINT_MAX
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int PointSet::FindPoint(const Point& NewPoint) const {
    std::array<double, 3> coords = { 
        NewPoint.GetCoordinates()[0][0], 
        NewPoint.GetCoordinates()[0][1], 
        NewPoint.GetCoordinates()[0][2] };

    auto it = std::find(m_PointSet.begin(), m_PointSet.end(), coords);

    if (it != m_PointSet.end()) {
        // 找到了点，返回其索引
        return std::distance(m_PointSet.begin(), it);
    }
    else {
        // 没找到点，返回 uint_max
        return UINT_MAX;
    }
}

/*************************************************************************
【函数名称】       GetCoordsByIndexRange
【函数功能】       获取指定索引范围内的点坐标
【参数】           uStartIndex（输入参数）：起始索引
                   uEndIndex（输入参数）：结束索引
【返回值】         返回指定范围内的点坐标向量
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::vector<std::array<double, 3>> PointSet::GetCoordsByIndexRange(
    unsigned int uStartIndex, unsigned int uEndIndex)const {
    if (uStartIndex == UINT_MAX || uEndIndex == UINT_MAX 
        || static_cast<size_t>(uEndIndex) > m_PointSet.size() 
        || uStartIndex >= uEndIndex) {
        throw ExceptionInvalidIndex();
    }
    return std::vector<std::array<double, 3>>(
        m_PointSet.begin() + uStartIndex, m_PointSet.begin() + uEndIndex);
}

/*************************************************************************
【函数名称】       GetCoordsByIndex
【函数功能】       获取指定索引的点坐标
【参数】           uIndex（输入参数）：点的索引
【返回值】         返回指定索引的点坐标
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::array<double, 3> PointSet::GetCoordsByIndex(unsigned int uIndex)const {
    if (uIndex == UINT_MAX 
        || static_cast<size_t>(uIndex) >= m_PointSet.size()) {
        throw ExceptionInvalidIndex();
    }
    return m_PointSet[uIndex];
}

/*************************************************************************
【函数名称】       GetPointByIndex
【函数功能】       获取指定索引的点
【参数】           uIndex（输入参数）：点的索引
【返回值】         返回指定索引的Point对象
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Point PointSet::GetPointByIndex(unsigned int uIndex) const {
    if (uIndex == UINT_MAX 
        || static_cast<size_t>(uIndex) >= m_PointSet.size()) {
        throw ExceptionInvalidIndex();
    }
    auto coords = m_PointSet[uIndex];
    return Point({ { coords[0], coords[1], coords[2] } });
}

/*************************************************************************
【函数名称】       GetIndexByCoords
【函数功能】       通过坐标获取点的索引
【参数】           coords（输入参数）：点的坐标
【返回值】         返回对应坐标的点的索引
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int PointSet::GetIndexByCoords(
    const std::array<double, 3> Coords) const {
    auto it = std::find(m_PointSet.begin(), m_PointSet.end(), Coords);
    if (it == m_PointSet.end()) {
        throw ExceptionInvalidIndex();
    }
    return std::distance(m_PointSet.begin(), it);
}

/*************************************************************************
【函数名称】       GetIndexByPoint
【函数功能】       通过Point对象获取点的索引
【参数】           point（输入参数）：Point对象
【返回值】         返回对应Point对象的索引
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int PointSet::GetIndexByPoint(const Point& APoint)const {
    std::array<double, 3> coords = { 
        APoint.GetCoordinates()[0][0], 
        APoint.GetCoordinates()[0][1], 
        APoint.GetCoordinates()[0][2] };
    return GetIndexByCoords(coords);
}

/*************************************************************************
【函数名称】       GetTotalPointCount
【函数功能】       获取点集中点的总数
【参数】           无
【返回值】         返回点集中点的总数
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
unsigned int PointSet::GetTotalPointCount()const {
    return m_PointSet.size();
}

/*************************************************************************
【函数名称】       GetBoundingBoxVolume
【函数功能】       计算点集的包围盒体积
【参数】           无
【返回值】         返回包围盒的体积
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
double PointSet::GetBoundingBoxVolume()const {
    if (m_PointSet.empty()) return 0.0;

    double minX = m_PointSet[0][0], maxX = m_PointSet[0][0];
    double minY = m_PointSet[0][1], maxY = m_PointSet[0][1];
    double minZ = m_PointSet[0][2], maxZ = m_PointSet[0][2];

    for (const auto& point : m_PointSet) {
        minX = std::min(minX, point[0]);
        maxX = std::max(maxX, point[0]);
        minY = std::min(minY, point[1]);
        maxY = std::max(maxY, point[1]);
        minZ = std::min(minZ, point[2]);
        maxZ = std::max(maxZ, point[2]);
    }

    double length = maxX - minX;
    double width = maxY - minY;
    double height = maxZ - minZ;

    return length * width * height;
}

/*************************************************************************
【函数名称】       ExceptionInvalidIndex
【函数功能】       无效索引异常的构造函数
【参数】           无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
PointSet::ExceptionInvalidIndex::ExceptionInvalidIndex()
: std::out_of_range("Index out of bounds.") {
}

/*************************************************************************
【函数名称】       ClearPointSet
【函数功能】       清空点集
【参数】           无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
void PointSet::ClearPointSet() {
    m_PointSet.clear();
}











