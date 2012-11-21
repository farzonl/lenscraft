#pragma once

#include "Effects.hpp"
//#include "opencv2\gpu\gpu.hpp"
#include <omp.h>

class Drawing : public Effects
{
	double sp,sr;
	public:
		Drawing(void): Effects(),sp(10.0),sr(35.0){}
		void performEffect(cv::Mat &input);
		/*void performEffect(cv::Mat &input)
		{
			cv::gpu::GpuMat dst, src,gray,bgr,edges,edgesBgr;
			src.upload(input);
			//src.copyTo(bgr);

			//std::cout <<"channels: " << input.channels() <<std::endl;
			if(input.channels() == 4)
				cv::gpu::cvtColor(src,bgr,CV_BGRA2BGR);
			else 
				bgr = src;

			#pragma omp parallel sections
			{
				#pragma omp section
				{
					cv::Mat bgr_cpu(input.rows,input.cols,CV_8UC3);
					bgr.download(bgr_cpu);
					cv::pyrMeanShiftFiltering(bgr_cpu.clone(),bgr_cpu, sp, sr);
					//cv::gpu::meanShiftSegmentation(bgr,bgr_cpu,sp,sr,0);
					bgr.upload(bgr_cpu);
					
				}
				#pragma omp section
				{
					cv::gpu::cvtColor(src,gray,CV_BGR2GRAY);
					cv::gpu::Canny(gray,edges,150,150);
					cv::gpu::cvtColor(edges,edgesBgr,CV_GRAY2BGR);
				}
			}
			
			//bgr = bgr - edgesBgr;
			cv::gpu::subtract(bgr,edgesBgr,bgr);

			cv::gpu::cvtColor(bgr,dst,CV_BGR2BGRA);
			dst.download(this->effect);
			//cv::imshow("draw", effect);
			//cv::waitKey(0);
		}*/
};