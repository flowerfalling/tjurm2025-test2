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
            int x0 = static_cast<int>(i / scale);
            int y0 = static_cast<int>(j / scale);
            int x1 = std::min(x0 + 1, input.rows - 1);
            int y1 = std::min(y0 + 1, input.cols - 1);
            float x_diff = (i / scale) - x0;
            float y_diff = (j / scale) - y0;

            cv::Vec3b a = input.at<cv::Vec3b>(x0, y0);
            cv::Vec3b b = input.at<cv::Vec3b>(x0, y1);
            cv::Vec3b c = input.at<cv::Vec3b>(x1, y0);
            cv::Vec3b d = input.at<cv::Vec3b>(x1, y1);

            for (int k = 0; k < 3; ++k) {
                output.at<cv::Vec3b>(i, j)[k] = static_cast<uchar>(
                    a[k] * (1 - x_diff) * (1 - y_diff) +
                    b[k] * (1 - x_diff) * y_diff +
                    c[k] * x_diff * (1 - y_diff) +
                    d[k] * x_diff * y_diff
                    );
            }
            int src_y = static_cast<int>(j / scale);
            output.at<cv::Vec3b>(i, j) = input.at<cv::Vec3b>(src_x, src_y);
        }
    }
    return output;
}
