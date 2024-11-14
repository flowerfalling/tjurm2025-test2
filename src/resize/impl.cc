#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     *
     * 提示：
     * 无。
     *
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    cv::Mat output(new_rows, new_cols, input.type());

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            float src_x = i / scale;
            float src_y = j / scale;

            int x1 = static_cast<int>(src_x);
            int y1 = static_cast<int>(src_y);
            int x2 = std::min(x1 + 1, input.rows - 1);
            int y2 = std::min(y1 + 1, input.cols - 1);

            float x_weight = src_x - x1;
            float y_weight = src_y - y1;

            cv::Vec3b top_left = input.at<cv::Vec3b>(x1, y1);
            cv::Vec3b top_right = input.at<cv::Vec3b>(x1, y2);
            cv::Vec3b bottom_left = input.at<cv::Vec3b>(x2, y1);
            cv::Vec3b bottom_right = input.at<cv::Vec3b>(x2, y2);

            for (int c = 0; c < 3; ++c) {
                output.at<cv::Vec3b>(i, j)[c] = static_cast<uchar>(
                    top_left[c] * (1 - x_weight) * (1 - y_weight) +
                    top_right[c] * (1 - x_weight) * y_weight +
                    bottom_left[c] * x_weight * (1 - y_weight) +
                    bottom_right[c] * x_weight * y_weight
                );
            }
        }
    }

    return output;
}
