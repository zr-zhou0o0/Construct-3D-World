/*************************************************************************
���ļ�����                 Controller.cpp
������ģ���Ŀ�ġ�         �������ඨ��
�������߼����ڡ�           ����� 2024/8/13
�����ļ�¼��               ��
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


// ��̬��Ա��������
std::unique_ptr<Controller, Controller::Deleter> Controller::m_Instance 
= nullptr;
std::once_flag Controller::m_OnceFlag;

//���п�����������Ա��������ֵ����Ӧ���ַ���
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
���������ơ�       GetInitializedModel
���������ܡ�       ��ʼ������ȡModel3Dʵ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         Model3D& - ����Model3D��ʵ������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
Model3D& Controller::GetInitializedModel() {
    Model3D::InitInstance();
    return Model3D::GetInstance();
}

/*************************************************************************
���������ơ�       Controller
���������ܡ�       Controller��Ĺ��캯��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
Controller::Controller() : m_Model(GetInitializedModel()) {
}

/*************************************************************************
���������ơ�       GetInstance
���������ܡ�       ��ȡController��ĵ���ʵ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         Controller& - ����Controller�ĵ���ʵ������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
Controller& Controller::GetInstance() {
    if (!m_Instance) {
        InitInstance();
    }
    return *m_Instance;
}

/*************************************************************************
���������ơ�       InitInstance
���������ܡ�       ��ʼ��Controller��ĵ���ʵ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
*************************************************************************/
void Controller::InitInstance() {
    std::call_once(m_OnceFlag, []() {
        m_Instance = std::unique_ptr<Controller, Controller::Deleter>
            (new Controller());
        });
}

/*************************************************************************
���������ơ�       OpenModelInOBJ
���������ܡ�       ��OBJ��ʽ��ģ���ļ�
����ڲ�����       const std::string& FileName - �ļ���
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       SaveModelToOBJ
���������ܡ�       ����ģ�͵�OBJ��ʽ�ļ�
����ڲ�����       const std::string& FileName - �ļ���
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       SetModelName
���������ܡ�       ����ģ������
����ڲ�����       const std::string& NewName - �µ�ģ������
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetModelName
���������ܡ�       ��ȡģ������
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ������
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetModel
���������ܡ�       ��ȡģ�͵���ϸ��Ϣ
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ��ȫ����Ϣ
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       AddPoint
���������ܡ�       ��ӵ㵽ģ��
����ڲ�����       const std::array<double, 3>& Coords - �������
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetPointSet
���������ܡ�       ��ȡģ���еĵ㼯
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ�͵㼯
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetLineSet
���������ܡ�       ��ȡģ���е��߼�
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ���߼�
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       DeleteLine
���������ܡ�       ɾ��ģ���е���
����ڲ�����       const unsigned int Index - �ߵ�����
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       AddLine
���������ܡ�       ����ߵ�ģ��
����ڲ�����       const std::array<unsigned int, 2>& Index - �ߵ���������
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       AddLine
���������ܡ�       ����ߵ�ģ��
����ڲ�����       const std::vector<std::array<double, 3>>& Coords 
                    �ߵ���������
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       ModifyLine
���������ܡ�       �޸�ģ���е���
����ڲ�����       const unsigned int iElementIndex - �ߵ�����
                   const unsigned int iPointIndex - �������
                   const std::array<double, 3>& Coords - �µ�����
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetPointsInLine
���������ܡ�       ��ȡ���ϵĵ�
����ڲ�����       const unsigned int iElementIndex - �ߵ�����
                   ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ�͵㼯������
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetFaceSet
���������ܡ�       ��ȡģ���е��漯
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ���漯
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       DeleteFace
���������ܡ�       ɾ��ģ���е���
����ڲ�����       const unsigned int Index - �������
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       AddFace
���������ܡ�       ����浽ģ��
����ڲ�����       const std::array<unsigned int, 3>& Index - �����������
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       AddFace
���������ܡ�       ����浽ģ��
����ڲ�����       const std::vector<std::array<double, 3>>& Coords 
                    �����������
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       ModifyFace
���������ܡ�       �޸�ģ���е���
����ڲ�����       const unsigned int iElementIndex - �������
                   const unsigned int iPointIndex - �������
                   const std::array<double, 3>& Coords - �µ�����
�����ڲ�����       ��
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetPointsInFace
���������ܡ�       ��ȡ���ϵĵ�
����ڲ�����       const unsigned int iElementIndex - �������
                   ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ���漯������
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetPointCount
���������ܡ�       ��ȡģ���еĵ���
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ�͵����
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetLineCount
���������ܡ�       ��ȡģ���е�����
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ������
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetFaceCount
���������ܡ�       ��ȡģ���е�����
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ������
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetTotalLineLength
���������ܡ�       ��ȡģ���������ߵ��ܳ���
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ���������ܳ���
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetTotalFaceArea
���������ܡ�       ��ȡģ����������������
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ�������
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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
���������ơ�       GetBoundingBoxVolume
���������ܡ�       ��ȡģ�͵İ�Χ�����
����ڲ�����       ModelInfoInner& ModelInfo - ģ����Ϣ�ṹ��
�����ڲ�����       ModelInfoInner& ModelInfo - ģ�Ͱ�Χ�����
������ֵ��         RES - ���ز������
�������߼����ڡ�   ����� 2024/8/13
�����ļ�¼��       ��
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



