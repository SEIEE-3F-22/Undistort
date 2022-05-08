#include "Undistort.h"

cv::Mat Undistort::numpy_uint8_to_cv_mat(py::array_t<unsigned char> &src) {
    if (src.ndim() != 3) {
        throw std::runtime_error("Input image must be 3 dimensional");
    }

    py::buffer_info buf = src.request();
    cv::Mat dst(buf.shape[0], buf.shape[1], CV_8UC3, (unsigned char *) buf.ptr);
    return dst;
}

py::array_t<unsigned char> Undistort::cv_mat_uint8_to_numpy(cv::Mat &src) {
    if (src.channels() != 3) {
        throw std::runtime_error("Input image must be 3 dimensional");
    }

    py::array_t<unsigned char> dst = py::array_t<unsigned char>({src.rows, src.cols, 3}, src.data);
    return dst;
}

Undistort::Undistort(const int width, const int height) {
    cv::Size correctedSize = cv::Size(width, height);

    ifstream intrinsicFile("intrinsics.txt");
    ifstream disFile("dis_coeff.txt");

    for(auto i = 0; i < 3; i++) {
        for (auto j = 0; j < 3; j++) {
            intrinsicFile >> intrinsics(i, j);
        }
    }

    for(auto i = 0; i < 4; i++){
        disFile >> distortion_coeff(i);
    }

    cv::fisheye::initUndistortRectifyMap(intrinsics, distortion_coeff, cv::Matx33d::eye(), intrinsics, correctedSize, CV_16SC2, mapx, mapy);
}

py::array_t<unsigned char> Undistort::remap(py::array_t<unsigned char> &src) {
    cv::Mat dst;
    cv::remap(numpy_uint8_to_cv_mat(src), dst, mapx, mapy, cv::INTER_LINEAR, cv::BORDER_TRANSPARENT);
    return cv_mat_uint8_to_numpy(dst);
}

PYBIND11_MODULE(Undistort, m){
    py::class_<Undistort>(m, "Undistort")
            .def(py::init<const int, const int>())
            .def("remap", &Undistort::remap);
}