import numpy as np
import cv2
from matplotlib import pyplot as plt


def find_ghost(img_who, img_where, img_to_change):
    mmc = 10
    sift = cv2.SIFT_create()

    kp1, des1 = sift.detectAndCompute(img_who, None)
    kp2, des2 = sift.detectAndCompute(img_where, None)
    fik = 0
    index_params = dict(algorithm=fik, trees=5)
    search_params = dict(checks=50)
    flann = cv2.FlannBasedMatcher(index_params, search_params)
    matches = flann.knnMatch(des1, des2, k=2)

    good = []
    for lb, n in matches:
        if lb.distance < 0.7*n.distance:
            good.append(lb)

    if len(good) > mmc:
        src_pts = np.float32([kp1[m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
        dst_pts = np.float32([kp2[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)
        lb, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 5.0)
        h, w = img_who.shape
        pts = np.float32([[0, 0], [0, h-1], [w-1, h-1], [w-1, 0]]).reshape(-1, 1, 2)
        dst = cv2.perspectiveTransform(pts, lb)
        img_to_change = cv2.polylines(img_to_change, [np.int32(dst)], True, 255, 3, cv2.LINE_AA)

        a = dst[0][0]
        b = dst[1][0]
        c = dst[2][0]
        d = dst[3][0]

        mx = [max(a[0], b[0], c[0], d[0]), max(a[1], b[1], c[1], d[1])]
        mn = [min(a[0], b[0], c[0], d[0]), min(a[1], b[1], c[1], d[1])]

        for i in range(int(mn[0]), int(mx[0])):
            if i % 2 == 0:
                z = mx[1]
            else:
                z = mn[1]
            x = [[[i, z]]]
            dst = np.append(dst, x, axis=0)
        img_rect = cv2.polylines(img_where, [np.int32(dst)], True, 255, 3, cv2.LINE_AA)
        return 1, img_rect, img_to_change
    else:
        return 0, img_where, img_to_change


img1_2 = cv2.imread('candy_ghost.png', 0)
img1_3 = cv2.imread('pampkin_ghost.png', 0)
img1_1 = cv2.imread('scary_ghost.png', 0)
g = [img1_1, img1_2, img1_3]
img2 = cv2.imread('lab7.png', 0)
img3 = cv2.imread('lab7.png', 0)
for p in g:
    while True:
        flag, img3, img2 = find_ghost(p, img3, img2)
        if flag == 0:
            flag, img3, img2 = find_ghost(cv2.flip(p, 1), img3, img2)
            if flag == 0:
                break
        plt.imshow(img2, 'gray'), plt.show()
