#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
int main(int argc, char const *argv[])
{
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
    std::ofstream myfile;

    for (size_t i = 0; i < 100000; i++)
    {
        myfile.open(std::to_string(i) + ".txt");
        myfile << "Writing this to a file.\n";
        myfile.close();
    }

    return 0;
}
