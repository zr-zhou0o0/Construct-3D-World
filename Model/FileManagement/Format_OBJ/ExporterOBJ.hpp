/*************************************************************************
【文件名】                 ExporterOBJ.hpp
【功能模块和目的】         OBJ导出器声明
【开发者及日期】           周子睿 2024 / 8 / 12
【更改记录】               无
**************************************************************************/

#ifndef EXPORTER_OBJ_HPP
#define EXPORTER_OBJ_HPP

#include <memory>
#include <string>

#include "../Exporter.hpp"
#include "../../GeometricModel/Model3D/Model3D.hpp"

/*************************************************************************
【类名】             ExporterOBJ.hpp
【功能】             OBJ文件导出器，用于将3D模型导出到OBJ文件
【接口说明】         提供文件保存和模型获取功能，包含具体的OBJ文件处理实现
【开发者及日期】     周子睿 2024/8/12
【更改记录】         无
*************************************************************************/
class ExporterOBJ : public Exporter {
public:
    //--------------------------------------------------------------------
    // 构造函数和析构函数
    //--------------------------------------------------------------------
    // 构造函数，接受一个Model3D的共享指针
    ExporterOBJ(std::shared_ptr<Model3D> Model3D);
    // 删除拷贝构造函数
    ExporterOBJ(const ExporterOBJ& Source) = delete;
    // 删除赋值运算符
    ExporterOBJ& operator=(const ExporterOBJ& Source) = delete;
    // 虚析构函数
    virtual ~ExporterOBJ();

    //--------------------------------------------------------------------
    // 公共成员函数
    //--------------------------------------------------------------------
    // 将模型保存到文件
    bool SaveToFile(const std::string& FileName, 
        const std::string& Comment = "") override;
    // 获取要导出的模型
    std::shared_ptr<Model3D> GetModelToExport() const override;

protected:
    //--------------------------------------------------------------------
    // 受保护的成员函数
    //--------------------------------------------------------------------
    // 设置文件路径
    bool SetFilePath(const std::string& FileName);
    // 检查文件扩展名
    bool CheckExtension() const override;
    // 检查文件是否能打开
    bool CheckOpen() const override;
    // 从Model3D对象保存模型到文件
    bool SaveFromModel(const std::string& FilePath, 
        const std::string& Comment = "") override;

private:
    //--------------------------------------------------------------------
    // 私有的成员变量
    //--------------------------------------------------------------------
    // 文件路径
    std::string m_Path;
    // Model3D对象的共享指针
    std::shared_ptr<Model3D> m_pModel3D = nullptr;


};

#endif




