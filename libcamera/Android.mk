
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS := -DDLOPEN_LIBMMCAMERA
LOCAL_CFLAGS += -DHW_ENCODE
LOCAL_CFLAGS += -DNUM_PREVIEW_BUFFERS=4 -D_ANDROID_

# To Choose neon/C routines for YV12 conversion
LOCAL_CFLAGS += -DUSE_NEON_CONVERSION
# Uncomment below line to enable smooth zoom
#LOCAL_CFLAGS+= -DCAMERA_SMOOTH_ZOOM

ifeq ($(strip $(TARGET_USES_ION)),true)
	LOCAL_CFLAGS += -DUSE_ION
endif

LOCAL_C_INCLUDES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_ADDITIONAL_DEPENDENCIES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_C_INCLUDES += \
	$(call project-path-for,qcom-display)/libgralloc \
	$(call project-path-for,qcom-display)/libgenlock \
	$(call project-path-for,qcom-media)/libstagefrighthw

LOCAL_SHARED_LIBRARIES := \
	libcamera_client \
	libcutils \
	libdl \
	libgenlock \
	libutils

LOCAL_SRC_FILES := \
	QCameraParameters.cpp \
	QualcommCamera.cpp \
	QualcommCameraHardware.cpp

LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE:= camera.$(TARGET_BOARD_PLATFORM)
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
