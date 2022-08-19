#include <opencv2/opencv.hpp>
#include <stdio.h>

cv::Mat CreateMarker(cv::String FILENAME, int size, cv::Mat mat);
cv::Mat OffsetMarker(cv::Mat mat, int offset);
cv::Mat outMat;
int MarkerDecoder(cv::Mat mat);

std::string MYFILE = "./myMarker_";

int index = 4;
cv::Mat markerMat = (cv::Mat_<int>(index, index) <<
	1, 0, 0, 0,
	0, 0, 0, 1,
	0, 1, 0, 0,
	0, 1, 1, 0
	);


void main() {
	outMat = CreateMarker(MYFILE, 400, markerMat);
	outMat = OffsetMarker(outMat, 5);
	MYFILE += std::to_string(MarkerDecoder(markerMat));
	MYFILE += ".jpg";
	cv::imwrite(MYFILE, outMat);
}

cv::Mat CreateMarker(cv::String FILENAME, int size, cv::Mat idMat) {
	int s = size * index / (index + 2);
	cv::Mat creMat(s, s, CV_8U, cv::Scalar(255));
	cv::Mat dreMat(size, size, CV_8U, cv::Scalar(0));

	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			int a = 255 * (1 - idMat.at<int>(index * i / s, index * j / s));
			creMat.at<uchar>(i, j) = a;
		}
	}

	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			dreMat.at<uchar>(i + size / (index + 2), j + size / (index + 2)) = creMat.at<uchar>(i, j);
		}
	}
	return dreMat;
}

cv::Mat OffsetMarker(cv::Mat mat, int offset) {
	cv::Mat out(mat.rows + 2 * offset, mat.cols + 2 * offset, CV_8U, cv::Scalar(255));
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.cols; j++) {
			out.at<uchar>(i + offset, j + offset) = mat.at<uchar>(i, j);
		}
	}
	return out;
}

int MarkerDecoder(cv::Mat mat) {
	int sum = 0;
	for (int i = 1; i < mat.rows * mat.cols; i++) {
		sum += mat.at<int>(i) * pow(2, i - 1);
		printf("inc = %f\n", mat.at<int>(i) * pow(2, i - 1));
	}
	return sum;
}