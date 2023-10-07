#include "VFSHeader.h"

UFDT         UFDTArr[MAXINODE];//global variable
SUPERBLOCK   SUPERBLOCKobj;//global variable
PINODE head = NULL;//global variable

int CountInode()
{
    return SUPERBLOCKobj.TotalInodes - SUPERBLOCKobj.FreeInodes;
}

void man(char* name)
{
    if (name == NULL)
    {
        return;
    }
    if (strcmp(name, "create") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to create new regular file\n");
        printf("USAGE:\n\tcreate File_name Permission\n");
    }
    else if (strcmp(name, "read") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to read data from regular file\n");
        printf("USAGE:\n\tread File_name No_Of_Bytes_To_Read\n");
    }
    else if (strcmp(name, "write") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to write into regular file\n");
        printf("USAGE:\n\twrite File_name\\n After this enter the data you want to enter\n");
    }
    else if (strcmp(name, "ls") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to list all contents in present directory\n");
        printf("USAGE:\n\tls\n");
    }
    else if (strcmp(name, "stat") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to display information of a file usign file name\n");
        printf("USAGE:\n\tstat File_name\n");
    }
    else if (strcmp(name, "fstat") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to display information file using file descriptor\n");
        printf("USAGE:\n\tfstat File_Descriptor\n");
    }
    else if (strcmp(name, "truncate") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to truncate(remove) all the data from file\n");
        printf("USAGE:\n\ttruncate File_name\n");
    }
    else if (strcmp(name, "open") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to open existing file\n");
        printf("USAGE:\n\topen File_name\n");
    }
    else if (strcmp(name, "close") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to close opened file(s)\n");
        printf("USAGE:\n\tclose File_name : closes File_Name file");
        printf("\n\tclose -r :close all files recursivley\n");
    }
    else if (strcmp(name, "lseek") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to change file offset\n");
        printf("USAGE:\n\tlseek File_name ChangeInOffset_StartPoint\n");
    }
    else if (strcmp(name, "rm") == 0)
    {
        printf("DESCRIPTION:\n\tUsed to delete the file\n");
        printf("USAGE:\n\trm File_name : removes File_Name");
        printf("USAGE:\n\trm -r : removes all files");
    }
    else
    {
        printf("\nERROR:No Manual Entry Available\n");
    }
}

void DisplayHelp()
{
    printf("ls        :To list out all files\n");
    printf("create    :To create a new file\n");
    printf("open      :To open the file\n");
    printf("close     :To close the file\n");
    printf("close -r  :To close all opened files\n");
    printf("read      :To read contents from a file\n");
    printf("write     :To write contents into a file\n");
    printf("stat      :To display information of file using name\n");
    printf("fstat     :To display information of file using file descriptor\n");
    printf("truncate  :To remove all data from a file\n");
    printf("rm        :To delete a file\n");
    printf("rm -r     :To delete all files recursively\n");
    printf("exit      :To terminate filesubsystem\n");
    printf("clear     :To clear the konsole\n");
}

void CreateDILB()
{
    int i = 1;//Because of LinkedList
    PINODE newn = NULL;
    PINODE temp = head;

    while (i <= MAXINODE)
    {
        newn = (PINODE)malloc(sizeof(INODE));
        if (newn == NULL)
        {
            return;
        }
        newn->LinkCount = 0;
        newn->ReferenceCount = 0;
        newn->FileType = 0;
        newn->FileSize = 0;
        newn->Buffer = NULL;
        newn->pnext = NULL;
        newn->InodeNumber = i;
        if (temp == NULL)
        {
            head = newn;
            temp = head;
        }
        else
        {
            temp->pnext = newn;
            temp = newn;
        }
        i++;
    }
    printf("DILB Created Successfully\n");
}

void InitialiseSuperBlock()
{
    int i = 0;
    while (i < MAXINODE)
    {
        UFDTArr[i].ptrfiletable = NULL;
        i++;
    }
    SUPERBLOCKobj.TotalInodes = MAXINODE;
    SUPERBLOCKobj.FreeInodes = MAXINODE;
}

int GetFDFromName(char* name)
{
    int i = 0;
    int cnt = CountInode();
    while (i < MAXINODE && cnt!=-1)
    {
        if (UFDTArr[i].ptrfiletable != NULL)
        {
            if (strcmp((UFDTArr[i].ptrfiletable->ptrinode->FileName), name) == 0)
            {
                break;
            }
            cnt--;
        }
        i++;
    }
    if (i == MAXINODE)
    {
        return -1;
    }
    else
    { 
        return i;
    }
}

PINODE Get_Inode(char* name)
{
    PINODE temp = head;
    int i = 0;
    if (name == NULL)
    {
        return NULL;
    }

    while (temp != NULL)
    {
        if (strcmp(name, temp->FileName) == 0)
            break;
        temp = temp->pnext;
    }
    return temp;//NULL for success
}

int CreateFile(char* name, int Permission)
{
    int i = 0;
    PINODE temp = head;
    if ((name == NULL) || (Permission <= 0) || (Permission > 3))
    {
        return -1;
    }
    if (SUPERBLOCKobj.FreeInodes == 0)
    {
        return -2;
    }
    if (Get_Inode(name) != NULL)
    {
        return -3;
    }
    while (temp != NULL)
    {
        if (temp->FileType == 0)
        {
            break;
        }
        temp = temp->pnext;
    }

    while (i < MAXINODE)
    {
        if (UFDTArr[i].ptrfiletable == NULL)
        {
            break;
        }
        i++;
    }
    UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));
    if (UFDTArr[i].ptrfiletable == NULL)
    {
        return -4;
    }
    UFDTArr[i].ptrfiletable->count = 1;
    UFDTArr[i].ptrfiletable->mode = Permission;
    UFDTArr[i].ptrfiletable->readoffset = 0;
    UFDTArr[i].ptrfiletable->writeoffset = 0;
    UFDTArr[i].ptrfiletable->ptrinode = temp;

    strcpy(UFDTArr[i].ptrfiletable->ptrinode->FileName, name);

    UFDTArr[i].ptrfiletable->ptrinode->FileType = REGULAR;
    UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount = 1;
    UFDTArr[i].ptrfiletable->ptrinode->LinkCount = 1;
    UFDTArr[i].ptrfiletable->ptrinode->FileSize = MAXFILESIZE;
    UFDTArr[i].ptrfiletable->ptrinode->FileActualSize = 0;
    UFDTArr[i].ptrfiletable->ptrinode->Permission = Permission;
    UFDTArr[i].ptrfiletable->ptrinode->Buffer = (char*)malloc(MAXFILESIZE);

    (SUPERBLOCKobj.FreeInodes)--;
    return i;
}

//similar to unlink
int rm_File(char* name)
{
    int fd = 0;
    fd = GetFDFromName(name);
    if (fd == -1)
    {
        return -1;
    }
    (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount)--;

    if (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount == 0)
    {
        UFDTArr[fd].ptrfiletable->ptrinode->FileType = 0;
        strcpy(UFDTArr[fd].ptrfiletable->ptrinode->FileName, "");
        UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = 0;
        UFDTArr[fd].ptrfiletable->ptrinode->Permission = 0;
        UFDTArr[fd].ptrfiletable->ptrinode->ReferenceCount = 0;
        free(UFDTArr[fd].ptrfiletable->ptrinode->Buffer);
        free(UFDTArr[fd].ptrfiletable);
    }
    UFDTArr[fd].ptrfiletable = NULL;
    (SUPERBLOCKobj.FreeInodes)++;
    return 0;
}

int rm_all()
{
    int i = 0;
    int cnt = CountInode();
    if (!CountInode())
    {
        return -1;
    }    
    while (cnt != 0)
    {
        if (UFDTArr[i].ptrfiletable != NULL)
        {
            (UFDTArr[i].ptrfiletable->ptrinode->LinkCount)--;

            if (UFDTArr[i].ptrfiletable->ptrinode->LinkCount == 0)
            {
                UFDTArr[i].ptrfiletable->ptrinode->FileType = 0;
                strcpy(UFDTArr[i].ptrfiletable->ptrinode->FileName, "");
                UFDTArr[i].ptrfiletable->ptrinode->FileActualSize = 0;
                UFDTArr[i].ptrfiletable->ptrinode->Permission = 0;
                UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount = 0;
                free(UFDTArr[i].ptrfiletable->ptrinode->Buffer);
                free(UFDTArr[i].ptrfiletable);
            }
            UFDTArr[i].ptrfiletable = NULL;
            (SUPERBLOCKobj.FreeInodes)++;
            cnt--;
        }
        i++;
    }
    return 0;
}


int ReadFile(int fd, char* arr, int isize)
{
    int read_size = 0;
    if (UFDTArr[fd].ptrfiletable == NULL)
    {
        return -1;
    }
    if (UFDTArr[fd].ptrfiletable->mode != READ && UFDTArr[fd].ptrfiletable->mode != READ + WRITE)
    {
        return -2;
    }
    if (UFDTArr[fd].ptrfiletable->ptrinode->Permission != READ && UFDTArr[fd].ptrfiletable->ptrinode->Permission != READ + WRITE)
    {
        return -2;
    }
    if (UFDTArr[fd].ptrfiletable->readoffset == UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
    {
        return -3;
    }
    if (UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR)
    {
        return -4;
    }
    read_size = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) - (UFDTArr[fd].ptrfiletable->readoffset);
    if (read_size < isize)
    {
        strncpy(arr, (UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset), read_size);
        UFDTArr[fd].ptrfiletable->readoffset = UFDTArr[fd].ptrfiletable->readoffset + read_size;
        return read_size;
    }
    else
    {
        strncpy(arr, (UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset), isize);
        UFDTArr[fd].ptrfiletable->readoffset = UFDTArr[fd].ptrfiletable->readoffset + isize;
        return isize;
    }
    
}

int WriteFile(int fd, char* arr, int isize)
{
    if (UFDTArr[fd].ptrfiletable->mode != WRITE && UFDTArr[fd].ptrfiletable->mode != READ + WRITE)
    {
        return -1;
    }

    if (UFDTArr[fd].ptrfiletable->ptrinode->Permission != WRITE && UFDTArr[fd].ptrfiletable->ptrinode->Permission != READ + WRITE)
    {
        return -1;
    }

    if (UFDTArr[fd].ptrfiletable->writeoffset == MAXFILESIZE)
    {
        return -2;
    }

    if (UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR)
    {
        return -3;
    }
    if (UFDTArr[fd].ptrfiletable->ptrinode->FileSize - UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize < isize)
    {
        return -2;
    }
    strncpy((UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->writeoffset), arr, isize);

    UFDTArr[fd].ptrfiletable->writeoffset = UFDTArr[fd].ptrfiletable->writeoffset + isize;

    UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize + isize;

    return isize;
}

int OpenFile(char* name, int mode)
{
    int i = 0;
    PINODE temp = NULL;

    if (name == NULL || mode <= 0)
    {
        return -1;
    }

    temp = Get_Inode(name);
    if (temp == NULL)
    {
        return -2;
    }

    if (temp->Permission < mode)
    {
        return -3;
    }

    while (i < MAXINODE)
    {
        if (UFDTArr[i].ptrfiletable == NULL)
        {
            break;
        }
        i++;
    }
    UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));
    if (UFDTArr[i].ptrfiletable == NULL)
    {
        return -1;
    }
    UFDTArr[i].ptrfiletable->count = 1;
    UFDTArr[i].ptrfiletable->mode = mode;
    if (mode == READ + WRITE)
    {
        UFDTArr[i].ptrfiletable->readoffset = 0;
        UFDTArr[i].ptrfiletable->writeoffset = 0;
    }
    else if (mode == READ)
    {
        UFDTArr[i].ptrfiletable->readoffset = 0;
    }
    else if (mode == WRITE)
    {
        UFDTArr[i].ptrfiletable->writeoffset = 0;
    }
    UFDTArr[i].ptrfiletable->ptrinode = temp;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)++;
    return i;
}

void CloseFileByFD(int fd)
{
    UFDTArr[fd].ptrfiletable->readoffset = 0;
    UFDTArr[fd].ptrfiletable->writeoffset = 0;
    if (UFDTArr[fd].ptrfiletable->ptrinode->ReferenceCount > 0)
    {
        (UFDTArr[fd].ptrfiletable->ptrinode->ReferenceCount)--;
    }
    else
    {
        UFDTArr[fd].ptrfiletable->ptrinode->ReferenceCount = 0;
    }
}

int CloseFileByName(char* name)
{
    int i = 0;
    i = GetFDFromName(name);
    if (i == -1 || SUPERBLOCKobj.FreeInodes == MAXINODE)
    {
        return -1;
    }

    UFDTArr[i].ptrfiletable->readoffset = 0;
    UFDTArr[i].ptrfiletable->writeoffset = 0;
    if (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount > 0)
    {
        (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;
    }
    else
    {
        UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount = 0;
    }
    return 0;
}

int CloseAllFiles()
{
    int i = 0;
    if (SUPERBLOCKobj.FreeInodes == MAXINODE)
    {
        return -1;
    }
    while (i < MAXINODE)
    {
        if (UFDTArr[i].ptrfiletable != NULL)
        {
            UFDTArr[i].ptrfiletable->readoffset = 0;
            UFDTArr[i].ptrfiletable->writeoffset = 0;
            UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount = 0;           
        }
        i++;
    }
    return 0;
}

int LseekFile(int fd, int size, int from)
{
    if (fd < 0 || from > 2)
    {
        return -1;
    }
    if (UFDTArr[fd].ptrfiletable == NULL)
    {
        return -1;
    }
    if (UFDTArr[fd].ptrfiletable->mode == READ || UFDTArr[fd].ptrfiletable->mode == READ + WRITE)
    {
        if (from == CURRENT)
        {
            if ((UFDTArr[fd].ptrfiletable->readoffset + size) > UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
            {
                return -1;
            }
            if (UFDTArr[fd].ptrfiletable->readoffset + size < 0)
            {
                return -1;
            }
            UFDTArr[fd].ptrfiletable->readoffset = UFDTArr[fd].ptrfiletable->readoffset + size;
        }
        else if (from == START)
        {
            if (size > UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
            {
                return -1;
            }
            if (size < 0)
            {
                return -1;
            }
            UFDTArr[fd].ptrfiletable->readoffset = size;
        }
        else if (from == END)
        {
            if (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize + size > MAXFILESIZE)
            {
                return -1;
            }
            if (UFDTArr[fd].ptrfiletable->readoffset + size < 0)
            {
                return -1;
            }
            UFDTArr[fd].ptrfiletable->readoffset = UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize + size;
        }
    }
    else if (UFDTArr[fd].ptrfiletable->mode == WRITE)
    {
        if (from == CURRENT)
        {
            if (UFDTArr[fd].ptrfiletable->writeoffset + size > MAXFILESIZE)
            {
                return -1;
            }
            if (UFDTArr[fd].ptrfiletable->writeoffset + size < 0)
            {
                return -1;
            }
            if (UFDTArr[fd].ptrfiletable->writeoffset + size > UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
            {
                UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = UFDTArr[fd].ptrfiletable->writeoffset + size;
            }
            UFDTArr[fd].ptrfiletable->writeoffset = UFDTArr[fd].ptrfiletable->writeoffset + size;
        }
        else if (from == START)
        {
            if (size > MAXFILESIZE)
            {
                return -1;
            }
            if (size < 0)
            {
                return -1;
            }
            if (size > UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
            {
                UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = size;
            }
            UFDTArr[fd].ptrfiletable->writeoffset = size;
        }
        else if (from == END)
        {
            if (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize + size > MAXFILESIZE)
            {
                return -1;
            }
            if (UFDTArr[fd].ptrfiletable->writeoffset + size < 0)
            {
                return -1;
            }
            UFDTArr[fd].ptrfiletable->writeoffset = UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize + size;
        }
    }
    return 0;
}

void ls_file()
{
    int cnt = CountInode();
    PINODE temp = head;
    if (SUPERBLOCKobj.FreeInodes == MAXINODE)
    {
        printf("Error:There are no files\n");
        return;
    }
    printf("\nFile Name\tInode number\tFile size\tLink count\n");
    printf("----------------------------------------------------------------------------------\n");
    while (temp != NULL && cnt !=0)
    {
        if (temp->FileType != 0)
        {
            printf("%s\t\t%d\t\t%d\t\t%d\n", temp->FileName, temp->InodeNumber, temp->FileActualSize, temp->LinkCount);
            cnt--;
        }
        temp = temp->pnext;
    }
    printf("----------------------------------------------------------------------------------\n");
}

int fstat_file(int fd)
{
    PINODE temp = head;
    int i = 0;

    if (fd < 0)
    {
        return -1;
    }
    if (UFDTArr[fd].ptrfiletable == NULL)
    {
        return -2;
    }
    temp = UFDTArr[fd].ptrfiletable->ptrinode;

    printf("\n-------------------Statistical Information about file---------------- \n");
    printf("File name : %s\n", temp->FileName);
    printf("Inode Number : %d\n", temp->InodeNumber);
    printf("File size : %d\n", temp->FileSize);
    printf("Actual File size : %d\n", temp->FileActualSize);
    printf("Link count : %d\n", temp->LinkCount);
    printf("Reference count : %d\n", temp->ReferenceCount);

    if (temp->Permission == 1)
    {
        printf("File Permission : Read Only\n");
    }
    else if (temp->Permission == 2)
    {
        printf("File Permission : write\n");
    }
    if (temp->Permission == 3)
    {
        printf("File Permission : Read and write\n");
    }
    printf("------------------------------------------------------------------------\n");
    return 0;
}

int stat_file(char* name)
{
    PINODE temp = head;

    if (name == NULL)
    {
        return -1;
    }
    while (temp != NULL)
    {
        if (strcmp(name, temp->FileName) == 0 && temp->FileType != 0)
        {
            break;
        }
        temp = temp->pnext;
    }
    if (temp == NULL)
    {
        return -2;
    }

    printf("\n-------------------Statistical Information about file-----------------\n");
    printf("File name : %s\n", temp->FileName);
    printf("Inode Number : %d\n", temp->InodeNumber);
    printf("File size(bytes) : %d\n", temp->FileSize);
    printf("Actual File size(bytes) : %d\n", temp->FileActualSize);
    printf("Link count : %d\n", temp->LinkCount);
    printf("Reference count : %d\n", temp->ReferenceCount);

    if (temp->Permission == 1)
    {
        printf("File Permission : Read Only\n");
    }
    else if (temp->Permission == 2)
    {
        printf("File Permission : write\n");
    }
    if (temp->Permission == 3)
    {
        printf("File Permission : Read and write\n");
    }
    printf("------------------------------------------------------------------------\n");
    return 0;
}

int truncate_File(char* name)
{
    if (SUPERBLOCKobj.FreeInodes == MAXINODE)
    {
        return  -1;
    }
    int fd = GetFDFromName(name);
    if (fd == -1)
    {
        return -1;
    }
    if (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize == 0)
    {
        return -2;
    }

    memset(UFDTArr[fd].ptrfiletable->ptrinode->Buffer,'\0', MAXFILESIZE);
    UFDTArr[fd].ptrfiletable->readoffset = 0;
    UFDTArr[fd].ptrfiletable->writeoffset = 0;
    UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = 0;
    return 0;
}

void DeallocteResource()
{
    int i = 0;
    int cnt = CountInode();
    PINODE temp = NULL;
    if (SUPERBLOCKobj.FreeInodes == MAXINODE)
    {
        return;
    }
    while (cnt != 0)
    {
        if (UFDTArr[i].ptrfiletable != NULL)
        {
            if (strcmp(UFDTArr[i].ptrfiletable->ptrinode->FileName, "") != 0)
            {
                if (UFDTArr[i].ptrfiletable->ptrinode->FileActualSize != 0)
                {
                    free(UFDTArr[i].ptrfiletable->ptrinode->Buffer);
                }
            }
            free(UFDTArr[i].ptrfiletable->ptrinode);
            UFDTArr[i].ptrfiletable->ptrinode = NULL;
            free(UFDTArr[i].ptrfiletable);
            UFDTArr[i].ptrfiletable = NULL;            
            cnt--;
        }
        i++;        
    }
}

int CopyFile(char* newname, char* oldname)
{
    int ofd = 0,nfd = 0,i = 0;
    if (SUPERBLOCKobj.FreeInodes == MAXINODE)
    {
        return -1;
    }
    if (SUPERBLOCKobj.FreeInodes == 0)
    {
        return -2;
    }
    ofd = GetFDFromName(oldname);
    nfd = GetFDFromName(newname);
    if (ofd == -1)
    {
        return -1;
    }
    if (nfd == -1)
    {
        nfd = CreateFile(newname, UFDTArr[ofd].ptrfiletable->ptrinode->Permission);
        UFDTArr[nfd].ptrfiletable->ptrinode->FileType = SPECIAL;
    }
    if (UFDTArr[nfd].ptrfiletable->ptrinode->FileType == SPECIAL)
    {
        strcpy(UFDTArr[nfd].ptrfiletable->ptrinode->Buffer, UFDTArr[ofd].ptrfiletable->ptrinode->Buffer);
        UFDTArr[nfd].ptrfiletable->ptrinode->FileActualSize = UFDTArr[ofd].ptrfiletable->ptrinode->FileActualSize;
    }
    return 0;
}
