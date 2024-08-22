/*************************************************************************
���ļ�����                 Exporter.cpp
������ģ���Ŀ�ġ�         ���������ඨ��
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <stdexcept>
#include "Exporter.hpp"
#include "../GeometricModel/Model3D/Model3D.hpp"

/*************************************************************************
���������ơ�       Exporter::Exporter
���������ܡ�       ���캯������ʼ��Model3D����Ĺ���ָ��
����ڲ�����       std::shared_ptr<Model3D> Model3D - 3Dģ�Ͷ���Ĺ���ָ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Exporter::Exporter(std::shared_ptr<Model3D> Model3D) : 
m_pModel3D(Model3D), FileManager(Model3D) {
    if (!m_pModel3D) {
        throw std::invalid_argument("Model3D pointer cannot be null");
    }
}

/*************************************************************************
���������ơ�       Exporter::~Exporter
���������ܡ�       ��������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Exporter::~Exporter() = default;

/*************************************************************************
���������ơ�       Exporter::SaveToFile
���������ܡ�       ��ģ�ͱ��浽�ļ�
����ڲ�����       const std::string& FileName - �ļ�·��
                   const std::string& Comment - �ļ�ע��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool Exporter::SaveToFile(
    const std::string& FileName, const std::string& Comment) {
    if (!SetFilePath(FileName)) {
        return false;
    }

    if (!CheckExtension()) {
        return false;
    }

    if (!CheckOpen()) {
        return false;
    }

    return SaveFromModel(m_Path, Comment);
}

/*************************************************************************
���������ơ�       Exporter::GetModelToExport
���������ܡ�       ��ȡҪ������ģ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::shared_ptr<Model3D> - 3Dģ�Ͷ���Ĺ���ָ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::shared_ptr<Model3D> Exporter::GetModelToExport() const {
    return m_pModel3D;
}

/*************************************************************************
���������ơ�       Exporter::SetFilePath
���������ܡ�       �����ļ�·��
����ڲ�����       const std::string& FileName - �ļ�·��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool Exporter::SetFilePath(const std::string& FileName) {
    if (FileName.empty()) {
        return false;
    }
    m_Path = FileName;
    return true;
}





