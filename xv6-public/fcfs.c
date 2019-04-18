#include "types.h"
#include "stat.h"
#include "user.h"

#define TEST_CHILD_NAME "p2_print_repeat"
#define TEST_CHILD_PRINTER 0
#define TEST_CHILD_SLEEPER 1

char* argv[][7] = {
      {TEST_CHILD_NAME, "printer", "2000000", "400000", "0", "0" , 0},
        {TEST_CHILD_NAME, "sleeper", "4000000", "400000", "400000", "1", 0},
};

void test_basic() {
    int i;
    for( i=0; i<5; i++) {
              int pid = fork();
                  if (pid == 0) {
                            sleep(10); // wait for all children fork()ed
                                  exec(TEST_CHILD_NAME, argv[TEST_CHILD_PRINTER]);
                                      } else {
                                                printf(1, "proc %d created\n", pid);
                                                    }
                    }
        while(wait()!=-1); // wait all children
}
void test_sleep() {
    int i;  
    for( i=0; i<5; i++) {
              int pid = fork();
                  if (pid == 0) {
                            sleep(10); // wait for all children fork()ed
                                  if (i == 0) 
                                              exec(TEST_CHILD_NAME, argv[TEST_CHILD_SLEEPER]);
                                        else 
                                                    exec(TEST_CHILD_NAME, argv[TEST_CHILD_PRINTER]);
                                            } else {
                                                      printf(1, "proc %d created\n", pid);
                                                          }
                    }
        while(wait()!=-1); // wait all children
}

int 
main(int argc, char* argv[]) {
     printf(1, "-----------test_basic----------\n");
       test_basic();
         printf(1, "-----------test_sleep----------\n");
           test_sleep();
             printf(1, "-----------test_finish----------\n");
               exit();
}

