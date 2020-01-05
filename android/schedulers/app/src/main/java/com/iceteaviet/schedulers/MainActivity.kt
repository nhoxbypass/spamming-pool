package com.iceteaviet.schedulers

import android.graphics.Color
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import java.util.*
import java.util.concurrent.TimeUnit


class MainActivity : AppCompatActivity() {
    private lateinit var tvCount: TextView
    private var count = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        tvCount = findViewById(R.id.tv_count)
        findViewById<Button>(R.id.btn_tap).setOnClickListener {
            Log.d("Genius", "onClick()")
            // Update color on each click
            tvCount.setTextColor(genRandomColor())

            ExecutorAndroidSchedulers.mainThread().debounce(ExecutorAndroidSchedulers.Key.TEST_KEY, Runnable {
                Log.d("Genius", "On result debounce!")

                count++
                tvCount.text = count.toString()
            }, 3, TimeUnit.SECONDS)

            /*HandlerAndroidSchedulers.mainThread().debounce(ExecutorAndroidSchedulers.Key.TEST_KEY, object : Callback<Any> {
                override fun callback(result: Any) {
                    Log.d("Genius", "On result debounce!")

                    count++
                    tvCount.text = count.toString()
                }
            }, 3, TimeUnit.SECONDS)*/
        }
    }

    private fun genRandomColor(): Int {
        val rnd = Random()
        return Color.argb(255, rnd.nextInt(256), rnd.nextInt(256), rnd.nextInt(256))
    }
}