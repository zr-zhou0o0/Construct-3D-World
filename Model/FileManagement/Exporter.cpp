/*************************************************************************
【文件名】                 Exporter.cpp
【功能模块和目的】         导出器基类定义
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <stdexcept>
#include "Exporter.hpp"
#include "../GeometricModel/Model3D/Model3D.hpp"

/*************************************************************************
【函数名称】       Exporter::Exporter
【函数功能】       构造函数，初始化Model3D对象的共享指针
【入口参数】       std::shared_ptr<Model3D> Model3D - 3D模型对象的共享指针
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Exporter::Exporter(std::shared_ptr<Model3D> Model3D) : 
m_pModel3D(Model3D), FileManager(Model3D) {
    if (!m_pModel3D) {
        throw std::invalid_argument("Model3D pointer cannot be null");
    }
}

/*************************************************************************
【函数名称】       Exporter::~Exporter
【函数功能】       析构函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Exporter::~Exporter() = default;

/*************************************************************************
【函数名称】       Exporter::SaveToFile
【函数功能】       将模型保存到文件
【入口参数】       const std::string& FileName - 文件路径
                   const std::string& Comment - 文件注释
【出口参数】       无
【返回值】         bool - 保存是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
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
【函数名称】       Exporter::GetModelToExport
【函数功能】       获取要导出的模型
【入口参数】       无
【出口参数】       无
【返回值】         std::shared_ptr<Model3D> - 3D模型对象的共享指针
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::shared_ptr<Model3D> Exporter::GetModelToExport() const {
    return m_pModel3D;
}

/*************************************************************************
【函数名称】       Exporter::SetFilePath
【函数功能】       设置文件路径
【入口参数】       const std::string& FileName - 文件路径
【出口参数】       无
【返回值】         bool - 设置是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Exporter::SetFilePath(const std::string& FileName) {
    if (FileName.empty()) {
        return false;
    }
    m_Path = FileName;
    return true;
}





