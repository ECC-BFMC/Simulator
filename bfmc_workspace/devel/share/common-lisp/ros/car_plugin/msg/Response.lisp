; Auto-generated. Do not edit!


(cl:in-package car_plugin-msg)


;//! \htmlinclude Response.msg.html

(cl:defclass <Response> (roslisp-msg-protocol:ros-message)
  ((key
    :reader key
    :initarg :key
    :type car_plugin-msg:Key
    :initform (cl:make-instance 'car_plugin-msg:Key))
   (response
    :reader response
    :initarg :response
    :type cl:string
    :initform ""))
)

(cl:defclass Response (<Response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car_plugin-msg:<Response> is deprecated: use car_plugin-msg:Response instead.")))

(cl:ensure-generic-function 'key-val :lambda-list '(m))
(cl:defmethod key-val ((m <Response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_plugin-msg:key-val is deprecated.  Use car_plugin-msg:key instead.")
  (key m))

(cl:ensure-generic-function 'response-val :lambda-list '(m))
(cl:defmethod response-val ((m <Response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_plugin-msg:response-val is deprecated.  Use car_plugin-msg:response instead.")
  (response m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Response>) ostream)
  "Serializes a message object of type '<Response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'key) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'response))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'response))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Response>) istream)
  "Deserializes a message object of type '<Response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'key) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'response) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'response) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Response>)))
  "Returns string type for a message object of type '<Response>"
  "car_plugin/Response")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Response)))
  "Returns string type for a message object of type 'Response"
  "car_plugin/Response")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Response>)))
  "Returns md5sum for a message object of type '<Response>"
  "62068c192be1c92f944918b622366c47")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Response)))
  "Returns md5sum for a message object of type 'Response"
  "62068c192be1c92f944918b622366c47")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Response>)))
  "Returns full string definition for message of type '<Response>"
  (cl:format cl:nil "Key key~%string response~%================================================================================~%MSG: car_plugin/Key~%# Message constabt field to describe the key values~%uint8 UNKNOWN=0~%uint8 MOVE=1~%uint8 BRAKE=2~%# Message field ~%uint8 v~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Response)))
  "Returns full string definition for message of type 'Response"
  (cl:format cl:nil "Key key~%string response~%================================================================================~%MSG: car_plugin/Key~%# Message constabt field to describe the key values~%uint8 UNKNOWN=0~%uint8 MOVE=1~%uint8 BRAKE=2~%# Message field ~%uint8 v~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'key))
     4 (cl:length (cl:slot-value msg 'response))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Response>))
  "Converts a ROS message object to a list"
  (cl:list 'Response
    (cl:cons ':key (key msg))
    (cl:cons ':response (response msg))
))
