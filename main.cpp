#include <stdio.h>
#include <iostream>
#include <string>
#include <queue>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "filter.hpp"

/**
 *
 * Software in text mode for apply image filter.
 *
 * @author Gabriel H. Klok
 * @since 2018-04-01
 * @version 1.0
 *
 */

using namespace std;
using namespace cv;

void webcam(Filter*);
void photo(Filter*, string, string, int);
void help();
Mat choiceFilter(Filter*, Mat, int);
void choiceKey(int, int&, bool&);

int main(int argc, char** argv){
  string parameter;
  string msgError = "Not found parameter. Please use command './main --help' for details.";

  Filter *filter = new Filter();
   
  if(argc <= 1){
    cout << msgError << endl;
    return(-1);
  }

  parameter = argv[1];

  if(parameter.compare("-webcam") == 0){

    webcam(filter);

  }else if(parameter.compare("-webcam-bg") == 0){

    webcamBG(filter);

  }else if(parameter.compare("-photo") == 0){

    photo(filter, argv[2], argv[3], atoi(argv[4]));

  }else if(parameter.compare("--help") == 0){
    help();
  }else{
    cout << msgError << endl;
    return(-1);
  }

  return(1);
}


/**
 *
 */
void webcam(Filter *filter){
  int key = 0;
  bool loop = true;
  VideoCapture cap(0);
   
  if (!cap.isOpened()) {
    cout << "Can't open camera!" << endl;
  }

  while(loop){
    Mat frame;

    cap >> frame;
    if (frame.empty())
      break;    
    
    imshow( "Webcam", choiceFilter(filter, frame, key) );
    
    choiceKey(waitKey(1), key, loop);
  }
}


/**
 *
 */
void webcamBG(Filter *filter){
  int aux = 1;
  bool loop = true;
  VideoCapture cap(0);
  queue<Filter> frames;

  if (!cap.isOpened()){
    cout << "Can't open camera!" << endl;
  }

  while(loop){
    Mat frame;

    cap >> frame;
    if (frame.empty())
      break;

    if(aux < 10){
      frames.push(frame);
      aux++;
    }else{
      frames.push(frame);
      imshow("Webcam", mergeFrames());
      frames.pop();
    }
    
  }
}


/**
 *
 */
Mat mergeFrames(){
  Mat frameResponse;

   

  return frameResponse;
}


/**
 *
 */
void photo(Filter *filter, string urlImgIn, string urlImgOut, int key){
  Mat imgIn, imgOut;

  imgIn = imread(urlImgIn);
  if(!imgIn.data){
    cout << "Can't open to image: " + urlImgIn << endl;
  }else{

    imshow("Photo", choiceFilter(filter, imgIn, key));
    waitKey(0);
  }
}

/**
 *
 */
Mat choiceFilter(Filter *filter, Mat frame, int key){
  Mat frameResponse, frameHistogram, frameTmp;

  switch(key){
    case 1:
      filter->grayscale(frame, frameResponse);
      filter->histogram(frameResponse, frameHistogram);
      break;

    case 2:
      filter->grayscale(frame, frameResponse);
      filter->histogram(frameResponse, frameHistogram);
      break;

    case 3:
      filter->thresholding(frame, 230, frameResponse);
      filter->histogram(frameResponse, frameHistogram);
      break;

    case 4:
      filter->negative(frame, frameResponse);
      filter->histogram(frameResponse, frameHistogram);
      break;

    case 5:
      filter->zoomIn(frame, frameResponse);
      filter->histogram(frameResponse, frameHistogram);
      break;

    case 6:
      filter->zoomOut(frame, frameResponse);
      filter->histogram(frameResponse, frameHistogram);
      break;

    case 7:
      filter->grayscale(frame, frameTmp);
      filter->outgoingPoints(frameTmp, frameResponse);
      filter->histogram(frameResponse, frameHistogram);
      break;

    case 8:
      filter->grayscale(frame, frameTmp);
      filter->detectBordersRoberts(frameTmp, frameResponse);
      filter->histogram(frameResponse, frameHistogram);
      break;

    case 9:
      filter->grayscale(frame, frameTmp);
      filter->detectBordersSobel(frameTmp, frameResponse);
      filter->histogram(frameResponse, frameHistogram);
      break;

    case 10:
      filter->grayscale(frame, frameTmp);
      filter->detectBorderRobinson(frameTmp, frameResponse);
      filter->histogram(frameResponse, frameHistogram);
      break;      

    default:
      frameResponse = frame;
      filter->histogram(frameResponse, frameHistogram);
  }

  return frameResponse;
}

/**
 *
 */
void choiceKey(int value, int &key, bool &loop){
  switch(value){
    case 27:
      loop = false;
      break;

    case 48: //0
      key = 0;
      break;

    case 49: //1
      key = 1;
      break;

    case 50: //2
      key = 2;
      break;
    
    case 51: //3
      key = 3;
      break;

    case 52: //4
      key = 4;
      break;
  
    case 53: //5
      key = 5;
      break;

    case 54: //6
      key = 6;
      break;

    case 55: //7
      key = 7;
      break;

    case 56: //8
      key = 8;
      break;

    case 57: //9
      key = 9;
      break;

    case 113: //q
      key = 10;
      break;

  }
}

/**
 *
 */
void help(){
  cout << "Ajuda:" << endl;
  cout << endl;
  cout << "./main [OPTION] [PARAM1] [PARAM2]" << endl;
  cout << endl;
  cout << endl;
  cout << "./main -webcam                                     utiliza webcam" << endl;
  cout << "./main -photo [URL-IMAGE-IN] [URL-IMAGE-OUT]       aplica o filtro em uma imagem" << endl;
}

