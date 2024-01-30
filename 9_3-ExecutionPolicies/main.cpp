#include "sequential.h"
#include "parallel.h"
#include "vectorized.h"
#include "par_vec.h"

int main() {
    seq::run();
    par::run();
    unseq::run();
    par_unseq::run();
    return 0;
}
