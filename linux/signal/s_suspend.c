/*
desciption:如果在信号阻塞时将其发送给进程，那么该信号的传递就被推迟直到对它解除了阻塞。
对应用程序而言，该信号好像发生在解除对SIGINT的阻塞和pause之间。
如果发生了这种情况，或者如果在解除阻塞时刻和pause之间确实发生了信号，那么就产生了问题。
为了纠正此问题，需要在一个原子操作中先恢复信号屏蔽字，然后使进程休眠。这种功能是由sigsuspend函数提供的
注：sigsuspend实际是将sigprocmask和pause结合起来原子操作。
*/
// error version
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
 
void handler(int sig)    //信号处理函数的实现
{
   printf("SIGINT sig\n");
}
int main()
{
    sigset_t new,old;
    struct sigaction act;
    act.sa_handler = handler;  //信号处理函数handler
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);  //准备捕捉SIGINT信号
    sigemptyset(&new);
    sigaddset(&new, SIGINT);
    sigprocmask(SIG_BLOCK, &new, &old);  //将SIGINT信号阻塞，同时保存当前信号集
    printf("Blocked\t");
    sigprocmask(SIG_SETMASK, &old, NULL);  //取消阻塞
    // pause();
    sleep(5);
    return 0;
}

// use sigsuspend
// #include <unistd.h>
// #include <signal.h>
// #include <stdio.h>
// void handler(int sig)   //信号处理程序
// {
//    if(sig == SIGINT)
//       printf("SIGINT sig\n");
//    else if(sig == SIGQUIT)
//       printf("SIGQUIT sig\n");
//    else
//       printf("SIGUSR1 sig\n");
// }
 
// int main()
// {
//     printf("pid = %d\n",getpid());
//     sigset_t new,old,wait;   //三个信号集
//     struct sigaction act;
//     act.sa_handler = handler;
//     sigemptyset(&act.sa_mask);
//     act.sa_flags = 0;
//     sigaction(SIGINT, &act, 0);    //可以捕捉以下三个信号：SIGINT/SIGQUIT/SIGUSR1
//     sigaction(SIGQUIT, &act, 0);
//     sigaction(SIGUSR1, &act, 0);
   
//     sigemptyset(&new);
//     sigaddset(&new, SIGINT);  //SIGINT信号加入到new信号集中
//     sigemptyset(&wait);
//     sigaddset(&wait, SIGUSR1);  //SIGUSR1信号加入wait
//     sigprocmask(SIG_BLOCK, &new, &old);       //将SIGINT阻塞，保存当前信号集到old中
   
//     //临界区代码执行    
  
//     if(sigsuspend(&wait) != -1)  //程序在此处挂起；用wait信号集替换new信号集。即：过来SIGUSR1信  号，阻塞掉，程序继续挂起；过来其他信号，例如SIGINT，则会唤醒程序。执行sigsuspend的原子操作。注意：如果“sigaddset(&wait, SIGUSR1);”这句没有，则此处不会阻塞任何信号，即过来任何信号均会唤醒程序。
//         printf("sigsuspend error");
//     printf("After sigsuspend\n");
//     sigprocmask(SIG_SETMASK, &old, NULL);
//     return 0;
// }