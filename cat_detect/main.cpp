#include "mobilenetssd.h"
#include "opencv2/opencv.hpp"

int main(int argc, char* argv[]) {
	const char* img_path = "C:/Users/Administrator/Desktop/MNN_Cat_Detect-master/images/cat_dog.jpg";
	cv::Mat img_src = cv::imread(img_path);
	mirror::MobilenetSSD* mobilenetssd = new mirror::MobilenetSSD();

	const char* root_path = "C:/Users/Administrator/Desktop/MNN_Cat_Detect-master/models";
	mobilenetssd->Init(root_path);
	std::vector<mirror::ObjectInfo> objects;
	mobilenetssd->Detect(img_src, &objects);

	int num_objects = static_cast<int>(objects.size());
	for (int i = 0; i < num_objects; ++i) {
		std::cout << "location: " << objects[i].location_ << std::endl;
		cv::rectangle(img_src, objects[i].location_, cv::Scalar(255, 0, 255), 2);
		char text[256];
		sprintf_s(text, "%s %.1f%%", objects[i].name_.c_str(), objects[i].score_ * 100);
		int baseLine = 0;
		cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
		cv::putText(img_src, text, cv::Point(objects[i].location_.x,
			objects[i].location_.y + label_size.height),
			cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
	}
	cv::imwrite("C:/Users/Administrator/Desktop/MNN_Cat_Detect-master/images/cat_dog_detect.jpg", img_src);
	cv::imshow("result", img_src);
	cv::waitKey(0);

	delete mobilenetssd;

	system("pause");
	return 0;
}