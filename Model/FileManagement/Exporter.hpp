/*************************************************************************
���ļ�����                 Exporter.hpp
������ģ���Ŀ�ġ�         ��������������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <string>
#include <memory>
#include <stdexcept>

#include "../GeometricModel/Model3D/Model3D.hpp"
#include "FileManager.hpp"

#ifndef EXPORTER_HPP
#define EXPORTER_HPP

/*************************************************************************
��������             Exporter
�����ܡ�             ���������࣬���ڽ�3Dģ�͵������ļ�
���ӿ�˵����         �ṩ�ļ������ģ�ͻ�ȡ���ܣ�
                     �������麯�����ھ��嵼����ʵ��
�������߼����ڡ�     ����� 2024/8/12
�����ļ�¼��         ��
*************************************************************************/
class Exporter : public FileManager {
public:
    //--------------------------------------------------------------------
    // ���캯������������
    //--------------------------------------------------------------------
    // ���캯��������һ��Model3D�Ĺ���ָ��
    Exporter(std::shared_ptr<Model3D> Model3D);
    // ɾ���������캯��
    Exporter(const Exporter& Source) = delete;
    // ɾ����ֵ�����
    Exporter& operator=(const Exporter& Source) = delete;
    // ����������
    virtual ~Exporter();

    //--------------------------------------------------------------------
    // ������Ա����
    //--------------------------------------------------------------------
    // ��ģ�ͱ��浽�ļ�
    virtual bool SaveToFile(
        const std::string& FileName, const std::string& Comment = "");
    // ��ȡҪ������ģ��
    virtual std::shared_ptr<Model3D> GetModelToExport() const;

protected:
    //--------------------------------------------------------------------
    // �ܱ����ĳ�Ա����
    //--------------------------------------------------------------------
    // �����ļ�·��
    bool SetFilePath(const std::string& FileName);
    // ����ļ���չ�������麯����
    virtual bool CheckExtension() const = 0;
    // ����ļ��Ƿ��ܴ򿪣����麯����
    virtual bool CheckOpen() const = 0;
    // ��Model3D���󱣴�ģ�͵��ļ������麯����
    virtual bool SaveFromModel(
        const std::string& FilePath, const std::string& Comment = "") = 0;

private:
    //--------------------------------------------------------------------
    // ˽�еĳ�Ա����
    //--------------------------------------------------------------------
    // �ļ�·��
    std::string m_Path;
    // Model3D����Ĺ���ָ��
    std::shared_ptr<Model3D> m_pModel3D = nullptr;

   
};

#endif









