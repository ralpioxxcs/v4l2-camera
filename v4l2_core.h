/***************************************************************
 *        @name      : v4l2_core.h
 *        @author    : ralpioxxcs
 *        @brief     : define class of v4l2 core units
 ****************************************************************/

#ifndef V4L2_CORE_H
#define V4L2_CORE_H

#include "v4l2_device.h"

#include <fcntl.h>
#include <string>
#include <linux/videodev2.h>

class v4l2_core {
 public:
  v4l2_core(){};
  
  void mmap_device();

 private:
  struct buffer {
    void* start;
    size_t length;
  };

};

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
