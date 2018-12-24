with import <nixpkgs> {};
{
    godot-lisp = stdenv.mkDerivation rec {
        name = "godot-lisp";
        buildInputs = [ ecl
                        libffi
                        gmp
                        clang ];
        # LIBGL_DIR=/run/opengl-driver/lib:/run/opengl-driver-32/lib;
        LD_LIBRARY_PATH = pkgs.stdenv.lib.makeLibraryPath buildInputs;
    };
}
