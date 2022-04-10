#include "LinksIdentifier.h"

// ErrorHandle class Definations starts
ErrorHandle::ErrorHandle(char *path[], int argc)
{
    if (argc > 1)
        this->path = string(path[1]);
    numberOfArg = argc;
}

void ErrorHandle::PrintErr(string msg)
{
    cout << msg << endl;
    exit(-1);
}

bool ErrorHandle::IsPathExist()
{
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

void ErrorHandle::validation()
{
    if (numberOfArg < 2)
    {
        PrintErr("Wrong Usage\nCorrect Usage: linksIdentifier absolutePath\ne.g.\n./linskIdentifier /home/rj1aditya/Dev/Tietoevry/WorkStation");
    }

    if (path[0] != '/')
    {
        PrintErr("Wrong Usage\nAbsolute path should begin with '/'");
    }

    if (!IsPathExist())
    {
        PrintErr("Wrong Usage\nGiven Absolute path not present");
    }
}
// ErrorHandle class Definations Ends

// ProjectsList class Definations starts
string filters[5] = {"*.cpp", "*.h", "*.cpp", "*.rc"};
ProjectsList *objPtr = NULL;

//Callback function, to register in ftw function to get the directory structure
int callback(const char *fpath, const struct stat *sb, int typeflag)
{
    /* if it's a file */
    if (typeflag == FTW_F)
    {
        int i;
        /* for each filter, */
        for (i = 0; i < sizeof(filters) / sizeof(filters[0]); i++)
        {
            /* if the filename matches the filter,{"*.cpp", "*.h", "*.cpp", "*.rc"}; */
            if (fnmatch(filters[i].c_str(), fpath, FNM_CASEFOLD) == 0)
            {
                scan(*objPtr, fpath);
                break;
            }
        }
    }
    /* tell ftw to continue */
    return 0;
}

ProjectsList::ProjectsList(char *path)
{
    this->path = string(path);
    objPtr = this;
    chdir((const char *)path);
    ftw("./", callback, 16);
}

void ProjectsList::findLinks()
{
    for (auto it = commonProjectsSharingFiles.begin(); it != commonProjectsSharingFiles.end(); it++)
    {
        auto vec = it->second;
        auto filename = it->first;

        vector<int> marked(vec.size(), -1);
        vector<string> pro;

        for (int i = 0; i < vec.size(); i++)
        {
            if (marked[i] == -1)
            {
                pro.push_back(vec[i]);
                marked[i] = 1;
            }
            else
                continue;

            for (int j = i + 1; j < vec.size(); j++)
            {
                if (marked[j] == -1 && comparefiles(vec[i]+"/"+filename, vec[j]+"/"+filename))
                {
                    marked[j] = 1;
                    pro.push_back(vec[j]);
                }
            }
            mm.insert({filename, pro});
            pro.clear();
        }
    }
    commonProjectsSharingFiles.clear();
    for (auto itr = mm.begin(); itr != mm.end(); ++itr)
    {
        auto vec = itr->second;
        sort(vec.begin(), vec.end());
        string key;
        for (auto a : vec)
        {
            key += a + "$";
        }
        commonProjectsSharingFiles[key].push_back(itr->first);
    }
}

//For displaying the links of files in different projects
void ProjectsList::DisplayLinks()
{
    string outfile = "fileLinksInProject_" + to_string(getpid()) + ".txt";
    ofstream fout;

    fout.open(outfile);

    for(auto it = commonProjectsSharingFiles.begin(); it != commonProjectsSharingFiles.end(); it++)
    {
        string paths = it->first;
        stringstream ss(paths);
        string str;
        while(getline(ss, str, '$'))
        {
            cout<<str<<endl;
            fout<<str<<'\n';
        }
        auto vec = it->second;
        
        for(int i = 0; i < vec.size(); i++)
        {
            cout<<'\t'<<vec[i]<<endl;
            fout<<'\t'<<vec[i]<<'\n';
        }
    }
    fout.close();
    cout<<endl<<"########################################################"<<endl;
    cout<<"Output log file:["<<outfile<<"]is saved in directory: "<<path<<endl;
}


//to store the filename and its corresponding directory names.
void scan(ProjectsList &ptr, const char *path)
{
    string newPath = string(path);

    // taking first root folder
    int pos = newPath.substr(2).find("/");

    // taking file name
    auto it = newPath.rbegin();

    string filename;
    while (*it != '/')
    {
        filename = *it + filename;
        it++;
    }

    newPath = newPath.substr(0, newPath.length() - filename.length());

    ptr.pushback(filename, newPath);
}

void ProjectsList::pushback(string filename, string path)
{
    commonProjectsSharingFiles[filename].push_back(path);
}

//ProjectsList::comparefiles compare the files content.
bool ProjectsList::comparefiles(string file1, string file2)
{

    fstream f1, f2;
    char name[20], c1, c2;
    int flag=3;

    f1.open(file1,ios::in);
    if(!f1)
        return false;

    f2.open(file2,ios::in);
    if(!f2)
    {
        f1.close();
        return false;
    }

    while(1){
        c1=f1.get();
        c2=f2.get();
        if(c1!=c2){
            flag=0;
            break;
        }
        if((c1==EOF)||(c2==EOF))
            break;
    }
    f1.close();
    f2.close();

    if(flag)
        return true;

    return false;
}

// ProjectsList class Definations ends