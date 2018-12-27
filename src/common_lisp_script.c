#include <wchar.h>

#include "common_lisp_script.h"
#include <ecl/ecl.h>

#include <gdnative_api_struct.gen.h>

static const char *COMMON_LISP_RECOGNIZED_EXTENSIONS[] = {"lisp", "lsp", "l", "cl"};

static const char *COMMON_LISP_RESERVED_WORDS[] = {};
static const char *COMMON_LISP_COMMENT_DELIMITERS[] = { ";", "#| |#", 0 };
static const char *COMMON_LISP_STRING_DELIMITERS[] = { "\" \"", 0 };

static godot_pluginscript_language_desc desc;

// called when language is first used?
static godot_pluginscript_language_data *cl_init() {
  //TODO: set boot options, mainly heap size etc.
  cl_boot(0, NULL);
  return NULL;
}

// called when no longer using the language?
static void cl_finish() {
  cl_shutdown();
}

// called when a new script is loaded? (load-compile-maybe)
static godot_pluginscript_script_manifest cl_script_init(godot_pluginscript_language_data *p_data, const godot_string *p_path, const godot_string *p_source, godot_error *r_error) {
  godot_pluginscript_script_manifest manifest;
  return manifest;
}

// called when a script is unloaded?
static void cl_script_finish(godot_pluginscript_script_data *p_data) {
  //What to do here?
}

// called when an instance of the script is created, returns identifier of the instance
static godot_pluginscript_instance_data *cl_script_instance_init(godot_pluginscript_script_data *p_data, godot_object *p_owner) {
  return NULL;
}

// called to destroy an instance of a script identified by p_data
static void cl_script_instance_finish(godot_pluginscript_instance_data *p_data) {}

// Makes template code in new files
static godot_string cl_get_template_source_code(godot_pluginscript_language_data *p_data, const godot_string *p_class_name, const godot_string *p_base_class_name) {
  return godot_string_chars_to_utf8("");
}

static void cl_add_global_constant(godot_pluginscript_language_data *p_data, const godot_string *p_variable, const godot_variant *p_value) {}

void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *options) {
  GDNATIVE_API_INIT(options);

  // name of script
  desc.name = "Common Lisp";
  desc.type = "Common Lisp";
    
  // file extensions
  desc.extension = "lisp";
  desc.recognized_extensions = COMMON_LISP_RECOGNIZED_EXTENSIONS;

  desc.init = &cl_init; 
  //godot_pluginscript_instance_data *(*init)(godot_pluginscript_script_data *p_data, godot_object *p_owner);
  desc.finish = &cl_finish;

  // semantics
  desc.reserved_words = COMMON_LISP_RESERVED_WORDS;
  desc.comment_delimiters = COMMON_LISP_COMMENT_DELIMITERS;
  desc.string_delimiters = COMMON_LISP_STRING_DELIMITERS;
  
  desc.has_named_classes = false;
  desc.get_template_source_code = &cl_get_template_source_code;
  desc.add_global_constant = &cl_add_global_constant;

  desc.script_desc.init = &cl_script_init;
  //godot_pluginscript_script_manifest (*init)(godot_pluginscript_language_data *p_data, const godot_string *p_path, const godot_string *p_source, godot_error *r_error);
  desc.script_desc.finish = &cl_script_finish;

  desc.script_desc.instance_desc.init = &cl_script_instance_init;
  desc.script_desc.instance_desc.finish = &cl_script_instance_finish;

  // get and set "properties" on script classes (slots), will have to convert godot's "variant" to "cl_object"
  desc.script_desc.instance_desc.set_prop = NULL;
  desc.script_desc.instance_desc.get_prop = NULL;

  // Godot provides a handle to the script class which the method is to be called on
  desc.script_desc.instance_desc.call_method = NULL;

  // should call all parent notification metods. Should be trivial with CLOS.
  desc.script_desc.instance_desc.notification = NULL;

  // not sure  what to do here.
  desc.script_desc.instance_desc.refcount_incremented = NULL;
  desc.script_desc.instance_desc.refcount_decremented = NULL;

  godot_pluginscript_register_language(&desc);
}


//dunno
void GDN_EXPORT godot_gdnative_singleton() {}
void GDN_EXPORT godot_gdnative_terminate() {}
