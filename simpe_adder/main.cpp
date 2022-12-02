#include <future>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "profile.h"
#include "worker.h"
#include "utils.h"

class IAdder {
public:
    virtual void operator()(const std::vector<std::vector<float>>& inputs, std::vector<float>& output) = 0;
    virtual std::string name() = 0;
    virtual ~IAdder() = default;
};

class NaiveAdder : public IAdder{
public:
    void operator()(const std::vector<std::vector<float>>& inputs, std::vector<float>& output) override {
        computeSum<float>(inputs, output, 0, static_cast<int>(output.size()));
    }
    std::string name() override { return "Naive"; }
};

class AsyncAdder : public IAdder{
public:
    explicit AsyncAdder(int threads)
    : threads_(threads) {}

    void operator()(const std::vector<std::vector<float>>& inputs, std::vector<float>& output) override {
        int size = static_cast<int>(output.size());
        auto intervals = splitIntoIntervals(size, threads_);
        std::vector<std::future<void>> futures;
        for (const auto& [offset, length] : intervals)
            futures.push_back(std::async(launch::async, [&](int int_offset, int int_size){
                computeSum<float>(inputs, output, int_offset, int_size);
            }, offset, length));
        for (auto& f : futures)
            f.wait();
    }
    std::string name() override { return "Async (" + std::to_string(threads_) + ")"; }
private:
    int threads_;
};

class ParallelAdder : public IAdder{
public:
    explicit ParallelAdder(int threads)
    : workers_(threads) {}

    void operator()(const std::vector<std::vector<float>>& inputs, std::vector<float>& output) override {
        int size = static_cast<int>(output.size());
        auto intervals = splitIntoIntervals(size, static_cast<int>(workers_.size()));

        int worker_id = 0;
        for (const auto& [offset, length]: intervals) {
            workers_[worker_id++].run(&inputs, &output, offset, length);
        }
        for (auto& worker : workers_)
            worker.wait();
    }

    std::string name() override { return "Parallel (" + std::to_string(workers_.size()) + ")"; }
private:
    std::vector<AdderWorker<float>> workers_;
};

int main(int argc, char** argv) {
    int array_size = 10240;
    int n_arrays = 20;

    if (argc > 1)
        array_size = std::atoi(argv[1]);
    std::cout << "Array size: " << array_size << "\n";
    if (argc > 2)
        n_arrays = std::atoi(argv[2]);
    std::cout << "Arrays number: " << n_arrays << "\n";

    auto arrays = generateInputs<float>(array_size, n_arrays);
    std::vector<float> result(array_size);

    std::vector<std::shared_ptr<IAdder>> adders {
        std::make_shared<NaiveAdder>(),
        std::make_shared<AsyncAdder>(1),
        std::make_shared<AsyncAdder>(2),
        std::make_shared<AsyncAdder>(10),
        std::make_shared<AsyncAdder>(20),
        std::make_shared<ParallelAdder>(1),
        std::make_shared<ParallelAdder>(2),
        std::make_shared<ParallelAdder>(10),
        std::make_shared<ParallelAdder>(20),
    };

    for (auto& adder : adders) {
        std::cout << "Running <" << adder->name() << "> adder...\n";
        {
            LOG_DURATION("Duration");
            for (int i = 0; i < 1000; i++) {
                adder->operator()(arrays, result);
            }
        }
        checkResult(arrays, result);
        std::cout << "Checked\n";
        std::cout << "\n\n";
    }
    return 0;
}