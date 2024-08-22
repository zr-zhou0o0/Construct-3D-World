/*************************************************************************
【文件名】                 LineSet.hpp
【功能模块和目的】         线集类声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <memory>
#include <vector>
#include <array>
#include <stdexcept>

#include "../Point/Point.hpp"
#include "../Element/Line.hpp"
#include "../PointSet/PointSet.hpp"
#include "ElementSet.hpp"

using namespace std;

#ifndef LINESET_HPP
#define LINESET_HPP

/*************************************************************************
【类名】             LineSet
【功能】             线集类，管理一组线段
【接口说明】         提供添加、删除、修改线段的方法，
                     以及获取线段集合和属性的方法
【开发者及日期】     周子睿 2024/8/12
【更改记录】         无
*************************************************************************/
class LineSet : public ElementSet<2> {
public:
    //--------------------------------------------------------------------
    //必要的构造、析构、赋值行为
    //--------------------------------------------------------------------
    //构造函数，初始化线集类
    LineSet(std::shared_ptr<PointSet> pPointSet);
    //构造函数，初始化线集类，带线段集合参数
    LineSet(std::shared_ptr<PointSet> pPointSet, 
        const std::vector<std::array<unsigned int, 2>>& NewLineSet);
    // 拷贝构造函数
    LineSet(const LineSet& Source);
    // 赋值运算符重载
    LineSet& operator=(const LineSet& Source);
    //默认析构函数
    virtual ~LineSet() = default;

    //--------------------------------------------------------------------
    //获取线段集合的方法
    //--------------------------------------------------------------------
    //获取线段集合
    std::vector<std::array<unsigned int, 2>> GetElementSet() const override;
    //获取指定索引的线段
    std::vector<std::array<unsigned int, 2>> GetElement(
        const unsigned int uIndex) const override;
    //获取线段集合的索引
    std::vector<unsigned int> GetElementSetIndex() const override;

    //--------------------------------------------------------------------
    //查找、添加、删除、修改线段的方法
    //--------------------------------------------------------------------
    //查找线段
    unsigned int FindElement(const Element<2>& NewLine)const override;
    //删除线段（通过索引）
    bool Delete(const unsigned int uIndex) override;
    //删除线段（通过点索引）
    bool Delete(const std::array<unsigned int, 2>& PointIndex) override;
    //添加线段（通过线段对象）
    unsigned int Add(const Element<2>& NewElement) override;
    //添加线段（通过点索引数组）
    unsigned int Add(const std::array<unsigned int, 2>& Index) override;
    //添加线段（通过点对象数组）
    unsigned int Add(const std::array<Point, 2>& Points) override;
    //添加线段（通过坐标数组）
    unsigned int Add(
        const std::vector<std::array<double, 3>>& Coordinates) override;
    //修改线段
    bool Modify(unsigned int uElementIndex, 
        unsigned int uPointIndex, const Point& NewPoint) override;
    //修改线段（通过坐标）
    bool Modify(unsigned int uElementIndex, unsigned int uPointIndex, 
        const std::array<double, 3>& Coordinates) override;

    //--------------------------------------------------------------------
    //获取线段属性的方法
    //--------------------------------------------------------------------
    //获取线段中的点
    std::array<unsigned int, 2> GetPointsInElement(
        unsigned int uElementIndex) const override;
    //获取线段总数
    unsigned int GetTotalCount() const override;
    //获取线段总长度
    double GetTotalLength() const override;
    //获取线段总面积（未定义）
    double GetTotalArea() const override;
    //获取所有线段的长度
    std::vector<double> GetLineLengths() const;

    //--------------------------------------------------------------------
    //清空线段集合的方法
    //--------------------------------------------------------------------
    //清空线段集合
    void ClearElementSet();

    //--------------------------------------------------------------------
    //异常类
    //--------------------------------------------------------------------
    //重复线段异常类
    class ExceptionDuplicateLine : public std::invalid_argument {
    public:
        ExceptionDuplicateLine();
    };

    //未定义面积异常类
    class ExceptionUndefinedArea : public std::logic_error {
    public:
        ExceptionUndefinedArea();
    };

private:
    //--------------------------------------------------------------------
    //成员变量
    //--------------------------------------------------------------------
    //线段集合
    std::vector<std::array<unsigned int, 2>> m_LineSet = {};
    //点集指针
    std::shared_ptr<PointSet> m_pPointSet = nullptr;
};

#endif

