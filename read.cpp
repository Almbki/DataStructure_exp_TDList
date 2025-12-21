#include "read.h"
#include <sstream>
#include <iostream>

namespace IO_File {
    std::string trim(const std::string& s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }
    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> result;
        std::string item;
        std::istringstream stream(s);
        
        while (std::getline(stream, item, delim)) {
            result.push_back(trim(item));
        }
        return result;
    }
    bool validateTaskData(const Task_data& task) {
        // 基本校验
        if (task.id < 0) return false;
        if (task.title.empty()) return false;
        if (task.priority < 1 || task.priority > 10) return false;
        if (task.deadline < 0) return false;
        return true;
    }
    bool loadData(Task_Stru& manager, const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "注意: 未找到数据文件 " << filename 
                     << "，将创建新文件。" << std::endl;
            return false;
        }
        manager.createList();
        std::string line;
        int lineNum = 0;
        
        while (std::getline(file, line)) {
            lineNum++;
            line = trim(line);
            
            // 跳过空行和注释
            if (line.empty() || line[0] == '#') continue;
            
            std::vector<std::string> fields = split(line, DELIMITER);
            
            // 必须7个字段：id|title|note|startline|deadline|priority|finished
            if (fields.size() != 7) {
                std::cerr << "警告: 第" << lineNum << "行格式错误，跳过" << std::endl;
                continue;
            }
            
            try {
                Task_data task;
                task.id = std::stoi(fields[0]);
                task.title = fields[1];
                task.note = fields[2];
                task.startline = std::stoll(fields[3]);
                task.deadline = std::stoll(fields[4]);
                task.priority = std::stoi(fields[5]);
                task.finished = (fields[6] == "1" || fields[6] == "true");
                if (!validateTaskData(task)) {
                    std::cerr << "警告: 第" << lineNum << "行数据无效，跳过" << std::endl;
                    continue;
                }
                manager.InsertNode(task);
                
            } catch (const std::exception& e) {
                std::cerr << "错误: 第" << lineNum << "行解析失败: " 
                         << e.what() << std::endl;
                continue;
            }
        }
        
        file.close();
        std::cout << "从 " << filename << " 加载了 " << lineNum << " 行数据" << std::endl;
        return true;
    }
    
    bool saveData(Task_Stru& manager, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "错误: 无法打开文件 " << filename << " 进行写入" << std::endl;
            return false;
        }
        file << "# 任务数据文件格式: id|title|note|startline|deadline|priority|finished\n";
        
        TNode_head head = manager.getHead();
        if (!head) {
            file.close();
            return true;  // 空链表，文件为空
        }
        
        int savedCount = 0;
        TNode_elem* current = head->first;
        
        while (current) {
            const Task_data& task = current->task;
            
            file << task.id << DELIMITER
                 << task.title << DELIMITER
                 << task.note << DELIMITER
                 << task.startline << DELIMITER
                 << task.deadline << DELIMITER
                 << task.priority << DELIMITER
                 << (task.finished ? "1" : "0") << "\n";
            
            savedCount++;
            current = current->next;
        }
        
        file.close();
        std::cout << "向 " << filename << " 保存了 " << savedCount << " 个任务" << std::endl;
        return true;
    }
    
} // namespace IO_File
