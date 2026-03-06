#include <iostream>
using namespace std;

class IFileOpe
{
public:
    IFileOpe() = default;
    virtual void openFile() = 0;
    virtual void closeFile() = 0;

    virtual ~IFileOpe() = default;
};

class ParseFile : public IFileOpe
{
public:
    void openFile() override
    {
        cout << "File opened for parsing." << endl;
    }

    void closeFile() override
    {
        cout << "Writing parsed data to file." << endl;
    }
};

class ParseXMLFile : public IFileOpe
{
public:
    void openFile() override
    {
        cout << "File opened for XML parsing." << endl;
    }

    void closeFile() override
    {
        cout << "Writing XML parsed data to file." << endl;
    }
};

template <typename T>
class FileOpeFactory
{
public:
    shared_ptr<IFileOpe> createObject()
    {
        return make_shared<T>();
    }
};

int main()
{
    FileOpeFactory<ParseFile> parseFileFactory;
    FileOpeFactory<ParseXMLFile> parseXMLFileFactory;

    shared_ptr<IFileOpe> parsefileObject = parseFileFactory.createObject();
    shared_ptr<IFileOpe> parseXMLfileObject = parseXMLFileFactory.createObject();

    parsefileObject->openFile();
    parseXMLfileObject->openFile();
    parsefileObject->closeFile();
    parseXMLfileObject->closeFile();

    return 0;
}