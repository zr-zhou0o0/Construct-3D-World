/*************************************************************************
���ļ�����                 LineSet.cpp
������ģ���Ŀ�ġ�         �߼��ඨ��
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <vector>
#include <array>
#include <cmath>
#include <iostream>
#include <limits.h>
#include <stdexcept>
#include <memory>
#include <numeric>

#include "../Point/Point.hpp"
#include "../Element/Line.hpp"
#include "../PointSet/PointSet.hpp"
#include "ElementSet.hpp"
#include "LineSet.hpp"

using namespace std;

/*************************************************************************
���������ơ�       LineSet
���������ܡ�       ���캯������ʼ���߼���
����ڲ�����       std::shared_ptr<PointSet> pPointSet
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
LineSet::LineSet(std::shared_ptr<PointSet> pPointSet) : 
ElementSet<2>(pPointSet), m_pPointSet(pPointSet) {
}

/*************************************************************************
���������ơ�       LineSet
���������ܡ�       ���캯������ʼ���߼��࣬���߶μ��ϲ���
����ڲ�����       std::shared_ptr<PointSet> pPointSet, 
                   const std::vector<std::array<unsigned int, 2>>& NewLineSet
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
LineSet::LineSet(std::shared_ptr<PointSet> pPointSet, 
    const std::vector<std::array<unsigned int, 2>>& NewLineSet) : 
    ElementSet<2>(pPointSet), m_LineSet(NewLineSet), 
    m_pPointSet(pPointSet) {
}

/*************************************************************************
���������ơ�       LineSet�������캯��
���������ܡ�       ����LineSet����
��������           const LineSet& Source
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
LineSet::LineSet(const LineSet& Source) : 
ElementSet<2>(Source), m_LineSet(Source.m_LineSet),
m_pPointSet(Source.m_pPointSet) {
}

/*************************************************************************
���������ơ�       LineSet��ֵ���������
���������ܡ�       ����LineSet����
��������           const LineSet& Source
������ֵ��         LineSet
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
LineSet& LineSet::operator=(const LineSet& Source)
{
    if (this != &Source) {
        ElementSet<2>::operator=(Source);
        m_LineSet = Source.m_LineSet;
        m_pPointSet = Source.m_pPointSet;
    }
    return *this;
}

/*************************************************************************
���������ơ�       GetElementSet
���������ܡ�       ��ȡ�߶μ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<std::array<unsigned int, 2>> �߶μ���
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<unsigned int, 2>> LineSet::GetElementSet() const {
    return m_LineSet;
}

/*************************************************************************
���������ơ�       GetElement
���������ܡ�       ��ȡָ���������߶�
����ڲ�����       const unsigned int uIndex
�����ڲ�����       ��
������ֵ��         std::vector<std::array<unsigned int, 2>> ָ���������߶�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<unsigned int, 2>> LineSet::GetElement(
    unsigned int uIndex) const {
    if (uIndex != UINT_MAX 
        && static_cast<size_t>(uIndex) < (m_LineSet.size())) {
        return { m_LineSet[uIndex] };
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
���������ơ�       GetElementSetIndex
���������ܡ�       ��ȡ�߶μ��ϵ�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<unsigned int> �߶μ��ϵ�����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::vector<unsigned int> LineSet::GetElementSetIndex() const {
    std::vector<unsigned int> LineSetIndex(GetTotalCount());
    std::iota(LineSetIndex.begin(), LineSetIndex.end(), 0);
    return LineSetIndex;
}

/*************************************************************************
���������ơ�       FindElement
���������ܡ�       �����߶�
����ڲ�����       const Element<2>& NewLine
�����ڲ�����       ��
������ֵ��         unsigned int �߶����������û���ҵ����� UINT_MAX
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int LineSet::FindElement(const Element<2>& NewLine)const {
    const Line* ALine = dynamic_cast<const Line*>(&NewLine);
    if (!ALine) {
        throw ExceptionTypeMismatch();
    }
    else if (!ALine->IsValid()) {
        throw ExceptionCoincidentPoints();
    }
    else {
        for (unsigned int i = 0; i < m_LineSet.size(); ++i) {
            if (ALine->IsSame
                (Line({ m_pPointSet->GetPointByIndex(m_LineSet[i][0]),
                        m_pPointSet->GetPointByIndex(m_LineSet[i][1]) }))) {
                return i;  // ���ص�һ���ظ��� ALine ������
            }
        }
    }
    return UINT_MAX;  // ���û���ҵ��ظ��� line������ UINT_MAX
}

/*************************************************************************
���������ơ�       Delete
���������ܡ�       ɾ���߶Σ�ͨ��������
����ڲ�����       const unsigned int uIndex
�����ڲ�����       ��
������ֵ��         bool ɾ���Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool LineSet::Delete(const unsigned int uIndex) {
    if (uIndex != UINT_MAX 
        && static_cast<size_t>(uIndex) < (m_LineSet.size())) {
        m_LineSet.erase(m_LineSet.begin() + uIndex);
        return true;
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
���������ơ�       Delete
���������ܡ�       ɾ���߶Σ�ͨ����������
����ڲ�����       const std::array<unsigned int, 2>& PointIndex
�����ڲ�����       ��
������ֵ��         bool ɾ���Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool LineSet::Delete(const std::array<unsigned int, 2>& PointIndex) {
    auto ALine = std::find(m_LineSet.begin(), m_LineSet.end(), PointIndex);
    if (ALine != m_LineSet.end()) {
        m_LineSet.erase(ALine);
        return true;
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
���������ơ�       Add
���������ܡ�       ����߶Σ�ͨ���߶ζ���
����ڲ�����       const Element<2>& NewElement
�����ڲ�����       ��
������ֵ��         unsigned int ���߶ε�����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int LineSet::Add(const Element<2>& NewElement) {
    const Line* ALine = dynamic_cast<const Line*>(&NewElement);
    if (!ALine) {
        throw ExceptionTypeMismatch();
    }
    else if (!ALine->IsValid()) {
        throw ExceptionCoincidentPoints();
    }
    else {
        const auto& Points = ALine->GetPoints();
        unsigned int uIndex1 = m_pPointSet->AddPoint(Points[0]);
        unsigned int uIndex2 = m_pPointSet->AddPoint(Points[1]);
        if (this->FindElement(NewElement) == UINT_MAX) {
            m_LineSet.push_back({ uIndex1, uIndex2 });
            return m_LineSet.size() - 1;
        }
        else {
            throw ExceptionDuplicateLine();
        }
    }
}

/*************************************************************************
���������ơ�       Add
���������ܡ�       ����߶Σ�ͨ�����������飩
����ڲ�����       const std::array<unsigned int, 2>& uIndex
�����ڲ�����       ��
������ֵ��         unsigned int ���߶ε�����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int LineSet::Add(const std::array<unsigned int, 2>& Index) {
    Point Point1 = m_pPointSet->GetPointByIndex(Index[0]);
    Point Point2 = m_pPointSet->GetPointByIndex(Index[1]);
    return Add(Line({ Point1, Point2 }));
}

/*************************************************************************
���������ơ�       Add
���������ܡ�       ����߶Σ�ͨ����������飩
����ڲ�����       const std::array<Point, 2>& Points
�����ڲ�����       ��
������ֵ��         unsigned int ���߶ε�����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int LineSet::Add(const std::array<Point, 2>& Points) {
    return Add(Line({ Points[0], Points[1] }));
}

/*************************************************************************
���������ơ�       Add
���������ܡ�       ����߶Σ�ͨ���������飩
����ڲ�����       const std::vector<std::array<double, 3>>& Coordinates
�����ڲ�����       ��
������ֵ��         unsigned int ���߶ε�����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int LineSet::Add(
    const std::vector<std::array<double, 3>>& Coordinates) {
    if (Coordinates.size() < 2) {
        throw ExceptionMissingParams();
    }
    else if (Coordinates.size() > 2) {
        throw ExceptionExcessParams();
    }
    else {
        Point Point1({ Coordinates[0] });
        Point Point2({ Coordinates[1] });
        return Add(Line({ Point1, Point2 }));
    }
}

/*************************************************************************
���������ơ�       Modify
���������ܡ�       �޸��߶�
����ڲ�����       unsigned int uElementIndex, unsigned int uPointIndex, 
                   const Point& NewPoint
�����ڲ�����       ��
������ֵ��         bool �޸��Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool LineSet::Modify(unsigned int uElementIndex, unsigned int uPointIndex, 
    const Point& NewPoint) {
    if (uElementIndex != UINT_MAX 
        && uElementIndex < static_cast<unsigned int>(m_LineSet.size()) 
        && (uPointIndex == 0 || uPointIndex == 1)) {
        Point RemainPoint;
        std::array<Point, 2> NewLineCoords;
        if (uPointIndex == 0) {
            RemainPoint = m_pPointSet->GetPointByIndex(
                GetElementSet()[uElementIndex][1]);
            NewLineCoords = { NewPoint, RemainPoint };
        }
        else {
            RemainPoint = m_pPointSet->GetPointByIndex(
                GetElementSet()[uElementIndex][0]);
            NewLineCoords = { RemainPoint, NewPoint };
        }

        if (RemainPoint.IsSame(NewPoint)) {
            throw ExceptionCoincidentPoints();
        }
        else {
            unsigned int uIndex = m_pPointSet->AddPoint(NewPoint);
            Line NewLine(NewLineCoords);
            if (FindElement(NewLine) != UINT_MAX) {
                throw ExceptionDuplicateLine();
            }
            else {
                m_LineSet[uElementIndex][uPointIndex] = uIndex;
                return true;
            }
        }
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
���������ơ�       Modify
���������ܡ�       �޸��߶Σ�ͨ�����꣩
����ڲ�����       unsigned int iElementIndex, unsigned int iPointIndex, 
                   const std::array<double, 3>& Coordinates
�����ڲ�����       ��
������ֵ��         bool �޸��Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool LineSet::Modify(unsigned int iElementIndex, unsigned int iPointIndex, 
    const std::array<double, 3>& rCoordinates) {
    return Modify(iElementIndex, iPointIndex, Point({ rCoordinates }));
}

/*************************************************************************
���������ơ�       GetPointsInElement
���������ܡ�       ��ȡ�߶��еĵ�
����ڲ�����       const unsigned int uElementIndex
�����ڲ�����       ��
������ֵ��         std::array<unsigned int, 2> �߶��еĵ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::array<unsigned int, 2> LineSet::GetPointsInElement(
    const unsigned int uElementIndex) const {
    if (uElementIndex >= m_LineSet.size() || uElementIndex == UINT_MAX) {
        throw ExceptionInvalidIndex();
    }
    return { GetElementSet()[uElementIndex][0], 
             GetElementSet()[uElementIndex][1] };
}

/*************************************************************************
���������ơ�       GetTotalCount
���������ܡ�       ��ȡ�߶�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         unsigned int �߶�����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int LineSet::GetTotalCount() const {
    return static_cast<unsigned int>(m_LineSet.size());
}

/*************************************************************************
���������ơ�       GetTotalLength
���������ܡ�       ��ȡ�߶��ܳ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         double �߶��ܳ���
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
double LineSet::GetTotalLength() const {
    double rTotalLength = 0.0;
    for (const auto& ALine : m_LineSet) {
        Point Point1 = m_pPointSet->GetPointByIndex(ALine[0]);
        Point Point2 = m_pPointSet->GetPointByIndex(ALine[1]);
        Line SelectLine({ Point1, Point2 });
        rTotalLength += SelectLine.GetLength();
    }
    return rTotalLength;
}

/*************************************************************************
���������ơ�       GetTotalArea
���������ܡ�       ��ȡ�߶��������δ���壩
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         double �߶��������δ���壩
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
double LineSet::GetTotalArea() const {
    throw ExceptionUndefinedArea();
}

/*************************************************************************
���������ơ�       GetLineLengths
���������ܡ�       ��ȡ�����߶εĳ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<double> �����߶εĳ���
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::vector<double> LineSet::GetLineLengths() const {
    std::vector<double> LineLegnths;
    for (const auto& ALine : m_LineSet) {
        Point Point1 = m_pPointSet->GetPointByIndex(ALine[0]);
        Point Point2 = m_pPointSet->GetPointByIndex(ALine[1]);
        Line SelectLine({ Point1, Point2 });
        LineLegnths.push_back(SelectLine.GetLength());
    }
    return LineLegnths;
}

/*************************************************************************
���������ơ�       ClearElementSet
���������ܡ�       ����߶μ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
void LineSet::ClearElementSet() {
    m_LineSet.clear();
}

/*************************************************************************
���������ơ�       ExceptionDuplicateLine
���������ܡ�       �ظ��߶��쳣�๹�캯��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
LineSet::ExceptionDuplicateLine::ExceptionDuplicateLine()
: invalid_argument("Duplicate Line.") {
}

/*************************************************************************
���������ơ�       ExceptionUndefinedArea
���������ܡ�       δ��������쳣�๹�캯��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
LineSet::ExceptionUndefinedArea::ExceptionUndefinedArea()
: logic_error("Undefined Area.") {
}




