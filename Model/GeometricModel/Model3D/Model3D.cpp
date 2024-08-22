/*************************************************************************
【文件名】                 Model3D.cpp
【功能模块和目的】         三维模型定义
【开发者及日期】           周子睿 2024/8/13
【更改记录】               无
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
【函数名称】          Model3D::ExceptionUninitModel::ExceptionUninitModel
【函数功能】          未初始化模型异常类构造函数
【入口参数】          无
【出口参数】          无
【返回值】            无
【开发者及日期】      周子睿 2024/8/13
【更改记录】          无
*************************************************************************/
Model3D::ExceptionUninitModel::ExceptionUninitModel()
: std::runtime_error("Model uninitialized.") {
}

/*************************************************************************
【函数名称】          Model3D::ExceptionInvalidName::ExceptionInvalidName
【函数功能】          无效名称异常类构造函数
【入口参数】          无
【出口参数】          无
【返回值】            无
【开发者及日期】      周子睿 2024/8/13
【更改记录】          无
*************************************************************************/
Model3D::ExceptionInvalidName::ExceptionInvalidName()
: std::invalid_argument("Invalid Model Name.") {
}

std::unique_ptr<Model3D, Model3D::Deleter> Model3D::m_Instance = nullptr;
std::once_flag Model3D::m_OnceFlag;

/*************************************************************************
【函数名称】              Model3D::Model3D
【函数功能】              Model3D类默认构造函数
【入口参数】              无
【出口参数】              无
【返回值】                无
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
Model3D::Model3D() : 
m_pPointSet(std::make_shared<PointSet>()), 
m_Lines(m_pPointSet), 
m_Faces(m_pPointSet),
m_ModelName("NewModel") {
}

/*************************************************************************
【函数名称】              Model3D::Model3D
【函数功能】              Model3D类带参构造函数
【入口参数】              const PointSet& NewPointSet, 
                          const LineSet& NewLineSet, 
                          const FaceSet& NewFaceSet
【出口参数】              无
【返回值】                无
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
Model3D::Model3D(const PointSet& NewPointSet, const LineSet& NewLineSet, 
    const FaceSet& NewFaceSet)
: m_pPointSet(std::make_shared<PointSet>(NewPointSet)), 
m_Lines(NewLineSet), m_Faces(NewFaceSet), m_ModelName("NewModel") {
}

/*************************************************************************
【函数名称】              Model3D::GetInstance
【函数功能】              获取Model3D单例实例
【入口参数】              无
【出口参数】              无
【返回值】                Model3D& - 单例实例的引用
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
Model3D& Model3D::GetInstance() {
    if (!m_Instance) {
        throw ExceptionUninitModel();
    }
    return *m_Instance;
}

/*************************************************************************
【函数名称】              Model3D::InitInstance
【函数功能】              初始化Model3D单例实例
【入口参数】              无
【出口参数】              无
【返回值】                无
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
void Model3D::InitInstance() {
    std::call_once(m_OnceFlag, []() {
        m_Instance = std::unique_ptr<Model3D, Model3D::Deleter>(new Model3D());
        });
}

/*************************************************************************
【函数名称】              Model3D::InitInstance
【函数功能】              初始化Model3D单例实例（带参数）
【入口参数】              const PointSet& NewPointSet, 
                          const LineSet& NewLineSet, 
                          const FaceSet& NewFaceSet
【出口参数】              无
【返回值】                无
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
void Model3D::InitInstance(const PointSet& NewPointSet, 
    const LineSet& NewLineSet, const FaceSet& NewFaceSet) {
    std::call_once(m_OnceFlag, [&]() {
        m_Instance = std::unique_ptr<Model3D, Model3D::Deleter>
            (new Model3D(NewPointSet, NewLineSet, NewFaceSet));
        });
}


/*************************************************************************
【函数名称】          Model3D::SetPointSet
【函数功能】          设置点集
【入口参数】          const std::vector<std::array<double, 3>>& NewPointSet
【出口参数】          无
【返回值】            无
【开发者及日期】      周子睿 2024/8/13
【更改记录】          无
*************************************************************************/
void Model3D::SetPointSet(
    const std::vector<std::array<double, 3>>& NewPointSet) {
    m_pPointSet->SetPointSet(NewPointSet);
}

/*************************************************************************
【函数名称】              Model3D::GetPointSet
【函数功能】              获取点集
【入口参数】              无
【出口参数】              无
【返回值】                std::vector<std::array<double, 3>> - 点集
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
std::vector<std::array<double, 3>> Model3D::GetPointSet() const {
    return m_pPointSet->GetPointSet();
}

/*************************************************************************
【函数名称】              Model3D::GetPointSetIndex
【函数功能】              获取点集索引
【入口参数】              无
【出口参数】              无
【返回值】                std::vector<unsigned int> - 点集索引
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
std::vector<unsigned int> Model3D::GetPointSetIndex() const {
    return m_pPointSet->GetPointSetIndex();
}

/*************************************************************************
【函数名称】              Model3D::AddPoint
【函数功能】              添加点
【入口参数】              const Point& NewPoint
【出口参数】              无
【返回值】                unsigned int - 新点的索引
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
unsigned int Model3D::AddPoint(const Point& NewPoint) {
    return m_pPointSet->AddPoint(NewPoint);
}

/*************************************************************************
【函数名称】              Model3D::AddPoint
【函数功能】              添加点（通过坐标数组）
【入口参数】              const std::array<double, 3>& NewCoords
【出口参数】              无
【返回值】                unsigned int - 新点的索引
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
unsigned int Model3D::AddPoint(const std::array<double, 3>& NewCoords) {
    return m_pPointSet->AddPoint(NewCoords);
}

/*************************************************************************
【函数名称】              Model3D::FindPoint
【函数功能】              查找点
【入口参数】              const Point& NewPoint
【出口参数】              无
【返回值】                unsigned int - 点的索引
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
unsigned int Model3D::FindPoint(const Point& NewPoint) const {
    return m_pPointSet->FindPoint(NewPoint);
}

/*************************************************************************
【函数名称】              Model3D::GetCoordsByIndexRange
【函数功能】              获取指定范围内的点坐标
【入口参数】              unsigned int uStartIndex, unsigned int uEndIndex
【出口参数】              无
【返回值】                std::vector<std::array<double, 3>> - 点坐标数组
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
std::vector<std::array<double, 3>> Model3D::GetCoordsByIndexRange(
    unsigned int uStartIndex, unsigned int uEndIndex) const {
    return m_pPointSet->GetCoordsByIndexRange(uStartIndex, uEndIndex);
}

/*************************************************************************
【函数名称】              Model3D::GetCoordsByIndex
【函数功能】              获取指定索引的点坐标
【入口参数】              unsigned int uIndex
【出口参数】              无
【返回值】                std::array<double, 3> - 点坐标
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
std::array<double, 3> Model3D::GetCoordsByIndex(unsigned int uIndex) const {
    return m_pPointSet->GetCoordsByIndex(uIndex);
}

/*************************************************************************
【函数名称】              Model3D::GetPointByIndex
【函数功能】              获取指定索引的点
【入口参数】              unsigned int uIndex
【出口参数】              无
【返回值】                Point
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
Point Model3D::GetPointByIndex(unsigned int uIndex) const {
    return m_pPointSet->GetPointByIndex(uIndex);
}

/*************************************************************************
【函数名称】              Model3D::GetIndexByCoords
【函数功能】              获取指定坐标的点索引
【入口参数】              点坐标
【出口参数】              无
【返回值】                unsigned int Index
【开发者及日期】          周子睿 2024/8/13
【更改记录】              无
*************************************************************************/
unsigned int Model3D::GetIndexByCoords(std::array<double, 3> Coords) const {
    return m_pPointSet->GetIndexByCoords(Coords);
}
/*************************************************************************
【函数名称】       Model3D::GetIndexByPoint
【函数功能】       获取指定点对象的索引
【入口参数】       Point& point - 点对象的引用
【出口参数】       无
【返回值】         unsigned int - 点对象的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::GetIndexByPoint(const Point& APoint) const {
    return m_pPointSet->GetIndexByPoint(APoint);
}

/*************************************************************************
【函数名称】       Model3D::HaveLine
【函数功能】       检查是否存在指定的线段
【入口参数】       const Element<2>& NewLine - 线段对象的引用
【出口参数】       无
【返回值】         unsigned int - 线段的索引，如果不存在则返回无效索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::HaveLine(const Element<2>& NewLine)const {
    return m_Lines.FindElement(NewLine);
}

/*************************************************************************
【函数名称】       Model3D::DeleteLine
【函数功能】       删除指定索引的线段
【入口参数】       const unsigned int Index - 线段的索引
【出口参数】       无
【返回值】         bool - 删除是否成功
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
bool Model3D::DeleteLine(const unsigned int uIndex) {
    return m_Lines.Delete(uIndex);
}

/*************************************************************************
【函数名称】       Model3D::DeleteLine
【函数功能】       删除指定点索引的线段
【入口参数】       const std::array<unsigned int, 2>& PointIndex 点索引数组
【出口参数】       无
【返回值】         bool - 删除是否成功
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
bool Model3D::DeleteLine(const std::array<unsigned int, 2>& PointIndex) {
    return m_Lines.Delete(PointIndex);
}

/*************************************************************************
【函数名称】       Model3D::AddLine
【函数功能】       添加线段对象
【入口参数】       const Element<2>& NewElement - 线段对象的引用
【出口参数】       无
【返回值】         unsigned int - 新添加的线段的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::AddLine(const Element<2>& NewElement) {
    return m_Lines.Add(NewElement);
}

/*************************************************************************
【函数名称】       Model3D::AddLine
【函数功能】       添加线段，通过点索引数组
【入口参数】       const std::array<unsigned int, 2>& Index - 点索引数组
【出口参数】       无
【返回值】         unsigned int - 新添加的线段的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::AddLine(const std::array<unsigned int, 2>& Index) {
    return m_Lines.Add(Index);
}

/*************************************************************************
【函数名称】       Model3D::AddLine
【函数功能】       添加线段，通过点对象数组
【入口参数】       const std::array<Point, 2>& Points - 点对象数组
【出口参数】       无
【返回值】         unsigned int - 新添加的线段的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::AddLine(const std::array<Point, 2>& Points) {
    return m_Lines.Add(Points);
}

/*************************************************************************
【函数名称】       Model3D::AddLine
【函数功能】       添加线段，通过坐标数组
【入口参数】       const std::vector<std::array<double, 3>>& NewCoords 
                   (坐标数组)
【出口参数】       无
【返回值】         unsigned int - 新添加的线段的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::AddLine(
    const std::vector<std::array<double, 3>>& NewCoords) {
    return m_Lines.Add(NewCoords);
}

/*************************************************************************
【函数名称】       Model3D::ModifyLine
【函数功能】       修改线段，通过点对象
【入口参数】       unsigned int iElementIndex - 线段索引
                   unsigned int iPointIndex - 点索引
                   const Point& NewPoint - 新点对象
【出口参数】       无
【返回值】         bool - 修改是否成功
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
bool Model3D::ModifyLine(unsigned int uElementIndex, 
    unsigned int uPointIndex, const Point& NewPoint) {
    return m_Lines.Modify(uElementIndex, uPointIndex, NewPoint);
}

/*************************************************************************
【函数名称】       Model3D::ModifyLine
【函数功能】       修改线段，通过坐标数组
【入口参数】       unsigned int iElementIndex - 线段索引
                   unsigned int iPointIndex - 点索引
                   const std::array<double, 3>& NewCoords - 新坐标数组
【出口参数】       无
【返回值】         bool - 修改是否成功
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
bool Model3D::ModifyLine(unsigned int uElementIndex, 
    unsigned int uPointIndex, const std::array<double, 3>& NewCoords) {
    return m_Lines.Modify(uElementIndex, uPointIndex, NewCoords);
}

/*************************************************************************
【函数名称】       Model3D::GetPointsInLine
【函数功能】       获取线段中的点
【入口参数】       const unsigned int iElementIndex - 线段索引
【出口参数】       无
【返回值】         std::array<unsigned int, 2> - 线段中的点索引数组
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::array<unsigned int, 2> Model3D::GetPointsInLine(
    const unsigned int uElementIndex) const {
    return m_Lines.GetPointsInElement(uElementIndex);
}

/*************************************************************************
【函数名称】       Model3D::HaveFace
【函数功能】       检查是否存在指定的面
【入口参数】       const Element<3>& NewFace - 面对象的引用
【出口参数】       无
【返回值】         unsigned int - 面的索引，如果不存在则返回无效索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::HaveFace(const Element<3>& NewFace)const {
    return m_Faces.FindElement(NewFace);
}

/*************************************************************************
【函数名称】       Model3D::DeleteFace
【函数功能】       删除指定索引的面
【入口参数】       const unsigned int Index - 面的索引
【出口参数】       无
【返回值】         bool - 删除是否成功
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
bool Model3D::DeleteFace(const unsigned int uIndex) {
    return m_Faces.Delete(uIndex);
}

/*************************************************************************
【函数名称】       Model3D::DeleteFace
【函数功能】       删除指定点索引的面
【入口参数】       const std::array<unsigned int, 3>& PointIndex 点索引数组
【出口参数】       无
【返回值】         bool - 删除是否成功
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
bool Model3D::DeleteFace(const std::array<unsigned int, 3>& PointIndex) {
    return m_Faces.Delete(PointIndex);
}

/*************************************************************************
【函数名称】       Model3D::AddFace
【函数功能】       添加面对象
【入口参数】       const Element<3>& NewElement - 面对象的引用
【出口参数】       无
【返回值】         unsigned int - 新添加的面的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::AddFace(const Element<3>& NewElement) {
    return m_Faces.Add(NewElement);
}

/*************************************************************************
【函数名称】       Model3D::AddFace
【函数功能】       添加面，通过点索引数组
【入口参数】       const std::array<unsigned int, 3>& Index - 点索引数组
【出口参数】       无
【返回值】         unsigned int - 新添加的面的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::AddFace(const std::array<unsigned int, 3>& Index) {
    return m_Faces.Add(Index);
}

/*************************************************************************
【函数名称】       Model3D::AddFace
【函数功能】       添加面，通过点对象数组
【入口参数】       const std::array<Point, 3>& Points - 点对象数组
【出口参数】       无
【返回值】         unsigned int - 新添加的面的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::AddFace(const std::array<Point, 3>& Points) {
    return m_Faces.Add(Points);
}

/*************************************************************************
【函数名称】       Model3D::AddFace
【函数功能】       添加面，通过坐标数组
【入口参数】       const std::vector<std::array<double, 3>>& NewCoords 
                   (坐标数组)
【出口参数】       无
【返回值】         unsigned int - 新添加的面的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::AddFace(
    const std::vector<std::array<double, 3>>& NewCoords) {
    return m_Faces.Add(NewCoords);
}

/*************************************************************************
【函数名称】       Model3D::ModifyFace
【函数功能】       修改面，通过点对象
【入口参数】       unsigned int iElementIndex - 面索引
                   unsigned int iPointIndex - 点索引
                   const Point& NewPoint - 新点对象
【出口参数】       无
【返回值】         bool - 修改是否成功
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
bool Model3D::ModifyFace(unsigned int uElementIndex, 
    unsigned int uPointIndex, const Point& NewPoint) {
    return m_Faces.Modify(uElementIndex, uPointIndex, NewPoint);
}

/*************************************************************************
【函数名称】       Model3D::ModifyFace
【函数功能】       修改指定索引的面
【入口参数】       unsigned int iElementIndex, unsigned int iPointIndex,
                   const std::array<double, 3>& NewCoords
【出口参数】       无
【返回值】         bool - 修改是否成功
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
bool Model3D::ModifyFace(unsigned int uElementIndex, unsigned int uPointIndex,
    const std::array<double, 3>& NewCoords) {
    return m_Faces.Modify(uElementIndex, uPointIndex, NewCoords);
}

/*************************************************************************
【函数名称】       Model3D::GetPointsInFace
【函数功能】       获取指定索引的面中的点
【入口参数】       const unsigned int iElementIndex
【出口参数】       无
【返回值】         std::array<unsigned int, 3> - 面中的点索引数组
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::array<unsigned int, 3> Model3D::GetPointsInFace(
    const unsigned int uElementIndex) const {
    return m_Faces.GetPointsInElement(uElementIndex);
}

/*************************************************************************
【函数名称】       Model3D::GetLines
【函数功能】       获取所有线段
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<std::array<unsigned int, 2>> - 线段集合
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::vector<std::array<unsigned int, 2>> Model3D::GetLines() const {
    return m_Lines.GetElementSet();
}

/*************************************************************************
【函数名称】       Model3D::GetLineSetIndex
【函数功能】       获取线段集合的索引
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<unsigned int> - 线段集合的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::vector<unsigned int> Model3D::GetLineSetIndex() const {
    return m_Lines.GetElementSetIndex();
}

/*************************************************************************
【函数名称】       Model3D::GetLine
【函数功能】       获取指定索引的线段
【入口参数】       const unsigned int Index
【出口参数】       无
【返回值】         std::vector<std::array<unsigned int, 2>> - 线段集合
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::vector<std::array<unsigned int, 2>> Model3D::GetLine(
    const unsigned int uIndex)const {
    return m_Lines.GetElement(uIndex);
}

/*************************************************************************
【函数名称】       Model3D::GetFaces
【函数功能】       获取所有面
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<std::array<unsigned int, 3>> - 面集合
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::vector<std::array<unsigned int, 3>> Model3D::GetFaces() const {
    return m_Faces.GetElementSet();
}

/*************************************************************************
【函数名称】       Model3D::GetFace
【函数功能】       获取指定索引的面
【入口参数】       const unsigned int Index
【出口参数】       无
【返回值】         std::vector<std::array<unsigned int, 3>> - 面集合
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::vector<std::array<unsigned int, 3>> Model3D::GetFace(
    const unsigned int uIndex)const {
    return m_Faces.GetElement(uIndex);
}

/*************************************************************************
【函数名称】       Model3D::GetFaceSetIndex
【函数功能】       获取面集合的索引
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<unsigned int> - 面集合的索引
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::vector<unsigned int> Model3D::GetFaceSetIndex() const {
    return m_Faces.GetElementSetIndex();
}

/*************************************************************************
【函数名称】       Model3D::GetPointCount
【函数功能】       获取点的总数
【入口参数】       无
【出口参数】       无
【返回值】         unsigned int - 点的总数
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::GetPointCount() const {
    return m_pPointSet->GetTotalPointCount();
}

/*************************************************************************
【函数名称】       Model3D::GetLineCount
【函数功能】       获取线段的总数
【入口参数】       无
【出口参数】       无
【返回值】         unsigned int - 线段的总数
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::GetLineCount() const {
    return m_Lines.GetTotalCount();
}

/*************************************************************************
【函数名称】       Model3D::GetFaceCount
【函数功能】       获取面的总数
【入口参数】       无
【出口参数】       无
【返回值】         unsigned int - 面的总数
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
unsigned int Model3D::GetFaceCount() const {
    return m_Faces.GetTotalCount();
}

/*************************************************************************
【函数名称】       Model3D::GetTotalLineLength
【函数功能】       获取线段的总长度
【入口参数】       无
【出口参数】       无
【返回值】         double - 线段的总长度
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
double Model3D::GetTotalLineLength() const {
    return m_Lines.GetTotalLength();
}

/*************************************************************************
【函数名称】       Model3D::GetTotalFaceArea
【函数功能】       获取面的总面积
【入口参数】       无
【出口参数】       无
【返回值】         double - 面的总面积
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
double Model3D::GetTotalFaceArea() const {
    return m_Faces.GetTotalArea();
}

/*************************************************************************
【函数名称】       Model3D::GetBoundingBoxVolume
【函数功能】       获取包围盒体积
【入口参数】       无
【出口参数】       无
【返回值】         double - 包围盒体积
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
double Model3D::GetBoundingBoxVolume() const {
    return m_pPointSet->GetBoundingBoxVolume();
}

/*************************************************************************
【函数名称】       Model3D::GetLineLegnths
【函数功能】       获取所有线段的长度
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<double> - 线段长度集合
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::vector<double> Model3D::GetLineLegnths() const {
    return m_Lines.GetLineLengths();
}

/*************************************************************************
【函数名称】       Model3D::GetFaceAreas
【函数功能】       获取所有面的面积
【入口参数】       无
【出口参数】       无
【返回值】         std::vector<double> - 面积集合
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::vector<double> Model3D::GetFaceAreas() const {
    return m_Faces.GetFaceAreas();
}

/*************************************************************************
【函数名称】       Model3D::SetModelName
【函数功能】       设置模型名称
【入口参数】       const std::string& NewName
【出口参数】       无
【返回值】         bool - 设置是否成功
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
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
【函数名称】       Model3D::GetModelName
【函数功能】       获取模型名称
【入口参数】       无
【出口参数】       无
【返回值】         std::string - 模型名称
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
std::string Model3D::GetModelName()const {
    return m_ModelName;
}

/*************************************************************************
【函数名称】       Model3D::ClearModel
【函数功能】       清空模型
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
void Model3D::ClearModel() {
    m_pPointSet->ClearPointSet();
    m_Lines.ClearElementSet();
    m_Faces.ClearElementSet();
}




