package com.blefish.huaweisettings.settings;

import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.TaskStackBuilder;
import android.content.Context;
import android.content.Intent;
import android.support.v4.app.NotificationCompat;

import com.blefish.huaweisettings.MainActivity;
import com.blefish.huaweisettings.R;

import java.io.File;

/**
 * Created by rudolf on 12/19/14.
 */
public class USBHost implements Setting {
    private static final String USB_HOST_PATH  = "/sys/devices/platform/msm_otg/mode";
    private static final Integer USB_HOST_ON_STATE = 1;
    private static final Integer USB_HOST_OFF_STATE = 0;

    private int mId = 0;

    @Override
    public boolean isSupported(Context context) {
        File file = new File(USB_HOST_PATH);
        return file.exists();
    }

    @Override
    public void writeValue(String value) {
        Integer state = USB_HOST_OFF_STATE;
        if (value.equals("true"))
            state = USB_HOST_ON_STATE;

        /* Update only if value is changed. */
        if (!FileUtils.readOneLine(USB_HOST_PATH).equals(state.toString()))
            FileUtils.writeLine(USB_HOST_PATH, state.toString());
    }

    public void writeValueNotification(Context context, String value) {
        writeValue(value);

        if (value.equals("true"))
            showNotification(context);
        else
            hideNotification(context);
    }

    private void showNotification(Context context) {
        NotificationCompat.Builder mBuilder =
                new NotificationCompat.Builder(context)
                        .setSmallIcon(com.android.internal.R.drawable.stat_sys_data_usb)
                        .setContentTitle(context.getString(R.string.not_usb_host_title))
                        .setContentText(context.getString(R.string.not_usb_host_text))
                        .setOngoing(true);
        // Creates an explicit intent for an Activity in your app
        Intent resultIntent = new Intent(context, MainActivity.class);

        // The stack builder object will contain an artificial back stack for the
        // started Activity.
        // This ensures that navigating backward from the Activity leads out of
        // your application to the Home screen.
        TaskStackBuilder stackBuilder = TaskStackBuilder.create(context);
        // Adds the back stack for the Intent (but not the Intent itself)
        stackBuilder.addParentStack(MainActivity.class);
        // Adds the Intent that starts the Activity to the top of the stack
        stackBuilder.addNextIntent(resultIntent);
        PendingIntent resultPendingIntent =
                stackBuilder.getPendingIntent(
                        0,
                        PendingIntent.FLAG_UPDATE_CURRENT
                );
        mBuilder.setContentIntent(resultPendingIntent);
        NotificationManager mNotificationManager =
                (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        // mId allows you to update the notification later on.
        mNotificationManager.notify(mId, mBuilder.build());
    }

    private void hideNotification(Context context) {
        NotificationManager mNotificationManager =
                (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        // mId allows you to update the notification later on.
        mNotificationManager.cancel(mId);
    }
}
