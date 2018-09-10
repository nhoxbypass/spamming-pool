package com.example.nhoxb.rtalab01.adapter;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.nhoxb.rtalab01.R;
import com.example.nhoxb.rtalab01.model.Data;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by nhoxb on 12/12/2016.
 */
public class DetailListAdapter extends RecyclerView.Adapter<DetailListAdapter.DetailViewHolder> {

    private List<Data> mDataList;
    private OnListDetailClickListener mListener;

    public DetailListAdapter() {
        mDataList = new ArrayList<>();
    }

    public DetailListAdapter(List<Data> datas) {
        mDataList = datas;
    }

    public void setOnListDetailClickListener(OnListDetailClickListener listener) {
        mListener = listener;
    }

    @Override
    public DetailViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View itemView = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_list_file, parent, false);
        return new DetailViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(DetailViewHolder holder, int position) {
        holder.setData(mDataList.get(position));
    }

    @Override
    public int getItemCount() {
        return mDataList.size();
    }

    public interface OnListDetailClickListener {
        public void onClick(String path);
    }

    class DetailViewHolder extends RecyclerView.ViewHolder {
        TextView txtFileName;

        public DetailViewHolder(final View itemView) {
            super(itemView);
            txtFileName = (TextView) itemView.findViewById(R.id.tv_file_name);
            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    mListener.onClick(mDataList.get(getAdapterPosition()).getDataFilePath());
                }
            });
        }

        void setData(Data data) {
            txtFileName.setText(data.getInstanceID());
        }
    }
}
