#include <iostream>
#include <windows.h> 
#include <cstdlib>
#include <sstream>
#include "Task.hpp"
#include "TaskIO.hpp"
#include "read.h"

int main(){

    Task_Stru taskManager;
    const std::string filename = "tasks.txt";

    std::cout << "程序启动中……\n";
    if (IO_File::loadData(taskManager, filename)) {
        std::cout << "✅ 数据加载成功\n";
    }else{
        IO_File::saveData(taskManager, filename);       // 自动创建空的 tasks.txt
    }
    Sleep(2000);

    //主逻辑
    
    int choice = 7;
    while (choice)
    {
        IO::printMenu();
        choice = IO::getChoice();

        switch (choice)
        {
        case 1:{
            system("cls");
            std::cout << "\n【所有任务列表】\n";
            taskManager.PrintList();
            system("pause");  
            break;
        }
        case 2:{
            int insertChoice = 1;
            while (insertChoice)
            {
                system("cls");
                taskManager.PrintList();
                taskManager.InsertNode(IO::inputTask());
                system("cls");
                taskManager.PrintList();
                IO::printOptionMenu("添加新任务");
                insertChoice = IO::getChoice();
            }
            break;
        }
        case 3:{
            int EditChoice = 1;
            while (EditChoice)
            {
                system("cls");
                taskManager.PrintList();
                int EditID = -1;
                std::cout << "请选择要修改的任务ID: ";
                std::cin >> EditID;
                if (taskManager.EditNode(EditID))
                {
                    system("cls");
                    taskManager.PrintList();
                    std::cout << "修改成功\n";
                }else{
                    system("cls");
                    taskManager.PrintList();
                    std::cout <<"修改失败，未找到该节点\n";
                }
                IO::printOptionMenu("修改任务");
                EditChoice = IO::getChoice();
            }
            break;
        }

        case 4:{
            int deleteChoice = 1;
            while (deleteChoice){
                system("cls");
                taskManager.PrintList();
                int deleteID = -1;
                std::cout << "请选择要删除的任务ID: ";
                std:: cin >> deleteID;
                if(taskManager.DeleteNode(deleteID)){
                    system("cls");
                    taskManager.PrintList();
                    std::cout <<"删除成功\n";
                }else{
                    system("cls");
                    taskManager.PrintList();
                    std::cout <<"删除失败，未找到该节点\n";
                }
                
                IO::printOptionMenu("删除任务");
                deleteChoice = IO::getChoice();
            }
            break;
        }

            
        case 5:
            //庄sir 靠你了
            break;
        case 6:
            IO_File::saveData(taskManager, filename);
            Sleep(1500);
            break;

        default:
            break;
        }
    }
    
    return 0;
}
