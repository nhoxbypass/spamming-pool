package com.example.nhoxb.rtalab01.activity;

import android.content.Intent;
import android.graphics.Paint;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.Toast;

import com.example.nhoxb.rtalab01.R;
import com.example.nhoxb.rtalab01.adapter.FileListAdapter;
import com.example.nhoxb.rtalab01.helper.DatabaseHelper;
import com.example.nhoxb.rtalab01.model.Data;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

public class ListActivity extends AppCompatActivity {

    RecyclerView rvListFile;
    Button btnImport;
    Button btnDetail;
    ProgressBar pbLoadData;

    private FileListAdapter mFileListAdapter;
    private RecyclerView.LayoutManager layoutManager;
    private File mCurrFile;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list);

        rvListFile = (RecyclerView) findViewById(R.id.rv_file_list);
        btnDetail = (Button) findViewById(R.id.btn_detail);
        btnImport = (Button) findViewById(R.id.btn_import);
        pbLoadData = (ProgressBar) findViewById(R.id.progress_bar);

        mFileListAdapter = new FileListAdapter(readDataFiles("data"));
        layoutManager = new LinearLayoutManager(this);

        mFileListAdapter.setOnListFileClickListener(new FileListAdapter.OnListFileClickListener() {
            @Override
            public void onClick(File file) {
                mCurrFile = file;
            }
        });

        rvListFile.setAdapter(mFileListAdapter);
        rvListFile.setLayoutManager(layoutManager);

        btnImport.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DataManipulation task = new DataManipulation();
                task.execute(mCurrFile);
            }
        });

        btnDetail.setPaintFlags(btnDetail.getPaintFlags() | Paint.UNDERLINE_TEXT_FLAG);
        btnDetail.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(ListActivity.this, DetailActivity.class);
                startActivity(intent);
            }
        });
    }

    List<File> readDataFiles(String subPath) {
        String path = Environment.getExternalStorageDirectory().toString() + "/" + subPath;
        Log.d("Files", "Path: " + path);
        File directory = new File(path);
        File[] files = directory.listFiles();
        Log.d("Files", "Size: " + files.length);

        mCurrFile = files[0];
        return Arrays.asList(files);
    }

    String parseXmlData(File file) {
        try {
            InputStream is = new FileInputStream(file.getPath());
            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            DocumentBuilder db = dbf.newDocumentBuilder();
            Document doc = db.parse(new InputSource(is));
            doc.getDocumentElement().normalize();

            NodeList nodeList = doc.getElementsByTagName("instanceID");

            for (int i = 0; i < nodeList.getLength(); i++) {

                Node node = nodeList.item(i);

                Element fstElmnt = (Element) node;
                return fstElmnt.getFirstChild().getNodeValue();
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        } catch (SAXException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    public File copy(File src, String dstPath, String instanceId) throws IOException {
        File desFolder = new File(Environment.getExternalStorageDirectory().toString() + "/" + dstPath + "/");

        if (!desFolder.exists()) {
            desFolder.mkdirs();
        }

        String path = desFolder.getPath() + File.separator + src.getName();
        File dst = new File(path);

        if (!dst.exists()) {
            dst.createNewFile();
            InputStream in = new FileInputStream(src);
            OutputStream out = new FileOutputStream(dst);

            // Transfer bytes from in to out
            byte[] buf = new byte[1024];
            int len;
            while ((len = in.read(buf)) > 0) {
                out.write(buf, 0, len);
            }
            in.close();
            out.close();

            DatabaseHelper databaseHelper = DatabaseHelper.getInstance(ListActivity.this);
            Data data = new Data(instanceId, dst.getPath());
            databaseHelper.addData(data);
        }

        return dst;
    }

    public class DataManipulation extends AsyncTask<File, Integer, String> {
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pbLoadData.setVisibility(View.VISIBLE);
        }

        @Override
        protected String doInBackground(File... files) {
            publishProgress(10);
            String instanceId = parseXmlData(files[0]);
            publishProgress(40);
            if (instanceId != null) {

                try {
                    File dstFile = copy(files[0], "official-data", instanceId);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            publishProgress(100);
            return instanceId;
        }

        @Override
        protected void onProgressUpdate(Integer... values) {
            super.onProgressUpdate(values);
            pbLoadData.setProgress(values[0]);
        }

        @Override
        protected void onPostExecute(String str) {
            super.onPostExecute(str);
            pbLoadData.setVisibility(View.GONE);
            if (str == null)
                Toast.makeText(ListActivity.this,"Can't find InstanceId tag!", Toast.LENGTH_SHORT).show();
        }
    }


}
