/*************************************************************************
【文件名】                 Element.hpp
【功能模块和目的】         元素类基类模板声明和定义
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include<ostream>
#include<sstream>
#include<string>
#include<array>
#include<vector>
#include<algorithm>

#include "../Point/Point.hpp"

using namespace std;

#ifndef TEMPLATE_ELEMENT_HPP
#define TEMPLATE_ELEMENT_HPP

/*************************************************************************
【类名】             Element<M>
【功能】             表示具有M个点的几何元素的基类模板
【接口说明】         提供元素的创建、设置、获取和验证功能
【开发者及日期】     周子睿 2024/8/12
【更改记录】         无
*************************************************************************/
template<size_t M>
class Element
{
public:
    //--------------------------------------------------------------------
    //异常类
    //--------------------------------------------------------------------
    // 参数不足异常
    class ExceptionMissingParams : public invalid_argument {
    public:
        ExceptionMissingParams();
    };

    // 参数过多异常
    class ExceptionExcessParams : public invalid_argument {
    public:
        ExceptionExcessParams();
    };

    // 重合点异常
    class ExceptionCoincidentPoints : public invalid_argument {
    public:
        ExceptionCoincidentPoints();
    };

    // 类型不匹配异常
    class ExceptionTypeMismatch : public std::logic_error {
    public:
        ExceptionTypeMismatch();
    };

    //未定义面积异常类
    class ExceptionUndefinedArea : public std::logic_error {
    public:
        ExceptionUndefinedArea();
    };
    //未定义周长异常类
    class ExceptionUndefinedLength : public std::logic_error {
    public:
        ExceptionUndefinedLength();
    };

    //--------------------------------------------------------------------
    //构造和析构函数
    //--------------------------------------------------------------------
    // 默认构造函数
    Element();
    // 使用坐标构造
    Element(const std::vector<std::array<double, 3>> CoordsInput);
    // 使用点构造
    Element(const std::array<Point, M>& Points);
    //拷贝构造函数
    Element(const Element& Source) = default;
    //赋值运算符overload
    Element& operator=(const Element& Source) = default;
    // 虚析构函数
    virtual ~Element() = default;

    //--------------------------------------------------------------------
    //设置函数
    //--------------------------------------------------------------------
    // 设置坐标
    virtual void SetCoordinates(
        const std::vector<std::array<double, 3>>& CoordsInput);
    // 设置点
    virtual void SetPoints(const std::array<Point, M>& Points);

    //--------------------------------------------------------------------
    //获取函数
    //--------------------------------------------------------------------
    // 获取坐标
    virtual std::vector<std::array<double, 3>> GetCoordinates() const;
    // 获取点
    virtual std::array<Point, M> GetPoints() const;
    // 转换为字符串
    virtual std::string ToString() const;
    // 获取长度
    virtual double GetLength() const;
    // 获取面积
    virtual double GetArea() const;

    //--------------------------------------------------------------------
    //其他函数
    //--------------------------------------------------------------------
    // 比较是否相同
    virtual bool IsSame(const Element<M>& NewElement)const;
    // 检查是否有效
    virtual bool IsValid()const;
    // 静态函数：检查坐标是否有效
    static bool IsValid(
        const std::vector<std::array<double, 3>>& CoordsInput);

private:
    // 存储元素坐标
    std::vector<std::array<double, 3>> m_Element{};

};


/*************************************************************************
【函数名称】       ExceptionMissingParams构造函数
【函数功能】       创建参数不足异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
Element<M>::ExceptionMissingParams::ExceptionMissingParams() : 
    invalid_argument("Missing Parameters.") {
}

/*************************************************************************
【函数名称】       ExceptionExcessParams构造函数
【函数功能】       创建参数过多异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
Element<M>::ExceptionExcessParams::ExceptionExcessParams() 
: invalid_argument("Excess Parameters.") {
}

/*************************************************************************
【函数名称】       ExceptionCoincidentPoints构造函数
【函数功能】       创建重合点异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
Element<M>::ExceptionCoincidentPoints::ExceptionCoincidentPoints() 
: invalid_argument("Coincident Points.") {
}

/*************************************************************************
【函数名称】       ExceptionTypeMismatch构造函数
【函数功能】       创建类型不匹配异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
Element<M>::ExceptionTypeMismatch::ExceptionTypeMismatch() 
: logic_error("Type mismatch: Expected Element<M> object.") {
}

/*************************************************************************
【函数名称】       ExceptionUndefinedArea构造函数
【函数功能】       面积未定义
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
Element<M>::ExceptionUndefinedArea::ExceptionUndefinedArea() 
: std::logic_error("Undefine Area.") {
}

/*************************************************************************
【函数名称】       ExceptionUndefinedLength构造函数
【函数功能】       周长未定义
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
Element<M>::ExceptionUndefinedLength::ExceptionUndefinedLength() 
: std::logic_error("Undefined Length.") {
}

/*************************************************************************
【函数名称】       Element默认构造函数
【函数功能】       创建一个空的Element对象
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
Element<M>::Element() {
}

/*************************************************************************
【函数名称】       Element构造函数（坐标输入）
【函数功能】       使用给定坐标创建Element对象
【入口参数】       CoordsInput：坐标输入
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
Element<M>::Element(
    const std::vector<std::array<double, 3>> CoordsInput) {
    SetCoordinates(CoordsInput);
}

/*************************************************************************
【函数名称】       Element构造函数（点输入）
【函数功能】       使用给定点创建Element对象
【入口参数】       Points：点输入
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
Element<M>::Element(const std::array<Point, M>& Points) {
    SetPoints(Points);
}

/*************************************************************************
【函数名称】       SetCoordinates
【函数功能】       设置元素的坐标
【入口参数】       CoordsInput：要设置的坐标
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
void Element<M>::SetCoordinates(
    const std::vector<std::array<double, 3>>& CoordsInput) {
    if (CoordsInput.size() < M) {
        throw ExceptionMissingParams();
    }
    else if (CoordsInput.size() > M) {
        throw ExceptionExcessParams();
    }
    else {
        if (IsValid(CoordsInput) == false) {
            throw ExceptionCoincidentPoints();
        }
        else {
            m_Element = CoordsInput;
        }
    }
}

/*************************************************************************
【函数名称】       SetPoints
【函数功能】       设置元素的点
【入口参数】       Points：要设置的点数组
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
void Element<M>::SetPoints(const std::array<Point, M>& Points) {
    std::vector<std::array<double, 3>> Coordinates;
    for (const auto& APoint : Points) {
        Coordinates.push_back(APoint.GetCoordinates()[0]);
    }
    if (IsValid(Coordinates) == false) {
        throw ExceptionCoincidentPoints();
    }
    else {
        SetCoordinates(Coordinates);
    }
}

/*************************************************************************
【函数名称】       ToString
【函数功能】       将元素转换为字符串表示
【入口参数】       无
【出口参数】       无
【返回值】         元素的字符串表示
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
std::string Element<M>::ToString() const {
    std::ostringstream Stream;
    std::for_each(m_Element.begin(), 
        m_Element.end(), [&Stream](const std::array<double, 3>& coord) {
        std::for_each(coord.begin(), coord.end(), 
            [&Stream](const double& e) {
            Stream << e << " ";
            });
        Stream << "\n";
        });
    return Stream.str();
}

/*************************************************************************
【函数名称】       GetCoordinates
【函数功能】       获取元素的坐标
【入口参数】       无
【出口参数】       无
【返回值】         元素的坐标向量
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
std::vector<std::array<double, 3>> Element<M>::GetCoordinates() const {
    return m_Element;
}

/*************************************************************************
【函数名称】       GetPoints
【函数功能】       获取元素的点
【入口参数】       无
【出口参数】       无
【返回值】         元素的点数组
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
std::array<Point, M> Element<M>::GetPoints() const {
    std::array<Point, M> Points;
    for (size_t i = 0; i < M; ++i) {
        Points[i] = Point(std::vector<std::array<double, 3>>{m_Element[i]});
    }
    return Points;
}

/*************************************************************************
【函数名称】       GetLength
【函数功能】       求周长
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
double Element<M>::GetLength() const {
    throw ExceptionUndefinedLength();
}

/*************************************************************************
【函数名称】       GetArea
【函数功能】       求面积
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
double Element<M>::GetArea() const {
    throw ExceptionUndefinedArea();
}

/*************************************************************************
【函数名称】       IsSame
【函数功能】       比较两个元素是否相同
【入口参数】       NewElement：要比较的元素
【出口参数】       无
【返回值】         如果相同返回true，否则返回false
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
bool Element<M>::IsSame(const Element<M>& NewElement)const {
    return this->GetCoordinates() == NewElement.GetCoordinates();
}

/*************************************************************************
【函数名称】       IsValid
【函数功能】       检查元素是否有效（点不重合）
【入口参数】       无
【出口参数】       无
【返回值】         如果有效返回true，否则返回false
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
bool Element<M>::IsValid() const {
    auto Points = GetPoints();
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = i + 1; j < M; ++j) {
            if (Points[i].IsSame(Points[j])) {
                return false;
            }
        }
    }
    return true;
}

/*************************************************************************
【函数名称】       IsValid（静态方法）
【函数功能】       检查给定坐标是否有效（点不重合）
【入口参数】       CoordsInput：要检查的坐标
【出口参数】       无
【返回值】         如果有效返回true，否则返回false
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
template<size_t M>
bool Element<M>::IsValid(
    const std::vector<std::array<double, 3>>& CoordsInput) {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = i + 1; j < M; ++j) {
            if (Point({ CoordsInput[i] }).IsSame
               (Point({ CoordsInput[j] }))) {
                return false;
            }
        }
    }
    return true;
}

#endif





