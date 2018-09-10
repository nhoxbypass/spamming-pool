package com.codepath.android.lollipopexercise.adapters;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.v4.app.ActivityOptionsCompat;
import android.support.v4.util.Pair;
import android.support.v7.graphics.Palette;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.codepath.android.lollipopexercise.Utils;
import com.codepath.android.lollipopexercise.activities.DetailsActivity;
import com.squareup.picasso.Target;

import com.codepath.android.lollipopexercise.R;
import com.codepath.android.lollipopexercise.models.Contact;
import com.squareup.picasso.Picasso;

import java.util.List;

// Provide the underlying view for an individual list item.
public class ContactsAdapter extends RecyclerView.Adapter<ContactsAdapter.VH> {
    private Activity mContext;
    private List<Contact> mContacts;
    public OnContactClickListener mListener;

    public ContactsAdapter(Activity context, List<Contact> contacts) {
        mContext = context;
        if (contacts == null) {
            throw new IllegalArgumentException("contacts must not be null");
        }
        mContacts = contacts;
    }


    public void setOnItemClickListener(OnContactClickListener listener)
    {
        mListener = listener;
    }


    // Inflate the view based on the viewType provided.
    @Override
    public VH onCreateViewHolder(ViewGroup parent, int viewType) {
        View itemView = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_contact, parent, false);
        return new VH(itemView, mContext);
    }

    // Display data at the specified position
    @Override
    public void onBindViewHolder(VH holder, int position) {
        Contact contact = mContacts.get(position);
        holder.rootView.setTag(contact);
        holder.tvName.setText(contact.getName());
        Picasso.with(mContext).load(contact.getThumbnailDrawable()).fit().centerCrop().into(holder.ivProfile);

        // Store the target into the tag for the profile to ensure target isn't garbage collected prematurely
        holder.ivProfile.setTag(holder.target);
        // Instruct Picasso to load the bitmap into the target defined above
        Picasso.with(mContext).load(contact.getThumbnailDrawable()).into(holder.target);
    }

    @Override
    public int getItemCount() {
        return mContacts.size();
    }

    public interface OnContactClickListener
    {
        public void onContactClick(Contact contact, ActivityOptionsCompat options);
    }

    // Provide a reference to the views for each contact item
    public final class VH extends RecyclerView.ViewHolder {
        final View rootView;
        final ImageView ivProfile;
        final TextView tvName;
        final View vPalette;
        Palette palette;
        Target target;


        public VH(View itemView, final Context context) {
            super(itemView);
            rootView = itemView;
            ivProfile = (ImageView)itemView.findViewById(R.id.ivProfile);
            tvName = (TextView)itemView.findViewById(R.id.tvName);
            vPalette = itemView.findViewById(R.id.vPalette);

            target = Utils.getTarget(vPalette);


            // Navigate to contact details activity on click of card view.
            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    final Contact contact = (Contact)v.getTag();
                    if (contact != null) {
                        // Fire an intent when a contact is selected
                        // Pass contact object in the bundle and populate details activity.
                        Pair<View, String> profilePair = Pair.create((View)ivProfile,"profile");
                        Pair<View, String> palettePair = new Pair<View, String>(vPalette,"palette");
                        Pair<View, String> namePair = new Pair<View, String>((View)tvName,"name");
                        ActivityOptionsCompat options = ActivityOptionsCompat.
                                makeSceneTransitionAnimation(mContext, profilePair, palettePair, namePair);

                        mListener.onContactClick(contact, options);
                    }
                }
            });
        }
    }
}
