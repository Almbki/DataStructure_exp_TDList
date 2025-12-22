#include "TaskIO.hpp"
#include "Task.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>


namespace IO{
    constexpr size_t id_Width       = 7;
    constexpr size_t tit_Width      = 25;    
    constexpr size_t pri_Width      = 15;
    constexpr size_t ddl_Width      = 15;
    constexpr size_t status_Width   = 10;

    void printSeparator(){      //输出分隔符
        size_t tabWidth = id_Width+tit_Width+pri_Width+ddl_Width+status_Width+5;
        std::cout << std::string(tabWidth,'-') << '\n';
    }

    size_t displayWidth(const std::string &s){      //计算字符宽度
        size_t colWidth = 0;

        for (size_t i = 0; i < s.size();)
        {
            unsigned char c = s[i];

            if (c < 0x80){      //2字节
                colWidth += 1;
                i += 1;
            }
            else if ((c & 0xE0) == 0xC0){   //2字节
                colWidth += 2;
                i += 2; 
            }
            else if ((c & 0xF0) == 0xE0){   //3字节
                colWidth += 2;
                i += 3;
            }
            else if ((c & 0xF8) == 0xF0){   //4字节
                colWidth += 2;
                i += 4;
            }
            else{
                colWidth += 1;
                i += 1;
            }
            
        }
        return colWidth;
    
    }
    void printCell(const std::string& s, size_t colWidth) {     //调整输出
        std::cout << s;

        size_t w = displayWidth(s);
        if (w < colWidth) {
            std::cout << std::string(colWidth - w, ' ');
        }

        std::cout << ' ';
    }

    void printTaskRow(const Task_data& t) {
    printCell(std::to_string(t.id), id_Width);
    printCell(t.title, tit_Width);
    printCell(std::to_string(t.priority), pri_Width);
    printCell(std::to_string(t.deadline), ddl_Width);
    printCell(t.finished ? "已完成" : "未完成",status_Width);
    std::cout << '\n';
}

    void printTaskHeader(){
        printSeparator();
        printCell("ID",id_Width);
        printCell("标题",tit_Width);
        printCell("优先度",pri_Width);
        printCell("截止时间",ddl_Width);
        printCell("状态", status_Width);
        std::cout << "\n";
        printSeparator();
    }

    void printTaskFooter(){
        printSeparator();
    }

    void printEmpty(){
        std::cout << "暂无数据" << '\n';
    };

    void printMenu() {
    system("cls"); // Windows 清屏，保持界面干净
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "       📝 任务清单管理系统 v1.0\n";
    std::cout << "========================================\n";
    std::cout << "[1] 查看所有任务\n";
    std::cout << "[2] 添加新任务\n";
    std::cout << "[3] 修改任务\n";
    std::cout << "[4] 删除任务\n";
    std::cout << "[5] 切换排序模式\n";
    // std::cout << "[6] 保存数据到文件\n";
    std:: cout << "[0] 保存并退出程序\n";
    std::cout << "----------------------------------------\n";
    std::cout << "请选择操作 (0-6): ";
}

    void printOptionMenu(std::string str){
        std::cout << "\n";
        std:: cout << "[0] 返回\n";
        std::cout << "[1] 继续" << str <<"\n";                
    }

    void printSortMenu(){
        std::cout << "[1] 默认模式\n";
        std::cout << "[2] ddl模式\n";
        std::cout << "[3] 优先度模式\n";
        std::cout << "[0] 返回\n";
    }

    int getChoice() {
        int choice;
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "❌ 请输入有效数字！请重新选择: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空输入缓冲区
        return choice;
    }

    template<typename T>        
    bool safeInput(T& value) {
        std::string line;
        if (!std::getline(std::cin, line)) return false;
        std::stringstream ss(line);
        return (ss >> value) && (ss.eof()); // 确保整行都是有效数字
}
    Task_data inputTask() {
        Task_data task{};
        std::string line;

        std::cout << "输入任务ID: ";
        while (!safeInput(task.id)) {
            std::cout << "❌ ID必须是整数，请重新输入: ";
        }

        std::cout << "输入任务标题: ";
        std::getline(std::cin, task.title); // getline 能读空格

        std::cout << "输入任务备注: ";
        std::getline(std::cin, task.note);

        std::cout << "输入起始时间 格式: YYYYMMDDHHMM: ";
        while (!safeInput(task.startline)) {
            std::cout << "❌ 起始时间必须是整数（如 202512221430），请重新输入: ";
        }

        std::
        cout << "输入截止时间 格式: YYYYMMDDHHMM: ";
        while (!safeInput(task.deadline)) {
            std::cout << "❌ 截止时间必须是整数，请重新输入: ";
        }

        std::cout << "输入优先度 (1-10): ";
        while (!safeInput(task.priority) || task.priority < 1 || task.priority > 10) {
            std::cout << "❌ 优先度必须是1~10之间的整数，请重新输入: ";
        }

        task.finished = false; // 默认未完成

        std::cout << "\n✅ 任务信息录入完成！\n";
        return task;
    }
}

