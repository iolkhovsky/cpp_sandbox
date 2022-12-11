#pragma once

#include <functional>
#include <vector>

std::vector<int> run(std::vector<std::function<int(int)>> tasks, int i);
