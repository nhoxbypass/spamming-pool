package com.example.nhoxb.rtalab01.model;

/**
 * Created by nhoxb on 12/12/2016.
 */
public class Data {
    public Data(String id, String path) {
        instanceID = id;
        dataFilePath = path;
    }

    public String getInstanceID() {
        return instanceID;
    }

    public String getDataFilePath() {
        return dataFilePath;
    }

    String instanceID;
    String dataFilePath;
}
