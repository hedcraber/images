#include <cmath>
#include<chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  cv::Mat img(180, 768, CV_8UC1);
  // draw dummy image
  img = 0;

  for (int j = 0; j < 180; j++ ) {
	  for (int i = 0; i < 768; i+=3 ) {
		  img.at<uint8_t>(j, i) = i/3;
		  img.at<uint8_t>(j, i+1) = i/3;
		  img.at<uint8_t>(j, i+2) = i/3;
	  }
  }

	cv::Mat img_2(180, 768, CV_8UC1);
	auto start = std::chrono::high_resolution_clock::now();
	auto start1 = clock();
	img.convertTo(img_2, CV_32F, 1 / 255.0);
	cv::pow(img_2, 2.3, img_2);
	img_2.convertTo(img_2, CV_8UC1, 255);
	auto stop = std::chrono::high_resolution_clock::now();
	auto rTime1 = clock() - start1;
	cv::Mat img_3(180, 768, CV_8UC1);
	img.copyTo(img_3);
	auto start2 = clock();

	for (size_t j = 0; j < 180; j++)
	{
		for (size_t i = 0; i < 768; i++)
		{
			img_3.at<uint8_t>(j, i) = pow((i / 3) / 255.0, 2.3) * 255;
		}
	}
  float rTime2 = clock() - start2;
  cv::Mat img_4(180, 768, CV_8UC1);
  img(cv::Rect2d(0, 0, 768, 60)).copyTo(img_4(cv::Rect2d(0, 0, 768, 60)));
  img_2(cv::Rect2d(0, 0, 768, 60)).copyTo(img_4(cv::Rect2d(0, 60, 768, 60)));
  img_3(cv::Rect2d(0, 0, 768, 60)).copyTo(img_4(cv::Rect2d(0, 120, 768, 60)));
  cv::rectangle(img_4, cv::Rect2d(0, 0, 768, 60), { 100 });
  cv::rectangle(img_4, cv::Rect2d(0, 60, 768, 60), { 150 });
  cv::rectangle(img_4, cv::Rect2d(0, 120, 768, 60), { 250 });
  std::cout << "Time for 1 GC = " << rTime1 / 1000.0F << " ms" << '\n';
  std::cout << "Time for 2 GC = " << rTime2 / 1000.0F << " ms" << '\n';

  // save result
  cv::imwrite("lab03.png", img_4);
  cv::imshow("lab03.png", img_4);
  cv::waitKey(0);




}
