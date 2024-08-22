/*************************************************************************
���ļ�����                 Model3D.hpp
������ģ���Ŀ�ġ�         ��άģ��������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include<ostream>
#include<sstream>
#include<string>
#include<array>
#include<vector>
#include<algorithm>
#include <memory>
#include <mutex>

#include"../Point/Point.hpp"

#include"../Element/Element.hpp"
#include"../Element/Line.hpp"
#include"../Element/Face.hpp"

#include"../PointSet/PointSet.hpp"

#include"../ElementSet/ElementSet.hpp"
#include"../ElementSet/LineSet.hpp"
#include"../ElementSet/FaceSet.hpp"

using namespace std;

#ifndef MODEL3D_HPP
#define MODEL3D_HPP

/*************************************************************************
��������             Model3D
�����ܡ�             ��άģ����
���ӿ�˵����         �ṩ����άģ�͵ĵ㡢�ߡ��������ģ��ͳ�ƹ���
�������߼����ڡ�     ����� 2024/8/12
�����ļ�¼��         ��
*************************************************************************/
class Model3D {
public:
    //--------------------------------------------------------------------
    // �쳣��
    //--------------------------------------------------------------------
    // δ��ʼ��ģ���쳣��
    class ExceptionUninitModel: public std::runtime_error {
    public:
        ExceptionUninitModel();
    };

    // ��Ч�����쳣��
    class ExceptionInvalidName: public std::invalid_argument {
    public:
        ExceptionInvalidName();
    };

    //--------------------------------------------------------------------
    // ��Ҫ�Ĺ��졢��������ֵ��Ϊ
    //--------------------------------------------------------------------
    // ɾ���������캯���͸�ֵ�����
    Model3D(const Model3D& Source) = delete;
    Model3D& operator=(const Model3D& Source) = delete;

    // ��ȡ����ʵ���ľ�̬����
    static Model3D& GetInstance();

    // ��ʼ�������ľ�̬����
    static void InitInstance();
    static void InitInstance(const PointSet& NewPointSet, 
        const LineSet& NewLineSet, const FaceSet& NewFaceSet);

    // �Զ���ɾ����
    struct Deleter {
        void operator()(Model3D* Source) const { delete Source; }
    };

    //--------------------------------------------------------------------
    // �����
    //--------------------------------------------------------------------
    // ���õ㼯
    void SetPointSet(const std::vector<std::array<double, 3>>& NewPointSet);
    // ��ȡ�㼯
    std::vector<std::array<double, 3>> GetPointSet()const;
    // ��ȡ�㼯����
    std::vector<unsigned int> GetPointSetIndex() const;
    // ��ӵ�
    unsigned int AddPoint(const Point& NewPoint);
    // ��ӵ㣨ͨ���������飩
    unsigned int AddPoint(const std::array<double, 3>& NewCoords);
    // ���ҵ�
    unsigned int FindPoint(const Point& NewPoint)const;
    // ��ȡָ����Χ�ڵĵ�����
    std::vector<std::array<double, 3>> GetCoordsByIndexRange(
        unsigned int uStartIndex, unsigned int uEndIndex)const;
    // ��ȡָ�������ĵ�����
    std::array<double, 3> GetCoordsByIndex(unsigned int uIndex)const;
    // ��ȡָ�������ĵ�
    Point GetPointByIndex(unsigned int uIndex)const;
    // ͨ�������ȡ����
    unsigned int GetIndexByCoords(
        const std::array<double, 3> NewCoords)const;
    // ͨ��������ȡ����
    unsigned int GetIndexByPoint(const Point& APoint)const;

    //--------------------------------------------------------------------
    // �߲���
    //--------------------------------------------------------------------
    // ����Ƿ�����߶�
    unsigned int HaveLine(const Element<2>& NewLine)const;
    // ɾ���߶Σ�ͨ��������
    bool DeleteLine(const unsigned int uIndex);
    // ɾ���߶Σ�ͨ����������
    bool DeleteLine(const std::array<unsigned int, 2>& PointIndex);
    // ����߶Σ�ͨ���߶ζ���
    unsigned int AddLine(const Element<2>& NewElement);
    // ����߶Σ�ͨ�����������飩
    unsigned int AddLine(const std::array<unsigned int, 2>& Index);
    // ����߶Σ�ͨ����������飩
    unsigned int AddLine(const std::array<Point, 2>& Points);
    // ����߶Σ�ͨ���������飩
    unsigned int AddLine
        (const std::vector<std::array<double, 3>>& NewCoords);
    // �޸��߶�
    bool ModifyLine(unsigned int uElementIndex, unsigned int uPointIndex, 
        const Point& NewPoint);
    // �޸��߶Σ�ͨ�����꣩
    bool ModifyLine(unsigned int uElementIndex, unsigned int uPointIndex, 
        const std::array<double, 3>& NewCoords);
    // ��ȡ�߶��еĵ�
    std::array<unsigned int, 2> GetPointsInLine(
        const unsigned int uElementIndex)const;

    //--------------------------------------------------------------------
    // �����
    //--------------------------------------------------------------------
    // ����Ƿ������
    unsigned int HaveFace(const Element<3>& NewFace)const;
    // ɾ���棨ͨ��������
    bool DeleteFace(const unsigned int uIndex);
    // ɾ���棨ͨ����������
    bool DeleteFace(const std::array<unsigned int, 3>& PointIndex);
    // ����棨ͨ�������
    unsigned int AddFace(const Element<3>& NewElement);
    // ����棨ͨ�����������飩
    unsigned int AddFace(const std::array<unsigned int, 3>& Index);
    // ����棨ͨ����������飩
    unsigned int AddFace(const std::array<Point, 3>& Points);
    // ����棨ͨ���������飩
    unsigned int AddFace(
        const std::vector<std::array<double, 3>>& NewCoords);
    // �޸���
    bool ModifyFace(unsigned int uElementIndex, unsigned int uPointIndex, 
        const Point& NewPoint);
    // �޸��棨ͨ�����꣩
    bool ModifyFace(unsigned int uElementIndex, unsigned int uPointIndex, 
        const std::array<double, 3>& NewCoords);
    // ��ȡ���еĵ�
    std::array<unsigned int, 3> GetPointsInFace(
        unsigned int iElementIndex)const;

    //--------------------------------------------------------------------
    // Getters
    //--------------------------------------------------------------------
    // ��ȡ�����߶�
    std::vector<std::array<unsigned int, 2>> GetLines() const;
    // ��ȡָ���������߶�
    std::vector<std::array<unsigned int, 2>> GetLine(
        const unsigned int Index)const;
    // ��ȡ�߶μ��ϵ�����
    std::vector<unsigned int> GetLineSetIndex() const;

    // ��ȡ������
    std::vector<std::array<unsigned int, 3>> GetFaces() const;
    // ��ȡָ����������
    std::vector<std::array<unsigned int, 3>> GetFace(
        const unsigned int Index)const;
    // ��ȡ�漯�ϵ�����
    std::vector<unsigned int> GetFaceSetIndex() const;

    //--------------------------------------------------------------------
    // ģ��ͳ��
    //--------------------------------------------------------------------
    // ��ȡ�������
    unsigned int GetPointCount() const;
    // ��ȡ�߶ε�����
    unsigned int GetLineCount() const;
    // ��ȡ�������
    unsigned int GetFaceCount() const;
    // ��ȡ�߶ε��ܳ���
    double GetTotalLineLength() const;
    // ��ȡ��������
    double GetTotalFaceArea() const;
    // ��ȡ��Χ�����
    double GetBoundingBoxVolume()const;

    // ��ȡ�����߶εĳ���
    std::vector<double> GetLineLegnths() const;
    // ��ȡ����������
    std::vector<double> GetFaceAreas() const;

    //--------------------------------------------------------------------
    // ģ������
    //--------------------------------------------------------------------
    // ����ģ������
    bool SetModelName(const std::string& NewName);
    // ��ȡģ������
    std::string GetModelName()const;

    // ���ģ��
    void ClearModel();

private:
    //--------------------------------------------------------------------
    // ˽�й��캯������������
    //--------------------------------------------------------------------
    // Ĭ�Ϲ��캯��
    Model3D();
    // ���ι��캯��
    Model3D(const PointSet& NewPointSet, const LineSet& NewLineSet, 
        const FaceSet& NewFaceSet);
    // ��������
    virtual ~Model3D()final = default;

    //--------------------------------------------------------------------
    // ˽�г�Ա����
    //--------------------------------------------------------------------
    // ����������
    static std::unique_ptr<Model3D, Deleter> m_Instance;
    // ������ʼ����־
    static std::once_flag m_OnceFlag;

    // �㼯
    std::shared_ptr<PointSet> m_pPointSet{nullptr};
    // �߼�
    LineSet m_Lines;
    // �漯
    FaceSet m_Faces;

    // ģ������
    std::string m_ModelName;
};

#endif


