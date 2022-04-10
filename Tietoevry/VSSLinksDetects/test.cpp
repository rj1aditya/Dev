#include<iostream>
#include<fstream>
using namespace std;

int main(){
    fstream f1, f2;
    char name[20], c1, c2;
    int flag=3;

    f1.open("./file1.txt",ios::in);
    if(!f1)
        cout<<"File can't be opened"<<endl;

    f2.open("./file2.txt",ios::in);
    if(!f2)
        cout<<"File can't be opened"<<endl;

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
        cout<<"Files are same.";
    else
        cout<<"Files are not same.";

    return 0;
}
