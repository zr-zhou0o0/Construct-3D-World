/*************************************************************************
���ļ�����                 Controller.cpp
������ģ���Ŀ�ġ�         ������������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
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
��������                 Controller
�����ܡ�                 ����3Dģ�͵Ĺ���Ͳ���
���ӿ�˵����             �ṩ��3Dģ�͵���ɾ�Ĳ�Ȳ����ӿ�
�������߼����ڡ�         ����� 2024/8/12
�����ļ�¼��             ��
*************************************************************************/
class Controller {

public: 
    //--------------------------------------------------------------------
    // ��Ƕö���࣬���ڱ�ʾ�����������Ľ��
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
    // ��Ƕ�ṹ�壬���ڴ洢ģ����Ϣ
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
    // ��ȡ����ʵ���ľ�̬����
    //--------------------------------------------------------------------
    // ��ȡ����ʵ��
    static Controller& GetInstance();

    //--------------------------------------------------------------------
    // ��ʼ�������ľ�̬����
    //--------------------------------------------------------------------
    // ��ʼ������
    static void InitInstance();

    //--------------------------------------------------------------------
    // �Զ���ɾ����
    //--------------------------------------------------------------------
    // �Զ���ɾ�����ṹ��
    struct Deleter {
        void operator()(Controller* AController) const { delete AController; }
    };

    //--------------------------------------------------------------------
    // ģ�Ͳ����ӿ�
    //--------------------------------------------------------------------
    // ��OBJ��ʽģ���ļ�
    RES OpenModelInOBJ(const std::string& FileName);
    // ����ģ�͵�OBJ��ʽ�ļ�
    RES SaveModelToOBJ(const std::string& FileName) const;
    // ����ģ������
    RES SetModelName(const std::string& NewName);
    // ��ȡģ������
    RES GetModelName(ModelInfoInner& ModelInfo) const;

    // ��ȡģ����Ϣ
    RES GetModel(ModelInfoInner& ModelInfo) const;

    // ��ӵ�
    RES AddPoint(const std::array<double, 3>& Coords);
    // ��ȡ�㼯
    RES GetPointSet(ModelInfoInner& ModelInfo) const;

    // ��ȡ�߼�
    RES GetLineSet(ModelInfoInner& ModelInfo) const;
    // ɾ����
    RES DeleteLine(unsigned int uIndex);
    // ����ߣ�ͨ��������
    RES AddLine(const std::array<unsigned int, 2>& Index);
    // ����ߣ�ͨ�����꣩
    RES AddLine(const std::vector<std::array<double, 3>>& Coords);
    // �޸���
    RES ModifyLine(unsigned int uElementIndex, 
        unsigned int uPointIndex, 
        const std::array<double, 3>& Coords);
    // ��ȡ���еĵ�
    RES GetPointsInLine(unsigned int uElementIndex, 
        ModelInfoInner& ModelInfo) const;

    // ��ȡ�漯
    RES GetFaceSet(ModelInfoInner& ModelInfo) const;
    // ɾ����
    RES DeleteFace(unsigned int uIndex);
    // ����棨ͨ��������
    RES AddFace(const std::array<unsigned int, 3>& Index);
    // ����棨ͨ�����꣩
    RES AddFace(const std::vector<std::array<double, 3>>& Coords);
    // �޸���
    RES ModifyFace(unsigned int uElementIndex, 
        unsigned int uPointIndex, const std::array<double, 3>& Coords);
    // ��ȡ���еĵ�
    RES GetPointsInFace(unsigned int uElementIndex, 
        ModelInfoInner& ModelInfo) const;

    //--------------------------------------------------------------------
    // ģ��ͳ����Ϣ�ӿ�
    //--------------------------------------------------------------------
    // ��ȡ�������
    RES GetPointCount(ModelInfoInner& ModelInfo) const;
    // ��ȡ�ߵ�����
    RES GetLineCount(ModelInfoInner& ModelInfo) const;
    // ��ȡ�������
    RES GetFaceCount(ModelInfoInner& ModelInfo) const;
    // ��ȡ���߳���
    RES GetTotalLineLength(ModelInfoInner& ModelInfo) const;
    // ��ȡ�������
    RES GetTotalFaceArea(ModelInfoInner& ModelInfo) const;
    // ��ȡ��Χ�����
    RES GetBoundingBoxVolume(ModelInfoInner& ModelInfo) const;

    //--------------------------------------------------------------------------
    //��̬Getter���ݳ�Ա
    //--------------------------------------------------------------------------
    //���п�����������Ա��������ֵ����Ӧ���ַ���
    static const std::string Res_Str[];

private:
    //--------------------------------------------------------------------
    // ���졢��������
    //--------------------------------------------------------------------
    // Ĭ�Ϲ��캯��
    Controller();
    // Ĭ����������
    virtual ~Controller() final = default;

    //--------------------------------------------------------------------
    // ɾ���������캯���͸�ֵ�����
    //--------------------------------------------------------------------
    // ɾ���������캯��
    Controller(const Controller& Source) = delete;
    // ɾ����ֵ�����
    Controller& operator=(const Controller& Source) = delete;

    //--------------------------------------------------------------------
    // �ڲ�����
    //--------------------------------------------------------------------
    // ��ȡ��ʼ����ģ��
    static Model3D& GetInitializedModel();

    //--------------------------------------------------------------------
    // ��Ա����
    //--------------------------------------------------------------------
    // 3Dģ�Ͷ���
    Model3D& m_Model;
    // ����������
    static std::unique_ptr<Controller, Deleter> m_Instance;
    // ������ʼ����־
    static std::once_flag m_OnceFlag;
};

#endif