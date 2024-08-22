/*************************************************************************
【文件名】                 Model3D.hpp
【功能模块和目的】         三维模型类声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
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
【类名】             Model3D
【功能】             三维模型类
【接口说明】         提供对三维模型的点、线、面操作及模型统计功能
【开发者及日期】     周子睿 2024/8/12
【更改记录】         无
*************************************************************************/
class Model3D {
public:
    //--------------------------------------------------------------------
    // 异常类
    //--------------------------------------------------------------------
    // 未初始化模型异常类
    class ExceptionUninitModel: public std::runtime_error {
    public:
        ExceptionUninitModel();
    };

    // 无效名称异常类
    class ExceptionInvalidName: public std::invalid_argument {
    public:
        ExceptionInvalidName();
    };

    //--------------------------------------------------------------------
    // 必要的构造、析构、赋值行为
    //--------------------------------------------------------------------
    // 删除拷贝构造函数和赋值运算符
    Model3D(const Model3D& Source) = delete;
    Model3D& operator=(const Model3D& Source) = delete;

    // 获取单例实例的静态方法
    static Model3D& GetInstance();

    // 初始化单例的静态方法
    static void InitInstance();
    static void InitInstance(const PointSet& NewPointSet, 
        const LineSet& NewLineSet, const FaceSet& NewFaceSet);

    // 自定义删除器
    struct Deleter {
        void operator()(Model3D* Source) const { delete Source; }
    };

    //--------------------------------------------------------------------
    // 点操作
    //--------------------------------------------------------------------
    // 设置点集
    void SetPointSet(const std::vector<std::array<double, 3>>& NewPointSet);
    // 获取点集
    std::vector<std::array<double, 3>> GetPointSet()const;
    // 获取点集索引
    std::vector<unsigned int> GetPointSetIndex() const;
    // 添加点
    unsigned int AddPoint(const Point& NewPoint);
    // 添加点（通过坐标数组）
    unsigned int AddPoint(const std::array<double, 3>& NewCoords);
    // 查找点
    unsigned int FindPoint(const Point& NewPoint)const;
    // 获取指定范围内的点坐标
    std::vector<std::array<double, 3>> GetCoordsByIndexRange(
        unsigned int uStartIndex, unsigned int uEndIndex)const;
    // 获取指定索引的点坐标
    std::array<double, 3> GetCoordsByIndex(unsigned int uIndex)const;
    // 获取指定索引的点
    Point GetPointByIndex(unsigned int uIndex)const;
    // 通过坐标获取索引
    unsigned int GetIndexByCoords(
        const std::array<double, 3> NewCoords)const;
    // 通过点对象获取索引
    unsigned int GetIndexByPoint(const Point& APoint)const;

    //--------------------------------------------------------------------
    // 线操作
    //--------------------------------------------------------------------
    // 检查是否存在线段
    unsigned int HaveLine(const Element<2>& NewLine)const;
    // 删除线段（通过索引）
    bool DeleteLine(const unsigned int uIndex);
    // 删除线段（通过点索引）
    bool DeleteLine(const std::array<unsigned int, 2>& PointIndex);
    // 添加线段（通过线段对象）
    unsigned int AddLine(const Element<2>& NewElement);
    // 添加线段（通过点索引数组）
    unsigned int AddLine(const std::array<unsigned int, 2>& Index);
    // 添加线段（通过点对象数组）
    unsigned int AddLine(const std::array<Point, 2>& Points);
    // 添加线段（通过坐标数组）
    unsigned int AddLine
        (const std::vector<std::array<double, 3>>& NewCoords);
    // 修改线段
    bool ModifyLine(unsigned int uElementIndex, unsigned int uPointIndex, 
        const Point& NewPoint);
    // 修改线段（通过坐标）
    bool ModifyLine(unsigned int uElementIndex, unsigned int uPointIndex, 
        const std::array<double, 3>& NewCoords);
    // 获取线段中的点
    std::array<unsigned int, 2> GetPointsInLine(
        const unsigned int uElementIndex)const;

    //--------------------------------------------------------------------
    // 面操作
    //--------------------------------------------------------------------
    // 检查是否存在面
    unsigned int HaveFace(const Element<3>& NewFace)const;
    // 删除面（通过索引）
    bool DeleteFace(const unsigned int uIndex);
    // 删除面（通过点索引）
    bool DeleteFace(const std::array<unsigned int, 3>& PointIndex);
    // 添加面（通过面对象）
    unsigned int AddFace(const Element<3>& NewElement);
    // 添加面（通过点索引数组）
    unsigned int AddFace(const std::array<unsigned int, 3>& Index);
    // 添加面（通过点对象数组）
    unsigned int AddFace(const std::array<Point, 3>& Points);
    // 添加面（通过坐标数组）
    unsigned int AddFace(
        const std::vector<std::array<double, 3>>& NewCoords);
    // 修改面
    bool ModifyFace(unsigned int uElementIndex, unsigned int uPointIndex, 
        const Point& NewPoint);
    // 修改面（通过坐标）
    bool ModifyFace(unsigned int uElementIndex, unsigned int uPointIndex, 
        const std::array<double, 3>& NewCoords);
    // 获取面中的点
    std::array<unsigned int, 3> GetPointsInFace(
        unsigned int iElementIndex)const;

    //--------------------------------------------------------------------
    // Getters
    //--------------------------------------------------------------------
    // 获取所有线段
    std::vector<std::array<unsigned int, 2>> GetLines() const;
    // 获取指定索引的线段
    std::vector<std::array<unsigned int, 2>> GetLine(
        const unsigned int Index)const;
    // 获取线段集合的索引
    std::vector<unsigned int> GetLineSetIndex() const;

    // 获取所有面
    std::vector<std::array<unsigned int, 3>> GetFaces() const;
    // 获取指定索引的面
    std::vector<std::array<unsigned int, 3>> GetFace(
        const unsigned int Index)const;
    // 获取面集合的索引
    std::vector<unsigned int> GetFaceSetIndex() const;

    //--------------------------------------------------------------------
    // 模型统计
    //--------------------------------------------------------------------
    // 获取点的总数
    unsigned int GetPointCount() const;
    // 获取线段的总数
    unsigned int GetLineCount() const;
    // 获取面的总数
    unsigned int GetFaceCount() const;
    // 获取线段的总长度
    double GetTotalLineLength() const;
    // 获取面的总面积
    double GetTotalFaceArea() const;
    // 获取包围盒体积
    double GetBoundingBoxVolume()const;

    // 获取所有线段的长度
    std::vector<double> GetLineLegnths() const;
    // 获取所有面的面积
    std::vector<double> GetFaceAreas() const;

    //--------------------------------------------------------------------
    // 模型名称
    //--------------------------------------------------------------------
    // 设置模型名称
    bool SetModelName(const std::string& NewName);
    // 获取模型名称
    std::string GetModelName()const;

    // 清空模型
    void ClearModel();

private:
    //--------------------------------------------------------------------
    // 私有构造函数和析构函数
    //--------------------------------------------------------------------
    // 默认构造函数
    Model3D();
    // 带参构造函数
    Model3D(const PointSet& NewPointSet, const LineSet& NewLineSet, 
        const FaceSet& NewFaceSet);
    // 析构函数
    virtual ~Model3D()final = default;

    //--------------------------------------------------------------------
    // 私有成员变量
    //--------------------------------------------------------------------
    // 单例计数器
    static std::unique_ptr<Model3D, Deleter> m_Instance;
    // 单例初始化标志
    static std::once_flag m_OnceFlag;

    // 点集
    std::shared_ptr<PointSet> m_pPointSet{nullptr};
    // 线集
    LineSet m_Lines;
    // 面集
    FaceSet m_Faces;

    // 模型名称
    std::string m_ModelName;
};

#endif


