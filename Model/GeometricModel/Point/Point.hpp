/*************************************************************************
【文件名】                 Point.hpp
【功能模块和目的】         三维点类声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include<ostream>
#include<sstream>
#include<string>
#include<array>
#include<vector>
#include<algorithm>
#include<memory>
#include<stdexcept>

using namespace std;

#ifndef POINT_HPP
#define POINT_HPP

/*************************************************************************
【类名】             Point
【功能】             表示三维空间中的点
【接口说明】         提供点的创建、坐标设置、获取、比较和计算功能
【开发者及日期】     周子睿 2024/8/12
【更改记录】         无
*************************************************************************/
class Point
{
public:
    //--------------------------------------------------------------------
    //必要的构造、析构、赋值行为
    //--------------------------------------------------------------------
    //默认构造函数
    Point();
    //带参构造函数
    Point(const std::vector<std::array<double, 3>>& NewCoords);
    //拷贝构造函数
    Point(const Point& Source);
    //赋值运算符overload
    Point& operator=(const Point& Source);
    //虚析构函数
    virtual ~Point();

    //--------------------------------------------------------------------
    //异常类
    //--------------------------------------------------------------------
    //空坐标异常
    class ExceptionEmptyCoords : public invalid_argument {
    public:
        ExceptionEmptyCoords();
    };
    //参数过多异常
    class ExceptionExcessParams : public invalid_argument {
    public:
        ExceptionExcessParams();
    };

    //--------------------------------------------------------------------
    //Setter/Getter
    //--------------------------------------------------------------------
    //设置坐标
    void SetCoordinates(
        const std::vector<std::array<double, 3>>& NewCoords);
    //获取坐标
    std::vector<std::array<double, 3>> GetCoordinates() const;

    //--------------------------------------------------------------------
    //其他成员函数
    //--------------------------------------------------------------------
    //比较坐标是否相同
    bool IsSame(
        const std::vector<std::array<double, 3>>& NewCoords) const;
    //比较点是否相同
    bool IsSame(const Point& NewPoint) const;
    //判断是否共线
    bool IsCollinear(const Point& Point1, const Point& Point2) const;
    //计算距离
    double GetDistance(const Point& NewPoint) const;

    //--------------------------------------------------------------------
    //静态成员函数
    //--------------------------------------------------------------------
    //判断给定坐标是否共线
    static bool IsCollinear(
        const std::vector<std::array<double, 3>>& NewCoords);
    //判断三点是否共线
    static bool IsCollinear(
        const Point& Point1, const Point& Point2, const Point& Point3);
    //计算两点距离
    static double GetDistance(
        const Point& NewPoint1, const Point& NewPoint2);

private:
    //--------------------------------------------------------------------
    //私有成员变量
    //--------------------------------------------------------------------
    //点的坐标
    std::array<double, 3> m_Coordinates{};
};


#endif
