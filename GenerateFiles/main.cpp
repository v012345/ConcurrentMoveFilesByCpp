#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#define FILES_COUNT 100000
#define IS_CONCURRENT true

void spawnFiles(int startIndex, int endIndex)
{
    std::ofstream myfile;
    for (size_t i = startIndex; i < endIndex; i++)
    {
        myfile.open(std::to_string(i) + ".txt");
        for (size_t i = 0; i < 5000; i++)
        {
            myfile << "Writing this to a file. Writing this to a file. Writing this to a file. Writing this to a file.\n";
        }
        myfile.close();
    }
}

int main(int argc, char const *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    if (std::filesystem::exists(std::filesystem::current_path().append("source")))
    {
        std::filesystem::remove_all(std::filesystem::current_path().append("source"));
    }
    if (std::filesystem::exists(std::filesystem::current_path().append("target")))
    {
        std::filesystem::remove_all(std::filesystem::current_path().append("target"));
    }
    std::filesystem::create_directory("source");
    std::filesystem::create_directory("target");

    std::filesystem::current_path(std::filesystem::current_path().append("source"));
    int concurrent_count = std::thread::hardware_concurrency();

    std::vector<std::thread> spawnFilesThread;

    if (IS_CONCURRENT)
    {
        for (size_t i = 0; i < concurrent_count; i++)
        {
            spawnFilesThread.push_back(std::thread(spawnFiles, i * (FILES_COUNT / concurrent_count), (i + 1) * (FILES_COUNT / concurrent_count)));
        }
        for (auto &&t : spawnFilesThread)
        {
            t.join();
        }
    }
    else
    {
        spawnFiles(0, FILES_COUNT);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "run time " << duration.count() / 1000000 << " s" << std::endl;
    return 0;
}
