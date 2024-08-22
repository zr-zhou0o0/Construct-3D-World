/*************************************************************************
���ļ�����                 Point.hpp
������ģ���Ŀ�ġ�         ��ά��������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include<ostream>
#include<sstream>
#include<string>
#include<array>
#include<vector>
#include<algorithm>
#include<memory>
#include<stdexcept>

using namespace std;

#ifndef POINT_HPP
#define POINT_HPP

/*************************************************************************
��������             Point
�����ܡ�             ��ʾ��ά�ռ��еĵ�
���ӿ�˵����         �ṩ��Ĵ������������á���ȡ���ȽϺͼ��㹦��
�������߼����ڡ�     ����� 2024/8/12
�����ļ�¼��         ��
*************************************************************************/
class Point
{
public:
    //--------------------------------------------------------------------
    //��Ҫ�Ĺ��졢��������ֵ��Ϊ
    //--------------------------------------------------------------------
    //Ĭ�Ϲ��캯��
    Point();
    //���ι��캯��
    Point(const std::vector<std::array<double, 3>>& NewCoords);
    //�������캯��
    Point(const Point& Source);
    //��ֵ�����overload
    Point& operator=(const Point& Source);
    //����������
    virtual ~Point();

    //--------------------------------------------------------------------
    //�쳣��
    //--------------------------------------------------------------------
    //�������쳣
    class ExceptionEmptyCoords : public invalid_argument {
    public:
        ExceptionEmptyCoords();
    };
    //���������쳣
    class ExceptionExcessParams : public invalid_argument {
    public:
        ExceptionExcessParams();
    };

    //--------------------------------------------------------------------
    //Setter/Getter
    //--------------------------------------------------------------------
    //��������
    void SetCoordinates(
        const std::vector<std::array<double, 3>>& NewCoords);
    //��ȡ����
    std::vector<std::array<double, 3>> GetCoordinates() const;

    //--------------------------------------------------------------------
    //������Ա����
    //--------------------------------------------------------------------
    //�Ƚ������Ƿ���ͬ
    bool IsSame(
        const std::vector<std::array<double, 3>>& NewCoords) const;
    //�Ƚϵ��Ƿ���ͬ
    bool IsSame(const Point& NewPoint) const;
    //�ж��Ƿ���
    bool IsCollinear(const Point& Point1, const Point& Point2) const;
    //�������
    double GetDistance(const Point& NewPoint) const;

    //--------------------------------------------------------------------
    //��̬��Ա����
    //--------------------------------------------------------------------
    //�жϸ��������Ƿ���
    static bool IsCollinear(
        const std::vector<std::array<double, 3>>& NewCoords);
    //�ж������Ƿ���
    static bool IsCollinear(
        const Point& Point1, const Point& Point2, const Point& Point3);
    //�����������
    static double GetDistance(
        const Point& NewPoint1, const Point& NewPoint2);

private:
    //--------------------------------------------------------------------
    //˽�г�Ա����
    //--------------------------------------------------------------------
    //�������
    std::array<double, 3> m_Coordinates{};
};


#endif
