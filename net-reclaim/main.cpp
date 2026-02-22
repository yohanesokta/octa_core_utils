#include <iostream>
#include <cstdio>
#include <memory>
#include <string>
#include <array>
#include <thread>
#include <chrono>
#include <regex>

enum class PingResultType {
    SUCCESS,
    TIMEOUT,
    FAIL
};

struct PingResult {
    PingResultType type;
    std::string time;
};

PingResult pingGoogle()
{
    const std::string command = "ping -n 1 8.8.8.8";
    std::regex timeRegex("time[=<]([0-9.]+)ms");
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
    if (!pipe)
        return {PingResultType::FAIL, ""};
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    if (result.find("Request timed out") != std::string::npos)
        return {PingResultType::TIMEOUT, ""};
    std::smatch match;
    if (std::regex_search(result, match, timeRegex))
        return {PingResultType::SUCCESS, match[1]};
    return {PingResultType::FAIL, ""};
}

void resetNetwork()
{
    std::cout << "\nPing gagal! Menjalankan perintah pemulihan jaringan...\n";
    system("ipconfig /release");
    system("ipconfig /renew");
    system("ipconfig /flushdns");
    std::cout << "Pemulihan jaringan selesai.\n";
}

int main()
{
    while (true)
    {
        PingResult result = pingGoogle();

        system("cls"); 

        if (result.type == PingResultType::SUCCESS)
        {
            std::cout << "ping: " << result.time << " ms\n";
        }
        else if (result.type == PingResultType::TIMEOUT)
        {
            std::cout << "RTO\n";
        }
        else
        {
            std::cout << "ping gagal total.\n";
            resetNetwork();
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
