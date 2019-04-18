#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/wait.h>

#define MAX_LEN 100

int token_cnt(char * arr);
void exe_cvp(char *p);

int main(int argc,char *argv[])
{
    char arr[MAX_LEN];
    char **p;
    int i=0;
    pid_t *pid;
    int cnt;
    int status;
    FILE * fp;

    if(argc>2)
    {
        printf("Too many arguments\n");
        return 0;
    }
    else if(argc==2)
    {
    if((fp = fopen(argv[1],"r")) !=NULL)
    {
        while( fgets(arr,MAX_LEN,fp)!=NULL)
         {
            arr[strlen(arr) -1]= '\0';
            puts(arr);

            if(strcmp("quit",arr)==0)
               exit(0);
        
            cnt = token_cnt(arr);
            
            p=(char**)malloc(sizeof(char*)*(cnt+1));
        
            p[0] = strtok(arr,";");

            for(i=1;i<cnt+1;i++)
                p[i] = strtok(NULL, ";");

            pid = malloc(sizeof(pid_t)*(cnt+1));

            for(i=0;i<cnt+1;i++)
            {
                pid[i] = fork();
                if(pid[i] ==0)
                    break;
            }
            
            for(i=0;i<cnt+1;i++)
            {
                switch(pid[i])
                {
                    case -1:
                        {
                            printf("error : can't make child process\n");
                            return -1;
                        }

                    case 0:
                        {
                            exe_cvp(p[i]);
                        }

                    default:
                        {
                            waitpid(pid[i],&status,0);
                        }
                }
            }

          }
    return 0;
    }
    
    else
    {
        printf("batch file open error\n");
        return 0;
    }
    }
   
    printf("Prompt>");
    while( fgets(arr,MAX_LEN,stdin)!=NULL)
    {
        
        arr[strlen(arr) -1]= '\0';
   
        if(strcmp("quit",arr)==0)
            exit(0);
        
        cnt = token_cnt(arr);
        
        p=(char**)malloc(sizeof(char*)*(cnt+1));
        
        p[0] = strtok(arr,";");

        for(i=1;i<cnt+1;i++)
            p[i] = strtok(NULL, ";");

        pid = malloc(sizeof(pid_t)*(cnt+1));

        for(i=0;i<cnt+1;i++)
        {
            pid[i] = fork();
            if(pid[i] ==0)
                break;
        }

        for(i=0;i<cnt+1;i++)
        {
            switch(pid[i])
            {
                case -1:
                    {
                        printf("error : can't make child process\n");
                        return -1;
                    }

                case 0:
                    {
                        exe_cvp(p[i]);
                    }

                default:
                    {
                        waitpid(pid[i],&status,0);
                    }
            }
        }
        printf("Prompt>");
    }
    return 0;
}

int token_cnt(char * arr)
{
    int i=0;
    int cnt=0;
    while(arr[i]!='\0')
    {
        if(arr[i] == ';')
            cnt++;
        i++;
    }
    return cnt;
}

void exe_cvp(char *p)
{
    char *argv[MAX_LEN];
    char *tmp=p;
    int i=0;

    p=strtok(tmp," ");

    while(p!=NULL)
    {  
        argv[i] = p;
        p=strtok(NULL," ");
        i++;
    }
    argv[i] = NULL;
    
    tmp = strtok(tmp," ");
   
   if( execvp(tmp,argv) ==-1)
   {
       fprintf(stderr, "execvp error!!\n");
       exit(0);
   }
}


