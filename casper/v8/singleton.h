#include "libplatform/libplatform.h"
#include "v8.h"

namespace casper
{
    
    namespace v8
    {
        
        class Singleton
        {
            
        public:
            
            static Singleton& GetInstance()
            {
                static Singleton instance;
                return instance;
            }
            
        private: // Data
            
            ::v8::Platform* platform_;

        public:
            
            Singleton()
            {
                platform_ = nullptr;
            }
            
            virtual ~Singleton ()
            {
                ::v8::V8::Dispose();
                ::v8::V8::ShutdownPlatform();
                delete platform_;
            }
            
            Singleton(Singleton const&)       = delete;
            void operator=(Singleton const&)  = delete;
            
        public: //
            
            void Startup (const char* a_config_path)
            {
                ::v8::V8::InitializeICUDefaultLocation(a_config_path);
                ::v8::V8::InitializeExternalStartupData(a_config_path);
                platform_ = ::v8::platform::CreateDefaultPlatform();
                ::v8::V8::InitializePlatform(platform_);
                ::v8::V8::Initialize();
                
                
            }
            
        }; // end of class 'Singleton'
        
    } // end of namespace 'v8'
    
} // end of namespace 'casper'

