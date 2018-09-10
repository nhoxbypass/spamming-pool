package com.example.nhoxb.demoservice;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

import java.net.Inet4Address;

public class MainActivity extends AppCompatActivity {

    private BroadcastReceiver receiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String path = intent.getStringExtra("FilePath");
            int res = intent.getIntExtra(MyIntentService.RESULT,0);

            if (res == Activity.RESULT_OK)
            {
                Toast.makeText(getApplicationContext(),"Succeed " + path,Toast.LENGTH_SHORT).show();
            }
            else
            {
                Toast.makeText(MainActivity.this,"Failed",Toast.LENGTH_SHORT).show();
            }
        }
    };

    @Override
    protected void onPause() {
        super.onPause();
        registerReceiver(receiver,new IntentFilter("com.example.nhoxb.demoservice"));
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //startDownload();


        Intent intent = new Intent(MainActivity.this, MyService.class);
        startService(intent);

    }

    public void startDownload()
    {
        Intent intent = new Intent(MainActivity.this,MyIntentService.class);
        intent.putExtra(MyIntentService.URL,"http://mp3.zing.vn/bai-hat/Gui-Anh-Xa-Nho-Bich-Phuong/ZW7UFI6I.html");
        intent.putExtra(MyIntentService.NAME,"GuiAnhXaNho.html");

        startService(intent);
    }
}
