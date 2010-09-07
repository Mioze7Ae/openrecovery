ifneq ($(TARGET_SIMULATOR),true)
ifeq ($(TARGET_ARCH),arm)

#open recovery unyaffs
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := unyaffs.c
LOCAL_CFLAGS := -Os 
LOCAL_MODULE := unyaffs-or
LOCAL_MODULE_TAGS := eng
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_STATIC_LIBRARIES := libc
include $(BUILD_EXECUTABLE)

#open recovery yaffs2image
include $(CLEAR_VARS)

LOCAL_SRC_FILES := mkyaffs2image.c
LOCAL_CFLAGS := -Os 
LOCAL_MODULE :=  mkyaffs2image-or
LOCAL_MODULE_TAGS := eng
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_STATIC_LIBRARIES := libc
include $(BUILD_EXECUTABLE)

endif	# TARGET_ARCH == arm
endif	# !TARGET_SIMULATOR
