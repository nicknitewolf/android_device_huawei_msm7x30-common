package com.blefish.huaweisettings.settings;

import android.content.Context;

import java.io.File;
import java.io.IOException;

/**
 * Created by rudolf on 12/26/14.
 */
public class WlanMac implements Setting {
    public static final String WLAN_MAC_DATA_PATH = "/data/misc/hwprops/wlanmac";
    private static final String WLAN_MAC_SYSFS_PATH = "/sys/hwprops/wlanmac";

    @Override
    public boolean isSupported(Context context) {
        File file = new File(WLAN_MAC_SYSFS_PATH);
        return file.exists();
    }

    public String getValue() {
        return FileUtils.readOneLine(WLAN_MAC_SYSFS_PATH);
    }

    @Override
    public void writeValue(String value) {
        FileUtils.writeLine(WLAN_MAC_DATA_PATH, value);
        try {
            Runtime.getRuntime().exec("/system/bin/hwprops -wlanmac");
        } catch (IOException e) {
        }
    }
}
