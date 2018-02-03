#include <stdio.h>
#include <stdlib.h>
#include <iostream> // std::cout
#include <thread>   // std::thread
#include <mutex> 
#include <future>
//	get_id  获取线程 ID。
//	joinable 检查线程是否可被 join。
//	join	Join 线程。
//	detach Detach 线程  !!!!
//	swap  Swap 线程 。
//	native_handle
//	hardware_concurrency [static]  检测硬件并发特性。
//
//	std::this_thread::yield() 是让当前线程让渡出自己的CPU时间片(给其他线程使用)
//	std::this_thread::sleep_for() 是让当前休眠”指定的一段”时间.

//	std::thread t1;						 // t1 is not a thread
//	std::thread t2(f1, n + 1);			 // pass by value
//	std::thread t3(f2, std::ref(n));		 // pass by reference
//	std::thread t4(std::move(t3));		 //(t3需要还在运行=可被 joinable)  t4 is now running f2(). t3 is no longer a 



//锁
//	std::mutex，最基本的 Mutex 类。
//	std::recursive_mutex，递归 Mutex 类。
//	std::time_mutex，定时 Mutex 类。			多了两个成员函数，try_lock_for()，try_lock_until()。	mtx.try_lock_for(std::chrono::milliseconds(200)
//	std::recursive_timed_mutex，定时递归 Mutex 类。

//	std::lock_guard，与 Mutex RAII 相关，方便线程对互斥量上锁。
//	std::unique_lock，与 Mutex RAII 相关，方便线程对互斥量上锁，但提供了更好的上锁和解锁控制。

//	std::once_flag
//	std::adopt_lock_t
//	std::defer_lock_t
//	std::try_to_lock_t

//	std::try_lock，尝试同时对多个互斥量上锁。
//	std::lock，可以同时对多个互斥量上锁。
//	std::call_once，如果多个线程需要同时调用某个函数，call_once 可以保证多个线程对该函数只调用一次。

//	std::mutex mtx;
//	mtx.lock();		mtx.try_lock()(尝试锁住互斥量，如果互斥量被其他线程占有，则当前线程也不会被阻塞);
//	mtx.unlock();

//	std::mutex mtx;
//	std::lock_guard<std::mutex> lck (mtx);  //构建 lck   lck销毁时互斥锁被解锁



//promise
//	std::promise<int> prom; // 生成一个 std::promise<int> 对象.
//	std::future<int> fut = prom.get_future(); // 和 future 关联.
//	prom.set_value(10); // 设置共享状态的值,  此后 promise 的共享状态标志变为 ready.
//	int x = fut.get(); // 获取共享状态的值.
//	prom.set_exception(std::current_exception()); //抛出异常

//	prom.set_value_at_thread_exit(10);	//设置共享状态的值，但是不将共享状态的标志设置为 ready 当线程退出时该 promise 对象会自动设置为 ready。

//packaged_task	 生命周期一直持续到最后一个与之相关联的对象被释放或者销毁为止
//	std::packaged_task<int(int, int)> task(countdown); // 设置 packaged_task	  //countdown 是个函数
//	std::future<int> ret = task.get_future(); // 获得与 packaged_task 共享状态相关联的 future 对象.
//	std::thread th(std::move(task), 10, 0);   //创建一个新线程完成计数任务.  只允许 move  ref 赋值运算
//	int value = ret.get();                    // 等待任务完成并获取结果.!!!!!!!!!!!!


//	 task.make_ready_at_thread_exit 
//   task.valid()		该函数返回 false，除非中间进行了 move 赋值操作或者 swap 操作
//	 task.reset()		重置 packaged_task 的共享状态，但是保留之前的被包装的任务



//std::future

//	 std::future < bool > fut = std::async(is_prime, 444444443);   异步执行
//	 std::chrono::milliseconds span(100);
//	 while (fut.wait_for(span) == std::future_status::timeout)
//		std::cout << '.';
//	 
//	 bool x = fut.get();

//	 std::future<int> fut = std::async(do_get_value);
//	 std::shared_future<int> shared_fut = fut.share();  //返回一个 std::shared_future 对象 std::future 对象本身已经不和任何共享状态相关联，因此该 std::future 的状态不再是 valid 的了
//	 get()
//	 valid()
//	 wait()  等待与当前std::future 对象相关联的共享状态的标志变为 ready.
//	 wait_for()		wait_for() 可以设置一个时间段 rel_time 在等待了 rel_time 的时间长度后 wait_until() 返回   future_status::ready	共享状态的标志已经变为 ready，即 Provider 在共享状态上设置了值或者异常。  future_status::timeout	超时，即在规定的时间内共享状态的标志没有变为 ready。 future_status::deferred	共享状态包含一个 deferred 函数。
//	 wait_until()	std::future::wait() 的功能类似，即等待与该 std::future 对象相关联的共享状态的标志变为 ready


//	  std::future < void >foo = std::async(std::launch::async, do_print_ten, '*', 100);


//std::atomic_flag
//	 std::atomic<bool> ready(false);   
//	 std::atomic_flag winner = ATOMIC_FLAG_INIT;

// 如果某个线程率先执行完上面的计数过程，则输出自己的 ID.
// 此后其他线程执行 test_and_set 是 if 语句判断为 false，
// 因此不会输出自身 ID.
//	if (!winner.test_and_set()) {
//		std::cout << "thread #" << id << " won!\n";
//	}

//	winner.clear()	 清除 std::atomic_flag 标志使得下一次调用 std::atomic_flag::test_and_set 返回 false


//std::atomic 是模板类，一个模板类型为 T 的原子对象中封装了一个类型为 T 的值。







void thread_task() {
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));//线程休眠
	std::cout << "hello thread" << std::endl;
}
void f1(int n)
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Thread " << n << " executing\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void f2(int& n)
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Thread 2 executing\n";
		++n;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void print_int(std::promise<int>& prom) {
	std::future<int> fut = prom.get_future(); // 和 future 关联.
	int x = fut.get(); // 获取共享状态的值.
	std::cout << "value: " << x << '\n'; // 打印 value: 10.
}

int countdown(int from, int to) {
	for (int i = from; i != to; --i) {
		std::cout << i << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Finished!\n";
	return from - to;
}
int triple(int x) { return x * 3; }
bool is_prime(int x)
{
	for (int i = 2; i < x; ++i)
		if (x % i == 0)
			return false;
	return true;
}

std::atomic<bool> ready(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;
void count1m(int id)
{
	while (!ready) {
		std::this_thread::yield();
	} // 等待主线程中设置 ready 为 true.

	for (int i = 0; i < 1000000; ++i) {
	} // 计数.

	  // 如果某个线程率先执行完上面的计数过程，则输出自己的 ID.
	  // 此后其他线程执行 test_and_set 是 if 语句判断为 false，
	  // 因此不会输出自身 ID.
	if (!winner.test_and_set()) {
		std::cout << "thread #" << id << " won!\n";
	}
};

int main(int argc, const char *argv[])
{
	std::vector<std::thread> threads;
	std::cout << "spawning 10 threads that count to 1 million...\n";
	for (int i = 1; i <= 10; ++i)
		threads.push_back(std::thread(count1m, i));
	ready = true;

	for (auto & th : threads)
		th.join();


	
	system("pause");
	return EXIT_SUCCESS;
}