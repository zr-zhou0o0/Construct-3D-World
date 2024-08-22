/*************************************************************************
���ļ�����                 LineSet.hpp
������ģ���Ŀ�ġ�         �߼�������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <memory>
#include <vector>
#include <array>
#include <stdexcept>

#include "../Point/Point.hpp"
#include "../Element/Line.hpp"
#include "../PointSet/PointSet.hpp"
#include "ElementSet.hpp"

using namespace std;

#ifndef LINESET_HPP
#define LINESET_HPP

/*************************************************************************
��������             LineSet
�����ܡ�             �߼��࣬����һ���߶�
���ӿ�˵����         �ṩ��ӡ�ɾ�����޸��߶εķ�����
                     �Լ���ȡ�߶μ��Ϻ����Եķ���
�������߼����ڡ�     ����� 2024/8/12
�����ļ�¼��         ��
*************************************************************************/
class LineSet : public ElementSet<2> {
public:
    //--------------------------------------------------------------------
    //��Ҫ�Ĺ��졢��������ֵ��Ϊ
    //--------------------------------------------------------------------
    //���캯������ʼ���߼���
    LineSet(std::shared_ptr<PointSet> pPointSet);
    //���캯������ʼ���߼��࣬���߶μ��ϲ���
    LineSet(std::shared_ptr<PointSet> pPointSet, 
        const std::vector<std::array<unsigned int, 2>>& NewLineSet);
    // �������캯��
    LineSet(const LineSet& Source);
    // ��ֵ���������
    LineSet& operator=(const LineSet& Source);
    //Ĭ����������
    virtual ~LineSet() = default;

    //--------------------------------------------------------------------
    //��ȡ�߶μ��ϵķ���
    //--------------------------------------------------------------------
    //��ȡ�߶μ���
    std::vector<std::array<unsigned int, 2>> GetElementSet() const override;
    //��ȡָ���������߶�
    std::vector<std::array<unsigned int, 2>> GetElement(
        const unsigned int uIndex) const override;
    //��ȡ�߶μ��ϵ�����
    std::vector<unsigned int> GetElementSetIndex() const override;

    //--------------------------------------------------------------------
    //���ҡ���ӡ�ɾ�����޸��߶εķ���
    //--------------------------------------------------------------------
    //�����߶�
    unsigned int FindElement(const Element<2>& NewLine)const override;
    //ɾ���߶Σ�ͨ��������
    bool Delete(const unsigned int uIndex) override;
    //ɾ���߶Σ�ͨ����������
    bool Delete(const std::array<unsigned int, 2>& PointIndex) override;
    //����߶Σ�ͨ���߶ζ���
    unsigned int Add(const Element<2>& NewElement) override;
    //����߶Σ�ͨ�����������飩
    unsigned int Add(const std::array<unsigned int, 2>& Index) override;
    //����߶Σ�ͨ����������飩
    unsigned int Add(const std::array<Point, 2>& Points) override;
    //����߶Σ�ͨ���������飩
    unsigned int Add(
        const std::vector<std::array<double, 3>>& Coordinates) override;
    //�޸��߶�
    bool Modify(unsigned int uElementIndex, 
        unsigned int uPointIndex, const Point& NewPoint) override;
    //�޸��߶Σ�ͨ�����꣩
    bool Modify(unsigned int uElementIndex, unsigned int uPointIndex, 
        const std::array<double, 3>& Coordinates) override;

    //--------------------------------------------------------------------
    //��ȡ�߶����Եķ���
    //--------------------------------------------------------------------
    //��ȡ�߶��еĵ�
    std::array<unsigned int, 2> GetPointsInElement(
        unsigned int uElementIndex) const override;
    //��ȡ�߶�����
    unsigned int GetTotalCount() const override;
    //��ȡ�߶��ܳ���
    double GetTotalLength() const override;
    //��ȡ�߶��������δ���壩
    double GetTotalArea() const override;
    //��ȡ�����߶εĳ���
    std::vector<double> GetLineLengths() const;

    //--------------------------------------------------------------------
    //����߶μ��ϵķ���
    //--------------------------------------------------------------------
    //����߶μ���
    void ClearElementSet();

    //--------------------------------------------------------------------
    //�쳣��
    //--------------------------------------------------------------------
    //�ظ��߶��쳣��
    class ExceptionDuplicateLine : public std::invalid_argument {
    public:
        ExceptionDuplicateLine();
    };

    //δ��������쳣��
    class ExceptionUndefinedArea : public std::logic_error {
    public:
        ExceptionUndefinedArea();
    };

private:
    //--------------------------------------------------------------------
    //��Ա����
    //--------------------------------------------------------------------
    //�߶μ���
    std::vector<std::array<unsigned int, 2>> m_LineSet = {};
    //�㼯ָ��
    std::shared_ptr<PointSet> m_pPointSet = nullptr;
};

#endif

