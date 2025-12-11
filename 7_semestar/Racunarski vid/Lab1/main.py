import cv2
import numpy as np
import matplotlib.pyplot as plt

def toFrequencyDomain(image):
    image_f = np.fft.fft2(image)
    image_f = np.fft.fftshift(image_f)
    return image_f

def toSpatialDomain(image_amplitude, image_phases):
    image_f = image_phases * image_amplitude
    filtered_image = np.abs(np.fft.ifft2(image_f))
    return filtered_image

def simpleNoiseRemoval(image):
    height = image.shape[0]
    width = image.shape[1]
    image_center = [height//2, width//2]

    image_f = toFrequencyDomain(image)
    image_f_amplitude = np.abs(image_f)
    image_f_phase = image_f / image_f_amplitude

    image_f_amplitude_log = np.log(image_f_amplitude)
    image_f_amplitude_log_before = image_f_amplitude_log.copy()

    # Kriticne tacke visokih intenziteta amplituda vracam na prosek okolnih tacaka i to uklanja sum

    image_f_amplitude_log[image_center[0] - 25, image_center[1] - 5] = 11
    image_f_amplitude_log[image_center[0] + 25, image_center[1] + 5] = 11

    image_f_amplitude_log[image_center[0] - 10, image_center[1] + 5] = 11
    image_f_amplitude_log[image_center[0] + 10, image_center[1] - 5] = 11

    #Prikaz before/after

    plt.figure(figsize=(10, 5))

    plt.subplot(1, 2, 1)
    plt.imshow(image_f_amplitude_log_before)
    plt.title("Pre obrade")

    plt.subplot(1, 2, 2)
    plt.imshow(image_f_amplitude_log)
    plt.title("Nakon obrade")

    plt.show()

    filtered_image = toSpatialDomain(np.exp(image_f_amplitude_log), image_f_phase)
    return filtered_image

if __name__ == '__main__':
    print("Laboratorijska vezba broj 1\nRistovski Nikola\nBroj indeksa: 19347\nZadatak 2")
    image = cv2.imread("slika_2.png")
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    plt.imshow(image, "gray")
    plt.title("Inicijalna slika")
    plt.show()

    filtered_image = simpleNoiseRemoval(image)

    cv2.imwrite("slika_2_filtered.png", filtered_image)

    plt.figure(figsize=(10, 5))

    plt.subplot(1, 2, 1)
    plt.imshow(image, cmap='gray')
    plt.title("Pre obrade")

    plt.subplot(1, 2, 2)
    plt.imshow(filtered_image, cmap='gray')
    plt.title("Nakon obrade")

    plt.show()
