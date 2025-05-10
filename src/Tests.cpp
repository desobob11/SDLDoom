
#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL2/SDL.h"

#include <Windows.h>
#include <DbgHelp.h>
#include "Tests.h"



//#pragma comment(lib, "Dbghelp.lib")


uint32_t FAILS = 0;
uint32_t PASSES = 0;

std::string getFunctionNameStack(size_t index) {
    void* stack[64];
    USHORT frames = CaptureStackBackTrace(0, 100, stack, NULL);
    // get this frame if bad index
    if (index >= frames || index < 0) {
        index = 0;
    }

    // 256 bytes, zero initialized
    SYMBOL_INFO* symInfo =
        (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);

    // name should be 255 chars,ax
    symInfo->SizeOfStruct = sizeof(SYMBOL_INFO);
    symInfo->MaxNameLen = 255;


    // TODO: FIX this some day, SymFromAddr is failing
    DWORD64 displacement = 0;
    if (!SymFromAddr(GetCurrentProcess(), (DWORD64)stack[index], &displacement,
                     symInfo)) {
        free(symInfo);
        DWORD error = GetLastError();
        return "SymFromAddr failed with error: " + std::to_string(error);
    }

    std::string result = symInfo->Name;
    free(symInfo);
    return result;
}

void assertTrue(bool actual, std::string msg) {
    if (!actual) {
        std::cout << "FAIL: " << getFunctionNameStack(1) << " -> " << msg
                  << std::endl;
        ++FAILS;
    } else {
        ++PASSES;
    }
}

void assertFalse(bool actual, std::string msg) {
    if (actual) {
        std::cout << "FAIL: " << getFunctionNameStack(1) << " -> " << msg
                  << std::endl;
        ++FAILS;
    } else {
        ++PASSES;
    }
}

template <typename T>
void assertEquals(T expected, T actual, std::string msg) {
    if (expected != actual) {
        std::cout << "FAIL: " << getFunctionNameStack(1) << " -> " << msg
                  << std::endl;
        ++FAILS;
    } else {
        ++PASSES;
    }
}

template <typename T>
void assertNotEquals(T expected, T actual, std::string msg) {
    if (expected == actual) {
        std::cout << "FAIL: " << getFunctionNameStack(1) << " -> " << msg
                  << std::endl;
        ++FAILS;
    } else {
        ++PASSES;
    }
}




void test_spriteGetHitBox() {
    NGIN::Sprite sp1 {"imp", DOOM::VERTEX {300, 0, 300}};
    DOOM::VERTEX* arr = sp1.getHitBox();
    assertEquals(arr[0], DOOM::VERTEX {275, 0, 275}, "TOP LEFT OFF");
    assertEquals(arr[1], DOOM::VERTEX {325, 0, 275}, "TOP RIGHT OFF");
    assertEquals(arr[2], DOOM::VERTEX {275, 0, 325}, "BOT LEFT OFF");
    assertEquals(arr[3], DOOM::VERTEX {325, 0, 325}, "BOT RIGHT OFF");
    delete arr;
}




void test_vectorOverlapsBox() {
    DOOM::VERTEX topl{200, 0, 200};
    DOOM::VERTEX topr{400, 0, 200};
    DOOM::VERTEX botl{200, 0, 400};
    DOOM::VERTEX botr{400, 0, 400};

    DOOM::Vector middle = DOOM::Vector{DOOM::VERTEX{300, 0, 300}};
    assertTrue(middle.overlapsBox(topl, topr, botl, botr),
               "MIDDLE TEST FAILED");

    DOOM::Vector edge = DOOM::Vector{DOOM::VERTEX{200, 0, 300}};
    assertTrue(edge.overlapsBox(topl, topr, botl, botr),
               "TOP EDGE TEST FAILED");

    DOOM::Vector corner = DOOM::Vector{DOOM::VERTEX{400, 0, 400}};
    assertTrue(corner.overlapsBox(topl, topr, botl, botr),
               "BOTTOM RIGHT CORNER FAILED");

    DOOM::Vector outside = DOOM::Vector{DOOM::VERTEX{401, 0, 401}};
    assertFalse(outside.overlapsBox(topl, topr, botl, botr),
                "BOTTOM RIGHT BEYOND CORNER FAILED");
}

int main() {
    if (!SymInitialize(GetCurrentProcess(), NULL, TRUE)) {
        std::cerr << "SymInitialize failed with error: " << GetLastError()
                  << std::endl;
        return 1;
    }

    test_vectorOverlapsBox();
    test_spriteGetHitBox();

    std::cout << "PASSED TESTS: -> " << PASSES << " / " << PASSES + FAILS
              << std::endl;

    SymCleanup(GetCurrentProcess());
}