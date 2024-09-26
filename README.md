# 一、工程复现步骤：
## 1、下载对应文件
lib文件夹当中缺少MNN.lib，见百度网盘链接：[MNN.lib](https://pan.baidu.com/s/13LmBXWdeHSZopXx6CFzbdA?pwd=lll5 )
下载之后将该lib文件放入 lib -> release_MD 中。

## 2、修改工程的 “包含目录” 和 “库目录”
使用Visual Studio 2022打开工程，右击项目，在 配置属性 -> VC++目录 当中修改 “包含目录” 和 “库目录” 为项目在你电脑上的本工程的include和lib文件夹

## 3、修改代码的绝对路径
工程中有些代码的路径是相对路径，需要修改为绝对路径。
分别是：
(检测图片路径)： const char* img_path = "C:/Users/Administrator/Desktop/MNN_Cat_Detect-master/images/cat_dog.jpg";
(检测模型路径)： const char* root_path = "C:/Users/Administrator/Desktop/MNN_Cat_Detect-master/models";
(输出图片路径)： cv::imwrite("C:/Users/Administrator/Desktop/MNN_Cat_Detect-master/images/cat_dog_detect.jpg", img_src);

## 4、修改工程编译版本
需要将Visual Studio的编译版本设置为“release”模式，否则会出现链接错误。

## 5、编译运行
编译运行，即可看到检测结果。