;; creates spec files for cl-autowrap
(defpackage :godot-lisp-ffi
  (:use #:common-lisp
        #:autowrap))

(defpackage :godot-lisp-embedded
  (:use #:common-lisp)
  (:export))

;; godot user package will contain user facing API for writing scripts (defscript etc.)
(defpackage :godot-user
  (:use #:common-lisp))

(defpackage :utils
  (:use #:common-lisp)
  (:export
   :load-compile-maybe))

;; DEBUG OPTIONS
(eval-when (:compile-toplevel :load-toplevel :execute)
  (declaim (optimize safety debug)))
