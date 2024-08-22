/*************************************************************************
【文件名】                 Controller.cpp
【功能模块和目的】         控制器类定义
【开发者及日期】           周子睿 2024/8/13
【更改记录】               无
*************************************************************************/

#include <stdexcept>
#include <memory>

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

#include "Controller.hpp"


// 静态成员变量定义
std::unique_ptr<Controller, Controller::Deleter> Controller::m_Instance 
= nullptr;
std::once_flag Controller::m_OnceFlag;

//所有控制器公开成员函数返回值，对应的字符串
const std::string Controller::Res_Str[]{
        enum_to_string(UNSUPPORT_FORMAT),
        enum_to_string(INVALID_FILE_NAME),
        enum_to_string(INVALID_MODEL_NAME),
        enum_to_string(CANNOT_OPEN_FILE),
        enum_to_string(CANNOT_WIRITE_FILE),

        enum_to_string(EXCESS_PARAMETERS),
        enum_to_string(MISSING_PARAMETERS),
        enum_to_string(INVALID_PARAMETERS),
        enum_to_string(INVALID_INPUT_FORMAT),

        enum_to_string(COINCIDENT_POINTS),
        enum_to_string(COLINEAR_POINTS),

        enum_to_string(INVALID_POINT_INDEX),
        enum_to_string(INVALID_LINE_INDEX),
        enum_to_string(INVALID_FACE_INDEX),

        enum_to_string(DUPLICATE_LINE),
        enum_to_string(DUPLICATE_FACE),

        enum_to_string(UNSUPPORTED_OPERATION),
        enum_to_string(INTERNAL_ERROR),
        enum_to_string(UNKNOWN_ERROR),

        enum_to_string(SUCCESS_CREATE),
        enum_to_string(SUCCESS_IMPORT),
        enum_to_string(SUCCESS_EXPORT),
        enum_to_string(SUCCESS_SET),
        enum_to_string(SUCCESS_GET),
        enum_to_string(SUCCESS_ADD),
        enum_to_string(SUCCESS_DELETE),
        enum_to_string(SUCCESS_MODIFY)
};

/*************************************************************************
【函数名称】       GetInitializedModel
【函数功能】       初始化并获取Model3D实例
【入口参数】       无
【出口参数】       无
【返回值】         Model3D& - 返回Model3D的实例引用
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Model3D& Controller::GetInitializedModel() {
    Model3D::InitInstance();
    return Model3D::GetInstance();
}

/*************************************************************************
【函数名称】       Controller
【函数功能】       Controller类的构造函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::Controller() : m_Model(GetInitializedModel()) {
}

/*************************************************************************
【函数名称】       GetInstance
【函数功能】       获取Controller类的单例实例
【入口参数】       无
【出口参数】       无
【返回值】         Controller& - 返回Controller的单例实例引用
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller& Controller::GetInstance() {
    if (!m_Instance) {
        InitInstance();
    }
    return *m_Instance;
}

/*************************************************************************
【函数名称】       InitInstance
【函数功能】       初始化Controller类的单例实例
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
void Controller::InitInstance() {
    std::call_once(m_OnceFlag, []() {
        m_Instance = std::unique_ptr<Controller, Controller::Deleter>
            (new Controller());
        });
}

/*************************************************************************
【函数名称】       OpenModelInOBJ
【函数功能】       打开OBJ格式的模型文件
【入口参数】       const std::string& FileName - 文件名
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::OpenModelInOBJ(const std::string& FileName) {
    try {
        ImporterOBJ AImporter(std::shared_ptr<Model3D>
            (&Model3D::GetInstance(), [](Model3D*) {}));
        AImporter.LoadFromFile(FileName);
    }
    catch (Importer::ExceptionInvalidFileName e) {
        return RES::INVALID_FILE_NAME;
    }
    catch (Importer::ExceptionInvalidExtension e) {
        return RES::UNSUPPORT_FORMAT;
    }
    catch (Importer::ExceptionFileOpenFailed e) {
        return RES::CANNOT_OPEN_FILE;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_IMPORT;
}

/*************************************************************************
【函数名称】       SaveModelToOBJ
【函数功能】       保存模型到OBJ格式文件
【入口参数】       const std::string& FileName - 文件名
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::SaveModelToOBJ(
    const std::string& FileName) const {
    try {
        ExporterOBJ AExporter(std::shared_ptr<Model3D>(
            &Model3D::GetInstance(), [](Model3D*) {}));
        AExporter.SaveToFile(FileName);
    }
    catch (Exporter::ExceptionInvalidFileName e) {
        return RES::INVALID_FILE_NAME;
    }
    catch (Exporter::ExceptionInvalidExtension e) {
        return RES::UNSUPPORT_FORMAT;
    }
    catch (Exporter::ExceptionFileOpenFailed e) {
        return RES::CANNOT_WIRITE_FILE;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_EXPORT;
}

/*************************************************************************
【函数名称】       SetModelName
【函数功能】       设置模型名称
【入口参数】       const std::string& NewName - 新的模型名称
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::SetModelName(const std::string& NewName) {
    try {
        m_Model.SetModelName(NewName);
    }
    catch (Model3D::ExceptionInvalidName e) {
        return RES::INVALID_MODEL_NAME;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_SET;
}

/*************************************************************************
【函数名称】       GetModelName
【函数功能】       获取模型名称
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型名称
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetModelName(ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.ModelName = m_Model.GetModelName();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       GetModel
【函数功能】       获取模型的详细信息
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型全部信息
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetModel(ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.ModelName = m_Model.GetModelName();
        ModelInfo.uPointCount = m_Model.GetPointCount();
        ModelInfo.uLineCount = m_Model.GetLineCount();
        ModelInfo.uFaceCount = m_Model.GetFaceCount();
        ModelInfo.PointSetIndex = m_Model.GetPointSetIndex();
        ModelInfo.LineSetIndex = m_Model.GetLineSetIndex();
        ModelInfo.FaceSetIndex = m_Model.GetFaceSetIndex();

        ModelInfo.PointSet = m_Model.GetPointSet();
        ModelInfo.LineSet = m_Model.GetLines();
        ModelInfo.FaceSet = m_Model.GetFaces();

        ModelInfo.LineLengths = m_Model.GetLineLegnths();
        ModelInfo.FaceAreas = m_Model.GetFaceAreas();

        ModelInfo.rBoundingBoxVolume = m_Model.GetBoundingBoxVolume();
        ModelInfo.rTotalLineLength = m_Model.GetTotalLineLength();
        ModelInfo.rTotalFaceArea = m_Model.GetTotalFaceArea();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       AddPoint
【函数功能】       添加点到模型
【入口参数】       const std::array<double, 3>& Coords - 点的坐标
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::AddPoint(
    const std::array<double, 3>& Coords) {
    try {
        m_Model.AddPoint(Coords);
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_ADD;
}

/*************************************************************************
【函数名称】       GetPointSet
【函数功能】       获取模型中的点集
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型点集
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetPointSet(ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.PointSet = m_Model.GetPointSet();
        ModelInfo.PointSetIndex = m_Model.GetPointSetIndex();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       GetLineSet
【函数功能】       获取模型中的线集
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型线集
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetLineSet(ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.LineSet = m_Model.GetLines();
        ModelInfo.LineSetIndex = m_Model.GetLineSetIndex();
        ModelInfo.LineLengths = m_Model.GetLineLegnths();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       DeleteLine
【函数功能】       删除模型中的线
【入口参数】       const unsigned int Index - 线的索引
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::DeleteLine(const unsigned int uIndex) {
    try {
        m_Model.DeleteLine(uIndex);
    }
    catch (const ElementSet<2>::ExceptionInvalidIndex e) {
        return RES::INVALID_LINE_INDEX;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_DELETE;
}

/*************************************************************************
【函数名称】       AddLine
【函数功能】       添加线到模型
【入口参数】       const std::array<unsigned int, 2>& Index - 线的索引数组
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::AddLine(
    const std::array<unsigned int, 2>& Index) {
    try {
        m_Model.AddLine(Index);
    }
    catch (ElementSet<2>::ExceptionCoincidentPoints  e) {
        return RES::COINCIDENT_POINTS;
    }
    catch (ElementSet<2>::ExceptionMissingParams  e) {
        return RES::MISSING_PARAMETERS;
    }
    catch (ElementSet<2>::ExceptionExcessParams  e) {
        return RES::EXCESS_PARAMETERS;
    }
    catch (PointSet::ExceptionInvalidIndex e) {
        return RES::INVALID_POINT_INDEX;
    }
    catch (LineSet::ExceptionDuplicateLine e) {
        return RES::DUPLICATE_LINE;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_ADD;
}

/*************************************************************************
【函数名称】       AddLine
【函数功能】       添加线到模型
【入口参数】       const std::vector<std::array<double, 3>>& Coords 
                    线的坐标数组
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::AddLine(
    const std::vector<std::array<double, 3>>& Coords) {
    try {
        m_Model.AddLine(Coords);
    }
    catch (ElementSet<2>::ExceptionCoincidentPoints  e) {
        return RES::COINCIDENT_POINTS;
    }
    catch (ElementSet<2>::ExceptionMissingParams  e) {
        return RES::MISSING_PARAMETERS;
    }
    catch (ElementSet<2>::ExceptionExcessParams  e) {
        return RES::EXCESS_PARAMETERS;
    }
    catch (PointSet::ExceptionInvalidIndex e) {
        return RES::INVALID_POINT_INDEX;
    }
    catch (LineSet::ExceptionDuplicateLine e) {
        return RES::DUPLICATE_LINE;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_ADD;
}

/*************************************************************************
【函数名称】       ModifyLine
【函数功能】       修改模型中的线
【入口参数】       const unsigned int iElementIndex - 线的索引
                   const unsigned int iPointIndex - 点的索引
                   const std::array<double, 3>& Coords - 新的坐标
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::ModifyLine(const unsigned int uElementIndex, 
    const unsigned int uPointIndex, 
    const std::array<double, 3>& Coords) {
    try {
        m_Model.ModifyLine(uElementIndex, uPointIndex, Coords);
    }
    catch (ElementSet<2>::ExceptionCoincidentPoints  e) {
        return RES::COINCIDENT_POINTS;
    }
    catch (ElementSet<2>::ExceptionInvalidIndex e) {
        return RES::INVALID_POINT_INDEX;
    }
    catch (LineSet::ExceptionDuplicateLine e) {
        return RES::DUPLICATE_LINE;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_MODIFY;
}

/*************************************************************************
【函数名称】       GetPointsInLine
【函数功能】       获取线上的点
【入口参数】       const unsigned int iElementIndex - 线的索引
                   ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型点集和索引
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetPointsInLine(const unsigned int uElementIndex,
    ModelInfoInner& ModelInfo) const {
    try {
        std::array<unsigned int, 2> PointIndex = m_Model.GetLine(
            uElementIndex)[0];
        std::array<double, 3> Point1 = m_Model.GetCoordsByIndex(
            PointIndex[0]);
        std::array<double, 3> Point2 = m_Model.GetCoordsByIndex(
            PointIndex[1]);
        std::vector<std::array<double, 3>> Points = { Point1, Point2 };
        ModelInfo.PointSetIndex = { PointIndex[0], PointIndex[1] };
        ModelInfo.PointSet = Points;
    }
    catch (PointSet::ExceptionInvalidIndex e) {
        return RES::INVALID_POINT_INDEX;
    }
    catch (ElementSet<2>::ExceptionInvalidIndex  e) {
        return RES::INVALID_LINE_INDEX;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       GetFaceSet
【函数功能】       获取模型中的面集
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型面集
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetFaceSet(ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.FaceSet = m_Model.GetFaces();
        ModelInfo.FaceSetIndex = m_Model.GetFaceSetIndex();
        ModelInfo.FaceAreas = m_Model.GetFaceAreas();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       DeleteFace
【函数功能】       删除模型中的面
【入口参数】       const unsigned int Index - 面的索引
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::DeleteFace(const unsigned int uIndex) {
    try {
        m_Model.DeleteFace(uIndex);
    }
    catch (const ElementSet<3>::ExceptionInvalidIndex  e) {
        return RES::INVALID_FACE_INDEX;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_DELETE;
}

/*************************************************************************
【函数名称】       AddFace
【函数功能】       添加面到模型
【入口参数】       const std::array<unsigned int, 3>& Index - 面的索引数组
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::AddFace(
    const std::array<unsigned int, 3>& Index) {
    try {
        m_Model.AddFace(Index);
    }
    catch (Face::ExceptionCollinearPoints e) {
        return RES::COLINEAR_POINTS;
    }
    catch (ElementSet<3>::ExceptionCoincidentPoints  e) {
        return RES::COINCIDENT_POINTS;
    }
    catch (ElementSet<3>::ExceptionMissingParams  e) {
        return RES::MISSING_PARAMETERS;
    }
    catch (ElementSet<3>::ExceptionExcessParams  e) {
        return RES::EXCESS_PARAMETERS;
    }
    catch (PointSet::ExceptionInvalidIndex e) {
        return RES::INVALID_POINT_INDEX;
    }
    catch (FaceSet::ExceptionDuplicateFace e) {
        return RES::DUPLICATE_FACE;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_ADD;
}

/*************************************************************************
【函数名称】       AddFace
【函数功能】       添加面到模型
【入口参数】       const std::vector<std::array<double, 3>>& Coords 
                    面的坐标数组
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::AddFace(
    const std::vector<std::array<double, 3>>& Coords) {
    try {
        m_Model.AddFace(Coords);
    }
    catch (Face::ExceptionCollinearPoints e) {
        return RES::COLINEAR_POINTS;
    }
    catch (ElementSet<3>::ExceptionCoincidentPoints  e) {
        return RES::COINCIDENT_POINTS;
    }
    catch (ElementSet<3>::ExceptionMissingParams  e) {
        return RES::MISSING_PARAMETERS;
    }
    catch (ElementSet<3>::ExceptionExcessParams  e) {
        return RES::EXCESS_PARAMETERS;
    }
    catch (PointSet::ExceptionInvalidIndex e) {
        return RES::INVALID_POINT_INDEX;
    }
    catch (FaceSet::ExceptionDuplicateFace e) {
        return RES::DUPLICATE_FACE;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_ADD;
}

/*************************************************************************
【函数名称】       ModifyFace
【函数功能】       修改模型中的面
【入口参数】       const unsigned int iElementIndex - 面的索引
                   const unsigned int iPointIndex - 点的索引
                   const std::array<double, 3>& Coords - 新的坐标
【出口参数】       无
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::ModifyFace(const unsigned int uElementIndex, 
    const unsigned int uPointIndex, 
    const std::array<double, 3>& Coords) {
    try {
        m_Model.ModifyFace(uElementIndex, uPointIndex, Coords);
    }
    catch (Face::ExceptionCollinearPoints e) {
        return RES::COLINEAR_POINTS;
    }
    catch (ElementSet<3>::ExceptionCoincidentPoints  e) {
        return RES::COINCIDENT_POINTS;
    }
    catch (ElementSet<3>::ExceptionInvalidIndex  e) {
        return RES::INVALID_POINT_INDEX;
    }
    catch (FaceSet::ExceptionDuplicateFace e) {
        return RES::DUPLICATE_FACE;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_MODIFY;
}

/*************************************************************************
【函数名称】       GetPointsInFace
【函数功能】       获取面上的点
【入口参数】       const unsigned int iElementIndex - 面的索引
                   ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型面集和索引
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetPointsInFace(const unsigned int uElementIndex,
    ModelInfoInner& ModelInfo) const {
    try {
        std::array<unsigned int, 3> PointIndex = m_Model.GetFace(
            uElementIndex)[0];
        std::array<double, 3> Point1 = m_Model.GetCoordsByIndex(
            PointIndex[0]);
        std::array<double, 3> Point2 = m_Model.GetCoordsByIndex(
            PointIndex[1]);
        std::array<double, 3> Point3 = m_Model.GetCoordsByIndex(
            PointIndex[2]);
        std::vector<std::array<double, 3>> Points 
            = { Point1, Point2, Point3 };
        ModelInfo.PointSetIndex 
            = { PointIndex[0], PointIndex[1], PointIndex[2] };
        ModelInfo.PointSet = Points;
    }
    catch (PointSet::ExceptionInvalidIndex e) {
        return RES::INVALID_POINT_INDEX;
    }
    catch (ElementSet<3>::ExceptionInvalidIndex  e) {
        return RES::INVALID_FACE_INDEX;
    }
    catch (const std::invalid_argument e) {
        return RES::INVALID_INPUT_FORMAT;
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       GetPointCount
【函数功能】       获取模型中的点数
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型点个数
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetPointCount(ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.uPointCount = m_Model.GetPointCount();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       GetLineCount
【函数功能】       获取模型中的线数
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型线数
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetLineCount(ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.uLineCount = m_Model.GetLineCount();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       GetFaceCount
【函数功能】       获取模型中的面数
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型面数
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetFaceCount(ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.uFaceCount = m_Model.GetFaceCount();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       GetTotalLineLength
【函数功能】       获取模型中所有线的总长度
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型所有线总长度
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetTotalLineLength(
    ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.rTotalLineLength = m_Model.GetTotalLineLength();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       GetTotalFaceArea
【函数功能】       获取模型中所有面的总面积
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型总面积
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetTotalFaceArea(
    ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.rTotalFaceArea = m_Model.GetTotalFaceArea();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}

/*************************************************************************
【函数名称】       GetBoundingBoxVolume
【函数功能】       获取模型的包围盒体积
【入口参数】       ModelInfoInner& ModelInfo - 模型信息结构体
【出口参数】       ModelInfoInner& ModelInfo - 模型包围盒体积
【返回值】         RES - 返回操作结果
【开发者及日期】   周子睿 2024/8/13
【更改记录】       无
*************************************************************************/
Controller::RES Controller::GetBoundingBoxVolume(
    ModelInfoInner& ModelInfo) const {
    try {
        ModelInfo.rBoundingBoxVolume = m_Model.GetBoundingBoxVolume();
    }
    catch (const std::exception e) {
        return RES::UNKNOWN_ERROR;
    }
    return RES::SUCCESS_GET;
}



