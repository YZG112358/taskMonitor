#include "AlertSender.hpp"
#include "AlertTrigger.hpp"
#include <stdio.h>
#if(WIN32)

#else
#include <unistd.h>
#endif
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xinclude.h>
#include <libxml2/libxml/xmlIO.h>
#include <libxml2/libxml/xmlreader.h>
#include <libxml2/libxml/xpath.h>

struct emailInfo{
    string usrname;
    string password;
    string from;
    string to;
    string server;
    string subject; 
};


void initialInfo(emailInfo& info, xmlAttr *attr){
    info.usrname = read_c_str(attr->children->content); attr = attr->next;
    info.password = read_c_str(attr->children->content); attr = attr->next;
    info.from = read_c_str(attr->children->content); attr = attr->next;
    info.to = read_c_str(attr->children->content); attr = attr->next;
    info.server = read_c_str(attr->children->content); attr = attr->next;
    info.subject = read_c_str(attr->children->content); attr = attr->next;
}

void initialSender(emailInfo& info, AlertSender& sender){
    sender.setUsrName(info.usrname);
    sender.setPassWord(info.password);
    sender.setFrom(info.from);
    sender.setTo(info.to);
    sender.setServer(info.server);
    sender.setSubject(info.subject);
}

void initalTrigger(AlertTrigger& trigger, xmlAttr *attr){
    while (attr){
        string b = read_c_str(attr->children->content);
        attr = attr->next;
        int a = stoi(read_c_str(attr->children->content));
        task* new_task = new task(a, b);
        trigger.addTask(*new_task);
        delete new_task;
        attr = attr->next;
    }
}

int main(){
    AlertTrigger trigger;
    AlertSender sender;
    emailInfo info;

    xmlInitParser();
    LIBXML_TEST_VERSION
    xmlDoc *doc = xmlParseFile( "config.xml" );

    xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );

    xmlXPathObject * xpathObj =
    xmlXPathEvalExpression( (xmlChar*)"/config/sender", xpathCtx );
    xmlNode *node = xpathObj->nodesetval->nodeTab[0];
    xmlAttr *attr = node->properties;
        
    xmlXPathObject * xpathObj_t =
    xmlXPathEvalExpression( (xmlChar*)"/config/trigger", xpathCtx );
    xmlNode *node_t = xpathObj_t->nodesetval->nodeTab[0];
    xmlAttr *attr_t = node_t->properties;
    
    initialInfo(info, attr);
    initalTrigger(trigger, attr_t);
    
    cout << "Using " << info.usrname << " to send email" << endl;
        
    initialSender(info, sender);
     
    while (1){    
        vector<task> temp = trigger.checkList();
        if (temp.size()){
            for (size_t i = 0; i < temp.size(); i++){
                string message = "Task: " + temp[i].name + " Pid: " + to_string(temp[i].pid) + " has been finished!";
                sender.setMessage(message);
                sender.sendEmail();
            }
        }
        sleep(5);
        cout << "monitoring" << endl;
    }
}
