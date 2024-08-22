/*************************************************************************
���ļ�����                 Line.hpp
������ģ���Ŀ�ġ�         ��Ԫ��������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <ostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>

#include "Element.hpp"
#include "../Point/Point.hpp"

using namespace std;

#ifndef LINE_HPP
#define LINE_HPP

/*************************************************************************
��������              Line
�����ܡ�              ��ʾ��Ԫ�ص��࣬�̳��� Element<2>
���ӿ�˵����          �ṩ���캯�����������������úͻ�ȡ����͵�ĺ�����
                      ���㳤�ȵĺ���
�������߼����ڡ�      ����� 2024/8/12
�����ļ�¼��          ��
*************************************************************************/
class Line : public Element<2> {
public:
    //--------------------------------------------------------------------
    // �ڲ��쳣��
    //--------------------------------------------------------------------
    // ��ʾδ��������쳣
    class ExceptionUndefinedArea : public std::logic_error {
    public:
        // Ĭ�Ϲ��캯��
        ExceptionUndefinedArea();
    };

    //--------------------------------------------------------------------
    // ��Ҫ�Ĺ��졢��������ֵ��Ϊ
    //--------------------------------------------------------------------
    // Ĭ�Ϲ��캯��
    Line();
    // ͨ�����깹��
    Line(const std::vector<std::array<double, 3>>& Coords);
    // ͨ���㹹��
    Line(const std::array<Point, 2>& Points);
    //�������캯��
    Line(const Line& Source);
    //��ֵ�����overload
    Line& operator=(const Line& Source);
    // ��������
    ~Line();

    //--------------------------------------------------------------------
    // �Ǿ�̬������
    //--------------------------------------------------------------------
    // ��������
    void SetCoordinates(
        const std::vector<std::array<double, 3>>& Coords) override;
    // ���õ�
    void SetPoints(const std::array<Point, 2>& Points) override;

    //--------------------------------------------------------------------
    // �Ǿ�̬��ȡ��
    //--------------------------------------------------------------------
    // ��ȡ����
    std::vector<std::array<double, 3>> GetCoordinates() const override;
    // ��ȡ��
    std::array<Point, 2> GetPoints() const override;
    // ��ȡ������ַ�����ʾ
    std::string ToString() const override;

    //--------------------------------------------------------------------
    // ���μ���
    //--------------------------------------------------------------------
    // ��ȡ�߶γ���
    double GetLength() const override;
    // ��ȡ������߶���������׳��쳣��
    double GetArea() const override;

    //--------------------------------------------------------------------
    // ��֤����
    //--------------------------------------------------------------------
    // �������Ԫ���Ƿ���ͬ
    bool IsSame(const Element<2>& NewElement) const override;
    // �������Ƿ���Ч
    bool IsValid() const override;
    // ��̬�������������������Ƿ񹹳���Ч�߶�
    static bool IsValid(
        const std::vector<std::array<double, 3>>& CoordsInput);

private:
    //--------------------------------------------------------------------
    // ��Ա����
    //--------------------------------------------------------------------
    // ��1
    Point m_Point1{};
    // ��2
    Point m_Point2{};
};

#endif


