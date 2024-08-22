/*************************************************************************
【文件名】                 Line.hpp
【功能模块和目的】         线元素类声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <ostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>

#include "Element.hpp"
#include "../Point/Point.hpp"

using namespace std;

#ifndef LINE_HPP
#define LINE_HPP

/*************************************************************************
【类名】              Line
【功能】              表示线元素的类，继承自 Element<2>
【接口说明】          提供构造函数、析构函数、设置和获取坐标和点的函数，
                      计算长度的函数
【开发者及日期】      周子睿 2024/8/12
【更改记录】          无
*************************************************************************/
class Line : public Element<2> {
public:
    //--------------------------------------------------------------------
    // 内部异常类
    //--------------------------------------------------------------------
    // 表示未定义面积异常
    class ExceptionUndefinedArea : public std::logic_error {
    public:
        // 默认构造函数
        ExceptionUndefinedArea();
    };

    //--------------------------------------------------------------------
    // 必要的构造、析构、赋值行为
    //--------------------------------------------------------------------
    // 默认构造函数
    Line();
    // 通过坐标构造
    Line(const std::vector<std::array<double, 3>>& Coords);
    // 通过点构造
    Line(const std::array<Point, 2>& Points);
    //拷贝构造函数
    Line(const Line& Source);
    //赋值运算符overload
    Line& operator=(const Line& Source);
    // 析构函数
    ~Line();

    //--------------------------------------------------------------------
    // 非静态设置器
    //--------------------------------------------------------------------
    // 设置坐标
    void SetCoordinates(
        const std::vector<std::array<double, 3>>& Coords) override;
    // 设置点
    void SetPoints(const std::array<Point, 2>& Points) override;

    //--------------------------------------------------------------------
    // 非静态获取器
    //--------------------------------------------------------------------
    // 获取坐标
    std::vector<std::array<double, 3>> GetCoordinates() const override;
    // 获取点
    std::array<Point, 2> GetPoints() const override;
    // 获取对象的字符串表示
    std::string ToString() const override;

    //--------------------------------------------------------------------
    // 几何计算
    //--------------------------------------------------------------------
    // 获取线段长度
    double GetLength() const override;
    // 获取面积（线段无面积，抛出异常）
    double GetArea() const override;

    //--------------------------------------------------------------------
    // 验证功能
    //--------------------------------------------------------------------
    // 检查两个元素是否相同
    bool IsSame(const Element<2>& NewElement) const override;
    // 检查对象是否有效
    bool IsValid() const override;
    // 静态方法：检查输入的坐标是否构成有效线段
    static bool IsValid(
        const std::vector<std::array<double, 3>>& CoordsInput);

private:
    //--------------------------------------------------------------------
    // 成员变量
    //--------------------------------------------------------------------
    // 点1
    Point m_Point1{};
    // 点2
    Point m_Point2{};
};

#endif


