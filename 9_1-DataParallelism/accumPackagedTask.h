//
// Created by Manoloon on 29/1/2024.
//

#ifndef INC_9_1_DATAPARALLELISM_ACCUMPACKAGEDTASK_H
#define INC_9_1_DATAPARALLELISM_ACCUMPACKAGEDTASK_H
#include <future>
#include <vector>

namespace accumPackagedTask{
    double accum(double *begin, double *end) {
        return std::accumulate(begin, end, 0.0);
    }
    double add_parallel(std::vector<double> &vec) {
        using taskType = double(double*,double*);
        std::packaged_task<taskType> ptask1(accum);
        std::packaged_task<taskType> ptask2(accum);
        std::packaged_task<taskType> ptask3(accum);
        std::packaged_task<taskType> ptask4(accum);

        auto fut1 = ptask1.get_future();
        auto fut2 = ptask2.get_future();
        auto fut3 = ptask3.get_future();
        auto fut4 = ptask4.get_future();

        auto firstElem = &vec[0];
        auto size = vec.size();

        std::thread thr1(std::move(ptask1),firstElem,firstElem + size/4);
        std::thread thr2(std::move(ptask2),firstElem+ size/4,firstElem + 2*size/4);
        std::thread thr3(std::move(ptask3),firstElem+ 2*size/4,firstElem + 2*size/4);
        std::thread thr4(std::move(ptask4),firstElem + 2*size/4,firstElem + size);
        thr1.join();
        thr2.join();
        thr3.join();
        thr4.join();
        return fut1.get() + fut2.get() + fut3.get() + fut4.get();
    }
}
#endif //INC_9_1_DATAPARALLELISM_ACCUMPACKAGEDTASK_H
