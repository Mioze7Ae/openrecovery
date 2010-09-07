ifneq ($(TARGET_SIMULATOR),true)
ifeq ($(TARGET_ARCH),arm)

#open recovery imenu
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := imenu.c
LOCAL_CFLAGS := -Os 
LOCAL_MODULE := imenu
LOCAL_MODULE_TAGS := eng
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_STATIC_LIBRARIES := libc
include $(BUILD_EXECUTABLE)


endif	# TARGET_ARCH == arm
endif	# !TARGET_SIMULATOR
