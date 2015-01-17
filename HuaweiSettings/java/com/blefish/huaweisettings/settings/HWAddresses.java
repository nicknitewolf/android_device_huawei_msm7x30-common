package com.blefish.huaweisettings.settings;

import android.content.Context;

import java.io.File;

/**
 * Created by rudolf on 12/26/14.
 */
public class HWAddresses implements Setting {
    private static final String HWADDR_DATA_PATH = "/data/misc/hwprops";
    private static final String HWADDR_RESET_SYFS_PATH = "/sys/hwprops/reset";

    @Override
    public boolean isSupported(Context context) {
        File file = new File(HWADDR_RESET_SYFS_PATH);
        File directory = new File(HWADDR_DATA_PATH);
        return file.exists() && directory.isDirectory();
    }

    @Override
    public void writeValue(String value) {
        /* This setting only resets the addresses if it has been turned off. */
        if (value.equals("false")) {
            FileUtils.writeLine(HWADDR_RESET_SYFS_PATH, "1");

            File btFile = new File(BTMac.BT_MAC_DATA_PATH);
            btFile.delete();

            File wlanFile = new File(WlanMac.WLAN_MAC_DATA_PATH);
            wlanFile.delete();
        }
    }
}
