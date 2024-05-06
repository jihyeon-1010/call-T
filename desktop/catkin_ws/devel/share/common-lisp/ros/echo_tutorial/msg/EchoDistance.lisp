; Auto-generated. Do not edit!


(cl:in-package echo_tutorial-msg)


;//! \htmlinclude EchoDistance.msg.html

(cl:defclass <EchoDistance> (roslisp-msg-protocol:ros-message)
  ((Stamp
    :reader Stamp
    :initarg :Stamp
    :type cl:real
    :initform 0)
   (Distance
    :reader Distance
    :initarg :Distance
    :type cl:float
    :initform 0.0))
)

(cl:defclass EchoDistance (<EchoDistance>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <EchoDistance>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'EchoDistance)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name echo_tutorial-msg:<EchoDistance> is deprecated: use echo_tutorial-msg:EchoDistance instead.")))

(cl:ensure-generic-function 'Stamp-val :lambda-list '(m))
(cl:defmethod Stamp-val ((m <EchoDistance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader echo_tutorial-msg:Stamp-val is deprecated.  Use echo_tutorial-msg:Stamp instead.")
  (Stamp m))

(cl:ensure-generic-function 'Distance-val :lambda-list '(m))
(cl:defmethod Distance-val ((m <EchoDistance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader echo_tutorial-msg:Distance-val is deprecated.  Use echo_tutorial-msg:Distance instead.")
  (Distance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <EchoDistance>) ostream)
  "Serializes a message object of type '<EchoDistance>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'Stamp)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'Stamp) (cl:floor (cl:slot-value msg 'Stamp)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'Distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <EchoDistance>) istream)
  "Deserializes a message object of type '<EchoDistance>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Stamp) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Distance) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<EchoDistance>)))
  "Returns string type for a message object of type '<EchoDistance>"
  "echo_tutorial/EchoDistance")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'EchoDistance)))
  "Returns string type for a message object of type 'EchoDistance"
  "echo_tutorial/EchoDistance")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<EchoDistance>)))
  "Returns md5sum for a message object of type '<EchoDistance>"
  "d7755fc5d2735bcfbf5a864c13aab9ab")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'EchoDistance)))
  "Returns md5sum for a message object of type 'EchoDistance"
  "d7755fc5d2735bcfbf5a864c13aab9ab")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<EchoDistance>)))
  "Returns full string definition for message of type '<EchoDistance>"
  (cl:format cl:nil "time Stamp~%float64 Distance~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'EchoDistance)))
  "Returns full string definition for message of type 'EchoDistance"
  (cl:format cl:nil "time Stamp~%float64 Distance~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <EchoDistance>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <EchoDistance>))
  "Converts a ROS message object to a list"
  (cl:list 'EchoDistance
    (cl:cons ':Stamp (Stamp msg))
    (cl:cons ':Distance (Distance msg))
))
