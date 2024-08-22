/*************************************************************************
���ļ�����                 Importer.hpp
������ģ���Ŀ�ġ�         ��������������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <vector>
#include <array>
#include <string>
#include <stdexcept>
#include <fstream>

#include "../GeometricModel/Model3D/Model3D.hpp"
#include "FileManager.hpp"

using namespace std;

#ifndef IMPORTER_HPP
#define IMPORTER_HPP

/*************************************************************************
��������             Importer
�����ܡ�             ���������࣬���ڴ��ļ��е���3Dģ��
���ӿ�˵����         �ṩ�ļ����غ�ģ�ͻ�ȡ���ܣ��������麯�����ھ���
                     ������ʵ��
�������߼����ڡ�     ����� 2024/8/12
�����ļ�¼��         ��
*************************************************************************/
class Importer : public FileManager {

public:
    //--------------------------------------------------------------------
    // ���캯������������
    //--------------------------------------------------------------------
    // ���캯��������һ��Model3D�Ĺ���ָ��
    Importer(std::shared_ptr<Model3D> Model3D);
    // ɾ���������캯��
    Importer(const Importer& Source) = delete;
    // ɾ����ֵ�����
    Importer& operator=(const Importer& Source) = delete;
    // ����������
    virtual ~Importer();

    //--------------------------------------------------------------------
    // ������Ա����
    //--------------------------------------------------------------------
    // ���ļ�����ģ��
    virtual bool LoadFromFile(const std::string& FilePath);
    // ��ȡ���ص�ģ��
    virtual std::shared_ptr<Model3D> GetLoadedModel() const;

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
    // ����ģ�͵�Model3D���󣨴��麯����
    virtual bool LoadToModel(const std::string& FilePath) = 0;

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




