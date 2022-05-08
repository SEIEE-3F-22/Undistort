#ifndef UNDISTORT_UNDISTORT_H
#define UNDISTORT_UNDISTORT_H

#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

using namespace std;
namespace py = pybind11;

class Undistort {
public:
    Undistort(int width, int height);

    py::array_t<unsigned char> remap(py::array_t<unsigned char> &src);

private:
    cv::Mat mapx, mapy;
    cv::Matx33d intrinsics;
    cv::Vec4d distortion_coeff;

    static cv::Mat numpy_uint8_to_cv_mat(py::array_t<unsigned char> &src);

    static py::array_t<unsigned char> cv_mat_uint8_to_numpy(cv::Mat &src);
};


#endif //UNDISTORT_UNDISTORT_H
