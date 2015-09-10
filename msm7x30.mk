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

PRODUCT_BOOT_JARS += qcmediaplayer

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

# Graphics libraries
PRODUCT_PACKAGES += \
	libc2dcolorconvert \
	libgenlock \
	libmemalloc \
	liboverlay \
	libqdutils \
	libqservice \
	libtilerenderer

# OMX libraries
PRODUCT_PACKAGES += \
	libstagefrighthw \
	libOmxCore \
	libOmxVdec \
	libOmxVenc

# Audio libraries
PRODUCT_PACKAGES += \
	libaudio-resampler \
	libaudioutils \
	libdashplayer

# HAL
PRODUCT_PACKAGES += \
	audio.a2dp.default \
	audio_policy.msm7x30 \
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
	fstab.qcom.lvm \
	init.fs.sh \
	init.qcom.rc \
	init.qcom.usb.rc \
	ueventd.qcom.rc \
	audio_policy.conf \
	media_codecs.xml \
	media_profiles.xml \
	qcmediaplayer \
	wpa_supplicant \
	wpa_supplicant.conf \
	wpa_supplicant_overlay.conf \
	lvm \
	lvm.conf

# Common apps
PRODUCT_PACKAGES += \
	Torch

# Recovery init script
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/recovery/init.recovery.qcom.rc:root/init.recovery.qcom.rc

# Common default properties
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
	persist.sys.usb.config=mtp

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
	ro.sys.fw.bg_apps_limit=16 \
	ro.config.max_starting_bg=8

# Audio properties
PRODUCT_PROPERTY_OVERRIDES += \
	audio.offload.disable=1 \
	persist.sys.media.use-awesome=true \
	lpa.decode=true

# Graphics properties
PRODUCT_PROPERTY_OVERRIDES += \
	debug.sf.hw=1 \
	debug.composition.type=mdp \
	persist.hwc.mdpcomp.enable=true \
	debug.mdpcomp.maxlayer=3 \
	debug.mdpcomp.idletime=-1 \
	persist.sys.force_highendgfx=true

# Recovery
PRODUCT_PROPERTY_OVERRIDES += \
	ro.cwm.forbid_format=/boot,/recovery,/cust

# Include proprietary stuff
$(call inherit-product, vendor/huawei/msm7x30-common/msm7x30-common-vendor.mk)
