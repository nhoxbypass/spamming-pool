package com.iceteaviet.schedulers

import android.os.Handler
import android.os.Looper
import java.util.concurrent.ConcurrentHashMap
import java.util.concurrent.TimeUnit

/**
 * Android schedulers using [Handler.sendMessageDelayed]
 */
class HandlerAndroidSchedulers private constructor() {

    /**
     * Schedulers
     */
    private val handler: Handler
    private val emissions = ConcurrentHashMap<Int, Callback<Any>>()

    /**
     * Debounce {@param runnable} by {@param delay}
     * Schedules it to be executed after given delay, or cancels its execution
     * if the method is called with the same key again within the delay time.
     */
    fun debounce(key: Int, callback: Callback<Any>, delay: Long, unit: TimeUnit) {
        handler.removeMessages(key)
        val message = handler.obtainMessage(key, callback)
        handler.sendMessageDelayed(message, unit.toMillis(delay))
    }

    /**
     * Debounce {@param runnable} by {@param delay}
     * Schedules it to be executed after given delay, and cancels other schedules
     * if the method is called with the same key again within the delay time.
     */
    fun throttleFirst(key: Int, data: Any, delay: Long, unit: TimeUnit) {

    }

    /**
     * Key to determine the group ID of debounce / throttle
     */
    class Key private constructor() {

    }

    companion object {
        private val LOCK = Any()
        private var T_MAIN_INSTANCE: HandlerAndroidSchedulers? = null
        /**
         * A scheduler which executes actions on the Android main thread.
         *
         *
         * The returned scheduler will post asynchronous messages to the looper by default.
         */
        fun mainThread(): HandlerAndroidSchedulers {
            if (T_MAIN_INSTANCE == null) {
                synchronized(LOCK) {
                    if (T_MAIN_INSTANCE == null) {
                        T_MAIN_INSTANCE = HandlerAndroidSchedulers()
                    }
                }
            }
            return T_MAIN_INSTANCE!!
        }
    }

    init {
        this.handler = Handler(Looper.getMainLooper()) { message ->
            val callback = message.obj as Callback<Any>
            callback.callback(message.obj)
            return@Handler true
        }
    }
}