import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt

# Prikaz slika
def show2images(img1,img2, desc1, desc2):
    plt.figure(figsize=(10, 4))
    plt.subplot(1, 2, 1)
    plt.imshow(img1, cmap='gray')
    plt.title(desc1)
    plt.subplot(1, 2, 2)
    plt.imshow(img2, cmap='gray')
    plt.title(desc2)
    plt.show()
def show3images(img1,img2,img3,desc1,desc2,desc3):
    plt.figure(figsize=(14, 5))
    plt.subplot(1, 3, 1)
    plt.imshow(img1, cmap='gray')
    plt.title(desc1)
    plt.subplot(1, 3, 2)
    plt.imshow(img2, cmap='gray')
    plt.title(desc2)
    plt.subplot(1, 3, 3)
    plt.imshow(img3, cmap='gray')
    plt.title(desc3)
    plt.show()
# Ucitavanje slika
def loadImage(imgPath):
    image = cv.imread(imgPath)
    image = cv.cvtColor(image, cv.COLOR_BGR2RGB)
    return image

# Uparivanje feature-a koristeci BFMatcher
def match_features(desA, desB):

    # bf = cv.BFMatcher()
    # matches = bf.knnMatch(desA, desB, k=2)

    FLANN_INDEX_KDTREE = 1
    index_params = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
    search_params = dict(checks=50)
    flann = cv.FlannBasedMatcher(index_params, search_params)
    matches = flann.knnMatch(desA, desB, k=2)

    good = []
    for m, n in matches:
        if m.distance < 0.7 * n.distance:
            good.append([m])
    return good

# Homografija pomocu RANSAC-a
def compute_homography(kp1, kp2, matches):
    src = np.float32([kp1[m.queryIdx].pt for m in matches]).reshape(-1,1,2)
    dst = np.float32([kp2[m.trainIdx].pt for m in matches]).reshape(-1,1,2)
    H, mask = cv.findHomography(src, dst, cv.RANSAC, 5.0)
    return H

# Formiranje panorame od 2 slike
def makePanorama(img1, img2):
    detector = cv.SIFT_create()

    # SIFT odredi feature-e
    kp1, des1 = detector.detectAndCompute(img2, None) #slika i maska
    kp2, des2 = detector.detectAndCompute(img1, None)

    # Koristeci BFMatcher ili FLANNMatcher vrsimo uparivanje feature-a
    matches = match_features(des1, des2)

    # Prikaz match-ovanih feature-a na slikama
    imgMatch = cv.drawMatchesKnn(img1, kp1, img2, kp2, matches, None, flags=cv.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)
    imgMatchInverted = cv.cvtColor(imgMatch, cv.COLOR_RGB2BGR)
    cv.imshow("Matched features", imgMatchInverted)
    cv.waitKey(0)

    matches = [x for sublist in matches for x in sublist]

    # Homografija pomocu RANSAC
    homography = compute_homography(kp1, kp2, matches)

    # Spajamo slike koristeci warpPerspective
    width = img1.shape[1] + img2.shape[1]
    height = img1.shape[0] + int(img2.shape[0] / 2)
    panorama = cv.warpPerspective(img2, homography, (width, height))
    panorama[0:img1.shape[0], 0:img1.shape[1] - 1] = img1[0:img1.shape[0], 0:img1.shape[1] - 1]
    # panorama[0:img1.shape[0], 0:img1.shape[1]] = img1

    return crop_black(panorama)

# Izbacivanje crnog dela slike
def crop_black(panorama):
    gray = cv.cvtColor(panorama, cv.COLOR_RGB2GRAY)
    _, thresh = cv.threshold(gray, 1, 255, cv.THRESH_BINARY)
    coords = cv.findNonZero(thresh)
    x, y, w, h = cv.boundingRect(coords)

    cropped = panorama[y:y+h, x:x+w]
    return cropped

# Main
if __name__ == '__main__':
    img1 = loadImage("1.jpg")
    img2 = loadImage("2.jpg")
    img3 = loadImage("3.jpg")

    #show3images(img1, img2, img3, "1", "2", "3")

    panorama23 = makePanorama(img2, img3)
    plt.imshow(panorama23)
    plt.title("Panorama izmedju 2 i 3")
    plt.show()

    panorama = makePanorama(img1,panorama23)

    plt.imshow(panorama)
    plt.title("Panorama")
    plt.show()

    panoramaInverted = cv.cvtColor(panorama, cv.COLOR_RGB2BGR)
    cv.imwrite("panorama.jpg", panoramaInverted)