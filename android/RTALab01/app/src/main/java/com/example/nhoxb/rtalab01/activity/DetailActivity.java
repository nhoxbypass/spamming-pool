package com.example.nhoxb.rtalab01.activity;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.MenuItem;

import com.example.nhoxb.rtalab01.R;
import com.example.nhoxb.rtalab01.adapter.DetailListAdapter;
import com.example.nhoxb.rtalab01.helper.DatabaseHelper;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringWriter;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

public class DetailActivity extends AppCompatActivity {

    RecyclerView rvDetailList;

    private DetailListAdapter mAdapter;
    private RecyclerView.LayoutManager mLayoutManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        rvDetailList = (RecyclerView) findViewById(R.id.rv_data_list);

        DatabaseHelper databaseHelper = DatabaseHelper.getInstance(this);

        mAdapter = new DetailListAdapter(databaseHelper.getAllData());
        mAdapter.setOnListDetailClickListener(new DetailListAdapter.OnListDetailClickListener() {
            @Override
            public void onClick(String path) {
                try {
                    showDetailDialog(path);
                } catch (ParserConfigurationException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (SAXException e) {
                    e.printStackTrace();
                } catch (TransformerException e) {
                    e.printStackTrace();
                }
            }
        });
        mLayoutManager = new LinearLayoutManager(this);

        rvDetailList.setAdapter(mAdapter);
        rvDetailList.setLayoutManager(mLayoutManager);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            finish(); // close this activity and return to preview activity (if there is any)
        }
        return super.onOptionsItemSelected(item);
    }

    private void showDetailDialog(String path) throws ParserConfigurationException, IOException, SAXException, TransformerException {
        InputStream is = new FileInputStream(path);
        DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
        DocumentBuilder db = dbf.newDocumentBuilder();
        Document doc = db.parse(new InputSource(is));
        doc.getDocumentElement().normalize();

        String data = beautifyXml(doc.getFirstChild());

        android.app.FragmentManager fm = getFragmentManager();
        DetailDialogFragment dialog = DetailDialogFragment.newInstance(data);
        dialog.show(fm, "fragment_data_detail");
    }

    public String beautifyXml(Node doc) throws TransformerException {
        Transformer transformer = TransformerFactory.newInstance().newTransformer();
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");
        transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");
        transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "yes");
        //initialize StreamResult with File object to save to file
        StreamResult result = new StreamResult(new StringWriter());
        DOMSource source = new DOMSource(doc);
        transformer.transform(source, result);
        String xmlString = result.getWriter().toString();
        return xmlString;
    }

}
