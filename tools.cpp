int my_random(int inf, int max)
//returns a random number between inf and max (included !!) usind std::uniform_int_distribution
{
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(inf, max); // distribution in range [1, 6]
  return(dist6(rng));
}
