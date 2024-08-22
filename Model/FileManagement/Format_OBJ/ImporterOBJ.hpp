/*************************************************************************
【文件名】                 ImporterOBJ.hpp
【功能模块和目的】         OBJ导入器声明
【开发者及日期】           周子睿 2024/8/12
【更改记录】               无
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
【类名】             ImporterOBJ
【功能】             OBJ文件导入器，用于从OBJ文件中导入3D模型
【接口说明】         提供文件加载和模型获取功能，包含具体的OBJ文件处理实现
【开发者及日期】     周子睿 2024/8/12
【更改记录】         无
*************************************************************************/
class ImporterOBJ : public Importer {

public:
    //--------------------------------------------------------------------
    // 构造函数和析构函数
    //--------------------------------------------------------------------
    // 构造函数，接受一个Model3D的共享指针
    ImporterOBJ(std::shared_ptr<Model3D> Model3D);
    // 删除拷贝构造函数
    ImporterOBJ(const ImporterOBJ& Source) = delete;
    // 删除赋值运算符
    ImporterOBJ& operator=(const ImporterOBJ& Source) = delete;
    // 虚析构函数
    virtual ~ImporterOBJ();

    //--------------------------------------------------------------------
    // 公共成员函数
    //--------------------------------------------------------------------
    // 从文件加载模型
    bool LoadFromFile(const std::string& FileName) override;
    // 获取加载的模型
    std::shared_ptr<Model3D> GetLoadedModel() const override;

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
    // 加载模型到Model3D对象
    bool LoadToModel(const std::string& FilePath) override;

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







