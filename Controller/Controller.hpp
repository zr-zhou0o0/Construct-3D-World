/*************************************************************************
【文件名】                 Controller.cpp
【功能模块和目的】         控制器类声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include<iostream>

#include"../Model/GeometricModel/Point/Point.hpp"

#include"../Model/GeometricModel/Element/Element.hpp"
#include"../Model/GeometricModel/Element/Line.hpp"
#include"../Model/GeometricModel/Element/Face.hpp"

#include"../Model/GeometricModel/PointSet/PointSet.hpp"

#include"../Model/GeometricModel/ElementSet/ElementSet.hpp"
#include"../Model/GeometricModel/ElementSet/LineSet.hpp"
#include"../Model/GeometricModel/ElementSet/FaceSet.hpp"

#include"../Model/GeometricModel/Model3D/Model3D.hpp"

#include"../Model/FileManagement/Importer.hpp"
#include"../Model/FileManagement/Exporter.hpp"
#include"../Model/FileManagement/Format_OBJ/ImporterOBJ.hpp"
#include"../Model/FileManagement/Format_OBJ/ExporterOBJ.hpp"

using namespace std;

#ifndef CONTROLLER
#define CONTROLLER

#define enum_to_string(x) #x

/*************************************************************************
【类名】                 Controller
【功能】                 控制3D模型的管理和操作
【接口说明】             提供对3D模型的增删改查等操作接口
【开发者及日期】         周子睿 2024/8/12
【更改记录】             无
*************************************************************************/
class Controller {

public: 
    //--------------------------------------------------------------------
    // 内嵌枚举类，用于表示控制器操作的结果
    //--------------------------------------------------------------------
    enum class ControllerResult {
        UNSUPPORT_FORMAT,
        INVALID_FILE_NAME,
        INVALID_MODEL_NAME,
        CANNOT_OPEN_FILE,
        CANNOT_WIRITE_FILE,

        EXCESS_PARAMETERS,
        MISSING_PARAMETERS,
        INVALID_PARAMETERS,
        INVALID_INPUT_FORMAT,

        COINCIDENT_POINTS,
        COLINEAR_POINTS,

        INVALID_POINT_INDEX,
        INVALID_LINE_INDEX,
        INVALID_FACE_INDEX,

        DUPLICATE_LINE,
        DUPLICATE_FACE,

        UNSUPPORTED_OPERATION, 
        INTERNAL_ERROR, 
        UNKNOWN_ERROR,

        SUCCESS_CREATE,
        SUCCESS_IMPORT,
        SUCCESS_EXPORT,
        SUCCESS_SET,
        SUCCESS_GET,
        SUCCESS_ADD,
        SUCCESS_DELETE,
        SUCCESS_MODIFY
	};

    using RES = ControllerResult;

    //--------------------------------------------------------------------
    // 内嵌结构体，用于存储模型信息
    //--------------------------------------------------------------------
    struct ModelInfoInner {
        string ModelName;
        unsigned int uPointCount;
        unsigned int uLineCount;
        unsigned int uFaceCount;
        std::vector<unsigned int> PointSetIndex;
        std::vector<unsigned int> LineSetIndex;
        std::vector<unsigned int> FaceSetIndex;
        std::vector<std::array<double, 3>> PointSet;
        std::vector<std::array<unsigned int, 2>> LineSet;
        std::vector<std::array<unsigned int, 3>> FaceSet;
        std::vector<double> LineLengths;
        std::vector<double> FaceAreas;
        double rBoundingBoxVolume;
        double rTotalLineLength;
        double rTotalFaceArea;
    };

    //--------------------------------------------------------------------
    // 获取单例实例的静态方法
    //--------------------------------------------------------------------
    // 获取单例实例
    static Controller& GetInstance();

    //--------------------------------------------------------------------
    // 初始化单例的静态方法
    //--------------------------------------------------------------------
    // 初始化单例
    static void InitInstance();

    //--------------------------------------------------------------------
    // 自定义删除器
    //--------------------------------------------------------------------
    // 自定义删除器结构体
    struct Deleter {
        void operator()(Controller* AController) const { delete AController; }
    };

    //--------------------------------------------------------------------
    // 模型操作接口
    //--------------------------------------------------------------------
    // 打开OBJ格式模型文件
    RES OpenModelInOBJ(const std::string& FileName);
    // 保存模型到OBJ格式文件
    RES SaveModelToOBJ(const std::string& FileName) const;
    // 设置模型名称
    RES SetModelName(const std::string& NewName);
    // 获取模型名称
    RES GetModelName(ModelInfoInner& ModelInfo) const;

    // 获取模型信息
    RES GetModel(ModelInfoInner& ModelInfo) const;

    // 添加点
    RES AddPoint(const std::array<double, 3>& Coords);
    // 获取点集
    RES GetPointSet(ModelInfoInner& ModelInfo) const;

    // 获取线集
    RES GetLineSet(ModelInfoInner& ModelInfo) const;
    // 删除线
    RES DeleteLine(unsigned int uIndex);
    // 添加线（通过索引）
    RES AddLine(const std::array<unsigned int, 2>& Index);
    // 添加线（通过坐标）
    RES AddLine(const std::vector<std::array<double, 3>>& Coords);
    // 修改线
    RES ModifyLine(unsigned int uElementIndex, 
        unsigned int uPointIndex, 
        const std::array<double, 3>& Coords);
    // 获取线中的点
    RES GetPointsInLine(unsigned int uElementIndex, 
        ModelInfoInner& ModelInfo) const;

    // 获取面集
    RES GetFaceSet(ModelInfoInner& ModelInfo) const;
    // 删除面
    RES DeleteFace(unsigned int uIndex);
    // 添加面（通过索引）
    RES AddFace(const std::array<unsigned int, 3>& Index);
    // 添加面（通过坐标）
    RES AddFace(const std::vector<std::array<double, 3>>& Coords);
    // 修改面
    RES ModifyFace(unsigned int uElementIndex, 
        unsigned int uPointIndex, const std::array<double, 3>& Coords);
    // 获取面中的点
    RES GetPointsInFace(unsigned int uElementIndex, 
        ModelInfoInner& ModelInfo) const;

    //--------------------------------------------------------------------
    // 模型统计信息接口
    //--------------------------------------------------------------------
    // 获取点的数量
    RES GetPointCount(ModelInfoInner& ModelInfo) const;
    // 获取线的数量
    RES GetLineCount(ModelInfoInner& ModelInfo) const;
    // 获取面的数量
    RES GetFaceCount(ModelInfoInner& ModelInfo) const;
    // 获取总线长度
    RES GetTotalLineLength(ModelInfoInner& ModelInfo) const;
    // 获取总面面积
    RES GetTotalFaceArea(ModelInfoInner& ModelInfo) const;
    // 获取包围盒体积
    RES GetBoundingBoxVolume(ModelInfoInner& ModelInfo) const;

    //--------------------------------------------------------------------------
    //静态Getter数据成员
    //--------------------------------------------------------------------------
    //所有控制器公开成员函数返回值，对应的字符串
    static const std::string Res_Str[];

private:
    //--------------------------------------------------------------------
    // 构造、析构函数
    //--------------------------------------------------------------------
    // 默认构造函数
    Controller();
    // 默认析构函数
    virtual ~Controller() final = default;

    //--------------------------------------------------------------------
    // 删除拷贝构造函数和赋值运算符
    //--------------------------------------------------------------------
    // 删除拷贝构造函数
    Controller(const Controller& Source) = delete;
    // 删除赋值运算符
    Controller& operator=(const Controller& Source) = delete;

    //--------------------------------------------------------------------
    // 内部方法
    //--------------------------------------------------------------------
    // 获取初始化的模型
    static Model3D& GetInitializedModel();

    //--------------------------------------------------------------------
    // 成员变量
    //--------------------------------------------------------------------
    // 3D模型对象
    Model3D& m_Model;
    // 单例计数器
    static std::unique_ptr<Controller, Deleter> m_Instance;
    // 单例初始化标志
    static std::once_flag m_OnceFlag;
};

#endif