/*************************************************************************
【文件名】                 ImporterOBJ.cpp
【功能模块和目的】         OBJ导入器定义
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "ImporterOBJ.hpp"
#include "../../GeometricModel/Model3D/Model3D.hpp"

/*************************************************************************
【函数名称】       ImporterOBJ::ImporterOBJ
【函数功能】       构造函数，初始化Model3D对象的共享指针
【入口参数】       std::shared_ptr<Model3D> Model3D - 3D模型对象的共享指针
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
ImporterOBJ::ImporterOBJ(std::shared_ptr<Model3D> Model3D) :
Importer(Model3D), m_pModel3D(Model3D) {
}

/*************************************************************************
【函数名称】       ImporterOBJ::~ImporterOBJ
【函数功能】       析构函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
ImporterOBJ::~ImporterOBJ() = default;

/*************************************************************************
【函数名称】       ImporterOBJ::LoadFromFile
【函数功能】       从文件加载模型
【入口参数】       const std::string& FileName - 文件路径
【出口参数】       无
【返回值】         bool - 加载是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool ImporterOBJ::LoadFromFile(const std::string& FileName) {
    m_pModel3D->ClearModel();

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
【函数名称】       ImporterOBJ::GetLoadedModel
【函数功能】       获取加载的模型
【入口参数】       无
【出口参数】       无
【返回值】         std::shared_ptr<Model3D> - 3D模型对象的共享指针
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::shared_ptr<Model3D> ImporterOBJ::GetLoadedModel() const {
    return m_pModel3D;
}

/*************************************************************************
【函数名称】       ImporterOBJ::SetFilePath
【函数功能】       设置文件路径
【入口参数】       const std::string& FileName - 文件路径
【出口参数】       无
【返回值】         bool - 设置是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool ImporterOBJ::SetFilePath(const std::string& FileName) {
    if (FileName.empty()) {
        throw ExceptionInvalidFileName();
    }
    m_Path = FileName;
    return true;
}

/*************************************************************************
【函数名称】       ImporterOBJ::CheckExtension
【函数功能】       检查文件扩展名是否为OBJ
【入口参数】       无
【出口参数】       无
【返回值】         bool - 扩展名是否有效
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool ImporterOBJ::CheckExtension() const {
    size_t DotPosition = m_Path.find_last_of('.');
    if (DotPosition == std::string::npos) {
        throw ExceptionInvalidExtension();
    }
    std::string Extension = m_Path.substr(DotPosition + 1);
    return (Extension == "obj" || Extension == "OBJ");
}

/*************************************************************************
【函数名称】       ImporterOBJ::CheckOpen
【函数功能】       检查文件是否能打开
【入口参数】       无
【出口参数】       无
【返回值】         bool - 文件是否能打开
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool ImporterOBJ::CheckOpen() const {
    std::ifstream File(m_Path);
    return File.is_open();
}

/*************************************************************************
【函数名称】       ImporterOBJ::LoadToModel
【函数功能】       加载模型到Model3D对象
【入口参数】       const std::string& FilePath - 文件路径
【出口参数】       无
【返回值】         bool - 加载是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool ImporterOBJ::LoadToModel(const std::string& FilePath) {
    std::ifstream File(FilePath);
    if (!File.is_open()) {
        throw ExceptionFileOpenFailed();
    }

    std::string ALine;
    while (std::getline(File, ALine)) {
        std::istringstream Stream(ALine);
        char cTag;

        if (!(Stream >> cTag)) {
            continue;  // 空行
        }

        switch (cTag) {
        case '#':
            // 处理注释
            break;
        case 'g':
        {
            std::string Name;
            std::getline(Stream >> std::ws, Name);  // 读取剩余的行作为名称
            m_pModel3D->SetModelName(Name);
            break;
        }
        case 'v':
        {
            double rX, rY, rZ;
            if (Stream >> rX >> rY >> rZ) {
                m_pModel3D->AddPoint({ rX, rY, rZ });
            }
            break;
        }
        case 'l':
        {
            unsigned int uIndex1, uIndex2;
            if (Stream >> uIndex1 >> uIndex2) {
                m_pModel3D->AddLine({ uIndex1 - 1, uIndex2 - 1 });
            }
            break;
        }
        case 'f':
        {
            unsigned int uIndex1, uIndex2, uIndex3;
            if (Stream >> uIndex1 >> uIndex2 >> uIndex3) {
                m_pModel3D->AddFace(
                    { uIndex1 - 1, uIndex2 - 1, uIndex3 - 1 });
            }
            break;
        }
        default :
            // 处理未知标签
            break;
        }
    }

    return true;
}











