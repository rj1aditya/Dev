//
// Created by Aditya Jain on 20/01/26.
//

#ifndef FACTORY_FILEOPE_H
#define FACTORY_FILEOPE_H
#include<iostream>
using namespace  std;

class IFileOpe {
public:
    IFileOpe() {

    }
    virtual ~IFileOpe() {}
    virtual int read() = 0;
    virtual int write() = 0;
    virtual int close() = 0;
};

class FileOpeXML: public IFileOpe {
public:
    FileOpeXML() {

    }

    virtual int read() override {
        cout<<"XML read"<<endl;
    }
    virtual int write() override {
        cout <<"XML write"<<endl;
    }

    virtual int close() override {
        cout <<"XML close"<<endl;
    }

    virtual ~FileOpeXML() {
        cout <<"XML destroy"<<endl;
    }
};

class FileOpeJSON: public IFileOpe {
public:
    FileOpeJSON() {

    }

    virtual int read() override {
        cout<<"JSON read"<<endl;
    }
    virtual int write() override {
        cout <<"JSON write"<<endl;
    }

    virtual int close() override {
        cout <<"JSON close"<<endl;
    }

    virtual ~FileOpeJSON() {
        cout <<"JSON destroy"<<endl;
    }
};


class FileOpeFactory {

    public:
    FileOpeFactory(){

    }

    virtual IFileOpe* createObject() = 0;

    virtual ~FileOpeFactory() {

    }
};

class FileOpeXMLConcreateFactory: public FileOpeFactory {
public:
    FileOpeXMLConcreateFactory() {

    }

    virtual IFileOpe* createObject() override {
        return new FileOpeXML();
    }

    ~FileOpeXMLConcreateFactory() {

    }
};

class FileOpeJSONConcreateFactory: public FileOpeFactory {
public:
    FileOpeJSONConcreateFactory() {

    }

    virtual IFileOpe* createObject() override {
        return new FileOpeJSON();
    }

    ~FileOpeJSONConcreateFactory() {

    }
};

class client {
public:
    client() {}
    virtual ~client() {}

    IFileOpe* createObject(FileOpeFactory* obj) {
        return obj->createObject();
    }
};
#endif //FACTORY_FILEOPE_H