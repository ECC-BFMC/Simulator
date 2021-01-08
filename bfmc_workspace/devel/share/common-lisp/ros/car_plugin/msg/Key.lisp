; Auto-generated. Do not edit!


(cl:in-package car_plugin-msg)


;//! \htmlinclude Key.msg.html

(cl:defclass <Key> (roslisp-msg-protocol:ros-message)
  ((v
    :reader v
    :initarg :v
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Key (<Key>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Key>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Key)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car_plugin-msg:<Key> is deprecated: use car_plugin-msg:Key instead.")))

(cl:ensure-generic-function 'v-val :lambda-list '(m))
(cl:defmethod v-val ((m <Key>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car_plugin-msg:v-val is deprecated.  Use car_plugin-msg:v instead.")
  (v m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<Key>)))
    "Constants for message type '<Key>"
  '((:UNKNOWN . 0)
    (:MOVE . 1)
    (:BRAKE . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'Key)))
    "Constants for message type 'Key"
  '((:UNKNOWN . 0)
    (:MOVE . 1)
    (:BRAKE . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Key>) ostream)
  "Serializes a message object of type '<Key>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'v)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Key>) istream)
  "Deserializes a message object of type '<Key>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'v)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Key>)))
  "Returns string type for a message object of type '<Key>"
  "car_plugin/Key")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Key)))
  "Returns string type for a message object of type 'Key"
  "car_plugin/Key")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Key>)))
  "Returns md5sum for a message object of type '<Key>"
  "e0ea58642b36fae1b5437fc7c2183bed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Key)))
  "Returns md5sum for a message object of type 'Key"
  "e0ea58642b36fae1b5437fc7c2183bed")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Key>)))
  "Returns full string definition for message of type '<Key>"
  (cl:format cl:nil "# Message constabt field to describe the key values~%uint8 UNKNOWN=0~%uint8 MOVE=1~%uint8 BRAKE=2~%# Message field ~%uint8 v~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Key)))
  "Returns full string definition for message of type 'Key"
  (cl:format cl:nil "# Message constabt field to describe the key values~%uint8 UNKNOWN=0~%uint8 MOVE=1~%uint8 BRAKE=2~%# Message field ~%uint8 v~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Key>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Key>))
  "Converts a ROS message object to a list"
  (cl:list 'Key
    (cl:cons ':v (v msg))
))
