/*************************************************************************
【文件名】                 Importer.cpp
【功能模块和目的】         导入器基类定义
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <stdexcept>

#include "Importer.hpp"
#include "../GeometricModel/Model3D/Model3D.hpp"

/*************************************************************************
【函数名称】       Importer::Importer
【函数功能】       构造函数，初始化Model3D对象的共享指针
【入口参数】       std::shared_ptr<Model3D> Model3D - 3D模型对象的共享指针
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Importer::Importer(std::shared_ptr<Model3D> Model3D): 
m_pModel3D(Model3D), FileManager(Model3D) {
    if (!m_pModel3D) {
        throw std::invalid_argument("Model3D pointer cannot be null");
    }
}

/*************************************************************************
【函数名称】       Importer::~Importer
【函数功能】       析构函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
Importer::~Importer() = default;

/*************************************************************************
【函数名称】       Importer::LoadFromFile
【函数功能】       从文件加载模型
【入口参数】       const std::string& FileName - 文件路径
【出口参数】       无
【返回值】         bool - 加载是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Importer::LoadFromFile(const std::string& FileName) {
    if (!SetFilePath(FileName)) {
        throw ExceptionInvalidFileName();
    }

    if (!CheckExtension()) {
        throw ExceptionInvalidExtension();
    }

    if (!CheckOpen()) {
        throw ExceptionFileOpenFailed();
    }

    return LoadToModel(m_Path);
}

/*************************************************************************
【函数名称】       Importer::GetLoadedModel
【函数功能】       获取加载的模型
【入口参数】       无
【出口参数】       无
【返回值】         std::shared_ptr<Model3D> - 3D模型对象的共享指针
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::shared_ptr<Model3D> Importer::GetLoadedModel() const {
    return m_pModel3D;
}

/*************************************************************************
【函数名称】       Importer::SetFilePath
【函数功能】       设置文件路径
【入口参数】       const std::string& FileName - 文件路径
【出口参数】       无
【返回值】         bool - 设置是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool Importer::SetFilePath(const std::string& FileName) {
    if (FileName.empty()) {
        throw ExceptionInvalidFileName();
    }
    m_Path = FileName;
    return true;
}








