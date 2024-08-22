/*************************************************************************
���ļ�����                 FileManager.cpp
������ģ���Ŀ�ġ�         �ļ����������ඨ��
�������߼����ڡ�           ����� 2024/8/13
�����ļ�¼��               ��
*************************************************************************/

#include "FileManager.hpp"
#include <stdexcept>

/*************************************************************************
���������ơ�       FileManager::FileManager
���������ܡ�       ���캯������ʼ��Model3D����Ĺ���ָ��
����ڲ�����       std::shared_ptr<Model3D> Model3D - 3Dģ�Ͷ���Ĺ���ָ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
FileManager::FileManager(std::shared_ptr<Model3D> Model3D) : 
m_pModel3D(Model3D) {
    if (!m_pModel3D) {
        throw std::invalid_argument("Model3D pointer cannot be null");
    }
}

/*************************************************************************
���������ơ�       FileManager::~FileManager
���������ܡ�       ��������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
FileManager::~FileManager() = default;

/*************************************************************************
���������ơ�       FileManager::GetModel
���������ܡ�       ��ȡModel3D����Ĺ���ָ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::shared_ptr<Model3D> - 3Dģ�Ͷ���Ĺ���ָ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::shared_ptr<Model3D> FileManager::GetModel() const {
    return m_pModel3D;
}

/*************************************************************************
���������ơ�       FileManager::SetFilePath
���������ܡ�       �����ļ�·��
����ڲ�����       const std::string& FilePath - �ļ�·��
�����ڲ�����       ��
������ֵ��         bool - �����Ƿ�ɹ�
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
bool FileManager::SetFilePath(const std::string& FilePath) {
    if (FilePath.empty()) {
        throw ExceptionInvalidFileName();
    }
    m_Path = FilePath;
    return true;
}

/*************************************************************************
���������ơ�FileManager::ExceptionInvalidFileName::ExceptionInvalidFileName
���������ܡ�       ��Ч�ļ����쳣��Ĺ��캯��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
FileManager::ExceptionInvalidFileName::ExceptionInvalidFileName() 
: std::invalid_argument("Invalid file name") {
}

/*************************************************************************
���������ơ�FileManager::ExceptionInvalidExtension::ExceptionInvalidExtension
���������ܡ�       ��Ч��չ���쳣��Ĺ��캯��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
FileManager::ExceptionInvalidExtension::ExceptionInvalidExtension() 
: std::invalid_argument("Invalid file extension") {
}

/*************************************************************************
���������ơ�FileManager::ExceptionFileOpenFailed::ExceptionFileOpenFailed
���������ܡ�       �ļ���ʧ���쳣��Ĺ��캯��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
FileManager::ExceptionFileOpenFailed::ExceptionFileOpenFailed()
: std::runtime_error("Failed to open file") {
}
















