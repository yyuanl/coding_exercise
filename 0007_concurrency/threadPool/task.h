#pragma once
#include <iostream>
class Task {
public:
	Task() {
		std::cout << "Task::Task() constructor" << std::endl;
	}
	virtual void task() {
		std::cout << "call Task::task()" << std::endl;
	}
};

class TK1 : public Task {
public:
	TK1() = default;
	void task() {
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		std::cout << "process this Tk1 task" << std::endl;
	}
};
class TK2 : public Task {
public:
	TK2() = default;
	void task() {
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		std::cout << "process this TK2 task" << std::endl;
	}
};
class TK3 : public Task {
public:
	TK3() = default;
	void task() {
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		std::cout << "process this TK3 task" << std::endl;
	}
};
class TK4 : public Task {
public:
	TK4() = default;
	void task() {
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		std::cout << "process this TK4 task" << std::endl;
	}
};
