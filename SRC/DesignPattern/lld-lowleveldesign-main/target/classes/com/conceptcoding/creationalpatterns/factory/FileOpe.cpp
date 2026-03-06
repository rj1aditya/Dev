//
// Created by Aditya Jain on 20/01/26.
//

#include "FileOpe.h"


int main() {
    // IFileOpe *xmlPtr = new FileOpeXML();
    // xmlPtr->read();
    // xmlPtr->write();
    // xmlPtr->close();


    client xmlclient;
    IFileOpe* xmlPtr = xmlclient.createObject(new FileOpeXMLConcreateFactory());
    xmlPtr->read();
    xmlPtr->write();
    xmlPtr->close();

    delete xmlPtr;
}