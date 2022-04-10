#include"LinksIdentifier.h"

int main(int argc, char **argv)
{
    //In case of wrong usage handling, i.e. 1 arg, non absolute path, path not present
    ErrorHandle errHandle(argv, argc);
    errHandle.validation();

    //If errHandle.validation() succeeds it means, path provided for the files is valid.
    //We can do further process to identify the links of files in different projects
    ProjectsList projectl(argv[1]);
    projectl.findLinks();
    projectl.DisplayLinks();
}