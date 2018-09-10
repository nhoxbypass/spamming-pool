package com.example.nhoxb.demoservice;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.IBinder;
import android.support.annotation.Nullable;
import android.widget.Toast;

public class MyService extends Service {
    public MyService() {
    }

    MediaPlayer mediaPlayer;


    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        MyRunable runable = new MyRunable(intent);
        Thread thread = new Thread(runable);
        thread.start();

        return START_STICKY;
    }


    class MyRunable implements Runnable
    {
        Intent intent;
        public MyRunable(Intent intent)
        {
            this.intent = intent;
        }

        @Override
        public void run() {
            //Toast.makeText(MyService.this, "Service started!", Toast.LENGTH_SHORT).show();

            intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);

            PendingIntent pendIntent = PendingIntent.getActivity(getApplicationContext(), 0, intent, 0);


            Notification.Builder builder = new Notification.Builder(getApplicationContext());
            builder.setTicker("Ticker text").setContentTitle("Content Title").setContentText("CONTENT text")
                    .setOngoing(true).setPriority(Notification.PRIORITY_HIGH)
                    .setWhen(System.currentTimeMillis()).setAutoCancel(false)
                    .setContentIntent(pendIntent)
                    .setSmallIcon(R.drawable.icon);

            Notification notice = builder.build();
            mediaPlayer.start();
            startForeground(1234, notice);
        }
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Toast.makeText(MyService.this, "Service destroyed!", Toast.LENGTH_SHORT).show();
        mediaPlayer.stop();
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Toast.makeText(MyService.this, "Service created!", Toast.LENGTH_SHORT).show();
        mediaPlayer = MediaPlayer.create(this,R.raw.guianhxanho);

        mediaPlayer.setLooping(true);

    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }


}
