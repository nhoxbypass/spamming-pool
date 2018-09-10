package iceteaviet.com.threadpool;

import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "Genius";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ///////////////////
        //THREADs
        //Create 10 Threads
        List<MyThread> threads = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            threads.add(new MyThread(String.valueOf(i)));
        }

        //and start together
        //All 10 Threads run parallel
        for (int i = 0; i < 10; i++) {
            threads.get(i).start();
        }

        //BUT
        //If we use ExecutorService to run these Threads
        //creating a pool of exactly 5 threads
        ExecutorService executorService = Executors.newFixedThreadPool(5);

        //Start all 10 threads together using this executor
        for (int i = 0; i < 10; i++) {
            executorService.execute(threads.get(i));
        }
        executorService.shutdown();

        while (!executorService.isTerminated()) {
            //Wait for these Threads to finish running
        }
        Log.e(TAG, "Finished all threads");

        //Output will be
        //pool-1-1: Thread 1 started: (pool-1-1 is the name of the current thread Thread.currentThread().getName())
        //pool-1-2: Thread 2 started
        //pool-1-3: Thread 3 started
        //pool-1-4: Thread 4 started
        //pool-1-5: Thread 5 started
        // *Wait 5 secs*
        //pool-1-1: Thread 1 finished
        //pool-1-2: Thread 6 started
        //pool-1-2: Thread 2 finished
        //pool-1-3: Thread 7 started
        //pool-1-4: Thread 4 finished
        //pool-1-5: Thread 8 started
        //...
        //Finished all threads
        //This means: There only 5 PARALLEL threads available provided by ThreadPool.
        // If we start more than 5, only 5 can run first, the others must wait for an empty slot.


        ///////////////////
        //ASYNCTASKs
        //Create 5 AsyncTask
        List<MyAsyncTask> myAsyncTasks = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            myAsyncTasks.add(new MyAsyncTask());
        }

        //And start together
        //BUT 5 AsyncTask run sequentially
        //Ex:
        //  All 5 AsyncTask run onPreExecute()
        // -> The AsyncTask-0 doInBackground()
        // -> The AsyncTask-0 sleep()
        // -> The AsyncTask-0 onPostExecute()
        // -> The AsyncTask-1 doInBackground()
        //...
        for (int i = 0; i < 5; i++) {
            myAsyncTasks.get(i).execute(String.valueOf(i));
        }

        //BUT
        //If we use ThreadPoolExecutor to execute these AsyncTasks
        //All 5 AsyncTask run parallel same as normal Thread above
        for (int i = 0; i < 5; i++) {
            if (Build.VERSION.SDK_INT >= 11) {
                //post GB (API 11) use SERIAL executor by default
                //So we need to use ThreadPoolExecutor to execute these AsyncTasks
                myAsyncTasks.get(i).executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, String.valueOf(i));
            } else {
                //Pre GB (API 11) uses ThreadPoolExecutor by default
                //So it's already running parallel, we DO NOT need to use Executor
                myAsyncTasks.get(i).execute(String.valueOf(i));
            }
        }
    }

    class MyThread extends Thread {
        String name;

        MyThread(String name) {
            this.name = name;
        }

        @Override
        public void run() {
            super.run();
            Log.e(TAG, "Thread " + name + " started");
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Log.e(TAG, "Thread " + name + " finished");
        }
    }

    class MyAsyncTask extends AsyncTask<String, String, String> {

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            Log.e(TAG, "onPreExecute");
        }

        @Override
        protected String doInBackground(String... strings) {
            Log.e(TAG, "doInBackground: " + strings[0]);
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return strings[0];
        }

        @Override
        protected void onPostExecute(String s) {
            super.onPostExecute(s);
            Log.e(TAG, "onPostExecute: " + s);
        }
    }
}
