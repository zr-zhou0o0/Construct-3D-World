/*************************************************************************
���ļ�����                 FaceSet.hpp
������ģ���Ŀ�ġ�         �漯������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <memory>
#include <vector>
#include <array>
#include "../Point/Point.hpp"
#include "../Element/Face.hpp"
#include "../PointSet/PointSet.hpp"
#include "ElementSet.hpp"

#ifndef FACESET_HPP
#define FACESET_HPP

/*************************************************************************
��������             FaceSet
�����ܡ�             �漯��
���ӿ�˵����         �ṩ�漯�Ĺ���Ͳ����ӿ�
�������߼����ڡ�     ����� 2024/8/12
�����ļ�¼��         ��
*************************************************************************/
class FaceSet : public ElementSet<3> {
public:
    //--------------------------------------------------------------------
    //��Ҫ�Ĺ��졢��������ֵ��Ϊ
    //--------------------------------------------------------------------
    //���㼯ָ��Ĺ��캯��
    FaceSet(std::shared_ptr<PointSet> pPointSet);
    //���㼯ָ������漯�Ĺ��캯��
    FaceSet(std::shared_ptr<PointSet> pPointSet, 
        const std::vector<std::array<unsigned int, 3>>& NewFaceSet);
    // �������캯��
    FaceSet(const FaceSet& Source);
    // ��ֵ���������
    FaceSet& operator=(const FaceSet& Source);
    //����������
    virtual ~FaceSet() = default;

    //--------------------------------------------------------------------
    //�漯�Ĳ���
    //--------------------------------------------------------------------
    //��ȡ�漯
    std::vector<std::array<unsigned int, 3>> GetElementSet() const override;
    //��ȡָ����������
    std::vector<std::array<unsigned int, 3>> GetElement(
        unsigned int uIndex) const override;
    //��ȡ�漯����
    std::vector<unsigned int> GetElementSetIndex() const override;
    //������
    unsigned int FindElement(const Element<3>& NewFace)const;
    //ɾ���棨ͨ��������
    bool Delete(const unsigned int uIndex) override;
    //ɾ���棨ͨ����������
    bool Delete(const std::array<unsigned int, 3>& PointIndex) override;
    //����棨ͨ�������
    unsigned int Add(const Element<3>& NewElement) override;
    //����棨ͨ�����������飩
    unsigned int Add(const std::array<unsigned int, 3>& uIndex) override;
    //����棨ͨ����������飩
    unsigned int Add(const std::array<Point, 3>& Points) override;
    //����棨ͨ���������飩
    unsigned int Add(
        const std::vector<std::array<double, 3>>& Coordinates) override;
    //�޸���
    bool Modify(unsigned int uElementIndex, 
        unsigned int uPointIndex, const Point& NewPoint) override;
    //�޸��棨ͨ�����꣩
    bool Modify(unsigned int uElementIndex, unsigned int uPointIndex, 
        const std::array<double, 3>& Coordinates) override;
    //��ȡ���еĵ�
    std::array<unsigned int, 3> GetPointsInElement(
        const unsigned int uElementIndex) const override;
    //��ȡ������
    unsigned int GetTotalCount() const override;
    //��ȡ���ܳ���
    double GetTotalLength() const override;
    //��ȡ�������
    double GetTotalArea() const override;
    //��ȡ����������
    std::vector<double> GetFaceAreas() const;
    //����漯
    void ClearElementSet();

    //--------------------------------------------------------------------
    //�쳣������
    //--------------------------------------------------------------------
    //�ظ����쳣
    class ExceptionDuplicateFace : public std::invalid_argument {
    public:
        ExceptionDuplicateFace();
    };

private:
    //�漯
    std::vector<std::array<unsigned int, 3>> m_FaceSet = {};
    //�㼯ָ��
    std::shared_ptr<PointSet> m_pPointSet = nullptr;
};

#endif // FACESET_HPP



