Command to compile:
gcc -I../external/godot_headers/ -fPIC -std=c99 -c src/godot_print.c -I./ -o src/godot_print.os && gcc -shared src/godot_print.os -o lib/godot_print.so

