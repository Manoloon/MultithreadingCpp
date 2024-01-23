#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

using namespace std::chrono_literals;

std::string sdata;
bool update_progress = false;
bool completed = false;

std::mutex data_mutex;
std::mutex completed_mutex;

std::condition_variable data_cv;
std::condition_variable complete_cv;

void FetchData(){
    for(int i =0;i<5;i++){
        std::cout << "Fetcher thread waiting for data" << std::endl;
        std::this_thread::sleep_for(2s);

        std::unique_lock data_lck(data_mutex);
        sdata += "block " + std::to_string(i+1) + " ";
        std::cout << "fetched sdata :" << sdata << std::endl;
        update_progress = true;
        data_lck.unlock();
        data_cv.notify_all();
    }
    std::cout << "Fetch sdata completed" << std::endl;
    std::lock_guard<std::mutex> completed_lck(completed_mutex);
    complete_cv.notify_all();
    completed = true;
}

void ProgressBar(){
    size_t len = 0;
    while(true){
        std::cout << "Progress Bar waiting for Data" << std::endl;
        std::unique_lock<std::mutex> data_lck(data_mutex);
        data_cv.wait(data_lck,[]{return update_progress;});

        len = sdata.size();
        update_progress = false;
        data_lck.unlock();
        std::cout << "Received : " << len << " bytes so far." << std::endl;
        std::unique_lock complete_lck(completed_mutex);
        if(complete_cv.wait_for(complete_lck,10ms,[]{return completed;})){
            std::cout << "progress bar thread has ended " << std::endl;
            break;
        }
    }
}

void ProcessData(){
    std::this_thread::sleep_for(200ms);
    std::cout << "Processing Thread Data" << std::endl;
    std::unique_lock<std::mutex> complete_lck(completed_mutex);
    complete_cv.wait(complete_lck,[]{return completed;});
    complete_lck.unlock();

    std::lock_guard<std::mutex> data_lck(data_mutex);
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
