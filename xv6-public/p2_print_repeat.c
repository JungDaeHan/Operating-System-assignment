#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char* argv[]) {
      int repeat, sleep_period, print_period, sleep_term;
        char* print_str;
          int i;

            if(argc != 6) {
                    printf(1, "argc : %d\n", argc);
                        printf(1, "Usage: print_repeat print_str #repeat #print_period(#iter) #sleep_period(#iter) sleep_term(ticks) \n");
                            exit();
                              }

              print_str = argv[1];
                repeat = atoi(argv[2]);
                  print_period = atoi(argv[3]);
                    sleep_period = atoi(argv[4]);
                      sleep_term = atoi(argv[5]);

                        for (i=0; i<repeat; i++) {
                                if (sleep_term) { 
                                          if (i%sleep_period == 0) {
                                                      sleep(sleep_term*2);
                                                            }
                                              }
                                    if (i%print_period == 0) {
                                              printf(1, "[%d][%d]: %s\n", getpid(), i/print_period, print_str);
                                                  }
                                      }
                          exit();
}

