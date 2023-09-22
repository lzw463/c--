#include <iostream>
#include <thread>

//using namespace std; //别写可能造成名字冲突

/*
c++语言级别的多线程编程 最大优点:可以跨平台
thread/mutex/condition_variable
lock_guard/unique_lock
atomic 原子类型 基于CAS操作的原子类型 线程安全的
sleep_for

线程内容
1：如何创建启动一个线程
    定义一个线程对象，传入线程所需要的函数及参数，线程自动开启
2.子线程如何结束
    子线程函数运行完成，主线程继续往下运行
3.主线程如何处理子线程
t.join()等待t线程结束,当前线程继续往下运行
t.detach()把子线程设置为分离线程，主线程结束，所有子线程自动结束

*/
void threadHandle1(int time)
{
    //让子线程睡眠两秒
    std::this_thread::sleep_for(std::chrono::seconds(time));
    std::cout << "hello thread1" << std::endl;
}
void threadHandle2(int time)
{
    //让子线程睡眠两秒
    std::this_thread::sleep_for(std::chrono::seconds(time));
    std::cout << "hello thread2" << std::endl;
}



// int main() 
// {
//     //创建类一个线程对象传入一个线程函数，新线程就开始运行了
//     std::thread t1(threadHandle1, 2);
//     std::thread t2(threadHandle2, 3);
//     //主线程等待子线程结束，主线程继续往下运行
//     t1.join(); //其实底层是利用条件变量实现的
//     t2.join();
//     //t1.detach(); //把子线程设置为分离线程（守护线程）

//     std::cout << "main thread down" << std::endl;

//     //主线程运行完成，查看如果当前进程还有未运行完成的子线程
//     //进程就会异常终止
//     return 0;
// }