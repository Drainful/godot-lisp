(asdf:defsystem #:godot-lisp
  :serial t
  :description "Common Lisp scripting for the Godot game engine"
  :version "0.0.1"
  :author "Adrian Fullmer"
  :depends-on (#:cl-autowrap
               #:cl-plus-c)
  :components ((:module #:src
                :components ((:file "packages")
                             (:file "utils")
                             (:file "autowrap")))
               (:module #:godot-spec)
               (:module #:godot-headers
                :components ((:static-file "gdnative_api_struct.gen.h")))))
