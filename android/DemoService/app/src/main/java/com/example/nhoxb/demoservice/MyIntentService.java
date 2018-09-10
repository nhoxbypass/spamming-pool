package com.example.nhoxb.demoservice;

import android.app.Activity;
import android.app.IntentService;
import android.app.Notification;
import android.app.PendingIntent;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Environment;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;


/**
 * An {@link IntentService} subclass for handling asynchronous task requests in
 * a service on a separate handler thread.
 * <p/>
 * TODO: Customize class - update intent actions and extra parameters.
 */
public class MyIntentService extends IntentService {

    private int res = Activity.RESULT_CANCELED;
    public static final String URL = "url";
    public static final String NAME = "name";
    public static final String RESULT = "result";
    public MyIntentService() {
        super("MyIntentService");
    }

    @Override
    protected void onHandleIntent(Intent intent) {
        if (intent != null) {
            String url = intent.getStringExtra(URL);
            String name = intent.getStringExtra(NAME);

            File file = new File(Environment.getExternalStorageDirectory(),name);

            if (file.exists())
            {
                file.delete();
            }
            else
            {
                try {
                    URL url1 = new URL(url);
                    HttpURLConnection connection = (HttpURLConnection) url1.openConnection();
                    connection.connect();

                    InputStream inputStream = connection.getInputStream();
                    InputStreamReader reader = new InputStreamReader(inputStream);

                    FileOutputStream fileOutputStream = new FileOutputStream(file.getPath());
                    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fileOutputStream));

                    BufferedReader br = new BufferedReader(reader);
                    StringBuilder builder = new StringBuilder();

                    String temp = "";

                    while ((temp = br.readLine()) != null)
                    {
                        builder.append(temp);
                    }

                    temp = builder.toString();

                    bw.write(temp);

                    fileOutputStream.close();


                    res = Activity.RESULT_OK;

                    sendDataBroadcast(url,res);

                } catch (MalformedURLException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public void sendDataBroadcast(String path, int res)
    {
        Intent intent = new Intent("com.example.nhoxb.demoservice");
        intent.putExtra("FilePath",path);
        intent.putExtra(RESULT,res);

        sendBroadcast(intent);
    }

    public void playMusic(Intent intent)
    {
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);

        PendingIntent pendIntent = PendingIntent.getActivity(this, 0, intent, 0);


        Notification.Builder builder = new Notification.Builder(getApplicationContext());
        builder.setTicker("Ticker text").setContentTitle("Content Title").setContentText("CONTENT text")
                .setOngoing(true).setPriority(Notification.PRIORITY_HIGH)
                .setWhen(System.currentTimeMillis()).setAutoCancel(false)
                .setContentIntent(pendIntent)
                .setSmallIcon(R.drawable.icon);

        Notification notice = builder.build();

        startForeground(1234, notice);

        MediaPlayer mediaPlayer;
        mediaPlayer = MediaPlayer.create(this,R.raw.guianhxanho);

        mediaPlayer.setLooping(true);

        mediaPlayer.start();
    }

}
