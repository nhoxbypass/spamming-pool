package com.example.nhoxb.rtalab01.helper;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.DatabaseErrorHandler;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import com.example.nhoxb.rtalab01.model.Data;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by nhoxb on 12/12/2016.
 */
public class DatabaseHelper extends SQLiteOpenHelper {
    private static DatabaseHelper sInstance;

    private static final String TAG = "DATABASE";

    // Database Info
    private static final String DATABASE_NAME = "rtaDatabase";
    private static final int DATABASE_VERSION = 1;

    // Table Names
    private static final String TABLE_USERS = "users";

    private static final String KEY_INSTANCE_ID = "id";
    private static final String KEY_DATA_PATH = "dataPath";

    public DatabaseHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
    }

    public DatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, 1);
    }

    public static synchronized DatabaseHelper getInstance(Context context) {
        // Use the application context, which will ensure that you
        // don't accidentally leak an Activity's context.
        // See this article for more information: http://bit.ly/6LRzfx
        if (sInstance == null) {
            sInstance = new DatabaseHelper(context.getApplicationContext());
        }
        return sInstance;
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        String CREATE_USERS_TABLE = "CREATE TABLE " + TABLE_USERS +
                "(" +
                KEY_INSTANCE_ID + " TEXT," +
                KEY_DATA_PATH + " TEXT" +
                ")";

        sqLiteDatabase.execSQL(CREATE_USERS_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int oldVersion, int newVersion) {
        if (oldVersion != newVersion) {
            // Simplest implementation is to drop all old tables and recreate them
            sqLiteDatabase.execSQL("DROP TABLE IF EXISTS " + TABLE_USERS);
            onCreate(sqLiteDatabase);
        }
    }

    public void addData(Data data)
    {
        // Create and/or open the database for writing
        SQLiteDatabase db = getWritableDatabase();

        // It's a good idea to wrap our insert in a transaction. This helps with performance and ensures
        // consistency of the database.
        db.beginTransaction();
        try {
            ContentValues values = new ContentValues();
            values.put(KEY_INSTANCE_ID, data.getInstanceID());
            values.put(KEY_DATA_PATH, data.getDataFilePath());

            // Notice how we haven't specified the primary key. SQLite auto increments the primary key column.
            db.insertOrThrow(TABLE_USERS, null, values);

            db.setTransactionSuccessful();
        } catch (Exception e) {
            Log.d(TAG, "Error while trying to add post to database");
        } finally {
            db.endTransaction();
        }
    }

    public List<Data> getAllData()
    {
        List<Data> dataList = new ArrayList<>();

        String query = "SELECT * FROM " + TABLE_USERS;

        SQLiteDatabase db = getReadableDatabase();
        Cursor cursor  = db.rawQuery(query, null);

        if (cursor.moveToFirst())
        {
            do {
                String id = cursor.getString(cursor.getColumnIndex(KEY_INSTANCE_ID));
                String path = cursor.getString(cursor.getColumnIndex(KEY_DATA_PATH));
                Data data = new Data(id, path);
                dataList.add(data);
            } while(cursor.moveToNext());
        }

        if (cursor != null && !cursor.isClosed()) {
            cursor.close();
        }

        return  dataList;
    }
}
