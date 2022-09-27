#include <filesystem>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <string>
#include <iostream>
int main(int argc, char const *argv[])
{
    // 文件
    auto source_path = std::filesystem::current_path().append("source");
    auto target_path = std::filesystem::current_path().append("target");

    // 逻辑核心数
    int concurrent_count = std::thread::hardware_concurrency();

    std::vector<std::string> all_file;

    for (auto &&file : std::filesystem::directory_iterator(source_path))
    {
        all_file.push_back(file.path().string());
    }

    std::cout << all_file[0] << std::endl;

    return 0;
}
