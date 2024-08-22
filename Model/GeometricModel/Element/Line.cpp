/*************************************************************************
【文件名】                 Line.cpp
【功能模块和目的】         线元素类定义
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <array>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <memory>

#include "Element.hpp"
#include "../Point/Point.hpp"
#include "Line.hpp"

using namespace std;

/*************************************************************************
【函数名称】       ExceptionUndefinedArea::ExceptionUndefinedArea
【函数功能】       构造异常对象，表示线段没有定义面积
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Line::ExceptionUndefinedArea::ExceptionUndefinedArea()
: std::logic_error("Undefined line's area.") {

}

/*************************************************************************
【函数名称】       Line::Line
【函数功能】       默认构造函数，初始化线元素
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Line::Line() : Element<2>() {
    SetPoints({ Point(), Point() });
}

/*************************************************************************
【函数名称】       Line::Line
【函数功能】       使用坐标构造线元素
【入口参数】       Coords - 线段两个端点的坐标
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Line::Line(const std::vector<std::array<double, 3>>& Coords): 
Element<2>() {
    SetCoordinates(Coords);
}

/*************************************************************************
【函数名称】       Line::Line
【函数功能】       使用点构造线元素
【入口参数】       Points - 两个端点的点对象
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Line::Line(const std::array<Point, 2>& Points) : Element<2>() {
    SetPoints(Points);
}

/*************************************************************************
【函数名称】       Line拷贝构造函数
【函数功能】       创建Line对象
【参数】           const Line& Source
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Line::Line(const Line& Source) : 
Element<2>(), m_Point1(Source.m_Point1), m_Point2(Source.m_Point2) {
}

/*************************************************************************
   【函数名称】       operator=
   【函数功能】       Line类的赋值运算符重载
   【参数】           Source（输入参数）：要复制的Line对象
   【返回值】         返回当前对象的引用
   【开发者及日期】   周子睿 2024/8/12
   【更改记录】       无
*************************************************************************/
Line& Line::operator=(const Line& Source) {
    if (this != &Source) {
        Element<2>::operator=(Source);
        m_Point1 = Source.m_Point1;
        m_Point2 = Source.m_Point2;
    }
    return *this;
}

/*************************************************************************
【函数名称】       Line::~Line
【函数功能】       析构函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 

【更改记录】       无
*************************************************************************/
Line::~Line() {}

/*************************************************************************
【函数名称】       Line::SetCoordinates
【函数功能】       设置线元素的坐标
【入口参数】       Coords - 两个端点的坐标向量
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
void Line::SetCoordinates(
    const std::vector<std::array<double, 3>>& Coords) {
    if (Coords.size() < 2) {
        throw ExceptionMissingParams();
    }
    else if (Coords.size() > 2) {
        throw ExceptionExcessParams();
    }
    else {
        std::array<Point, 2> Points = {
            Point(std::vector<std::array<double, 3>>{Coords[0]}),
            Point(std::vector<std::array<double, 3>>{Coords[1]})
        };
        if (Points[0].IsSame(Points[1])) {
            throw ExceptionCoincidentPoints();
        }
        else {
            SetPoints(Points);
        }
    }
}

/*************************************************************************
【函数名称】       Line::SetPoints
【函数功能】       设置线元素的端点
【入口参数】       Points - 包含两个端点的数组
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
void Line::SetPoints(const std::array<Point, 2>& Points) {
    if (Points[0].IsSame(Points[1])) {
        throw ExceptionCoincidentPoints();
    }
    else {
        m_Point1 = Points[0];
        m_Point2 = Points[1];
        std::vector<std::array<double, 3>> Coordinates;
        Coordinates.push_back(m_Point1.GetCoordinates()[0]);
        Coordinates.push_back(m_Point2.GetCoordinates()[0]);
        Element<2>::SetCoordinates(Coordinates);
    }
}

/*************************************************************************
【函数名称】       Line::GetCoordinates
【函数功能】       获取线元素的坐标
【入口参数】       无
【出口参数】       无
【返回值】         返回一个包含两个端点坐标的向量
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::vector<std::array<double, 3>> Line::GetCoordinates() const {
    std::vector<std::array<double, 3>> Coordinates;
    Coordinates.push_back(m_Point1.GetCoordinates()[0]);
    Coordinates.push_back(m_Point2.GetCoordinates()[0]);
    return Coordinates;
}

/*************************************************************************
【函数名称】       Line::GetPoints
【函数功能】       获取线元素的端点
【入口参数】       无
【出口参数】       无
【返回值】         返回一个数组，包含两个端点的点对象
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::array<Point, 2> Line::GetPoints() const {
    return { m_Point1, m_Point2 };
}

/*************************************************************************
【函数名称】       Line::ToString
【函数功能】       获取线元素的字符串表示
【入口参数】       无
【出口参数】       无
【返回值】         返回线元素的字符串表示
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::string Line::ToString() const {
    return "Line: " + Element<2>::ToString();
}

/*************************************************************************
【函数名称】       Line::GetLength
【函数功能】       计算线元素的长度
【入口参数】       无
【出口参数】       无
【返回值】         返回线元素的长度
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
double Line::GetLength() const {
    return Point::GetDistance(m_Point1, m_Point2);
}

/*************************************************************************
【函数名称】       Line::GetArea
【函数功能】       获取线元素的面积，线段没有面积
【入口参数】       无
【出口参数】       无
【返回值】         无，抛出异常
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
double Line::GetArea() const {
    throw ExceptionUndefinedArea();
}

/*************************************************************************
【函数名称】       Line::IsSame
【函数功能】       检查两个线元素是否相同
【入口参数】       NewElement - 要比较的另一个元素
【出口参数】       无
【返回值】         返回布尔值，表示两个线元素是否相同
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Line::IsSame(const Element<2>& NewElement) const {
    const Line* ALine = dynamic_cast<const Line*>(&NewElement);
    if (!ALine) {
        throw ExceptionTypeMismatch();
    }
    return (m_Point1.IsSame(ALine->m_Point1) 
        && m_Point2.IsSame(ALine->m_Point2)) 
        || (m_Point1.IsSame(ALine->m_Point2) 
            && m_Point2.IsSame(ALine->m_Point1));
}

/*************************************************************************
【函数名称】       Line::IsValid
【函数功能】       验证当前线元素的有效性
【入口参数】       无
【出口参数】       无
【返回值】         返回布尔值，表示当前线元素是否有效
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Line::IsValid() const {
    return !m_Point1.IsSame(m_Point2);
}

/*************************************************************************
【函数名称】       Line::IsValid
【函数功能】       验证给定坐标是否构成有效的线元素
【入口参数】       CoordsInput - 两个端点的坐标向量
【出口参数】       无
【返回值】         返回布尔值，表示坐标是否构成有效的线元素
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Line::IsValid(
    const std::vector<std::array<double, 3>>& CoordsInput) {
    if (Point({ CoordsInput[0] }).IsSame
       (Point({ CoordsInput[1] }))) {
        return false;
    }
    return true;
}




