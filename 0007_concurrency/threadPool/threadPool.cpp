 /*
 c++ 11 封装线程池
 1. 接口：
     1.1 向线程池任务队列添加任务
 2. 组件：
     2.1 线程集合：系列线程的集合， 线程入口函数封装为抽象基类虚函数
     2.2 任务队列：装系列任务
 3.单例模式
 4.任务队列空怎么处理
 5.线程同步问题
 6.线程任务结束，怎么回到池里
 */

//  有bug  2020.8.15  还不知道怎么修改
#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include "task.h"
#define POOLINSTANCE ( ThreadPool<Task>::getInstance() )
#define THREAD_NUM 8
 
 template <typename TASK>
 class ThreadPool{
 public:
     bool addTask(TASK *one_task); // 
     static ThreadPool &getInstance(){
         static ThreadPool poolInstance;
         return poolInstance;
     }
     int numTask(){return m_task_queue.size();}
	 ~ThreadPool() {
		 {
			 std::unique_lock<std::mutex>lock(thd_pl_mutex);
			 stop = true;
		 }
		
		 m_cond.notify_all();
		 for (std::thread& thread : thd_pool) {
		//thread.detach(); // 让线程“自生自灭”
			if (thread.joinable())
				thread.join(); // 等待任务结束， 前提：线程一定会执行完
		 }
	 }
	 /*void test(){
		worker();
	 }*/
 private:
 /*单例条件*/
     ThreadPool();
     ThreadPool(const ThreadPool &thd_pool){
         std::cout<<"call copy constructor "<<std::endl;
     }
     ThreadPool& operator = (const ThreadPool &thd_pool){return *this;}

 private:
      void worker(){
		std::unique_lock<std::mutex>unqe_lk(thd_pl_mutex);
		m_cond.wait(unqe_lk, [this]() {
			return stop || !m_task_queue.empty(); // 空 阻塞等待唤醒 非空 直接返回
		});
		auto tk = std::move(m_task_queue.front());
		tk = std::move(m_task_queue.front());
		m_task_queue.pop_front();

		tk->task();
      }

 private:
     std::list<TASK*>m_task_queue;
	 std::vector<std::thread>thd_pool;
	 std::mutex thd_pl_mutex;
	 std::condition_variable m_cond;
	 bool stop;

 };
 template <typename TASK>
 bool ThreadPool<TASK>::addTask(TASK *one_task){
	 thd_pl_mutex.lock();
     m_task_queue.push_back(one_task);
	 m_cond.notify_one();
	 thd_pl_mutex.unlock();

     std::cout<<"ThreadPool::addTask()"<<std::endl;
	 return true;
 }
 template <typename TASK>
 ThreadPool<TASK>::ThreadPool():m_task_queue(0),thd_pool(THREAD_NUM), stop(false){
         //创建系列线程
	 for (int i = 0; i < THREAD_NUM; i++) {
		
		 std::thread tmp(&ThreadPool<TASK>::worker, this);
		 thd_pool.push_back(std::move(tmp));
		 //thd_pool.push_back(std::thread(&ThreadPool<TASK>::worker, this));
		 //thd_pool.back().detach();
	 }
 }
 // 线程执行完毕 如何回收？

 int main(){
	 TK1 fir;
	 TK2 sec;
	 TK3 thr;
	 TK4 fou;
	 POOLINSTANCE.addTask(&fir);
	 POOLINSTANCE.addTask(&sec);
	 POOLINSTANCE.addTask(&thr);
	 POOLINSTANCE.addTask(&fou);

     return 0;
 }






//#include <iostream>
//#include <list>
//#include <vector>
//using namespace std;
//class A {
//public:
//	virtual void f() const {
//		cout << "call A::f()" << endl;
//	}
//};
//
//class B :public A {
//public:
//	void f() const {
//		cout << "B::f()" << endl;
//	}
//	B() = default;
//	B(const A &a) {
//		cout << "call B::B(const A &a)" << endl;
//	}
//	B(const B &b) {
//		cout << "call B copy constructor " << endl;
//	}
//};
//void test_f(const A &a) {
//	a.f();
//
//}
//
// void test_f1(const int &&e){
//     cout<<"............"<<endl;
// }
//int main() {
//	// vector<A*>v;
//	// B b;
//	// v.push_back(&b);
//	// v[0]->f();
//
//
//
//
//
//
//
//
//	vector<A>v;
//	B b;
//
//	v.push_back(b);
//	v.front().f();
//
//
//
//	return 0;
//}
//
//
///*
//
//右值引用作为函数参数
//void test_f1(const int &&e){
//	cout<<"............"<<endl;
//}
//const 对象只能调用const成员函数
//
//
//如何实现多态：
//基类类型的vector，当插入派生类对象时，不能实现多态。可以改为基类指针类型的vector。
//
//函数接口实现多态时，参数可以是const基类类型  也可以是基类指针类型
//
//*/