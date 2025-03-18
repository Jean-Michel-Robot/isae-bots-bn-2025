""" Classes for detecting Aruco tags on images and normalizing images with Aruco tags """

import cv2
import numpy as np
from loadImage import loadImage

class ArucoDetector:
    _dictionary =  cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_4X4_50)
    _params = cv2.aruco.DetectorParameters()
   
    def __init__(self):
        self._detector = cv2.aruco.ArucoDetector(ArucoDetector._dictionary, ArucoDetector._params)
    
    def detect(self, image):
        tags = {}
        corners, ids, _ = self._detector.detectMarkers(image)
        for box, tag in zip(corners, ids):
            # topLeft, topRight, bottomRight, bottomLeft
            tags[tag.item()] = box.squeeze()

        return ArucoTags(image, tags)

    def __call__(self, image):
        return self.detect(image)
    
class ArucoTags:

    def __init__(self, image, tags):
        self._image = image
        self._tags = tags
    
    def __getitem__(self, index):
        return self._tags[index]
    
    def __iter__(self):
        return iter(self._tags)
    
    def __contains__(self, tag):
        return tag in self._tags
    
    def draw(self):
        image = self._image.copy()
        for tag in self:            
            corners = self[tag].reshape((4, 2)).astype(int)
            (topLeft, topRight, bottomRight, bottomLeft) = corners

            cv2.line(image, topLeft, topRight, (0, 255, 0), 2)
            cv2.line(image, topRight, bottomRight, (0, 255, 0), 2)
            cv2.line(image, bottomRight, bottomLeft, (0, 255, 0), 2)
            cv2.line(image, bottomLeft, topLeft, (0, 255, 0), 2)

            cv2.putText(image, str(tag),
                (topLeft[0], topLeft[1] - 15), cv2.FONT_HERSHEY_SIMPLEX,
                0.5, (0, 255, 0), 2)
        
        return image

class ImageNormalize:

    def __init__(self, reference, preprocess=None):
        if preprocess is None:
            preprocess = loadImage
        
        self._preprocess = preprocess
        self._detector = ArucoDetector()

        self._calibrated = False
               
        self._reference = self._detector(loadImage(reference))
        self._shape = self._reference._image.shape
    
    def calibrate(self, calibration, draw=True):
        calibration = self._preprocess(calibration)
        calibration = self._detector(calibration)        
        reference = self._reference
     
        src_pts = []
        dst_pts = []

        for tag in calibration:
            if tag in reference:
                src_pts.extend(reference[tag])
                dst_pts.extend(calibration[tag])

        self._H, _ = cv2.findHomography(np.array(src_pts), np.array(dst_pts), cv2.RANSAC)
        self._calibrated = True

        if draw:
            return calibration.draw()

    def __call__(self, image):        
        return self.normalize(image)
    
    def normalize(self, image):        
        if not self._calibrated:
            self.calibrate(image)
            self._calibrated = True

        image = self._preprocess(image)  
        size = self._shape[1::-1]
        output = np.uint8(255 * np.ones((size[0], size[1], 3)))       
        output = cv2.warpPerspective(image, self._H, size, output, flags=cv2.INTER_LINEAR+cv2.WARP_INVERSE_MAP, borderMode=cv2.BORDER_TRANSPARENT)
        return output