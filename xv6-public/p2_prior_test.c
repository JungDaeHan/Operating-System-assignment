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

/*
     가장 높은 우선순위를가진 프로세스가 주기적으로 잠듭니다.
       잠들었을 경우 다름 우선순위의 프로세스가 실행되고, 깨어나면 선점해야 합니다.
       */
void
test_sleep() {
    int i;
    setpriority(getpid(), 5);
        for( i=0; i<5; i++) {
                int pid = fork();
                    if (pid == 0) {
                              sleep(10); // wait for all children fork()ed
                                    if (i == 0) 
                                                exec(TEST_CHILD_NAME, argv[TEST_CHILD_SLEEPER]);
                                          else 
                                                      exec(TEST_CHILD_NAME, argv[TEST_CHILD_PRINTER]);
                                              } else {
                                                        printf(1, "proc %d created priority: %d\n", pid, 5-i);
                                                              setpriority(pid , 5-i);
                                                                  }
                      }
          while(wait()!=-1); // wait all children
          setpriority(getpid(), 0);
}

/*
     우선순위 0, 1을 가지는 프로세스 각각 두개,
       우선순위 4를 가지는 프로세스를 한개 실행합니다.

         우선순위4를 가진 프로세스가 종료되면, 1을 가진 프로세스들이 RR로 실행되어야 합니다.
         */
void
test_same_priority() {
      setpriority(getpid(), 5);
      int i;  
      for( i=0; i<5; i++) {
                int pid = fork();
                    if (pid == 0) {
                              sleep(10); // wait for all children fork()ed
                                    exec(TEST_CHILD_NAME, argv[TEST_CHILD_PRINTER]);
                                        } else {
                                                  int prior = 2;
                                                        if (i==0)
                                                                    prior = 2;
                                                              else
                                                                          prior =i%2; 
                                                                    printf(1, "proc %d created priority: %d\n", pid, prior);
                                                                          setpriority(pid, prior);
                                                                              }
                      }
          while(wait()!=-1); // wait all children
          setpriority(getpid(), 0);
}

/*
     가장 높은 우선순위를 가지는 프로세스가 5tick이 지난 후에 생성됩니다.
       이 프로세스가 생성되면 먼저 스케줄링되어야 합니다. 
       */
void
test_preemption() {
      setpriority(getpid(), 5);
      int i;  
      for( i=0; i<5; i++) {
                if (i == 4)
                          sleep(5);
                    int pid = fork();
                        if (pid == 0) {
                                  sleep(10); // wait for all children fork()ed
                                        exec(TEST_CHILD_NAME, argv[TEST_CHILD_PRINTER]);
                                            } else {
                                                      printf(1, "proc %d created priority: %d\n", pid, i);
                                                            setpriority(pid, i);
                                                                }
                          }
          while(wait()!=-1); // wait all children
          setpriority(getpid(), 0);
}

/*
     모든 프로세스가 다른 우선순위를 가집니다.
     */
void
test_diff_priority() {
      setpriority(getpid(), 5);
      int i; 
      for( i=0; i<5; i++) {
                int pid = fork();
                    if (pid == 0) {
                              sleep(10); // wait for all children fork()ed
                                    exec(TEST_CHILD_NAME, argv[TEST_CHILD_PRINTER]);
                                        } else {
                                                  printf(1, "proc %d created priority: %d\n", pid, i);
                                                        setpriority(pid, i);
                                                            }
                      }
          while(wait()!=-1); // wait all children
          setpriority(getpid(), 0);
}

int 
main(int argc, char* argv[]) {
      printf(1, "-----------test_diff_priority----------\n");
        test_diff_priority();
          printf(1, "-----------test_same_priority----------\n");
            test_same_priority();
              printf(1, "-----------test_preemption----------\n");
                test_preemption();
                  printf(1, "-----------test_sleep----------\n");
                    test_sleep();
                      printf(1, "-----------test_finish----------\n");
                        exit();
}

