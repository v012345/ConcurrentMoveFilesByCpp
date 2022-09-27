#include <filesystem>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <string>
#include <iostream>
#define IS_CONCURRENT true

std::vector<std::string> all_files;

void moveFiles(int startIndex, int endIndex)
{

    for (size_t i = startIndex; i < endIndex; i++)
    {
        std::filesystem::copy(std::filesystem::current_path().append("source").append(all_files[i]), std::filesystem::current_path().append("target").append(all_files[i]), std::filesystem::copy_options::overwrite_existing);
        std::filesystem::remove(std::filesystem::current_path().append("source").append(all_files[i]));
    }
}

int main(int argc, char const *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    // 文件
    auto source_path = std::filesystem::current_path().append("source");
    auto target_path = std::filesystem::current_path().append("target");

    // 逻辑核心数
    int concurrent_count = std::thread::hardware_concurrency();

    for (auto &&file : std::filesystem::directory_iterator(source_path))
    {
        all_files.push_back(file.path().filename().string());
    }

    std::vector<std::thread> moveFilesThread;

    if (IS_CONCURRENT)
    {
        for (size_t i = 0; i < concurrent_count; i++)
        {
            moveFilesThread.push_back(std::thread(moveFiles, i * (all_files.size() / concurrent_count), (i + 1) * (all_files.size() / concurrent_count)));
        }
        for (auto &&t : moveFilesThread)
        {
            t.join();
        }
    }
    else
    {
        for (auto &&file : all_files)
        {
            std::filesystem::copy(std::filesystem::current_path().append("source").append(file), std::filesystem::current_path().append("target").append(file), std::filesystem::copy_options::overwrite_existing);
            std::filesystem::remove(std::filesystem::current_path().append("source").append(file));
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "run time " << duration.count() / 1000000 << " s" << std::endl;

    return 0;
}
