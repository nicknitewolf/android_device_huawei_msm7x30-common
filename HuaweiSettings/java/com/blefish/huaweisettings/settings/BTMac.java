package com.blefish.huaweisettings.settings;

import java.io.File;
import java.io.IOException;

/**
 * Created by rudolf on 12/26/14.
 */
public class BTMac implements Setting {
    public static final String BT_MAC_DATA_PATH = "/data/misc/hwprops/btmac";
    private static final String BT_MAC_SYSFS_PATH = "/sys/hwprops/btmac";

    @Override
    public boolean isSupported() {
        File file = new File(BT_MAC_SYSFS_PATH);
        return file.exists();
    }

    public String getValue() {
        return FileUtils.readOneLine(BT_MAC_SYSFS_PATH);
    }

    @Override
    public void writeValue(String value) {
        if (value != getValue())
            FileUtils.writeLine(BT_MAC_DATA_PATH, value);
        try {
            Runtime.getRuntime().exec("/system/bin/hwprops -btmac");
        } catch (IOException e) {
        }
    }
}
