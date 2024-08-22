/*************************************************************************
���ļ�����                 Face.cpp
������ģ���Ŀ�ġ�         ��Ԫ���ඨ��
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cmath>

#include "Face.hpp"

/*************************************************************************
���������ơ�       ExceptionCollinearPoints::ExceptionCollinearPoints
���������ܡ�       �����쳣���󣬱�ʾ���㹲��ʱ�׳����쳣
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Face::ExceptionCollinearPoints::ExceptionCollinearPoints() 
: invalid_argument("Collinear Points.") {
}

/*************************************************************************
���������ơ�       Face::Face
���������ܡ�       Ĭ�Ϲ��캯������ʼ����Ԫ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Face::Face() : Element<3>() {
    SetPoints({ Point(), Point(), Point() });
}

/*************************************************************************
���������ơ�       Face::Face
���������ܡ�       ʹ�����깹����Ԫ��
����ڲ�����       Coords - ������ÿ�����������
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Face::Face(const std::vector<std::array<double, 3>>& Coords): 
Element<3>() {
    SetCoordinates(Coords);
}

/*************************************************************************
���������ơ�       Face::Face
���������ܡ�       ʹ�õ㹹����Ԫ��
����ڲ�����       Points - ��������ĵ����
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Face::Face(const std::array<Point, 3>& Points) : Element<3>() {
    SetPoints(Points);
}

/*************************************************************************
���������ơ�       Face�������캯��
���������ܡ�       ����Face����
��������           const Face& Source
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Face::Face(const Face& Source) :
Element<3>(), m_Point1(Source.m_Point1), m_Point2(Source.m_Point2),
m_Point3(Source.m_Point3) {
}

/*************************************************************************
   ���������ơ�       operator=
   ���������ܡ�       Face��ĸ�ֵ���������
   ��������           Source�������������Ҫ���Ƶ�Face����
   ������ֵ��         ���ص�ǰ���������
   �������߼����ڡ�   ����� 2024/8/12
   �����ļ�¼��       ��
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
���������ơ�       Face::~Face
���������ܡ�       ��������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Face::~Face() {}

/*************************************************************************
���������ơ�       Face::SetCoordinates
���������ܡ�       ������Ԫ�ص�����
����ڲ�����       Coords - �����������������
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
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
���������ơ�       Face::SetPoints
���������ܡ�       ������Ԫ�صĶ���
����ڲ�����       Points - �����������������
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
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
���������ơ�       Face::GetCoordinates
���������ܡ�       ��ȡ��Ԫ�ص�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ����һ�����������������������
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<double, 3>> Face::GetCoordinates() const {
    std::vector<std::array<double, 3>> Coordinates;
    Coordinates.push_back(m_Point1.GetCoordinates()[0]);
    Coordinates.push_back(m_Point2.GetCoordinates()[0]);
    Coordinates.push_back(m_Point3.GetCoordinates()[0]);
    return Coordinates;
}

/*************************************************************************
���������ơ�       Face::GetPoints
���������ܡ�       ��ȡ��Ԫ�صĶ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ����һ�����飬������������ĵ����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::array<Point, 3> Face::GetPoints() const {
    return { m_Point1, m_Point2, m_Point3 };
}

/*************************************************************************
���������ơ�       Face::ToString
���������ܡ�       ��ȡ��Ԫ�ص��ַ�����ʾ
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ������Ԫ�ص��ַ�����ʾ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string Face::ToString() const {
    return "Face: " + Element<3>::ToString();
}

/*************************************************************************
���������ơ�       Face::GetLength
���������ܡ�       ������Ԫ�صı߳��ܺ�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ������Ԫ�صı߳��ܺ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
double Face::GetLength() const {
    double rSide1 = Point::GetDistance(m_Point1, m_Point2);
    double rSide2 = Point::GetDistance(m_Point2, m_Point3);
    double rSide3 = Point::GetDistance(m_Point3, m_Point1);
    return rSide1 + rSide2 + rSide3;
}

/*************************************************************************
���������ơ�       Face::GetArea
���������ܡ�       ������Ԫ�ص����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ������Ԫ�ص����
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
double Face::GetArea() const {
    // ʹ�ú��׹�ʽ�������
    double rA = Point::GetDistance(m_Point1, m_Point2);
    double rB = Point::GetDistance(m_Point2, m_Point3);
    double rC = Point::GetDistance(m_Point3, m_Point1);
    double rS = (rA + rB + rC) / 2;
    return std::sqrt(rS * (rS - rA) * (rS - rB) * (rS - rC));
}

/*************************************************************************
���������ơ�       Face::IsSame
���������ܡ�       ���������Ԫ���Ƿ���ͬ
����ڲ�����       NewElement - Ҫ�Ƚϵ���һ��Ԫ��
�����ڲ�����       ��
������ֵ��         ���ز���ֵ����ʾ������Ԫ���Ƿ���ͬ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool Face::IsSame(const Element<3>& NewElement) const {
    const Face* AFace = dynamic_cast<const Face*>(&NewElement);
    if (!AFace) {
        throw ExceptionTypeMismatch();
    }
    std::array<Point, 3> ThisPoint = { m_Point1, m_Point2, m_Point3 };
    std::array<Point, 3> OtherPoint = AFace->GetPoints();

    // ������е��Ƿ���ͬ�����ǵ��˳����ܲ�ͬ
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
���������ơ�       Face::IsValid
���������ܡ�       ��֤��ǰ��Ԫ�ص���Ч��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ���ز���ֵ����ʾ��ǰ��Ԫ���Ƿ���Ч
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool Face::IsValid() const {
    return IsValid(GetCoordinates());
}

/*************************************************************************
���������ơ�       Face::IsValid
���������ܡ�       ��֤���������Ƿ񹹳���Ч����Ԫ��
����ڲ�����       CoordsInput - �����������������
�����ڲ�����       ��
������ֵ��         ���ز���ֵ����ʾ�����Ƿ񹹳���Ч����Ԫ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool Face::IsValid(
    const std::vector<std::array<double, 3>>& CoordsInput) {
    Point Point1 = Point({ CoordsInput[0] });
    Point Point2 = Point({ CoordsInput[1] });
    Point Point3 = Point({ CoordsInput[2] });
    // ��������Ƿ���
    if (Point::IsCollinear(Point1, Point2, Point3)) {
        throw ExceptionCollinearPoints();
    }

    // ����Ƿ����ظ��ĵ�
    if (Point1.IsSame(Point2) 
        || Point2.IsSame(Point3) 
        || Point3.IsSame(Point1)) {
        return false;
    }

    return true;
}



