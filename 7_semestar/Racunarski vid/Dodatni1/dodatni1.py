import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt

#UCITAVANJE SLIKE
def loadImageGray(path):
    image = cv.imread(path)
    image = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
    return image

#THRESHOLD
def threshImage(image, threshVal):
    _, imageThresh = cv.threshold(image, threshVal, 255, cv.THRESH_BINARY)
    return imageThresh

#DILACIJA
def dilateImage(image, ksize):
    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, ksize=(ksize, ksize))
    imageDilate = cv.dilate(image, kernel=kernel)
    return imageDilate

#REKONSTRUKCIJA
def morphological_reconstruction(marker: np.ndarray, mask: np.ndarray):
    kernel = np.ones(shape=(7, 7), dtype=np.uint8) * 255
    while True:
        expanded = cv.dilate(src=marker, kernel=kernel)
        expanded = cv.bitwise_and(src1=expanded, src2=mask)

        if (marker == expanded).all():
            return expanded
        marker = expanded

#PRIKAZIVANJE SLIKA
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

#MAIN
if __name__ == '__main__':

    #DODATNI ZADATAK 1 - RACUNARSKI VID - Ristovski Nikola 19347

    # imageGRAY = loadImageGray("slika1.jpg")
    imageGRAY = loadImageGray("slika2.jpg")

    #Da dobijemo cistu masku sa vrednostima 0 i 255
    imageMASK = threshImage(imageGRAY, 128)

    #Pravljenje maske gde je samo border debljine 1px oko slike sa vrednoscu 255, unutrasnjost je 0
    border = np.zeros_like(imageGRAY)
    border[0, :] = 255
    border[-1, :] = 255
    border[:, 0] = 255
    border[:, -1] = 255
    # show2images(imageMASK, border, "Maska", "Border")

    #Sad imamo samo one pixele iz originalne slike koji dodiruju ivicu:
    borderPartsOfImage = cv.bitwise_and(imageMASK, border)
    #show2images(imageMASK, borderPartsOfImage, "Maska", "Pixeli slike koji dodiruju obod")

    #Rekonstruisemo te pixele da ih vratimo na "originalne objekte" bez onih koji ne dodiruju ivice:
    justBorderParts = morphological_reconstruction(borderPartsOfImage, imageMASK)
    # show2images(imageMASK, justBorderParts, "Maska", "Delovi slike koji dodiruju obod")

    #Rezultat invertujemo i and-ujemo sa maskom tako da prakticno uklonimo te objekte koji dodiruju ivicu:
    justBorderPartsINVERTED = cv.bitwise_not(justBorderParts)
    imageWithoutBorderParts = cv.bitwise_and(imageMASK, justBorderPartsINVERTED)
    show3images(imageMASK, justBorderPartsINVERTED ,imageWithoutBorderParts, "Maska", "Invertovani delovi do oboda" ,"Slika bez delova koji dodiruju obod")
