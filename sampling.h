#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

template <typename T>
std::vector<T> sampling (std::vector<T>& dataset, int sampleNum) {
  std::map<int, T> sampleMap;
  srand((unsigned)time(NULL));
  for (int i = 0; i < dataset.size(); i++) {
    if (i < sampleNum) {
      sampleMap[i] = dataset[i];
    }
    else {
      int randValue =int( rand()/RAND_MAX * dataset.size());
      if(randValue < sampleNum)
        sampleMap[randValue] = dataset[i];
    }
  }
  
  std::vector<T> sample;
  for(auto it = sampleMap.cbegin(); it != sampleMap.cend(); ++it)
    sample.push_back(it->second);

  return sample;
}


std::vector<int> sampling (int total, int sampleNum, unsigned long seed) {
  std::vector<int> sample(sampleNum);
  srand(seed);
  for (int i = 1; i <= total; i++) {
    if (i < sampleNum) {
      sample[i-1] = i;
    }
    else {
      int randValue = int(rand()/RAND_MAX * (total-1)) + 1;
      if (randValue <= sampleNum)
        sample[randValue-1] = i;
    }
  }
  std::sort(sample.begin(), sample.end());

  return sample;
}

std::vector<int> sampling (int total, int sampleNum) {
  return sampling(total, sampleNum, (unsigned long)time(NULL));
}
