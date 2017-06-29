#ifndef ALERTTRIGGER_HPP
#define ALERTTRIGGER_HPP

#include <vector>
#include <string>
#include <iostream>
#include "utils.hpp"
#include <regex>

using namespace std;
struct task{
    int pid;
    string name;
    task(int a, string b) : pid(a), name(b){}
};

class AlertTrigger{
public:
    void addTask(task t){
       taskList.push_back(t);
    }    
    void printList(){
        auto it = taskList.begin();
        int i = 0;
        for (; it != taskList.end(); it++){
            cout << "Task " << i << ": " << endl;
            cout << "pid: " << it->pid << endl;
            cout << "name: " << it->name << endl;
            i++;
        }
    }
    vector<task> checkList(){
        string output = exec("ps");
        vector<task> retval;
        auto it = taskList.begin();
        for (; it != taskList.end(); it++){
            regex n(it->name);
            regex p(to_string(it->pid));
            if (regex_match(output.begin(), output.end(), n) || regex_match(output.begin(), output.end(), p)){
                retval.push_back(*it);
                taskList.erase(it);
                it--;
            }
            else{
                // has the task running    
            }
        }
        return retval;
    } 
    

private:
    vector<task> taskList;    
    
};



#endif
