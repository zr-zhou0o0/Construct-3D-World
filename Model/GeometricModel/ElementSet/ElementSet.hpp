/*************************************************************************
【文件名】                 ElementSet.hpp
【功能模块和目的】         元素集类基类模板声明及定义
【开发者及日期】           周子睿 2024/8/14
【更改记录】               无
*************************************************************************/

#include <numeric>
#include <vector>
#include <array>
#include <memory>
#include"../Point/Point.hpp"
#include"../Element/Element.hpp"
#include"../PointSet/PointSet.hpp"

#ifndef TEMPLATE_ELEMENTSET_HPP
#define TEMPLATE_ELEMENTSET_HPP

/*************************************************************************
【类名】             ElementSet
【功能】             元素集类基类模板
【接口说明】         提供元素集的管理和操作接口
【开发者及日期】     周子睿 2024/8/14
【更改记录】         无
*************************************************************************/
template<size_t M>
class ElementSet {
public:
    //--------------------------------------------------------------------
    //必要的构造、析构、赋值行为
    //--------------------------------------------------------------------
    //带点集指针的构造函数
    ElementSet(std::shared_ptr<PointSet> pPointSet);
    //带点集指针和新元素集的构造函数
    ElementSet(std::shared_ptr<PointSet> pPointSet, 
        const std::vector<std::array<int, M>>& NewElementSet);
    //拷贝构造函数
    ElementSet(const ElementSet& Source);
    //赋值运算符overload
    ElementSet& operator=(const ElementSet& Source);
    //虚析构函数
    virtual ~ElementSet() = default;

    //--------------------------------------------------------------------
    //元素集操作
    //--------------------------------------------------------------------
    //获取元素集
    virtual std::vector<std::array<unsigned int, M>> GetElementSet
    () const = 0;
    //获取指定索引的元素
    virtual std::vector<std::array<unsigned int, M>> GetElement(
        unsigned int uIndex) const;
    //获取元素集索引
    virtual std::vector<unsigned int> GetElementSetIndex() const;
    //查找元素
    virtual unsigned int FindElement(const Element<M>& NewElement)const;
    //删除元素（通过索引）
    virtual bool Delete(const unsigned int uIndex);
    //删除元素（通过点索引）
    virtual bool Delete(const std::array<unsigned int, M>& PointIndex);
    //添加元素（通过元素对象）
    virtual unsigned int Add(const Element<M>& NewElement);
    //添加元素（通过点索引数组）
    virtual unsigned int Add(const std::array<unsigned int, M>& Index);
    //添加元素（通过点对象数组）
    virtual unsigned int Add(const std::array<Point, M>& Points);
    //添加元素（通过坐标数组）
    virtual unsigned int Add(
        const std::vector<std::array<double, 3>>& Coordinates);
    //修改元素
    virtual bool Modify(unsigned int uElementIndex, 
        unsigned int uPointIndex, const Point& NewPoint);
    //修改元素（通过坐标）
    virtual bool Modify(unsigned int uElementIndex, 
        unsigned int uPointIndex, 
        const std::array<double, 3>& Coordinates);
    //获取元素中的点
    virtual std::array<unsigned int, M> GetPointsInElement(
        const unsigned int uElementIndex) const;
    //清空元素集
    void ClearElementSet();
    //获取元素总数
    virtual unsigned int GetTotalCount() const;
    //获取元素总长度
    virtual double GetTotalLength() const;
    //获取元素总面积
    virtual double GetTotalArea() const;

    //--------------------------------------------------------------------
    //异常类声明
    //--------------------------------------------------------------------
    //缺少参数异常
    class ExceptionMissingParams : public std::invalid_argument {
    public:
        ExceptionMissingParams();
    };
    //参数过多异常
    class ExceptionExcessParams : public std::invalid_argument {
    public:
        ExceptionExcessParams();
    };
    //重合点异常
    class ExceptionCoincidentPoints : public std::invalid_argument {
    public:
        ExceptionCoincidentPoints();
    };
    //类型不匹配异常
    class ExceptionTypeMismatch : public std::logic_error {
    public:
        ExceptionTypeMismatch();
    };
    //无效索引异常
    class ExceptionInvalidIndex : public std::out_of_range {
    public:
        ExceptionInvalidIndex();
    };
    //重复元素异常
    class ExceptionDuplicateElement : public std::invalid_argument {
    public:
        ExceptionDuplicateElement();
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

private:
    //元素集
    std::vector<std::array<unsigned int, M>> m_ElementSet = {};
    //点集指针
    std::shared_ptr<PointSet> m_pPointSet = nullptr;
};

/*************************************************************************
【函数名称】       ExceptionMissingParams
【函数功能】       构造缺少参数异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionMissingParams::ExceptionMissingParams()
: std::invalid_argument("Missing Parameters.") {
}

/*************************************************************************
【函数名称】       ExceptionExcessParams
【函数功能】       构造参数过多异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionExcessParams::ExceptionExcessParams()
: std::invalid_argument("Excess Parameters.") {
}

/*************************************************************************
【函数名称】       ExceptionCoincidentPoints
【函数功能】       构造重合点异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionCoincidentPoints::ExceptionCoincidentPoints()
: std::invalid_argument("Coincident Points.") {
}

/*************************************************************************
【函数名称】       ExceptionTypeMismatch
【函数功能】       构造类型不匹配异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionTypeMismatch::ExceptionTypeMismatch()
: std::logic_error("Type Mismatch.") {
}

/*************************************************************************
【函数名称】       ExceptionInvalidIndex
【函数功能】       构造无效索引异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionInvalidIndex::ExceptionInvalidIndex()
: std::out_of_range("Invalid Index.") {
}

/*************************************************************************
【函数名称】       ExceptionDuplicateElement
【函数功能】       构造重复元素异常
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionDuplicateElement::ExceptionDuplicateElement()
: std::invalid_argument("Duplicate Element.") {
}

/*************************************************************************
【函数名称】       ExceptionDuplicateElement
【函数功能】       求面积未定义
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionUndefinedArea::ExceptionUndefinedArea() 
: std::logic_error("Undefine Area.") {
}

/*************************************************************************
【函数名称】       ExceptionDuplicateElement
【函数功能】       求长度未定义
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionUndefinedLength::ExceptionUndefinedLength()
: std::logic_error("Undefined Length.") {
}

/*************************************************************************
【函数名称】       ElementSet
【函数功能】       构造函数，初始化点集指针
【入口参数】       std::shared_ptr<PointSet> pPointSet
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ElementSet(std::shared_ptr<PointSet> pPointSet): 
m_pPointSet(pPointSet) {
}

/*************************************************************************
【函数名称】       ElementSet
【函数功能】       构造函数，初始化点集指针和新元素集
【入口参数】       std::shared_ptr<PointSet> pPointSet, 
                   const std::vector<std::array<int, M>>& NewElementSet
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ElementSet(std::shared_ptr<PointSet> pPointSet, 
    const std::vector<std::array<int, M>>& NewElementSet) : 
    m_ElementSet(NewElementSet), m_pPointSet(pPointSet) {}

/*************************************************************************
【函数名称】       ElementSet
【函数功能】       拷贝构造函数
【入口参数】       const ElementSet& Source
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>::ElementSet(const ElementSet& Source) : 
m_ElementSet(Source.m_ElementSet), m_pPointSet(Source.m_pPointSet) {
}

/*************************************************************************
【函数名称】       ElementSet
【函数功能】       赋值运算符overload
【入口参数】       const ElementSet& Source
【出口参数】       无
【返回值】         ElementSet
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
ElementSet<M>& ElementSet<M>::operator=(const ElementSet& Source) {
    if (this != &Source) {
        m_ElementSet = Source.m_ElementSet;
        m_pPointSet = Source.m_pPointSet;
    }
    return *this;
}

/*************************************************************************
【函数名称】       ClearElementSet
【函数功能】       清空元素集
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 

【更改记录】       无
*************************************************************************/
template<size_t M>
void ElementSet<M>::ClearElementSet() {
    m_ElementSet.clear();
}

/*************************************************************************
【函数名称】       ElementSet<M>::GetElementSetIndex
【函数功能】       获取元素集合的索引列表
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<unsigned int> 元素集合的索引列表
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
std::vector<unsigned int> ElementSet<M>::GetElementSetIndex() const {
    std::vector<unsigned int> ElementSetIndex(GetTotalCount());
    std::iota(ElementSetIndex.begin(), ElementSetIndex.end(), 0);
    return ElementSetIndex;
}

/*************************************************************************
【函数名称】       ElementSet<M>::GetElement
【函数功能】       获取指定索引的元素
【入口参数】       unsigned int uIndex 元素的索引
【出口参数】       无
【返回值】         std::vector<std::array<unsigned int, M>> 指定索引的元素
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
std::vector<std::array<unsigned int, M>> ElementSet<M>::GetElement(
    unsigned int uIndex) const {
    std::vector<std::array<unsigned int, M>> Result;
    auto AElementSet = GetElementSet();
    if (uIndex < AElementSet.size()) {
        // 将指定索引的元素添加到结果中
        Result.push_back(AElementSet[uIndex]);
    }
    return Result;
}

/*************************************************************************
【函数名称】       ElementSet<M>::FindElement
【函数功能】       查找指定元素在集合中的索引
【入口参数】       const Element<M>& NewElement 要查找的元素
【出口参数】       无
【返回值】         unsigned int 元素的索引，如果未找到则返回 UINT_MAX
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
unsigned int ElementSet<M>::FindElement(const Element<M>& NewElement) const {
    for (unsigned int i = 0; i < m_ElementSet.size(); ++i) {
        std::array<Point, M> Points;
        for (size_t j = 0; j < M; ++j) {
            Points[j] = m_pPointSet->GetPointByIndex(m_ElementSet[i][j]);
        }

        if (NewElement.IsSame(Element<M>(Points))) {
            return i;
        }
    }
    return UINT_MAX;
}

/*************************************************************************
【函数名称】       ElementSet<M>::Delete
【函数功能】       删除指定索引的元素
【入口参数】       const unsigned int uIndex 要删除的元素索引
【出口参数】       无
【返回值】         bool 删除是否成功
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
bool ElementSet<M>::Delete(const unsigned int uIndex) {
    if (uIndex != UINT_MAX && uIndex < m_ElementSet.size()) {
        m_ElementSet.erase(m_ElementSet.begin() + uIndex);
        return true;
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       ElementSet<M>::Delete
【函数功能】       删除指定点索引数组的元素
【入口参数】       const std::array<unsigned int, M>& PointIndex 
【出口参数】       无
【返回值】         bool 删除是否成功
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
bool ElementSet<M>::Delete(const std::array<unsigned int, M>& PointIndex) {
    auto AElement = std::find(
        m_ElementSet.begin(), m_ElementSet.end(), PointIndex);
    if (AElement != m_ElementSet.end()) {
        m_ElementSet.erase(AElement);
        return true;
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       ElementSet<M>::Add
【函数功能】       添加一个新元素
【入口参数】       const Element<M>& NewElement 新元素
【出口参数】       无
【返回值】         unsigned int 新元素的索引
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
unsigned int ElementSet<M>::Add(const Element<M>& NewElement) {
    if (!NewElement.IsValid()) {
        throw ExceptionCoincidentPoints();
    }
    const auto& Points = NewElement.GetPoints();
    std::array<unsigned int, M> Indices;
    for (size_t i = 0; i < M; ++i) {
        Indices[i] = m_pPointSet->AddPoint(Points[i]);
    }
    if (this->FindElement(NewElement) == UINT_MAX) {
        m_ElementSet.push_back(Indices);
        return m_ElementSet.size() - 1;
    }
    else {
        throw ExceptionDuplicateElement();
    }
}

/*************************************************************************
【函数名称】       ElementSet<M>::Add
【函数功能】       添加一个新元素，通过点索引数组
【入口参数】       const std::array<unsigned int, M>& Index 点索引数组
【出口参数】       无
【返回值】         unsigned int 新元素的索引
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
unsigned int ElementSet<M>::Add(const std::array<unsigned int, M>& Index) {
    std::array<Point, M> Points;
    for (size_t i = 0; i < M; ++i) {
        Points[i] = m_pPointSet->GetPointByIndex(Index[i]);
    }
    return Add(Element<M>(Points));
}

/*************************************************************************
【函数名称】       ElementSet<M>::Add
【函数功能】       添加一个新元素，通过点数组
【入口参数】       const std::array<Point, M>& Points 点数组
【出口参数】       无
【返回值】         unsigned int 新元素的索引
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
unsigned int ElementSet<M>::Add(const std::array<Point, M>& Points) {
    return Add(Element<M>(Points));
}

/*************************************************************************
【函数名称】       ElementSet<M>::Add
【函数功能】       添加一个新元素，通过坐标数组
【入口参数】       const std::vector<std::array<double, 3>>& Coordinates 
【出口参数】       无
【返回值】         unsigned int 新元素的索引
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
unsigned int ElementSet<M>::Add(
    const std::vector<std::array<double, 3>>& Coordinates) {
    if (Coordinates.size() < M) {
        throw ExceptionMissingParams();
    }
    else if (Coordinates.size() > M) {
        throw ExceptionExcessParams();
    }
    else {
        std::array<Point, M> Points;
        for (size_t i = 0; i < M; ++i) {
            Points[i] = Point({ Coordinates[i] });
        }
        return Add(Element<M>(Points));
    }
}

/*************************************************************************
【函数名称】       ElementSet<M>::Modify
【函数功能】       修改指定元素的指定点
【入口参数】       unsigned int uElementIndex 元素索引
                  unsigned int uPointIndex 点索引
                  const Point& NewPoint 新点
【出口参数】       无
【返回值】         bool 修改是否成功
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
bool ElementSet<M>::Modify(
    unsigned int uElementIndex, unsigned int uPointIndex, 
    const Point& NewPoint) {
    if (uElementIndex != UINT_MAX 
        && uElementIndex < m_ElementSet.size() && uPointIndex < M) {
        std::array<Point, M> NewElementPoints;
        for (size_t i = 0; i < M; ++i) {
            if (i == uPointIndex) {
                NewElementPoints[i] = NewPoint;
            }
            else {
                NewElementPoints[i] = m_pPointSet->GetPointByIndex
                (GetElementSet()[uElementIndex][i]);
            }
        }
        Element<M> NewElement(NewElementPoints);
        unsigned int uNewIndex = m_pPointSet->AddPoint(NewPoint);
        if (FindElement(NewElement) != UINT_MAX) {
            throw ExceptionDuplicateElement();
        }
        else {
            m_ElementSet[uElementIndex][uPointIndex] = uNewIndex;
            return true;
        }
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
【函数名称】       ElementSet<M>::Modify
【函数功能】       修改指定元素的指定点，通过坐标数组
【入口参数】       unsigned int uElementIndex 元素索引
                  unsigned int uPointIndex 点索引
                  const std::array<double, 3>& Coordinates 新点的坐标
【出口参数】       无
【返回值】         bool 修改是否成功
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
bool ElementSet<M>::Modify(unsigned int uElementIndex, 
    unsigned int uPointIndex, const std::array<double, 3>& Coordinates) {
    return Modify(uElementIndex, uPointIndex, Point({ Coordinates }));
}

/*************************************************************************
【函数名称】       ElementSet<M>::GetPointsInElement
【函数功能】       获取指定元素索引的点集
【入口参数】       const unsigned int uElementIndex - 元素索引
【出口参数】       无
【返回值】         std::array<unsigned int, M> - 返回指定元素索引的点集
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
std::array<unsigned int, M> ElementSet<M>::GetPointsInElement(
    const unsigned int uElementIndex) const {
    if (uElementIndex >= m_ElementSet.size() || uElementIndex == UINT_MAX) {
        throw ExceptionInvalidIndex();
    }
    return m_ElementSet[uElementIndex];
}

/*************************************************************************
【函数名称】       ElementSet<M>::GetTotalCount
【函数功能】       获取元素集合的总数
【入口参数】       无
【出口参数】       无
【返回值】         unsigned int - 返回元素集合的总数
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
unsigned int ElementSet<M>::GetTotalCount() const {
    return static_cast<unsigned int>(m_ElementSet.size());
}

/*************************************************************************
【函数名称】       ElementSet<M>::GetTotalLength
【函数功能】       获取元素集合的总长度
【入口参数】       无
【出口参数】       无
【返回值】         double - 抛出异常，表示未定义长度
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
double ElementSet<M>::GetTotalLength() const {
    throw ExceptionUndefinedLength();
}

/*************************************************************************
【函数名称】       ElementSet<M>::GetTotalArea
【函数功能】       获取元素集合的总面积
【入口参数】       无
【出口参数】       无
【返回值】         double - 抛出异常，表示未定义面积
【开发者及日期】   周子睿 2024/8/14
【更改记录】       无
*************************************************************************/
template<size_t M>
double ElementSet<M>::GetTotalArea() const {
    throw ExceptionUndefinedArea();
}


#endif 







