#include <algorithm>
#include <cassert>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

#include "utils.h"


template<class T>
class AdderWorker {
public:
    using InputsPtr = const std::vector<std::vector<T>>*;
    using OutputPtr = std::vector<T>*;

    AdderWorker()
    : enable_(true)
    , start_(false)
    , done_(false) {
        thread_ptr_ = std::make_unique<std::thread>(
            &AdderWorker::processingLoop, this);
    }

    ~AdderWorker() {
        kill();
    }

    void kill() {
        if (thread_ptr_) {
            {
                std::lock_guard<std::mutex> locker(m_);
                enable_ = false;
            }
            cv_.notify_one();
            thread_ptr_->join();
            thread_ptr_ = nullptr;
        }
    }

    bool isReady() {
        std::lock_guard<std::mutex> locker(m_);
        return done_;
    }

    void wait() {
        std::unique_lock lk(m_);
        cv_done.wait(lk, [this]() { return done_; });
    }

    void run(InputsPtr inputs, OutputPtr output, int offset, int size) {
        std::lock_guard<std::mutex> locker(m_);
        inputs_ptr_ = inputs;
        output_ptr_ = output;
        offset_ = offset;
        length_ = size;
        start_ = true;
        done_ = false;
        cv_.notify_one();
    }

private:
    void processingLoop() {
        while (true)
        {
            std::unique_lock lk(m_);
            cv_.wait(lk, [this]() { return start_ || (!enable_); });
            if (!enable_)
                break;
            start_ = false;

            std::vector<T>& output = *output_ptr_;
            auto& inputs = *inputs_ptr_;
            computeSum(inputs, output, offset_, length_);

            done_ = true;
            cv_done.notify_all();
        }
    }

    std::unique_ptr<std::thread> thread_ptr_;
    std::mutex m_;
    std::condition_variable cv_;
    std::condition_variable cv_done;
    bool enable_;
    bool start_;
    bool done_;

    InputsPtr inputs_ptr_;
    OutputPtr output_ptr_;
    int offset_;
    int length_;
};
