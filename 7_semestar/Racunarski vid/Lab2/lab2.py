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

def threshImage(image, threshVal):
    _, imageThresh = cv.threshold(image, threshVal, 255, cv.THRESH_BINARY_INV)
    return imageThresh

def dilateImage(image):
    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, ksize=(15, 15))
    imageDilate = cv.dilate(image, kernel=kernel)
    return imageDilate

def erodeImage(image, ksize):
    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, ksize=(ksize, ksize))
    imageErode = cv.erode(image, kernel=kernel)
    return imageErode

def closeImage(image, ksize):
    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, ksize=(ksize, ksize))
    imageClose = cv.dilate(image, kernel=kernel)
    imageClose = cv.erode(imageClose, kernel=kernel)
    return imageClose

def openImage(image, ksize):
    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, ksize=(ksize, ksize))
    imageOpen = cv.erode(image, kernel=kernel)
    imageOpen = cv.dilate(imageOpen, kernel=kernel)
    return imageOpen

def morphological_reconstruction(marker: np.ndarray, mask: np.ndarray):
    kernel = np.ones(shape=(7, 7), dtype=np.uint8) * 255
    while True:
        expanded = cv.dilate(src=marker, kernel=kernel)
        expanded = cv.bitwise_and(src1=expanded, src2=mask)

        if (marker == expanded).all():
            return expanded
        marker = expanded

if __name__ == '__main__':

    imageRGB = loadImageRGB("coins.png")
    imageGRAY = loadImageGray("coins.png")
    plt.figure(figsize=(10, 4))
    plt.subplot(1, 2, 1)
    plt.imshow(imageRGB, cmap='gray')
    plt.title("RGB")
    plt.subplot(1, 2, 2)
    plt.imshow(imageGRAY, cmap='gray')
    plt.title("GRAY")
    plt.show()

    # threshSlider(imageGRAY)

    imageThresh = threshImage(imageGRAY, 140)
    # imageDilate = dilateImage(imageThresh)
    imageClose = closeImage(imageThresh, 16)

    # plt.figure(figsize=(10, 4))
    # plt.subplot(1, 2, 1)
    # plt.imshow(imageThresh, cmap='gray')
    # plt.title("Thresh")
    # plt.subplot(1, 2, 2)
    # plt.imshow(imageDilate, cmap='gray')
    # plt.title("Dilatacija")
    # plt.show()

    plt.figure(figsize=(10, 4))
    plt.subplot(1, 2, 1)
    plt.imshow(imageThresh, cmap='gray')
    plt.title("Thresh")
    plt.subplot(1, 2, 2)
    plt.imshow(imageClose, cmap='gray')
    plt.title("Zatvaranje")
    plt.show()

    # plt.figure(figsize=(10, 4))
    # plt.subplot(1, 2, 1)
    # plt.imshow(imageDilate, cmap='gray')
    # plt.title("Dilatacija")
    # plt.subplot(1, 2, 2)
    # plt.imshow(imageClose, cmap='gray')
    # plt.title("Zatvaranje")
    # plt.show()

    coinsMask = imageClose #Cisto da bude u skladu sa tekstom zadatka, ovo je maska svih novcica

    imageHSV = loadImageHSV("coins.png")
    imageSaturation = imageHSV[:,:,1]

    # threshSlider(imageSaturation)

    imageThreshSat = threshImage(imageSaturation, 100)

    imageSatOpen = openImage(imageThreshSat, 2)
    marker = 255 - imageSatOpen

    plt.figure(figsize=(14, 5))
    plt.subplot(1, 3, 1)
    plt.imshow(imageSaturation, cmap='gray')
    plt.title("Kanal saturacije")
    plt.subplot(1, 3, 2)
    plt.imshow(imageThreshSat, cmap='gray')
    plt.title("Thresh saturacije")
    plt.subplot(1, 3, 3)
    plt.imshow(marker, cmap='gray')
    plt.title("Otvaranje saturacije")
    plt.show()

    imageReconstructed = morphological_reconstruction(marker, coinsMask)
    plt.imshow(imageReconstructed, cmap="gray")
    plt.title("Rekonstrukcija")
    plt.show()

    bakarniNovcic = cv.bitwise_and(imageRGB, imageRGB, mask=imageReconstructed)
    plt.imshow(bakarniNovcic)
    plt.title("Bakarni novcic")
    plt.show()