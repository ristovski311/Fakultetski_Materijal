import imutils
import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt
import argparse

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

# Sliding window
def pyramid(image, scale=1.5, minSize=(30, 30)):
	yield image
	while True:
		w = int(image.shape[1] / scale)
		image = imutils.resize(image, width=w)
		if image.shape[0] < minSize[1] or image.shape[1] < minSize[0]:
			break
		yield image

# Sliding window funkcija
def sliding_window(image, stepSize, windowSize):
	for y in range(0, image.shape[0], stepSize):
		for x in range(0, image.shape[1], stepSize):
			yield (x, y, image[y:y + windowSize[1], x:x + windowSize[0]])

# Argumenti - postavljanje GoogLeNet-a

ap = argparse.ArgumentParser()
ap.add_argument("-p", "--prototxt", required=True, 	help="path to Caffe 'deploy' prototxt file")
ap.add_argument("-m", "--model", required=True,	help="path to Caffe pre-trained model")
ap.add_argument("-l", "--labels", required=True, help="path to ImageNet labels (i.e., syn-sets)")
args = vars(ap.parse_args())

rows = open(args["labels"]).read().strip().split("\n")
classes = [r[r.find(" ") + 1:].split(",")[0] for r in rows]

net = cv.dnn.readNetFromCaffe(args["prototxt"], args["model"])


# Funkcija za croppovanje slike
def extract_rect(image):
    # Canny detekcija
    gray = cv.cvtColor(image, cv.COLOR_RGB2GRAY)
    blur = cv.GaussianBlur(gray, (5, 5), 0)
    edges = cv.Canny(blur, 50, 200)

    # plt.imshow(edges, cmap="gray")
    # plt.title("Canny")
    # plt.show()

    # Hough transformacija
    lines = cv.HoughLinesP(
        edges,
        rho=1,
        theta=np.pi / 180,
        threshold=100,
        minLineLength=200,
        maxLineGap=10
    )

    if lines is None:
        return None

    # Razdvajanje na horizontalne i vertikalne
    horizontal_lines = []
    vertical_lines = []

    for line in lines:
        x1, y1, x2, y2 = line[0]
        dx = abs(x2 - x1)
        dy = abs(y2 - y1)

        # Horizontalne
        if dx > dy and dx > 200:
            y_avg = (y1 + y2) // 2
            horizontal_lines.append((y_avg, min(x1, x2), max(x1, x2), dx))

        # Vertikalne
        elif dy > dx and dy > 200:
            x_avg = (x1 + x2) // 2
            vertical_lines.append((x_avg, min(y1, y2), max(y1, y2), dy))

    # Sortiranje po duzini linija
    horizontal_lines.sort(key=lambda a: a[3], reverse=True)
    vertical_lines.sort(key=lambda a: a[3], reverse=True)

    if len(horizontal_lines) < 2 or len(vertical_lines) < 2:
        print("Nedovoljno linija detektovano!")
        return None

    # Horizontalne
    h_sorted_by_y = sorted(horizontal_lines[:4], key=lambda a: a[0])
    top_line = h_sorted_by_y[0]  # najmanje y (gore)
    bottom_line = h_sorted_by_y[-1]  # najvece y (dole)

    # Vertikalne
    v_sorted_by_x = sorted(vertical_lines[:4], key=lambda a: a[0])
    left_line = v_sorted_by_x[0]  # najmanje x (levo)
    right_line = v_sorted_by_x[-1]  # najvece x (desno)

    # Koordinate linija
    y_top = top_line[0]
    y_bottom = bottom_line[0]
    x_left = left_line[0]
    x_right = right_line[0]

    # Prikaz
    linije = image.copy()
    cv.line(linije, (0, y_top), (image.shape[1], y_top), (255, 0, 0), 2)
    cv.line(linije, (0, y_bottom), (image.shape[1], y_bottom), (255, 0, 0), 2)
    cv.line(linije, (x_left, 0), (x_left, image.shape[0]), (0, 255, 0), 2)
    cv.line(linije, (x_right, 0), (x_right, image.shape[0]), (0, 255, 0), 2)

    # Preseci linija - temena
    vertices = [
        (x_left, y_top),
        (x_right, y_top),
        (x_right, y_bottom),
        (x_left, y_bottom)
    ]

    for vertex in vertices:
        cv.circle(linije, vertex, 10, (0, 0, 255), -1)

    plt.imshow(linije)
    plt.title("Pravougaonik")
    plt.show()

    # Croppovanje
    cropped = image[y_top:y_bottom, x_left:x_right]

    plt.imshow(cropped)
    plt.title("Extracted rectangle")
    plt.show()

    return cropped

# GoogLe net klasifikacija
def find_cats_and_dogs(image):
    WINDOW_X = 180
    WINDOW_Y = 180
    WINDOW_STEP = 180
    RESULT_THRESHOLD = 0.7
    for resized_image in pyramid(image, scale=2):
        for (x, y, window) in sliding_window(resized_image, WINDOW_STEP, (WINDOW_X, WINDOW_Y)):
            # Ignorisemo prozor koji nije 180x180
            if window.shape[0] != WINDOW_X or window.shape[1] != WINDOW_Y:
                continue

            blob = cv.dnn.blobFromImage(
                window,
                scalefactor=1.0,
                size=(224, 224),
                mean=(104, 117, 123)
            )

            net.setInput(blob)
            predictions = net.forward()

            idx = np.argmax(predictions[0])
            confidence = predictions[0][idx]

            if confidence > RESULT_THRESHOLD:
                label = classes[idx]

                scale_x = cats_and_dogs.shape[1] / resized_image.shape[1]
                scale_y = cats_and_dogs.shape[0] / resized_image.shape[0]

                orig_x = int(x * scale_x)
                orig_y = int(y * scale_y)
                orig_w = int(WINDOW_X * scale_x)
                orig_h = int(WINDOW_Y * scale_y)

                is_dog = "dog" in label.lower()
                color = (255,255,0) if is_dog else (255, 0, 0)
                text = "DOG" if is_dog else "CAT"

                cv.rectangle(
                    image,
                    (orig_x + 3, orig_y + 3),
                    (orig_x + orig_w - 3, orig_y + orig_h - 3),
                    color,
                    2
                )

                cv.putText(
                    image,
                    text,
                    (orig_x + 5, orig_y + 30),
                    cv.FONT_HERSHEY_DUPLEX,
                    0.8,
                    color,
                    2
                )
    return image

#MAIN
if __name__ == '__main__':

    original_image = loadImage("image.png")
    # CROP PREKO CANNY I HOUGH:
    cropped_image = extract_rect(original_image)
    cats_and_dogs = cropped_image.copy()

    result = find_cats_and_dogs(cats_and_dogs)

    plt.imshow(cats_and_dogs, cmap='gray')
    plt.title("Cats and dogs!")
    plt.show()

    cats_and_dogs = cv.cvtColor(cats_and_dogs, cv.COLOR_RGB2BGR)
    cv.imwrite("output.jpg", cats_and_dogs)