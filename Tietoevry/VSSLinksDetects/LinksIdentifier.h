#ifndef LINKS_IDENTIFIER
#define LINKS_IDENTIFIER

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <stdlib.h>
#include <map>
#include <unordered_map>
#include <vector>
#include <ftw.h>
#include <fnmatch.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <set>
#include <sstream>
#include <algorithm>
using namespace std;

class ProjectsList;

// Callback function, to register in ftw function to get the directory structure
int callback(const char *fpath, const struct stat *sb, int typeflag);

void scan(ProjectsList &ptr, const char *path);

// This class can be improved to singleton design pattern
class ErrorHandle
{
    void PrintErr(string msg);
    bool IsPathExist();
    string path;
    int numberOfArg;

public:
    ErrorHandle(char *path[], int argc);
    void validation();
};

// ProjectsList to lists the common file links between different projects
class ProjectsList
{
    // key -> filename, Path -> value
    // To store all the paths which have common file name
    unordered_map<string, vector<string>> commonProjectsSharingFiles;

    // To store samename file which has same content.
    unordered_multimap<string, vector<string>> mm;

    // to store the Command line argument given path, for scanning the Tree Directory
    string path;

    // To store the Directory path which have to common file names.
    void pushback(string filename, string path);
    // For comparing the file, to identify the links
    bool comparefiles(string, string);

    // to store the filename and its corresponding directory names.
    friend void scan(ProjectsList &, const char *);

public:
    ProjectsList(char *path);
    ProjectsList(const ProjectsList &obj) = default;
    ProjectsList &operator=(const ProjectsList &obj) = default;
    ~ProjectsList() = default;

    // Exposed method to find the links to identify the common file in the directory structure
    void findLinks();

    // For displaying the links of files in different projects
    void DisplayLinks();
};
#endif // LINKS_IDENTIFIER
