import cv2
import numpy as np
import pyzbar.pyzbar as pyzbar

cap = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_PLAIN


while (cap.isOpened()):
    # Capture frame-by-frame
    ret, frame = cap.read()
    # Our operations on the frame come here
    im = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    decodedObjects = pyzbar.decode(frame)
    for decodedObject in decodedObjects:
        points = decodedObject.polygon

        # If the points do not form a quad, find convex hull
        if len(points) > 4:
            hull = cv2.convexHull(np.array([point for point in points], dtype=np.float32))
            hull = list(map(tuple, np.squeeze(hull)))
        else:
            hull = points;

        # Number of points in the convex hull
        n = len(hull)
        # Draw the convext hull

        for j in range(0, n):
            cv2.line(frame, hull[j], hull[(j + 1) % n], (0, 0, 255), 3)

        x = decodedObject.rect.left
        y = decodedObject.rect.top - 5

        # print(x, y)

        # print('Type : ', decodedObject.type)
        print('Data : ', decodedObject.data)

        barCode = str(decodedObject.data)
        cv2.putText(frame, barCode, (x, y), font, 2, (0, 0, 255), 3)
       

    # Display the resulting frame
    cv2.imshow('frame', frame)
    key = cv2.waitKey(1)
    if key & 0xFF == ord('q'):
        break
    elif key & 0xFF == ord('s'):  # wait for 's' key to save
        cv2.imwrite('Capture.png', frame)

    # When everything done, release the capture
cap.release()
cv2.destroyAllWindows()