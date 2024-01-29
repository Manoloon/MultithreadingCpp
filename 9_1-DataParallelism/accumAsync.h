//
// Created by Manoloon on 29/1/2024.
//

#ifndef INC_9_1_DATAPARALLELISM_ACCUMASYNC_H
#define INC_9_1_DATAPARALLELISM_ACCUMASYNC_H

#include <future>
#include <iostream>
#include <vector>

namespace asyncAccum {
    double accum(double *begin, double *end) {
        return std::accumulate(begin, end, 0.0);
    }

    double add_parallel(std::vector<double> &vec) {
        auto firstElem = &vec[0];
        auto numElem = vec.size();

        //start threads
        auto fut1 = std::async(std::launch::async, accum, firstElem, firstElem + numElem / 4);
        auto fut2 = std::async(std::launch::async, accum, firstElem + numElem / 4, firstElem + 2 * numElem / 4);
        auto fut3 = std::async(std::launch::async, accum, firstElem + 2 * numElem / 4, firstElem + 3 * numElem / 4);
        auto fut4 = std::async(std::launch::async, accum, firstElem + 3 * numElem / 4, firstElem + numElem);
        return fut1.get() + fut2.get() + fut3.get() + fut4.get();
    }
}
#endif //INC_9_1_DATAPARALLELISM_ACCUMASYNC_H
