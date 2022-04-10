New changes:

1. ProjectsList::findLinks is modified to handled if the different name file are present in the same number of directory.
2. Comparision of the 2 files content is done by charcter wise.

#############################################################################################################################################
Design:

A. 2 class are created named ErrorHandle and ProjectsList.
A.1 ErrorHandle are created for handling the wrong usage or invalid path
A.2 ProjectsList are created to find those links by identifying similar files directly in the file system.

Source File name:
LinksIdentifier.h, LinksIdentifier.cpp, main.cpp, compile.sh

Useful
Readme.txt

1. 
Scan the directory first and take those file along with absolute path which has {"*.cpp", "*.h", "*.cpp", "*.rc"} extention, then by splitting the filename and its path stored the result in the map( filename as an key, and path as a value in a vector)
e.g. 
filename1 -> /root/user1/aditya/Dev/Project1/, /root/user1/aditya/Dev/Project2/, /root/user1/aditya/Dev/Project3/
filename2 -> /root/user1/aditya/Dev/Project1/, /root/user1/aditya/Dev/Project2/, /root/user1/aditya/Dev/Project3/
filename3 -> /root/user1/aditya/Dev1/Project1/, /root/user1/aditya/Dev1/, /root/user1/aditya/Dev1/

>>>>>>>>>>>>>>>>>>>>>>>>>>>This point will be done when the instance of the class will be created.

2. 
it is possible same name files are not same by their content, so same name file content will be compared, and stored in multimap those filename and path will be store which have same content.
e.g.
filename1 -> /root/user1/aditya/Dev/Project1/, /root/user1/aditya/Dev/Project2/ key->ABC
filename1 -> /root/user1/aditya/Dev/Project3/                                   key->ACB
filename2 -> /root/user1/aditya/Dev/Project1/, /root/user1/aditya/Dev/Project2/ key->ABC
filename3 -> /root/user1/aditya/Dev1/Project1/, /root/user1/aditya/Dev1/        key->BAC
filename4 -> /root/user1/aditya/Dev/Project1/, /root/user1/aditya/Dev/Project2/, /root/user1/aditya/Dev/Project3/ key->CBA

>>>>>>>>>>>>>>>>>>>>>>>>>>>This point will be done, using ProjectsList::findLinks method.
3.
As per requirement, projects which has common file should appear together.

e.g.
As mentioned in the step no 2, filename1 and filename2 are present in /root/user1/aditya/Dev/Project1/ and /root/user1/aditya/Dev/Project2/
/root/user1/aditya/Dev/Project1/
/root/user1/aditya/Dev/Project2/
                                    filename1
                                    filename2
filename1 is present in /root/user1/aditya/Dev/Project3/
/root/user1/aditya/Dev/Project3/
                                    filename1
									
filename4 is present in /root/user1/aditya/Dev/Project1/, /root/user1/aditya/Dev/Project2/ and /root/user1/aditya/Dev/Project3/
/root/user1/aditya/Dev/Project1/
/root/user1/aditya/Dev/Project2/
/root/user1/aditya/Dev/Project3/
                                    filename4

filename3 is present in /root/user1/aditya/Dev1/Project1/ and /root/user1/aditya/Dev1/
/root/user1/aditya/Dev1/Project1/
/root/user1/aditya/Dev1/
                                    filename3

>>>>>>>>>>>>>>>>>>>>>>>>>>>To display the output and to save the output, ProjectsList::DisplayLinks() method used.
################################################################################################################################################

OUTPUT:

1. output will be display on the console as well as output will be store in the file fileLinksInProject_pid.txt file in the (command line argument path) given path.

2. Given path as the argument for the tool would be considered as the root directory for all the projects, and on console and log file, paths for projects will be logged from root directory only. 

################################################################################################################################################

Usage:

./tool absolutePath

################################################################################################################################################

How to compile extention

./compile.sh

exe name: tool

###############################################################################################################################################

considerations:
1. Program is implemented on Linux platform.
2. Compiler used: g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
3. tool exe will scan the directory for files which has extention {"*.cpp", "*.h", "*.cpp", "*.rc"}

limitations 
1. If file found in the directory which has no read permission can cause the undefined behaviour[Not handled].
2. This tool is designed and tested on Linux platform, It can be portable into other OS platform however directory structure of different plantform may require the changes in the code(platform specifics).


###############################################################################################################################################