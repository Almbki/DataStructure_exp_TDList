#ifndef READ
#define READ_H

#include "Task.hpp"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// 文件配置
const string DEFAULT_FILENAME = "tasks.txt";
const char DELIMITER = '|';
TList* loadData(const string& filename = DEFAULT_FILENAME);
bool saveData(TList* taskList, const string& filename = DEFAULT_FILENAME);
vector<string> split(const string& str, char delimiter);
string trim(const string& str);
bool validateDeadline(const string& deadlineStr);

#endif // READ_H