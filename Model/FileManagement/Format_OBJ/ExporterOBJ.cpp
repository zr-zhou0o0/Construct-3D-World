/*************************************************************************
���ļ�����                 ExporterOBJ.cpp
������ģ���Ŀ�ġ�         OBJ����������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ExporterOBJ.hpp"
#include "../Exporter.hpp"
#include "../../GeometricModel/Model3D/Model3D.hpp"

/*************************************************************************
���������ơ�       ExporterOBJ::ExporterOBJ
���������ܡ�       ���캯������ʼ��Model3D����Ĺ���ָ��
����ڲ�����       std::shared_ptr<Model3D> Model3D - 3Dģ�Ͷ���Ĺ���ָ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
ExporterOBJ::ExporterOBJ(std::shared_ptr<Model3D> Model3D) : 
Exporter(Model3D), m_pModel3D(Model3D) {
}

/*************************************************************************
���������ơ�       ExporterOBJ::~ExporterOBJ
���������ܡ�       ��������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
ExporterOBJ::~ExporterOBJ() = default;

/*************************************************************************
���������ơ�       ExporterOBJ::SaveToFile
���������ܡ�       ��ģ�ͱ��浽�ļ�
����ڲ�����       const std::string& FileName - �ļ�·��
                   const std::string& Comment - ע�ͣ���ѡ��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool ExporterOBJ::SaveToFile(
    const std::string& FileName, const std::string& Comment) {
    if (!SetFilePath(FileName)) {
        throw ExceptionInvalidFileName();
    }

    if (!CheckExtension()) {
        throw ExceptionInvalidExtension();
    }

    if (!CheckOpen()) {
        throw ExceptionFileOpenFailed();
    }

    return SaveFromModel(m_Path, Comment);
}

/*************************************************************************
���������ơ�       ExporterOBJ::GetModelToExport
���������ܡ�       ��ȡҪ������ģ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::shared_ptr<Model3D> - 3Dģ�Ͷ���Ĺ���ָ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::shared_ptr<Model3D> ExporterOBJ::GetModelToExport() const {
    return m_pModel3D;
}

/*************************************************************************
���������ơ�       ExporterOBJ::SetFilePath
���������ܡ�       �����ļ�·��
����ڲ�����       const std::string& FileName - �ļ�·��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool ExporterOBJ::SetFilePath(const std::string& FileName) {
    if (FileName.empty()) {
        throw ExceptionInvalidFileName();
    }
    m_Path = FileName;
    return true;
}

/*************************************************************************
���������ơ�       ExporterOBJ::CheckExtension
���������ܡ�       ����ļ���չ���Ƿ�ΪOBJ
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         bool - ��չ���Ƿ���Ч
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool ExporterOBJ::CheckExtension() const {
    size_t DotPosition = m_Path.find_last_of('.');
    if (DotPosition == std::string::npos) {
        throw ExceptionInvalidExtension();
    }
    std::string Extension = m_Path.substr(DotPosition + 1);
    return (Extension == "obj" || Extension == "OBJ");
}

/*************************************************************************
���������ơ�       ExporterOBJ::CheckOpen
���������ܡ�       ����ļ��Ƿ��ܴ�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         bool - �ļ��Ƿ��ܴ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool ExporterOBJ::CheckOpen() const {
    std::ofstream File(m_Path);
    return File.good();
}

/*************************************************************************
���������ơ�       ExporterOBJ::SaveFromModel
���������ܡ�       ��Model3D���󱣴�ģ�͵��ļ�
����ڲ�����       const std::string& FilePath - �ļ�·��
                   const std::string& Comment - ע�ͣ���ѡ��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool ExporterOBJ::SaveFromModel(
    const std::string& FilePath, const std::string& Comment) {
    std::ofstream File(FilePath);
    if (!File.is_open()) {
        throw ExceptionFileOpenFailed();
        return false;
    }

    const auto& Points = m_pModel3D->GetPointSet();
    const auto& Lines = m_pModel3D->GetLines();
    const auto& Faces = m_pModel3D->GetFaces();

    if (!Comment.empty()) {
        File << "# " << Comment << "\n";
    }

    File << "g " << m_pModel3D->GetModelName() << "\n";

    for (const auto& APoint : Points) {
        File << "v " 
             << APoint[0] << " " 
             << APoint[1] << " " 
             << APoint[2] << "\n";
    }

    for (const auto& ALine : Lines) {
        File << "l " << (ALine[0] + 1) << " " << (ALine[1] + 1) << "\n";
    }

    for (const auto& AFace : Faces) {
        File << "f " 
            << (AFace[0] + 1) << " " 
            << (AFace[1] + 1) << " " 
            << (AFace[2] + 1) << "\n";
    }

    return true;
}





