; Auto-generated. Do not edit!


(cl:in-package traffic_light_pkg-msg)


;//! \htmlinclude traffic_light.msg.html

(cl:defclass <traffic_light> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (state
    :reader state
    :initarg :state
    :type cl:fixnum
    :initform 0))
)

(cl:defclass traffic_light (<traffic_light>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <traffic_light>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'traffic_light)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name traffic_light_pkg-msg:<traffic_light> is deprecated: use traffic_light_pkg-msg:traffic_light instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <traffic_light>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader traffic_light_pkg-msg:id-val is deprecated.  Use traffic_light_pkg-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <traffic_light>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader traffic_light_pkg-msg:state-val is deprecated.  Use traffic_light_pkg-msg:state instead.")
  (state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <traffic_light>) ostream)
  "Serializes a message object of type '<traffic_light>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <traffic_light>) istream)
  "Deserializes a message object of type '<traffic_light>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'state) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<traffic_light>)))
  "Returns string type for a message object of type '<traffic_light>"
  "traffic_light_pkg/traffic_light")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'traffic_light)))
  "Returns string type for a message object of type 'traffic_light"
  "traffic_light_pkg/traffic_light")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<traffic_light>)))
  "Returns md5sum for a message object of type '<traffic_light>"
  "a9df1e2ca2c0390fc1af4aa647e41b61")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'traffic_light)))
  "Returns md5sum for a message object of type 'traffic_light"
  "a9df1e2ca2c0390fc1af4aa647e41b61")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<traffic_light>)))
  "Returns full string definition for message of type '<traffic_light>"
  (cl:format cl:nil "int8 id~%int8 state~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'traffic_light)))
  "Returns full string definition for message of type 'traffic_light"
  (cl:format cl:nil "int8 id~%int8 state~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <traffic_light>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <traffic_light>))
  "Converts a ROS message object to a list"
  (cl:list 'traffic_light
    (cl:cons ':id (id msg))
    (cl:cons ':state (state msg))
))
