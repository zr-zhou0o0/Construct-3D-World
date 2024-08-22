/*************************************************************************
���ļ�����                 FileManager.hpp
������ģ���Ŀ�ġ�         �ļ���������������
�������߼����ڡ�           ����� 2024/8/13
�����ļ�¼��               ��
*************************************************************************/
#include <string>
#include <memory>
#include <stdexcept>

#include "../GeometricModel/Model3D/Model3D.hpp"

#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

/*************************************************************************
��������             FileManager
�����ܡ�             �ļ����������࣬���ڹ���3Dģ���ļ��Ķ�ȡ��д��
���ӿ�˵����         �ṩ�������ļ�·�����ú�ģ�ͻ�ȡ���ܣ������쳣������
�������߼����ڡ�     ����� 2024/8/13
�����ļ�¼��         ��
*************************************************************************/
class FileManager {
public:
    //--------------------------------------------------------------------
    // ���캯������������
    //--------------------------------------------------------------------
    // ���캯��������һ��Model3D�Ĺ���ָ��
    FileManager(std::shared_ptr<Model3D> Model3D);
    // ɾ���������캯��
    FileManager(const FileManager& Source) = delete;
    // ɾ����ֵ�����
    FileManager& operator=(const FileManager& Source) = delete;
    // ����������
    virtual ~FileManager();

    //--------------------------------------------------------------------
    // ������Ա����
    //--------------------------------------------------------------------
    // ��ȡModel3D����Ĺ���ָ��
    std::shared_ptr<Model3D> GetModel() const;

    //--------------------------------------------------------------------
    // �쳣��
    //--------------------------------------------------------------------
    // ��Ч�ļ����쳣��
    class ExceptionInvalidFileName : public std::invalid_argument {
    public:
        ExceptionInvalidFileName();
    };

    // ��Ч��չ���쳣��
    class ExceptionInvalidExtension : public std::invalid_argument {
    public:
        ExceptionInvalidExtension();
    };

    // �ļ���ʧ���쳣��
    class ExceptionFileOpenFailed : public std::runtime_error {
    public:
        ExceptionFileOpenFailed();
    };

protected:
    //--------------------------------------------------------------------
    // �ܱ����ĳ�Ա����
    //--------------------------------------------------------------------
    // �����ļ�·��
    bool SetFilePath(const std::string& FilePath);
    // ����ļ���չ�������麯����
    virtual bool CheckExtension() const = 0;
    // ����ļ��Ƿ��ܴ򿪣����麯����
    virtual bool CheckOpen() const = 0;

private:
    //--------------------------------------------------------------------
    // ˽�еĵĳ�Ա����
    //--------------------------------------------------------------------
    // �ļ�·��
    std::string m_Path;
    // Model3D����Ĺ���ָ��
    std::shared_ptr<Model3D> m_pModel3D = nullptr;

    
   
};

#endif


