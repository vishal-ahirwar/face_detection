#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>

#include<vector>
using namespace std;
using namespace cv;
void faceDetector(const Mat& image,
                  std::vector<Rect> &faces,
                  CascadeClassifier &face_cascade) {
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
        gray, 
        faces, 
        1.4, // pyramid scale factor
        3,   // lower thershold for neighbors count
        // here we hint the classifier to only look for one face
        CASCADE_SCALE_IMAGE + CASCADE_FIND_BIGGEST_OBJECT);
}
int main(int argc,char**argv)
{
        CommandLineParser parser(argc, argv,
                             "{help h||}"
                             "{face_cascade|data/haarcascades/haarcascade_frontalface_alt.xml|Path to face cascade.}"
                             "{eyes_cascade|data/haarcascades/haarcascade_eye_tree_eyeglasses.xml|Path to eyes cascade.}"
                             "{camera|0|Camera device number.}");
    parser.about( "\nThis program demonstrates using the cv::CascadeClassifier class to detect objects (Face + eyes) in a video stream.\n"
                  "You can use Haar or LBP features.\n\n" );
    parser.printMessage();
      String face_cascade_name = samples::findFile( parser.get<String>("face_cascade") );
        String eyes_cascade_name = samples::findFile( parser.get<String>("eyes_cascade") );

CascadeClassifier face_cascade;
if (not face_cascade.load(face_cascade_name)) {
    cerr << "Cannot load cascade classifier from file: " << face_cascade_name << endl;
    return -1;
}

// ... obtain an image in img

vector<Rect> faces;
Mat img;
VideoCapture cap(0);
while(true)
{
    cap.read(img);
    if(img.empty())
    {
        cerr<<"empty image!";
        return -1;
    };

    faceDetector(img, faces, face_cascade);

// Check if any faces were detected or not
if (faces.size() == 0) {
    cerr << "Cannot detect any faces in the image." << endl;
    return -1;
};
    imshow("web camera.",img);
    if(waitKey(10)==27)break;
}
    
    return 0;
}