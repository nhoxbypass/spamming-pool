package com.example.nhoxb.rtalab01.activity;

import android.app.Dialog;
import android.app.DialogFragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

import com.example.nhoxb.rtalab01.R;

/**
 * Created by nhoxb on 12/12/2016.
 */
public class DetailDialogFragment extends DialogFragment {
    private static final String KEY_DATA = "data";
    private TextView mTextView;

    public DetailDialogFragment() {
        // Empty constructor is required for DialogFragment
        // Make sure not to add arguments to the constructor
        // Use `newInstance` instead as shown below
    }

    public static DetailDialogFragment newInstance(String xmlData) {

        Bundle args = new Bundle();
        args.putString(KEY_DATA, xmlData);
        DetailDialogFragment fragment = new DetailDialogFragment();
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.dialog_datacontent, container);
    }

    @Override
    public void onStart() {
        super.onStart();
        int height = getResources().getDimensionPixelSize(R.dimen.popup_height);
        getDialog().getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT, height);
    }

    @Override
    public void onResume() {
        //Get existing layout params of window
        ViewGroup.LayoutParams layoutParams = getDialog().getWindow().getAttributes();

        //Assign window properties to layout params width and height
        layoutParams.width = WindowManager.LayoutParams.MATCH_PARENT;
        layoutParams.height = getResources().getDimensionPixelSize(R.dimen.popup_height);


        //Set the layout params back to the dialog
        getDialog().getWindow().setAttributes((WindowManager.LayoutParams) layoutParams);

        // Call super onResume after sizing
        super.onResume();
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        Dialog dialog = super.onCreateDialog(savedInstanceState);

        //request
        dialog.getWindow().requestFeature(Window.FEATURE_NO_TITLE);
        return dialog;
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        mTextView = (TextView) view.findViewById(R.id.tv_data_detail);
        String data = getArguments().getString(KEY_DATA);
        mTextView.setText(data);
    }
}
