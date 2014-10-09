ifneq ($(USE_CAMERA_STUB),true)
ifeq ($(BOARD_USES_QCOM_HARDWARE),true)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# When zero we link against libmmcamera; when 1, we dlopen libmmcamera.
DLOPEN_LIBMMCAMERA := 1

# Uncomment below line to enable smooth zoom
#LOCAL_CFLAGS += -DCAMERA_SMOOTH_ZOOM

LOCAL_SRC_FILES := \
    QualcommCamera.cpp \
    QualcommCameraHardware.cpp

ifeq ($(TARGET_USES_ION),true)
    LOCAL_CFLAGS += -DUSE_ION
endif

# 4 buffers on 7x30
LOCAL_CFLAGS += -DNUM_PREVIEW_BUFFERS=4

LOCAL_C_INCLUDES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_ADDITIONAL_DEPENDENCIES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr
LOCAL_C_INCLUDES += \
    hardware/qcom/display-$(TARGET_QCOM_DISPLAY_VARIANT)/libgralloc \
    hardware/qcom/media-$(TARGET_QCOM_MEDIA_VARIANT)/libstagefrighthw

LOCAL_SHARED_LIBRARIES := \
    libcamera_client \
    libcutils \
    liblog \
    libutils

ifeq ($(DLOPEN_LIBMMCAMERA),1)
    LOCAL_SHARED_LIBRARIES += libdl
    LOCAL_CFLAGS += -DDLOPEN_LIBMMCAMERA
else
    LOCAL_SHARED_LIBRARIES += liboemcamera
endif

LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE := camera.$(TARGET_BOARD_PLATFORM)
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

endif # BOARD_USES_QCOM_HARDWARE
endif # USE_CAMERA_STUB
