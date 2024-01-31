# Algorithms Sequential and Policies Friendly Versions

- std::accumulate() : Accumulate values from a vector sequentially.
 ---std::inclusive_scan() does the same but accept policies
 ---std::exclusive_scan() vec(1,2,3,4) -> vec2(1,3,6,10).
- std::transform() : transform a value by a lambda sequentially.
-- std::inner_product() : Apply Map and Reduce pattern sequentially.
-- std::transform_reduce() : apply Map And Reduce Pattern accepting policies.