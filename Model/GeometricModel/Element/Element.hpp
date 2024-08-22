/*************************************************************************
���ļ�����                 Element.hpp
������ģ���Ŀ�ġ�         Ԫ�������ģ�������Ͷ���
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
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
��������             Element<M>
�����ܡ�             ��ʾ����M����ļ���Ԫ�صĻ���ģ��
���ӿ�˵����         �ṩԪ�صĴ��������á���ȡ����֤����
�������߼����ڡ�     ����� 2024/8/12
�����ļ�¼��         ��
*************************************************************************/
template<size_t M>
class Element
{
public:
    //--------------------------------------------------------------------
    //�쳣��
    //--------------------------------------------------------------------
    // ���������쳣
    class ExceptionMissingParams : public invalid_argument {
    public:
        ExceptionMissingParams();
    };

    // ���������쳣
    class ExceptionExcessParams : public invalid_argument {
    public:
        ExceptionExcessParams();
    };

    // �غϵ��쳣
    class ExceptionCoincidentPoints : public invalid_argument {
    public:
        ExceptionCoincidentPoints();
    };

    // ���Ͳ�ƥ���쳣
    class ExceptionTypeMismatch : public std::logic_error {
    public:
        ExceptionTypeMismatch();
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

    //--------------------------------------------------------------------
    //�������������
    //--------------------------------------------------------------------
    // Ĭ�Ϲ��캯��
    Element();
    // ʹ�����깹��
    Element(const std::vector<std::array<double, 3>> CoordsInput);
    // ʹ�õ㹹��
    Element(const std::array<Point, M>& Points);
    //�������캯��
    Element(const Element& Source) = default;
    //��ֵ�����overload
    Element& operator=(const Element& Source) = default;
    // ����������
    virtual ~Element() = default;

    //--------------------------------------------------------------------
    //���ú���
    //--------------------------------------------------------------------
    // ��������
    virtual void SetCoordinates(
        const std::vector<std::array<double, 3>>& CoordsInput);
    // ���õ�
    virtual void SetPoints(const std::array<Point, M>& Points);

    //--------------------------------------------------------------------
    //��ȡ����
    //--------------------------------------------------------------------
    // ��ȡ����
    virtual std::vector<std::array<double, 3>> GetCoordinates() const;
    // ��ȡ��
    virtual std::array<Point, M> GetPoints() const;
    // ת��Ϊ�ַ���
    virtual std::string ToString() const;
    // ��ȡ����
    virtual double GetLength() const;
    // ��ȡ���
    virtual double GetArea() const;

    //--------------------------------------------------------------------
    //��������
    //--------------------------------------------------------------------
    // �Ƚ��Ƿ���ͬ
    virtual bool IsSame(const Element<M>& NewElement)const;
    // ����Ƿ���Ч
    virtual bool IsValid()const;
    // ��̬��������������Ƿ���Ч
    static bool IsValid(
        const std::vector<std::array<double, 3>>& CoordsInput);

private:
    // �洢Ԫ������
    std::vector<std::array<double, 3>> m_Element{};

};


/*************************************************************************
���������ơ�       ExceptionMissingParams���캯��
���������ܡ�       �������������쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
Element<M>::ExceptionMissingParams::ExceptionMissingParams() : 
    invalid_argument("Missing Parameters.") {
}

/*************************************************************************
���������ơ�       ExceptionExcessParams���캯��
���������ܡ�       �������������쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
Element<M>::ExceptionExcessParams::ExceptionExcessParams() 
: invalid_argument("Excess Parameters.") {
}

/*************************************************************************
���������ơ�       ExceptionCoincidentPoints���캯��
���������ܡ�       �����غϵ��쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
Element<M>::ExceptionCoincidentPoints::ExceptionCoincidentPoints() 
: invalid_argument("Coincident Points.") {
}

/*************************************************************************
���������ơ�       ExceptionTypeMismatch���캯��
���������ܡ�       �������Ͳ�ƥ���쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
Element<M>::ExceptionTypeMismatch::ExceptionTypeMismatch() 
: logic_error("Type mismatch: Expected Element<M> object.") {
}

/*************************************************************************
���������ơ�       ExceptionUndefinedArea���캯��
���������ܡ�       ���δ����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
Element<M>::ExceptionUndefinedArea::ExceptionUndefinedArea() 
: std::logic_error("Undefine Area.") {
}

/*************************************************************************
���������ơ�       ExceptionUndefinedLength���캯��
���������ܡ�       �ܳ�δ����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
Element<M>::ExceptionUndefinedLength::ExceptionUndefinedLength() 
: std::logic_error("Undefined Length.") {
}

/*************************************************************************
���������ơ�       ElementĬ�Ϲ��캯��
���������ܡ�       ����һ���յ�Element����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
Element<M>::Element() {
}

/*************************************************************************
���������ơ�       Element���캯�����������룩
���������ܡ�       ʹ�ø������괴��Element����
����ڲ�����       CoordsInput����������
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
Element<M>::Element(
    const std::vector<std::array<double, 3>> CoordsInput) {
    SetCoordinates(CoordsInput);
}

/*************************************************************************
���������ơ�       Element���캯���������룩
���������ܡ�       ʹ�ø����㴴��Element����
����ڲ�����       Points��������
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
Element<M>::Element(const std::array<Point, M>& Points) {
    SetPoints(Points);
}

/*************************************************************************
���������ơ�       SetCoordinates
���������ܡ�       ����Ԫ�ص�����
����ڲ�����       CoordsInput��Ҫ���õ�����
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
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
���������ơ�       SetPoints
���������ܡ�       ����Ԫ�صĵ�
����ڲ�����       Points��Ҫ���õĵ�����
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
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
���������ơ�       ToString
���������ܡ�       ��Ԫ��ת��Ϊ�ַ�����ʾ
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         Ԫ�ص��ַ�����ʾ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
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
���������ơ�       GetCoordinates
���������ܡ�       ��ȡԪ�ص�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         Ԫ�ص���������
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
std::vector<std::array<double, 3>> Element<M>::GetCoordinates() const {
    return m_Element;
}

/*************************************************************************
���������ơ�       GetPoints
���������ܡ�       ��ȡԪ�صĵ�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         Ԫ�صĵ�����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
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
���������ơ�       GetLength
���������ܡ�       ���ܳ�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
double Element<M>::GetLength() const {
    throw ExceptionUndefinedLength();
}

/*************************************************************************
���������ơ�       GetArea
���������ܡ�       �����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
double Element<M>::GetArea() const {
    throw ExceptionUndefinedArea();
}

/*************************************************************************
���������ơ�       IsSame
���������ܡ�       �Ƚ�����Ԫ���Ƿ���ͬ
����ڲ�����       NewElement��Ҫ�Ƚϵ�Ԫ��
�����ڲ�����       ��
������ֵ��         �����ͬ����true�����򷵻�false
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
template<size_t M>
bool Element<M>::IsSame(const Element<M>& NewElement)const {
    return this->GetCoordinates() == NewElement.GetCoordinates();
}

/*************************************************************************
���������ơ�       IsValid
���������ܡ�       ���Ԫ���Ƿ���Ч���㲻�غϣ�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         �����Ч����true�����򷵻�false
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
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
���������ơ�       IsValid����̬������
���������ܡ�       �����������Ƿ���Ч���㲻�غϣ�
����ڲ�����       CoordsInput��Ҫ��������
�����ڲ�����       ��
������ֵ��         �����Ч����true�����򷵻�false
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
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





