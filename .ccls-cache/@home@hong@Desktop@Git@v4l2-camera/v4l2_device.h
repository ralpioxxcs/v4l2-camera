#ifndef V4L2_DEVICE_H
#define V4L2_DEVICE_H

#include <errno.h>
#include <fcntl.h>
#include <libv4l2.h>
#include <linux/videodev2.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include "v4l2_props.h"

struct deviceParameter {
  char* deviceName;
  int deviceHandler;
  int width;
  int height;
  int format;
};

class V4l2Device {
 public:
  V4l2Device();
  V4l2Device(deviceParameter param);
  virtual ~V4l2Device();

  bool initDevice();
  void closeDevice();

 protected:
  bool configCapability();
  bool configCrop();
  bool configImageFormat();

 private:
  struct deviceParameter m_params;
};

#endif /* V4L2_DEVICE_H */
