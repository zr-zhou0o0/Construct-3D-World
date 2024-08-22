/*************************************************************************
���ļ�����                 PointSet.hpp
������ģ���Ŀ�ġ�         ��ά�㼯������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include<ostream>
#include<sstream>
#include<string>
#include<array>
#include<vector>
#include<algorithm>
#include<limits.h>

#include"../Point/Point.hpp"

using namespace std;

#ifndef POINTSET_HPP
#define POINTSET_HPP


/*************************************************************************
��������             PointSet
�����ܡ�             ��ʾ��ά��ļ��ϣ��������ʾ��
���ӿ�˵����         �ṩ��ӵ㡢ɾ���㡢���ҵ�ȹ��ܣ�֧�����ꡢ��������
                     Χ�ȶ��ֽӿ�
�������߼����ڡ�     ����� 2024/8/12
�����ļ�¼��         ��
*************************************************************************/
class PointSet {

public:
    //--------------------------------------------------------------------
    //�������������
    //--------------------------------------------------------------------
    // Ĭ�Ϲ��캯��
    PointSet();
    // ʹ�ø����㼯����PointSet����
    PointSet(const std::vector<std::array<double, 3>>& NewPointSet);
    // �������캯��
    PointSet(const PointSet& Source);
    // ��ֵ���������
    PointSet& operator=(const PointSet& Source);
    // ��������
    virtual ~PointSet();

    //--------------------------------------------------------------------
    //�㼯��������
    //--------------------------------------------------------------------
    // ���õ㼯����ɾ��ԭ�е�
    void SetPointSet(const std::vector<std::array<double, 3>>& NewPointSet);
    // ��ȡ��ǰ�㼯
    std::vector<std::array<double, 3>> GetPointSet() const;
    // ��ȡ�㼯����
    std::vector<unsigned int> GetPointSetIndex() const;

    // ����µ㣬�����µ�����
    unsigned int AddPoint(const Point& NewPoint);
    // ����µ����꣬�����µ�����
    unsigned int AddPoint(const array<double, 3>& NewCoords);
    // ��ָ������������µ�
    unsigned int AddPoint(const Point& NewPoint, unsigned int uIndex);
    // ɾ��ָ�������ĵ�
    bool DeletePoint(unsigned int uIndex);

    //--------------------------------------------------------------------
    //���Һͻ�ȡ����
    //--------------------------------------------------------------------
    // ���ҵ㣬��������
    unsigned int FindPoint(const Point& NewPoint) const;
    // ��ȡָ��������Χ�ڵ�����
    std::vector<std::array<double, 3>> 
        GetCoordsByIndexRange(
            unsigned int uStartIndex, unsigned int uEndIndex) const;
    // ��ȡָ������������
    std::array<double, 3> GetCoordsByIndex(unsigned int uIndex) const;
    // ��ȡָ�������ĵ�
    Point GetPointByIndex(unsigned int uIndex) const;
    // ͨ�������ȡ����
    unsigned int GetIndexByCoords(const std::array<double, 3> Coords) const;
    // ͨ�����ȡ����
    unsigned int GetIndexByPoint(const Point& APoint) const;

    // ��ȡ�������
    unsigned int GetTotalPointCount() const;
    // �����Χ�����
    double GetBoundingBoxVolume() const;

    //--------------------------------------------------------------------
    //���ò���
    //--------------------------------------------------------------------
    // ��յ㼯
    void ClearPointSet();

    //--------------------------------------------------------------------
    //�쳣��
    //--------------------------------------------------------------------
    // ��Ч�����쳣��
    class ExceptionInvalidIndex : public std::out_of_range {
    public:
        ExceptionInvalidIndex();
    };

private:
    //--------------------------------------------------------------------
    //˽�г�Ա����
    //--------------------------------------------------------------------
    // �洢�㼯������
    std::vector<std::array<double, 3>> m_PointSet{};

};

#endif