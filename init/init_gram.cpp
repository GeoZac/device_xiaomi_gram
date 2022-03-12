/*
   Copyright (C) 2020 The LineageOS Project.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <vector>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

using android::base::GetProperty;

std::vector<std::string> ro_props_default_source_order = {
    "",
    "bootimage.",
    "odm.",
    "product.",
    "system.",
    "system_ext.",
    "vendor.",
};

void property_override(char const prop[], char const value[], bool add = true)
{
    prop_info *pi;

    pi = (prop_info *) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void set_ro_build_prop(const std::string &prop, const std::string &value) {
    for (const auto &source : ro_props_default_source_order) {
        auto prop_name = "ro." + source + "build." + prop;
        if (source == "")
            property_override(prop_name.c_str(), value.c_str());
        else
            property_override(prop_name.c_str(), value.c_str(), false);
    }
};

void set_ro_product_prop(const std::string &prop, const std::string &value) {
    for (const auto &source : ro_props_default_source_order) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    }
};


void load_dalvik_properties() {
    char const *heapstartsize;
    char const *heapgrowthlimit;
    char const *heapsize;
    char const *heapminfree;
    char const *heapmaxfree;
    char const *heaptargetutilization;
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram >= 5ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-6144-dalvik-heap.mk
        heapstartsize = "16m";
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heaptargetutilization = "0.5";
        heapminfree = "8m";
        heapmaxfree = "32m";
    } else {
        // from - phone-xhdpi-4096-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.6";
        heapminfree = "8m";
        heapmaxfree = "16m";
    }

    property_override("dalvik.vm.heapstartsize", heapstartsize);
    property_override("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_override("dalvik.vm.heapsize", heapsize);
    property_override("dalvik.vm.heaptargetutilization", heaptargetutilization);
    property_override("dalvik.vm.heapminfree", heapminfree);
    property_override("dalvik.vm.heapmaxfree", heapmaxfree);
}

// From Magisk@native/jni/magiskhide/hide_utils.c
static const char *cts_prop_key[] = {
    "ro.boot.vbmeta.device_state",
    "ro.boot.verifiedbootstate",
    "ro.boot.flash.locked",
    "ro.boot.veritymode",
    "ro.boot.warranty_bit",
    "ro.warranty_bit",
    "ro.debuggable",
    "ro.secure",
    "ro.build.type",
    "ro.build.tags",
    "ro.vendor.boot.warranty_bit",
    "ro.vendor.warranty_bit",
    "vendor.boot.vbmeta.device_state",
    nullptr
};

static const char *cts_prop_value[] = {
    "locked",
    "green",
    "1",
    "enforcing",
    "0",
    "0",
    "0",
    "1",
    "user",
    "release-keys",
    "0",
    "0",
    "locked",
    nullptr
};

static const char *cts_late_prop_key[] =
        { "vendor.boot.verifiedbootstate", nullptr };

static const char *cts_late_prop_value[] =
        { "green", nullptr };

void workaround_cts_properties() {

    // Hide all sensitive props
    for (int i = 0; cts_prop_key[i]; ++i) {
        property_override(cts_prop_key[i], cts_prop_value[i]);
    }
    for (int i = 0; cts_late_prop_key[i]; ++i) {
        property_override(cts_late_prop_key[i], cts_late_prop_value[i]);
    }
}

void vendor_load_properties() {
    std::string hwname;
    std::string region;
    hwname = GetProperty("ro.boot.hwname", "");
    region = GetProperty("ro.boot.hwc", "");

    std::string model;
    std::string device;
    std::string fingerprint;
    std::string description;
    std::string mod_device;
    std::string brand;

    if (hwname == "curtana") {
        brand = "Redmi";
        device = "curtana";
        if (region == "India") {
            model = "Redmi Note 9 Pro";
            fingerprint = "Redmi/curtana_in/curtana:11/RKQ1.200826.002/V12.0.5.0.RJWINXM:user/release-keys";
            description = "curtana_in-user 11 RKQ1.200826.002 V12.0.5.0.RJWINXM release-keys";
            // marketname = "Redmi Note 9 Pro";
            mod_device = "curtana_in";
        } else {
            model = "Redmi Note 9S";
            fingerprint = "Redmi/curtana_global/curtana:11/RKQ1.200826.002/V12.0.4.0.RJWMIXM:user/release-keys";
            description = "curtana_global-user 11 RKQ1.200826.002 V12.0.4.0.RJWMIXM release-keys";
            // marketname = "Redmi Note 9S";
            mod_device = "curtana_global";
        }
    } else if (hwname == "gram") {
        brand = "POCO";
        model = "POCO M2 Pro";
        device = "gram";
        fingerprint = "POCO/gram_in/gram:11/RKQ1.200826.002/V12.0.1.1.RJPINXM:user/release-keys";
        description = "gram_in-user 11 RKQ1.200826.002 V12.0.1.0.RJPINXM release-keys";
        mod_device = "gram_in_global";
    }

    set_ro_build_prop("fingerprint", fingerprint);
    set_ro_product_prop("brand", brand);
    set_ro_product_prop("device", device);
    set_ro_product_prop("model", model);
    property_override("ro.build.description", description.c_str());
    property_override("ro.build.display.id", description.c_str());
    if (mod_device != "") {
        property_override("ro.product.mod_device", mod_device.c_str());
    }

    load_dalvik_properties();

    // SafetyNet workaround
    workaround_cts_properties();
}
