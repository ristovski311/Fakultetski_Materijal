import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt

def loadImageRGB(path):
    image = cv.imread(path)
    image = cv.cvtColor(image, cv.COLOR_BGR2RGB)
    return image
def loadImageHSV(path):
    image = cv.imread(path)
    image = cv.cvtColor(image, cv.COLOR_BGR2HSV)
    return image
def loadImageGray(path):
    image = cv.imread(path)
    image = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
    return image

def show2images(img1,img2, desc1, desc2):
    plt.figure(figsize=(10, 4))
    plt.subplot(1, 2, 1)
    plt.imshow(img1, cmap='gray')
    plt.title(desc1)
    plt.subplot(1, 2, 2)
    plt.imshow(img2, cmap='gray')
    plt.title(desc2)
    plt.show()


#THRESH SLIDER
def threshSlider(image):

    #Callback za slajder (trackbar)
    def threshSliderRefresh(x):
        _, imageThresh = cv.threshold(image, x, 255, cv.THRESH_BINARY_INV)
        cv.imshow("Output", imageThresh)

    cv.namedWindow("Output")
    cv.createTrackbar("sliderThresh", "Output", 127, 255, threshSliderRefresh)

    _, imageThresh = cv.threshold(image, 127, 255, cv.THRESH_BINARY)
    imageThresh = 255 - imageThresh

    cv.imshow("Input", image)
    cv.imshow("Output", imageThresh)
    cv.waitKey(0)

#THRESHOLD
def threshImage(image, threshVal):
    _, imageThresh = cv.threshold(image, threshVal, 255, cv.THRESH_BINARY_INV)
    return imageThresh

#DILACIJA
def dilateImage(image, ksize):
    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, ksize=(ksize, ksize))
    imageDilate = cv.dilate(image, kernel=kernel)
    return imageDilate

#EROZIJA
def erodeImage(image, ksize):
    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, ksize=(ksize, ksize))
    imageErode = cv.erode(image, kernel=kernel)
    return imageErode

#ZATVARANJE
def closeImage(image, ksize):
    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, ksize=(ksize, ksize))
    imageClose = cv.dilate(image, kernel=kernel)
    imageClose = cv.erode(imageClose, kernel=kernel)
    return imageClose

#OTVARANJE
def openImage(image, ksize):
    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, ksize=(ksize, ksize))
    imageOpen = cv.erode(image, kernel=kernel)
    imageOpen = cv.dilate(imageOpen, kernel=kernel)
    return imageOpen

#REKONSTRUKCIJA
def morphological_reconstruction(marker: np.ndarray, mask: np.ndarray):
    kernel = np.ones(shape=(7, 7), dtype=np.uint8) * 255
    while True:
        expanded = cv.dilate(src=marker, kernel=kernel)
        expanded = cv.bitwise_and(src1=expanded, src2=mask)

        if (marker == expanded).all():
            return expanded
        marker = expanded

#
# MAIN
#

if __name__ == '__main__':

    imageRGB = loadImageRGB("coins.png")
    imageGRAY = loadImageGray("coins.png")
    show2images(imageRGB, imageGRAY, "RGB", "GRAY")

    # threshSlider(imageGRAY)

    imageThresh = threshImage(imageGRAY, 140)
    imageClose = closeImage(imageThresh, 16)
    show2images(imageThresh, imageClose, "Thrashold", "Zatvaranje")

    coinsMask = imageClose #Cisto da bude u skladu sa tekstom zadatka, ovo je maska svih novcica

    imageHSV = loadImageHSV("coins.png")
    imageSaturation = imageHSV[:,:,1]

    # threshSlider(imageSaturation)

    imageThreshSat = threshImage(imageSaturation, 100)
    imageSatOpen = openImage(imageThreshSat, 2) #Mora da bi uklonio noise da ne pokvari rekonstrukciju
    marker = 255 - imageSatOpen
    show3images(imageSaturation, imageThreshSat, marker, "Saturacija", "Thresh saturacije", "Otvaranje thr saturacije", )


    imageReconstructed = morphological_reconstruction(marker, coinsMask)
    bakarniNovcic = cv.bitwise_and(imageRGB, imageRGB, mask=imageReconstructed)
    show2images(imageReconstructed, bakarniNovcic, "Rekonstrukcija", "Bakarni novcic")