//语言级别的同步通信机制

#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

/*
c++多线程编程-线程间的同步通信机制
多线程编程的两个问题：
1.线程间的互斥
    互斥锁，轻量级的无无锁机制CAS
2.线程间的同步通信
    生产者消费者线程模型
*/

/*
unique_lock condition_variable
1.lock_guard和unique_lock  利用智能指针的概念，对象出作用域会自动释放锁
    lock_guard 左值引用的拷贝构造和赋值delete掉，不可能用在函数参数传递或者返回过程中，只能用在简单的临界区代码断的互斥操作中
    unique_lock 提供了右值引用的拷贝构造和赋值中
    所以wait只能传进来unique_lock
2.condition_variable wait和notify
    cv.notify_all();

*/


mutex mtx; //定义互斥锁
//std::condition_variable cv; //定义条件变量作线程间的同步通信
std::condition_variable empty, full;

class Queue
{
public:
    void put(int val)
    {
        //lock_guard<mutex> guard(mtx);  //scoped_ptr
        unique_lock<std::mutex> lck(mtx); //unique_ptr
        while (!que.empty())
        {
            // que不为空，生产者应该通知消费者去消费，消费完了再继续生产
            //生产者线程应该进入等待状态并且释放mtx锁
            //被唤醒时重新获取锁
            empty.wait(lck);
        }
        que.push(val);
        /*
        notify_all通知所有线程
        notify_one通知一个线程
        其他线程的到该通知就会从等待状态变入阻塞并获取互斥锁
        */
        full.notify_all(); //通知其他所有线程有物品可用
        cout << "生产者生产：" << val << "号物品" << endl;
    }

    int get()
    {
        //lock_guard<mutex> guard(mtx);
        unique_lock<std::mutex> lck(mtx);
        while(que.empty())
        {
            //消费者发现que是空的，通知生产者线程生产
            //进入等待状态，释放互斥锁
            full.wait(lck);
        }
        int val = que.front();
        que.pop();
        empty.notify_all(); //通知其他线程
        cout << "消费者消费：" << val << "号物品" << endl;
        return val;
    }
private:
    queue<int> que;
};


void producer(Queue *que) //生产者线程
{
    for (int i = 1; i <= 10; ++i)
    {
        que->put(i);
        this_thread::sleep_for(chrono::milliseconds(100));
    }unique_lock<std::mutex> lck(mtx);
}

void consumer(Queue *que) //消费者线程
{
    for (int i = 1; i <= 10; ++i)
    {
        que->get();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main()
{
    Queue que; //两个线程共享的队列
    std::thread t1(producer, &que);
    std::thread t2(consumer, &que);

    t1.join();
    t2.join();

    return 0;
}

//用两个条件变量，因为不希望看到消费者唤醒消费者