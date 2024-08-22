/*************************************************************************
���ļ�����                 ImporterOBJ.cpp
������ģ���Ŀ�ġ�         OBJ����������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "ImporterOBJ.hpp"
#include "../../GeometricModel/Model3D/Model3D.hpp"

/*************************************************************************
���������ơ�       ImporterOBJ::ImporterOBJ
���������ܡ�       ���캯������ʼ��Model3D����Ĺ���ָ��
����ڲ�����       std::shared_ptr<Model3D> Model3D - 3Dģ�Ͷ���Ĺ���ָ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
ImporterOBJ::ImporterOBJ(std::shared_ptr<Model3D> Model3D) :
Importer(Model3D), m_pModel3D(Model3D) {
}

/*************************************************************************
���������ơ�       ImporterOBJ::~ImporterOBJ
���������ܡ�       ��������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
ImporterOBJ::~ImporterOBJ() = default;

/*************************************************************************
���������ơ�       ImporterOBJ::LoadFromFile
���������ܡ�       ���ļ�����ģ��
����ڲ�����       const std::string& FileName - �ļ�·��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool ImporterOBJ::LoadFromFile(const std::string& FileName) {
    m_pModel3D->ClearModel();

    if (!SetFilePath(FileName)) {
        throw ExceptionInvalidFileName();
    }

    if (!CheckExtension()) {
        throw ExceptionInvalidExtension();
    }

    if (!CheckOpen()) {
        throw ExceptionFileOpenFailed();
    }

    return LoadToModel(m_Path);
}

/*************************************************************************
���������ơ�       ImporterOBJ::GetLoadedModel
���������ܡ�       ��ȡ���ص�ģ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::shared_ptr<Model3D> - 3Dģ�Ͷ���Ĺ���ָ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::shared_ptr<Model3D> ImporterOBJ::GetLoadedModel() const {
    return m_pModel3D;
}

/*************************************************************************
���������ơ�       ImporterOBJ::SetFilePath
���������ܡ�       �����ļ�·��
����ڲ�����       const std::string& FileName - �ļ�·��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool ImporterOBJ::SetFilePath(const std::string& FileName) {
    if (FileName.empty()) {
        throw ExceptionInvalidFileName();
    }
    m_Path = FileName;
    return true;
}

/*************************************************************************
���������ơ�       ImporterOBJ::CheckExtension
���������ܡ�       ����ļ���չ���Ƿ�ΪOBJ
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         bool - ��չ���Ƿ���Ч
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool ImporterOBJ::CheckExtension() const {
    size_t DotPosition = m_Path.find_last_of('.');
    if (DotPosition == std::string::npos) {
        throw ExceptionInvalidExtension();
    }
    std::string Extension = m_Path.substr(DotPosition + 1);
    return (Extension == "obj" || Extension == "OBJ");
}

/*************************************************************************
���������ơ�       ImporterOBJ::CheckOpen
���������ܡ�       ����ļ��Ƿ��ܴ�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         bool - �ļ��Ƿ��ܴ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool ImporterOBJ::CheckOpen() const {
    std::ifstream File(m_Path);
    return File.is_open();
}

/*************************************************************************
���������ơ�       ImporterOBJ::LoadToModel
���������ܡ�       ����ģ�͵�Model3D����
����ڲ�����       const std::string& FilePath - �ļ�·��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool ImporterOBJ::LoadToModel(const std::string& FilePath) {
    std::ifstream File(FilePath);
    if (!File.is_open()) {
        throw ExceptionFileOpenFailed();
    }

    std::string ALine;
    while (std::getline(File, ALine)) {
        std::istringstream Stream(ALine);
        char cTag;

        if (!(Stream >> cTag)) {
            continue;  // ����
        }

        switch (cTag) {
        case '#':
            // ����ע��
            break;
        case 'g':
        {
            std::string Name;
            std::getline(Stream >> std::ws, Name);  // ��ȡʣ�������Ϊ����
            m_pModel3D->SetModelName(Name);
            break;
        }
        case 'v':
        {
            double rX, rY, rZ;
            if (Stream >> rX >> rY >> rZ) {
                m_pModel3D->AddPoint({ rX, rY, rZ });
            }
            break;
        }
        case 'l':
        {
            unsigned int uIndex1, uIndex2;
            if (Stream >> uIndex1 >> uIndex2) {
                m_pModel3D->AddLine({ uIndex1 - 1, uIndex2 - 1 });
            }
            break;
        }
        case 'f':
        {
            unsigned int uIndex1, uIndex2, uIndex3;
            if (Stream >> uIndex1 >> uIndex2 >> uIndex3) {
                m_pModel3D->AddFace(
                    { uIndex1 - 1, uIndex2 - 1, uIndex3 - 1 });
            }
            break;
        }
        default :
            // ����δ֪��ǩ
            break;
        }
    }

    return true;
}











