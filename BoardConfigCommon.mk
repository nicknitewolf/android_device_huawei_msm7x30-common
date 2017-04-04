#
# Copyright (C) 2014  Rudolf Tammekivi <rtammekivi@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

TARGET_SPECIFIC_HEADER_PATH := device/huawei/msm7x30-common/include

TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv7-a-neon
TARGET_CPU_VARIANT := scorpion
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_CPU_SMP := false

TARGET_ARCH_LOWMEM := true
TARGET_BOARD_PLATFORM := msm7x30
USE_CLANG_PLATFORM_BUILD := true

# Qualcomm hardware
BOARD_USES_QCOM_HARDWARE := true
TARGET_USE_QCOM_BIONIC_OPTIMIZATION := true

# Graphics
USE_OPENGL_RENDERER := true
TARGET_USES_C2D_COMPOSITION := true
TARGET_DISPLAY_INSECURE_MM_HEAP := true
TARGET_NO_ADAPTIVE_PLAYBACK := true

# Audio
BOARD_USES_LEGACY_ALSA_AUDIO := true
AUDIO_FEATURE_ENABLED_INCALL_MUSIC := false
AUDIO_FEATURE_ENABLED_COMPRESS_VOIP := false
AUDIO_FEATURE_ENABLED_PROXY_DEVICE := false
BOARD_USES_QCOM_AUDIO_CALIBRATION := true

# RIL
BOARD_PROVIDES_LIBRIL := true

# Bluetooth
BOARD_HAVE_BLUETOOTH := true

# GPS
BOARD_VENDOR_QCOM_GPS_LOC_API_AMSS_VERSION := 50000
USE_DEVICE_SPECIFIC_GPS := true

# Kernel
TARGET_NO_KERNEL := false
TARGET_KERNEL_SOURCE := kernel/huawei/msm7x30
BOARD_KERNEL_CMDLINE := androidboot.hardware=qcom androidboot.selinux=permissive
BOARD_KERNEL_BASE := 0x00200000
BOARD_KERNEL_PAGESIZE := 4096

# Charger
BOARD_CHARGER_DISABLE_INIT_BLANK := true
BOARD_CHARGER_ENABLE_SUSPEND := true

# Recovery
TARGET_RECOVERY_FSTAB := device/huawei/msm7x30-common/rootdir/fstab.qcom
TARGET_RECOVERY_PIXEL_FORMAT := RGBX_8888
TARGET_RECOVERY_DEVICE_DIRS := device/huawei/msm7x30-common
TW_HAS_NO_BOOT_PARTITION := true
TW_HAS_NO_RECOVERY_PARTITION := true
TW_CUSTOM_BATTERY_PATH := "/sys/class/power_supply/huawei-battery"
TW_USE_TOOLBOX := true

# Filesystem
# 12MiB
BOARD_CACHEIMAGE_PARTITION_SIZE := 12582912
# 1GiB
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1073741824
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_SYSTEMIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_USERDATAIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_FLASH_BLOCK_SIZE := 512
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_USERIMAGES_USE_F2FS := true

# Generic flags
BOARD_HARDWARE_CLASS := device/huawei/msm7x30-common/cmhw/
TARGET_PROVIDES_LIBLIGHT := true
TARGET_USES_ION := true
TARGET_USE_CUSTOM_LUN_FILE_PATH := /sys/devices/platform/msm_hsusb/gadget/lun%d/file
LINKER_NON_PIE_EXECUTABLES_HEADER_DIR := $(TARGET_SPECIFIC_HEADER_PATH)
TARGET_NEEDS_NONPIE_CAMERASERVER := true
TARGET_NEEDS_PLATFORM_TEXT_RELOCATIONS := true
MALLOC_SVELTE := true
TARGET_CONTINUOUS_SPLASH_ENABLED := true

# Enable dex pre-optimization
ifeq ($(HOST_OS),linux)
    ifeq ($(WITH_DEXPREOPT),)
        WITH_DEXPREOPT := true
        WITH_DEXPREOPT_COMP := false
        WITH_DEXPREOPT_PIC := true
    endif
endif

# inherit from the proprietary version
-include vendor/huawei/msm7x30-common/BoardConfigVendor.mk
