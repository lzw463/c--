#include <iostream>
#include <thread>
#include <atomic> //包含了很多原子类型

using namespace std;

/*
c++11 基于CAS操作的atomic原子类型

互斥锁是比较重的，临界区代码做的事比较多复杂，用
++--用CAS来保证++--操作的原子特性就足够了，无锁操作
    exchange/swap
*/


int main()
{
    return 0;
}