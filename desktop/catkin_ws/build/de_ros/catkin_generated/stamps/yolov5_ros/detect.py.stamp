#!/usr/bin/env python3

import rospy
import cv2
import torch
import torch.backends.cudnn as cudnn
import numpy as np
from cv_bridge import CvBridge
from pathlib import Path
import os
import sys
from rostopic import get_topic_type

from sensor_msgs.msg import Image, CompressedImage
from detection_msgs.msg import BoundingBox, BoundingBoxes


# 파이썬 시스템 경로에 yolov5 서브모듈 추가하여 상대경로로 변환
FILE = Path(__file__).resolve()  # 현재 스크립트 파일의 절대 경로를 가져옴
ROOT = FILE.parents[0] / "yolov5"  # 스크립트 파일의 부모 디렉토리에서 yolov5 서브 디렉토리를 가져옴
if str(ROOT) not in sys.path:  # yolov5 서브 디렉토리가 sys.path 경로에 없다면
    sys.path.append(str(ROOT))  # yolov5 서브 디렉토리를 시스템 경로 sys.path에 추가
ROOT = Path(os.path.relpath(ROOT, Path.cwd()))  

# yolov5 서브모듈에서 임포트
from models.common import DetectMultiBackend
from utils.general import (
    check_img_size,
    check_requirements,
    non_max_suppression,
    scale_coords
)
from utils.plots import Annotator, colors
from utils.torch_utils import select_device
from utils.augmentations import letterbox


@torch.no_grad()
class Yolov5Detector:
    def __init__(self):
        self.conf_thres = rospy.get_param("~confidence_threshold")  # 객체의 신뢰도를 ros 파라미터에서 가져와 설정
        self.iou_thres = rospy.get_param("~iou_threshold")  # 예측된 객체의 바운딩 박스와 실제 객체의 바운딩 박스 간의 겹치는 영역의 임계값을 ros 파라미터에서 가져와 설정
        self.agnostic_nms = rospy.get_param("~agnostic_nms")  # agnostic_nms를 사용할 지 여부를 ros 파라미터에서 가져와 설정
        self.max_det = rospy.get_param("~max_detections")  # 한 프레임에서 최대 감지 개수를 ros 파라미터에서 가져와 설정
        self.classes = rospy.get_param("~classes", None)  # 클래스 정보를 ros 파라미터에서 가져와 설정
        self.line_thickness = rospy.get_param("~bounding_thickness")  # 바운딩 박스의 두께를 ros 파라미터에서 가져와 설정
        self.view_image = rospy.get_param("~view_image")  # 검출된 객체가 표시된 이미지를 보여줄지 여부를 ros 파라미터에서 가져와 설정
        weights = rospy.get_param("~weights")  # weight 파일을 ros 파라미터에서 가져와 yolov5 모델 초기화
        self.device = select_device(str(rospy.get_param("~device","")))  # 실행시킬 디바이스를 ros 파라미터에서 가져와 설정
        # yolov5 모델에 사용할 가중치와 디바이스, DNN 사용 여부 등을 ros 파라미터에서 가져와 yolov5 모델 초기화
        self.model = DetectMultiBackend(weights, device=self.device, dnn=rospy.get_param("~dnn"), data=rospy.get_param("~data")) 
        # yolov5 모델의 속성을 가져와 클래스 변수에 할당
        self.stride, self.names, self.pt, self.jit, self.onnx, self.engine = (  
            self.model.stride,  # 입력 이미지와 출력간의 크기 비율
            self.model.names,  # 객체의 클래스 이름 리스트
            self.model.pt,  # 모델이 파이토치로 작성되었는지 여부
            self.model.jit,  # 모델이 토치스크립트로 컴파일되었는지 여부
            self.model.onnx,  # 모델이 ONNX 형식으로 변환되었는지 여부
            self.model.engine,  # 모델의 엔진 종류
        )

        # 추론을 수행할 이미지 크기 설정 
        self.img_size = [rospy.get_param("width", 640), rospy.get_param("height",640)]  # 이미지의 너비와 높이를 ros 파라미터에서 가져와 리스트 형태로 설정
        self.img_size = check_img_size(self.img_size, s=self.stride)  # 가져온 이미지 크기를 yolov5 모델의 스트라이드값과 함께 유효성 검사를 진행하여 적절한 크기로 조정

        # 정밀도 사용 방법
        self.half = rospy.get_param("~half", False)  # 기본값으로 FP32 단일 정밀도 사용
        # CUDA 환경에서만 FP16 사용
        self.half &= (
            self.pt or self.jit or self.onnx or self.engine
        ) and self.device.type != "cpu"  
        if self.pt or self.jit:
            self.model.model.half() if self.half else self.model.model.float()
        bs = 1  # batch_size를 1로 설정
        cudnn.benchmark = True  # cudnn을 사용하여 일정한 이미지 크기를 추론
        self.model.warmup()  # 모델 워밍업      
        
        # ros 토픽에서 이미지를 구독하기 위한 초기화 과정
        # ros 파라미터에서 이미지 토픽을 가져와 토픽의 유형과 이름을 결정
        input_image_type, input_image_topic, _ = get_topic_type(rospy.get_param("~input_image_topic"), blocking = True)  
        # 이미지 유형이 sensor_msgs/CompressedImage 인지 여부를 확인하고, 그 결과를 self.compressed_input에 저장
        self.compressed_input = input_image_type == "sensor_msgs/CompressedImage"

        # 압축되어 있는 이미지를 구독할 때 
        if self.compressed_input:  
            self.image_sub = rospy.Subscriber(
                input_image_topic, CompressedImage, self.callback, queue_size=1
            )
        # 압축되지 않은 이미지를 구독할 때
        else:
            self.image_sub = rospy.Subscriber(
                input_image_topic, Image, self.callback, queue_size=1
            )

        # 객체 감지 결과를 발행할 토픽의 이름을 ros 파라미터에서 가져와 바운딩박스를 발행, 발행 큐의 최대 길이를 10으로 설정
        self.pred_pub = rospy.Publisher(
            rospy.get_param("~output_topic"), BoundingBoxes, queue_size=10
        )
        # ros 파라미터로 이미지 발행 여부를 가져와 True일 때 Image 메시지를 발행, 이미지를 발행할 토픽의 이름을 ros 파라미터에서 가져옴
        self.publish_image = rospy.get_param("~publish_image")
        if self.publish_image:
            self.image_pub = rospy.Publisher(
                rospy.get_param("~output_image_topic"), Image, queue_size=10
            )
        
        # CV_Bridge 초기화
        self.bridge = CvBridge()
        
    # 이미지 데이터를 받아서 객체 감지를 수행한 후 바운딩 박스를 메시지로 생성하여 발행    
    def callback(self, data):
        """adapted from yolov5/detect.py"""
        if self.compressed_input:  # 받아온 이미지가 압축되어 있다면
            im = self.bridge.compressed_imgmsg_to_cv2(data, desired_encoding="bgr8")  # 압축된 이미지 메시지를 cv2 이미지로 변환하여 'im' 변수에 저장
        else:  # 받아온 이미지가 압축되어 있지 않다면 
            im = self.bridge.imgmsg_to_cv2(data, desired_encoding="bgr8")  # 압축되지 않은 이미지 메시지를 cv2 이미지로 변환하여 'im' 변수에 저장
        
        im, im0 = self.preprocess(im)  # 받아온 이미지 'im'를 전처리한 후 'im', 'im0' 변수에 저장 -> preprocess(): 이미지를 전처리하는 함수
        im = torch.from_numpy(im).to(self.device)  # 넘파이 배열 형태의 이미지를 파이터치 텐서로 변환하고, 설정된 디바이스로 이동
        im = im.half() if self.half else im.float()  # 이미지 데이터를 float16으로 변환하거나 그대로 유지
        im /= 255  # 이미지 데이터 정규화
        if len(im.shape) == 3:  # 만약 이미지가 3차원인 경우에 배치 차원 추가
            im = im[None]

        pred = self.model(im, augment=False, visualize=False)  # 전처리가 완료된 이미지를 모델에 전달하여 객체 감지 실행, 이 때 시각화를 사용하지 않음
        # 객체 감지 결과에서 가장 확률이 높은 바운딩 박스만 남김
        pred = non_max_suppression( 
            pred, self.conf_thres, self.iou_thres, self.classes, self.agnostic_nms, max_det=self.max_det
        )

        # 객체 감지 결과를 바운딩 박스 형태로 구성
        det = pred[0].cpu().numpy()

        bounding_boxes = BoundingBoxes()  # 바운딩 박스 초기화
        bounding_boxes.header = data.header  # 바운딩 박스 메시지의 헤더 설정
        bounding_boxes.image_header = data.header  # 바운딩 박스 메시지의 이미지 헤더 설정
        
        annotator = Annotator(im0, line_width=self.line_thickness, example=str(self.names))  # 이미지에 바운딩 박스를 추가하기 위한 Annotator 객체 초기화
        if len(det):
            # 객체 감지 결과의 좌표를 입력 이미지와 동일한 크기로 변환
            det[:, :4] = scale_coords(im.shape[2:], det[:, :4], im0.shape).round()

            # 바운딩 박스 메시지 구성
            for *xyxy, conf, cls in reversed(det):
                bounding_box = BoundingBox()
                c = int(cls)
                # 바운딩 박스 메시지 채우기
                bounding_box.Class = self.names[c]
                bounding_box.probability = conf 
                bounding_box.xmin = int(xyxy[0])
                bounding_box.ymin = int(xyxy[1])
                bounding_box.xmax = int(xyxy[2])
                bounding_box.ymax = int(xyxy[3])

                bounding_boxes.bounding_boxes.append(bounding_box)

                # 이미지 주석 처리 
                if self.publish_image or self.view_image:  # 바운딩 박스를 이미지에 추가
                      # 정수형 클래스
                    label = f"{self.names[c]} {conf:.2f}"
                    annotator.box_label(xyxy, label, color=colors(c, True))       

                
                ### 객체 감지 메시지 채우기 

            # 결과 스트리밍
            im0 = annotator.result()

        # 예측 결과 발행
        self.pred_pub.publish(bounding_boxes)

        # 이미지 발행 및 시각화 
        if self.view_image:
            cv2.imshow(str(0), im0)
            cv2.waitKey(1)  
        if self.publish_image:
            self.image_pub.publish(self.bridge.cv2_to_imgmsg(im0, "bgr8"))
        

    def preprocess(self, img):
        """
        yolov5/utils/datasets.py LoadStreams 클래스에서 적용된 함수
        """
        img0 = img.copy()
        img = np.array([letterbox(img, self.img_size, stride=self.stride, auto=self.pt)[0]])
        img = img[..., ::-1].transpose((0, 3, 1, 2))  # BGR을 RGB로, BHWC를 BCHW로 변환
        img = np.ascontiguousarray(img)

        return img, img0 


if __name__ == "__main__":

    check_requirements(exclude=("tensorboard", "thop"))
    
    # ros 노드 초기화
    rospy.init_node("yolov5", anonymous=True)
    detector = Yolov5Detector()
    
    # 무한 루프를 돌며 메시지 수신 대기 
    rospy.spin()
