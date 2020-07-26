#include "v4l2_device.h"

V4l2Device::V4l2Device() {}

V4l2Device::V4l2Device(deviceParameter param) : m_params(param) {}

bool V4l2Device::initDevice() {
  m_params.deviceHandler =
      v4l2_open(m_params.deviceName, O_RDWR /* required */ | O_NONBLOCK, 0);

  // If open is failed
  if (m_params.deviceHandler == -1) {
    fprintf(stderr, "Cannot identify '%s': %d, %s\n", m_params.deviceName,
            errno, strerror(errno));
    closeDevice();
    return false;
  }

  if(configCapability() == false) {

    return false;
  }



  return true;
}

bool V4l2Device::configCapability() {
  


}
