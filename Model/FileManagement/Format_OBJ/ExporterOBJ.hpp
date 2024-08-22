/*************************************************************************
���ļ�����                 ExporterOBJ.hpp
������ģ���Ŀ�ġ�         OBJ����������
�������߼����ڡ�           ����� 2024 / 8 / 12
�����ļ�¼��               ��
**************************************************************************/

#ifndef EXPORTER_OBJ_HPP
#define EXPORTER_OBJ_HPP

#include <memory>
#include <string>

#include "../Exporter.hpp"
#include "../../GeometricModel/Model3D/Model3D.hpp"

/*************************************************************************
��������             ExporterOBJ.hpp
�����ܡ�             OBJ�ļ������������ڽ�3Dģ�͵�����OBJ�ļ�
���ӿ�˵����         �ṩ�ļ������ģ�ͻ�ȡ���ܣ����������OBJ�ļ�����ʵ��
�������߼����ڡ�     ����� 2024/8/12
�����ļ�¼��         ��
*************************************************************************/
class ExporterOBJ : public Exporter {
public:
    //--------------------------------------------------------------------
    // ���캯������������
    //--------------------------------------------------------------------
    // ���캯��������һ��Model3D�Ĺ���ָ��
    ExporterOBJ(std::shared_ptr<Model3D> Model3D);
    // ɾ���������캯��
    ExporterOBJ(const ExporterOBJ& Source) = delete;
    // ɾ����ֵ�����
    ExporterOBJ& operator=(const ExporterOBJ& Source) = delete;
    // ����������
    virtual ~ExporterOBJ();

    //--------------------------------------------------------------------
    // ������Ա����
    //--------------------------------------------------------------------
    // ��ģ�ͱ��浽�ļ�
    bool SaveToFile(const std::string& FileName, 
        const std::string& Comment = "") override;
    // ��ȡҪ������ģ��
    std::shared_ptr<Model3D> GetModelToExport() const override;

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
    // ��Model3D���󱣴�ģ�͵��ļ�
    bool SaveFromModel(const std::string& FilePath, 
        const std::string& Comment = "") override;

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




