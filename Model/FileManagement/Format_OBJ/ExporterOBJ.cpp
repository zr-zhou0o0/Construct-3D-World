/*************************************************************************
【文件名】                 ExporterOBJ.cpp
【功能模块和目的】         OBJ导出器定义
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
*************************************************************************/

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ExporterOBJ.hpp"
#include "../Exporter.hpp"
#include "../../GeometricModel/Model3D/Model3D.hpp"

/*************************************************************************
【函数名称】       ExporterOBJ::ExporterOBJ
【函数功能】       构造函数，初始化Model3D对象的共享指针
【入口参数】       std::shared_ptr<Model3D> Model3D - 3D模型对象的共享指针
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
ExporterOBJ::ExporterOBJ(std::shared_ptr<Model3D> Model3D) : 
Exporter(Model3D), m_pModel3D(Model3D) {
}

/*************************************************************************
【函数名称】       ExporterOBJ::~ExporterOBJ
【函数功能】       析构函数
【入口参数】       无
【出口参数】       无
【返回值】         无
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
ExporterOBJ::~ExporterOBJ() = default;

/*************************************************************************
【函数名称】       ExporterOBJ::SaveToFile
【函数功能】       将模型保存到文件
【入口参数】       const std::string& FileName - 文件路径
                   const std::string& Comment - 注释（可选）
【出口参数】       无
【返回值】         bool - 保存是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool ExporterOBJ::SaveToFile(
    const std::string& FileName, const std::string& Comment) {
    if (!SetFilePath(FileName)) {
        throw ExceptionInvalidFileName();
    }

    if (!CheckExtension()) {
        throw ExceptionInvalidExtension();
    }

    if (!CheckOpen()) {
        throw ExceptionFileOpenFailed();
    }

    return SaveFromModel(m_Path, Comment);
}

/*************************************************************************
【函数名称】       ExporterOBJ::GetModelToExport
【函数功能】       获取要导出的模型
【入口参数】       无
【出口参数】       无
【返回值】         std::shared_ptr<Model3D> - 3D模型对象的共享指针
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
std::shared_ptr<Model3D> ExporterOBJ::GetModelToExport() const {
    return m_pModel3D;
}

/*************************************************************************
【函数名称】       ExporterOBJ::SetFilePath
【函数功能】       设置文件路径
【入口参数】       const std::string& FileName - 文件路径
【出口参数】       无
【返回值】         bool - 设置是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool ExporterOBJ::SetFilePath(const std::string& FileName) {
    if (FileName.empty()) {
        throw ExceptionInvalidFileName();
    }
    m_Path = FileName;
    return true;
}

/*************************************************************************
【函数名称】       ExporterOBJ::CheckExtension
【函数功能】       检查文件扩展名是否为OBJ
【入口参数】       无
【出口参数】       无
【返回值】         bool - 扩展名是否有效
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool ExporterOBJ::CheckExtension() const {
    size_t DotPosition = m_Path.find_last_of('.');
    if (DotPosition == std::string::npos) {
        throw ExceptionInvalidExtension();
    }
    std::string Extension = m_Path.substr(DotPosition + 1);
    return (Extension == "obj" || Extension == "OBJ");
}

/*************************************************************************
【函数名称】       ExporterOBJ::CheckOpen
【函数功能】       检查文件是否能打开
【入口参数】       无
【出口参数】       无
【返回值】         bool - 文件是否能打开
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool ExporterOBJ::CheckOpen() const {
    std::ofstream File(m_Path);
    return File.good();
}

/*************************************************************************
【函数名称】       ExporterOBJ::SaveFromModel
【函数功能】       从Model3D对象保存模型到文件
【入口参数】       const std::string& FilePath - 文件路径
                   const std::string& Comment - 注释（可选）
【出口参数】       无
【返回值】         bool - 保存是否成功
【开发者及日期】   周子睿 2024/8/12
【更改记录】       无
*************************************************************************/
bool ExporterOBJ::SaveFromModel(
    const std::string& FilePath, const std::string& Comment) {
    std::ofstream File(FilePath);
    if (!File.is_open()) {
        throw ExceptionFileOpenFailed();
        return false;
    }

    const auto& Points = m_pModel3D->GetPointSet();
    const auto& Lines = m_pModel3D->GetLines();
    const auto& Faces = m_pModel3D->GetFaces();

    if (!Comment.empty()) {
        File << "# " << Comment << "\n";
    }

    File << "g " << m_pModel3D->GetModelName() << "\n";

    for (const auto& APoint : Points) {
        File << "v " 
             << APoint[0] << " " 
             << APoint[1] << " " 
             << APoint[2] << "\n";
    }

    for (const auto& ALine : Lines) {
        File << "l " << (ALine[0] + 1) << " " << (ALine[1] + 1) << "\n";
    }

    for (const auto& AFace : Faces) {
        File << "f " 
            << (AFace[0] + 1) << " " 
            << (AFace[1] + 1) << " " 
            << (AFace[2] + 1) << "\n";
    }

    return true;
}





