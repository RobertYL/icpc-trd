/**
 * Author: Thomas Marlowe
 * Description: RNG in C++ for Wilbert.
 */
#pragma once
mt19937 rng(time(0)); // 32 bits
mt19937_64 rng64(time(0)); // 64 bits
rng(), rng64(); // random unsigned 32 bit and 64 bit resp.
uniform_int_distribution<>(0,10)(rng); // random integer in [0,10]
uniform_real_distribution<>(0,10)(rng); // random double in [0,10]
normal_distribution<>(0,10)(rng); // mean=0, stddev=10
// like every other distribution exists too, look in offline C++ reference.
vector<int> vec = {0,1,2};
ranges::shuffle(vec, rng); // shuffle vector
vector<int> sample;
ranges::sample(vec, back_inserter(sample), 2, rng); // sample 2 elements from vec, push to sample
minstd_rand min_rng; // much faster RNG with limited randomness