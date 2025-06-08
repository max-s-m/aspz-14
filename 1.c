#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
//час простою сервера в секундах
#define TIME 5
//обробник сигналу SIGALRM
void timer_handler(int);

int main(){
    printf("Server is on. Turns off after %d sec of no requests\nPress enter to make request\n", TIME);
    //сетап хендлера: alarm() відрахує 5 секунд, надішле SIGALRM, а далі викличеться хендлер
    signal(SIGALRM, timer_handler);
    alarm(TIME);
    //цикл "сервера" (за запити взято ввід, можна просто клацнути enter)
    int i = 0;
    while(1){
        printf("Waiting for request...\n");
        getchar();
        //виводиться тільки після "запиту" (enter)
        printf("Got request (%d)\n", ++i);
        //таймер скидається, щоб заново рахувати простой
        alarm(TIME);
    }
}
//обробник виводить повідомлення і завершує програму коли спрацьовує таймер alarm()
void timer_handler(int sig){
    char buf[50];
    snprintf(buf, sizeof(buf), "No req for %d seconds, shutting down\n", TIME);
    //write() замість printf() безпечніше для хендлера (async-signal-safe)
    write(STDOUT_FILENO, buf, sizeof(buf));
    exit(0);
}
