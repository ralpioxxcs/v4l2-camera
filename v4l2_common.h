#ifndef V4L2_COMMON_H
#define V4L2_COMMON_H

#include <libv4l2.h>

class V4l2Common {
 private:
 public:
  V4l2Common();
  virtual ~V4l2Common();
  static int xioctl(int fd, int request, void* argp) {
    int r;
    do
      r = v4l2_ioctl(fd, request, argp);
    while (-1 == r && EINTR == errno);
    return r;
  }
};

#endif /* V4L2_COMMON_H */
