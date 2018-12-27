(in-package :utils)

;; CDR-10
;;https://common-lisp.net/project/cdr/document/10/compiled-file-p.html
(defun compiled-file-p (file-name)
  (with-open-file (in file-name :direction :input :if-does-not-exist nil)
    (and in (char= #\( (peek-char nil in))
         (let ((form (ignore-errors (read in nil nil))))
           (and (consp form)
                ;; not sure how to check version
                ;;(eq (car form) 'SYSTEM::VERSION)
                (null (nth-value 1 (ignore-errors (eval form)))))))))

;;from this url:
;;http://clocc.hg.sourceforge.net/hgweb/clocc/clocc/file/tip/src/cllib/fileio.lisp#l393
(defun file-newer (f0 f1)
  "Return T if the first arg is newer than the second.
Non-existent files are assumed to be VERY old."
  (flet ((fwd (ff) (or (ignore-errors (file-write-date ff)) 0)))
    (> (fwd f0) (fwd f1))))

(defun load-compile-maybe (file &key load-only-if-compiled force)
  "Compile the file if newer than the compiled and load it."
  (if force (load (compile-file file))
      (let ((cf (compile-file-pathname file)))
        (if (or (file-newer file cf)
                (not (compiled-file-p cf)))
            (load (compile-file file))
            (unless load-only-if-compiled
              (load cf))))))
