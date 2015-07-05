#include "windowDo4.h"


WindowDo4::WindowDo4(QString windowTitle, WindowImage* harrisImage, WindowImage* fastImage, WindowImage* siftImage, WindowImage* surfImage)
		: mHarrisImage(harrisImage), mFastImage(fastImage), mSiftImage(siftImage), mSurfImage(surfImage), mTimer(new QTimer()) {
	setupUi(this);
	
	setWindowTitle(windowTitle + " - Do4!");
	setAttribute(Qt::WA_DeleteOnClose);
	
	uiHLayout1->insertWidget(1, mHarrisImage);
	uiHLayout1->insertWidget(3, mFastImage);
	uiHLayout2->insertWidget(1, mSiftImage);
	uiHLayout2->insertWidget(3, mSurfImage);
	
	connect(uiPushButtonZoomBestFit, &QPushButton::released, this, &WindowDo4::zoomBestFit);
	connect(mTimer, &QTimer::timeout, this, &WindowDo4::zoomBestFit);
	
	show();
	
	// This timer is to resize the images once the WindowStateChange event is fired because the window is actually resized
	// after the event is fired, i.e., when the window's size is not yet ready and images would get a not fit size.
	mTimer->setSingleShot(true);
	mTimer->setInterval(200);
	mTimer->start();
	
}




void WindowDo4::zoomBestFit() {
	mHarrisImage->zoomBestFit();
	mFastImage->zoomBestFit();
	mSiftImage->zoomBestFit();
	mSurfImage->zoomBestFit();
}




void WindowDo4::changeEvent(QEvent* event) {
	if (event->type() == QEvent::WindowStateChange) {
		QWindowStateChangeEvent* eventb = static_cast<QWindowStateChangeEvent*>(event);
		if (eventb->oldState() == Qt::WindowMaximized && this->windowState() == Qt::WindowNoState)
			mTimer->start();
		else if (eventb->oldState() == Qt::WindowNoState && this->windowState() == Qt::WindowMaximized)
			mTimer->start();
	}
}
