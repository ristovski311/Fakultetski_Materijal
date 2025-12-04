import cv2
import numpy as np
import matplotlib.pyplot as plt

def toFrequencyDomain(image):
    image_f = np.fft.fft2(image)
    image_f = np.fft.fftshift(image_f)
    return image_f

def toSpatialDomain(image_amplitude, image_phases):
    image_f = image_phases * np.exp(image_amplitude)
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
    image_f_amplitude_log[image_center[0] - 3, image_center[1] - 8] = 6
    image_f_amplitude_log[image_center[0] + 3, image_center[1] + 8] = 6

    filtered_image = toSpatialDomain(image_f_amplitude_log, image_f_phase)
    return filtered_image

if __name__ == '__main__':
    print("Laboratorijska vezba broj 1\nRistovski Nikola\nBroj indeksa: 19347\nZadatak 2")
    image = cv2.imread("slika_2.png")
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    plt.imshow(image, "gray")
    plt.show()

    filtered_image = simpleNoiseRemoval(image)
    plt.imshow(filtered_image, "gray")
    plt.show()
