#include "opencvfunction.h"

namespace opencvfun
{
    void salt(Mat &image, int n)
    {
        for(int k=0; k < n; k++)
        {
            int i = rand() % image.cols;
            int j = rand() % image.rows;
            if(image.channels() == 1)
            {
                image.at<uchar>(j, i) = 255;
            }
            else if(image.channels() == 3)
            {
                image.at<cv::Vec3b>(j, i)[0] = 255;
                image.at<cv::Vec3b>(j, i)[1] = 255;
                image.at<cv::Vec3b>(j, i)[2] = 255;
            }
        }
    }

    void colorReduce(const Mat image, Mat& resultImage, int div)
    {
        resultImage.create(image.rows, image.cols, image.type());
        int nl = image.rows;
        int nc = image.cols * image.channels();
        if(image.isContinuous())
        {
            nc = nc * nl;
            nl = 1;
        }
        for(int j = 0; j < nl; j++)
        {
            const uchar* data_in = image.ptr<uchar>(j);
            uchar* data_out = resultImage.ptr<uchar>(j);
            for(int i = 0; i < nc; i++)
            {
                data_out[i] = data_in[i] / div * div / 2;
            }
        }
    }

    void getColorChannel(const Mat image, Mat &result, int channel)
    {
        result.create(image.rows, image.cols, image.type());
        return;
        if(image.channels() == 1)
        {
            result.create(image.rows, image.cols, image.type());
        }
        else if(image.channels() == 3)
        {
            //cv::Mat Iterator_<cv::Vec3b> it = image.begin<cv::Vec3b>();
            //cv::Mat_<cv::Vec3b> itend = image.end<cv::Vec3b>();
            result.create(image.rows, image.cols, CV_8UC1);
            //while(it != itend)
            {
                //*(result++) = (*it)[channel];
                //it++;
            }
        }
        else
        {
            result.create(image.rows, image.cols, image.type());
        }
    }

    void sharpen(const Mat &image, Mat &result)
    {
        result.create(image.size(), image.type());
        for(int j = 1; j < image.rows - 1; j++)
        {
            const uchar* previous = image.ptr<const uchar>(j - 1);
            const uchar* current = image.ptr<const uchar>(j);
            const uchar* next = image.ptr<const uchar>(j + 1);
            uchar* output = result.ptr<uchar>(j);
            int cols = image.channels() == 3 ? image.cols * 3 : image.cols;
            for(int i = 1; i < cols; i++)
            {
                *output++ = cv::saturate_cast<uchar>(
                            5*current[i] - current[i - 1]
                        - current[i+1] - previous[i] - next[i]);
            }
        }
        result.row(0).setTo(cv::Scalar(0));
        result.row(result.rows-1).setTo(cv::Scalar(0));
        result.col(0).setTo(cv::Scalar(0));
        result.col(result.cols-1).setTo(cv::Scalar(0));
    }

    void sharpen2D(const Mat &image, Mat &result)
    {
        Mat kernel(3, 3, CV_32F, Scalar(0));
        kernel.at<float>(1, 1) = 5.0;
        kernel.at<float>(0, 1) = -1.0;
        kernel.at<float>(2, 1) = -1.0;
        kernel.at<float>(1, 0) = -1.0;
        kernel.at<float>(1, 2) = -1.0;
        filter2D(image, result, image.depth(), kernel);
    }

    void imageChangeAdd(const Mat &image, Mat &result, int channel, int value)
    {
        if(image.channels() != 3 || channel < 0 || channel > 3)
        {
            result.create(image.size(), image.type());
            return;
        }
        std::vector<cv::Mat> planes;
        split(image, planes);
        planes[channel] += value;
        merge(planes, result);
    }

    void addLogo(const Mat &image, Mat &result, char *logo)
    {
        Mat logoImage = imread(logo);
        if(image.rows < logoImage.rows || image.cols < logoImage.cols)
        {
            result.create(image.size(), image.type());
            return;
        }
        result = image.clone();
        Mat imageROI = result(Rect(0, 0, logoImage.cols, logoImage.rows));
        cv::addWeighted(imageROI, 1.0, logoImage, 0.2, 0, imageROI);
    }

}
