#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

/**
 * @brief img_to_row - transform a source image to row representation
 * @param src_img
 * @return
 */
std::vector<cv::Vec3b> mat2row(const cv::Mat &src_img)
{
    std::vector<cv::Vec3b> row_repr; //row representation of source image
    for (int i = 0; i < src_img.rows; i++)
        for (int j = 0; j < src_img.cols; j++)
            row_repr.push_back(src_img.at<cv::Vec3b>(i,j));
    return row_repr;
}

/**
 * @brief row2mat - transform a row represenation of image to cv::Mat
 * @param row_repr
 * @param n
 * @return
 */
cv::Mat row2mat(const std::vector<cv::Vec3b> &row_repr, int n)
{
    assert(row_repr.size() % n == 0);
    cv::Mat mat_repr(n, n, CV_8UC3);

    int i = 0;
    for (int j = 0; j < row_repr.size(); j++)
    {
        if (j % n == 0 && j != 0) i++;
        mat_repr.at<cv::Vec3b>(i, j%n) = row_repr[j];
    }
    return mat_repr;
}

/**
 * @brief rotate90 - perform rotation of a flatten array(inplace rotation without allocation extra space)
 * @param raw_repr
 * @param n
 */
void rotate90(std::vector<cv::Vec3b> &row_repr, int n)
{
    assert(row_repr.size() > 0);

    for (int i = 0; i < n / 2; i++)
    {
        for (int j = i; j < n-i-1; j++)
        {
            cv::Vec3b temp = row_repr[n*i+j];
            row_repr[n*i+j] = row_repr[n*j + (n-1-i)];
            row_repr[n*j + (n-1-i)] = row_repr[n*(n-1-i)+(n-1-j)];
            row_repr[n*(n-1-i)+(n-1-j)] = row_repr[n*(n-1-j)+i];
            row_repr[n*(n-1-j)+i] = temp;
        }
    }
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Program requeres two params: path to image and path to saving image after rotate!\n";
        return 0;
    }

    std::string src_img_path = argv[1], rot_img_path = argv[2];
    cv::Mat src_img = cv::imread(src_img_path), rotated_src;

    std::vector<cv::Vec3b> row_repr = mat2row(src_img);
    rotate90(row_repr, src_img.rows);
    rotated_src = row2mat(row_repr, src_img.rows);

    //saving
    std::vector<int> compression_params = {CV_IMWRITE_JPEG_QUALITY, 100};
    cv::imwrite(rot_img_path, rotated_src, compression_params);

    return 0;
}
