/*************************************************************************
【文件名】                 Face.hpp
【功能模块和目的】         面元素类声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <ostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <algorithm>

#include "Element.hpp"
#include "../Point/Point.hpp"

#ifndef FACE_HPP
#define FACE_HPP

/*************************************************************************
【类名】              Face
【功能】              表示三角形面元素的类，继承自 Element<3>
【接口说明】          提供构造函数、析构函数、设置和获取坐标和点的函数，
                      以及计算长度和面积的函数
【开发者及日期】      周子睿 2024/8/12
【更改记录】          无
*************************************************************************/
class Face : public Element<3> {
public:
    //--------------------------------------------------------------------
    // 内部异常类
    //--------------------------------------------------------------------
    // 表示共线点异常
    class ExceptionCollinearPoints : public invalid_argument {
    public:
        // 默认构造函数
        ExceptionCollinearPoints();
    };

    //--------------------------------------------------------------------
    // 必要的构造、析构、赋值行为
    //--------------------------------------------------------------------
    // 默认构造函数
    Face();
    // 通过坐标构造
    Face(const std::vector<std::array<double, 3>>& Coords);
    // 通过点构造
    Face(const std::array<Point, 3>& Points);
    //拷贝构造函数
    Face(const Face& Source);
    //赋值运算符overload
    Face& operator=(const Face& Source);
    // 析构函数
    virtual ~Face();

    //--------------------------------------------------------------------
    // 非静态设置器
    //--------------------------------------------------------------------
    // 设置坐标
    void SetCoordinates(
        const std::vector<std::array<double, 3>>& Coords) override;
    // 设置点
    void SetPoints(const std::array<Point, 3>& Points) override;

    //--------------------------------------------------------------------
    // 非静态获取器
    //--------------------------------------------------------------------
    // 获取坐标
    std::vector<std::array<double, 3>> GetCoordinates() const override;
    // 获取点
    std::array<Point, 3> GetPoints() const override;

    //--------------------------------------------------------------------
    // 字符串表示
    //--------------------------------------------------------------------
    // 获取对象的字符串表示
    std::string ToString() const override;

    //--------------------------------------------------------------------
    // 几何计算
    //--------------------------------------------------------------------
    // 获取曲线长度
    double GetLength() const override;
    // 获取面积
    double GetArea() const override;

    //--------------------------------------------------------------------
    // 验证功能
    //--------------------------------------------------------------------
    // 检查两个元素是否相同
    bool IsSame(const Element<3>& NewElement) const override;
    // 检查对象是否有效
    bool IsValid() const override;
    // 静态方法：检查输入的坐标是否构成有效面
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
    // 点3
    Point m_Point3{};
};

#endif




