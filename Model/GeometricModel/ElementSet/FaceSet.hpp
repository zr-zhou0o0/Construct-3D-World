/*************************************************************************
【文件名】                 FaceSet.hpp
【功能模块和目的】         面集类声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <memory>
#include <vector>
#include <array>
#include "../Point/Point.hpp"
#include "../Element/Face.hpp"
#include "../PointSet/PointSet.hpp"
#include "ElementSet.hpp"

#ifndef FACESET_HPP
#define FACESET_HPP

/*************************************************************************
【类名】             FaceSet
【功能】             面集类
【接口说明】         提供面集的管理和操作接口
【开发者及日期】     周子睿 2024/8/12
【更改记录】         无
*************************************************************************/
class FaceSet : public ElementSet<3> {
public:
    //--------------------------------------------------------------------
    //必要的构造、析构、赋值行为
    //--------------------------------------------------------------------
    //带点集指针的构造函数
    FaceSet(std::shared_ptr<PointSet> pPointSet);
    //带点集指针和新面集的构造函数
    FaceSet(std::shared_ptr<PointSet> pPointSet, 
        const std::vector<std::array<unsigned int, 3>>& NewFaceSet);
    // 拷贝构造函数
    FaceSet(const FaceSet& Source);
    // 赋值运算符重载
    FaceSet& operator=(const FaceSet& Source);
    //虚析构函数
    virtual ~FaceSet() = default;

    //--------------------------------------------------------------------
    //面集的操作
    //--------------------------------------------------------------------
    //获取面集
    std::vector<std::array<unsigned int, 3>> GetElementSet() const override;
    //获取指定索引的面
    std::vector<std::array<unsigned int, 3>> GetElement(
        unsigned int uIndex) const override;
    //获取面集索引
    std::vector<unsigned int> GetElementSetIndex() const override;
    //查找面
    unsigned int FindElement(const Element<3>& NewFace)const;
    //删除面（通过索引）
    bool Delete(const unsigned int uIndex) override;
    //删除面（通过点索引）
    bool Delete(const std::array<unsigned int, 3>& PointIndex) override;
    //添加面（通过面对象）
    unsigned int Add(const Element<3>& NewElement) override;
    //添加面（通过点索引数组）
    unsigned int Add(const std::array<unsigned int, 3>& uIndex) override;
    //添加面（通过点对象数组）
    unsigned int Add(const std::array<Point, 3>& Points) override;
    //添加面（通过坐标数组）
    unsigned int Add(
        const std::vector<std::array<double, 3>>& Coordinates) override;
    //修改面
    bool Modify(unsigned int uElementIndex, 
        unsigned int uPointIndex, const Point& NewPoint) override;
    //修改面（通过坐标）
    bool Modify(unsigned int uElementIndex, unsigned int uPointIndex, 
        const std::array<double, 3>& Coordinates) override;
    //获取面中的点
    std::array<unsigned int, 3> GetPointsInElement(
        const unsigned int uElementIndex) const override;
    //获取面总数
    unsigned int GetTotalCount() const override;
    //获取面总长度
    double GetTotalLength() const override;
    //获取面总面积
    double GetTotalArea() const override;
    //获取所有面的面积
    std::vector<double> GetFaceAreas() const;
    //清空面集
    void ClearElementSet();

    //--------------------------------------------------------------------
    //异常类声明
    //--------------------------------------------------------------------
    //重复面异常
    class ExceptionDuplicateFace : public std::invalid_argument {
    public:
        ExceptionDuplicateFace();
    };

private:
    //面集
    std::vector<std::array<unsigned int, 3>> m_FaceSet = {};
    //点集指针
    std::shared_ptr<PointSet> m_pPointSet = nullptr;
};

#endif // FACESET_HPP



