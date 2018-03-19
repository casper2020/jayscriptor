#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include "casper/term.h"
#include "casper/dm_data_source.h"
#include "casper/java/fake_java_expression.h"
#include "v8_shell.h"

int main(int argc, char* argv[]) {
  v8::V8::InitializeICUDefaultLocation(argv[0]);
  v8::V8::InitializeExternalStartupData(argv[0]);
  v8::Platform* platform = v8::platform::CreateDefaultPlatform();
  v8::V8::InitializePlatform(platform);
  v8::V8::Initialize();
  v8::V8::SetFlagsFromCommandLine(&argc, argv, true);
  v8::Isolate::CreateParams create_params;
  create_params.array_buffer_allocator =
        v8::ArrayBuffer::Allocator::NewDefaultAllocator();
  v8::Isolate* isolate = v8::Isolate::New(create_params);
  run_shell = (argc == 1);
  int result;
  {
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::Context> context = CreateShellContext(isolate);
    if (context.IsEmpty()) {
      fprintf(stderr, "Error creating context\n");
      return 1;
    }

//------------------------------------------------------------------------------

    /*
    static const int kBufferSize = 256;
    char buffer[kBufferSize];
    char* str = fgets(buffer, kBufferSize, stdin);
    v8::String::NewFromUtf8(context->GetIsolate(), str,
                            v8::NewStringType::kNormal).ToLocalChecked()
    */

    v8::Context::Scope context_scope(context);
    //Compile files given in stdin
    result = RunMain(isolate, platform, argc, argv);


    //Declarations
    v8::Local<v8::String> func_name =
      v8::String::NewFromUtf8(context->GetIsolate(), "calc_tipo1", v8::NewStringType::kNormal).ToLocalChecked();
    v8::Local<v8::Object> global = context->Global();
    v8::Local<v8::Value> value = global->Get(context, func_name).ToLocalChecked();;
    v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(value);
    v8::Local<v8::Value> args[3];
    v8::Local<v8::Value> js_result;

    v8::Local<v8::String> func_name2 =
      v8::String::NewFromUtf8(context->GetIsolate(), "convert_json", v8::NewStringType::kNormal).ToLocalChecked();
    v8::Local<v8::Value> value2 = global->Get(context, func_name2).ToLocalChecked();;
    v8::Local<v8::Function> convert_json = v8::Local<v8::Function>::Cast(value2);
    v8::Local<v8::Value> json_args[1];
    v8::Local<v8::Value> json_data_final;

    //Load JSON-----------------------------------------------------------------

    auto start1 = std::chrono::high_resolution_clock::now();

    std::ifstream ifs("jsonapi.json");
    std::string content( (std::istreambuf_iterator<char>(ifs)),
                         (std::istreambuf_iterator<char>()) );

    v8::Local<v8::Value> json_data = v8::JSON::Parse(context,
      v8::String::NewFromUtf8(context->GetIsolate(), content.c_str(), v8::NewStringType::kNormal).ToLocalChecked()).ToLocalChecked();
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end1 - start1 ).count();
    std::cout << "\nTime for JSON Parse: " << (duration)/1000.0 << "ms\n\n";

    //Convert JSON
    json_args[0]=json_data;
    if (!convert_json->Call(context, context->Global(), 1, json_args).ToLocal(&json_data_final))
      printf("error..\n");


    //Calculate the expressions-------------------------------------------------

    casper::Term resultado;
    int cnt0=1;
    int cnt1=1;
    int cnt2=1;

    auto start = std::chrono::high_resolution_clock::now();

    for(int ii=0; ii<cnt0; ii++){
      for(int i=0; i<cnt1; i++){

        //const char* arg1 = "dados1";
        const char* arg2 = std::to_string(i).c_str();
        //args[1] = v8::String::NewFromUtf8(context->GetIsolate(), arg1, v8::NewStringType::kNormal).ToLocalChecked();
        args[1] = json_data_final;
        args[2] = v8::String::NewFromUtf8(context->GetIsolate(), arg2, v8::NewStringType::kNormal).ToLocalChecked();

        for(int l=0; l<cnt2; l++){

          const char* arg0 = std::to_string(l+1).c_str();
          args[0] = v8::String::NewFromUtf8(context->GetIsolate(), arg0, v8::NewStringType::kNormal).ToLocalChecked();

          if (!func->Call(context, context->Global(), 3, args).ToLocal(&js_result))
            printf("error..\n");
          else{
            v8::String::Utf8Value str_2(js_result);
            const char* cstr = ToCString(str_2);
            resultado = cstr;
            //printf("%s\n", cstr);
          }
        }
      }
    }
    auto end = std::chrono::high_resolution_clock::now();
    //printf("%s\n", resultado);
    std::cout << "------Output:\n\n" << resultado.GetText() << "\n\n------------\n";
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
    std::cout << "\nV8 ---> nr of operations: " << cnt1 * cnt2 * cnt0
              << "\nTime for each operation: " << (elapsed_seconds/1000.0)/(cnt1*cnt2*cnt0) << " ms\n";



/*
    casper::Term resultado;

    resultado = ExecuteString3(
        context->GetIsolate(),
        v8::String::NewFromUtf8(context->GetIsolate(), str,
                                v8::NewStringType::kNormal).ToLocalChecked(),
        name, true, true);

    Local<Function> process_fun = Local<Function>::Cast(process_val);
*/

/*

    //const char* resultado;
    v8::Local<v8::String> name(
          v8::String::NewFromUtf8(context->GetIsolate(), "expr3.js",
                                  v8::NewStringType::kNormal).ToLocalChecked());

    casper::Term resultado;
    int cnt=1000;

    auto start = std::chrono::high_resolution_clock::now();

    for(int i=0; i<cnt; i++){
      resultado = ExecuteString2(
          context->GetIsolate(), ReadFile(context->GetIsolate(), "expr3.js").ToLocalChecked(),
          name, true, true);
    }

    auto end = std::chrono::high_resolution_clock::now();
    //printf("%s\n", resultado);
    std::cout << resultado.GetText();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
    std::cout << "\nV8 ---> nr of operations: " << cnt * 4
              << "\nTime for each operation: " << (elapsed_seconds/1000.0)/(4000) << " ms\n";
*/

//------------------------------------------------------------------------------

    //if (run_shell) RunShell(context, platform);
  }
  isolate->Dispose();
  v8::V8::Dispose();
  v8::V8::ShutdownPlatform();
  delete platform;
  delete create_params.array_buffer_allocator;
  return result;
}
