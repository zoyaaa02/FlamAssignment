
# EdgeViewer

EdgeViewer is a boilerplate camera app for processing camera preview frames in real-time using the OpenCV Android SDK and native OpenCV library. It provides a simple platform for developers to prototype real-time image processing techniques on smartphones, leveraging native code for optimal performance.

As an example, the app applies OpenCV’s Laplacian filter to each preview frame.

🧩 Features  
- Modifies preview frames from Camera2 API using OpenCV Android SDK  
- Performs image processing with native C++ code for efficiency  
- Supports swapping between front and back cameras  
- Displays FPS overlay in the application  

⚙️ Tech Stack  
| Layer          | Technology                  |  
|----------------|-----------------------------|  
| Android App    | Java + OpenCV Android SDK   |  
| Native Processing | C++ via JNI                |  
| Build Tools    | Gradle, CMake, NDK          |  


💡 Usage  
The main Java callback `MyGLSurfaceView.onCameraTexture` passes frames to native `processFrame` for image processing.  

📌 Notes  
- Tested with OpenCV 3.4.2 and target SDK 27  
- Designed for prototyping real-time image processing  
- Example processing: Laplacian edge detection of live camera frames  

***
