#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <algorithm>
#include <random>
#include <ctime>

class Timer
{
	using watch_t = std::chrono::steady_clock;
	using timepoint_t = watch_t::time_point;

public:
	Timer() : m_begin(watch_t::now()), time(0)
	{
		std::cout << "Timer_CTOR" << std::endl;
	}
	~Timer() noexcept
	{
		auto end = watch_t::now();
		std::cout << "Timer stopped, ";
		if (working)
			time += std::chrono::duration_cast <std::chrono::milliseconds> (end - m_begin);
		std::cout << time.count();
		std::cout << " milliseconds passed." << std::endl;
	}
	void pause()
	{
		auto end = watch_t::now();
		working = false;
		time += std::chrono::duration_cast <std::chrono::milliseconds> (end - m_begin);
		std::cout << "Timer paused, " << time.count() << " milliseconds passed." << std::endl;

	}
	void resume()
	{
		working = true;
		m_begin = watch_t::now();
		std::cout << "Timer resumed" << std::endl;
	}
private:
	timepoint_t m_begin;
	std::chrono::milliseconds time;
	bool working = true;
};

int main()
{
	int number;
	std::cin >> number;

	std::vector <int> vector;
	std::mt19937 gen(time(0));
	std::uniform_int_distribution<> uid(0, 100);

	{
		Timer timer_for_vector;
	for (int i = 0; i < number; i++) {
		vector.push_back(uid(gen));
	}
	std::sort(vector.begin(), vector.end());
	}

	{
		Timer timer_for_array;
	std::array <int, 100000> array;
	for (int i = 0; i < array.size(); i++) {
		array[i] = vector[i];
	}
	std::sort(array.begin(), array.end());
	}

	{
		Timer timer_for_deque;
	std::deque<int> deque;
	for (int i = 0; i < number; i++) {
		//deque[i] = vector[i];
		deque.push_back(vector[i]);
	}
	std::sort(deque.begin(), deque.end());
	}

	{
		Timer timer_for_list;
	std::list<int> list;
	for (int i = 0; i < number; i++) {
		list.push_back(vector[i]);
	}
	list.sort();
	}

	{
		Timer timer_for_forward_list;
		std::list<int> f_list;
		for (int i = 0; i < number; i++) {
			f_list.push_back(vector[i]);
		}
		f_list.sort();
	}
		
	system("pause");
	return 0;
}