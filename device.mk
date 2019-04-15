#
# Copyright (C) 2020 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Installs gsi keys into ramdisk, to boot a GSI with verified boot.
$(call inherit-product, $(SRC_TARGET_DIR)/product/gsi_keys.mk)

# setup dalvik vm configs.
$(call inherit-product, frameworks/native/build/phone-xhdpi-6144-dalvik-heap.mk)

# Enable updating of APEXes
$(call inherit-product, $(SRC_TARGET_DIR)/product/updatable_apex.mk)

# Get non-open-source specific aspects
$(call inherit-product, vendor/xiaomi/gram/gram-vendor.mk)

# The first api level, device has been commercially launched on.
PRODUCT_SHIPPING_API_LEVEL := 29

PRODUCT_TARGET_VNDK_VERSION := 30

# A/B
AB_OTA_UPDATER := false

# Boot animation
TARGET_SCREEN_HEIGHT := 2400
TARGET_SCREEN_WIDTH := 1080

# Camera
PRODUCT_PACKAGES += \
    Snap

# Fastbootd
PRODUCT_PACKAGES += \
    fastbootd

# fstab
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/rootdir/etc/fstab.qcom:$(TARGET_COPY_OUT_RAMDISK)/fstab.qcom

# FM
PRODUCT_PACKAGES += \
    FM2 \
    libqcomfm_jni \
    qcom.fmradio

# HIDL
PRODUCT_PACKAGES += \
    android.hidl.base@1.0 \
    android.hidl.manager@1.0

# IDC
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/idc/uinput-fpc.idc:$(TARGET_COPY_OUT_SYSTEM)/usr/idc/uinput-fpc.idc \
    $(LOCAL_PATH)/configs/idc/uinput-goodix.idc:$(TARGET_COPY_OUT_SYSTEM)/usr/idc/uinput-goodix.idc

# Init
PRODUCT_PACKAGES += \
    init.qcom.rc

# Keylayout
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/keylayout/uinput-fpc.kl:$(TARGET_COPY_OUT_SYSTEM)/usr/keylayout/uinput-fpc.kl \
    $(LOCAL_PATH)/configs/keylayout/uinput-goodix.kl:$(TARGET_COPY_OUT_SYSTEM)/usr/keylayout/uinput-goodix.kl

# Lights
PRODUCT_PACKAGES += \
    android.hardware.lights-service.qti-gram

# Livedisplay
PRODUCT_PACKAGES += \
    lineage.livedisplay@2.0-service-sdm \
    LiveDisplayOverlay

# Overlays -- Override vendor ones
PRODUCT_PACKAGES += \
    FrameworksResTarget \
    DevicesOverlay \
    DevicesAndroidOverlay

# Overlays
DEVICE_PACKAGE_OVERLAYS += \
    $(LOCAL_PATH)/overlay

# rro_overlays
PRODUCT_PACKAGES += \
    WifiOverlay \
    TetheringConfigOverlay

# Partitions 
PRODUCT_USE_DYNAMIC_PARTITIONS := true
PRODUCT_BUILD_SUPER_PARTITION := false

# Perf
PRODUCT_PACKAGES += \
    vendor.qti.hardware.perf@2.0

# Power
PRODUCT_PACKAGES += \
    android.hardware.power-service.gram

# Soong namespaces
PRODUCT_SOONG_NAMESPACES += \
    $(LOCAL_PATH)

# Telephony
PRODUCT_PACKAGES += \
    ims-ext-common \
    ims_ext_common.xml \
    qti-telephony-hidl-wrapper \
    qti_telephony_hidl_wrapper.xml \
    qti-telephony-utils \
    qti_telephony_utils.xml \
    telephony-ext

PRODUCT_BOOT_JARS += \
    telephony-ext

# WiFi Display
PRODUCT_PACKAGES += \
    libdisplayconfig.qti \
    libnl \
    libqdMetaData \
    libavservices_minijail \
    libavservices_minijail_32 \
    vendor.display.config@2.0

PRODUCT_BOOT_JARS += \
    WfdCommon
