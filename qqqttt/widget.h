#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include "ui_widget.h"

#include <QtWidgets/Qlabel>      

#include <opencv/cv.h>  
#include <opencv/highgui.h> 

#include <QtNetwork/QTcpSocket>
#include <QtCore\QString>
#include <QtCore\QMutex>
#include "cv.h"
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <qtgui\QImage>
#include "IplImageToQImage.h"
#include <QtCore\qtimer.h>

#define SRCVIDEOMODE	1
#define OBJECTVIDEOMODE  2
#define GRAYVIDEOMODE	3
#define FACEVIDEOMODE	4

#define MIN_AREA 1000//定义最小有效的矩形面积
namespace Ui {
	class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

	private slots:
	void on_connect_clicked();
	void on_stop_clicked();
	void on_record_clicked();
	void on_stoprecord_clicked();
	void sendrequest();
	void read();
	void socketerror();
	void doRun();
	void doBack();
	void doLeft();
	void doRight();
	void doStopCar();
	void doBuzzer();
	void doHelp();
	void doSpeed();
	void doSrcMode();
	void doGrayMode();
	void doFaceMode();
	void doObjectMode();
	void read_t();
	void readFrameRate();
	void loadFaceImg();
	int faceMatchProcess();
	QImage *iplImgToQImg(IplImage *cvimage);
private:
	Ui::Widget *ui;
	QTcpSocket *client;
	QTcpSocket *motor_client;
	QByteArray block1;
	QMutex mutex;
	QTimer * testTimer;
	QTimer * frameTimeCal;
	int graySetValue;
	int displayFlagMode;
	cv::Mat targetFaceImg;
	

};

#endif // WIDGET_H
