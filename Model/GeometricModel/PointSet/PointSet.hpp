/*************************************************************************
【文件名】                 PointSet.hpp
【功能模块和目的】         三维点集类声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include<ostream>
#include<sstream>
#include<string>
#include<array>
#include<vector>
#include<algorithm>
#include<limits.h>

#include"../Point/Point.hpp"

using namespace std;

#ifndef POINTSET_HPP
#define POINTSET_HPP


/*************************************************************************
【类名】             PointSet
【功能】             表示三维点的集合（用坐标表示）
【接口说明】         提供添加点、删除点、查找点等功能，支持坐标、索引、范
                     围等多种接口
【开发者及日期】     周子睿 2024/8/12
【更改记录】         无
*************************************************************************/
class PointSet {

public:
    //--------------------------------------------------------------------
    //构造和析构函数
    //--------------------------------------------------------------------
    // 默认构造函数
    PointSet();
    // 使用给定点集构造PointSet对象
    PointSet(const std::vector<std::array<double, 3>>& NewPointSet);
    // 拷贝构造函数
    PointSet(const PointSet& Source);
    // 赋值运算符重载
    PointSet& operator=(const PointSet& Source);
    // 析构函数
    virtual ~PointSet();

    //--------------------------------------------------------------------
    //点集操作函数
    //--------------------------------------------------------------------
    // 设置点集，不删除原有点
    void SetPointSet(const std::vector<std::array<double, 3>>& NewPointSet);
    // 获取当前点集
    std::vector<std::array<double, 3>> GetPointSet() const;
    // 获取点集索引
    std::vector<unsigned int> GetPointSetIndex() const;

    // 添加新点，返回新点索引
    unsigned int AddPoint(const Point& NewPoint);
    // 添加新点坐标，返回新点索引
    unsigned int AddPoint(const array<double, 3>& NewCoords);
    // 在指定索引处添加新点
    unsigned int AddPoint(const Point& NewPoint, unsigned int uIndex);
    // 删除指定索引的点
    bool DeletePoint(unsigned int uIndex);

    //--------------------------------------------------------------------
    //查找和获取函数
    //--------------------------------------------------------------------
    // 查找点，返回索引
    unsigned int FindPoint(const Point& NewPoint) const;
    // 获取指定索引范围内的坐标
    std::vector<std::array<double, 3>> 
        GetCoordsByIndexRange(
            unsigned int uStartIndex, unsigned int uEndIndex) const;
    // 获取指定索引的坐标
    std::array<double, 3> GetCoordsByIndex(unsigned int uIndex) const;
    // 获取指定索引的点
    Point GetPointByIndex(unsigned int uIndex) const;
    // 通过坐标获取索引
    unsigned int GetIndexByCoords(const std::array<double, 3> Coords) const;
    // 通过点获取索引
    unsigned int GetIndexByPoint(const Point& APoint) const;

    // 获取点的总数
    unsigned int GetTotalPointCount() const;
    // 计算包围盒体积
    double GetBoundingBoxVolume() const;

    //--------------------------------------------------------------------
    //重置操作
    //--------------------------------------------------------------------
    // 清空点集
    void ClearPointSet();

    //--------------------------------------------------------------------
    //异常类
    //--------------------------------------------------------------------
    // 无效索引异常类
    class ExceptionInvalidIndex : public std::out_of_range {
    public:
        ExceptionInvalidIndex();
    };

private:
    //--------------------------------------------------------------------
    //私有成员变量
    //--------------------------------------------------------------------
    // 存储点集的容器
    std::vector<std::array<double, 3>> m_PointSet{};

};

#endif