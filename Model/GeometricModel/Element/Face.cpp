/*************************************************************************
【文件名】                 Face.cpp
【功能模块和目的】         面元素类定义
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cmath>

#include "Face.hpp"

/*************************************************************************
【函数名称】       ExceptionCollinearPoints::ExceptionCollinearPoints
【函数功能】       构造异常对象，表示当点共线时抛出的异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Face::ExceptionCollinearPoints::ExceptionCollinearPoints() 
: invalid_argument("Collinear Points.") {
}

/*************************************************************************
【函数名称】       Face::Face
【函数功能】       默认构造函数，初始化面元素
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Face::Face() : Element<3>() {
    SetPoints({ Point(), Point(), Point() });
}

/*************************************************************************
【函数名称】       Face::Face
【函数功能】       使用坐标构造面元素
【入口参数】       Coords - 三角面每个顶点的坐标
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Face::Face(const std::vector<std::array<double, 3>>& Coords): 
Element<3>() {
    SetCoordinates(Coords);
}

/*************************************************************************
【函数名称】       Face::Face
【函数功能】       使用点构造面元素
【入口参数】       Points - 三个顶点的点对象
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Face::Face(const std::array<Point, 3>& Points) : Element<3>() {
    SetPoints(Points);
}

/*************************************************************************
【函数名称】       Face拷贝构造函数
【函数功能】       创建Face对象
【参数】           const Face& Source
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Face::Face(const Face& Source) :
Element<3>(), m_Point1(Source.m_Point1), m_Point2(Source.m_Point2),
m_Point3(Source.m_Point3) {
}

/*************************************************************************
   【函数名称】       operator=
   【函数功能】       Face类的赋值运算符重载
   【参数】           Source（输入参数）：要复制的Face对象
   【返回值】         返回当前对象的引用
   【开发者及日期】   周子睿 2024/8/12
   【更改记录】       无
*************************************************************************/
Face& Face::operator=(const Face& Source) {
    if (this != &Source) {
        Element<3>::operator=(Source);
        m_Point1 = Source.m_Point1;
        m_Point2 = Source.m_Point2;
        m_Point3 = Source.m_Point3;
    }
    return *this;
}

/*************************************************************************
【函数名称】       Face::~Face
【函数功能】       析构函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Face::~Face() {}

/*************************************************************************
【函数名称】       Face::SetCoordinates
【函数功能】       设置面元素的坐标
【入口参数】       Coords - 三个顶点的坐标向量
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
void Face::SetCoordinates(
    const std::vector<std::array<double, 3>>& Coords) {
    if (Coords.size() < 3) {
        throw ExceptionMissingParams();
    }
    else if (Coords.size() > 3) {
        throw ExceptionExcessParams();
    }
    else {
        std::array<Point, 3> Points = {
            Point(std::vector<std::array<double, 3>>{Coords[0]}),
            Point(std::vector<std::array<double, 3>>{Coords[1]}),
            Point(std::vector<std::array<double, 3>>{Coords[2]})
        };
        if (!IsValid(Coords)) {
            throw ExceptionCoincidentPoints();
        }
        else {
            SetPoints(Points);
        }
    }
}

/*************************************************************************
【函数名称】       Face::SetPoints
【函数功能】       设置面元素的顶点
【入口参数】       Points - 包含三个顶点的数组
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
void Face::SetPoints(const std::array<Point, 3>& Points) {
    if (!IsValid({ Points[0].GetCoordinates()[0], 
                   Points[1].GetCoordinates()[0],
                   Points[2].GetCoordinates()[0] })) {
        throw ExceptionCoincidentPoints();
    }
    else {
        m_Point1 = Points[0];
        m_Point2 = Points[1];
        m_Point3 = Points[2];
        std::vector<std::array<double, 3>> Coordinates;
        Coordinates.push_back(m_Point1.GetCoordinates()[0]);
        Coordinates.push_back(m_Point2.GetCoordinates()[0]);
        Coordinates.push_back(m_Point3.GetCoordinates()[0]);
        Element<3>::SetCoordinates(Coordinates);
    }
}

/*************************************************************************
【函数名称】       Face::GetCoordinates
【函数功能】       获取面元素的坐标
【入口参数】       无
【出口参数】       无
【返回值】         返回一个包含三个顶点坐标的向量
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::vector<std::array<double, 3>> Face::GetCoordinates() const {
    std::vector<std::array<double, 3>> Coordinates;
    Coordinates.push_back(m_Point1.GetCoordinates()[0]);
    Coordinates.push_back(m_Point2.GetCoordinates()[0]);
    Coordinates.push_back(m_Point3.GetCoordinates()[0]);
    return Coordinates;
}

/*************************************************************************
【函数名称】       Face::GetPoints
【函数功能】       获取面元素的顶点
【入口参数】       无
【出口参数】       无
【返回值】         返回一个数组，包含三个顶点的点对象
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::array<Point, 3> Face::GetPoints() const {
    return { m_Point1, m_Point2, m_Point3 };
}

/*************************************************************************
【函数名称】       Face::ToString
【函数功能】       获取面元素的字符串表示
【入口参数】       无
【出口参数】       无
【返回值】         返回面元素的字符串表示
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::string Face::ToString() const {
    return "Face: " + Element<3>::ToString();
}

/*************************************************************************
【函数名称】       Face::GetLength
【函数功能】       计算面元素的边长总和
【入口参数】       无
【出口参数】       无
【返回值】         返回面元素的边长总和
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
double Face::GetLength() const {
    double rSide1 = Point::GetDistance(m_Point1, m_Point2);
    double rSide2 = Point::GetDistance(m_Point2, m_Point3);
    double rSide3 = Point::GetDistance(m_Point3, m_Point1);
    return rSide1 + rSide2 + rSide3;
}

/*************************************************************************
【函数名称】       Face::GetArea
【函数功能】       计算面元素的面积
【入口参数】       无
【出口参数】       无
【返回值】         返回面元素的面积
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
double Face::GetArea() const {
    // 使用海伦公式计算面积
    double rA = Point::GetDistance(m_Point1, m_Point2);
    double rB = Point::GetDistance(m_Point2, m_Point3);
    double rC = Point::GetDistance(m_Point3, m_Point1);
    double rS = (rA + rB + rC) / 2;
    return std::sqrt(rS * (rS - rA) * (rS - rB) * (rS - rC));
}

/*************************************************************************
【函数名称】       Face::IsSame
【函数功能】       检查两个面元素是否相同
【入口参数】       NewElement - 要比较的另一个元素
【出口参数】       无
【返回值】         返回布尔值，表示两个面元素是否相同
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Face::IsSame(const Element<3>& NewElement) const {
    const Face* AFace = dynamic_cast<const Face*>(&NewElement);
    if (!AFace) {
        throw ExceptionTypeMismatch();
    }
    std::array<Point, 3> ThisPoint = { m_Point1, m_Point2, m_Point3 };
    std::array<Point, 3> OtherPoint = AFace->GetPoints();

    // 检查所有点是否相同，考虑点的顺序可能不同
    for (const auto& APoint : ThisPoint) {
        bool bFind = false;
        for (const auto& OtherPoint : OtherPoint) {
            if (APoint.IsSame(OtherPoint)) {
                bFind = true;
                break;
            }
        }
        if (!bFind) {
            return false;
        }
    }
    return true;
}

/*************************************************************************
【函数名称】       Face::IsValid
【函数功能】       验证当前面元素的有效性
【入口参数】       无
【出口参数】       无
【返回值】         返回布尔值，表示当前面元素是否有效
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Face::IsValid() const {
    return IsValid(GetCoordinates());
}

/*************************************************************************
【函数名称】       Face::IsValid
【函数功能】       验证给定坐标是否构成有效的面元素
【入口参数】       CoordsInput - 三个顶点的坐标向量
【出口参数】       无
【返回值】         返回布尔值，表示坐标是否构成有效的面元素
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Face::IsValid(
    const std::vector<std::array<double, 3>>& CoordsInput) {
    Point Point1 = Point({ CoordsInput[0] });
    Point Point2 = Point({ CoordsInput[1] });
    Point Point3 = Point({ CoordsInput[2] });
    // 检查三点是否共线
    if (Point::IsCollinear(Point1, Point2, Point3)) {
        throw ExceptionCollinearPoints();
    }

    // 检查是否有重复的点
    if (Point1.IsSame(Point2) 
        || Point2.IsSame(Point3) 
        || Point3.IsSame(Point1)) {
        return false;
    }

    return true;
}



