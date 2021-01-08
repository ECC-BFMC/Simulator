;; Auto-generated. Do not edit!


(when (boundp 'car_plugin::Response)
  (if (not (find-package "CAR_PLUGIN"))
    (make-package "CAR_PLUGIN"))
  (shadow 'Response (find-package "CAR_PLUGIN")))
(unless (find-package "CAR_PLUGIN::RESPONSE")
  (make-package "CAR_PLUGIN::RESPONSE"))

(in-package "ROS")
;;//! \htmlinclude Response.msg.html


(defclass car_plugin::Response
  :super ros::object
  :slots (_key _response ))

(defmethod car_plugin::Response
  (:init
   (&key
    ((:key __key) (instance car_plugin::Key :init))
    ((:response __response) "")
    )
   (send-super :init)
   (setq _key __key)
   (setq _response (string __response))
   self)
  (:key
   (&rest __key)
   (if (keywordp (car __key))
       (send* _key __key)
     (progn
       (if __key (setq _key (car __key)))
       _key)))
  (:response
   (&optional __response)
   (if __response (setq _response __response)) _response)
  (:serialization-length
   ()
   (+
    ;; car_plugin/Key _key
    (send _key :serialization-length)
    ;; string _response
    4 (length _response)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; car_plugin/Key _key
       (send _key :serialize s)
     ;; string _response
       (write-long (length _response) s) (princ _response s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; car_plugin/Key _key
     (send _key :deserialize buf ptr-) (incf ptr- (send _key :serialization-length))
   ;; string _response
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _response (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get car_plugin::Response :md5sum-) "62068c192be1c92f944918b622366c47")
(setf (get car_plugin::Response :datatype-) "car_plugin/Response")
(setf (get car_plugin::Response :definition-)
      "Key key
string response
================================================================================
MSG: car_plugin/Key
# Message constabt field to describe the key values
uint8 UNKNOWN=0
uint8 MOVE=1
uint8 BRAKE=2
# Message field 
uint8 v
")



(provide :car_plugin/Response "62068c192be1c92f944918b622366c47")


