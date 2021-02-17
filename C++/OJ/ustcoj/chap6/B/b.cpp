//  All are files. Some(dir) point to some files, while others(single file) point to NULL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define EACH_LINE 22   //  the most length of a file, also the most length of each line
#define MOST_FILES 100 //  the largest number of files in a directory

using namespace std;

typedef struct file
{
    char name[EACH_LINE]; //  the name of a file(other characteristic can be added)
} File;

typedef struct list //  the list of files in a directory, including directories
{
    struct file member[MOST_FILES];    //  members in the directory, including directories
    int num_member;                    //  the number of members in the directory, including directoriess
    struct list *point_to[MOST_FILES]; //  directories here point to their own list
    int num_list;                      //  number of directories or number of list pointed
} List;

//  function:   make the file & directory tree, create the containment relationship
//  parameters:
//      dir:    the list belond to the directory pointing to this list
//      judgement:  whether the directory is root
//                  y?  * as the terminator in input
//                  n?  ] as the terminator in input
//  return:
//      make the list under or belonging to the directory pointing to the list
void make_tree(List *dir, const char judgement[2]);

//  function:   print the tree. (More precisely, print the list under the directory)
//  parameters:
//      dir:    the list belond to the directory pointing to this list
//      depth:  the number of "|     " needed to be printed
//  return:     print the tree in a recursive way
void print_tree(List *dir, int depth);

//  function:   initialize the dir
//  parameters:
//      dir:    the list belond to the directory pointing to this list
//  return:     num_member, num_list & point_to initialized
void Initialize_list(List *dir);

//  function:   compare the file in lexicographic order
//  parameters:
//      p1, p2: will be changed to char * (two strings)
//  return:
//      p1 < p2, negative value
//      p1 > p2, positive value
//      p1 = p2, 0
int cmp(const void *p1, const void *p2);

int main(void)
{
    int num = 1; //  num:    the number of groups

    do
    {
        List *root = new List; //  the root (also a directory)
        Initialize_list(root);
        make_tree(root, "*"); //  root ends with *
        getchar();            //  read '\n' so that # can be read later

        printf("DATA SET %d:\n", num);
        printf("ROOT\n");
        print_tree(root, 0); //  0 "|    " should be output if it's a file in root
        putchar('\n');

        num++;
    } while ((cin.peek()) != '#'); //  have a try to read. if it's #, that means the end of the input
    return 0;
}

void make_tree(List *dir, const char judgement[2])
{
    char name[EACH_LINE] = "";                //  the name input
    char files[MOST_FILES][EACH_LINE] = {""}; //  all files, not including directories. this array will be sorted later
    int num_files = 0;                        //  the number of files, not including directories. it's necessary when qsort()

    while ((scanf("%s", name)) && ((strcmp(name, judgement) != 0))) //  if the input is the same as judgement, it means the end of the dir or root
    {
        if (name[0] == 'd')     //  directory input
        {
            strcpy(dir->member[dir->num_member].name, name);
            
            List *new_dir = new List;   //  create a new list under this directory input
            Initialize_list(new_dir);

            strcpy(new_dir->member[0].name, name);      //  the first member of the list is the directory input
            dir->point_to[dir->num_member] = new_dir;   //  the original directory list should have the link to the new directory list
            make_tree(new_dir, "]");                    //  make the list under the directory input. ] as the terminator
            (dir->num_member)++;                        //  the number of files and directories increases
            (dir->num_list)++;                          //  the number of lists pointed increases
        }
        else if (name[0] == 'f')                        //  file input
        {
            strcpy(files[num_files], name);             //  store it to the files array temporarily to sort them
            num_files++;                                //  the number of files needed to be sorted increases
        }
    }

    qsort(files, num_files, sizeof(char) * EACH_LINE, cmp);                 //  sort files array in lexicographic order

    for (int i = dir->num_member; i < dir->num_member + num_files; i++)     //  store files to the list of the original directory
    {
        strcpy(dir->member[i].name, files[i - dir->num_member]);
        dir->point_to[dir->num_member] = NULL;                              //  files point to nothing
    }
    dir->num_member += num_files;                                           //  the total number of files & directories in the list
}

int cmp(const void *p1, const void *p2)
{
    return strcmp((char *)p1, (char *)p2);
}

void print_tree(List *dir, int depth)
{
    for (int i = 0; i < dir->num_member; i++)       //  print the files and directories
    {
        if (dir->member[i].name[0] == 'd')          //  direcotries need "|     " one more time than files
        {
            printf("|     ");
        }

        for (int j = 0; j < depth; j++)             //  files and directories both need depth "|     "
        {
            printf("|     ");
        }

        printf("%s\n", dir->member[i].name);        //  print the member
        if (dir->point_to[i] != NULL)               //  i member is a direcoty and the list under it is needed to be printed
        {
            print_tree(dir->point_to[i], depth + 1);    //  "|    " is needed to be printed one more time
        }
    }
}

void Initialize_list(List *dir)
{
    dir->num_member = 0;
    dir->num_list = 0;
    for (int i = 0; i < MOST_FILES; i++)    //  all point_to are set NULL
    {
        dir->point_to[i] = NULL;
    }
}