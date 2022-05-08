# Undistort
Fisheye camera undistort bindings of c++ code.

Download source file and extract. Run command below to generate a '.so' file and copy it to your project source folder.
```text
mkdir build && cd build
cmake ..
make
```
And camera parameter txt files 'intrinsics.txt' and 'dis_coeff.txt' in format shown below are required:

intrinsics.txt
```text
369.465	0	293.981	
0	370.06	250.893	
0	0	1	
```
dis_coeff.txt
```text
-0.0264624	0.00321169	-0.0615013	0.0856743
```

Usage example:
```python
import Undistort
import cv2

cap = cv2.VideoCapture(0)
# create instance with parameters (camera frame width and height)
undistort = Undistort.Undistort(640, 480)
while True:
    _, frame = cap.read()
    corrected = undistort.remap(frame) # remap the frame
    cv2.imshow("frame", frame)
    cv2.imshow("corrected", corrected)
    q = cv2.waitKey(1)
    if q == ord('q'):
        break;
```
