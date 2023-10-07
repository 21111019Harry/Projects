#include "VFSHeader.h"
int main()
{
    char* ptr = NULL;
    int ret = 0, fd = 0, count = 0;
    char command[4][80], str[80], arr[MAXFILESIZE];
    int running = 1;
    InitialiseSuperBlock();
    CreateDILB();

    while (running)
    {
        fflush(stdin);
        memset((void*)str,0,(size_t)80);
        printf("\nMarvellous CustomizedVFS: > ");
        
        fgets(str, 80, stdin);
        //scanf_s("%[^'\n']s",str);
        count = sscanf(str, "%s %s %s %s", command[0], command[1], command[2], command[3]);
        if (count == 1)
        {
            if (strcmp(command[0], "ls") == 0)
            {
                ls_file();
            }
            else if (strcmp(command[0], "clear") == 0)
            {
                system("cls");
                continue;
            }
            else if (strcmp(command[0], "help") == 0)
            {
                DisplayHelp();
                continue;
            }
            else if (strcmp(command[0], "exit") == 0)
            {
                printf("Terminating Marvellous Customized filesystem\n");
                DeallocteResource();
                break;
            }
            else
            {
                printf("\nERROR : Bad Command!!!\n");
                printf("Try man %s or type \"help\"\n", command[0]);
                continue;
            }
        }
        else if (count == 2)
        {
            if (strcmp(command[0], "stat") == 0)
            {
                ret = stat_file(command[1]);
                if (ret == -1)
                    printf("ERROR : Incorrect parameters\n");
                if (ret == -2)
                    printf("ERROR : There is no such file\n");
                continue;
            }
            else if (strcmp(command[0], "fstat") == 0)
            {
                ret = fstat_file(atoi(command[1]));
                if (ret == -1)
                    printf("ERROR : Incorrect parameters\n");
                if (ret == -2)
                    printf("ERROR : There is no such file\n");
                continue;
            }
            else if (strcmp(command[0], "close") == 0)
            {
                if (strcmp(command[1], "-r") == 0)
                {
                    ret = CloseAllFiles();
                    if (ret == -1)
                    {
                        printf("There are no files present\n");
                    }
                    else if (ret == 0)
                    {
                        printf("All files closed succesfully\n");
                    }
                    continue;
                }
                else
                {
                    ret = CloseFileByName(command[1]);
                    if (ret == -1)
                    {
                        printf("ERROR : File Does not exists!\n");
                    }
                    else if (ret == 0)
                    {
                        printf("File Closed Successfully\n");
                    }
                    continue;
                }
            }
            else if (strcmp(command[0], "rm") == 0)
            {
                if (strcmp(command[1], "-r") == 0)
                {
                    ret = rm_all();
                    if (ret == 0)
                    {
                        printf("All files deleted succesfully\n");
                        continue;
                    }
                    else if (ret == -1)
                    {
                        printf("There are no files\n");
                    }
                }
                else
                {
                    ret = rm_File(command[1]); //rm Demo.txt
                    if (ret == -1)
                        printf("ERROR : There is no such file\n");
                    else if (ret == 0)
                        printf("File removed Successfully\n");
                    continue;
                }
            }
            else if (strcmp(command[0], "man") == 0)
            {
                man(command[1]);
            }
            else if (strcmp(command[0], "write") == 0) //write Demo.txt
            {
                fd = GetFDFromName(command[1]); 
                if (fd == -1)
                {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }                
               
                printf("Enter the data : \n");
                //fgets(arr, 1024, stdin); 
                scanf("%[^\t]",arr);//abcd  
                while ((getchar()) != '\n');
                ret = (int)strlen(arr);
               
                if (ret == 0)
                {
                    printf("Error : Incorrct parameter\n");
                    continue;
                }
                ret = WriteFile(fd, arr, ret);
                if (ret == -1)
                {
                    printf("ERROR : Permission denied\n");
                }
                if (ret == -2)
                {
                    printf("ERROR : There is no sufficient  memory to write\n");
                }
                if (ret == -3)
                {
                    printf("ERROR : It is not regular file\n");
                }
                if (ret > 0)
                {
                    printf("Success:%d bytes successfully written", ret);
                }
                
                continue;

            }
            else if (strcmp(command[0], "truncate") == 0)
            {
                ret = truncate_File(command[1]);
                if (ret == -1)
                    printf("Error : Incorrect parameter or ther is no such file\n");
                else if (ret == -2)
                {
                    printf("Error :File is Already empty");
                }
                else if (ret == 0)
                {
                    printf("File truncated Successfully\n");
                }
                continue;
            }
            else
            {
                printf("\nERROR : Bad Command!!!\n");
                printf("Try man %s or type \"help\"\n", command[0]);
                continue;
            }
        }
        else if (count == 3)
        {
            if (strcmp(command[0], "create") == 0)
            {
                ret = CreateFile(command[1], atoi(command[2]));
                if (ret >= 0)
                {
                    printf("File Successfully created with file descriptor %d \n", ret);
                }
                if (ret == -1)
                {
                    printf("ERROR : Incorrect paramters\n");
                }
                if (ret == -2)
                {
                    printf("ERROR : There is no inode\n");
                }
                if (ret == -3)
                {
                    printf("ERROR : File already exists\n");
                }
                if (ret == -4)
                {
                    printf("ERROR : Memory Allocation failure\n");
                }
                continue;
            }
            else if (strcmp(command[0], "open") == 0)
            {
                ret =OpenFile(command[1], atoi(command[2]));
                if (ret >= 0)
                {
                    printf("File Successfully opened with file descriptor %d \n", ret);
                }
                if (ret == -1)
                {
                    printf("ERROR : Incorrect paramters\n");
                }
                if (ret == -2)
                {
                    printf("ERROR : File Not present\n");
                }
                if (ret == -3)
                {
                    printf("ERROR : Permission denied\n");
                }
                continue;
            }
            else if (strcmp(command[0], "read") == 0)
            {
                fd = GetFDFromName(command[1]);
                if (ret == -1)
                {
                    printf("ERROR : Incorrect paramters\n");
                    continue;
                }
                ptr = (char*)malloc(sizeof(atoi(command[2])) + 1);
                if (ptr == NULL)
                {
                    printf("ERROR : Memory allocation failure\n");
                    continue;
                }
                ret = ReadFile(fd, ptr, atoi(command[2]));
                if (ret == -1)
                {
                    printf("ERROR : File does not exists\n");
                }
                if (ret == -2)
                {
                    printf("ERROR : Permission Denied\n");
                }
                if (ret == -3)
                {
                    printf("ERROR : Reached At end of file\n");
                }
                if (ret == -4)
                {
                    printf("ERROR : It is not regular file\n");
                }
                if (ret == 0)
                {
                    printf("ERROR : File Empty\n");
                }
                if (ret > 0)
                {
                    write(1, ptr, ret);//Display data in ptr upto ret(bytes) on screen(STDOUT - 2)
                }
                continue;
            }
            else if (strcmp(command[0], "copy") == 0)
            {
                ret = CopyFile(command[1], command[2]);
                if (ret == -1)
                {
                    printf("Error : File Does Not Exixts!!\n");
                }
                else if (ret == -2)
                {
                    printf("Error : Ther are no inodes\n");
                }
                else if(ret == 0)
                {
                    printf("Successfully Copy made\n");
                }
            }
            else
            {
                printf("\nERROR : Bad Command!!!\n");
                printf("Try man %s or type \"help\"\n", command[0]);
                continue;
            }
        }
        else if (count == 4)
        {
            if (strcmp(command[0], "lseek") == 0)
            {
                fd = GetFDFromName(command[1]);
                if (fd == -1)
                {
                    printf("ERROR : Incorrect paramters\n");
                    continue;
                }
                ret = LseekFile(fd, atoi(command[2]), atoi(command[3]));
                if (ret == -1)
                {
                    printf("ERROR : Unable to perform lseek");
                }
            }
            else
            {
                printf("\nERROR : Bad Command!!!\n");
                printf("Try man %s or type \"help\"\n", command[0]);
                continue;
            }
        }
        else
        {
            printf("\nERROR : Bad Command!!!\n");
            printf("Try man %s or type \"help\"\n", command[0]);
            continue;
        }
    } 
    return 0;
}
