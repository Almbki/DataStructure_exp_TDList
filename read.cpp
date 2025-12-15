#include "read.h"
string trim(const string& s) {
    size_t l = s.find_first_not_of(" \t\r\n");
    size_t r = s.find_last_not_of(" \t\r\n");
    if (l == string::npos) return "";
    return s.substr(l, r - l + 1);
}
vector<string> split(const string& s, char delim) {
    vector<string> res;
    string item;
    stringstream ss(s);
    while (getline(ss, item, delim)) {
        res.push_back(trim(item));
    }
    return res;
}
bool validateDateTimeFormat(const string& s) {
    if (s.size() != 12) return false;
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}
bool loadDataFromFile(Task_Stru& manager, bool /*loadCompleted*/, const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) return false;
    manager.createList(); //清空
    string line;
    while (getline(fin, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        vector<string> f = split(line, DELIMITER);
        if (f.size() < 7) continue;

        Task_data t;
        t.id        = stoi(f[0]);
        t.title     = f[1];
        t.priority  = stoi(f[2]);
        t.startline = stoll(f[3]);
        t.deadline  = stoll(f[4]);
        t.finished  = (f[5] == "1");
        t.note      = f[6];

        manager.InsertNode(t);
    }

    fin.close();
    return true;
}
bool saveDataToFile(Task_Stru& manager, bool saveCompleted, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) return false;

    fout << "# id|title|priority|startline|deadline|finished|note\n";

    TNode_head head = manager.getHead();
    if (!head) return true;

    for (TNode_elem* p = head->first; p; p = p->next) {
        const Task_data& t = p->task;

        if (t.finished != saveCompleted) continue;

        fout << t.id << DELIMITER
             << t.title << DELIMITER
             << t.priority << DELIMITER
             << t.startline << DELIMITER
             << t.deadline << DELIMITER
             << (t.finished ? "1" : "0") << DELIMITER
             << t.note << "\n";
    }

    fout.close();
    return true;
}
// 创建任务
Task_data createTask(const string& title, const string& note,
                     int deadline, int priority, bool finished) {
    Task_data t{};
    t.id = 0;
    t.title = title;
    t.note = note;
    t.startline = stoll(getCurrentDateTime());
    t.deadline = deadline;
    t.priority = (priority < 1 || priority > 10) ? 5 : priority;
    t.finished = finished;
    return t;
}