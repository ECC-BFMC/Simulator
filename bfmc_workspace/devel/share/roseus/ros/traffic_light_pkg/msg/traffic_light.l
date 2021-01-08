;; Auto-generated. Do not edit!


(when (boundp 'traffic_light_pkg::traffic_light)
  (if (not (find-package "TRAFFIC_LIGHT_PKG"))
    (make-package "TRAFFIC_LIGHT_PKG"))
  (shadow 'traffic_light (find-package "TRAFFIC_LIGHT_PKG")))
(unless (find-package "TRAFFIC_LIGHT_PKG::TRAFFIC_LIGHT")
  (make-package "TRAFFIC_LIGHT_PKG::TRAFFIC_LIGHT"))

(in-package "ROS")
;;//! \htmlinclude traffic_light.msg.html


(defclass traffic_light_pkg::traffic_light
  :super ros::object
  :slots (_id _state ))

(defmethod traffic_light_pkg::traffic_light
  (:init
   (&key
    ((:id __id) 0)
    ((:state __state) 0)
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _state (round __state))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:state
   (&optional __state)
   (if __state (setq _state __state)) _state)
  (:serialization-length
   ()
   (+
    ;; int8 _id
    1
    ;; int8 _state
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _id
       (write-byte _id s)
     ;; int8 _state
       (write-byte _state s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _id 127) (setq _id (- _id 256)))
   ;; int8 _state
     (setq _state (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _state 127) (setq _state (- _state 256)))
   ;;
   self)
  )

(setf (get traffic_light_pkg::traffic_light :md5sum-) "a9df1e2ca2c0390fc1af4aa647e41b61")
(setf (get traffic_light_pkg::traffic_light :datatype-) "traffic_light_pkg/traffic_light")
(setf (get traffic_light_pkg::traffic_light :definition-)
      "int8 id
int8 state

")



(provide :traffic_light_pkg/traffic_light "a9df1e2ca2c0390fc1af4aa647e41b61")


