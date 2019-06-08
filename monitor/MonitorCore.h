/**
 * @file MonitorCore.h
 * @brief
 * @author  lenovo <xxx@lenovo.com>
 * @version 1.0.0
 * @date 2019-06-07
 */
/* Copyright(C) 2009-2019, Lenovo Inc.
 * All right reserved
 *
 */
#ifndef __MONITORCORE_H__
#define __MONITORCORE_H__
#include <functional>

#include "common.h"
#include "threads/ThreadPoolEx.h"
#include "MonitorUtils.h"
#include "FileManager.h"

namespace uranium
{
class MonitorUtils;
class FileManager;
class MonitorCore
{
public:

public:
    int32_t construct();
    int32_t destruct();
    MonitorCore(std::string fileMagePath, std::string monitorPath);
    virtual ~MonitorCore();

private:
    MonitorCore(const MonitorCore &rhs) = delete;
    MonitorCore &operator=(const MonitorCore &rhs) = delete;
    void processHandle(const std::vector<event>& envets);

private:
    bool            mConstructed;
    ModuleType      mModule;
    MonitorUtils    *mMonitor;
    FileManager     *mFileMage;
    std::string     mFileMagePath;
    std::string     mMonitorPath;
    ThreadPoolEx    *mThreads;

};  // class MonitorCore

}

#endif //__MONITORCORE_H__
