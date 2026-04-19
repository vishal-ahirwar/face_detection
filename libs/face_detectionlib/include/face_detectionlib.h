#pragma once

#include <string>

class face_detectionlib {
  inline static int argc = 0;
  inline static char** argv = NULL;

 public:
  static void getArgvAndArgc(int _argc, char** _argv) {
    argc = _argc;
    argv = _argv;
  }
  static int getArgc() { return argc; }
  static char** getArgv() { return argv; } 
 public:
  static void run();
};  // namespace face_detectionlib