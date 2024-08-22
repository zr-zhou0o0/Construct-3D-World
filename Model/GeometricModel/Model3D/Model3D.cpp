/*************************************************************************
���ļ�����                 Model3D.cpp
������ģ���Ŀ�ġ�         ��άģ�Ͷ���
�������߼����ڡ�           ����� 2024/8/13
�����ļ�¼��               ��
*************************************************************************/

#include<ostream>
#include<sstream>
#include<string>
#include<array>
#include<vector>
#include<algorithm>
#include <stdexcept>

#include"../Point/Point.hpp"

#include"../Element/Element.hpp"
#include"../Element/Line.hpp"
#include"../Element/Face.hpp"

#include"../PointSet/PointSet.hpp"

#include"../ElementSet/ElementSet.hpp"
#include"../ElementSet/LineSet.hpp"
#include"../ElementSet/FaceSet.hpp"

#include"Model3D.hpp"

using namespace std;

/*************************************************************************
���������ơ�          Model3D::ExceptionUninitModel::ExceptionUninitModel
���������ܡ�          δ��ʼ��ģ���쳣�๹�캯��
����ڲ�����          ��
�����ڲ�����          ��
������ֵ��            ��
�������߼����ڡ�      ����� 2024/8/13
�����ļ�¼��          ��
*************************************************************************/
Model3D::ExceptionUninitModel::ExceptionUninitModel()
: std::runtime_error("Model uninitialized.") {
}

/*************************************************************************
���������ơ�          Model3D::ExceptionInvalidName::ExceptionInvalidName
���������ܡ�          ��Ч�����쳣�๹�캯��
����ڲ�����          ��
�����ڲ�����          ��
������ֵ��            ��
�������߼����ڡ�      ����� 2024/8/13
�����ļ�¼��          ��
*************************************************************************/
Model3D::ExceptionInvalidName::ExceptionInvalidName()
: std::invalid_argument("Invalid Model Name.") {
}

std::unique_ptr<Model3D, Model3D::Deleter> Model3D::m_Instance = nullptr;
std::once_flag Model3D::m_OnceFlag;

/*************************************************************************
���������ơ�              Model3D::Model3D
���������ܡ�              Model3D��Ĭ�Ϲ��캯��
����ڲ�����              ��
�����ڲ�����              ��
������ֵ��                ��
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
Model3D::Model3D() : 
m_pPointSet(std::make_shared<PointSet>()), 
m_Lines(m_pPointSet), 
m_Faces(m_pPointSet),
m_ModelName("NewModel") {
}

/*************************************************************************
���������ơ�              Model3D::Model3D
���������ܡ�              Model3D����ι��캯��
����ڲ�����              const PointSet& NewPointSet, 
                          const LineSet& NewLineSet, 
                          const FaceSet& NewFaceSet
�����ڲ�����              ��
������ֵ��                ��
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
Model3D::Model3D(const PointSet& NewPointSet, const LineSet& NewLineSet, 
    const FaceSet& NewFaceSet)
: m_pPointSet(std::make_shared<PointSet>(NewPointSet)), 
m_Lines(NewLineSet), m_Faces(NewFaceSet), m_ModelName("NewModel") {
}

/*************************************************************************
���������ơ�              Model3D::GetInstance
���������ܡ�              ��ȡModel3D����ʵ��
����ڲ�����              ��
�����ڲ�����              ��
������ֵ��                Model3D& - ����ʵ��������
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
Model3D& Model3D::GetInstance() {
    if (!m_Instance) {
        throw ExceptionUninitModel();
    }
    return *m_Instance;
}

/*************************************************************************
���������ơ�              Model3D::InitInstance
���������ܡ�              ��ʼ��Model3D����ʵ��
����ڲ�����              ��
�����ڲ�����              ��
������ֵ��                ��
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
void Model3D::InitInstance() {
    std::call_once(m_OnceFlag, []() {
        m_Instance = std::unique_ptr<Model3D, Model3D::Deleter>(new Model3D());
        });
}

/*************************************************************************
���������ơ�              Model3D::InitInstance
���������ܡ�              ��ʼ��Model3D����ʵ������������
����ڲ�����              const PointSet& NewPointSet, 
                          const LineSet& NewLineSet, 
                          const FaceSet& NewFaceSet
�����ڲ�����              ��
������ֵ��                ��
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
void Model3D::InitInstance(const PointSet& NewPointSet, 
    const LineSet& NewLineSet, const FaceSet& NewFaceSet) {
    std::call_once(m_OnceFlag, [&]() {
        m_Instance = std::unique_ptr<Model3D, Model3D::Deleter>
            (new Model3D(NewPointSet, NewLineSet, NewFaceSet));
        });
}


/*************************************************************************
���������ơ�          Model3D::SetPointSet
���������ܡ�          ���õ㼯
����ڲ�����          const std::vector<std::array<double, 3>>& NewPointSet
�����ڲ�����          ��
������ֵ��            ��
�������߼����ڡ�      ����� 2024/8/13
�����ļ�¼��          ��
*************************************************************************/
void Model3D::SetPointSet(
    const std::vector<std::array<double, 3>>& NewPointSet) {
    m_pPointSet->SetPointSet(NewPointSet);
}

/*************************************************************************
���������ơ�              Model3D::GetPointSet
���������ܡ�              ��ȡ�㼯
����ڲ�����              ��
�����ڲ�����              ��
������ֵ��                std::vector<std::array<double, 3>> - �㼯
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
std::vector<std::array<double, 3>> Model3D::GetPointSet() const {
    return m_pPointSet->GetPointSet();
}

/*************************************************************************
���������ơ�              Model3D::GetPointSetIndex
���������ܡ�              ��ȡ�㼯����
����ڲ�����              ��
�����ڲ�����              ��
������ֵ��                std::vector<unsigned int> - �㼯����
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
std::vector<unsigned int> Model3D::GetPointSetIndex() const {
    return m_pPointSet->GetPointSetIndex();
}

/*************************************************************************
���������ơ�              Model3D::AddPoint
���������ܡ�              ��ӵ�
����ڲ�����              const Point& NewPoint
�����ڲ�����              ��
������ֵ��                unsigned int - �µ������
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
unsigned int Model3D::AddPoint(const Point& NewPoint) {
    return m_pPointSet->AddPoint(NewPoint);
}

/*************************************************************************
���������ơ�              Model3D::AddPoint
���������ܡ�              ��ӵ㣨ͨ���������飩
����ڲ�����              const std::array<double, 3>& NewCoords
�����ڲ�����              ��
������ֵ��                unsigned int - �µ������
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
unsigned int Model3D::AddPoint(const std::array<double, 3>& NewCoords) {
    return m_pPointSet->AddPoint(NewCoords);
}

/*************************************************************************
���������ơ�              Model3D::FindPoint
���������ܡ�              ���ҵ�
����ڲ�����              const Point& NewPoint
�����ڲ�����              ��
������ֵ��                unsigned int - �������
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
unsigned int Model3D::FindPoint(const Point& NewPoint) const {
    return m_pPointSet->FindPoint(NewPoint);
}

/*************************************************************************
���������ơ�              Model3D::GetCoordsByIndexRange
���������ܡ�              ��ȡָ����Χ�ڵĵ�����
����ڲ�����              unsigned int uStartIndex, unsigned int uEndIndex
�����ڲ�����              ��
������ֵ��                std::vector<std::array<double, 3>> - ����������
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
std::vector<std::array<double, 3>> Model3D::GetCoordsByIndexRange(
    unsigned int uStartIndex, unsigned int uEndIndex) const {
    return m_pPointSet->GetCoordsByIndexRange(uStartIndex, uEndIndex);
}

/*************************************************************************
���������ơ�              Model3D::GetCoordsByIndex
���������ܡ�              ��ȡָ�������ĵ�����
����ڲ�����              unsigned int uIndex
�����ڲ�����              ��
������ֵ��                std::array<double, 3> - ������
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
std::array<double, 3> Model3D::GetCoordsByIndex(unsigned int uIndex) const {
    return m_pPointSet->GetCoordsByIndex(uIndex);
}

/*************************************************************************
���������ơ�              Model3D::GetPointByIndex
���������ܡ�              ��ȡָ�������ĵ�
����ڲ�����              unsigned int uIndex
�����ڲ�����              ��
������ֵ��                Point
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
Point Model3D::GetPointByIndex(unsigned int uIndex) const {
    return m_pPointSet->GetPointByIndex(uIndex);
}

/*************************************************************************
���������ơ�              Model3D::GetIndexByCoords
���������ܡ�              ��ȡָ������ĵ�����
����ڲ�����              ������
�����ڲ�����              ��
������ֵ��                unsigned int Index
�������߼����ڡ�          ����� 2024/8/13
�����ļ�¼��              ��
*************************************************************************/
unsigned int Model3D::GetIndexByCoords(std::array<double, 3> Coords) const {
    return m_pPointSet->GetIndexByCoords(Coords);
}
/*************************************************************************
���������ơ�       Model3D::GetIndexByPoint
���������ܡ�       ��ȡָ������������
����ڲ�����       Point& point - ����������
�����ڲ�����       ��
������ֵ��         unsigned int - ����������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::GetIndexByPoint(const Point& APoint) const {
    return m_pPointSet->GetIndexByPoint(APoint);
}

/*************************************************************************
���������ơ�       Model3D::HaveLine
���������ܡ�       ����Ƿ����ָ�����߶�
����ڲ�����       const Element<2>& NewLine - �߶ζ��������
�����ڲ�����       ��
������ֵ��         unsigned int - �߶ε�����������������򷵻���Ч����
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::HaveLine(const Element<2>& NewLine)const {
    return m_Lines.FindElement(NewLine);
}

/*************************************************************************
���������ơ�       Model3D::DeleteLine
���������ܡ�       ɾ��ָ���������߶�
����ڲ�����       const unsigned int Index - �߶ε�����
�����ڲ�����       ��
������ֵ��         bool - ɾ���Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
bool Model3D::DeleteLine(const unsigned int uIndex) {
    return m_Lines.Delete(uIndex);
}

/*************************************************************************
���������ơ�       Model3D::DeleteLine
���������ܡ�       ɾ��ָ�����������߶�
����ڲ�����       const std::array<unsigned int, 2>& PointIndex ����������
�����ڲ�����       ��
������ֵ��         bool - ɾ���Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
bool Model3D::DeleteLine(const std::array<unsigned int, 2>& PointIndex) {
    return m_Lines.Delete(PointIndex);
}

/*************************************************************************
���������ơ�       Model3D::AddLine
���������ܡ�       ����߶ζ���
����ڲ�����       const Element<2>& NewElement - �߶ζ��������
�����ڲ�����       ��
������ֵ��         unsigned int - ����ӵ��߶ε�����
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::AddLine(const Element<2>& NewElement) {
    return m_Lines.Add(NewElement);
}

/*************************************************************************
���������ơ�       Model3D::AddLine
���������ܡ�       ����߶Σ�ͨ������������
����ڲ�����       const std::array<unsigned int, 2>& Index - ����������
�����ڲ�����       ��
������ֵ��         unsigned int - ����ӵ��߶ε�����
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::AddLine(const std::array<unsigned int, 2>& Index) {
    return m_Lines.Add(Index);
}

/*************************************************************************
���������ơ�       Model3D::AddLine
���������ܡ�       ����߶Σ�ͨ�����������
����ڲ�����       const std::array<Point, 2>& Points - ���������
�����ڲ�����       ��
������ֵ��         unsigned int - ����ӵ��߶ε�����
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::AddLine(const std::array<Point, 2>& Points) {
    return m_Lines.Add(Points);
}

/*************************************************************************
���������ơ�       Model3D::AddLine
���������ܡ�       ����߶Σ�ͨ����������
����ڲ�����       const std::vector<std::array<double, 3>>& NewCoords 
                   (��������)
�����ڲ�����       ��
������ֵ��         unsigned int - ����ӵ��߶ε�����
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::AddLine(
    const std::vector<std::array<double, 3>>& NewCoords) {
    return m_Lines.Add(NewCoords);
}

/*************************************************************************
���������ơ�       Model3D::ModifyLine
���������ܡ�       �޸��߶Σ�ͨ�������
����ڲ�����       unsigned int iElementIndex - �߶�����
                   unsigned int iPointIndex - ������
                   const Point& NewPoint - �µ����
�����ڲ�����       ��
������ֵ��         bool - �޸��Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
bool Model3D::ModifyLine(unsigned int uElementIndex, 
    unsigned int uPointIndex, const Point& NewPoint) {
    return m_Lines.Modify(uElementIndex, uPointIndex, NewPoint);
}

/*************************************************************************
���������ơ�       Model3D::ModifyLine
���������ܡ�       �޸��߶Σ�ͨ����������
����ڲ�����       unsigned int iElementIndex - �߶�����
                   unsigned int iPointIndex - ������
                   const std::array<double, 3>& NewCoords - ����������
�����ڲ�����       ��
������ֵ��         bool - �޸��Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
bool Model3D::ModifyLine(unsigned int uElementIndex, 
    unsigned int uPointIndex, const std::array<double, 3>& NewCoords) {
    return m_Lines.Modify(uElementIndex, uPointIndex, NewCoords);
}

/*************************************************************************
���������ơ�       Model3D::GetPointsInLine
���������ܡ�       ��ȡ�߶��еĵ�
����ڲ�����       const unsigned int iElementIndex - �߶�����
�����ڲ�����       ��
������ֵ��         std::array<unsigned int, 2> - �߶��еĵ���������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::array<unsigned int, 2> Model3D::GetPointsInLine(
    const unsigned int uElementIndex) const {
    return m_Lines.GetPointsInElement(uElementIndex);
}

/*************************************************************************
���������ơ�       Model3D::HaveFace
���������ܡ�       ����Ƿ����ָ������
����ڲ�����       const Element<3>& NewFace - ����������
�����ڲ�����       ��
������ֵ��         unsigned int - �������������������򷵻���Ч����
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::HaveFace(const Element<3>& NewFace)const {
    return m_Faces.FindElement(NewFace);
}

/*************************************************************************
���������ơ�       Model3D::DeleteFace
���������ܡ�       ɾ��ָ����������
����ڲ�����       const unsigned int Index - �������
�����ڲ�����       ��
������ֵ��         bool - ɾ���Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
bool Model3D::DeleteFace(const unsigned int uIndex) {
    return m_Faces.Delete(uIndex);
}

/*************************************************************************
���������ơ�       Model3D::DeleteFace
���������ܡ�       ɾ��ָ������������
����ڲ�����       const std::array<unsigned int, 3>& PointIndex ����������
�����ڲ�����       ��
������ֵ��         bool - ɾ���Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
bool Model3D::DeleteFace(const std::array<unsigned int, 3>& PointIndex) {
    return m_Faces.Delete(PointIndex);
}

/*************************************************************************
���������ơ�       Model3D::AddFace
���������ܡ�       ��������
����ڲ�����       const Element<3>& NewElement - ����������
�����ڲ�����       ��
������ֵ��         unsigned int - ����ӵ��������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::AddFace(const Element<3>& NewElement) {
    return m_Faces.Add(NewElement);
}

/*************************************************************************
���������ơ�       Model3D::AddFace
���������ܡ�       ����棬ͨ������������
����ڲ�����       const std::array<unsigned int, 3>& Index - ����������
�����ڲ�����       ��
������ֵ��         unsigned int - ����ӵ��������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::AddFace(const std::array<unsigned int, 3>& Index) {
    return m_Faces.Add(Index);
}

/*************************************************************************
���������ơ�       Model3D::AddFace
���������ܡ�       ����棬ͨ�����������
����ڲ�����       const std::array<Point, 3>& Points - ���������
�����ڲ�����       ��
������ֵ��         unsigned int - ����ӵ��������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::AddFace(const std::array<Point, 3>& Points) {
    return m_Faces.Add(Points);
}

/*************************************************************************
���������ơ�       Model3D::AddFace
���������ܡ�       ����棬ͨ����������
����ڲ�����       const std::vector<std::array<double, 3>>& NewCoords 
                   (��������)
�����ڲ�����       ��
������ֵ��         unsigned int - ����ӵ��������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::AddFace(
    const std::vector<std::array<double, 3>>& NewCoords) {
    return m_Faces.Add(NewCoords);
}

/*************************************************************************
���������ơ�       Model3D::ModifyFace
���������ܡ�       �޸��棬ͨ�������
����ڲ�����       unsigned int iElementIndex - ������
                   unsigned int iPointIndex - ������
                   const Point& NewPoint - �µ����
�����ڲ�����       ��
������ֵ��         bool - �޸��Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
bool Model3D::ModifyFace(unsigned int uElementIndex, 
    unsigned int uPointIndex, const Point& NewPoint) {
    return m_Faces.Modify(uElementIndex, uPointIndex, NewPoint);
}

/*************************************************************************
���������ơ�       Model3D::ModifyFace
���������ܡ�       �޸�ָ����������
����ڲ�����       unsigned int iElementIndex, unsigned int iPointIndex,
                   const std::array<double, 3>& NewCoords
�����ڲ�����       ��
������ֵ��         bool - �޸��Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
bool Model3D::ModifyFace(unsigned int uElementIndex, unsigned int uPointIndex,
    const std::array<double, 3>& NewCoords) {
    return m_Faces.Modify(uElementIndex, uPointIndex, NewCoords);
}

/*************************************************************************
���������ơ�       Model3D::GetPointsInFace
���������ܡ�       ��ȡָ�����������еĵ�
����ڲ�����       const unsigned int iElementIndex
�����ڲ�����       ��
������ֵ��         std::array<unsigned int, 3> - ���еĵ���������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::array<unsigned int, 3> Model3D::GetPointsInFace(
    const unsigned int uElementIndex) const {
    return m_Faces.GetPointsInElement(uElementIndex);
}

/*************************************************************************
���������ơ�       Model3D::GetLines
���������ܡ�       ��ȡ�����߶�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<std::array<unsigned int, 2>> - �߶μ���
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<unsigned int, 2>> Model3D::GetLines() const {
    return m_Lines.GetElementSet();
}

/*************************************************************************
���������ơ�       Model3D::GetLineSetIndex
���������ܡ�       ��ȡ�߶μ��ϵ�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<unsigned int> - �߶μ��ϵ�����
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::vector<unsigned int> Model3D::GetLineSetIndex() const {
    return m_Lines.GetElementSetIndex();
}

/*************************************************************************
���������ơ�       Model3D::GetLine
���������ܡ�       ��ȡָ���������߶�
����ڲ�����       const unsigned int Index
�����ڲ�����       ��
������ֵ��         std::vector<std::array<unsigned int, 2>> - �߶μ���
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<unsigned int, 2>> Model3D::GetLine(
    const unsigned int uIndex)const {
    return m_Lines.GetElement(uIndex);
}

/*************************************************************************
���������ơ�       Model3D::GetFaces
���������ܡ�       ��ȡ������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<std::array<unsigned int, 3>> - �漯��
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<unsigned int, 3>> Model3D::GetFaces() const {
    return m_Faces.GetElementSet();
}

/*************************************************************************
���������ơ�       Model3D::GetFace
���������ܡ�       ��ȡָ����������
����ڲ�����       const unsigned int Index
�����ڲ�����       ��
������ֵ��         std::vector<std::array<unsigned int, 3>> - �漯��
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::vector<std::array<unsigned int, 3>> Model3D::GetFace(
    const unsigned int uIndex)const {
    return m_Faces.GetElement(uIndex);
}

/*************************************************************************
���������ơ�       Model3D::GetFaceSetIndex
���������ܡ�       ��ȡ�漯�ϵ�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<unsigned int> - �漯�ϵ�����
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::vector<unsigned int> Model3D::GetFaceSetIndex() const {
    return m_Faces.GetElementSetIndex();
}

/*************************************************************************
���������ơ�       Model3D::GetPointCount
���������ܡ�       ��ȡ�������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         unsigned int - �������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::GetPointCount() const {
    return m_pPointSet->GetTotalPointCount();
}

/*************************************************************************
���������ơ�       Model3D::GetLineCount
���������ܡ�       ��ȡ�߶ε�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         unsigned int - �߶ε�����
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::GetLineCount() const {
    return m_Lines.GetTotalCount();
}

/*************************************************************************
���������ơ�       Model3D::GetFaceCount
���������ܡ�       ��ȡ�������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         unsigned int - �������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
unsigned int Model3D::GetFaceCount() const {
    return m_Faces.GetTotalCount();
}

/*************************************************************************
���������ơ�       Model3D::GetTotalLineLength
���������ܡ�       ��ȡ�߶ε��ܳ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         double - �߶ε��ܳ���
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
double Model3D::GetTotalLineLength() const {
    return m_Lines.GetTotalLength();
}

/*************************************************************************
���������ơ�       Model3D::GetTotalFaceArea
���������ܡ�       ��ȡ��������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         double - ��������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
double Model3D::GetTotalFaceArea() const {
    return m_Faces.GetTotalArea();
}

/*************************************************************************
���������ơ�       Model3D::GetBoundingBoxVolume
���������ܡ�       ��ȡ��Χ�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         double - ��Χ�����
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
double Model3D::GetBoundingBoxVolume() const {
    return m_pPointSet->GetBoundingBoxVolume();
}

/*************************************************************************
���������ơ�       Model3D::GetLineLegnths
���������ܡ�       ��ȡ�����߶εĳ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<double> - �߶γ��ȼ���
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::vector<double> Model3D::GetLineLegnths() const {
    return m_Lines.GetLineLengths();
}

/*************************************************************************
���������ơ�       Model3D::GetFaceAreas
���������ܡ�       ��ȡ����������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::vector<double> - �������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::vector<double> Model3D::GetFaceAreas() const {
    return m_Faces.GetFaceAreas();
}

/*************************************************************************
���������ơ�       Model3D::SetModelName
���������ܡ�       ����ģ������
����ڲ�����       const std::string& NewName
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
bool Model3D::SetModelName(const std::string& NewName) {
    if (NewName.empty()) {
        throw ExceptionInvalidName();
    }
    else {
        m_ModelName = NewName;
        return true;
    }
}

/*************************************************************************
���������ơ�       Model3D::GetModelName
���������ܡ�       ��ȡģ������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string - ģ������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
std::string Model3D::GetModelName()const {
    return m_ModelName;
}

/*************************************************************************
���������ơ�       Model3D::ClearModel
���������ܡ�       ���ģ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
void Model3D::ClearModel() {
    m_pPointSet->ClearPointSet();
    m_Lines.ClearElementSet();
    m_Faces.ClearElementSet();
}




