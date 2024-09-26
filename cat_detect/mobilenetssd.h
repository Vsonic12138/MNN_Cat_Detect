#ifndef _MOBILENET_SSD_H_
#define _MOBILENET_SSD_H_

#include <vector>

#include "MNN/Interpreter.hpp"
#include "MNN/MNNDefine.h"
#include "MNN/Tensor.hpp"
#include "MNN/ImageProcess.hpp"

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"

namespace mirror {
	struct ObjectInfo {
		std::string name_;
		cv::Rect location_;
		float score_;
	};

	class MobilenetSSD {
	public:
		MobilenetSSD();
		~MobilenetSSD();
		int Init(const char* root_path);
		int Detect(const cv::Mat& img_src, std::vector<ObjectInfo>* objects);
	private:
		uint8_t* GetImage(const cv::Mat& img_src) {
			uchar* data_ptr = new uchar[img_src.total() * 4];
			cv::Mat img_tmp(img_src.size(), CV_8UC4, data_ptr);
			cv::cvtColor(img_src, img_tmp, CV_BGR2RGBA, 4);
			return (uint8_t*)img_tmp.data;
		}

	private:
		bool initialized_;
		const cv::Size inputSize_ = { 300, 300 };
		std::vector<int> dims_ = { 1, 3, 300, 300 };
		const float meanVals_[3] = { 0.5f, 0.5f, 0.5f };
		const float normVals_[3] = { 0.007843f, 0.007843f, 0.007843f };
		std::vector<std::string> class_names = {
			"background", "aeroplane", "bicycle", "bird", "boat",
			"bottle", "bus", "car", "cat", "chair",
			"cow", "diningtable", "dog", "horse",
			"motorbike", "person", "pottedplant",
			"sheep", "sofa", "train", "tvmonitor"
		};

		std::shared_ptr<MNN::Interpreter> mobilenetssd_interpreter_;
		MNN::Session* mobilenetssd_sess_ = nullptr;
		MNN::Tensor* input_tensor_ = nullptr;
		std::shared_ptr<MNN::CV::ImageProcess> pretreat_data_ = nullptr;

	};

}


#endif // !_MOBILENET_SSD_H_