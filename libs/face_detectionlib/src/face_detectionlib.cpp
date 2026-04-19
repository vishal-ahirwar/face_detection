#include "face_detectionlib.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void faceDetector(const Mat& image, std::vector<Rect>& faces,
                                     CascadeClassifier& face_cascade) {
  Mat gray;

  // The cascade classifier works best on grayscale images
  if (image.channels() > 1) {
    cvtColor(image, gray, COLOR_BGR2GRAY);
  } else {
    gray = image.clone();
  }

  // Histogram equalization generally aids in face detection
  equalizeHist(gray, gray);

  faces.clear();

  // Run the cascade classifier
  face_cascade.detectMultiScale(
      gray, faces,
      1.4,  // pyramid scale factor
      3,    // lower thershold for neighbors count
      // here we hint the classifier to only look for one face
      CASCADE_SCALE_IMAGE + CASCADE_FIND_BIGGEST_OBJECT);
}

void getFaceCascade(
                                       CascadeClassifier& face_cascade) {
  CommandLineParser parser(
      face_detectionlib::getArgc(), face_detectionlib::getArgv(),
      "{help h||}"
      "{face_cascade|data/haarcascades/haarcascade_frontalface_alt.xml|Path to "
      "face cascade.}"
      "{eyes_cascade|data/haarcascades/"
      "haarcascade_eye_tree_eyeglasses.xml|Path to eyes cascade.}"
      "{camera|0|Camera device number.}");
  parser.about(
      "\nThis program demonstrates using the cv::CascadeClassifier class to "
      "detect objects (Face + eyes) in a video stream.\n"
      "You can use Haar or LBP features.\n\n");
  parser.printMessage();
  String face_cascade_name =
      samples::findFile(parser.get<String>("face_cascade"));
  String eyes_cascade_name =
      samples::findFile(parser.get<String>("eyes_cascade"));

  if (not face_cascade.load(face_cascade_name)) {
    cerr << "Cannot load cascade classifier from file: " << face_cascade_name
         << endl;
  }
}

void face_detectionlib::run() {
  CascadeClassifier face_cascade;
  getFaceCascade(face_cascade);
  vector<Rect> faces;
  Mat img;
  VideoCapture cap(0);
  while (true) {
    cap.read(img);
    if (img.empty()) {
      cerr << "empty image!";
      return;
    };

    faceDetector(img, faces, face_cascade);


    for (size_t i = 0; i < faces.size(); i++) {
      rectangle(img, faces[i], Scalar(25, 78, 125), 2);
    }
    imshow("Web camera", img);
    if (waitKey(10) == 27) break;
  }
}