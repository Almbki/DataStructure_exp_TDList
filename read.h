#ifndef READ_H
#define READ_H

#include "Task.hpp"
#include <string>
#include <fstream>
#include <vector>

namespace IO_File { 
    const std::string TASKS_FILE = "tasks.txt"; 
    const char DELIMITER = '|';
    bool loadData(Task_Stru& taskManager, const std::string& filename = TASKS_FILE);
    bool saveData(Task_Stru& taskManager, const std::string& filename = TASKS_FILE);
    
    // 辅助函数
    std::string trim(const std::string& str);
    std::vector<std::string> split(const std::string& str, char delimiter);
    
    // 校验函数
    bool validateTaskData(const Task_data& task);
    
} // namespace IO_File

#endif
