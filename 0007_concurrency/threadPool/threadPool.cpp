 /*
 c++ 11 ��װ�̳߳�
 1. �ӿڣ�
     1.1 ���̳߳���������������
 2. �����
     2.1 �̼߳��ϣ�ϵ���̵߳ļ��ϣ� �߳���ں�����װΪ��������麯��
     2.2 ������У�װϵ������
 3.����ģʽ
 4.������п���ô����
 5.�߳�ͬ������
 6.�߳������������ô�ص�����
 */

//  ��bug  2020.8.15  ����֪����ô�޸�
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
		//thread.detach(); // ���̡߳���������
			if (thread.joinable())
				thread.join(); // �ȴ���������� ǰ�᣺�߳�һ����ִ����
		 }
	 }
	 /*void test(){
		worker();
	 }*/
 private:
 /*��������*/
     ThreadPool();
     ThreadPool(const ThreadPool &thd_pool){
         std::cout<<"call copy constructor "<<std::endl;
     }
     ThreadPool& operator = (const ThreadPool &thd_pool){return *this;}

 private:
      void worker(){
		std::unique_lock<std::mutex>unqe_lk(thd_pl_mutex);
		m_cond.wait(unqe_lk, [this]() {
			return stop || !m_task_queue.empty(); // �� �����ȴ����� �ǿ� ֱ�ӷ���
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
         //����ϵ���߳�
	 for (int i = 0; i < THREAD_NUM; i++) {
		
		 std::thread tmp(&ThreadPool<TASK>::worker, this);
		 thd_pool.push_back(std::move(tmp));
		 //thd_pool.push_back(std::thread(&ThreadPool<TASK>::worker, this));
		 //thd_pool.back().detach();
	 }
 }
 // �߳�ִ����� ��λ��գ�

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
//��ֵ������Ϊ��������
//void test_f1(const int &&e){
//	cout<<"............"<<endl;
//}
//const ����ֻ�ܵ���const��Ա����
//
//
//���ʵ�ֶ�̬��
//�������͵�vector�����������������ʱ������ʵ�ֶ�̬�����Ը�Ϊ����ָ�����͵�vector��
//
//�����ӿ�ʵ�ֶ�̬ʱ������������const��������  Ҳ�����ǻ���ָ������
//
//*/