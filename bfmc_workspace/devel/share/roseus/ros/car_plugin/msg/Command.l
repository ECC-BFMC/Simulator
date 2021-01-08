;; Auto-generated. Do not edit!


(when (boundp 'car_plugin::Command)
  (if (not (find-package "CAR_PLUGIN"))
    (make-package "CAR_PLUGIN"))
  (shadow 'Command (find-package "CAR_PLUGIN")))
(unless (find-package "CAR_PLUGIN::COMMAND")
  (make-package "CAR_PLUGIN::COMMAND"))

(in-package "ROS")
;;//! \htmlinclude Command.msg.html


(defclass car_plugin::Command
  :super ros::object
  :slots (_key _msg_val ))

(defmethod car_plugin::Command
  (:init
   (&key
    ((:key __key) (instance car_plugin::Key :init))
    ((:msg_val __msg_val) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _key __key)
   (setq _msg_val __msg_val)
   self)
  (:key
   (&rest __key)
   (if (keywordp (car __key))
       (send* _key __key)
     (progn
       (if __key (setq _key (car __key)))
       _key)))
  (:msg_val
   (&optional __msg_val)
   (if __msg_val (setq _msg_val __msg_val)) _msg_val)
  (:serialization-length
   ()
   (+
    ;; car_plugin/Key _key
    (send _key :serialization-length)
    ;; float32[] _msg_val
    (* 4    (length _msg_val)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; car_plugin/Key _key
       (send _key :serialize s)
     ;; float32[] _msg_val
     (write-long (length _msg_val) s)
     (dotimes (i (length _msg_val))
       (sys::poke (elt _msg_val i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; car_plugin/Key _key
     (send _key :deserialize buf ptr-) (incf ptr- (send _key :serialization-length))
   ;; float32[] _msg_val
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _msg_val (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _msg_val i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get car_plugin::Command :md5sum-) "e127791eeae9498f8888358c49884e30")
(setf (get car_plugin::Command :datatype-) "car_plugin/Command")
(setf (get car_plugin::Command :definition-)
      "Key key
float32[] msg_val
================================================================================
MSG: car_plugin/Key
# Message constabt field to describe the key values
uint8 UNKNOWN=0
uint8 MOVE=1
uint8 BRAKE=2
# Message field 
uint8 v
")



(provide :car_plugin/Command "e127791eeae9498f8888358c49884e30")


