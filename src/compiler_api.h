#ifndef COMPILER_API_H
#define COMPILER_API_H


#ifdef WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

struct Compiler;

// @Volatile must match Compiler.jyu stuff
struct Build_Options {
    String executable_name;
    String target_triple;
    bool only_want_obj_file  = false;
    bool verbose_diagnostics = false;
    bool emit_llvm_ir = false;
};

#ifdef __cplusplus
extern "C" {
#endif

    EXPORT Compiler *create_compiler_instance(Build_Options *options);
    EXPORT bool compiler_run_default_link_command(Compiler *compiler);
    EXPORT bool compiler_load_file(Compiler *compiler, String filename);
    EXPORT bool compiler_load_string(Compiler *compiler, String source);
    EXPORT bool compiler_typecheck_program(Compiler *compiler);
    EXPORT bool compiler_generate_llvm_module(Compiler *compiler);
    EXPORT bool compiler_emit_object_file(Compiler *compiler);
    EXPORT bool compiler_jit_program(Compiler *compiler);
    EXPORT void *compiler_jit_lookup_symbol(Compiler *compiler, String symbol_name);
    EXPORT void compiler_add_library_search_path(Compiler *compiler, String path);
    EXPORT void compiler_add_compiled_object_for_linking(Compiler *compiler, String path);

#ifdef __cplusplus
}; // extern "C"
#endif

#endif

