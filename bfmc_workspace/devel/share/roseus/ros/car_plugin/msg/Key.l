;; Auto-generated. Do not edit!


(when (boundp 'car_plugin::Key)
  (if (not (find-package "CAR_PLUGIN"))
    (make-package "CAR_PLUGIN"))
  (shadow 'Key (find-package "CAR_PLUGIN")))
(unless (find-package "CAR_PLUGIN::KEY")
  (make-package "CAR_PLUGIN::KEY"))

(in-package "ROS")
;;//! \htmlinclude Key.msg.html


(intern "*UNKNOWN*" (find-package "CAR_PLUGIN::KEY"))
(shadow '*UNKNOWN* (find-package "CAR_PLUGIN::KEY"))
(defconstant car_plugin::Key::*UNKNOWN* 0)
(intern "*MOVE*" (find-package "CAR_PLUGIN::KEY"))
(shadow '*MOVE* (find-package "CAR_PLUGIN::KEY"))
(defconstant car_plugin::Key::*MOVE* 1)
(intern "*BRAKE*" (find-package "CAR_PLUGIN::KEY"))
(shadow '*BRAKE* (find-package "CAR_PLUGIN::KEY"))
(defconstant car_plugin::Key::*BRAKE* 2)
(defclass car_plugin::Key
  :super ros::object
  :slots (_v ))

(defmethod car_plugin::Key
  (:init
   (&key
    ((:v __v) 0)
    )
   (send-super :init)
   (setq _v (round __v))
   self)
  (:v
   (&optional __v)
   (if __v (setq _v __v)) _v)
  (:serialization-length
   ()
   (+
    ;; uint8 _v
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _v
       (write-byte _v s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _v
     (setq _v (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get car_plugin::Key :md5sum-) "e0ea58642b36fae1b5437fc7c2183bed")
(setf (get car_plugin::Key :datatype-) "car_plugin/Key")
(setf (get car_plugin::Key :definition-)
      "# Message constabt field to describe the key values
uint8 UNKNOWN=0
uint8 MOVE=1
uint8 BRAKE=2
# Message field 
uint8 v
")



(provide :car_plugin/Key "e0ea58642b36fae1b5437fc7c2183bed")


