/*************************************************************************
���ļ�����                 PointSet.cpp
������ģ���Ŀ�ġ�         ��ά�㼯�ඨ��
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <vector>
#include <array>
#include <limits.h>
#include <stdexcept>
#include <numeric>

#include "PointSet.hpp"
#include "../Point/Point.hpp"

using namespace std;

/*************************************************************************
���������ơ�       PointSet���캯��
���������ܡ�       ����һ���յ�PointSet����
��������           ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
PointSet::PointSet() : m_PointSet() {}

/*************************************************************************
���������ơ�       PointSet���캯��
���������ܡ�       ʹ�ø����ĵ㼯����PointSet����
��������           NewPointSet���������������ʼ�㼯
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
PointSet::PointSet(const std::vector<std::array<double, 3>>& NewPointSet) : 
m_PointSet(NewPointSet) {}

/*************************************************************************
���������ơ�       PointSet�������캯��
���������ܡ�       ����PointSet����
��������           const PointSet& Source
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
PointSet::PointSet(const PointSet& Source) {
    m_PointSet = Source.m_PointSet;
}

/*************************************************************************
���������ơ�       PointSet��ֵ���������
���������ܡ�       ����PointSet����
��������           const PointSet& Source
������ֵ��         PointSet
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
PointSet& PointSet::operator=(const PointSet& Source) {
    if (this != &Source) {
        m_PointSet = Source.m_PointSet;
    }
    return *this;
}

/*************************************************************************
���������ơ�       ~PointSet
���������ܡ�       PointSet��������
��������           ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
PointSet::~PointSet() {}

/*************************************************************************
���������ơ�       SetPointSet
���������ܡ�       �����е㼯����µĵ�
��������           NewPointSet�������������Ҫ��ӵ��µ㼯
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
void PointSet::SetPointSet(
    const std::vector<std::array<double, 3>>& NewPointSet) {
    m_PointSet.insert(
        m_PointSet.end(), NewPointSet.begin(), NewPointSet.end());
}

/*************************************************************************
���������ơ�       GetPointSet
���������ܡ�       ��ȡ��ǰ�㼯
��������           ��
������ֵ��         ���ص�ǰ�㼯�ĸ���
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<double, 3>> PointSet::GetPointSet() const {
    return m_PointSet;
}

/*************************************************************************
���������ơ�       GetPointSetIndex
���������ܡ�       ��ȡ�㼯������
��������           ��
������ֵ��         ����һ���������е�����������
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::vector<unsigned int> PointSet::GetPointSetIndex()const {
    std::vector<unsigned int> PointSetIndex(GetTotalPointCount());
    std::iota(PointSetIndex.begin(), PointSetIndex.end(), 0);
    return PointSetIndex;
}

/*************************************************************************
���������ơ�       AddPoint
���������ܡ�       ��㼯����µ�
��������           NewPoint�������������Ҫ��ӵ��µ�
������ֵ��         ��������ӵ������
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int PointSet::AddPoint(const Point& NewPoint) {
    return AddPoint(NewPoint, m_PointSet.size());
}

/*************************************************************************
���������ơ�       AddPoint
���������ܡ�       ��㼯����µ�����
��������           rCoordinates�������������Ҫ��ӵ��µ�����
������ֵ��         ��������ӵ������
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int PointSet::AddPoint(const array<double, 3>& NewCoords) {
    return AddPoint(Point({ NewCoords }));
}

/*************************************************************************
���������ơ�       AddPoint
���������ܡ�       ��ָ����������㼯����µ�
��������           NewPoint�������������Ҫ��ӵ��µ�
                   uIndex�������������ָ��������λ��
������ֵ��         ��������ӵ��������������Ѵ����򷵻�ԭ����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int PointSet::AddPoint(const Point& NewPoint, unsigned int uIndex) {
    if (uIndex == UINT_MAX 
        || static_cast<size_t>(uIndex) > m_PointSet.size()) {
        throw ExceptionInvalidIndex();
    }
    else {
        if (FindPoint(NewPoint) == UINT_MAX) {
            std::array<double, 3> coords = { 
                NewPoint.GetCoordinates()[0][0], 
                NewPoint.GetCoordinates()[0][1], 
                NewPoint.GetCoordinates()[0][2] };
            m_PointSet.insert(m_PointSet.begin() + uIndex, coords);
            return uIndex;
        }
        else {
            return FindPoint(NewPoint);
        }
    }
}

/*************************************************************************
���������ơ�       DeletePoint
���������ܡ�       ɾ��ָ�������ĵ�
��������           uIndex�������������Ҫɾ���ĵ������
������ֵ��         ����ɹ�ɾ������true�������׳��쳣
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool PointSet::DeletePoint(unsigned int uIndex) {
    if (uIndex == UINT_MAX 
        || static_cast<size_t>(uIndex) >= m_PointSet.size()) {
        throw ExceptionInvalidIndex();
    }
    else {
        m_PointSet.erase(m_PointSet.begin() + uIndex);
        return true;
    }
}

/*************************************************************************
���������ơ�       FindPoint
���������ܡ�       ����ָ�����ڵ㼯�е�����
��������           NewPoint�������������Ҫ���ҵĵ�
������ֵ��         ����ҵ��������������򷵻�UINT_MAX
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int PointSet::FindPoint(const Point& NewPoint) const {
    std::array<double, 3> coords = { 
        NewPoint.GetCoordinates()[0][0], 
        NewPoint.GetCoordinates()[0][1], 
        NewPoint.GetCoordinates()[0][2] };

    auto it = std::find(m_PointSet.begin(), m_PointSet.end(), coords);

    if (it != m_PointSet.end()) {
        // �ҵ��˵㣬����������
        return std::distance(m_PointSet.begin(), it);
    }
    else {
        // û�ҵ��㣬���� uint_max
        return UINT_MAX;
    }
}

/*************************************************************************
���������ơ�       GetCoordsByIndexRange
���������ܡ�       ��ȡָ��������Χ�ڵĵ�����
��������           uStartIndex���������������ʼ����
                   uEndIndex���������������������
������ֵ��         ����ָ����Χ�ڵĵ���������
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<double, 3>> PointSet::GetCoordsByIndexRange(
    unsigned int uStartIndex, unsigned int uEndIndex)const {
    if (uStartIndex == UINT_MAX || uEndIndex == UINT_MAX 
        || static_cast<size_t>(uEndIndex) > m_PointSet.size() 
        || uStartIndex >= uEndIndex) {
        throw ExceptionInvalidIndex();
    }
    return std::vector<std::array<double, 3>>(
        m_PointSet.begin() + uStartIndex, m_PointSet.begin() + uEndIndex);
}

/*************************************************************************
���������ơ�       GetCoordsByIndex
���������ܡ�       ��ȡָ�������ĵ�����
��������           uIndex��������������������
������ֵ��         ����ָ�������ĵ�����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::array<double, 3> PointSet::GetCoordsByIndex(unsigned int uIndex)const {
    if (uIndex == UINT_MAX 
        || static_cast<size_t>(uIndex) >= m_PointSet.size()) {
        throw ExceptionInvalidIndex();
    }
    return m_PointSet[uIndex];
}

/*************************************************************************
���������ơ�       GetPointByIndex
���������ܡ�       ��ȡָ�������ĵ�
��������           uIndex��������������������
������ֵ��         ����ָ��������Point����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Point PointSet::GetPointByIndex(unsigned int uIndex) const {
    if (uIndex == UINT_MAX 
        || static_cast<size_t>(uIndex) >= m_PointSet.size()) {
        throw ExceptionInvalidIndex();
    }
    auto coords = m_PointSet[uIndex];
    return Point({ { coords[0], coords[1], coords[2] } });
}

/*************************************************************************
���������ơ�       GetIndexByCoords
���������ܡ�       ͨ�������ȡ�������
��������           coords��������������������
������ֵ��         ���ض�Ӧ����ĵ������
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int PointSet::GetIndexByCoords(
    const std::array<double, 3> Coords) const {
    auto it = std::find(m_PointSet.begin(), m_PointSet.end(), Coords);
    if (it == m_PointSet.end()) {
        throw ExceptionInvalidIndex();
    }
    return std::distance(m_PointSet.begin(), it);
}

/*************************************************************************
���������ơ�       GetIndexByPoint
���������ܡ�       ͨ��Point�����ȡ�������
��������           point�������������Point����
������ֵ��         ���ض�ӦPoint���������
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int PointSet::GetIndexByPoint(const Point& APoint)const {
    std::array<double, 3> coords = { 
        APoint.GetCoordinates()[0][0], 
        APoint.GetCoordinates()[0][1], 
        APoint.GetCoordinates()[0][2] };
    return GetIndexByCoords(coords);
}

/*************************************************************************
���������ơ�       GetTotalPointCount
���������ܡ�       ��ȡ�㼯�е������
��������           ��
������ֵ��         ���ص㼯�е������
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
unsigned int PointSet::GetTotalPointCount()const {
    return m_PointSet.size();
}

/*************************************************************************
���������ơ�       GetBoundingBoxVolume
���������ܡ�       ����㼯�İ�Χ�����
��������           ��
������ֵ��         ���ذ�Χ�е����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
double PointSet::GetBoundingBoxVolume()const {
    if (m_PointSet.empty()) return 0.0;

    double minX = m_PointSet[0][0], maxX = m_PointSet[0][0];
    double minY = m_PointSet[0][1], maxY = m_PointSet[0][1];
    double minZ = m_PointSet[0][2], maxZ = m_PointSet[0][2];

    for (const auto& point : m_PointSet) {
        minX = std::min(minX, point[0]);
        maxX = std::max(maxX, point[0]);
        minY = std::min(minY, point[1]);
        maxY = std::max(maxY, point[1]);
        minZ = std::min(minZ, point[2]);
        maxZ = std::max(maxZ, point[2]);
    }

    double length = maxX - minX;
    double width = maxY - minY;
    double height = maxZ - minZ;

    return length * width * height;
}

/*************************************************************************
���������ơ�       ExceptionInvalidIndex
���������ܡ�       ��Ч�����쳣�Ĺ��캯��
��������           ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
PointSet::ExceptionInvalidIndex::ExceptionInvalidIndex()
: std::out_of_range("Index out of bounds.") {
}

/*************************************************************************
���������ơ�       ClearPointSet
���������ܡ�       ��յ㼯
��������           ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
void PointSet::ClearPointSet() {
    m_PointSet.clear();
}











