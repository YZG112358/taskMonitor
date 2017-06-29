#include "AlertSender.hpp"
#include "AlertTrigger.hpp"
#if(WIN32)

#else
#include <unistd.h>
#endif
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xinclude.h>
#include <libxml2/libxml/xmlIO.h>


int main(){
    AlertTrigger trigger;
    AlertSender sender;
    xmlDocPtr doc = xmlReadMemory("config.xml");
    if (doc == NULL){
        cout << "No such file" << endl;
    }

    while (1){
        sender.setUsrName("billytaskalert@gmail.com");
        sender.setPassWord("UIUC61802");
        sender.setFrom("billytaskalert@gmail.com");
        sender.setTo("guyongzhou@gmail.com");
        sender.setSubject("test");
        sender.setMessage("testing");
        sender.sendEmail();
    }
}
