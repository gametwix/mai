#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <queue>
#include <functional>
#include <atomic>
#include <vector>

#include <iostream>

template<typename T>
class TFunctions
{
private:
bool started = false, running = true;
    std::mutex mutex_queue;
    std::thread thread;
    std::condition_variable cv;
    std::queue<T> queue;
    std::vector<std::function<void(const std::vector<T>&)>> functions;
    std::size_t queue_max_size = 0;
public:
    TFunctions(size_t queue_ms):queue_max_size(queue_ms){}

    ~

};