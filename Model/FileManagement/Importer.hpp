/*************************************************************************
【文件名】                 Importer.hpp
【功能模块和目的】         导入器基类声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
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
【类名】             Importer
【功能】             导入器基类，用于从文件中导入3D模型
【接口说明】         提供文件加载和模型获取功能，包含纯虚函数用于具体
                     导入器实现
【开发者及日期】     周子睿 2024/8/12
【更改记录】         无
*************************************************************************/
class Importer : public FileManager {

public:
    //--------------------------------------------------------------------
    // 构造函数和析构函数
    //--------------------------------------------------------------------
    // 构造函数，接受一个Model3D的共享指针
    Importer(std::shared_ptr<Model3D> Model3D);
    // 删除拷贝构造函数
    Importer(const Importer& Source) = delete;
    // 删除赋值运算符
    Importer& operator=(const Importer& Source) = delete;
    // 虚析构函数
    virtual ~Importer();

    //--------------------------------------------------------------------
    // 公共成员函数
    //--------------------------------------------------------------------
    // 从文件加载模型
    virtual bool LoadFromFile(const std::string& FilePath);
    // 获取加载的模型
    virtual std::shared_ptr<Model3D> GetLoadedModel() const;

protected:
    //--------------------------------------------------------------------
    // 受保护的成员函数
    //--------------------------------------------------------------------
    // 设置文件路径
    bool SetFilePath(const std::string& FilePath);
    // 检查文件扩展名（纯虚函数）
    virtual bool CheckExtension() const = 0;
    // 检查文件是否能打开（纯虚函数）
    virtual bool CheckOpen() const = 0;
    // 加载模型到Model3D对象（纯虚函数）
    virtual bool LoadToModel(const std::string& FilePath) = 0;

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




