
#include <face_detectionlib.h>

#include <vector>

using namespace std;

int main(int argc, char** argv) {
  face_detectionlib::getArgvAndArgc(argc, argv);
  face_detectionlib::run();
  return 0;
}