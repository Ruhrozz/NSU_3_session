import cv2
import numpy as np

cap = cv2.VideoCapture(0)

_, frame1 = cap.read()
_, frame2 = cap.read()

green = np.array([0, 0, 255], dtype=np.uint8)
red = np.array([0, 255, 0], dtype=np.uint8)
blank = np.zeros(frame1.shape[:2], dtype='uint8')

acc = 0
f = 0

while cap.isOpened():
    if acc == 1000 and f == 1:
        green = np.array([0, 255, 0], dtype=np.uint8)
        f = 0
        acc = 0
    elif acc == 1000:
        green = np.array([0, 0, 255], dtype=np.uint8)
        f = 1
        acc = 0

    diff = cv2.absdiff(frame1, frame2)

    diff_r = cv2.GaussianBlur(diff, (5, 5), cv2.BORDER_DEFAULT)
    diff_r = cv2.inRange(diff_r, (0, 20, 0), (255, 255, 255))
    diff_r = cv2.cvtColor(diff_r, cv2.IMREAD_COLOR)

    mask_r = np.where(np.all(diff_r != (255, 255, 255), axis=-1, keepdims=True), red, green)

    res1 = cv2.addWeighted(frame1, 0.8, mask_r, 0.6, 0)

    cv2.imshow("frame1", res1)

    frame1 = frame2
    ret, frame2 = cap.read()
    acc += 10
    if cv2.waitKey(10) == 27:
        break

cap.release()
cv2.destroyAllWindows()
