
(cl:in-package :asdf)

(defsystem "echo_tutorial-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "EchoDistance" :depends-on ("_package_EchoDistance"))
    (:file "_package_EchoDistance" :depends-on ("_package"))
  ))