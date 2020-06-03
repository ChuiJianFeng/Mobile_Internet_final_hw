//
// Created by jian on 2020-06-01.
//

#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct Package Package;
struct Package{
    int dist;
    char content[100];
};

static Package *test_var;

int main(){
    test_var = mmap(NULL, sizeof(Package)*3, PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    test_var[0].dist = 0;
    strcpy(test_var[0].content, "abc");

    if(fork()==0){
        test_var[0].dist = 1;
        exit(0);
    }
    wait(NULL);
    printf("%d\n%s", test_var[0].dist, test_var[0].content);
}