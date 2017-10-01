#include <godot/gdnative.h>
#include <godot/node_path.h>

#include <godot_nativescript.h>
#include <math.h>
#include <stdio.h>
#define PI 3.14159265

double res;

void *test_constructor(godot_object *obj, void *method_data) {
        res = cos ( 60.0 * PI / 180.0 );
        printf("test.constructor() %f\n", res );
        return 0;
}

void test_destructor(godot_object *obj, void *method_data, void *user_data) {
        printf("test.destructor()\n");
}

/** func _ready() **/
godot_variant test_ready(godot_object *obj, void *method_data, void *user_data, int num_args, godot_variant **args) {
        godot_variant ret;
        godot_variant_new_nil(&ret);

        printf("_ready()\n");

        return ret;
}

/** Library entry point **/
void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
}

/** Library de-initialization **/
void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
}

/** Script entry (Registering all the classes and stuff) **/
void GDN_EXPORT godot_nativescript_init(void *desc) {
        printf("nativescript init\n");

        godot_instance_create_func create_func = {
                .create_func = &test_constructor,
                .method_data = 0,
                .free_func   = 0
        };

        godot_instance_destroy_func destroy_func = {
                .destroy_func = &test_destructor,
                .method_data  = 0,
                .free_func    = 0
        };

        godot_nativescript_register_class(desc, "SimpleClass", "Node", create_func, destroy_func);

        {
                godot_instance_method method = {
                        .method = &test_ready,
                        .method_data = 0,
                        .free_func = 0
                };

                godot_method_attributes attr = {
                        .rpc_type = GODOT_METHOD_RPC_MODE_DISABLED
                };

                godot_nativescript_register_method(desc, "SimpleClass", "_ready", attr, method);
        }
}

godot_variant GDN_EXPORT some_godot_print(void *data, godot_array *args) {
        godot_variant ret;
        godot_variant_new_int(&ret, 77);

        godot_string s;
        godot_string_new_unicode_data(&s, L"Print example!", 14);
        godot_print(&s);
        godot_string_destroy(&s);

        char print_warning[] = "This is a warning!";
        char print_error[] = "This is an error!";
        char cc[] = "";
        godot_print_warning(print_warning,cc,cc,1);
        godot_print_error(print_error,cc,cc,1);
        return ret;
}
