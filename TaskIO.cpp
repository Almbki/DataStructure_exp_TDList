#include "TaskIO.hpp"
#include "Task.hpp"
#include <iostream>
#include <string>


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
}

