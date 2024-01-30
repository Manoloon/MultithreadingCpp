# Execution Policies (std::execution)
# Sequential (std::execution::seq)
- Will run a single instruction per data item.
# Parallel (std::execution::par)
- Will run a single instruction per several data items.
# Vectorized (std::execution::unseq)
- Will run several instructions per each data item at the same time.
# Parallel and Vectorized (std::execution::par_unseq)
- will run several instructions per several data items at the same time.