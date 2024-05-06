;; Auto-generated. Do not edit!


(when (boundp 'echo_tutorial::EchoDistance)
  (if (not (find-package "ECHO_TUTORIAL"))
    (make-package "ECHO_TUTORIAL"))
  (shadow 'EchoDistance (find-package "ECHO_TUTORIAL")))
(unless (find-package "ECHO_TUTORIAL::ECHODISTANCE")
  (make-package "ECHO_TUTORIAL::ECHODISTANCE"))

(in-package "ROS")
;;//! \htmlinclude EchoDistance.msg.html


(defclass echo_tutorial::EchoDistance
  :super ros::object
  :slots (_Stamp _Distance ))

(defmethod echo_tutorial::EchoDistance
  (:init
   (&key
    ((:Stamp __Stamp) (instance ros::time :init))
    ((:Distance __Distance) 0.0)
    )
   (send-super :init)
   (setq _Stamp __Stamp)
   (setq _Distance (float __Distance))
   self)
  (:Stamp
   (&optional __Stamp)
   (if __Stamp (setq _Stamp __Stamp)) _Stamp)
  (:Distance
   (&optional __Distance)
   (if __Distance (setq _Distance __Distance)) _Distance)
  (:serialization-length
   ()
   (+
    ;; time _Stamp
    8
    ;; float64 _Distance
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _Stamp
       (write-long (send _Stamp :sec) s) (write-long (send _Stamp :nsec) s)
     ;; float64 _Distance
       (sys::poke _Distance (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _Stamp
     (send _Stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _Stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _Distance
     (setq _Distance (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get echo_tutorial::EchoDistance :md5sum-) "d7755fc5d2735bcfbf5a864c13aab9ab")
(setf (get echo_tutorial::EchoDistance :datatype-) "echo_tutorial/EchoDistance")
(setf (get echo_tutorial::EchoDistance :definition-)
      "time Stamp
float64 Distance

")



(provide :echo_tutorial/EchoDistance "d7755fc5d2735bcfbf5a864c13aab9ab")


