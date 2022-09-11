//test_gprof.c

// source: https://www.howtoforge.com/tutorial/how-to-install-and-use-profiling-tool-gprof/
#include<stdio.h>

void func4(void){
    printf("\n Inside func4() \n");
    for(int count=0;count<=0XFFFF;count++);
}
void func3(void){
    printf("\n Inside func3() \n");
    for(int count=0;count<=0XFFFFFFF;count++);
}
void func2(void){
    printf("\n Inside func2() \n");
    long g = 1;
    for(int count=0;count<=0XFFFFF;count++)
    {
        g *= 5;
        g /= 4;
    }
    func3();
}
void func1(void){
    printf("\n Inside func1() \n");
    for(int count=0;count<=0XFFFFFF;count++);

    func2();
}
int main(void){
    printf("\n main() starts...\n");
    for(int count=0;count<=0XFFFFF;count++);
    func1();
    func4();
    func3();
    func2();
    printf("\n main() ends...\n");

    return 0;
}