#include "custom_exec.h"

#include <future>

std::vector<int> run(std::vector<std::function<int(int)>> tasks, int i) {
    std::vector<int> ans;
    std::vector<std::future<int>> futures;
    for (auto& task : tasks)
        futures.emplace_back(std::async(task, i));
    for (auto& f : futures)
        ans.push_back(f.get());
    return ans;
}
