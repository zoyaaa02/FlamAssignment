package com.example.edgeviewer;

import androidx.appcompat.app.AppCompatActivity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;
import org.opencv.android.OpenCVLoader;

public class MainActivity extends AppCompatActivity {

    static {
        if (!OpenCVLoader.initLocal()) {
            System.loadLibrary("opencv_java4");
        }
        System.loadLibrary("edgeviewer");
    }

    private native Bitmap processImage(Bitmap inputImage);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ImageView imgOriginal = findViewById(R.id.imageOriginal);
        ImageView imgProcessed = findViewById(R.id.imageProcessed);

        // Load sample image from drawable
        Bitmap input = BitmapFactory.decodeResource(getResources(), R.drawable.sample);
        imgOriginal.setImageBitmap(input);

        // Process it using OpenCV (JNI)
        Bitmap output = processImage(input);
        imgProcessed.setImageBitmap(output);
    }
}
