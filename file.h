#include <iostream>
#include <fstream>
#include <string>
#include <gzstream.h>

using namespace std;

class fileHandle {
        public:
                fileHandle(std::string file) : file_(file) {
                        if(file.substr(file.size()-3) == ".gz")
                                FTYPE_ = GZS;
                        else FTYPE_ = FS;
                };
                ~fileHandle() { }

                void fileOpen() {
                        if(FTYPE_ == GZS)  gzs.open(file_.c_str());
                        else fs.open(file_.c_str());
                }
                void fileClose() {
                        if(FTYPE_ == GZS) gzs.close();
                        else fs.close();
                }
                std::string readLine () {
                        std::string line;
                        if(FTYPE_ == GZS) getline(gzs, line);
                        else getline(fs, line);

                        return line;
                }
                bool ifend() {
                        if(FTYPE_ == GZS)  return gzs.eof();
                        else return fs.eof();
                }
        private:
                std::string file_;
                enum FTYPE {GZS, FS} FTYPE_;
                igzstream gzs;
                ifstream fs;
};
