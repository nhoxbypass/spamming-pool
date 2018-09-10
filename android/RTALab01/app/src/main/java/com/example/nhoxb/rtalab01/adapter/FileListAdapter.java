package com.example.nhoxb.rtalab01.adapter;

import android.support.v4.content.ContextCompat;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.nhoxb.rtalab01.R;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by nhoxb on 12/12/2016.
 */
public class FileListAdapter extends RecyclerView.Adapter<FileListAdapter.FileViewHolder> {

    private List<File> mFileList;
    private OnListFileClickListener mListener;
    private int focusedItem = 0;

    public FileListAdapter() {
        mFileList = new ArrayList<>();
    }

    public FileListAdapter(List<File> files) {
        mFileList = files;
    }

    public void setOnListFileClickListener(OnListFileClickListener listener) {
        mListener = listener;
    }

    @Override
    public FileViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View itemView = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_list_file, parent, false);
        return new FileViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(FileViewHolder holder, int position) {
        holder.setData(mFileList.get(position));
        holder.itemView.setSelected(focusedItem == position);
    }

    @Override
    public int getItemCount() {
        return mFileList.size();
    }

    public interface OnListFileClickListener {
        public void onClick(File file);
    }

    class FileViewHolder extends RecyclerView.ViewHolder {
        TextView txtFileName;

        public FileViewHolder(final View itemView) {
            super(itemView);
            txtFileName = (TextView) itemView.findViewById(R.id.tv_file_name);
            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    notifyItemChanged(focusedItem);
                    focusedItem = getLayoutPosition();
                    notifyItemChanged(focusedItem);
                    mListener.onClick(mFileList.get(getAdapterPosition()));
                }
            });

            itemView.setBackground(ContextCompat.getDrawable(txtFileName.getContext(), R.drawable.state_item_filelist));
        }

        void setData(File file) {
            txtFileName.setText(file.getName());
        }
    }
}
