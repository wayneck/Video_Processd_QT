#include "widget.h"
//#include <stdio.h>

#include<Windows.h>
#include <QMainWindow>  
#include <QFileDialog> 
#include <QTextCodec> 
#include <QMessageBox> 

#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv\cv.hpp>
#include <opencv2\features2d\features2d.hpp>

#include "stdio.h"
#include "facedetect-dll.h"
//#include "qt_windows.h"
//test v8.0、

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib,"libfacedetect.lib")

using namespace std;
using namespace cv;

int frameCount;
CvVideoWriter* videowr;
bool record;
uchar* qImageBuffer;

Widget::Widget(QWidget *parent) :
QWidget(parent),
ui(new Ui::Widget)
{
	ui->setupUi(this);

	/* 设置调节速度的滚动条 */
	ui->speed->setRange(0, 255);
	ui->speed->setValue(125);

	/* 设置边框及其颜色 */
	ui->Image->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(0, 0, 110);");
	ui->statuslabel->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(0, 0, 110);");

	/* 用于视频传输 */
	client = new QTcpSocket;
	/* 用于空中小车的方向 */
	motor_client = new QTcpSocket;
	qImageBuffer = (uchar *)(malloc(640 * 360 * 4 * sizeof(uchar)));

	/* 设置QLCD相关参数 */
	ui->lcdNumber->setStyleSheet("background: rgb(255, 0, 0);border-color: rgb(0, 0, 110);");
	ui->lcdNumber->setDecMode();
	//ui->lcdNumber->setSmallDecimalPoint(TRUE);
	ui->lcdNumber->setSmallDecimalPoint(FALSE);
	//ui->lcdNumber->setNumDigits(4);
	ui->lcdNumber->setDigitCount(4);
	ui->lcdNumber->display(13.4);

	/* 给按键加图标 */
	ui->run->setIcon(QIcon("./icon/key.png"));
	ui->back->setIcon(QIcon("./icon/key.png"));
	ui->left->setIcon(QIcon("./icon/key.png"));
	ui->right->setIcon(QIcon("./icon/key.png"));
	ui->stop_car->setIcon(QIcon("./icon/key.png"));
	ui->connect->setIcon(QIcon("./icon/connect.png"));
	ui->stop->setIcon(QIcon("./icon/disconnect.png"));
	ui->buzzer->setIcon(QIcon("./icon/speaker_red.png"));
	ui->objectMode->setIcon(QIcon("./icon/refresh.png"));
	ui->srcMode->setIcon(QIcon("./icon/refresh.png"));
	ui->faceMode->setIcon(QIcon("./icon/refresh.png"));
	ui->grayMode->setIcon(QIcon("./icon/refresh.png"));
	ui->record->setIcon(QIcon("./icon/play.png"));
	ui->stoprecord->setIcon(QIcon("./icon/stop.png"));
	ui->pushButton->setIcon(QIcon("./icon/on-off.png"));
	ui->help->setIcon(QIcon("./icon/help.png"));

	/* 设置按键的颜色 */
	ui->run->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->back->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->left->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->right->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->stop_car->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->connect->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->stop->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->objectMode->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->srcMode->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->faceMode->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->grayMode->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->loadFaceImgBtn->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->record->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->stoprecord->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->pushButton->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->help->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(190,190,190)");
	ui->buzzer->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(0,190,0)");

    //do some iniall
	//ui->speed->setValue(49);
	graySetValue = 124;
	ui->speeLabel->setText(tr("124"));
	displayFlagMode = SRCVIDEOMODE;
	frameCount = 0;

	connect(client, SIGNAL(connected()), this, SLOT(sendrequest()));
	testTimer = new QTimer(this);
	frameTimeCal = new QTimer(this);
	//connect(client, SIGNAL(readyRead()), this, SLOT(read()));
	connect(testTimer, SIGNAL(timeout()), this, SLOT(read()));

	connect(frameTimeCal, SIGNAL(timeout()), this, SLOT(readFrameRate()));

	connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketerror()));

	connect(ui->run, SIGNAL(clicked()), this, SLOT(on_stoprecord_clicked()));
	//connect(ui->run, SIGNAL(clicked()), this, SLOT(on_stoprecord_clicked()));

	connect(ui->srcMode, SIGNAL(clicked()), this, SLOT(doSrcMode()));
	connect(ui->grayMode, SIGNAL(clicked()), this, SLOT(doGrayMode()));
	connect(ui->faceMode, SIGNAL(clicked()), this, SLOT(doFaceMode()));
	connect(ui->objectMode, SIGNAL(clicked()), this, SLOT(doObjectMode()));
	
	connect(ui->loadFaceImgBtn, SIGNAL(clicked()), this, SLOT(loadFaceImg()));
	connect(ui->back, SIGNAL(clicked()), this, SLOT(doBack()));
	connect(ui->left, SIGNAL(clicked()), this, SLOT(doLeft()));
	connect(ui->right, SIGNAL(clicked()), this, SLOT(doRight()));
	connect(ui->stop_car, SIGNAL(clicked()), this, SLOT(doStopCar()));
	connect(ui->buzzer, SIGNAL(clicked()), this, SLOT(doBuzzer()));
	connect(ui->help, SIGNAL(clicked()), this, SLOT(doHelp()));

	connect(ui->speed, SIGNAL(valueChanged(int)), this, SLOT(doSpeed()));
	connect(motor_client, SIGNAL(readyRead()), this, SLOT(read_t()));
}

Widget::~Widget()
{
	delete ui;
	delete client;
	free(qImageBuffer);
}

void Widget::doRun()
{
	qDebug("run...\n");

	QByteArray block("direction:run");
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);
	motor_client->write(block);
}

void Widget::doBack()
{
	qDebug("back...\n");

	QByteArray block("direction:back");
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);
	motor_client->write(block);
}

void Widget::doLeft()
{
	qDebug("left...\n");

	QByteArray block("DJ_Zuo");
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);
	motor_client->write(block);
}

void Widget::doRight()
{
	qDebug("right...\n");

	QByteArray block("direction:right");
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);
	motor_client->write(block);
}

void Widget::doStopCar()
{
	qDebug("stop...\n");

	QByteArray block("direction:stop");
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);
	motor_client->write(block);
}

void Widget::doBuzzer()
{
	QString QbuzzerText = ui->buzzer->text();
	char* buzzerText = (char*)QbuzzerText.toStdString().c_str();

	/* Buzzer\n(on) */
	if (NULL != strstr(buzzerText, "on"))
	{
		ui->buzzer->setText(tr("Buzzer\n(off)"));
		ui->buzzer->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(255,0,0)");

		QByteArray block("buzzer:on");
		QDataStream out(&block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_5_6);
		motor_client->write(block);
	}
	else if (NULL != strstr(buzzerText, "off"))
	{
		ui->buzzer->setText(tr("Buzzer\n(on)"));
		ui->buzzer->setStyleSheet("border:2px groove gray;border-radius:10px;background-color: rgb(0,190,0)");

		QByteArray block("buzzer:off");
		QDataStream out(&block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_5_6);
		motor_client->write(block);
	}
}

void Widget::doHelp()
{
	qDebug("help...\n");

	LPCSTR filePath = "WiFi_robot_usr_manual.pdf";

	ShellExecuteA(0, "open", "explorer.exe", filePath, NULL, true);
}

void Widget::doSpeed()
{
	graySetValue = ui->speed->value();
	//qDebug("speed:%d\n", pos);

	QString str;// = "speed:";
	str.append(qPrintable(tr("%1").arg(graySetValue)));
	ui->speeLabel->setText(str);
	//ui->statuslabel->setText(tr("socket error!"));
	qDebug("test:%s\n", qPrintable(str));
	//ui->speeLabel
	QByteArray block(qPrintable(str));
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);
	motor_client->write(block);
}

void Widget::loadFaceImg()
{
	QString filename = QFileDialog::getOpenFileName(this,
		tr("Open Image"), ".", tr("Image File (*.jpg *.png *.bmp)"));
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()  
	Mat opentmp = cv::imread(name);
	if (!opentmp.data)
	{
		QMessageBox msgBox;
		msgBox.setText(tr("Image Data Is Null"));
		msgBox.exec();
	}
	else {
		cv::resize(opentmp, targetFaceImg, Size(160, 180), 0, 0, CV_INTER_LINEAR);
		IplImage *	pInputFaceImg = &IplImage(targetFaceImg);
		QImage*	qImagetmp = iplImgToQImg(pInputFaceImg);// new QImage(qImageBuffer, g_pGrayImage->width, g_pGrayImage->height, QImage::Format_RGB32);
		QPixmap	lastpixtmp = QPixmap::fromImage(qImagetmp->scaled(160, 180));

		ui->detectFaceLabel->setPixmap(lastpixtmp);
		
	}
}

const float inlier_threshold = 2.5f; // Distance threshold to identify inliers
const float nn_match_ratio = 0.8f;   // Nearest neighbor matching ratio

int Widget:: faceMatchProcess(void)
{
	Mat img1 = imread("../data/graf1.png", IMREAD_GRAYSCALE);
	Mat img2 = imread("../data/graf3.png", IMREAD_GRAYSCALE);

	Mat homography;
	FileStorage fs("../data/H1to3p.xml", FileStorage::READ);
	fs.getFirstTopLevelNode() >> homography;

	vector<KeyPoint> kpts1, kpts2;
	Mat desc1, desc2;

	Ptr<AKAZE> akaze = AKAZE::create();
	akaze->detectAndCompute(img1, noArray(), kpts1, desc1);
	akaze->detectAndCompute(img2, noArray(), kpts2, desc2);

	BFMatcher matcher(NORM_HAMMING);
	vector< vector<DMatch> > nn_matches;
	matcher.knnMatch(desc1, desc2, nn_matches, 2);

	vector<KeyPoint> matched1, matched2, inliers1, inliers2;
	vector<DMatch> good_matches;
	for (size_t i = 0; i < nn_matches.size(); i++) {
		DMatch first = nn_matches[i][0];
		float dist1 = nn_matches[i][0].distance;
		float dist2 = nn_matches[i][1].distance;

		if (dist1 < nn_match_ratio * dist2) {
			matched1.push_back(kpts1[first.queryIdx]);
			matched2.push_back(kpts2[first.trainIdx]);
		}
	}

	for (unsigned i = 0; i < matched1.size(); i++) {
		Mat col = Mat::ones(3, 1, CV_64F);
		col.at<double>(0) = matched1[i].pt.x;
		col.at<double>(1) = matched1[i].pt.y;

		col = homography * col;
		col /= col.at<double>(2);
		double dist = sqrt(pow(col.at<double>(0) - matched2[i].pt.x, 2) +
			pow(col.at<double>(1) - matched2[i].pt.y, 2));

		if (dist < inlier_threshold) {
			int new_i = static_cast<int>(inliers1.size());
			inliers1.push_back(matched1[i]);
			inliers2.push_back(matched2[i]);
			good_matches.push_back(DMatch(new_i, new_i, 0));
		}
	}

	Mat res;
	drawMatches(img1, inliers1, img2, inliers2, good_matches, res);
	imwrite("res.png", res);

	double inlier_ratio = inliers1.size() * 1.0 / matched1.size();
	cout << "A-KAZE Matching Results" << endl;
	cout << "*******************************" << endl;
	cout << "# Keypoints 1:                        \t" << kpts1.size() << endl;
	cout << "# Keypoints 2:                        \t" << kpts2.size() << endl;
	cout << "# Matches:                            \t" << matched1.size() << endl;
	cout << "# Inliers:                            \t" << inliers1.size() << endl;
	cout << "# Inliers Ratio:                      \t" << inlier_ratio << endl;
	cout << endl;

	return 0;
}


void Widget::doObjectMode()
{
	displayFlagMode = OBJECTVIDEOMODE;
	ui->vedioText->setText(tr("object mode"));
}
void Widget::doSrcMode()
{
	displayFlagMode = SRCVIDEOMODE;
	ui->vedioText->setText(tr("src mode"));
}
void Widget::doFaceMode()
{
	displayFlagMode = FACEVIDEOMODE;
	ui->vedioText->setText(tr("face mode"));
}
void Widget::doGrayMode()
{
	displayFlagMode = GRAYVIDEOMODE;
	ui->vedioText->setText(tr("gray mode"));
}

void Widget::read_t()
{
	float t;

	QByteArray tep = motor_client->readAll();
	QString tep_string = QVariant(tep).toString();

	//qDebug("%s", qPrintable(tep_string));
	ui->statuslabel->setText(tep_string);
	t = tep_string.toFloat();

	ui->lcdNumber->display(t);
}

void Widget::on_connect_clicked()
{
	//ui->statuslabel->setText(tr("connecting..."));
	ui->statuslabel->setText(ui->lineEdit->text());
	/* 用于视频传输 */
	//sendrequest(); 
	client->connectToHost(ui->lineEdit->text(), ui->port->text().toInt());
	/* 用于空中小车的方向 */
	motor_client->connectToHost(ui->lineEdit->text(), 2001);
	testTimer->start(20);
	frameTimeCal->start(1000);

}

void Widget::on_stop_clicked()
{
	/* 用于视频传输 */
	client->abort();
	/* 用于空中小车的方向 */
	motor_client->abort();
	block1.clear();
	ui->statuslabel->setText(tr("stoped"));
	if (testTimer->isActive())
		testTimer->stop();

	if (frameTimeCal->isActive())
		frameTimeCal->stop();
}
#include <qdatetime.h>
void Widget::on_record_clicked()
{
	CvSize size;
	size.width = 640;
	size.height = 360;

	QTime time;
	time = time.currentTime();//获得当前时间，如:08:37:34
	QString Tstr = time.toString() + ".avi";//转换成QString类型，如08:37:34.avi
	Tstr = Tstr.replace(QChar(':'), QLatin1String("-"));//将:换成-，因为windows下文件名不能含:
	//char *filen = Tstr.toStdString().data();//转换成const char*型的文件名
	QByteArray ba = Tstr.toLatin1();
	char *filen = ba.data();

	//cvCreateVideoWriter last paratm 0=gray 1=color
	videowr = cvCreateVideoWriter(filen, CV_FOURCC('M', 'J', 'P', 'G'), 15, size, 1);//1=color

	record = true;
}

void Widget::on_stoprecord_clicked()
{
	record = false;
	cvReleaseVideoWriter(&videowr);
}

void Widget::sendrequest()
{
	QByteArray block("GET /?action=stream\r\n\r\n");
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);
	client->write(block);
}

void Widget::socketerror()
{
	ui->statuslabel->setText(tr("socket error!"));
}
void Widget::readFrameRate()
{
	if (frameCount > 1000)
		frameCount = 1;
	QString str;
	str.append(qPrintable(tr("%1").arg(frameCount)));
	ui->frameRate->setText(str);
	//frameCount = 0;
	//ui->speeLabel->setText(str);
}
IplImage* pFrImg = NULL;
IplImage* pBkImg = NULL;
IplImage* pSrcBkImg = NULL;

CvMat* pFrameMat = NULL;
CvMat* pFrMat = NULL;
CvMat* pBkMat = NULL;

IplImage * mubiaoshibie(IplImage *inputIpImage)
{
	if (!inputIpImage)
		return 0;

	
	if ((frameCount%200) ==1 )
	{
		//g_pGrayImage = cvCreateImage(cvGetSize(iplimg), IPL_DEPTH_8U, 1);
		//cvCvtColor(iplimg, g_pGrayImage, CV_BGR2GRAY);
		//g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);
		pSrcBkImg = inputIpImage;
		pBkImg = cvCreateImage(cvGetSize(inputIpImage), IPL_DEPTH_8U, 1); // 存放背景图像(灰度)
		pFrImg = cvCreateImage(cvGetSize(inputIpImage), IPL_DEPTH_8U, 1); // 存放中间图像(灰度)

		pBkMat = cvCreateMat(360, 640, CV_32FC1);
		pFrMat = cvCreateMat(360, 640, CV_32FC1);
		pFrameMat = cvCreateMat(360, 640, CV_32FC1);

		
		//转化成单通道图像再处理(灰度)
		cvCvtColor(inputIpImage, pBkImg, CV_BGR2GRAY);
		cvCvtColor(inputIpImage, pFrImg, CV_BGR2GRAY);
		cvConvert(pFrImg, pFrameMat);
		cvConvert(pFrImg, pFrMat);
		cvConvert(pFrImg, pBkMat);
		return pFrImg;
	}
	else
	{
		cvCvtColor(inputIpImage, pFrImg, CV_BGR2GRAY); //转化成单通道图像再处理(灰度)
		cvConvert(pFrImg, pFrameMat);
		//高斯滤波先，以平滑图像
		//cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);

		//当前帧跟背景图相减(求背景差并取绝对值)
		cvAbsDiff(pFrameMat, pBkMat, pFrMat);

		//二值化前景图(这里采用特定阈值进行二值化)
		cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);

		//进行形态学滤波，去掉噪音
		cvErode(pFrImg, pFrImg, 0, 1);
		cvDilate(pFrImg, pFrImg, 0, 1);

		//滑动平均更新背景(求平均)
		cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);
		//将背景转化为图像格式，用以显示
		cvConvert(pBkMat, pBkImg);

		// 保持原图像的旋转方向
		pBkImg->origin = pFrImg->origin = inputIpImage->origin;

		CvMemStorage * storage = cvCreateMemStorage(0);
		CvSeq * contour = 0;
		int num = cvFindContours(pFrImg, storage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		for (; contour != 0; contour = contour->h_next)
		{
			CvRect rect = ((CvContour *)contour)->rect;
			if (rect.width*rect.height>MIN_AREA)
			{
				cvRectangle(inputIpImage, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(255, 0, 0), 1, CV_AA, 0);
			}
		}
		//如果有按键事件，则跳出循环
		//此等待也为cvShowImage函数提供时间完成显示
		//等待时间可以根据CPU速度调整
		//cvReleaseImage(&pFrImg);
		//cvReleaseImage(&pBkImg);

		//cvReleaseMat(&pFrameMat);
		//cvReleaseMat(&pFrMat);
		//cvReleaseMat(&pBkMat);
		return inputIpImage;
	}

	return inputIpImage;

}

#define DETECT_BUFFER_SIZE 0x20000

IplImage * faceDetectedCheck(IplImage * inputIpImage)
{
	if (!inputIpImage)
		return inputIpImage;
	IplImage* pInputFaceImg = NULL;
	IplImage* pOutputFaceImg = NULL;
	pInputFaceImg = cvCreateImage(cvGetSize(inputIpImage), IPL_DEPTH_8U, 1); // 存放中间图像(灰度)
	cvCvtColor(inputIpImage, pInputFaceImg, CV_BGR2GRAY);
	//return inputIpImage;
	//pInputFaceMat = cvCreateMat(360, 640, CV_32FC1);
		//转化成单通道图像再处理(灰度)
		//cvCvtColor(inputIpImage, pInputFaceImg, CV_BGR2GRAY);
	Mat gray;
	Mat img;
	Mat processedTmp;
	img = processedTmp = cvarrToMat(inputIpImage, false);
	gray = cvarrToMat(pInputFaceImg, false);
	
	//cvtColor(img, gray, CV_BGR2GRAY);
	//pOutputFaceImg = &IplImage(img);// (result_frontal);
	//return (pOutputFaceImg);

	int * pResults = NULL;
	//pBuffer is used in the detection functions.
	//If you call functions in multiple threads, please create one buffer for each thread!
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	if (!pBuffer)
	{
		fprintf(stderr, "Can not alloc buffer.\n");
		return inputIpImage;
	}

	int doLandmark = 1;
	//pInputFaceImg->widthStep;
	///////////////////////////////////////////
	// frontal face detection / 68 landmark detection
	// it's fast, but cannot detect side view faces
	//////////////////////////////////////////
	//!!! The input image must be a gray one (single-channel)
	//!!! DO NOT RELEASE pResults !!! (gray.ptr(0)) gray.step
	//gray.ptr(0);
	pResults = facedetect_frontal(pBuffer, (unsigned char*)(pInputFaceImg->imageData), gray.cols, gray.rows, (int)pInputFaceImg->widthStep,
		1.2f, 2, 48, 0, doLandmark);

	printf("%d faces detected.\n", (pResults ? *pResults : 0));
	Mat result_frontal = cvarrToMat(inputIpImage, false); //processedTmp.clone();
	//print the detection results
	for (int i = 0; i < (pResults ? *pResults : 0); i++)
	{
		short * p = ((short*)(pResults + 1)) + 142 * i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];
		int angle = p[5];

		//printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
		rectangle(result_frontal, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
		//cvRectangle(inputIpImage, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
		if (doLandmark)
		{  //
			for (int j = 0; j < 68; j++){
				//circle(result_frontal, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, Scalar(0, 255, 0));
				cvDrawCircle(inputIpImage, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, Scalar(0, 255, 0));
			}
			
		}
	}
	//imshow("Results_frontal", result_frontal);	
	free(pBuffer);
	pInputFaceImg = &IplImage(processedTmp);
	return (inputIpImage);

}


QImage * Widget::iplImgToQImg(IplImage *cvimage)
{
	if (!cvimage)
		return 0;
	QImage* desImage = new QImage(cvimage->width, cvimage->height, QImage::Format_RGB32);
	/*对图像的像素操作*/
	for (int i = 0; i < cvimage->height; i++)  //行数循环
	{
		for (int j = 0; j < cvimage->width; j++)   //列数循环
		{
			int r, g, b;

			if (3 == cvimage->nChannels)
			{
				b = (int)CV_IMAGE_ELEM(cvimage, uchar, i, j * 3 + 0);
				g = (int)CV_IMAGE_ELEM(cvimage, uchar, i, j * 3 + 1);
				r = (int)CV_IMAGE_ELEM(cvimage, uchar, i, j * 3 + 2);

			}
			else if (1 == cvimage->nChannels)
			{
				b = (int)CV_IMAGE_ELEM(cvimage, uchar, i, j);
				g = b;
				r = b;
			}

			desImage->setPixel(j, i, qRgb(r, g, b));
		}
	}
	return desImage;
}

#include <fstream>
int vjpgtime;
int anypacklen;
IplImage *g_pGrayImage = NULL;
IplImage *g_pBinaryImage = NULL;
void Widget::read()
{
	if ((anypacklen = client->bytesAvailable())<3000)
		return;

	QByteArray tmpBlock;
	static const char SOIData[] = { 0xFF, 0xD8 };
	static const char EOIData[] = { 0xFF, 0xD9 };

	QByteArray SOIstr = QByteArray::fromRawData(SOIData, sizeof(SOIData));
	QByteArray EOIstr = QByteArray::fromRawData(EOIData, sizeof(EOIData));

	int SOIPos = 0;
	int EOIPos = 0;

	mutex.lock();
	//tmpBlock = client->readAll();
	tmpBlock = client->read(anypacklen);

	block1.append(tmpBlock);//保存实际读到的数据

	if ((SOIPos = block1.indexOf(SOIstr)) != -1)
	//if ((SOIPos = block1.lastIndexOf(SOIstr)) != -1)
	{

		if ((EOIPos = block1.lastIndexOf(EOIstr)) != -1)
		{

			if (EOIPos>SOIPos)
			{
				while ((SOIPos > -1) && EOIPos > SOIPos){
					//bool ok;
					
					QByteArray packlen = block1.mid(SOIPos - 0x24, 5);
					//int perpacklen = packlen.toInt(&ok,10);
					int perpacklen = (packlen[0] - 0x30) * 10000 + (packlen[1] - 0x30) * 1000 + (packlen[2] - 0x30) * 100 +
						(packlen[3] - 0x30) * 10 + (packlen[3] - 0x30);
					QByteArray perpackdata;
					perpackdata = block1.mid(SOIPos, perpacklen);
					perpackdata.append(EOIstr);
					
					QPixmap pix;
					pix.loadFromData(perpackdata, "JPG");
					//pix = pix.fromImage(image);
					//IplImage * iplimg;
					//if ((record == true)){
					
					QImage  picQPixmap = pix.toImage();
					//ui->Image->setPixmap(pix);

					CvSize size;
					size.width = picQPixmap.width();
					size.height = picQPixmap.height();
					IplImage *  iplimg = cvCreateImage(size, IPL_DEPTH_8U, 3);//与cvReleaseImage配对使用
					QImageToIplImage(&picQPixmap, iplimg);
					
					if ((iplimg->height == 0) || (iplimg->width == 0)){
						perpackdata.clear();				
						SOIPos = block1.indexOf(SOIstr, SOIPos + 1);
						cvReleaseImage(&iplimg);
						continue;
					}
					//char savpic[] = "tmmpp.jpg";
					//pix.save(savpic, "JPG");
					QPixmap lastpix;
					IplImage * outProcessd;
					QImage* qImage;
					//}

					if (displayFlagMode == SRCVIDEOMODE){

						
						outProcessd = cvCreateImage(cvGetSize(iplimg), IPL_DEPTH_8U, 3);
						cvCvtColor(iplimg, outProcessd, CV_RGBA2BGR);
						//outProcessd = iplimg;
						//qImage = iplImgToQImg(iplimg);
						//lastpix = QPixmap::fromImage(qImage->scaled(640, 360));
						ui->Image->setPixmap(pix);
						
						//delete qImage;
					}
					else if (displayFlagMode == GRAYVIDEOMODE){
						g_pGrayImage = cvCreateImage(cvGetSize(iplimg), IPL_DEPTH_8U, 1);
						cvCvtColor(iplimg, g_pGrayImage, CV_BGR2GRAY);
						g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);
						cvThreshold(g_pGrayImage, g_pBinaryImage, 0, graySetValue, CV_THRESH_OTSU);
						outProcessd = g_pGrayImage;
						qImage = iplImgToQImg(g_pBinaryImage);
						lastpix = QPixmap::fromImage(qImage->scaled(640, 360));
						ui->Image->setPixmap(lastpix);
						delete qImage;
					}
					else if (displayFlagMode == OBJECTVIDEOMODE){
						if ((iplimg->height == 0) || (iplimg->width == 0)){
							 outProcessd = iplimg;
						}
						else{
							frameCount++;
							outProcessd = mubiaoshibie(iplimg);						
					   }
						qImage = iplImgToQImg(outProcessd);// new QImage(qImageBuffer, g_pGrayImage->width, g_pGrayImage->height, QImage::Format_RGB32);
						lastpix = QPixmap::fromImage(qImage->scaled(640, 360));
						ui->Image->setPixmap(lastpix);
						delete qImage;
					}
					else if (displayFlagMode == FACEVIDEOMODE){
						if ((iplimg->height == 0) || (iplimg->width == 0)){
							 outProcessd = iplimg;
						}
						else{
							outProcessd = faceDetectedCheck(iplimg);
					    }
						qImage = iplImgToQImg(outProcessd);// new QImage(qImageBuffer, g_pGrayImage->width, g_pGrayImage->height, QImage::Format_RGB32);
						lastpix = QPixmap::fromImage(qImage->scaled(640, 360));
						
						ui->Image->setPixmap(lastpix);
						delete qImage;

					}
					///////////////////////////////////////////////////////////////
					if ((record == true)){
						cvWriteFrame(videowr, outProcessd);//录制视频
					}
					//ui->Image->setPixmap(pix);
					//////////////////////////////////////////////////////////////////
					//caculate frame per second
					perpackdata.clear();
					//packlen.clear();					
					SOIPos = block1.indexOf(SOIstr, SOIPos + 1);
					//delete qImage;
					//delete desImage;
					cvReleaseImage(&iplimg);
				}

			}
			block1.remove(0, EOIPos + 1);
		}
	}
	mutex.unlock();

}
