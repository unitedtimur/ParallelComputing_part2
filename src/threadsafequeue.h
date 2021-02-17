#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <thread>
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeQueue
{
public:
    explicit ThreadSafeQueue() = default;

    T &front();
    T &back();
    bool empty();
    size_t size();
    void push(const T &value);
    void pop();

private:
    std::queue<T> m_deque;
    mutable std::mutex m_mutex;
};

template<typename T>
T &ThreadSafeQueue<T>::front()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_deque.front();
}

template<typename T>
T &ThreadSafeQueue<T>::back()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_deque.back();
}

template<typename T>
bool ThreadSafeQueue<T>::empty()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_deque.empty();
}

template<typename T>
size_t ThreadSafeQueue<T>::size()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_deque.size();
}

template<typename T>
void ThreadSafeQueue<T>::push(const T &value)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deque.push(value);
}

template<typename T>
void ThreadSafeQueue<T>::pop()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deque.pop();
}

#endif // THREADSAFEQUEUE_H
