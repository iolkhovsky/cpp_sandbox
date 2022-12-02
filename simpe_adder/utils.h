#pragma once

#include <cassert>
#include <vector>

template<class T>
std::vector<std::vector<T>> generateInputs(int size, int n) {
    std::vector<std::vector<T>> out(n);
    T cntr = 0;
    for (auto& a: out) {
        a.resize(size);
        for (auto& item: a)
            item = cntr++;
    }
    return out;
}

template<class T>
void checkResult(const std::vector<std::vector<T>>& inputs, std::vector<T>& output) {
    int n_arrays = static_cast<int>(inputs.size());
    int array_size = static_cast<int>(inputs[0].size());
    for (int i = 0; i < array_size; i++) {
        T acc = 0;
        for (int j = 0; j < n_arrays; j++)
            acc += inputs[j][i];
        if (acc != output[i])
            throw std::runtime_error("Sum is invalid");
    }
}

template<class T>
void computeSum(const std::vector<std::vector<T>>& inputs, std::vector<T>& output, int offset, int length) {
    int n_arrays = static_cast<int>(inputs.size());
    for (int i = offset; i < length; i++) {
        T acc = 0;
        for (int arr_idx = 0; arr_idx < n_arrays; arr_idx++)
            acc += inputs[arr_idx][i];
        output[i] = acc;
    }
}

std::vector<std::pair<int, int>> splitIntoIntervals(int size, int intervals) {
    assert(intervals > 0);
    int interval_width = std::min(size, std::max(1, size / intervals));
    std::vector<std::pair<int, int>> res = {{0, interval_width}};
    for (int i = 1; i < intervals; i++) {
        const auto& [prev_offset, prev_length] = res.back();
        int offset = prev_offset + prev_length;
        bool last_interval = i == intervals - 1;
        int width = std::min(size - offset, interval_width);
        if (last_interval)
            width = size - offset;
        res.push_back({offset, width});
    }
    return res;
}
