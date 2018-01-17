int my_random(int inf, int max)
//returns a random number between inf and max (included !!) usind std::uniform_int_distribution
{
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(inf, max); // distribution in range [1, 6]
  return(dist6(rng));
}

template<class T>
int index(std::vector<T> v, T value) {
  // Retourne l'index de l'élément value dans le vecteur v
  int idx;
  int flag = 0;
  if !(v.empty()) {
    int i=0;
    while ((i<v.size()) && (!flag)) {
      if (v[i] == value) {
        idx = i;
        flag = 1;
      }
      i++;
    }
  }
  if (flag) {return idx;}
  else {return -1;}
}

template<class T>
int maxIndex(std::vector<T> v) {
  // Retourne l'index de l'élément de valeur maximale du vecteur v
  int idx;
  T m = v[0];
  if !(v.empty()) {
    for (int i=0 ; i<v.size() ; i++) {
      if (v[i] > m) {
        m = v[i];
        idx = i;
      }
    }
    return idx;
  }
  else {return -1;}
}
