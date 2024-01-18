#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>

using namespace std::chrono_literals;

std::string sdata;
bool update_progress = false;
bool completed = false;

std::mutex data_mutex;
std::mutex completed_mutex;

void FetchData(){
    for(int i =0;i<5;i++){
        std::cout << "Fetcher thread waiting for data" << std::endl;
        std::this_thread::sleep_for(2s);

        std::lock_guard data_lck(data_mutex);
        sdata += "block " + std::to_string(i+1) + " ";
        std::cout << "sdata :" << sdata << std::endl;
        update_progress = true;
    }
    std::cout << "Fetch sdata completed" << std::endl;
    std::lock_guard completed_lck(completed_mutex);
    completed = true;
}

void ProgressBar(){
    size_t len = 0;
    while(true){
        std::cout << "Progress Bar waiting for Data" << std::endl;
        std::unique_lock data_lck(data_mutex);
        while(!update_progress){
            data_lck.unlock();
            std::this_thread::sleep_for(10ms);
            data_lck.lock();
        }
        len = sdata.size();
        update_progress = false;
        data_lck.unlock();
        std::cout << "Received : " << len << " bytes so far." << std::endl;
        std::lock_guard complete_lck(completed_mutex);
        if(completed){
            std::cout << " progress bar completed" << std::endl;
            break;
        }
    }
}

void ProcessData(){
    std::cout << "Processing Thread Data" << std::endl;
    std::unique_lock complete_lck(completed_mutex);
    while (!completed){
        complete_lck.unlock();
        std::this_thread::sleep_for(10ms);
        complete_lck.lock();
    }
    complete_lck.unlock();
    std::lock_guard data_lck(data_mutex);
    std::cout << "Processing Data " << std::endl;
}

int main() {
    std::thread fetcher(FetchData);
    std::thread progress(ProgressBar);
    std::thread processor(ProcessData);
    fetcher.join();
    progress.join();
    processor.join();

    return 0;
}
