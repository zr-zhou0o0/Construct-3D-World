/*************************************************************************
【文件名】                 FileManager.hpp
【功能模块和目的】         文件管理器基类声明
【开发者及日期】           周子睿 2024/8/13
【更改记录】               无
*************************************************************************/
#include <string>
#include <memory>
#include <stdexcept>

#include "../GeometricModel/Model3D/Model3D.hpp"

#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

/*************************************************************************
【类名】             FileManager
【功能】             文件管理器基类，用于管理3D模型文件的读取和写入
【接口说明】         提供基本的文件路径设置和模型获取功能，包含异常类声明
【开发者及日期】     周子睿 2024/8/13
【更改记录】         无
*************************************************************************/
class FileManager {
public:
    //--------------------------------------------------------------------
    // 构造函数和析构函数
    //--------------------------------------------------------------------
    // 构造函数，接受一个Model3D的共享指针
    FileManager(std::shared_ptr<Model3D> Model3D);
    // 删除拷贝构造函数
    FileManager(const FileManager& Source) = delete;
    // 删除赋值运算符
    FileManager& operator=(const FileManager& Source) = delete;
    // 虚析构函数
    virtual ~FileManager();

    //--------------------------------------------------------------------
    // 公共成员函数
    //--------------------------------------------------------------------
    // 获取Model3D对象的共享指针
    std::shared_ptr<Model3D> GetModel() const;

    //--------------------------------------------------------------------
    // 异常类
    //--------------------------------------------------------------------
    // 无效文件名异常类
    class ExceptionInvalidFileName : public std::invalid_argument {
    public:
        ExceptionInvalidFileName();
    };

    // 无效扩展名异常类
    class ExceptionInvalidExtension : public std::invalid_argument {
    public:
        ExceptionInvalidExtension();
    };

    // 文件打开失败异常类
    class ExceptionFileOpenFailed : public std::runtime_error {
    public:
        ExceptionFileOpenFailed();
    };

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

private:
    //--------------------------------------------------------------------
    // 私有的的成员变量
    //--------------------------------------------------------------------
    // 文件路径
    std::string m_Path;
    // Model3D对象的共享指针
    std::shared_ptr<Model3D> m_pModel3D = nullptr;

    
   
};

#endif


