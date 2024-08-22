/*************************************************************************
���ļ�����                 ImporterOBJ.hpp
������ģ���Ŀ�ġ�         OBJ����������
�������߼����ڡ�           ����� 2024/8/12
�����ļ�¼��               ��
*************************************************************************/

#include <vector>
#include <array>
#include <string>
#include <stdexcept>
#include <fstream>

#include "../Importer.hpp"
#include "../../GeometricModel/Model3D/Model3D.hpp"

#ifndef IMPORTER_OBJ_HPP
#define IMPORTER_OBJ_HPP

/*************************************************************************
��������             ImporterOBJ
�����ܡ�             OBJ�ļ������������ڴ�OBJ�ļ��е���3Dģ��
���ӿ�˵����         �ṩ�ļ����غ�ģ�ͻ�ȡ���ܣ����������OBJ�ļ�����ʵ��
�������߼����ڡ�     ����� 2024/8/12
�����ļ�¼��         ��
*************************************************************************/
class ImporterOBJ : public Importer {

public:
    //--------------------------------------------------------------------
    // ���캯������������
    //--------------------------------------------------------------------
    // ���캯��������һ��Model3D�Ĺ���ָ��
    ImporterOBJ(std::shared_ptr<Model3D> Model3D);
    // ɾ���������캯��
    ImporterOBJ(const ImporterOBJ& Source) = delete;
    // ɾ����ֵ�����
    ImporterOBJ& operator=(const ImporterOBJ& Source) = delete;
    // ����������
    virtual ~ImporterOBJ();

    //--------------------------------------------------------------------
    // ������Ա����
    //--------------------------------------------------------------------
    // ���ļ�����ģ��
    bool LoadFromFile(const std::string& FileName) override;
    // ��ȡ���ص�ģ��
    std::shared_ptr<Model3D> GetLoadedModel() const override;

protected:
    //--------------------------------------------------------------------
    // �ܱ����ĳ�Ա����
    //--------------------------------------------------------------------
    // �����ļ�·��
    bool SetFilePath(const std::string& FileName);
    // ����ļ���չ��
    bool CheckExtension() const override;
    // ����ļ��Ƿ��ܴ�
    bool CheckOpen() const override;
    // ����ģ�͵�Model3D����
    bool LoadToModel(const std::string& FilePath) override;

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







