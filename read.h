#ifndef READ_H
#define READ_H
#include "Task.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

// 文件配置
const string ACTIVE_TASKS_FILE = "active_tasks.txt";     // 未完成任务文件
const string COMPLETED_TASKS_FILE = "completed_tasks.txt"; // 已完成任务文件
const char DELIMITER = '|';                              // 字段分隔符

// 主要数据持久化函数
bool loadDataFromFile(Task_Stru& taskManager, bool loadCompleted, const string& filename = ACTIVE_TASKS_FILE);
bool saveDataToFile(Task_Stru& taskManager, bool saveCompleted, const string& filename = ACTIVE_TASKS_FILE);

// 辅助函数
string trim(const string& str);
vector<string> split(const string& str, char delimiter);
string getCurrentDateTime();                     // 获取当前日期时间
int getNextAvailableId(Task_Stru& taskManager, bool checkCompleted = false); // 获取下一个可用ID
bool validateDateTimeFormat(const string& datetimeStr); // 验证日期时间格式
int stringToDateTime(const string& datetimeStr);  // 字符串转时间戳
string dateTimeToString(int datetime);           // 时间戳转字符串
bool isLeapYear(int year);                       // 判断闰年
bool isValidDate(int year, int month, int day);  // 验证日期有效性
bool isValidTime(int hour, int minute);         // 验证时间有效性

// 任务创建辅助函数
Task_data createTask(const string& title, const string& note = "", 
                     int deadline = 0, int priority = 5, bool finished = false);
bool moveTaskToCompleted(Task_Stru& activeManager, Task_Stru& completedManager, int taskId);
bool moveTaskToActive(Task_Stru& activeManager, Task_Stru& completedManager, int taskId);

// 文件管理函数
bool backupDataFiles();
void listDataFiles();
bool clearDataFile(const string& filename);

#endif // READ_H