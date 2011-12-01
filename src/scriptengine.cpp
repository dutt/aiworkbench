#include "scriptengine.h"

#include <iostream>
#include <assert.h>
#include <scriptstdstring/scriptstdstring.h>
#include <stdio.h>

#ifdef __APPLE__
#define __LINUX__ //good enough for now
#endif 

#ifdef __LINUX__
#include <sys/time.h>
#include <termios.h>
#else
#include <windows.h>
#endif

using namespace std;


#ifdef __LINUX__
typedef unsigned int DWORD;
DWORD timeGetTime();
DWORD timeGetTime()
{
    timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec*1000 + time.tv_usec/1000;
}

int getch();
int getch()
{
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );

    ch = getchar();

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
#endif

void messageCallback(const asSMessageInfo* msg, void* param);
void messageCallback(const asSMessageInfo* msg, void* param)
{
    const char* type = "ERR ";
    if(msg->type == asMSGTYPE_WARNING)
        type = "WARN ";
    else if(msg->type == asMSGTYPE_INFORMATION)
        type = "INFO ";
    printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

void print(string& text);
void print(string& text)
{
    cout <<text;
}
void lineCallback(asIScriptContext* context, DWORD* timeout);
void lineCallback(asIScriptContext* context, DWORD* timeout)
{
    if(*timeout < timeGetTime())
        context->Abort();
}

bool startUp();
bool startUp()
{
    asIScriptEngine* engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
    if(engine == 0)
    {
        cout <<"Failed to create script engine" <<endl;
        return false;
    }
    engine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_GENERIC);
    RegisterStdString(engine);
    int r = 0;
    r = engine->RegisterGlobalFunction("void print(string& in)", asFUNCTION(print), asCALL_CDECL); assert(r >= 0);

    asIScriptContext* context = engine->CreateContext();
    if(context == 0)
    {
        cout <<"Failed to create context" <<endl;
        return false;
    }

    DWORD timeout;
    r = context->SetLineCallback(asFUNCTION(lineCallback), &timeout, asCALL_CDECL); assert(r >= 0);

    FILE* f = fopen("/Users/dutt/workspace/aiworkbench/scripts/main.as", "rb");
    assert(f != 0);
    if(f == 0)
    {
        cout <<"Failed to open script" <<endl;
        return false;
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);

    string script;
    script.resize(len);
    size_t c = fread(&script[0], len, 1, f);
    fclose(f);
    if(c == 0)
    {
        cout <<"Failed to read script" <<endl;
        return false;
    }

    asIScriptModule* module = engine->GetModule(0, asGM_ALWAYS_CREATE);
    r = module->AddScriptSection("main", &script[0], len); assert(r >= 0);
    r = module->Build(); assert(r >= 0);

    int func = engine->GetModule(0)->GetFunctionIdByDecl("void main()"); assert(func >= 0);
    r = context->Prepare(func); assert(r >= 0);

    string s = "a";
    print(s);
    timeout = timeGetTime() + 3000;
    cout <<"Running script..." <<endl;
    r = context->Execute();
    cout <<"done." <<endl;
    if(r != asEXECUTION_FINISHED)
    {
        if(r == asEXECUTION_ABORTED)
            cout <<"Script was aborted, probably timed out" <<endl;
        else if(r == asEXECUTION_EXCEPTION)
        {
            cout <<"Exception caught: " <<endl;
            int func = context->GetExceptionFunction();
            asIScriptFunction* expFunc = engine->GetFuncdefByIndex(func);
            cout <<"module: " <<expFunc->GetModuleName() <<endl;
            cout <<"section: " <<expFunc->GetScriptSectionName() <<endl;
            cout <<"function: " <<expFunc->GetDeclaration() <<endl;
            cout <<context->GetExceptionLineNumber() <<": " <<context->GetExceptionString() <<endl;
        }
    }
    return true;
}

ScriptEngine::ScriptEngine()
{
    assert(startUp());
}
