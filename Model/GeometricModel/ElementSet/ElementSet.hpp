/*************************************************************************
���ļ�����                 ElementSet.hpp
������ģ���Ŀ�ġ�         Ԫ�ؼ������ģ������������
�������߼����ڡ�           ����� 2024/8/14
�����ļ�¼��               ��
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
��������             ElementSet
�����ܡ�             Ԫ�ؼ������ģ��
���ӿ�˵����         �ṩԪ�ؼ��Ĺ���Ͳ����ӿ�
�������߼����ڡ�     ����� 2024/8/14
�����ļ�¼��         ��
*************************************************************************/
template<size_t M>
class ElementSet {
public:
    //--------------------------------------------------------------------
    //��Ҫ�Ĺ��졢��������ֵ��Ϊ
    //--------------------------------------------------------------------
    //���㼯ָ��Ĺ��캯��
    ElementSet(std::shared_ptr<PointSet> pPointSet);
    //���㼯ָ�����Ԫ�ؼ��Ĺ��캯��
    ElementSet(std::shared_ptr<PointSet> pPointSet, 
        const std::vector<std::array<int, M>>& NewElementSet);
    //�������캯��
    ElementSet(const ElementSet& Source);
    //��ֵ�����overload
    ElementSet& operator=(const ElementSet& Source);
    //����������
    virtual ~ElementSet() = default;

    //--------------------------------------------------------------------
    //Ԫ�ؼ�����
    //--------------------------------------------------------------------
    //��ȡԪ�ؼ�
    virtual std::vector<std::array<unsigned int, M>> GetElementSet
    () const = 0;
    //��ȡָ��������Ԫ��
    virtual std::vector<std::array<unsigned int, M>> GetElement(
        unsigned int uIndex) const;
    //��ȡԪ�ؼ�����
    virtual std::vector<unsigned int> GetElementSetIndex() const;
    //����Ԫ��
    virtual unsigned int FindElement(const Element<M>& NewElement)const;
    //ɾ��Ԫ�أ�ͨ��������
    virtual bool Delete(const unsigned int uIndex);
    //ɾ��Ԫ�أ�ͨ����������
    virtual bool Delete(const std::array<unsigned int, M>& PointIndex);
    //���Ԫ�أ�ͨ��Ԫ�ض���
    virtual unsigned int Add(const Element<M>& NewElement);
    //���Ԫ�أ�ͨ�����������飩
    virtual unsigned int Add(const std::array<unsigned int, M>& Index);
    //���Ԫ�أ�ͨ����������飩
    virtual unsigned int Add(const std::array<Point, M>& Points);
    //���Ԫ�أ�ͨ���������飩
    virtual unsigned int Add(
        const std::vector<std::array<double, 3>>& Coordinates);
    //�޸�Ԫ��
    virtual bool Modify(unsigned int uElementIndex, 
        unsigned int uPointIndex, const Point& NewPoint);
    //�޸�Ԫ�أ�ͨ�����꣩
    virtual bool Modify(unsigned int uElementIndex, 
        unsigned int uPointIndex, 
        const std::array<double, 3>& Coordinates);
    //��ȡԪ���еĵ�
    virtual std::array<unsigned int, M> GetPointsInElement(
        const unsigned int uElementIndex) const;
    //���Ԫ�ؼ�
    void ClearElementSet();
    //��ȡԪ������
    virtual unsigned int GetTotalCount() const;
    //��ȡԪ���ܳ���
    virtual double GetTotalLength() const;
    //��ȡԪ�������
    virtual double GetTotalArea() const;

    //--------------------------------------------------------------------
    //�쳣������
    //--------------------------------------------------------------------
    //ȱ�ٲ����쳣
    class ExceptionMissingParams : public std::invalid_argument {
    public:
        ExceptionMissingParams();
    };
    //���������쳣
    class ExceptionExcessParams : public std::invalid_argument {
    public:
        ExceptionExcessParams();
    };
    //�غϵ��쳣
    class ExceptionCoincidentPoints : public std::invalid_argument {
    public:
        ExceptionCoincidentPoints();
    };
    //���Ͳ�ƥ���쳣
    class ExceptionTypeMismatch : public std::logic_error {
    public:
        ExceptionTypeMismatch();
    };
    //��Ч�����쳣
    class ExceptionInvalidIndex : public std::out_of_range {
    public:
        ExceptionInvalidIndex();
    };
    //�ظ�Ԫ���쳣
    class ExceptionDuplicateElement : public std::invalid_argument {
    public:
        ExceptionDuplicateElement();
    };
    //δ��������쳣��
    class ExceptionUndefinedArea : public std::logic_error {
    public:
        ExceptionUndefinedArea();
    };
    //δ�����ܳ��쳣��
    class ExceptionUndefinedLength : public std::logic_error {
    public:
        ExceptionUndefinedLength();
    };

private:
    //Ԫ�ؼ�
    std::vector<std::array<unsigned int, M>> m_ElementSet = {};
    //�㼯ָ��
    std::shared_ptr<PointSet> m_pPointSet = nullptr;
};

/*************************************************************************
���������ơ�       ExceptionMissingParams
���������ܡ�       ����ȱ�ٲ����쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionMissingParams::ExceptionMissingParams()
: std::invalid_argument("Missing Parameters.") {
}

/*************************************************************************
���������ơ�       ExceptionExcessParams
���������ܡ�       ������������쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionExcessParams::ExceptionExcessParams()
: std::invalid_argument("Excess Parameters.") {
}

/*************************************************************************
���������ơ�       ExceptionCoincidentPoints
���������ܡ�       �����غϵ��쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionCoincidentPoints::ExceptionCoincidentPoints()
: std::invalid_argument("Coincident Points.") {
}

/*************************************************************************
���������ơ�       ExceptionTypeMismatch
���������ܡ�       �������Ͳ�ƥ���쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionTypeMismatch::ExceptionTypeMismatch()
: std::logic_error("Type Mismatch.") {
}

/*************************************************************************
���������ơ�       ExceptionInvalidIndex
���������ܡ�       ������Ч�����쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionInvalidIndex::ExceptionInvalidIndex()
: std::out_of_range("Invalid Index.") {
}

/*************************************************************************
���������ơ�       ExceptionDuplicateElement
���������ܡ�       �����ظ�Ԫ���쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionDuplicateElement::ExceptionDuplicateElement()
: std::invalid_argument("Duplicate Element.") {
}

/*************************************************************************
���������ơ�       ExceptionDuplicateElement
���������ܡ�       �����δ����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionUndefinedArea::ExceptionUndefinedArea() 
: std::logic_error("Undefine Area.") {
}

/*************************************************************************
���������ơ�       ExceptionDuplicateElement
���������ܡ�       �󳤶�δ����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ExceptionUndefinedLength::ExceptionUndefinedLength()
: std::logic_error("Undefined Length.") {
}

/*************************************************************************
���������ơ�       ElementSet
���������ܡ�       ���캯������ʼ���㼯ָ��
����ڲ�����       std::shared_ptr<PointSet> pPointSet
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ElementSet(std::shared_ptr<PointSet> pPointSet): 
m_pPointSet(pPointSet) {
}

/*************************************************************************
���������ơ�       ElementSet
���������ܡ�       ���캯������ʼ���㼯ָ�����Ԫ�ؼ�
����ڲ�����       std::shared_ptr<PointSet> pPointSet, 
                   const std::vector<std::array<int, M>>& NewElementSet
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ElementSet(std::shared_ptr<PointSet> pPointSet, 
    const std::vector<std::array<int, M>>& NewElementSet) : 
    m_ElementSet(NewElementSet), m_pPointSet(pPointSet) {}

/*************************************************************************
���������ơ�       ElementSet
���������ܡ�       �������캯��
����ڲ�����       const ElementSet& Source
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
ElementSet<M>::ElementSet(const ElementSet& Source) : 
m_ElementSet(Source.m_ElementSet), m_pPointSet(Source.m_pPointSet) {
}

/*************************************************************************
���������ơ�       ElementSet
���������ܡ�       ��ֵ�����overload
����ڲ�����       const ElementSet& Source
�����ڲ�����       ��
������ֵ��         ElementSet
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
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
���������ơ�       ClearElementSet
���������ܡ�       ���Ԫ�ؼ�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 

�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
void ElementSet<M>::ClearElementSet() {
    m_ElementSet.clear();
}

/*************************************************************************
���������ơ�       ElementSet<M>::GetElementSetIndex
���������ܡ�       ��ȡԪ�ؼ��ϵ������б�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<unsigned int> Ԫ�ؼ��ϵ������б�
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
std::vector<unsigned int> ElementSet<M>::GetElementSetIndex() const {
    std::vector<unsigned int> ElementSetIndex(GetTotalCount());
    std::iota(ElementSetIndex.begin(), ElementSetIndex.end(), 0);
    return ElementSetIndex;
}

/*************************************************************************
���������ơ�       ElementSet<M>::GetElement
���������ܡ�       ��ȡָ��������Ԫ��
����ڲ�����       unsigned int uIndex Ԫ�ص�����
�����ڲ�����       ��
������ֵ��         std::vector<std::array<unsigned int, M>> ָ��������Ԫ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
std::vector<std::array<unsigned int, M>> ElementSet<M>::GetElement(
    unsigned int uIndex) const {
    std::vector<std::array<unsigned int, M>> Result;
    auto AElementSet = GetElementSet();
    if (uIndex < AElementSet.size()) {
        // ��ָ��������Ԫ����ӵ������
        Result.push_back(AElementSet[uIndex]);
    }
    return Result;
}

/*************************************************************************
���������ơ�       ElementSet<M>::FindElement
���������ܡ�       ����ָ��Ԫ���ڼ����е�����
����ڲ�����       const Element<M>& NewElement Ҫ���ҵ�Ԫ��
�����ڲ�����       ��
������ֵ��         unsigned int Ԫ�ص����������δ�ҵ��򷵻� UINT_MAX
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
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
���������ơ�       ElementSet<M>::Delete
���������ܡ�       ɾ��ָ��������Ԫ��
����ڲ�����       const unsigned int uIndex Ҫɾ����Ԫ������
�����ڲ�����       ��
������ֵ��         bool ɾ���Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
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
���������ơ�       ElementSet<M>::Delete
���������ܡ�       ɾ��ָ�������������Ԫ��
����ڲ�����       const std::array<unsigned int, M>& PointIndex 
�����ڲ�����       ��
������ֵ��         bool ɾ���Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
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
���������ơ�       ElementSet<M>::Add
���������ܡ�       ���һ����Ԫ��
����ڲ�����       const Element<M>& NewElement ��Ԫ��
�����ڲ�����       ��
������ֵ��         unsigned int ��Ԫ�ص�����
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
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
���������ơ�       ElementSet<M>::Add
���������ܡ�       ���һ����Ԫ�أ�ͨ������������
����ڲ�����       const std::array<unsigned int, M>& Index ����������
�����ڲ�����       ��
������ֵ��         unsigned int ��Ԫ�ص�����
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
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
���������ơ�       ElementSet<M>::Add
���������ܡ�       ���һ����Ԫ�أ�ͨ��������
����ڲ�����       const std::array<Point, M>& Points ������
�����ڲ�����       ��
������ֵ��         unsigned int ��Ԫ�ص�����
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
unsigned int ElementSet<M>::Add(const std::array<Point, M>& Points) {
    return Add(Element<M>(Points));
}

/*************************************************************************
���������ơ�       ElementSet<M>::Add
���������ܡ�       ���һ����Ԫ�أ�ͨ����������
����ڲ�����       const std::vector<std::array<double, 3>>& Coordinates 
�����ڲ�����       ��
������ֵ��         unsigned int ��Ԫ�ص�����
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
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
���������ơ�       ElementSet<M>::Modify
���������ܡ�       �޸�ָ��Ԫ�ص�ָ����
����ڲ�����       unsigned int uElementIndex Ԫ������
                  unsigned int uPointIndex ������
                  const Point& NewPoint �µ�
�����ڲ�����       ��
������ֵ��         bool �޸��Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
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
���������ơ�       ElementSet<M>::Modify
���������ܡ�       �޸�ָ��Ԫ�ص�ָ���㣬ͨ����������
����ڲ�����       unsigned int uElementIndex Ԫ������
                  unsigned int uPointIndex ������
                  const std::array<double, 3>& Coordinates �µ������
�����ڲ�����       ��
������ֵ��         bool �޸��Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
bool ElementSet<M>::Modify(unsigned int uElementIndex, 
    unsigned int uPointIndex, const std::array<double, 3>& Coordinates) {
    return Modify(uElementIndex, uPointIndex, Point({ Coordinates }));
}

/*************************************************************************
���������ơ�       ElementSet<M>::GetPointsInElement
���������ܡ�       ��ȡָ��Ԫ�������ĵ㼯
����ڲ�����       const unsigned int uElementIndex - Ԫ������
�����ڲ�����       ��
������ֵ��         std::array<unsigned int, M> - ����ָ��Ԫ�������ĵ㼯
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
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
���������ơ�       ElementSet<M>::GetTotalCount
���������ܡ�       ��ȡԪ�ؼ��ϵ�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         unsigned int - ����Ԫ�ؼ��ϵ�����
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
unsigned int ElementSet<M>::GetTotalCount() const {
    return static_cast<unsigned int>(m_ElementSet.size());
}

/*************************************************************************
���������ơ�       ElementSet<M>::GetTotalLength
���������ܡ�       ��ȡԪ�ؼ��ϵ��ܳ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         double - �׳��쳣����ʾδ���峤��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
double ElementSet<M>::GetTotalLength() const {
    throw ExceptionUndefinedLength();
}

/*************************************************************************
���������ơ�       ElementSet<M>::GetTotalArea
���������ܡ�       ��ȡԪ�ؼ��ϵ������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         double - �׳��쳣����ʾδ�������
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
double ElementSet<M>::GetTotalArea() const {
    throw ExceptionUndefinedArea();
}


#endif 







