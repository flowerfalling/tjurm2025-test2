#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     *
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat gray;
    cv::Mat binary;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 128, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    int maxContourIndex = -1;
    double maxContourArea = 0.0;
    for (size_t i = 1; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        if (area > maxContourArea) {
            maxContourArea = area;
            maxContourIndex = i;
        }
    }
    cv::Rect boundingRect = cv::boundingRect(contours[maxContourIndex]);
    cv::RotatedRect minAreaRect = cv::minAreaRect(contours[maxContourIndex]);
    std::pair<cv::Rect, cv::RotatedRect> res(boundingRect, minAreaRect);
    return res;
}
