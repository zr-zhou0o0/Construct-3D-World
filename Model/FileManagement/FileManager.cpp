/*************************************************************************
【文件名】                 FileManager.cpp
【功能模块和目的】         文件管理器基类定义
【开发者及日期】           周子睿 2024/8/13
【更改记录】               无
*************************************************************************/

#include "FileManager.hpp"
#include <stdexcept>

/*************************************************************************
【函数名称】       FileManager::FileManager
【函数功能】       构造函数，初始化Model3D对象的共享指针
【入口参数】       std::shared_ptr<Model3D> Model3D - 3D模型对象的共享指针
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
FileManager::FileManager(std::shared_ptr<Model3D> Model3D) : 
m_pModel3D(Model3D) {
    if (!m_pModel3D) {
        throw std::invalid_argument("Model3D pointer cannot be null");
    }
}

/*************************************************************************
【函数名称】       FileManager::~FileManager
【函数功能】       析构函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
FileManager::~FileManager() = default;

/*************************************************************************
【函数名称】       FileManager::GetModel
【函数功能】       获取Model3D对象的共享指针
【入口参数】       无
【出口参数】       无
【返回值】         std::shared_ptr<Model3D> - 3D模型对象的共享指针
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::shared_ptr<Model3D> FileManager::GetModel() const {
    return m_pModel3D;
}

/*************************************************************************
【函数名称】       FileManager::SetFilePath
【函数功能】       设置文件路径
【入口参数】       const std::string& FilePath - 文件路径
【出口参数】       无
【返回值】         bool - 设置是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool FileManager::SetFilePath(const std::string& FilePath) {
    if (FilePath.empty()) {
        throw ExceptionInvalidFileName();
    }
    m_Path = FilePath;
    return true;
}

/*************************************************************************
【函数名称】FileManager::ExceptionInvalidFileName::ExceptionInvalidFileName
【函数功能】       无效文件名异常类的构造函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
FileManager::ExceptionInvalidFileName::ExceptionInvalidFileName() 
: std::invalid_argument("Invalid file name") {
}

/*************************************************************************
【函数名称】FileManager::ExceptionInvalidExtension::ExceptionInvalidExtension
【函数功能】       无效扩展名异常类的构造函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
FileManager::ExceptionInvalidExtension::ExceptionInvalidExtension() 
: std::invalid_argument("Invalid file extension") {
}

/*************************************************************************
【函数名称】FileManager::ExceptionFileOpenFailed::ExceptionFileOpenFailed
【函数功能】       文件打开失败异常类的构造函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
FileManager::ExceptionFileOpenFailed::ExceptionFileOpenFailed()
: std::runtime_error("Failed to open file") {
}
















