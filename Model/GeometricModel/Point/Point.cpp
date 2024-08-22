/*************************************************************************
【文件名】                 Point.cpp
【功能模块和目的】         三维点类定义
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include<ostream>
#include<sstream>
#include<string>
#include<array>
#include<vector>
#include<algorithm>
#include <cmath>

#include"Point.hpp"

/*************************************************************************
    【类名】             ExceptionEmptyCoords
    【功能】             表示空坐标异常
    【接口说明】         继承自 invalid_argument
    【开发者及日期】     周子睿 2024/8/12
    【更改记录】         无
*************************************************************************/
Point::ExceptionEmptyCoords::ExceptionEmptyCoords()
: invalid_argument("Empty Coordinates.") {
}

/*************************************************************************
   【类名】             ExceptionExcessParams
   【功能】             表示参数过多异常
   【接口说明】         继承自 invalid_argument
   【开发者及日期】     周子睿 2024/8/12
   【更改记录】         无
*************************************************************************/
Point::ExceptionExcessParams::ExceptionExcessParams()
: invalid_argument("Excess Parameters.") {
}

/*************************************************************************
    【函数名称】       Point（默认构造函数）
    【函数功能】       创建一个默认的Point对象
    【参数】           无
    【返回值】         无
    【开发者及日期】   周子睿 2024/8/12
    【更改记录】       无
*************************************************************************/
Point::Point() {
}

/*************************************************************************
    【函数名称】       Point（带参数构造函数）
    【函数功能】       使用给定坐标创建Point对象
    【参数】           rCoordinates（输入参数）：包含坐标的向量
    【返回值】         无
    【开发者及日期】   周子睿 2024/8/12
    【更改记录】       无
*************************************************************************/
Point::Point(const std::vector<std::array<double, 3>>& NewCoords) 
{
    SetCoordinates(NewCoords);
}

/*************************************************************************
    【函数名称】       ~Point
    【函数功能】       Point类的析构函数
    【参数】           无
    【返回值】         无
    【开发者及日期】   周子睿 2024/8/12
    【更改记录】       无
*************************************************************************/
Point::~Point() {}

/*************************************************************************
【函数名称】       Point拷贝构造函数
【函数功能】       创建Point对象
【参数】           const Point& Source
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Point::Point(const Point& Source) {
    m_Coordinates = Source.m_Coordinates;
}

/*************************************************************************
   【函数名称】       operator=
   【函数功能】       Point类的赋值运算符重载
   【参数】           Source（输入参数）：要复制的Point对象
   【返回值】         返回当前对象的引用
   【开发者及日期】   周子睿 2024/8/12
   【更改记录】       无
*************************************************************************/
Point& Point::operator=(const Point& Source) {
    if (this != &Source) {
        SetCoordinates(Source.GetCoordinates());
    }
    return *this;
}

/*************************************************************************
    【函数名称】       SetCoordinates
    【函数功能】       设置点的坐标
    【参数】           rCoordinates（输入参数）：包含新坐标的向量
    【返回值】         无
    【开发者及日期】   周子睿 2024/8/12
    【更改记录】       无
*************************************************************************/
void Point::SetCoordinates(
    const std::vector<std::array<double, 3>>& NewCoords) {
    if (NewCoords.empty()) {
        throw ExceptionEmptyCoords();
    }
    else if (NewCoords.size() > 1) {
        throw ExceptionExcessParams();
    }
    else {
        m_Coordinates = NewCoords[0];
    }
}

/*************************************************************************
   【函数名称】       GetCoordinates
   【函数功能】       获取点的坐标
   【参数】           无
   【返回值】         返回包含点坐标的向量
   【开发者及日期】   周子睿 2024/8/12
   【更改记录】       无
*************************************************************************/
std::vector<std::array<double, 3>> Point::GetCoordinates() const {
    std::vector<std::array<double, 3>> rCoordinatesVector;
    rCoordinatesVector.push_back(m_Coordinates);
    return rCoordinatesVector;
}

/*************************************************************************
   【函数名称】       IsSame
   【函数功能】       比较当前点与给定坐标是否相同
   【参数】           rCoordinates（输入参数）：要比较的坐标向量
   【返回值】         如果相同返回true，否则返回false
   【开发者及日期】   周子睿 2024/8/12
   【更改记录】       无
*************************************************************************/
bool Point::IsSame(
    const std::vector<std::array<double, 3>>& NewCoords) const {
    if (NewCoords.empty()) {
        throw ExceptionEmptyCoords();
        return false;
    }
    else if (NewCoords.size() > 1) {
        throw ExceptionExcessParams();
        return false;
    }
    else {
        return m_Coordinates == NewCoords[0];
    }
}

/*************************************************************************
    【函数名称】       IsSame
    【函数功能】       比较两个点是否相同
    【参数】           NewPoint（输入参数）：要比较的Point对象
    【返回值】         如果相同返回true，否则返回false
    【开发者及日期】   周子睿 2024/8/12
    【更改记录】       无
*************************************************************************/
bool Point::IsSame(const Point& NewPoint) const {
    return m_Coordinates == NewPoint.m_Coordinates;
}

/*************************************************************************
    【函数名称】       IsCollinear
    【函数功能】       判断当前点与其他两个点是否共线
    【参数】           Point1, p2（输入参数）：要判断的其他两个点
    【返回值】         如果共线返回true，否则返回false
    【开发者及日期】   周子睿 2024/8/12
    【更改记录】       无
*************************************************************************/
bool Point::IsCollinear(const Point& Point1, const Point& Point2) const {
    return Point::IsCollinear(*this, Point1, Point2);
}

/*************************************************************************
   【函数名称】       GetDistance
   【函数功能】       计算当前点与另一个点的距离
   【参数】           NewPoint（输入参数）：要计算距离的另一个点
   【返回值】         返回两点之间的距离
   【开发者及日期】   周子睿 2024/8/12
   【更改记录】       无
*************************************************************************/
double Point::GetDistance(const Point& NewPoint) const {
    return Point::GetDistance(*this, NewPoint);
}

/*************************************************************************
【函数名称】       IsCollinear
【函数功能】       判断给定的坐标点是否共线
【参数】           rCoordinates（输入参数）：包含坐标的向量
【返回值】         如果点共线或少于三个点返回true，否则返回false
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Point::IsCollinear(
    const std::vector<std::array<double, 3>>& NewCoords) {
    if (NewCoords.size() == 0 ) {
        throw ExceptionEmptyCoords();
    }
    else if (NewCoords.size() < 3 && NewCoords.size() > 0) {
        return IsCollinear(
            Point(std::vector<std::array<double, 3>>{NewCoords[0]}),
            Point(std::vector<std::array<double, 3>>{NewCoords[1]}),
            Point(std::vector<std::array<double, 3>>{NewCoords[2]}));
    }
    else if (NewCoords.size() > 3) {
        throw ExceptionExcessParams();
    }
}

/*************************************************************************
【函数名称】       IsCollinear
【函数功能】       判断三个点是否共线
【参数】           Point1, Point2, p3（输入参数）：三个待判断的点
【返回值】         如果三点共线返回true，否则返回false
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Point::IsCollinear(
    const Point& Point1, const Point& Point2, const Point& Point3) {
    const double rEpsilon = 1e-9;  // 定义一个小的误差容限

    double rX1 = Point2.m_Coordinates[0] - Point1.m_Coordinates[0];
    double rY1 = Point2.m_Coordinates[1] - Point1.m_Coordinates[1];
    double rZ1 = Point2.m_Coordinates[2] - Point1.m_Coordinates[2];

    double rX2 = Point3.m_Coordinates[0] - Point1.m_Coordinates[0];
    double rY2 = Point3.m_Coordinates[1] - Point1.m_Coordinates[1];
    double rZ2 = Point3.m_Coordinates[2] - Point1.m_Coordinates[2];

    // 计算叉积的各分量
    double rCrossX = rY1 * rZ2 - rZ1 * rY2;
    double rCrossY = rZ1 * rX2 - rX1 * rZ2;
    double rCrossZ = rX1 * rY2 - rY1 * rX2;

    // 检查叉积是否接近零向量
    return (std::abs(rCrossX) < rEpsilon)
        && (std::abs(rCrossY) < rEpsilon)
        && (std::abs(rCrossZ) < rEpsilon);
}

/*************************************************************************
【函数名称】       GetDistance
【函数功能】       计算两点之间的距离
【参数】           NewPoint1, NewPoint2（输入参数）：要计算距离的两个点
【返回值】         返回两点之间的欧几里得距离
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
double Point::GetDistance(const Point& NewPoint1, const Point& NewPoint2) {
    double rDX = NewPoint1.m_Coordinates[0] - NewPoint2.m_Coordinates[0];
    double rDY = NewPoint1.m_Coordinates[1] - NewPoint2.m_Coordinates[1];
    double rDZ = NewPoint1.m_Coordinates[2] - NewPoint2.m_Coordinates[2];

    return std::sqrt(rDX * rDX + rDY * rDY + rDZ * rDZ);
}