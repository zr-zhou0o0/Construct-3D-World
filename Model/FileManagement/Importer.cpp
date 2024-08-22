/*************************************************************************
���ļ�����                 Importer.cpp
������ģ���Ŀ�ġ�         ���������ඨ��
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <stdexcept>

#include "Importer.hpp"
#include "../GeometricModel/Model3D/Model3D.hpp"

/*************************************************************************
���������ơ�       Importer::Importer
���������ܡ�       ���캯������ʼ��Model3D����Ĺ���ָ��
����ڲ�����       std::shared_ptr<Model3D> Model3D - 3Dģ�Ͷ���Ĺ���ָ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Importer::Importer(std::shared_ptr<Model3D> Model3D): 
m_pModel3D(Model3D), FileManager(Model3D) {
    if (!m_pModel3D) {
        throw std::invalid_argument("Model3D pointer cannot be null");
    }
}

/*************************************************************************
���������ơ�       Importer::~Importer
���������ܡ�       ��������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Importer::~Importer() = default;

/*************************************************************************
���������ơ�       Importer::LoadFromFile
���������ܡ�       ���ļ�����ģ��
����ڲ�����       const std::string& FileName - �ļ�·��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool Importer::LoadFromFile(const std::string& FileName) {
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
���������ơ�       Importer::GetLoadedModel
���������ܡ�       ��ȡ���ص�ģ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::shared_ptr<Model3D> - 3Dģ�Ͷ���Ĺ���ָ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::shared_ptr<Model3D> Importer::GetLoadedModel() const {
    return m_pModel3D;
}

/*************************************************************************
���������ơ�       Importer::SetFilePath
���������ܡ�       �����ļ�·��
����ڲ�����       const std::string& FileName - �ļ�·��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool Importer::SetFilePath(const std::string& FileName) {
    if (FileName.empty()) {
        throw ExceptionInvalidFileName();
    }
    m_Path = FileName;
    return true;
}








