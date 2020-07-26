/***************************************************************
 *        @name      : v4l2.h
 *        @author    : ralpioxx (ralpioxx@gmail.com)
 *        @brief     : camera v4l2 functions
 ****************************************************************/

#ifndef V4L2_H
#define V4L2_H

#define CLEAR(x) memset(&(x), 0, sizeof(x))

#include <asm/types.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <libv4l1.h>
#include <libv4l2.h>
#include <linux/videodev2.h>
#include <malloc.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "opencv2/opencv.hpp"

/* Defaults
 * If your board can do better, set it here.
 * Set for the most common type inputs. */
#define DEFAULT_V4L_WIDTH 640
#define DEFAULT_V4L_HEIGHT 480
#define CHANNEL_NUMBER 1
#define MAX_CAMERAS 1
#define MAX_V4L_BUFFERS 5
#define DEFAULT_V4L_BUFFERS 5
#define USE_TEMP_BUFFERS
#define MAX_DEVICE_DRIVER_NAME 256
#define IO_MMAP
#define VIDIOC_REQBUFS_COUNT 20
#define CAMERA_BUFFER_MAX 10
#define CAMERA_FPS 60






/* Device Capture Objects ( v4l2 structure ) */
struct buffer {
  void* start;
  size_t length;
};

typedef struct {
  __u32 ctrl_id;
  __s32 initial_value;
  __s32 current_value;
  __s32 minimum;
  __s32 maximum;
  __s32 default_value;
} v4l2_ctrl_range;

typedef enum {
  IO_METHOD_MMAP,
} io_method;

typedef struct {
  /* device info */
  char* deviceName;
  int deviceHandler;
  int FirstCapture;
  int is_v4l2_device;
  int width, height;
  int mode;
  int fps;

  /* camera buffer info */
  int bufferIndex;
  struct timeval timestamp;
  sImage* buffer;
  struct buffer* back_buffers;

  /* V4L2 variables */
  struct v4l2_capability cap;
  struct v4l2_input inp;
  struct v4l2_format form;
  struct v4l2_crop crop;
  struct v4l2_cropcap cropcap;
  struct v4l2_streamparm frameint;
  struct v4l2_requestbuffers req;
  struct v4l2_jpegcompression compr;
  struct v4l2_control control;
  enum v4l2_buf_type type;
  struct v4l2_queryctrl queryctrl;

  struct video_capability capability;
  struct video_window captureWindow;
  struct video_picture imageProperties;
  struct video_mbuf memoryBuffer;
  struct video_mmap* mmaps;
  char* memoryMap;

  /* V4L2 control variables */
  v4l2_ctrl_range** v4l2_ctrl_ranges;
  int v4l2_ctrl_count;
} GzCapture_UVC;

/************************
  [UVC camera functions ]
*************************/
static Capture_UVC* OpenCAM_UVC(int index);
static void CloseCAM_UVC(GzCapture_UVC* cap);
static int GrabCAM_UVC(GzCapture_UVC* cap);
static IplImage* RetreiveCAM_UVC(GzCapture_UVC* cap);
static double GetPropCAM_UVC(GzCapture_UVC* cap, int propertyId);
static bool SetPropCAM_UVC(GzCapture_UVC* cap, int propertyId, double value);

/************************
  [UVC camera Class ]
*************************/
class Camera_UVC : public sCapture {
 public:
  Camera_UVC() { cap = 0; }
  virtual ~Camera_UVC();
  virtual bool open(int device);
  virtual void close();
  virtual bool grabFrame();
  virtual IplImage* retrieveFrame(int);
  virtual sImage* getBufferPtr();
  virtual int getLastIndex();
  virtual bool setProperty(int propId, double value);
  virtual double getProperty(int propId) const;

 protected:
  GzCapture_UVC* cap;
};

#endif
