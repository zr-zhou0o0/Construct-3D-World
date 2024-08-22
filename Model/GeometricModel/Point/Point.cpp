/*************************************************************************
���ļ�����                 Point.cpp
������ģ���Ŀ�ġ�         ��ά���ඨ��
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
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
    ��������             ExceptionEmptyCoords
    �����ܡ�             ��ʾ�������쳣
    ���ӿ�˵����         �̳��� invalid_argument
    �������߼����ڡ�     ����� 2024/8/12
    �����ļ�¼��         ��
*************************************************************************/
Point::ExceptionEmptyCoords::ExceptionEmptyCoords()
: invalid_argument("Empty Coordinates.") {
}

/*************************************************************************
   ��������             ExceptionExcessParams
   �����ܡ�             ��ʾ���������쳣
   ���ӿ�˵����         �̳��� invalid_argument
   �������߼����ڡ�     ����� 2024/8/12
   �����ļ�¼��         ��
*************************************************************************/
Point::ExceptionExcessParams::ExceptionExcessParams()
: invalid_argument("Excess Parameters.") {
}

/*************************************************************************
    ���������ơ�       Point��Ĭ�Ϲ��캯����
    ���������ܡ�       ����һ��Ĭ�ϵ�Point����
    ��������           ��
    ������ֵ��         ��
    �������߼����ڡ�   ����� 2024/8/12
    �����ļ�¼��       ��
*************************************************************************/
Point::Point() {
}

/*************************************************************************
    ���������ơ�       Point�����������캯����
    ���������ܡ�       ʹ�ø������괴��Point����
    ��������           rCoordinates��������������������������
    ������ֵ��         ��
    �������߼����ڡ�   ����� 2024/8/12
    �����ļ�¼��       ��
*************************************************************************/
Point::Point(const std::vector<std::array<double, 3>>& NewCoords) 
{
    SetCoordinates(NewCoords);
}

/*************************************************************************
    ���������ơ�       ~Point
    ���������ܡ�       Point�����������
    ��������           ��
    ������ֵ��         ��
    �������߼����ڡ�   ����� 2024/8/12
    �����ļ�¼��       ��
*************************************************************************/
Point::~Point() {}

/*************************************************************************
���������ơ�       Point�������캯��
���������ܡ�       ����Point����
��������           const Point& Source
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Point::Point(const Point& Source) {
    m_Coordinates = Source.m_Coordinates;
}

/*************************************************************************
   ���������ơ�       operator=
   ���������ܡ�       Point��ĸ�ֵ���������
   ��������           Source�������������Ҫ���Ƶ�Point����
   ������ֵ��         ���ص�ǰ���������
   �������߼����ڡ�   ����� 2024/8/12
   �����ļ�¼��       ��
*************************************************************************/
Point& Point::operator=(const Point& Source) {
    if (this != &Source) {
        SetCoordinates(Source.GetCoordinates());
    }
    return *this;
}

/*************************************************************************
    ���������ơ�       SetCoordinates
    ���������ܡ�       ���õ������
    ��������           rCoordinates����������������������������
    ������ֵ��         ��
    �������߼����ڡ�   ����� 2024/8/12
    �����ļ�¼��       ��
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
   ���������ơ�       GetCoordinates
   ���������ܡ�       ��ȡ�������
   ��������           ��
   ������ֵ��         ���ذ��������������
   �������߼����ڡ�   ����� 2024/8/12
   �����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<double, 3>> Point::GetCoordinates() const {
    std::vector<std::array<double, 3>> rCoordinatesVector;
    rCoordinatesVector.push_back(m_Coordinates);
    return rCoordinatesVector;
}

/*************************************************************************
   ���������ơ�       IsSame
   ���������ܡ�       �Ƚϵ�ǰ������������Ƿ���ͬ
   ��������           rCoordinates�������������Ҫ�Ƚϵ���������
   ������ֵ��         �����ͬ����true�����򷵻�false
   �������߼����ڡ�   ����� 2024/8/12
   �����ļ�¼��       ��
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
    ���������ơ�       IsSame
    ���������ܡ�       �Ƚ��������Ƿ���ͬ
    ��������           NewPoint�������������Ҫ�Ƚϵ�Point����
    ������ֵ��         �����ͬ����true�����򷵻�false
    �������߼����ڡ�   ����� 2024/8/12
    �����ļ�¼��       ��
*************************************************************************/
bool Point::IsSame(const Point& NewPoint) const {
    return m_Coordinates == NewPoint.m_Coordinates;
}

/*************************************************************************
    ���������ơ�       IsCollinear
    ���������ܡ�       �жϵ�ǰ���������������Ƿ���
    ��������           Point1, p2�������������Ҫ�жϵ�����������
    ������ֵ��         ������߷���true�����򷵻�false
    �������߼����ڡ�   ����� 2024/8/12
    �����ļ�¼��       ��
*************************************************************************/
bool Point::IsCollinear(const Point& Point1, const Point& Point2) const {
    return Point::IsCollinear(*this, Point1, Point2);
}

/*************************************************************************
   ���������ơ�       GetDistance
   ���������ܡ�       ���㵱ǰ������һ����ľ���
   ��������           NewPoint�������������Ҫ����������һ����
   ������ֵ��         ��������֮��ľ���
   �������߼����ڡ�   ����� 2024/8/12
   �����ļ�¼��       ��
*************************************************************************/
double Point::GetDistance(const Point& NewPoint) const {
    return Point::GetDistance(*this, NewPoint);
}

/*************************************************************************
���������ơ�       IsCollinear
���������ܡ�       �жϸ�����������Ƿ���
��������           rCoordinates��������������������������
������ֵ��         ����㹲�߻����������㷵��true�����򷵻�false
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
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
���������ơ�       IsCollinear
���������ܡ�       �ж��������Ƿ���
��������           Point1, Point2, p3��������������������жϵĵ�
������ֵ��         ������㹲�߷���true�����򷵻�false
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool Point::IsCollinear(
    const Point& Point1, const Point& Point2, const Point& Point3) {
    const double rEpsilon = 1e-9;  // ����һ��С���������

    double rX1 = Point2.m_Coordinates[0] - Point1.m_Coordinates[0];
    double rY1 = Point2.m_Coordinates[1] - Point1.m_Coordinates[1];
    double rZ1 = Point2.m_Coordinates[2] - Point1.m_Coordinates[2];

    double rX2 = Point3.m_Coordinates[0] - Point1.m_Coordinates[0];
    double rY2 = Point3.m_Coordinates[1] - Point1.m_Coordinates[1];
    double rZ2 = Point3.m_Coordinates[2] - Point1.m_Coordinates[2];

    // �������ĸ�����
    double rCrossX = rY1 * rZ2 - rZ1 * rY2;
    double rCrossY = rZ1 * rX2 - rX1 * rZ2;
    double rCrossZ = rX1 * rY2 - rY1 * rX2;

    // ������Ƿ�ӽ�������
    return (std::abs(rCrossX) < rEpsilon)
        && (std::abs(rCrossY) < rEpsilon)
        && (std::abs(rCrossZ) < rEpsilon);
}

/*************************************************************************
���������ơ�       GetDistance
���������ܡ�       ��������֮��ľ���
��������           NewPoint1, NewPoint2�������������Ҫ��������������
������ֵ��         ��������֮���ŷ����þ���
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
double Point::GetDistance(const Point& NewPoint1, const Point& NewPoint2) {
    double rDX = NewPoint1.m_Coordinates[0] - NewPoint2.m_Coordinates[0];
    double rDY = NewPoint1.m_Coordinates[1] - NewPoint2.m_Coordinates[1];
    double rDZ = NewPoint1.m_Coordinates[2] - NewPoint2.m_Coordinates[2];

    return std::sqrt(rDX * rDX + rDY * rDY + rDZ * rDZ);
}