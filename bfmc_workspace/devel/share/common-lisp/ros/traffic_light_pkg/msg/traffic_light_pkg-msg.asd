
(cl:in-package :asdf)

(defsystem "traffic_light_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "traffic_light" :depends-on ("_package_traffic_light"))
    (:file "_package_traffic_light" :depends-on ("_package"))
  ))