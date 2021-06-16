package com.example.infinitybox.fragments;

import android.app.Fragment;
import android.os.Bundle;


import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.infinitybox.R;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link PatternsFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class PatternsFragment extends Fragment {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_patterns, container, false);
    }
}