#include <opencv2/opencv.hpp>
#include <GL/freeglut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

string title = "track", bar_name = "Threshold";
int add_value = 0;
int markerindex = 4;
Mat image, gray, thres, trans;
Mat marker(60, 60, CV_8U, Scalar(0)), id(markerindex + 2, markerindex + 2, CV_8UC1, Scalar(0));
Mat id2(markerindex, markerindex, CV_32S, Scalar(0));
int winWidth = 400, winHeight = 300;
int degree = 0;

vector<vector<Point>> allContours;
vector<Point> approxCurve, dst;
Point2f src[4], ds[4];

void MyTrackBar(int value, void* userdata);
void MyMouse(int event, int x, int y, int flags, void* param);
void myPrintMat(Mat mat);
int MarkerDecoder(cv::Mat mat);
void MyMarkerArray(Mat src, Mat dst, int index);
bool MyCheckArray(Mat mat);
Mat MyRotateArray(Mat mat);
float dist(Point, Point);

//const string MYFILE[1] = { "../marker_image/MyMarker01.jpg" };

int main() {
	namedWindow(title);
	//createTrackbar(bar_name, title, &value, 1000, MyTrackBar);
	//setMouseCallback(title, MyMouse, 0);
	VideoCapture camera = VideoCapture(0);

	ds[0] = Point2f(0, 0);
	ds[1] = Point2f(60, 0);
	ds[2] = Point2f(60, 60);
	ds[3] = Point2f(0, 60);

	while (1) {
		int count = 0;
		Mat ct = Mat(winHeight, winWidth, CV_8UC3, Scalar(0));
		camera.read(image);
		//Mat image = imread(MYFILE1, 1);
		resize(image, image, Size(winWidth, winHeight));
		flip(image, image, 1);
		cvtColor(image, gray, COLOR_BGRA2GRAY);
		threshold(gray, thres, 60, 255, THRESH_BINARY);
		findContours(thres, allContours, RETR_LIST, CHAIN_APPROX_NONE);
		if (allContours.size() > 0) { // 윤곽선이 있으면...
			drawContours(ct, allContours, -1, Scalar(255, 255, 255), 1);
			for (int i = 0; i < allContours.size(); i++) { // 모든 윤곽선에 대하여 ...
				double eps = allContours[i].size() * 0.13; // 윤곽선 검출 감도
				approxPolyDP(allContours[i], approxCurve, eps, true);

				if (approxCurve.size() == 4 && isContourConvex(approxCurve) &&
					dist(approxCurve[0], approxCurve[1]) > 50 && dist(approxCurve[0], approxCurve[1]) < 150)
				{ // 사각형만...
					count++; // 사각형 갯수
					src[0] = approxCurve[0];
					src[1] = approxCurve[1];
					src[2] = approxCurve[2];
					src[3] = approxCurve[3];
					trans = getPerspectiveTransform(src, ds);
					warpPerspective(thres, marker, trans, Size(60, 60)); // 사각형 윤곽선을 변환

					MyMarkerArray(marker, id, markerindex); // id행렬에 이진행렬 
					if (MyCheckArray(id)) { // 테두리 검정인지, 코너에 검정 한개인지 확인
						line(image, approxCurve[0], approxCurve[1], Scalar(0, 0, 255), 2);
						line(image, approxCurve[1], approxCurve[2], Scalar(0, 0, 255), 2);
						line(image, approxCurve[2], approxCurve[3], Scalar(0, 0, 255), 2);
						line(image, approxCurve[3], approxCurve[0], Scalar(0, 0, 255), 2);
						flip(id, id, 1);
						id = MyRotateArray(id); // 좌상단에 검정 오게 회전
						for (int i = 0; i < id2.rows; i++) {
							for (int j = 0; j < id2.cols; j++) {
								if (id.at<uchar>(i + 1, j + 1) == 1) id2.at<int>(i, j) = 1;
								else id2.at<int>(i, j) = 0;
							}
						} // 가운데만 뽑아서 int로 변환, id2는 정렬된 축소 마커 이진 행렬
						//myPrintMat(id2);
						putText(image, to_string(MarkerDecoder(id2)),
							(approxCurve[0] + approxCurve[2]) * 0.5 + Point(-20, 5), 2, 0.5, Scalar(0, 255, 0));
					}

				} // 사각형만...
			} // 모든 윤곽선에 대하여 ...
		} // 윤곽선이 있으면...
		//resize(marker, marker, Size(300, 300));
		//if (MyCheckArray(id)) {
		//	if (degree != 3 && count > 0) rotate(marker, marker, degree);
		//	imshow("marker", marker);
		//}
		if (count == 0) marker = Mat(300, 300, CV_8U, Scalar(0));
		resize(image, image, Size(800, 600));
		imshow(title, image);
		if (waitKey(30) >= 0) break;
	}
	camera.release();
	return 0;
}

void MyTrackBar(int value, void* userdata) {
}

void MyMouse(int event, int x, int y, int flags, void* param) {
}

float dist(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void MyMarkerArray(Mat src, Mat dst, int index) {
	int r = src.rows / (index + 2);
	int c = src.cols / (index + 2);

	for (int i = 0; i < index + 2; i++) {
		for (int j = 0; j < index + 2; j++) {
			if (src.at<uchar>(r * (0.5 + i), c * (0.5 + j)) < 50) {
				dst.at<uchar>(i, j) = 1;
			}
			else {
				dst.at<uchar>(i, j) = 0;
			}
		}
	}
}
bool MyCheckArray(Mat mat) {
	int ch = 0;
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.cols; j++) {
			if ((i == 0 || i == mat.rows - 1 || j == 0 || j == mat.cols - 1) && mat.at<uchar>(i, j) == 0) {
				return false;
			}
		}
	}
	if ((int)mat.at<uchar>(1, 1) == 1) ch++;
	if ((int)mat.at<uchar>(1, mat.cols - 2) == 1) ch++;
	if ((int)mat.at<uchar>(mat.rows - 2, 1) == 1) ch++;
	if ((int)mat.at<uchar>(mat.rows - 2, mat.cols - 2) == 1) ch++;
	if (ch != 1) return false;
	return true;
}
Mat MyRotateArray(Mat mat) {
	Mat rot(markerindex + 2, markerindex + 2, CV_8U, Scalar(0));
	if ((int)mat.at<uchar>(1, 1) == 1) {
		rot = mat;
		degree = 3;
	}
	else if ((int)mat.at<uchar>(1, mat.cols - 2) == 1) {
		rotate(mat, rot, ROTATE_90_COUNTERCLOCKWISE);
		degree = ROTATE_90_COUNTERCLOCKWISE;
	}
	else if ((int)mat.at<uchar>(mat.rows - 2, 1) == 1) {
		rotate(mat, rot, ROTATE_90_CLOCKWISE);
		degree = ROTATE_90_CLOCKWISE;
	}
	else if ((int)mat.at<uchar>(mat.rows - 2, mat.cols - 2) == 1) {
		rotate(mat, rot, ROTATE_180);
		degree = ROTATE_180;
	}
	return rot;
}

void myPrintMat(Mat mat) {
	cout << "Mat : " << endl;
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.cols; j++) {
			cout << mat.at<int>(i, j) << "\t";
		}
		cout << endl;
	}

}

int MarkerDecoder(cv::Mat mat) {
	int sum = 0;
	for (int i = 1; i < mat.rows * mat.cols; i++)
		sum += mat.at<int>(i) * pow(2, i - 1);
	return sum;
}

void MyDisplay() {
	//glClear();

}