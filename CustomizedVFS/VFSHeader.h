#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<unistd.h>
#include<io.h>

#pragma warning(disable : 4996)

#define MAXINODE            3
#define READ                1
#define WRITE               2
#define MAXFILESIZE      2048
#define REGULAR             1
#define SPECIAL             2
#define DIRECTORY           3
#define START               0
#define CURRENT             1
#define END                 2
#define MEM_ERR            -4

typedef struct superblock
{
    int     TotalInodes;
    int     FreeInodes;
}SUPERBLOCK, * PSUPERBLOCK;

typedef struct inode
{
    char    FileName[50];
    int     InodeNumber;
    int     FileSize;
    int     FileActualSize;
    int     FileType;
    char*   Buffer;
    int     LinkCount;
    int     ReferenceCount;
    int     Permission;
    struct inode* pnext;
   
}INODE, * PINODE;

typedef struct filetable
{
    int     readoffset;
    int     writeoffset;
    int     count;
    int     mode;
    PINODE  ptrinode;
}FILETABLE, * PFILETABLE;

typedef struct ufdt
{
    PFILETABLE      ptrfiletable;
}UFDT;

/* Function Declarations */
int CountInode();
void man(char*);
void DisplayHelp();
void CreateDILB();
void InitialiseSuperBlock();
int GetFDFromName(char*);
PINODE Get_Inode(char*);
int CreateFile(char*, int);
int rm_File(char*);
int rm_all();
int ReadFile(int, char*, int);
int WriteFile(int, char*, int);
int OpenFile(char*, int);
void CloseFileByFD(int);
int CloseFileByName(char*);
int CloseAllFiles();
int LseekFile(int, int, int);
void ls_file();
int fstat_file(int);
int stat_file(char*);
int truncate_File(char*);
void DeallocteResource();
int CopyFile(char*, char*);
