#include <string.h>

int main(void){

    char buffer[128] = "lelloaskjdhaklfha";
    char *l = strstr(buffer, "lallo");

    printf(l);

}