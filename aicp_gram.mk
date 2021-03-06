#
# Copyright (C) 2020 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit some common AICP stuff
$(call inherit-product, vendor/aicp/config/common_full_phone.mk)

# Inherit from gram device
$(call inherit-product, $(LOCAL_PATH)/device.mk)

PRODUCT_BRAND := xiaomi
PRODUCT_DEVICE := gram
PRODUCT_MANUFACTURER := xiaomi
PRODUCT_NAME := aicp_gram
PRODUCT_MODEL := POCO M2 Pro

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi
TARGET_VENDOR := xiaomi
TARGET_VENDOR_PRODUCT_NAME := gram
PRODUCT_BUILD_PROP_OVERRIDES += PRIVATE_BUILD_DESC="gram-user 11 RKQ1.200826.002 V12.0.1.0.RJPINXM release-keys"

# Set BUILD_FINGERPRINT variable to be picked up by both system and vendor build.prop
BUILD_FINGERPRINT := POCO/gram_in/gram:11/RKQ1.200826.002/V12.0.1.0.RJPINXM:user/release-keys

PRODUCT_OVERRIDE_INFO := true
PRODUCT_OVERRIDE_FINGERPRINT := google/walleye/walleye:8.1.0/OPM1.171019.011/4448085:user/release-keys
