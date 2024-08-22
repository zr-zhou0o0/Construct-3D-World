/*************************************************************************
【文件名】                 Exporter.hpp
【功能模块和目的】         导出器基类声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <string>
#include <memory>
#include <stdexcept>

#include "../GeometricModel/Model3D/Model3D.hpp"
#include "FileManager.hpp"

#ifndef EXPORTER_HPP
#define EXPORTER_HPP

/*************************************************************************
【类名】             Exporter
【功能】             导出器基类，用于将3D模型导出到文件
【接口说明】         提供文件保存和模型获取功能，
                     包含纯虚函数用于具体导出器实现
【开发者及日期】     周子睿 2024/8/12
【更改记录】         无
*************************************************************************/
class Exporter : public FileManager {
public:
    //--------------------------------------------------------------------
    // 构造函数和析构函数
    //--------------------------------------------------------------------
    // 构造函数，接受一个Model3D的共享指针
    Exporter(std::shared_ptr<Model3D> Model3D);
    // 删除拷贝构造函数
    Exporter(const Exporter& Source) = delete;
    // 删除赋值运算符
    Exporter& operator=(const Exporter& Source) = delete;
    // 虚析构函数
    virtual ~Exporter();

    //--------------------------------------------------------------------
    // 公共成员函数
    //--------------------------------------------------------------------
    // 将模型保存到文件
    virtual bool SaveToFile(
        const std::string& FileName, const std::string& Comment = "");
    // 获取要导出的模型
    virtual std::shared_ptr<Model3D> GetModelToExport() const;

protected:
    //--------------------------------------------------------------------
    // 受保护的成员函数
    //--------------------------------------------------------------------
    // 设置文件路径
    bool SetFilePath(const std::string& FileName);
    // 检查文件扩展名（纯虚函数）
    virtual bool CheckExtension() const = 0;
    // 检查文件是否能打开（纯虚函数）
    virtual bool CheckOpen() const = 0;
    // 从Model3D对象保存模型到文件（纯虚函数）
    virtual bool SaveFromModel(
        const std::string& FilePath, const std::string& Comment = "") = 0;

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









