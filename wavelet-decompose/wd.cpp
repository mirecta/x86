
#include <opencv2/opencv.hpp>
#include <stdlib.h>

int main( int argc, char** argv )
{

    cv::Mat image;
    image = cv::imread( "orig.jpg", 1 );


    cv::Mat other(image.size(),image.type()) ;
    //image.copyTo(other);

    for(int y = 0; y < image.rows; ++y)
        for(int x = 0; x < image.cols; ++x){
             int index = (image.step[0]*y + image.step[1]*x);
             
             if(rand()%5 != 0 ){
                 continue;
             }
             
             other.data[index + 0] = image.data[index + 0];
             other.data[index + 1] = image.data[index + 1];
             other.data[index + 2] = image.data[index + 2];
             

        }














    cv::imwrite( "out.jpg", other );

    cv::namedWindow( "Original", CV_WINDOW_AUTOSIZE );
    cv::namedWindow( "Out", CV_WINDOW_AUTOSIZE );

    cv::imshow( "Original", image );
    cv::imshow( "Out", other );

    cv::waitKey(0);

    return 0;
}
