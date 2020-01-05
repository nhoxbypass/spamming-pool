package com.iceteaviet.schedulers

import android.os.Handler
import android.os.Looper
import java.util.concurrent.ConcurrentHashMap
import java.util.concurrent.Executors
import java.util.concurrent.Future
import java.util.concurrent.TimeUnit

/**
 * Android schedulers using [java.util.concurrent.Executor]
 */
class ExecutorAndroidSchedulers private constructor(private val handler: Handler) {

    /**
     * Schedulers
     */
    private val scheduledExecutor = Executors.newSingleThreadScheduledExecutor()
    private val emissions = ConcurrentHashMap<Any, Future<*>>()

    /**
     * Debounce {@param runnable} by {@param delay}
     * Schedules it to be executed after given delay, or cancels its execution
     * if the method is called with the same key again within the delay time.
     */
    fun debounce(key: Any, runnable: Runnable, delay: Long, unit: TimeUnit) {
        val prev = emissions.put(key, scheduledExecutor.schedule({
            try {
                handler.post(runnable)
            } finally {
                emissions.remove(key)
            }
        }, delay, unit))
        prev?.cancel(true)
    }

    /**
     * Debounce {@param runnable} by {@param delay}
     * Schedules it to be executed after given delay, and cancels other schedules
     * if the method is called with the same key again within the delay time.
     */
    fun throttleFirst(key: Any, runnable: Runnable, delay: Long, unit: TimeUnit) {
        if (emissions.containsKey(key)) return
        emissions[key] = scheduledExecutor.schedule({
            try {
                handler.post(runnable)
            } finally {
                emissions.remove(key)
            }
        }, delay, unit)
    }

    fun shutdown() {
        scheduledExecutor.shutdownNow()
    }

    /**
     * Key to determine the group ID of debounce / throttle
     */
    object Key {
        const val TEST_KEY = 1
    }

    companion object {
        private val LOCK = Any()
        private var T_MAIN_INSTANCE: ExecutorAndroidSchedulers? = null
        /**
         * A scheduler which executes actions on the Android main thread.
         *
         *
         * The returned scheduler will post asynchronous messages to the looper by default.
         */
        fun mainThread(): ExecutorAndroidSchedulers {
            if (T_MAIN_INSTANCE == null) {
                synchronized(LOCK) {
                    if (T_MAIN_INSTANCE == null) {
                        T_MAIN_INSTANCE = ExecutorAndroidSchedulers(Handler(Looper.getMainLooper()))
                    }
                }
            }
            return T_MAIN_INSTANCE!!
        }
    }

}