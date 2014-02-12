/*!
 * \file
 * \brief 
 * \author Mikolaj Kojdecki
 */

#ifndef CAMERAPGR_HPP_
#define CAMERAPGR_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>

#include <boost/thread.hpp>
//FlyCapture2 imports
#include <FlyCapture2.h>
#include <GigECamera.h>
#include <BusManager.h>
#include <Image.h>

namespace Sources {
namespace CameraPGR {

/*!
 * \class CameraPGR
 * \brief CameraPGR processor class.
 *
 * CameraPGR processor.
 */
class CameraPGR_Source: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	CameraPGR_Source(const std::string & name = "CameraPGR");

	/*!
	 * Destructor
	 */
	virtual ~CameraPGR_Source();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to 
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();

	void captureAndSendImages();

	// Input data streams
	Base::DataStreamIn<float> shutterTimeChange;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;
	Base::DataStreamOut<string> out_info;

	// Handlers
	Base::EventHandler2 h_onShutterTimeChanged;
	// Properties
	Base::Property<int> width;
	Base::Property<int> height;
	Base::Property<float> fps;
	Base::Property<float> shutter;
	Base::Property<int> gain;
	Base::Property<string> camera_url;
	Base::Property<unsigned int> camera_serial;
	Base::Property<string> pixel_format;

	void sendCameraInfo();
	// Handlers
	void onShutterTimeChanged();

private:
	bool ok;
	FlyCapture2::GigECamera cam;
	FlyCapture2::CameraInfo camInfo;
	boost::thread image_thread;
};

} //: namespace CameraPGR
} //: namespace Sources

/*
 * Register processor component.
 */
REGISTER_COMPONENT("CameraPGR", Sources::CameraPGR::CameraPGR_Source)

#endif /* CAMERAPGR_HPP_ */