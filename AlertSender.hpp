#ifndef ALERTSENDER_HPP
#define ALERTSENDER_HPP

#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <isotream>
using namespace std;
class AlertSender{
public:
    AlertSender(){
        _server = "smtp.gmail.com:587";
    }
    void setUsrName(string name){
        _usrname = name;
    }
    void setPassWord(string password){
        _password = password;
    }
    void setFrom(string from){
        _from = from;
    }
    void setTo(string to){
        _to = to;
    }
    void setSubject(string subject){
        _subject = subject;
    }
    void setServer(string server){
        _server = server;
    }
    bool sendEmail(){
        string command;
        command += "sendemail -f ";
        command += _from;
        command += " -t ";
        command += _to;
        command += " -m ";
        command += _message;
        command += " -u ";
        command += _subject;
        command += " -s ";
        command += _server;
        command += " -xu ";
        command += _usrname;
        command += " -xp ";
        command += _password;

        int ret = system(command.c_str());
        if (ret == 0){
            cout << "sending succeed " << endl;
            return true;
        }
        else{
            cout << "failed " << endl;
            return false;
        }
    }

private:
    string _usrname;
    string _password; 
    string _from;
    string _to;
    string _subject;
    string _message;
    string _server;
};


#endif






