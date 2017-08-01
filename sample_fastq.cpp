#include <string>
#include "file.h"
#include "sampling.h"

using namespace std;

#define READFQ(fh) \
std::string id = (fh).readLine(); \
std::string seq = (fh).readLine(); \
std::string flag = (fh).readLine(); \
std::string qual = (fh).readLine();


int main (int argc, char* argv[]) {
  if(argc != 2 ) {
      std::cout << "Usage: sampleFastq <input fastq> > output_fastq"
      <<std::endl;
      return 0;
  }
  long seqNum = 0;
  long baseNum = 0;
  fileHandle fh1(argv[1]);
  fh1.fileOpen();
  while(!fh1.ifend()) {
    READFQ(fh1)
    if(id.empty()) continue;
    if(seq.empty() || flag.empty() || qual.empty()) {
      std::cerr << "fastq file format wrong!" <<std::endl;
      exit(-1);
    }
    
    seqNum++;
    baseNum += seq.length();
  }
  fh1.fileClose();
  
  int sampleNum = int(1e9 / (baseNum/seqNum));
  std::vector<int> sample = sampling(seqNum, sampleNum, (unsigned long)seqNum);

  int orderFlag = 0, i=0;
  fileHandle fh2(argv[1]);
  fh2.fileOpen();
  while(!fh2.ifend()) {
    READFQ(fh2)
    if(id.empty()) continue;
    if(i == sample[orderFlag]) {
      std::cout << id << '\n' << seq << '\n' << flag << '\n' << qual << std::endl;
      orderFlag++;
    }

    i++;
  }
  fh2.fileClose();

  return 0;
}
