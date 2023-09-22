//语言级别的互斥操作
#include <iostream>
#include <thread>
#include <list>
#include <mutex>

using namespace std;

int count = 100;
mutex mtx; //全局的一把互斥锁

/*
多线程程序
竞态条件：多线程程序执行的结果是一致的，不会随着cpu对线程不同的调用顺序，而产生不同的运行结果

lock_guard和unique
*/


void sellTicket(int index)
{
    while (count > 0) //count == 1
    {
        {
            //mtx.lock();
            //lock_guard<mutex> lock(mtx); //参数传递过程中不能使用，因为他不支持拷贝构造和拷贝赋值类似scoped_ptr
            unique_lock<mutex> lck(mtx);//unique_ptr
            lck.lock();
            if(count > 0)
            {
                //临界区代码段（访问共享资源的代码）要保证原子操作
                cout << "窗口" << index << "卖出第" << count << "张票" << endl;
                //cout << count << endl;
                count--;
            }
            lck.unlock();
        }
        //mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(100));
    }

}

// int main()
// {
//     list<std::thread> tlist;
//     for (int i  = 1; i <= 3; ++i)
//     {
//         tlist.push_back(std::thread(sellTicket, i));
//     }

//     for (auto &t : tlist)
//     {
//         t.join();
//     }

//     cout << "sell out" << endl; 

//     return 0;
// }