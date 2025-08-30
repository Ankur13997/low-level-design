#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 5;
queue<int> buffer;

class Semaphore {
    int count;
    mutex mtx;
    condition_variable cv;

public:
    Semaphore(int value = 0) : count(value) {}

    void acquire() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&]() { return count > 0; });
        count--;
    }

    void release() {
        unique_lock<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
};

mutex mtx;                    // Protects buffer
Semaphore empty(BUFFER_SIZE); // Initially all slots are empty
Semaphore full(0);           // Initially no item is present

void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        int item = id * 100 + i;
        empty.acquire(); // Wait for empty slot
        {
            lock_guard<mutex> lock(mtx);
            buffer.push(item);
            cout << "Producer " << id << " produced: " << item << endl;
        }
        full.release(); // Signal that item is available
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        full.acquire(); // Wait for item
        int item;
        {
            lock_guard<mutex> lock(mtx);
            item = buffer.front();
            buffer.pop();
            cout << "Consumer " << id << " consumed: " << item << endl;
        }
        empty.release(); // Signal empty slot
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

int main() {
    thread p1(producer, 1);
    thread p2(producer, 2);
    thread c1(consumer, 1);
    thread c2(consumer, 2);

    p1.join();
    p2.join();
    c1.join();
    c2.join();

    return 0;
}
