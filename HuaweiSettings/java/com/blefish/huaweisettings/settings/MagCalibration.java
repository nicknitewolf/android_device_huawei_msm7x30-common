package com.blefish.huaweisettings.settings;

import java.io.File;

/**
 * Created by rudolf on 12/26/14.
 */
public class MagCalibration implements Setting {
    private static final String MAG_CALIBRATION_PATH = "/data/misc/sensors/lsm303dlh_mag";

    @Override
    public boolean isSupported() {
        File file = new File(MAG_CALIBRATION_PATH);
        return file.exists();
    }

    @Override
    public void writeValue(String value) {
        File file = new File(MAG_CALIBRATION_PATH);
        file.delete();
    }
}
