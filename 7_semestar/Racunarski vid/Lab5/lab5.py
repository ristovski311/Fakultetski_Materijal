import cv2 as cv
import numpy as np
from pathlib import Path
import os

# Posluzio sam se sledecim linkom:
# https://github.com/abhishekpadalkar/camera_calibration/blob/master/data_generation.py

# Kalibracija kamere:
def calibrate():
    aruco_dict = cv.aruco.getPredefinedDictionary(cv.aruco.DICT_6X6_50)
    markersX = 5
    markersY = 7
    markerLength = 0.0466
    markerSeparation = 0.0092

    source_images_path = Path("Aruco")

    board = cv.aruco.GridBoard_create(
        markersX,
        markersY,
        markerLength,
        markerSeparation,
        aruco_dict
    )

    arucoParams = cv.aruco.DetectorParameters_create()

    # Ucitamo filenames slika koje koristimo za kalibraciju
    img_list = []
    calib_fnms = source_images_path.glob('calib_image*.jpg')
    fns = list(calib_fnms)

    # Ucitavamo zapravo same slike
    for idx, fn in enumerate(fns):
        img = cv.imread(str(fn))
        img_list.append(img)

    # Nalazenje uglova i id-eva markera
    counter, all_corners, all_ids = [], [], []
    for idx, im in enumerate(img_list):
        print(f"Calibrating on {idx} {fns[idx]}")
        img_gray = cv.cvtColor(im, cv.COLOR_RGB2GRAY)

        corners, ids, _ = cv.aruco.detectMarkers(img_gray, aruco_dict, parameters=arucoParams)

        # Dodajemo markere samo ako su pronadjeni
        if ids is not None and len(ids) > 0:
            for corner in corners:
                all_corners.append(corner)
            for id in ids:
                all_ids.append(id)
            counter.append(len(ids))
        else:
            print(f"No markers found in image {fns[idx]}")

    # Provera da li imamo bar neki marker
    if len(all_corners) == 0:
        print("No markers detected in any image!")
        return None, None, None

    # Konvertujemo all_ids u numpy array
    all_ids = np.array(all_ids)
    flat_ids = all_ids.flatten()
    print('Found {} unique markers'.format(len(np.unique(flat_ids))))

    # Kalibracija
    counter = np.array(counter)
    # Koristimo poslednju sliku za dimenzije
    img_gray = cv.cvtColor(img_list[-1], cv.COLOR_RGB2GRAY)
    ret, mtx, dist, rvecs, tvecs = cv.aruco.calibrateCameraAruco(
        all_corners, all_ids, counter, board, img_gray.shape[::-1], None, None)
    print("Camera matrix is \n", mtx)

    return mtx, dist, fns, board

# Undistorzija:
def undistort_images(images, cameraMatrix, distCoeffs):
    out_dir = "Calibrated"
    os.makedirs(out_dir, exist_ok=True)

    for fn in images:
        img = cv.imread(str(fn))
        h, w = img.shape[:2]

        newCameraMatrix, roi = cv.getOptimalNewCameraMatrix(
            cameraMatrix,
            distCoeffs,
            (w, h),
            alpha=1,
            newImgSize=(w, h)
        )

        undistorted = cv.undistort(
            img,
            cameraMatrix,
            distCoeffs,
            None,
            newCameraMatrix
        )

        # Croppujemo samo region of interest na slici (bez crnih delova)
        x, y, w, h = roi
        undistorted = undistorted[y:y+h, x:x+w]

        out_path = os.path.join(out_dir, fn.name)
        cv.imwrite(out_path, undistorted)

# Detekcija markera i odredjivanje poze:
def detect_and_estimate_pose(video_path, cameraMatrix, distCoeffs, board):
    aruco_dict = cv.aruco.getPredefinedDictionary(cv.aruco.DICT_6X6_1000)
    arucoParams = cv.aruco.DetectorParameters_create()

    # Otvaranje video fajla
    cap = cv.VideoCapture(video_path)

    if not cap.isOpened():
        print(f"Cannot open video file {video_path}")
        return

    print("Press 'q' to quit")
    while True:
        ret, frame = cap.read()

        if not ret:
            print("End of video or cannot read frame")
            break

        # Konvertuj u grayscale za detekciju
        gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

        # Detektuj markere
        corners, ids, _ = cv.aruco.detectMarkers(
            gray, aruco_dict, parameters=arucoParams
        )

        # Ako su markeri detektovani
        if ids is not None and len(ids) > 0:
            # Nacrtaj detektovane markere
            cv.aruco.drawDetectedMarkers(frame, corners, ids)

            # Estimiraj pozu board-a
            retval, rvec, tvec = cv.aruco.estimatePoseBoard(
                corners, ids, board, cameraMatrix, distCoeffs, None, None
            )

            if retval > 0:
                # Nacrtaj 3D ose na board-u
                cv.aruco.drawAxis(frame, cameraMatrix, distCoeffs, rvec, tvec, 0.046)

        else:
            cv.putText(frame, "No markers detected",
                       (10, 30), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

        # Prikaži rezultat
        cv.imshow('ArUco Marker Detection and Pose Estimation', frame)

        # Kontrole tastature
        key = cv.waitKey(30)
        if key == ord('q'):
            break

    cap.release()
    cv.destroyAllWindows()

# MAIN
if __name__ == '__main__':
    # Kalibracija:
    matrix, dist, images, board = calibrate()
    undistort_images(images, matrix, dist)

    #Video u kome trazimo markere i pozu
    video_path = "Aruco/Aruco_board.mp4"

    # Detekcija i estimacija poze board-a
    detect_and_estimate_pose(video_path, matrix, dist, board)