/*************************************************************************
���ļ�����                 FaceSet.cpp
������ģ���Ŀ�ġ�         �漯�ඨ��
�������߼����ڡ�           ����� 2024/8/7
�����ļ�¼��               ��
*************************************************************************/

#include <algorithm>
#include <limits.h>
#include <numeric>
#include"../Point/Point.hpp"
#include"../Element/Face.hpp"

#include"../PointSet/PointSet.hpp"
#include"ElementSet.hpp"

#include "FaceSet.hpp"

using namespace std;

/*************************************************************************
���������ơ�       FaceSet::FaceSet
���������ܡ�       ���캯������ʼ���漯��
����ڲ�����       std::shared_ptr<PointSet> pPointSet
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
FaceSet::FaceSet(std::shared_ptr<PointSet> pPointSet) : 
ElementSet<3>(pPointSet), m_pPointSet(pPointSet) {}

/*************************************************************************
���������ơ�       FaceSet::FaceSet
���������ܡ�       ���캯������ʼ���漯��
����ڲ�����       std::shared_ptr<PointSet> pPointSet, 
                   std::vector<std::array<unsigned int, 3>>& NewFaceSet
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
FaceSet::FaceSet(std::shared_ptr<PointSet> pPointSet, 
    const std::vector<std::array<unsigned int, 3>>& NewFaceSet) : 
    ElementSet<3>(pPointSet), m_FaceSet(NewFaceSet), 
    m_pPointSet(pPointSet) {
}

/*************************************************************************
���������ơ�       FaceSet�������캯��
���������ܡ�       ����FaceSet����
��������           const FaceSet& Source
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
FaceSet::FaceSet(const FaceSet& Source) : 
ElementSet<3>(Source), m_FaceSet(Source.m_FaceSet), 
m_pPointSet(Source.m_pPointSet) {
}

/*************************************************************************
���������ơ�       FaceSet��ֵ���������
���������ܡ�       ����FaceSet����
��������           const FaceSet& Source
������ֵ��         FaceSet
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
FaceSet& FaceSet::operator=(const FaceSet& Source)
{
    if (this != &Source) {
        ElementSet<3>::operator=(Source);
        m_FaceSet = Source.m_FaceSet;
        m_pPointSet = Source.m_pPointSet;
    }
    return *this;
}

/*************************************************************************
���������ơ�       FaceSet::GetElementSet
���������ܡ�       ��ȡ�漯
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<std::array<unsigned int, 3>> �漯
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<unsigned int, 3>> FaceSet::GetElementSet() const {
    return m_FaceSet;
}

/*************************************************************************
���������ơ�       FaceSet::GetElement
���������ܡ�       ��ȡָ����������
����ڲ�����       const unsigned int uIndex
�����ڲ�����       ��
������ֵ��         std::vector<std::array<unsigned int, 3>> ��
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<unsigned int, 3>> FaceSet::GetElement(
    unsigned int uIndex) const {
    if (uIndex != UINT_MAX 
        && static_cast<size_t>(uIndex) < (m_FaceSet.size())) {
        return { m_FaceSet[uIndex] };
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
���������ơ�       FaceSet::GetElementSetIndex
���������ܡ�       ��ȡ�漯����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<unsigned int> �漯����
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
std::vector<unsigned int> FaceSet::GetElementSetIndex() const {
    std::vector<unsigned int> FaceSetIndex(GetTotalCount());
    std::iota(FaceSetIndex.begin(), FaceSetIndex.end(), 0);
    return FaceSetIndex;
}

/*************************************************************************
���������ơ�       FaceSet::FindElement
���������ܡ�       ������
����ڲ�����       const Element<3>& NewFace
�����ڲ�����       ��
������ֵ��         unsigned int �������
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
unsigned int FaceSet::FindElement(const Element<3>& NewFace) const {
    const Face* AFace = dynamic_cast<const Face*>(&NewFace);
    if (!AFace) {
        throw ExceptionTypeMismatch();
    }
    else if (!AFace->IsValid()) {
        throw ExceptionCoincidentPoints();
    }
    else {
        for (unsigned int i = 0; i < m_FaceSet.size(); ++i) {
            if (AFace->IsSame
            (Face({ m_pPointSet->GetPointByIndex(m_FaceSet[i][0]),
                m_pPointSet->GetPointByIndex(m_FaceSet[i][1]),
                m_pPointSet->GetPointByIndex(m_FaceSet[i][2]) }))) {
                return i;  // ���ص�һ���ظ��� AFace ������
            }
        }
    }
    return UINT_MAX;  // ���û���ҵ��ظ��� face������ UINT_MAX
}

/*************************************************************************
���������ơ�       FaceSet::Delete
���������ܡ�       ɾ���棨ͨ��������
����ڲ�����       const unsigned int uIndex
�����ڲ�����       ��
������ֵ��         bool ɾ���Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
bool FaceSet::Delete(const unsigned int uIndex) {
    if (uIndex != UINT_MAX && uIndex < m_FaceSet.size()) {
        m_FaceSet.erase(m_FaceSet.begin() + uIndex);
        return true;
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
���������ơ�       FaceSet::Delete
���������ܡ�       ɾ���棨ͨ����������
����ڲ�����       const std::array<unsigned int, 3>& PointIndex
�����ڲ�����       ��
������ֵ��         bool ɾ���Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
bool FaceSet::Delete(const std::array<unsigned int, 3>& PointIndex) {
    auto AFace = std::find(m_FaceSet.begin(), m_FaceSet.end(), PointIndex);
    if (AFace != m_FaceSet.end()) {
        m_FaceSet.erase(AFace);
        return true;
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
���������ơ�       FaceSet::Add
���������ܡ�       ����棨ͨ�������
����ڲ�����       const Element<3>& NewElement
�����ڲ�����       ��
������ֵ��         unsigned int ��������
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
unsigned int FaceSet::Add(const Element<3>& NewElement) {
    const Face* AFace = dynamic_cast<const Face*>(&NewElement);
    if (!AFace) {
        throw ExceptionTypeMismatch();
    }
    else if (!AFace->IsValid()) {
        throw ExceptionCoincidentPoints();
    }
    else {
        const auto& Points = AFace->GetPoints();
        unsigned int uIndex1 = m_pPointSet->AddPoint(Points[0]);
        unsigned int uIndex2 = m_pPointSet->AddPoint(Points[1]);
        unsigned int uIndex3 = m_pPointSet->AddPoint(Points[2]);
        if (this->FindElement(NewElement) == UINT_MAX) {
            m_FaceSet.push_back({ uIndex1, uIndex2, uIndex3 });
            return m_FaceSet.size() - 1;
        }
        else {
            throw ExceptionDuplicateFace();
        }
    }
    //return this->FindElement(NewElement);
}

/*************************************************************************
���������ơ�       FaceSet::Add
���������ܡ�       ����棨ͨ�����������飩
����ڲ�����       const std::array<unsigned int, 3>& uIndex
�����ڲ�����       ��
������ֵ��         unsigned int ��������
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
unsigned int FaceSet::Add(const std::array<unsigned int, 3>& uIndex) {
    Point Point1 = m_pPointSet->GetPointByIndex(uIndex[0]);
    Point Point2 = m_pPointSet->GetPointByIndex(uIndex[1]);
    Point Point3 = m_pPointSet->GetPointByIndex(uIndex[2]);
    return Add(Face({ Point1, Point2, Point3 }));
}

/*************************************************************************
���������ơ�       FaceSet::Add
���������ܡ�       ����棨ͨ����������飩
����ڲ�����       const std::array<Point, 3>& Points
�����ڲ�����       ��
������ֵ��         unsigned int ��������
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
unsigned int FaceSet::Add(const std::array<Point, 3>& Points) {
    return Add(Face({ Points[0], Points[1], Points[2] }));
}

/*************************************************************************
���������ơ�       FaceSet::Add
���������ܡ�       ����棨ͨ���������飩
����ڲ�����       const std::vector<std::array<double, 3>>& Coordinates
�����ڲ�����       ��
������ֵ��         unsigned int ��������
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
unsigned int FaceSet::Add(
    const std::vector<std::array<double, 3>>& Coordinates) {
    if (Coordinates.size() < 3) {
        throw ExceptionMissingParams();
    }
    else if (Coordinates.size() > 3) {
        throw ExceptionExcessParams();
    }
    else {
        Point Point1({ Coordinates[0] });
        Point Point2({ Coordinates[1] });
        Point Point3({ Coordinates[2] });
        return Add(Face({ Point1, Point2, Point3 }));
    }
}

/*************************************************************************
���������ơ�       FaceSet::Modify
���������ܡ�       �޸���
����ڲ�����       unsigned int uElementIndex, unsigned int uPointIndex, 
                   const Point& NewPoint
�����ڲ�����       ��
������ֵ��         bool �޸��Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
bool FaceSet::Modify(unsigned int uElementIndex, unsigned int uPointIndex, 
    const Point& NewPoint) {
    if (uElementIndex != UINT_MAX 
        && uElementIndex < m_FaceSet.size() && uPointIndex < 3) {
        std::array<Point, 3> NewFaceCoords;
        for (unsigned int i = 0; i < 3; ++i) {
            if (i == uPointIndex) {
                NewFaceCoords[i] = NewPoint;
            }
            else {
                NewFaceCoords[i] = m_pPointSet->GetPointByIndex(
                    GetElementSet()[uElementIndex][i]);
            }
        }
        Face NewFace(NewFaceCoords);
        unsigned int uNewIndex = m_pPointSet->AddPoint(NewPoint);
        if (FindElement(NewFace) != UINT_MAX) {
            throw ExceptionDuplicateFace();
        }
        else {
            m_FaceSet[uElementIndex][uPointIndex] = uNewIndex;
            return true;
        }
    }
    else {
        throw ExceptionInvalidIndex();
    }
}

/*************************************************************************
���������ơ�       FaceSet::Modify
���������ܡ�       �޸��棨ͨ�����꣩
����ڲ�����       unsigned int uElementIndex, unsigned int uPointIndex, 
                   const std::array<double, 3>& Coordinates
�����ڲ�����       ��
������ֵ��         bool �޸��Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
bool FaceSet::Modify(unsigned int uElementIndex, unsigned int uPointIndex, 
    const std::array<double, 3>& Coordinates) {
    return Modify(uElementIndex, uPointIndex, Point({ Coordinates }));
}

/*************************************************************************
���������ơ�       FaceSet::GetPointsInElement
���������ܡ�       ��ȡ���еĵ�
����ڲ�����       const unsigned int uElementIndex
�����ڲ�����       ��
������ֵ��         std::array<unsigned int, 3> ����������
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
std::array<unsigned int, 3> FaceSet::GetPointsInElement(
    const unsigned int uElementIndex) const {
    if (uElementIndex >= m_FaceSet.size() || uElementIndex == UINT_MAX) {
        throw ExceptionInvalidIndex();
    }
    return { GetElementSet()[uElementIndex][0], 
             GetElementSet()[uElementIndex][1], 
             GetElementSet()[uElementIndex][2] };
}

/*************************************************************************
���������ơ�       FaceSet::GetTotalCount
���������ܡ�       ��ȡ������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         unsigned int ������
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
unsigned int FaceSet::GetTotalCount() const {
    return static_cast<unsigned int>(m_FaceSet.size());
}

/*************************************************************************
���������ơ�       FaceSet::GetTotalLength
���������ܡ�       ��ȡ���ܳ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         double ���ܳ���
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
double FaceSet::GetTotalLength() const {
    double rTotalLength = 0.0;
    for (const auto& AFace : m_FaceSet) {
        Point Point1 = m_pPointSet->GetPointByIndex(AFace[0]);
        Point Point2 = m_pPointSet->GetPointByIndex(AFace[1]);
        Point Point3 = m_pPointSet->GetPointByIndex(AFace[2]);
        Face SelectFace({ Point1,Point2,Point3 });
        rTotalLength += SelectFace.GetLength();
    }
    return rTotalLength;
}

/*************************************************************************
���������ơ�       FaceSet::GetTotalArea
���������ܡ�       ��ȡ�������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         double �������
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
double FaceSet::GetTotalArea() const {
    double rTotalArea = 0.0;
    for (const auto& AFace : m_FaceSet) {
        Point Point1 = m_pPointSet->GetPointByIndex(AFace[0]);
        Point Point2 = m_pPointSet->GetPointByIndex(AFace[1]);
        Point Point3 = m_pPointSet->GetPointByIndex(AFace[2]);
        Face SelectFace({ Point1, Point2, Point3 });
        rTotalArea += SelectFace.GetArea();
    }
    return rTotalArea;
}

/*************************************************************************
���������ơ�       FaceSet::GetFaceAreas
���������ܡ�       ��ȡ����������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<double> �������
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
std::vector<double> FaceSet::GetFaceAreas() const {
    std::vector<double> FaceAreas;
    for (const auto& AFace : m_FaceSet) {
        Point Point1 = m_pPointSet->GetPointByIndex(AFace[0]);
        Point Point2 = m_pPointSet->GetPointByIndex(AFace[1]);
        Point Point3 = m_pPointSet->GetPointByIndex(AFace[2]);
        Face SelectFace({ Point1, Point2, Point3 });
        FaceAreas.push_back(SelectFace.GetArea());
    }
    return FaceAreas;
}

/*************************************************************************
���������ơ�       FaceSet::ExceptionDuplicateFace::ExceptionDuplicateFace
���������ܡ�       �ظ����쳣���캯��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
FaceSet::ExceptionDuplicateFace::ExceptionDuplicateFace()
: std::invalid_argument("Duplicate Face.") {
}

/*************************************************************************
���������ơ�       FaceSet::ClearElementSet
���������ܡ�       ����漯
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/7
�����ļ�¼��       ��
*************************************************************************/
void FaceSet::ClearElementSet() {
    m_FaceSet.clear();
}



