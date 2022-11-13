#include <iostream>
#include <thread>
#include <queue>
#include <future>
#include <mutex>
#include <algorithm>


template <class T>
class MessageQueue{
public:
    T receive(){
        std::unique_lock<std::mutex> ulock(_mutex);
        _cond.wait(ulock, [this](){return !_message.empty(); 
            }
        );

    T msg = std::move(_message.back());
    _message.pop_back();

    return msg;
    }

    void send(T &&msg){

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> ulock(_mutex);

        std::cout << "   Message " << msg << " has been sent to the queue" << std::endl;
        _message.push_back(std::move(msg));
        _cond.notify_one();
    }

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _message;
};


int main(){
    std::shared_ptr<MessageQueue<int>> queue(new MessageQueue<int>);
    std::cout << " Spawning threads ..." << std::endl;

    std::vector<std::future<void>> ftrs;
    for(int i = 0; i < 10; i++){
        int message = i;

        ftrs.emplace_back(std::async(std::launch::async, 
        &MessageQueue<int>::send, 
        queue, std::move(message))
        );
    }

    std::for_each(ftrs.begin(), ftrs.end(), [](std::future<void> &ftr){
        ftr.wait();
    }
    );

    return 0;
}