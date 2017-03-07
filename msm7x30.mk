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

# The gps config appropriate for this device
$(call inherit-product, device/common/gps/gps_eu_supl.mk)

# Use standard dalvik heap sizes
$(call inherit-product, frameworks/native/build/phone-hdpi-512-dalvik-heap.mk)

DEVICE_PACKAGE_OVERLAYS += device/huawei/msm7x30-common/overlay

PRODUCT_AAPT_CONFIG := normal
PRODUCT_AAPT_PREF_CONFIG := hdpi

# Common hardware-specific features
PRODUCT_COPY_FILES += \
	frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml \
	frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
	frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
	frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
	frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
	frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
	frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
	frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
	frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
	frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml

# Media codecs
PRODUCT_COPY_FILES += \
	frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:system/etc/media_codecs_google_audio.xml \
	frameworks/av/media/libstagefright/data/media_codecs_google_telephony.xml:system/etc/media_codecs_google_telephony.xml \
	frameworks/av/media/libstagefright/data/media_codecs_google_video.xml:system/etc/media_codecs_google_video.xml

# Graphics libraries
PRODUCT_PACKAGES += \
	libc2dcolorconvert \
	libgenlock \
	libmemalloc \
	liboverlay \
	libqdutils \
	libqservice \
	libtilerenderer

PRODUCT_PACKAGES += \
	libboringssl-compat \
	libstlport

# OMX libraries
PRODUCT_PACKAGES += \
	libstagefrighthw \
	libOmxCore \
	libOmxVdec \
	libOmxVenc

# Audio libraries
PRODUCT_PACKAGES += \
	libaudio-resampler \
	libaudioutils

# HAL
PRODUCT_PACKAGES += \
	audio.a2dp.default \
	audio.primary.msm7x30 \
	audio.r_submix.default \
	audio.usb.default \
	camera.msm7x30 \
	copybit.msm7x30 \
	gralloc.msm7x30 \
	gps.msm7x30 \
	hwcomposer.msm7x30 \
	lights.msm7x30 \
	memtrack.msm7x30 \
	power.msm7x30

# Common packages
PRODUCT_PACKAGES += \
	charger_res_images \
	HuaweiSettings \
	hostapd \
	hwprops \
	fstab.qcom \
	init.qcom.rc \
	init.qcom.usb.rc \
	ueventd.qcom.rc \
	audio_policy.conf \
	media_codecs.xml \
	media_profiles.xml \
	wpa_supplicant \
	wpa_supplicant.conf \
	wpa_supplicant_overlay.conf \
	lvm \
	lvm.conf

# Recovery init script
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/recovery/init.recovery.qcom.rc:root/init.recovery.qcom.rc

# Common properties
PRODUCT_PROPERTY_OVERRIDES += \
	ro.sf.lcd_density=240 \
	ro.config.low_ram=true \
	ro.opengles.version=131072 \
	wifi.interface=wlan0 \
	ro.bt.bdaddr_path=/sys/hwprops/btmac \
	ro.hwro=1 \
	persist.sys.strictmode.visual=0 \
	persist.sys.strictmode.disable=1 \
	ro.sys.fw.bg_apps_limit=8 \
	config.disable_atlas=true

# IO Scheduler
PRODUCT_PROPERTY_OVERRIDES += \
	sys.io.scheduler=bfq

# ART
PRODUCT_PROPERTY_OVERRIDES += \
	dalvik.vm.dex2oat-filter=balanced \
	dalvik.vm.dex2oat-swap=false \
	dalvik.vm.image-dex2oat-filter=speed

# Audio properties
PRODUCT_PROPERTY_OVERRIDES += \
	audio.offload.disable=1

# Graphics properties
PRODUCT_PROPERTY_OVERRIDES += \
	debug.sf.hw=1 \
	debug.composition.type=mdp \
	persist.hwc.mdpcomp.enable=true \
	debug.mdpcomp.maxlayer=3 \
	debug.mdpcomp.idletime=-1 \
	persist.sys.force_highendgfx=true

# Include proprietary stuff
$(call inherit-product, vendor/huawei/msm7x30-common/msm7x30-common-vendor.mk)
