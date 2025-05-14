#include <stdio.h>
#include <stdlib.h>

struct clock{
    int hours;
    int minutes;
} watch;

void clock(struct clock var);

int main(void){
    watch.hours = 19;
    watch.minutes = 30;

    clock(watch);

    return 0;
}
void clock(struct clock var){
    printf("Horas: %d\n", var.hours);
    printf("Minutos: %d\n", var.minutes);
}
