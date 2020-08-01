#include "colordetectcontroller.h"

ColorDetectController* ColorDetectController::singleton = 0;

ColorDetectController *ColorDetectController::getSingleton()
{
    return singleton;
}

void ColorDetectController::setSingleton(ColorDetectController *value)
{
    singleton = value;
}

ColorDetectController::ColorDetectController()
{
    cdetect = new ColorDetector();
}

ColorDetectController::~ColorDetectController()
{
    delete cdetect;
}

void ColorDetectController::setColorDistanceThreshold(int distance)
{
    cdetect->setColorDistanceThreshold(distance);
}

int ColorDetectController::getColorDistanceThreshold() const
{
    return cdetect->getColorDistanceThreshold();
}

void ColorDetectController::setTargetColor(unsigned char red, unsigned char green, unsigned char blue)
{
    cdetect->setTargetColor(red, green, blue);
}

void ColorDetectController::getTargetColor(unsigned char &red, unsigned char &green, unsigned char &blue)
{
    Vec3b color = cdetect->getTargetColor();
    red = color[2];
    green = color[1];
    blue = color[0];
}
bool ColorDetectController::setInputImage(std::string filename, int flags)
{
    image = imread(filename, flags);
    if(!image.data)
        return false;
    else
        return true;
}

const Mat ColorDetectController::getInputImage() const
{
    return image;
}

void ColorDetectController::process()
{
    result = cdetect->process(image);
}

const Mat ColorDetectController::getLastResult() const
{
    return result;
}

ColorDetectController *ColorDetectController::getInstance()
{
    if(singleton == 0)
        singleton = new ColorDetectController;
    return singleton;
}

void ColorDetectController::destroy()
{
    if(singleton != 0)
    {
        delete singleton;
        singleton = 0;
    }
}
