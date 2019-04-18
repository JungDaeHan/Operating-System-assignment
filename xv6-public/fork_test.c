#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    int i;
    int pid;

    printf(1,"before fork => "); 
    get_n_free_pages();
    
    pid = fork();
    if(pid == 0)
    {
        for(i=0 ; i<10 ; i++)
            printf(1,"aaaa(%d) ",i);
        printf(1,"child fork => ");  
        get_n_free_pages();
    }
    else
    {
        wait();
        printf(1,"parent fork => ");
        get_n_free_pages();
    }
    exit();
    
    
}

