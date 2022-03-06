/*
 *  Catch v2.13.0
 *  Generated: 2020-07-12 20:07:49.015950
 *  ----------------------------------------------------------
 *  This file has been merged from multiple headers. Please don't edit it directly
 *  Copyright (c) 2020 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
#define TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
// start catch.hpp


#define CATCH_VERSION_MAJOR 2
#define CATCH_VERSION_MINOR 13
#define CATCH_VERSION_PATCH 0

#ifdef __clang__
#    pragma clang system_header
#elif defined __GNUC__
#    pragma GCC system_header
#endif

// start catch_suppress_warnings.h

#ifdef __clang__
#   ifdef __ICC // icpc defines the __clang__ macro
#       pragma warning(push)
#       pragma warning(disable: 161 1682)
#   else // __ICC
#       pragma clang diagnostic push
#       pragma clang diagnostic ignored "-Wpadded"
#       pragma clang diagnostic ignored "-Wswitch-enum"
#       pragma clang diagnostic ignored "-Wcovered-switch-default"
#    endif
#elif defined __GNUC__
     // Because REQUIREs trigger GCC's -Wparentheses, and because still
     // supported version of g++ have only buggy support for _Pragmas,
     // Wparentheses have to be suppressed globally.
#    pragma GCC diagnostic ignored "-Wparentheses" // See #674 for details

#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wunused-variable"
#    pragma GCC diagnostic ignored "-Wpadded"
#endif
// end catch_suppress_warnings.h
#if defined(CATCH_CONFIG_MAIN) || defined(CATCH_CONFIG_RUNNER)
#  define CATCH_IMPL
#  define CATCH_CONFIG_ALL_PARTS
#endif

// In the impl file, we want to have access to all parts of the headers
// Can also be used to sanely support PCHs
#if defined(CATCH_CONFIG_ALL_PARTS)
#  define CATCH_CONFIG_EXTERNAL_INTERFACES
#  if defined(CATCH_CONFIG_DISABLE_MATCHERS)
#    undef CATCH_CONFIG_DISABLE_MATCHERS
#  endif
#  if !defined(CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER)
#    define CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER
#  endif
#endif

#if !defined(CATCH_CONFIG_IMPL_ONLY)
// start catch_platform.h

#ifdef __APPLE__
# include <TargetConditionals.h>
# if TARGET_OS_OSX == 1
#  define CATCH_PLATFORM_MAC
# elif TARGET_OS_IPHONE == 1
#  define CATCH_PLATFORM_IPHONE
# endif

#elif defined(linux) || defined(__linux) || defined(__linux__)
#  define CATCH_PLATFORM_LINUX

#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(_MSC_VER) || defined(__MINGW32__)
#  define CATCH_PLATFORM_WINDOWS
#endif

// end catch_platform.h

#ifdef CATCH_IMPL
#  ifndef CLARA_CONFIG_MAIN
#    define CLARA_CONFIG_MAIN_NOT_DEFINED
#    define CLARA_CONFIG_MAIN
#  endif
#endif

// start catch_user_interfaces.h

namespace Catch {
    unsigned int rngSeed();
}

// end catch_user_interfaces.h
// start catch_tag_alias_autoregistrar.h

// start catch_common.h

// start catch_compiler_capabilities.h

// Detect a number of compiler features - by compiler
// The following features are defined:
//
// CATCH_CONFIG_COUNTER : is the __COUNTER__ macro supported?
// CATCH_CONFIG_WINDOWS_SEH : is Windows SEH supported?
// CATCH_CONFIG_POSIX_SIGNALS : are POSIX signals supported?
// CATCH_CONFIG_DISABLE_EXCEPTIONS : Are exceptions enabled?
// ****************
// Note to maintainers: if new toggles are added please document them
// in configuration.md, too
// ****************

// In general each macro has a _NO_<feature name> form
// (e.g. CATCH_CONFIG_NO_POSIX_SIGNALS) which disables the feature.
// Many features, at point of detection, define an _INTERNAL_ macro, so they
// can be combined, en-mass, with the _NO_ forms later.

#ifdef __cplusplus

#  if (__cplusplus >= 201402L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201402L)
#    define CATCH_CPP14_OR_GREATER
#  endif

#  if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
#    define CATCH_CPP17_OR_GREATER
#  endif

#endif

#if defined(__cpp_lib_uncaught_exceptions)
#  define CATCH_INTERNAL_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS
#endif

// We have to avoid both ICC and Clang, because they try to mask themselves
// as gcc, and we want only GCC in this block
#if defined(__GNUC__) && !defined(__clang__) && !defined(__ICC)
#    define CATCH_INTERNAL_START_WARNINGS_SUPPRESSION _Pragma( "GCC diagnostic push" )
#    define CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION  _Pragma( "GCC diagnostic pop" )

#    define CATCH_INTERNAL_IGNORE_BUT_WARN(...) (void)__builtin_constant_p(__VA_ARGS__)

#endif

#if defined(__clang__)

#    define CATCH_INTERNAL_START_WARNINGS_SUPPRESSION _Pragma( "clang diagnostic push" )
#    define CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION  _Pragma( "clang diagnostic pop" )

// As of this writing, IBM XL's implementation of __builtin_constant_p has a bug
// which results in calls to destructors being emitted for each temporary,
// without a matching initialization. In practice, this can result in something
// like `std::string::~string` being called on an uninitialized value.
//
// For example, this code will likely segfault under IBM XL:
// ```
// REQUIRE(std::string("12") + "34" == "1234")
// ```
//
// Therefore, `CATCH_INTERNAL_IGNORE_BUT_WARN` is not implemented.
#  if !defined(__ibmxl__)
#    define CATCH_INTERNAL_IGNORE_BUT_WARN(...) (void)__builtin_constant_p(__VA_ARGS__) /* NOLINT(cppcoreguidelines-pro-type-vararg, hicpp-vararg) */
#  endif

#    define CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
         _Pragma( "clang diagnostic ignored \"-Wexit-time-destructors\"" ) \
         _Pragma( "clang diagnostic ignored \"-Wglobal-constructors\"")

#    define CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS \
         _Pragma( "clang diagnostic ignored \"-Wparentheses\"" )

#    define CATCH_INTERNAL_SUPPRESS_UNUSED_WARNINGS \
         _Pragma( "clang diagnostic ignored \"-Wunused-variable\"" )

#    define CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS \
         _Pragma( "clang diagnostic ignored \"-Wgnu-zero-variadic-macro-arguments\"" )

#    define CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
         _Pragma( "clang diagnostic ignored \"-Wunused-template\"" )

#endif // __clang__

////////////////////////////////////////////////////////////////////////////////
// Assume that non-Windows platforms support posix signals by default
#if !defined(CATCH_PLATFORM_WINDOWS)
    #define CATCH_INTERNAL_CONFIG_POSIX_SIGNALS
#endif

////////////////////////////////////////////////////////////////////////////////
// We know some environments not to support full POSIX signals
#if defined(__CYGWIN__) || defined(__QNX__) || defined(__EMSCRIPTEN__) || defined(__DJGPP__)
    #define CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS
#endif

#ifdef __OS400__
#       define CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS
#       define CATCH_CONFIG_COLOUR_NONE
#endif

////////////////////////////////////////////////////////////////////////////////
// Android somehow still does not support std::to_string
#if defined(__ANDROID__)
#    define CATCH_INTERNAL_CONFIG_NO_CPP11_TO_STRING
#    define CATCH_INTERNAL_CONFIG_ANDROID_LOGWRITE
#endif

////////////////////////////////////////////////////////////////////////////////
// Not all Windows environments support SEH properly
#if defined(__MINGW32__)
#    define CATCH_INTERNAL_CONFIG_NO_WINDOWS_SEH
#endif

////////////////////////////////////////////////////////////////////////////////
// PS4
#if defined(__ORBIS__)
#    define CATCH_INTERNAL_CONFIG_NO_NEW_CAPTURE
#endif

////////////////////////////////////////////////////////////////////////////////
// Cygwin
#ifdef __CYGWIN__

// Required for some versions of Cygwin to declare gettimeofday
// see: http://stackoverflow.com/questions/36901803/gettimeofday-not-declared-in-this-scope-cygwin
#   define _BSD_SOURCE
// some versions of cygwin (most) do not support std::to_string. Use the libstd check.
// https://gcc.gnu.org/onlinedocs/gcc-4.8.2/libstdc++/api/a01053_source.html line 2812-2813
# if !((__cplusplus >= 201103L) && defined(_GLIBCXX_USE_C99) \
           && !defined(_GLIBCXX_HAVE_BROKEN_VSWPRINTF))

#    define CATCH_INTERNAL_CONFIG_NO_CPP11_TO_STRING

# endif
#endif // __CYGWIN__

////////////////////////////////////////////////////////////////////////////////
// Visual C++
#if defined(_MSC_VER)

#  define CATCH_INTERNAL_START_WARNINGS_SUPPRESSION __pragma( warning(push) )
#  define CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION  __pragma( warning(pop) )

#  if _MSC_VER >= 1900 // Visual Studio 2015 or newer
#    define CATCH_INTERNAL_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS
#  endif

// Universal Windows platform does not support SEH
// Or console colours (or console at all...)
#  if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
#    define CATCH_CONFIG_COLOUR_NONE
#  else
#    define CATCH_INTERNAL_CONFIG_WINDOWS_SEH
#  endif

// MSVC traditional preprocessor needs some workaround for __VA_ARGS__
// _MSVC_TRADITIONAL == 0 means new conformant preprocessor
// _MSVC_TRADITIONAL == 1 means old traditional non-conformant preprocessor
#  if !defined(__clang__) // Handle Clang masquerading for msvc
#    if !defined(_MSVC_TRADITIONAL) || (defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL)
#      define CATCH_INTERNAL_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#    endif // MSVC_TRADITIONAL
#  endif // __clang__

#endif // _MSC_VER

#if defined(_REENTRANT) || defined(_MSC_VER)
// Enable async processing, as -pthread is specified or no additional linking is required
# define CATCH_INTERNAL_CONFIG_USE_ASYNC
#endif // _MSC_VER

////////////////////////////////////////////////////////////////////////////////
// Check if we are compiled with -fno-exceptions or equivalent
#if defined(__EXCEPTIONS) || defined(__cpp_exceptions) || defined(_CPPUNWIND)
#  define CATCH_INTERNAL_CONFIG_EXCEPTIONS_ENABLED
#endif

////////////////////////////////////////////////////////////////////////////////
// DJGPP
#ifdef __DJGPP__
#  define CATCH_INTERNAL_CONFIG_NO_WCHAR
#endif // __DJGPP__

////////////////////////////////////////////////////////////////////////////////
// Embarcadero C++Build
#if defined(__BORLANDC__)
    #define CATCH_INTERNAL_CONFIG_POLYFILL_ISNAN
#endif

////////////////////////////////////////////////////////////////////////////////

// Use of __COUNTER__ is suppressed during code analysis in
// CLion/AppCode 2017.2.x and former, because __COUNTER__ is not properly
// handled by it.
// Otherwise all supported compilers support COUNTER macro,
// but user still might want to turn it off
#if ( !defined(__JETBRAINS_IDE__) || __JETBRAINS_IDE__ >= 20170300L )
    #define CATCH_INTERNAL_CONFIG_COUNTER
#endif

////////////////////////////////////////////////////////////////////////////////

// RTX is a special version of Windows that is real time.
// This means that it is detected as Windows, but does not provide
// the same set of capabilities as real Windows does.
#if defined(UNDER_RTSS) || defined(RTX64_BUILD)
    #define CATCH_INTERNAL_CONFIG_NO_WINDOWS_SEH
    #define CATCH_INTERNAL_CONFIG_NO_ASYNC
    #define CATCH_CONFIG_COLOUR_NONE
#endif

#if !defined(_GLIBCXX_USE_C99_MATH_TR1)
#define CATCH_INTERNAL_CONFIG_GLOBAL_NEXTAFTER
#endif

// Various stdlib support checks that require __has_include
#if defined(__has_include)
  // Check if string_view is available and usable
  #if __has_include(<string_view>) && defined(CATCH_CPP17_OR_GREATER)
  #    define CATCH_INTERNAL_CONFIG_CPP17_STRING_VIEW
  #endif

  // Check if optional is available and usable
  #  if __has_include(<optional>) && defined(CATCH_CPP17_OR_GREATER)
  #    define CATCH_INTERNAL_CONFIG_CPP17_OPTIONAL
  #  endif // __has_include(<optional>) && defined(CATCH_CPP17_OR_GREATER)

  // Check if byte is available and usable
  #  if __has_include(<cstddef>) && defined(CATCH_CPP17_OR_GREATER)
  #    define CATCH_INTERNAL_CONFIG_CPP17_BYTE
  #  endif // __has_include(<cstddef>) && defined(CATCH_CPP17_OR_GREATER)

  // Check if variant is available and usable
  #  if __has_include(<variant>) && defined(CATCH_CPP17_OR_GREATER)
  #    if defined(__clang__) && (__clang_major__ < 8)
         // work around clang bug with libstdc++ https://bugs.llvm.org/show_bug.cgi?id=31852
         // fix should be in clang 8, workaround in libstdc++ 8.2
  #      include <ciso646>
  #      if defined(__GLIBCXX__) && defined(_GLIBCXX_RELEASE) && (_GLIBCXX_RELEASE < 9)
  #        define CATCH_CONFIG_NO_CPP17_VARIANT
  #      else
  #        define CATCH_INTERNAL_CONFIG_CPP17_VARIANT
  #      endif // defined(__GLIBCXX__) && defined(_GLIBCXX_RELEASE) && (_GLIBCXX_RELEASE < 9)
  #    else
  #      define CATCH_INTERNAL_CONFIG_CPP17_VARIANT
  #    endif // defined(__clang__) && (__clang_major__ < 8)
  #  endif // __has_include(<variant>) && defined(CATCH_CPP17_OR_GREATER)
#endif // defined(__has_include)

#if defined(CATCH_INTERNAL_CONFIG_COUNTER) && !defined(CATCH_CONFIG_NO_COUNTER) && !defined(CATCH_CONFIG_COUNTER)
#   define CATCH_CONFIG_COUNTER
#endif
#if defined(CATCH_INTERNAL_CONFIG_WINDOWS_SEH) && !defined(CATCH_CONFIG_NO_WINDOWS_SEH) && !defined(CATCH_CONFIG_WINDOWS_SEH) && !defined(CATCH_INTERNAL_CONFIG_NO_WINDOWS_SEH)
#   define CATCH_CONFIG_WINDOWS_SEH
#endif
// This is set by default, because we assume that unix compilers are posix-signal-compatible by default.
#if defined(CATCH_INTERNAL_CONFIG_POSIX_SIGNALS) && !defined(CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS) && !defined(CATCH_CONFIG_NO_POSIX_SIGNALS) && !defined(CATCH_CONFIG_POSIX_SIGNALS)
#   define CATCH_CONFIG_POSIX_SIGNALS
#endif
// This is set by default, because we assume that compilers with no wchar_t support are just rare exceptions.
#if !defined(CATCH_INTERNAL_CONFIG_NO_WCHAR) && !defined(CATCH_CONFIG_NO_WCHAR) && !defined(CATCH_CONFIG_WCHAR)
#   define CATCH_CONFIG_WCHAR
#endif

#if !defined(CATCH_INTERNAL_CONFIG_NO_CPP11_TO_STRING) && !defined(CATCH_CONFIG_NO_CPP11_TO_STRING) && !defined(CATCH_CONFIG_CPP11_TO_STRING)
#    define CATCH_CONFIG_CPP11_TO_STRING
#endif

#if defined(CATCH_INTERNAL_CONFIG_CPP17_OPTIONAL) && !defined(CATCH_CONFIG_NO_CPP17_OPTIONAL) && !defined(CATCH_CONFIG_CPP17_OPTIONAL)
#  define CATCH_CONFIG_CPP17_OPTIONAL
#endif

#if defined(CATCH_INTERNAL_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS) && !defined(CATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS) && !defined(CATCH_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS)
#  define CATCH_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS
#endif

#if defined(CATCH_INTERNAL_CONFIG_CPP17_STRING_VIEW) && !defined(CATCH_CONFIG_NO_CPP17_STRING_VIEW) && !defined(CATCH_CONFIG_CPP17_STRING_VIEW)
#  define CATCH_CONFIG_CPP17_STRING_VIEW
#endif

#if defined(CATCH_INTERNAL_CONFIG_CPP17_VARIANT) && !defined(CATCH_CONFIG_NO_CPP17_VARIANT) && !defined(CATCH_CONFIG_CPP17_VARIANT)
#  define CATCH_CONFIG_CPP17_VARIANT
#endif

#if defined(CATCH_INTERNAL_CONFIG_CPP17_BYTE) && !defined(CATCH_CONFIG_NO_CPP17_BYTE) && !defined(CATCH_CONFIG_CPP17_BYTE)
#  define CATCH_CONFIG_CPP17_BYTE
#endif

#if defined(CATCH_CONFIG_EXPERIMENTAL_REDIRECT)
#  define CATCH_INTERNAL_CONFIG_NEW_CAPTURE
#endif

#if defined(CATCH_INTERNAL_CONFIG_NEW_CAPTURE) && !defined(CATCH_INTERNAL_CONFIG_NO_NEW_CAPTURE) && !defined(CATCH_CONFIG_NO_NEW_CAPTURE) && !defined(CATCH_CONFIG_NEW_CAPTURE)
#  define CATCH_CONFIG_NEW_CAPTURE
#endif

#if !defined(CATCH_INTERNAL_CONFIG_EXCEPTIONS_ENABLED) && !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
#  define CATCH_CONFIG_DISABLE_EXCEPTIONS
#endif

#if defined(CATCH_INTERNAL_CONFIG_POLYFILL_ISNAN) && !defined(CATCH_CONFIG_NO_POLYFILL_ISNAN) && !defined(CATCH_CONFIG_POLYFILL_ISNAN)
#  define CATCH_CONFIG_POLYFILL_ISNAN
#endif

#if defined(CATCH_INTERNAL_CONFIG_USE_ASYNC)  && !defined(CATCH_INTERNAL_CONFIG_NO_ASYNC) && !defined(CATCH_CONFIG_NO_USE_ASYNC) && !defined(CATCH_CONFIG_USE_ASYNC)
#  define CATCH_CONFIG_USE_ASYNC
#endif

#if defined(CATCH_INTERNAL_CONFIG_ANDROID_LOGWRITE) && !defined(CATCH_CONFIG_NO_ANDROID_LOGWRITE) && !defined(CATCH_CONFIG_ANDROID_LOGWRITE)
#  define CATCH_CONFIG_ANDROID_LOGWRITE
#endif

#if defined(CATCH_INTERNAL_CONFIG_GLOBAL_NEXTAFTER) && !defined(CATCH_CONFIG_NO_GLOBAL_NEXTAFTER) && !defined(CATCH_CONFIG_GLOBAL_NEXTAFTER)
#  define CATCH_CONFIG_GLOBAL_NEXTAFTER
#endif

// Even if we do not think the compiler has that warning, we still have
// to provide a macro that can be used by the code.
#if !defined(CATCH_INTERNAL_START_WARNINGS_SUPPRESSION)
#   define CATCH_INTERNAL_START_WARNINGS_SUPPRESSION
#endif
#if !defined(CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION)
#   define CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION
#endif
#if !defined(CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS
#endif
#if !defined(CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS
#endif
#if !defined(CATCH_INTERNAL_SUPPRESS_UNUSED_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_UNUSED_WARNINGS
#endif
#if !defined(CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS
#endif

// The goal of this macro is to avoid evaluation of the arguments, but
// still have the compiler warn on problems inside...
#if !defined(CATCH_INTERNAL_IGNORE_BUT_WARN)
#   define CATCH_INTERNAL_IGNORE_BUT_WARN(...)
#endif

#if defined(__APPLE__) && defined(__apple_build_version__) && (__clang_major__ < 10)
#   undef CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS
#elif defined(__clang__) && (__clang_major__ < 5)
#   undef CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS
#endif

#if !defined(CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS
#endif

#if defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
#define CATCH_TRY if ((true))
#define CATCH_CATCH_ALL if ((false))
#define CATCH_CATCH_ANON(type) if ((false))
#else
#define CATCH_TRY try
#define CATCH_CATCH_ALL catch (...)
#define CATCH_CATCH_ANON(type) catch (type)
#endif

#if defined(CATCH_INTERNAL_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR) && !defined(CATCH_CONFIG_NO_TRADITIONAL_MSVC_PREPROCESSOR) && !defined(CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR)
#define CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#endif

// end catch_compiler_capabilities.h
#define INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line ) name##line
#define INTERNAL_CATCH_UNIQUE_NAME_LINE( name, line ) INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line )
#ifdef CATCH_CONFIG_COUNTER
#  define INTERNAL_CATCH_UNIQUE_NAME( name ) INTERNAL_CATCH_UNIQUE_NAME_LINE( name, __COUNTER__ )
#else
#  define INTERNAL_CATCH_UNIQUE_NAME( name ) INTERNAL_CATCH_UNIQUE_NAME_LINE( name, __LINE__ )
#endif

#include <iosfwd>
#include <string>
#include <cstdint>

// We need a dummy global operator<< so we can bring it into Catch namespace later
struct Catch_global_namespace_dummy {};
std::ostream& operator<<(std::ostream&, Catch_global_namespace_dummy);

namespace Catch {

    struct CaseSensitive { enum Choice {
        Yes,
        No
    }; };

    class NonCopyable {
        NonCopyable( NonCopyable const& )              = delete;
        NonCopyable( NonCopyable && )                  = delete;
        NonCopyable& operator = ( NonCopyable const& ) = delete;
        NonCopyable& operator = ( NonCopyable && )     = delete;

    protected:
        NonCopyable();
        virtual ~NonCopyable();
    };

    struct SourceLineInfo {

        SourceLineInfo() = delete;
        SourceLineInfo( char const* _file, std::size_t _line ) noexcept
        :   file( _file ),
            line( _line )
        {}

        SourceLineInfo( SourceLineInfo const& other )            = default;
        SourceLineInfo& operator = ( SourceLineInfo const& )     = default;
        SourceLineInfo( SourceLineInfo&& )              noexcept = default;
        SourceLineInfo& operator = ( SourceLineInfo&& ) noexcept = default;

        bool empty() const noexcept { return file[0] == '\0'; }
        bool operator == ( SourceLineInfo const& other ) const noexcept;
        bool operator < ( SourceLineInfo const& other ) const noexcept;

        char const* file;
        std::size_t line;
    };

    std::ostream& operator << ( std::ostream& os, SourceLineInfo const& info );

    // Bring in operator<< from global namespace into Catch namespace
    // This is necessary because the overload of operator<< above makes
    // lookup stop at namespace Catch
    using ::operator<<;

    // Use this in variadic streaming macros to allow
    //    >> +StreamEndStop
    // as well as
    //    >> stuff +StreamEndStop
    struct StreamEndStop {
        std::string operator+() const;
    };
    template<typename T>
    T const& operator + ( T const& value, StreamEndStop ) {
        return value;
    }
}

#define CATCH_INTERNAL_LINEINFO \
    ::Catch::SourceLineInfo( __FILE__, static_cast<std::size_t>( __LINE__ ) )

// end catch_common.h
namespace Catch {

    struct RegistrarForTagAliases {
        RegistrarForTagAliases( char const* alias, char const* tag, SourceLineInfo const& lineInfo );
    };

} // end namespace Catch

#define CATCH_REGISTER_TAG_ALIAS( alias, spec ) \
    CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
    CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
    namespace{ Catch::RegistrarForTagAliases INTERNAL_CATCH_UNIQUE_NAME( AutoRegisterTagAlias )( alias, spec, CATCH_INTERNAL_LINEINFO ); } \
    CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

// end catch_tag_alias_autoregistrar.h
// start catch_test_registry.h

// start catch_interfaces_testcase.h

#include <vector>

namespace Catch {

    class TestSpec;

    struct ITestInvoker {
        virtual void invoke () const = 0;
        virtual ~ITestInvoker();
    };

    class TestCase;
    struct IConfig;

    struct ITestCaseRegistry {
        virtual ~ITestCaseRegistry();
        virtual std::vector<TestCase> const& getAllTests() const = 0;
        virtual std::vector<TestCase> const& getAllTestsSorted( IConfig const& config ) const = 0;
    };

    bool isThrowSafe( TestCase const& testCase, IConfig const& config );
    bool matchTest( TestCase const& testCase, TestSpec const& testSpec, IConfig const& config );
    std::vector<TestCase> filterTests( std::vector<TestCase> const& testCases, TestSpec const& testSpec, IConfig const& config );
    std::vector<TestCase> const& getAllTestCasesSorted( IConfig const& config );

}

// end catch_interfaces_testcase.h
// start catch_stringref.h

#include <cstddef>
#include <string>
#include <iosfwd>
#include <cassert>

namespace Catch {

    /// A non-owning string class (similar to the forthcoming std::string_view)
    /// Note that, because a StringRef may be a substring of another string,
    /// it may not be null terminated.
    class StringRef {
    public:
        using size_type = std::size_t;
        using const_iterator = const char*;

    private:
        static constexpr char const* const s_empty = "";

        char const* m_start = s_empty;
        size_type m_size = 0;

    public: // construction
        constexpr StringRef() noexcept = default;

        StringRef( char const* rawChars ) noexcept;

        constexpr StringRef( char const* rawChars, size_type size ) noexcept
        :   m_start( rawChars ),
            m_size( size )
        {}

        StringRef( std::string const& stdString ) noexcept
        :   m_start( stdString.c_str() ),
            m_size( stdString.size() )
        {}

        explicit operator std::string() const {
            return std::string(m_start, m_size);
        }

    public: // operators
        auto operator == ( StringRef const& other ) const noexcept -> bool;
        auto operator != (StringRef const& other) const noexcept -> bool {
            return !(*this == other);
        }

        auto operator[] ( size_type index ) const noexcept -> char {
            assert(index < m_size);
            return m_start[index];
        }

    public: // named queries
        constexpr auto empty() const noexcept -> bool {
            return m_size == 0;
        }
        constexpr auto size() const noexcept -> size_type {
            return m_size;
        }

        // Returns the current start pointer. If the StringRef is not
        // null-terminated, throws std::domain_exception
        auto c_str() const -> char const*;

    public: // substrings and searches
        // Returns a substring of [start, start + length).
        // If start + length > size(), then the substring is [start, size()).
        // If start > size(), then the substring is empty.
        auto substr( size_type start, size_type length ) const noexcept -> StringRef;

        // Returns the current start pointer. May not be null-terminated.
        auto data() const noexcept -> char const*;

        constexpr auto isNullTerminated() const noexcept -> bool {
            return m_start[m_size] == '\0';
        }

    public: // iterators
        constexpr const_iterator begin() const { return m_start; }
        constexpr const_iterator end() const { return m_start + m_size; }
    };

    auto operator += ( std::string& lhs, StringRef const& sr ) -> std::string&;
    auto operator << ( std::ostream& os, StringRef const& sr ) -> std::ostream&;

    constexpr auto operator "" _sr( char const* rawChars, std::size_t size ) noexcept -> StringRef {
        return StringRef( rawChars, size );
    }
} // namespace Catch

constexpr auto operator "" _catch_sr( char const* rawChars, std::size_t size ) noexcept -> Catch::StringRef {
    return Catch::StringRef( rawChars, size );
}

// end catch_stringref.h
// start catch_preprocessor.hpp


#define CATCH_RECURSION_LEVEL0(...) __VA_ARGS__
#define CATCH_RECURSION_LEVEL1(...) CATCH_RECURSION_LEVEL0(CATCH_RECURSION_LEVEL0(CATCH_RECURSION_LEVEL0(__VA_ARGS__)))
#define CATCH_RECURSION_LEVEL2(...) CATCH_RECURSION_LEVEL1(CATCH_RECURSION_LEVEL1(CATCH_RECURSION_LEVEL1(__VA_ARGS__)))
#define CATCH_RECURSION_LEVEL3(...) CATCH_RECURSION_LEVEL2(CATCH_RECURSION_LEVEL2(CATCH_RECURSION_LEVEL2(__VA_ARGS__)))
#define CATCH_RECURSION_LEVEL4(...) CATCH_RECURSION_LEVEL3(CATCH_RECURSION_LEVEL3(CATCH_RECURSION_LEVEL3(__VA_ARGS__)))
#define CATCH_RECURSION_LEVEL5(...) CATCH_RECURSION_LEVEL4(CATCH_RECURSION_LEVEL4(CATCH_RECURSION_LEVEL4(__VA_ARGS__)))

#ifdef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define INTERNAL_CATCH_EXPAND_VARGS(...) __VA_ARGS__
// MSVC needs more evaluations
#define CATCH_RECURSION_LEVEL6(...) CATCH_RECURSION_LEVEL5(CATCH_RECURSION_LEVEL5(CATCH_RECURSION_LEVEL5(__VA_ARGS__)))
#define CATCH_RECURSE(...)  CATCH_RECURSION_LEVEL6(CATCH_RECURSION_LEVEL6(__VA_ARGS__))
#else
#define CATCH_RECURSE(...)  CATCH_RECURSION_LEVEL5(__VA_ARGS__)
#endif

#define CATCH_REC_END(...)
#define CATCH_REC_OUT

#define CATCH_EMPTY()
#define CATCH_DEFER(id) id CATCH_EMPTY()

#define CATCH_REC_GET_END2() 0, CATCH_REC_END
#define CATCH_REC_GET_END1(...) CATCH_REC_GET_END2
#define CATCH_REC_GET_END(...) CATCH_REC_GET_END1
#define CATCH_REC_NEXT0(test, next, ...) next CATCH_REC_OUT
#define CATCH_REC_NEXT1(test, next) CATCH_DEFER ( CATCH_REC_NEXT0 ) ( test, next, 0)
#define CATCH_REC_NEXT(test, next)  CATCH_REC_NEXT1(CATCH_REC_GET_END test, next)

#define CATCH_REC_LIST0(f, x, peek, ...) , f(x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST1) ) ( f, peek, __VA_ARGS__ )
#define CATCH_REC_LIST1(f, x, peek, ...) , f(x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST0) ) ( f, peek, __VA_ARGS__ )
#define CATCH_REC_LIST2(f, x, peek, ...)   f(x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST1) ) ( f, peek, __VA_ARGS__ )

#define CATCH_REC_LIST0_UD(f, userdata, x, peek, ...) , f(userdata, x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST1_UD) ) ( f, userdata, peek, __VA_ARGS__ )
#define CATCH_REC_LIST1_UD(f, userdata, x, peek, ...) , f(userdata, x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST0_UD) ) ( f, userdata, peek, __VA_ARGS__ )
#define CATCH_REC_LIST2_UD(f, userdata, x, peek, ...)   f(userdata, x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST1_UD) ) ( f, userdata, peek, __VA_ARGS__ )

// Applies the function macro `f` to each of the remaining parameters, inserts commas between the results,
// and passes userdata as the first parameter to each invocation,
// e.g. CATCH_REC_LIST_UD(f, x, a, b, c) evaluates to f(x, a), f(x, b), f(x, c)
#define CATCH_REC_LIST_UD(f, userdata, ...) CATCH_RECURSE(CATCH_REC_LIST2_UD(f, userdata, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define CATCH_REC_LIST(f, ...) CATCH_RECURSE(CATCH_REC_LIST2(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define INTERNAL_CATCH_EXPAND1(param) INTERNAL_CATCH_EXPAND2(param)
#define INTERNAL_CATCH_EXPAND2(...) INTERNAL_CATCH_NO## __VA_ARGS__
#define INTERNAL_CATCH_DEF(...) INTERNAL_CATCH_DEF __VA_ARGS__
#define INTERNAL_CATCH_NOINTERNAL_CATCH_DEF
#define INTERNAL_CATCH_STRINGIZE(...) INTERNAL_CATCH_STRINGIZE2(__VA_ARGS__)
#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define INTERNAL_CATCH_STRINGIZE2(...) #__VA_ARGS__
#define INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS(param) INTERNAL_CATCH_STRINGIZE(INTERNAL_CATCH_REMOVE_PARENS(param))
#else
// MSVC is adding extra space and needs another indirection to expand INTERNAL_CATCH_NOINTERNAL_CATCH_DEF
#define INTERNAL_CATCH_STRINGIZE2(...) INTERNAL_CATCH_STRINGIZE3(__VA_ARGS__)
#define INTERNAL_CATCH_STRINGIZE3(...) #__VA_ARGS__
#define INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS(param) (INTERNAL_CATCH_STRINGIZE(INTERNAL_CATCH_REMOVE_PARENS(param)) + 1)
#endif

#define INTERNAL_CATCH_MAKE_NAMESPACE2(...) ns_##__VA_ARGS__
#define INTERNAL_CATCH_MAKE_NAMESPACE(name) INTERNAL_CATCH_MAKE_NAMESPACE2(name)

#define INTERNAL_CATCH_REMOVE_PARENS(...) INTERNAL_CATCH_EXPAND1(INTERNAL_CATCH_DEF __VA_ARGS__)

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define INTERNAL_CATCH_MAKE_TYPE_LIST2(...) decltype(get_wrapper<INTERNAL_CATCH_REMOVE_PARENS_GEN(__VA_ARGS__)>())
#define INTERNAL_CATCH_MAKE_TYPE_LIST(...) INTERNAL_CATCH_MAKE_TYPE_LIST2(INTERNAL_CATCH_REMOVE_PARENS(__VA_ARGS__))
#else
#define INTERNAL_CATCH_MAKE_TYPE_LIST2(...) INTERNAL_CATCH_EXPAND_VARGS(decltype(get_wrapper<INTERNAL_CATCH_REMOVE_PARENS_GEN(__VA_ARGS__)>()))
#define INTERNAL_CATCH_MAKE_TYPE_LIST(...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_MAKE_TYPE_LIST2(INTERNAL_CATCH_REMOVE_PARENS(__VA_ARGS__)))
#endif

#define INTERNAL_CATCH_MAKE_TYPE_LISTS_FROM_TYPES(...)\
    CATCH_REC_LIST(INTERNAL_CATCH_MAKE_TYPE_LIST,__VA_ARGS__)

#define INTERNAL_CATCH_REMOVE_PARENS_1_ARG(_0) INTERNAL_CATCH_REMOVE_PARENS(_0)
#define INTERNAL_CATCH_REMOVE_PARENS_2_ARG(_0, _1) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_1_ARG(_1)
#define INTERNAL_CATCH_REMOVE_PARENS_3_ARG(_0, _1, _2) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_2_ARG(_1, _2)
#define INTERNAL_CATCH_REMOVE_PARENS_4_ARG(_0, _1, _2, _3) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_3_ARG(_1, _2, _3)
#define INTERNAL_CATCH_REMOVE_PARENS_5_ARG(_0, _1, _2, _3, _4) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_4_ARG(_1, _2, _3, _4)
#define INTERNAL_CATCH_REMOVE_PARENS_6_ARG(_0, _1, _2, _3, _4, _5) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_5_ARG(_1, _2, _3, _4, _5)
#define INTERNAL_CATCH_REMOVE_PARENS_7_ARG(_0, _1, _2, _3, _4, _5, _6) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_6_ARG(_1, _2, _3, _4, _5, _6)
#define INTERNAL_CATCH_REMOVE_PARENS_8_ARG(_0, _1, _2, _3, _4, _5, _6, _7) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_7_ARG(_1, _2, _3, _4, _5, _6, _7)
#define INTERNAL_CATCH_REMOVE_PARENS_9_ARG(_0, _1, _2, _3, _4, _5, _6, _7, _8) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_8_ARG(_1, _2, _3, _4, _5, _6, _7, _8)
#define INTERNAL_CATCH_REMOVE_PARENS_10_ARG(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_9_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9)
#define INTERNAL_CATCH_REMOVE_PARENS_11_ARG(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_10_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10)

#define INTERNAL_CATCH_VA_NARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

#define INTERNAL_CATCH_TYPE_GEN\
    template<typename...> struct TypeList {};\
    template<typename...Ts>\
    constexpr auto get_wrapper() noexcept -> TypeList<Ts...> { return {}; }\
    template<template<typename...> class...> struct TemplateTypeList{};\
    template<template<typename...> class...Cs>\
    constexpr auto get_wrapper() noexcept -> TemplateTypeList<Cs...> { return {}; }\
    template<typename...>\
    struct append;\
    template<typename...>\
    struct rewrap;\
    template<template<typename...> class, typename...>\
    struct create;\
    template<template<typename...> class, typename>\
    struct convert;\
    \
    template<typename T> \
    struct append<T> { using type = T; };\
    template< template<typename...> class L1, typename...E1, template<typename...> class L2, typename...E2, typename...Rest>\
    struct append<L1<E1...>, L2<E2...>, Rest...> { using type = typename append<L1<E1...,E2...>, Rest...>::type; };\
    template< template<typename...> class L1, typename...E1, typename...Rest>\
    struct append<L1<E1...>, TypeList<mpl_::na>, Rest...> { using type = L1<E1...>; };\
    \
    template< template<typename...> class Container, template<typename...> class List, typename...elems>\
    struct rewrap<TemplateTypeList<Container>, List<elems...>> { using type = TypeList<Container<elems...>>; };\
    template< template<typename...> class Container, template<typename...> class List, class...Elems, typename...Elements>\
    struct rewrap<TemplateTypeList<Container>, List<Elems...>, Elements...> { using type = typename append<TypeList<Container<Elems...>>, typename rewrap<TemplateTypeList<Container>, Elements...>::type>::type; };\
    \
    template<template <typename...> class Final, template< typename...> class...Containers, typename...Types>\
    struct create<Final, TemplateTypeList<Containers...>, TypeList<Types...>> { using type = typename append<Final<>, typename rewrap<TemplateTypeList<Containers>, Types...>::type...>::type; };\
    template<template <typename...> class Final, template <typename...> class List, typename...Ts>\
    struct convert<Final, List<Ts...>> { using type = typename append<Final<>,TypeList<Ts>...>::type; };

#define INTERNAL_CATCH_NTTP_1(signature, ...)\
    template<INTERNAL_CATCH_REMOVE_PARENS(signature)> struct Nttp{};\
    template<INTERNAL_CATCH_REMOVE_PARENS(signature)>\
    constexpr auto get_wrapper() noexcept -> Nttp<__VA_ARGS__> { return {}; } \
    template<template<INTERNAL_CATCH_REMOVE_PARENS(signature)> class...> struct NttpTemplateTypeList{};\
    template<template<INTERNAL_CATCH_REMOVE_PARENS(signature)> class...Cs>\
    constexpr auto get_wrapper() noexcept -> NttpTemplateTypeList<Cs...> { return {}; } \
    \
    template< template<INTERNAL_CATCH_REMOVE_PARENS(signature)> class Container, template<INTERNAL_CATCH_REMOVE_PARENS(signature)> class List, INTERNAL_CATCH_REMOVE_PARENS(signature)>\
    struct rewrap<NttpTemplateTypeList<Container>, List<__VA_ARGS__>> { using type = TypeList<Container<__VA_ARGS__>>; };\
    template< template<INTERNAL_CATCH_REMOVE_PARENS(signature)> class Container, template<INTERNAL_CATCH_REMOVE_PARENS(signature)> class List, INTERNAL_CATCH_REMOVE_PARENS(signature), typename...Elements>\
    struct rewrap<NttpTemplateTypeList<Container>, List<__VA_ARGS__>, Elements...> { using type = typename append<TypeList<Container<__VA_ARGS__>>, typename rewrap<NttpTemplateTypeList<Container>, Elements...>::type>::type; };\
    template<template <typename...> class Final, template<INTERNAL_CATCH_REMOVE_PARENS(signature)> class...Containers, typename...Types>\
    struct create<Final, NttpTemplateTypeList<Containers...>, TypeList<Types...>> { using type = typename append<Final<>, typename rewrap<NttpTemplateTypeList<Containers>, Types...>::type...>::type; };

#define INTERNAL_CATCH_DECLARE_SIG_TEST0(TestName)
#define INTERNAL_CATCH_DECLARE_SIG_TEST1(TestName, signature)\
    template<INTERNAL_CATCH_REMOVE_PARENS(signature)>\
    static void TestName()
#define INTERNAL_CATCH_DECLARE_SIG_TEST_X(TestName, signature, ...)\
    template<INTERNAL_CATCH_REMOVE_PARENS(signature)>\
    static void TestName()

#define INTERNAL_CATCH_DEFINE_SIG_TEST0(TestName)
#define INTERNAL_CATCH_DEFINE_SIG_TEST1(TestName, signature)\
    template<INTERNAL_CATCH_REMOVE_PARENS(signature)>\
    static void TestName()
#define INTERNAL_CATCH_DEFINE_SIG_TEST_X(TestName, signature,...)\
    template<INTERNAL_CATCH_REMOVE_PARENS(signature)>\
    static void TestName()

#define INTERNAL_CATCH_NTTP_REGISTER0(TestFunc, signature)\
    template<typename Type>\
    void reg_test(TypeList<Type>, Catch::NameAndTags nameAndTags)\
    {\
        Catch::AutoReg( Catch::makeTestInvoker(&TestFunc<Type>), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), nameAndTags);\
    }

#define INTERNAL_CATCH_NTTP_REGISTER(TestFunc, signature, ...)\
    template<INTERNAL_CATCH_REMOVE_PARENS(signature)>\
    void reg_test(Nttp<__VA_ARGS__>, Catch::NameAndTags nameAndTags)\
    {\
        Catch::AutoReg( Catch::makeTestInvoker(&TestFunc<__VA_ARGS__>), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), nameAndTags);\
    }

#define INTERNAL_CATCH_NTTP_REGISTER_METHOD0(TestName, signature, ...)\
    template<typename Type>\
    void reg_test(TypeList<Type>, Catch::StringRef className, Catch::NameAndTags nameAndTags)\
    {\
        Catch::AutoReg( Catch::makeTestInvoker(&TestName<Type>::test), CATCH_INTERNAL_LINEINFO, className, nameAndTags);\
    }

#define INTERNAL_CATCH_NTTP_REGISTER_METHOD(TestName, signature, ...)\
    template<INTERNAL_CATCH_REMOVE_PARENS(signature)>\
    void reg_test(Nttp<__VA_ARGS__>, Catch::StringRef className, Catch::NameAndTags nameAndTags)\
    {\
        Catch::AutoReg( Catch::makeTestInvoker(&TestName<__VA_ARGS__>::test), CATCH_INTERNAL_LINEINFO, className, nameAndTags);\
    }

#define INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD0(TestName, ClassName)
#define INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD1(TestName, ClassName, signature)\
    template<typename TestType> \
    struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName)<TestType> { \
        void test();\
    }

#define INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X(TestName, ClassName, signature, ...)\
    template<INTERNAL_CATCH_REMOVE_PARENS(signature)> \
    struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName)<__VA_ARGS__> { \
        void test();\
    }

#define INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD0(TestName)
#define INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD1(TestName, signature)\
    template<typename TestType> \
    void INTERNAL_CATCH_MAKE_NAMESPACE(TestName)::TestName<TestType>::test()
#define INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X(TestName, signature, ...)\
    template<INTERNAL_CATCH_REMOVE_PARENS(signature)> \
    void INTERNAL_CATCH_MAKE_NAMESPACE(TestName)::TestName<__VA_ARGS__>::test()

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define INTERNAL_CATCH_NTTP_0
#define INTERNAL_CATCH_NTTP_GEN(...) INTERNAL_CATCH_VA_NARGS_IMPL(__VA_ARGS__, INTERNAL_CATCH_NTTP_1(__VA_ARGS__), INTERNAL_CATCH_NTTP_1(__VA_ARGS__), INTERNAL_CATCH_NTTP_1(__VA_ARGS__), INTERNAL_CATCH_NTTP_1(__VA_ARGS__), INTERNAL_CATCH_NTTP_1(__VA_ARGS__), INTERNAL_CATCH_NTTP_1( __VA_ARGS__), INTERNAL_CATCH_NTTP_1( __VA_ARGS__), INTERNAL_CATCH_NTTP_1( __VA_ARGS__), INTERNAL_CATCH_NTTP_1( __VA_ARGS__),INTERNAL_CATCH_NTTP_1( __VA_ARGS__), INTERNAL_CATCH_NTTP_0)
#define INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD(TestName, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD1, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD0)(TestName, __VA_ARGS__)
#define INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD(TestName, ClassName, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD1, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD0)(TestName, ClassName, __VA_ARGS__)
#define INTERNAL_CATCH_NTTP_REG_METHOD_GEN(TestName, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD0, INTERNAL_CATCH_NTTP_REGISTER_METHOD0)(TestName, __VA_ARGS__)
#define INTERNAL_CATCH_NTTP_REG_GEN(TestFunc, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER0, INTERNAL_CATCH_NTTP_REGISTER0)(TestFunc, __VA_ARGS__)
#define INTERNAL_CATCH_DEFINE_SIG_TEST(TestName, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DEFINE_SIG_TEST1, INTERNAL_CATCH_DEFINE_SIG_TEST0)(TestName, __VA_ARGS__)
#define INTERNAL_CATCH_DECLARE_SIG_TEST(TestName, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DECLARE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST1, INTERNAL_CATCH_DECLARE_SIG_TEST0)(TestName, __VA_ARGS__)
#define INTERNAL_CATCH_REMOVE_PARENS_GEN(...) INTERNAL_CATCH_VA_NARGS_IMPL(__VA_ARGS__, INTERNAL_CATCH_REMOVE_PARENS_11_ARG,INTERNAL_CATCH_REMOVE_PARENS_10_ARG,INTERNAL_CATCH_REMOVE_PARENS_9_ARG,INTERNAL_CATCH_REMOVE_PARENS_8_ARG,INTERNAL_CATCH_REMOVE_PARENS_7_ARG,INTERNAL_CATCH_REMOVE_PARENS_6_ARG,INTERNAL_CATCH_REMOVE_PARENS_5_ARG,INTERNAL_CATCH_REMOVE_PARENS_4_ARG,INTERNAL_CATCH_REMOVE_PARENS_3_ARG,INTERNAL_CATCH_REMOVE_PARENS_2_ARG,INTERNAL_CATCH_REMOVE_PARENS_1_ARG)(__VA_ARGS__)
#else
#define INTERNAL_CATCH_NTTP_0(signature)
#define INTERNAL_CATCH_NTTP_GEN(...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL(__VA_ARGS__, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1,INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_0)( __VA_ARGS__))
#define INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD(TestName, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD1, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD0)(TestName, __VA_ARGS__))
#define INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD(TestName, ClassName, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD1, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD0)(TestName, ClassName, __VA_ARGS__))
#define INTERNAL_CATCH_NTTP_REG_METHOD_GEN(TestName, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD0, INTERNAL_CATCH_NTTP_REGISTER_METHOD0)(TestName, __VA_ARGS__))
#define INTERNAL_CATCH_NTTP_REG_GEN(TestFunc, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER0, INTERNAL_CATCH_NTTP_REGISTER0)(TestFunc, __VA_ARGS__))
#define INTERNAL_CATCH_DEFINE_SIG_TEST(TestName, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DEFINE_SIG_TEST1, INTERNAL_CATCH_DEFINE_SIG_TEST0)(TestName, __VA_ARGS__))
#define INTERNAL_CATCH_DECLARE_SIG_TEST(TestName, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DECLARE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST1, INTERNAL_CATCH_DECLARE_SIG_TEST0)(TestName, __VA_ARGS__))
#define INTERNAL_CATCH_REMOVE_PARENS_GEN(...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL(__VA_ARGS__, INTERNAL_CATCH_REMOVE_PARENS_11_ARG,INTERNAL_CATCH_REMOVE_PARENS_10_ARG,INTERNAL_CATCH_REMOVE_PARENS_9_ARG,INTERNAL_CATCH_REMOVE_PARENS_8_ARG,INTERNAL_CATCH_REMOVE_PARENS_7_ARG,INTERNAL_CATCH_REMOVE_PARENS_6_ARG,INTERNAL_CATCH_REMOVE_PARENS_5_ARG,INTERNAL_CATCH_REMOVE_PARENS_4_ARG,INTERNAL_CATCH_REMOVE_PARENS_3_ARG,INTERNAL_CATCH_REMOVE_PARENS_2_ARG,INTERNAL_CATCH_REMOVE_PARENS_1_ARG)(__VA_ARGS__))
#endif

// end catch_preprocessor.hpp
// start catch_meta.hpp


#include <type_traits>

namespace Catch {
    template<typename T>
    struct always_false : std::false_type {};

    template <typename> struct true_given : std::true_type {};
    struct is_callable_tester {
        template <typename Fun, typename... Args>
        true_given<decltype(std::declval<Fun>()(std::declval<Args>()...))> static test(int);
        template <typename...>
        std::false_type static test(...);
    };

    template <typename T>
    struct is_callable;

    template <typename Fun, typename... Args>
    struct is_callable<Fun(Args...)> : decltype(is_callable_tester::test<Fun, Args...>(0)) {};

#if defined(__cpp_lib_is_invocable) && __cpp_lib_is_invocable >= 201703
    // std::result_of is deprecated in C++17 and removed in C++20. Hence, it is
    // replaced with std::invoke_result here.
    template <typename Func, typename... U>
    using FunctionReturnType = std::remove_reference_t<std::remove_cv_t<std::invoke_result_t<Func, U...>>>;
#else
    // Keep ::type here because we still support C++11
    template <typename Func, typename... U>
    using FunctionReturnType = typename std::remove_reference<typename std::remove_cv<typename std::result_of<Func(U...)>::type>::type>::type;
#endif

} // namespace Catch

namespace mpl_{
    struct na;
}

// end catch_meta.hpp
namespace Catch {

template<typename C>
class TestInvokerAsMethod : public ITestInvoker {
    void (C::*m_testAsMethod)();
public:
    TestInvokerAsMethod( void (C::*testAsMethod)() ) noexcept : m_testAsMethod( testAsMethod ) {}

    void invoke() const override {
        C obj;
        (obj.*m_testAsMethod)();
    }
};

auto makeTestInvoker( void(*testAsFunction)() ) noexcept -> ITestInvoker*;

template<typename C>
auto makeTestInvoker( void (C::*testAsMethod)() ) noexcept -> ITestInvoker* {
    return new(std::nothrow) TestInvokerAsMethod<C>( testAsMethod );
}

struct NameAndTags {
    NameAndTags( StringRef const& name_ = StringRef(), StringRef const& tags_ = StringRef() ) noexcept;
    StringRef name;
    StringRef tags;
};

struct AutoReg : NonCopyable {
    AutoReg( ITestInvoker* invoker, SourceLineInfo const& lineInfo, StringRef const& classOrMethod, NameAndTags const& nameAndTags ) noexcept;
    ~AutoReg();
};

} // end namespace Catch

#if defined(CATCH_CONFIG_DISABLE)
    #define INTERNAL_CATCH_TESTCASE_NO_REGISTRATION( TestName, ... ) \
        static void TestName()
    #define INTERNAL_CATCH_TESTCASE_METHOD_NO_REGISTRATION( TestName, ClassName, ... ) \
        namespace{                        \
            struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName) { \
                void test();              \
            };                            \
        }                                 \
        void TestName::test()
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION_2( TestName, TestFunc, Name, Tags, Signature, ... )  \
        INTERNAL_CATCH_DEFINE_SIG_TEST(TestFunc, INTERNAL_CATCH_REMOVE_PARENS(Signature))
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION_2( TestNameClass, TestName, ClassName, Name, Tags, Signature, ... )    \
        namespace{                                                                                  \
            namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName) {                                      \
            INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD(TestName, ClassName, INTERNAL_CATCH_REMOVE_PARENS(Signature));\
        }                                                                                           \
        }                                                                                           \
        INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD(TestName, INTERNAL_CATCH_REMOVE_PARENS(Signature))

    #ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION(Name, Tags, ...) \
            INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename TestType, __VA_ARGS__ )
    #else
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION(Name, Tags, ...) \
            INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename TestType, __VA_ARGS__ ) )
    #endif

    #ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG_NO_REGISTRATION(Name, Tags, Signature, ...) \
            INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__ )
    #else
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG_NO_REGISTRATION(Name, Tags, Signature, ...) \
            INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__ ) )
    #endif

    #ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION( ClassName, Name, Tags,... ) \
            INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, typename T, __VA_ARGS__ )
    #else
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION( ClassName, Name, Tags,... ) \
            INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, typename T, __VA_ARGS__ ) )
    #endif

    #ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG_NO_REGISTRATION( ClassName, Name, Tags, Signature, ... ) \
            INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, Signature, __VA_ARGS__ )
    #else
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG_NO_REGISTRATION( ClassName, Name, Tags, Signature, ... ) \
            INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, Signature, __VA_ARGS__ ) )
    #endif
#endif

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_TESTCASE2( TestName, ... ) \
        static void TestName(); \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        namespace{ Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( &TestName ), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), Catch::NameAndTags{ __VA_ARGS__ } ); } /* NOLINT */ \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        static void TestName()
    #define INTERNAL_CATCH_TESTCASE( ... ) \
        INTERNAL_CATCH_TESTCASE2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), __VA_ARGS__ )

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_METHOD_AS_TEST_CASE( QualifiedMethod, ... ) \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        namespace{ Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( &QualifiedMethod ), CATCH_INTERNAL_LINEINFO, "&" #QualifiedMethod, Catch::NameAndTags{ __VA_ARGS__ } ); } /* NOLINT */ \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_TEST_CASE_METHOD2( TestName, ClassName, ... )\
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        namespace{ \
            struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName) { \
                void test(); \
            }; \
            Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar ) ( Catch::makeTestInvoker( &TestName::test ), CATCH_INTERNAL_LINEINFO, #ClassName, Catch::NameAndTags{ __VA_ARGS__ } ); /* NOLINT */ \
        } \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        void TestName::test()
    #define INTERNAL_CATCH_TEST_CASE_METHOD( ClassName, ... ) \
        INTERNAL_CATCH_TEST_CASE_METHOD2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), ClassName, __VA_ARGS__ )

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_REGISTER_TESTCASE( Function, ... ) \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( Function ), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), Catch::NameAndTags{ __VA_ARGS__ } ); /* NOLINT */ \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_2(TestName, TestFunc, Name, Tags, Signature, ... )\
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
        INTERNAL_CATCH_DECLARE_SIG_TEST(TestFunc, INTERNAL_CATCH_REMOVE_PARENS(Signature));\
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName){\
            INTERNAL_CATCH_TYPE_GEN\
            INTERNAL_CATCH_NTTP_GEN(INTERNAL_CATCH_REMOVE_PARENS(Signature))\
            INTERNAL_CATCH_NTTP_REG_GEN(TestFunc,INTERNAL_CATCH_REMOVE_PARENS(Signature))\
            template<typename...Types> \
            struct TestName{\
                TestName(){\
                    int index = 0;                                    \
                    constexpr char const* tmpl_types[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, __VA_ARGS__)};\
                    using expander = int[];\
                    (void)expander{(reg_test(Types{}, Catch::NameAndTags{ Name " - " + std::string(tmpl_types[index]), Tags } ), index++, 0)... };/* NOLINT */ \
                }\
            };\
            static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){\
            TestName<INTERNAL_CATCH_MAKE_TYPE_LISTS_FROM_TYPES(__VA_ARGS__)>();\
            return 0;\
        }();\
        }\
        }\
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        INTERNAL_CATCH_DEFINE_SIG_TEST(TestFunc,INTERNAL_CATCH_REMOVE_PARENS(Signature))

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE(Name, Tags, ...) \
        INTERNAL_CATCH_TEMPLATE_TEST_CASE_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename TestType, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE(Name, Tags, ...) \
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename TestType, __VA_ARGS__ ) )
#endif

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG(Name, Tags, Signature, ...) \
        INTERNAL_CATCH_TEMPLATE_TEST_CASE_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG(Name, Tags, Signature, ...) \
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__ ) )
#endif

    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE2(TestName, TestFuncName, Name, Tags, Signature, TmplTypes, TypesList) \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION                      \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS                      \
        CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS                \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS              \
        template<typename TestType> static void TestFuncName();       \
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName) {                                     \
            INTERNAL_CATCH_TYPE_GEN                                                  \
            INTERNAL_CATCH_NTTP_GEN(INTERNAL_CATCH_REMOVE_PARENS(Signature))         \
            template<typename... Types>                               \
            struct TestName {                                         \
                void reg_tests() {                                          \
                    int index = 0;                                    \
                    using expander = int[];                           \
                    constexpr char const* tmpl_types[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, INTERNAL_CATCH_REMOVE_PARENS(TmplTypes))};\
                    constexpr char const* types_list[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, INTERNAL_CATCH_REMOVE_PARENS(TypesList))};\
                    constexpr auto num_types = sizeof(types_list) / sizeof(types_list[0]);\
                    (void)expander{(Catch::AutoReg( Catch::makeTestInvoker( &TestFuncName<Types> ), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), Catch::NameAndTags{ Name " - " + std::string(tmpl_types[index / num_types]) + "<" + std::string(types_list[index % num_types]) + ">", Tags } ), index++, 0)... };/* NOLINT */\
                }                                                     \
            };                                                        \
            static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){ \
                using TestInit = typename create<TestName, decltype(get_wrapper<INTERNAL_CATCH_REMOVE_PARENS(TmplTypes)>()), TypeList<INTERNAL_CATCH_MAKE_TYPE_LISTS_FROM_TYPES(INTERNAL_CATCH_REMOVE_PARENS(TypesList))>>::type; \
                TestInit t;                                           \
                t.reg_tests();                                        \
                return 0;                                             \
            }();                                                      \
        }                                                             \
        }                                                             \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION                       \
        template<typename TestType>                                   \
        static void TestFuncName()

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE(Name, Tags, ...)\
        INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE2(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename T,__VA_ARGS__)
#else
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE(Name, Tags, ...)\
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename T, __VA_ARGS__ ) )
#endif

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG(Name, Tags, Signature, ...)\
        INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE2(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__)
#else
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG(Name, Tags, Signature, ...)\
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__ ) )
#endif

    #define INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_2(TestName, TestFunc, Name, Tags, TmplList)\
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
        template<typename TestType> static void TestFunc();       \
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName){\
        INTERNAL_CATCH_TYPE_GEN\
        template<typename... Types>                               \
        struct TestName {                                         \
            void reg_tests() {                                          \
                int index = 0;                                    \
                using expander = int[];                           \
                (void)expander{(Catch::AutoReg( Catch::makeTestInvoker( &TestFunc<Types> ), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), Catch::NameAndTags{ Name " - " + std::string(INTERNAL_CATCH_STRINGIZE(TmplList)) + " - " + std::to_string(index), Tags } ), index++, 0)... };/* NOLINT */\
            }                                                     \
        };\
        static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){ \
                using TestInit = typename convert<TestName, TmplList>::type; \
                TestInit t;                                           \
                t.reg_tests();                                        \
                return 0;                                             \
            }();                                                      \
        }}\
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION                       \
        template<typename TestType>                                   \
        static void TestFunc()

    #define INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE(Name, Tags, TmplList) \
        INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, TmplList )

    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_2( TestNameClass, TestName, ClassName, Name, Tags, Signature, ... ) \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName){ \
            INTERNAL_CATCH_TYPE_GEN\
            INTERNAL_CATCH_NTTP_GEN(INTERNAL_CATCH_REMOVE_PARENS(Signature))\
            INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD(TestName, ClassName, INTERNAL_CATCH_REMOVE_PARENS(Signature));\
            INTERNAL_CATCH_NTTP_REG_METHOD_GEN(TestName, INTERNAL_CATCH_REMOVE_PARENS(Signature))\
            template<typename...Types> \
            struct TestNameClass{\
                TestNameClass(){\
                    int index = 0;                                    \
                    constexpr char const* tmpl_types[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, __VA_ARGS__)};\
                    using expander = int[];\
                    (void)expander{(reg_test(Types{}, #ClassName, Catch::NameAndTags{ Name " - " + std::string(tmpl_types[index]), Tags } ), index++, 0)... };/* NOLINT */ \
                }\
            };\
            static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){\
                TestNameClass<INTERNAL_CATCH_MAKE_TYPE_LISTS_FROM_TYPES(__VA_ARGS__)>();\
                return 0;\
        }();\
        }\
        }\
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD(TestName, INTERNAL_CATCH_REMOVE_PARENS(Signature))

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD( ClassName, Name, Tags,... ) \
        INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, typename T, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD( ClassName, Name, Tags,... ) \
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, typename T, __VA_ARGS__ ) )
#endif

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( ClassName, Name, Tags, Signature, ... ) \
        INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, Signature, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( ClassName, Name, Tags, Signature, ... ) \
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, Signature, __VA_ARGS__ ) )
#endif

    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_2(TestNameClass, TestName, ClassName, Name, Tags, Signature, TmplTypes, TypesList)\
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
        template<typename TestType> \
            struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName <TestType>) { \
                void test();\
            };\
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestNameClass) {\
            INTERNAL_CATCH_TYPE_GEN                  \
            INTERNAL_CATCH_NTTP_GEN(INTERNAL_CATCH_REMOVE_PARENS(Signature))\
            template<typename...Types>\
            struct TestNameClass{\
                void reg_tests(){\
                    int index = 0;\
                    using expander = int[];\
                    constexpr char const* tmpl_types[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, INTERNAL_CATCH_REMOVE_PARENS(TmplTypes))};\
                    constexpr char const* types_list[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, INTERNAL_CATCH_REMOVE_PARENS(TypesList))};\
                    constexpr auto num_types = sizeof(types_list) / sizeof(types_list[0]);\
                    (void)expander{(Catch::AutoReg( Catch::makeTestInvoker( &TestName<Types>::test ), CATCH_INTERNAL_LINEINFO, #ClassName, Catch::NameAndTags{ Name " - " + std::string(tmpl_types[index / num_types]) + "<" + std::string(types_list[index % num_types]) + ">", Tags } ), index++, 0)... };/* NOLINT */ \
                }\
            };\
            static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){\
                using TestInit = typename create<TestNameClass, decltype(get_wrapper<INTERNAL_CATCH_REMOVE_PARENS(TmplTypes)>()), TypeList<INTERNAL_CATCH_MAKE_TYPE_LISTS_FROM_TYPES(INTERNAL_CATCH_REMOVE_PARENS(TypesList))>>::type;\
                TestInit t;\
                t.reg_tests();\
                return 0;\
            }(); \
        }\
        }\
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        template<typename TestType> \
        void TestName<TestType>::test()

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( ClassName, Name, Tags, ... )\
        INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), ClassName, Name, Tags, typename T, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( ClassName, Name, Tags, ... )\
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), ClassName, Name, Tags, typename T,__VA_ARGS__ ) )
#endif

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( ClassName, Name, Tags, Signature, ... )\
        INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), ClassName, Name, Tags, Signature, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( ClassName, Name, Tags, Signature, ... )\
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), ClassName, Name, Tags, Signature,__VA_ARGS__ ) )
#endif

    #define INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_METHOD_2( TestNameClass, TestName, ClassName, Name, Tags, TmplList) \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
        template<typename TestType> \
        struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName <TestType>) { \
            void test();\
        };\
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName){ \
            INTERNAL_CATCH_TYPE_GEN\
            template<typename...Types>\
            struct TestNameClass{\
                void reg_tests(){\
                    int index = 0;\
                    using expander = int[];\
                    (void)expander{(Catch::AutoReg( Catch::makeTestInvoker( &TestName<Types>::test ), CATCH_INTERNAL_LINEINFO, #ClassName, Catch::NameAndTags{ Name " - " + std::string(INTERNAL_CATCH_STRINGIZE(TmplList)) + " - " + std::to_string(index), Tags } ), index++, 0)... };/* NOLINT */ \
                }\
            };\
            static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){\
                using TestInit = typename convert<TestNameClass, TmplList>::type;\
                TestInit t;\
                t.reg_tests();\
                return 0;\
            }(); \
        }}\
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        template<typename TestType> \
        void TestName<TestType>::test()

#define INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_METHOD(ClassName, Name, Tags, TmplList) \
        INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), ClassName, Name, Tags, TmplList )

// end catch_test_registry.h
// start catch_capture.hpp

// start catch_assertionhandler.h

// start catch_assertioninfo.h

// start catch_result_type.h

namespace Catch {

    // ResultWas::OfType enum
    struct ResultWas { enum OfType {
        Unknown = -1,
        Ok = 0,
        Info = 1,
        Warning = 2,

        FailureBit = 0x10,

        ExpressionFailed = FailureBit | 1,
        ExplicitFailure = FailureBit | 2,

        Exception = 0x100 | FailureBit,

        ThrewException = Exception | 1,
        DidntThrowException = Exception | 2,

        FatalErrorCondition = 0x200 | FailureBit

    }; };

    bool isOk( ResultWas::OfType resultType );
    bool isJustInfo( int flags );

    // ResultDisposition::Flags enum
    struct ResultDisposition { enum Flags {
        Normal = 0x01,

        ContinueOnFailure = 0x02,   // Failures fail test, but execution continues
        FalseTest = 0x04,           // Prefix expression with !
        SuppressFail = 0x08         // Failures are reported but do not fail the test
    }; };

    ResultDisposition::Flags operator | ( ResultDisposition::Flags lhs, ResultDisposition::Flags rhs );

    bool shouldContinueOnFailure( int flags );
    inline bool isFalseTest( int flags ) { return ( flags & ResultDisposition::FalseTest ) != 0; }
    bool shouldSuppressFailure( int flags );

} // end namespace Catch

// end catch_result_type.h
namespace Catch {

    struct AssertionInfo
    {
        StringRef macroName;
        SourceLineInfo lineInfo;
        StringRef capturedExpression;
        ResultDisposition::Flags resultDisposition;

        // We want to delete this constructor but a compiler bug in 4.8 means
        // the struct is then treated as non-aggregate
        //AssertionInfo() = delete;
    };

} // end namespace Catch

// end catch_assertioninfo.h
// start catch_decomposer.h

// start catch_tostring.h

#include <vector>
#include <cstddef>
#include <type_traits>
#include <string>
// start catch_stream.h

#include <iosfwd>
#include <cstddef>
#include <ostream>

namespace Catch {

    std::ostream& cout();
    std::ostream& cerr();
    std::ostream& clog();

    class StringRef;

    struct IStream {
        virtual ~IStream();
        virtual std::ostream& stream() const = 0;
    };

    auto makeStream( StringRef const &filename ) -> IStream const*;

    class ReusableStringStream : NonCopyable {
        std::size_t m_index;
        std::ostream* m_oss;
    public:
        ReusableStringStream();
        ~ReusableStringStream();

        auto str() const -> std::string;

        template<typename T>
        auto operator << ( T const& value ) -> ReusableStringStream& {
            *m_oss << value;
            return *this;
        }
        auto get() -> std::ostream& { return *m_oss; }
    };
}

// end catch_stream.h
// start catch_interfaces_enum_values_registry.h

#include <vector>

namespace Catch {

    namespace Detail {
        struct EnumInfo {
            StringRef m_name;
            std::vector<std::pair<int, StringRef>> m_values;

            ~EnumInfo();

            StringRef lookup( int value ) const;
        };
    } // namespace Detail

    struct IMutableEnumValuesRegistry {
        virtual ~IMutableEnumValuesRegistry();

        virtual Detail::EnumInfo const& registerEnum( StringRef enumName, StringRef allEnums, std::vector<int> const& values ) = 0;

        template<typename E>
        Detail::EnumInfo const& registerEnum( StringRef enumName, StringRef allEnums, std::initializer_list<E> values ) {
            static_assert(sizeof(int) >= sizeof(E), "Cannot serialize enum to int");
            std::vector<int> intValues;
            intValues.reserve( values.size() );
            for( auto enumValue : values )
                intValues.push_back( static_cast<int>( enumValue ) );
            return registerEnum( enumName, allEnums, intValues );
        }
    };

} // Catch

// end catch_interfaces_enum_values_registry.h

#ifdef CATCH_CONFIG_CPP17_STRING_VIEW
#include <string_view>
#endif

#ifdef __OBJC__
// start catch_objc_arc.hpp

#import <Foundation/Foundation.h>

#ifdef __has_feature
#define CATCH_ARC_ENABLED __has_feature(objc_arc)
#else
#define CATCH_ARC_ENABLED 0
#endif

void arcSafeRelease( NSObject* obj );
id performOptionalSelector( id obj, SEL sel );

#if !CATCH_ARC_ENABLED
inline void arcSafeRelease( NSObject* obj ) {
    [obj release];
}
inline id performOptionalSelector( id obj, SEL sel ) {
    if( [obj respondsToSelector: sel] )
        return [obj performSelector: sel];
    return nil;
}
#define CATCH_UNSAFE_UNRETAINED
#define CATCH_ARC_STRONG
#else
inline void arcSafeRelease( NSObject* ){}
inline id performOptionalSelector( id obj, SEL sel ) {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
#endif
    if( [obj respondsToSelector: sel] )
        return [obj performSelector: sel];
#ifdef __clang__
#pragma clang diagnostic pop
#endif
    return nil;
}
#define CATCH_UNSAFE_UNRETAINED __unsafe_unretained
#define CATCH_ARC_STRONG __strong
#endif

// end catch_objc_arc.hpp
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4180) // We attempt to stream a function (address) by const&, which MSVC complains about but is harmless
#endif

namespace Catch {
    namespace Detail {

        extern const std::string unprintableString;

        std::string rawMemoryToString( const void *object, std::size_t size );

        template<typename T>
        std::string rawMemoryToString( const T& object ) {
          return rawMemoryToString( &object, sizeof(object) );
        }

        template<typename T>
        class IsStreamInsertable {
            template<typename Stream, typename U>
            static auto test(int)
                -> decltype(std::declval<Stream&>() << std::declval<U>(), std::true_type());

            template<typename, typename>
            static auto test(...)->std::false_type;

        public:
            static const bool value = decltype(test<std::ostream, const T&>(0))::value;
        };

        template<typename E>
        std::string convertUnknownEnumToString( E e );

        template<typename T>
        typename std::enable_if<
            !std::is_enum<T>::value && !std::is_base_of<std::exception, T>::value,
        std::string>::type convertUnstreamable( T const& ) {
            return Detail::unprintableString;
        }
        template<typename T>
        typename std::enable_if<
            !std::is_enum<T>::value && std::is_base_of<std::exception, T>::value,
         std::string>::type convertUnstreamable(T const& ex) {
            return ex.what();
        }

        template<typename T>
        typename std::enable_if<
            std::is_enum<T>::value
        , std::string>::type convertUnstreamable( T const& value ) {
            return convertUnknownEnumToString( value );
        }

#if defined(_MANAGED)
        //! Convert a CLR string to a utf8 std::string
        template<typename T>
        std::string clrReferenceToString( T^ ref ) {
            if (ref == nullptr)
                return std::string("null");
            auto bytes = System::Text::Encoding::UTF8->GetBytes(ref->ToString());
            cli::pin_ptr<System::Byte> p = &bytes[0];
            return std::string(reinterpret_cast<char const *>(p), bytes->Length);
        }
#endif

    } // namespace Detail

    // If we decide for C++14, change these to enable_if_ts
    template <typename T, typename = void>
    struct StringMaker {
        template <typename Fake = T>
        static
        typename std::enable_if<::Catch::Detail::IsStreamInsertable<Fake>::value, std::string>::type
            convert(const Fake& value) {
                ReusableStringStream rss;
                // NB: call using the function-like syntax to avoid ambiguity with
                // user-defined templated operator<< under clang.
                rss.operator<<(value);
                return rss.str();
        }

        template <typename Fake = T>
        static
        typename std::enable_if<!::Catch::Detail::IsStreamInsertable<Fake>::value, std::string>::type
            convert( const Fake& value ) {
#if !defined(CATCH_CONFIG_FALLBACK_STRINGIFIER)
            return Detail::convertUnstreamable(value);
#else
            return CATCH_CONFIG_FALLBACK_STRINGIFIER(value);
#endif
        }
    };

    namespace Detail {

        // This function dispatches all stringification requests inside of Catch.
        // Should be preferably called fully qualified, like ::Catch::Detail::stringify
        template <typename T>
        std::string stringify(const T& e) {
            return ::Catch::StringMaker<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::convert(e);
        }

        template<typename E>
        std::string convertUnknownEnumToString( E e ) {
            return ::Catch::Detail::stringify(static_cast<typename std::underlying_type<E>::type>(e));
        }

#if defined(_MANAGED)
        template <typename T>
        std::string stringify( T^ e ) {
            return ::Catch::StringMaker<T^>::convert(e);
        }
#endif

    } // namespace Detail

    // Some predefined specializations

    template<>
    struct StringMaker<std::string> {
        static std::string convert(const std::string& str);
    };

#ifdef CATCH_CONFIG_CPP17_STRING_VIEW
    template<>
    struct StringMaker<std::string_view> {
        static std::string convert(std::string_view str);
    };
#endif

    template<>
    struct StringMaker<char const *> {
        static std::string convert(char const * str);
    };
    template<>
    struct StringMaker<char *> {
        static std::string convert(char * str);
    };

#ifdef CATCH_CONFIG_WCHAR
    template<>
    struct StringMaker<std::wstring> {
        static std::string convert(const std::wstring& wstr);
    };

# ifdef CATCH_CONFIG_CPP17_STRING_VIEW
    template<>
    struct StringMaker<std::wstring_view> {
        static std::string convert(std::wstring_view str);
    };
# endif

    template<>
    struct StringMaker<wchar_t const *> {
        static std::string convert(wchar_t const * str);
    };
    template<>
    struct StringMaker<wchar_t *> {
        static std::string convert(wchar_t * str);
    };
#endif

    // TBD: Should we use `strnlen` to ensure that we don't go out of the buffer,
    //      while keeping string semantics?
    template<int SZ>
    struct StringMaker<char[SZ]> {
        static std::string convert(char const* str) {
            return ::Catch::Detail::stringify(std::string{ str });
        }
    };
    template<int SZ>
    struct StringMaker<signed char[SZ]> {
        static std::string convert(signed char const* str) {
            return ::Catch::Detail::stringify(std::string{ reinterpret_cast<char const *>(str) });
        }
    };
    template<int SZ>
    struct StringMaker<unsigned char[SZ]> {
        static std::string convert(unsigned char const* str) {
            return ::Catch::Detail::stringify(std::string{ reinterpret_cast<char const *>(str) });
        }
    };

#if defined(CATCH_CONFIG_CPP17_BYTE)
    template<>
    struct StringMaker<std::byte> {
        static std::string convert(std::byte value);
    };
#endif // defined(CATCH_CONFIG_CPP17_BYTE)
    template<>
    struct StringMaker<int> {
        static std::string convert(int value);
    };
    template<>
    struct StringMaker<long> {
        static std::string convert(long value);
    };
    template<>
    struct StringMaker<long long> {
        static std::string convert(long long value);
    };
    template<>
    struct StringMaker<unsigned int> {
        static std::string convert(unsigned int value);
    };
    template<>
    struct StringMaker<unsigned long> {
        static std::string convert(unsigned long value);
    };
    template<>
    struct StringMaker<unsigned long long> {
        static std::string convert(unsigned long long value);
    };

    template<>
    struct StringMaker<bool> {
        static std::string convert(bool b);
    };

    template<>
    struct StringMaker<char> {
        static std::string convert(char c);
    };
    template<>
    struct StringMaker<signed char> {
        static std::string convert(signed char c);
    };
    template<>
    struct StringMaker<unsigned char> {
        static std::string convert(unsigned char c);
    };

    template<>
    struct StringMaker<std::nullptr_t> {
        static std::string convert(std::nullptr_t);
    };

    template<>
    struct StringMaker<float> {
        static std::string convert(float value);
        static int precision;
    };

    template<>
    struct StringMaker<double> {
        static std::string convert(double value);
        static int precision;
    };

    template <typename T>
    struct StringMaker<T*> {
        template <typename U>
        static std::string convert(U* p) {
            if (p) {
                return ::Catch::Detail::rawMemoryToString(p);
            } else {
                return "nullptr";
            }
        }
    };

    template <typename R, typename C>
    struct StringMaker<R C::*> {
        static std::string convert(R C::* p) {
            if (p) {
                return ::Catch::Detail::rawMemoryToString(p);
            } else {
                return "nullptr";
            }
        }
    };

#if defined(_MANAGED)
    template <typename T>
    struct StringMaker<T^> {
        static std::string convert( T^ ref ) {
            return ::Catch::Detail::clrReferenceToString(ref);
        }
    };
#endif

    namespace Detail {
        template<typename InputIterator>
        std::string rangeToString(InputIterator first, InputIterator last) {
            ReusableStringStream rss;
            rss << "{ ";
            if (first != last) {
                rss << ::Catch::Detail::stringify(*first);
                for (++first; first != last; ++first)
                    rss << ", " << ::Catch::Detail::stringify(*first);
            }
            rss << " }";
            return rss.str();
        }
    }

#ifdef __OBJC__
    template<>
    struct StringMaker<NSString*> {
        static std::string convert(NSString * nsstring) {
            if (!nsstring)
                return "nil";
            return std::string("@") + [nsstring UTF8String];
        }
    };
    template<>
    struct StringMaker<NSObject*> {
        static std::string convert(NSObject* nsObject) {
            return ::Catch::Detail::stringify([nsObject description]);
        }

    };
    namespace Detail {
        inline std::string stringify( NSString* nsstring ) {
            return StringMaker<NSString*>::convert( nsstring );
        }

    } // namespace Detail
#endif // __OBJC__

} // namespace Catch

//////////////////////////////////////////////////////
// Separate std-lib types stringification, so it can be selectively enabled
// This means that we do not bring in

#if defined(CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS)
#  define CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER
#  define CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER
#  define CATCH_CONFIG_ENABLE_VARIANT_STRINGMAKER
#  define CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER
#  define CATCH_CONFIG_ENABLE_OPTIONAL_STRINGMAKER
#endif

// Separate std::pair specialization
#if defined(CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER)
#include <utility>
namespace Catch {
    template<typename T1, typename T2>
    struct StringMaker<std::pair<T1, T2> > {
        static std::string convert(const std::pair<T1, T2>& pair) {
            ReusableStringStream rss;
            rss << "{ "
                << ::Catch::Detail::stringify(pair.first)
                << ", "
                << ::Catch::Detail::stringify(pair.second)
                << " }";
            return rss.str();
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER

#if defined(CATCH_CONFIG_ENABLE_OPTIONAL_STRINGMAKER) && defined(CATCH_CONFIG_CPP17_OPTIONAL)
#include <optional>
namespace Catch {
    template<typename T>
    struct StringMaker<std::optional<T> > {
        static std::string convert(const std::optional<T>& optional) {
            ReusableStringStream rss;
            if (optional.has_value()) {
                rss << ::Catch::Detail::stringify(*optional);
            } else {
                rss << "{ }";
            }
            return rss.str();
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_OPTIONAL_STRINGMAKER

// Separate std::tuple specialization
#if defined(CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER)
#include <tuple>
namespace Catch {
    namespace Detail {
        template<
            typename Tuple,
            std::size_t N = 0,
            bool = (N < std::tuple_size<Tuple>::value)
            >
            struct TupleElementPrinter {
            static void print(const Tuple& tuple, std::ostream& os) {
                os << (N ? ", " : " ")
                    << ::Catch::Detail::stringify(std::get<N>(tuple));
                TupleElementPrinter<Tuple, N + 1>::print(tuple, os);
            }
        };

        template<
            typename Tuple,
            std::size_t N
        >
            struct TupleElementPrinter<Tuple, N, false> {
            static void print(const Tuple&, std::ostream&) {}
        };

    }

    template<typename ...Types>
    struct StringMaker<std::tuple<Types...>> {
        static std::string convert(const std::tuple<Types...>& tuple) {
            ReusableStringStream rss;
            rss << '{';
            Detail::TupleElementPrinter<std::tuple<Types...>>::print(tuple, rss.get());
            rss << " }";
            return rss.str();
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER

#if defined(CATCH_CONFIG_ENABLE_VARIANT_STRINGMAKER) && defined(CATCH_CONFIG_CPP17_VARIANT)
#include <variant>
namespace Catch {
    template<>
    struct StringMaker<std::monostate> {
        static std::string convert(const std::monostate&) {
            return "{ }";
        }
    };

    template<typename... Elements>
    struct StringMaker<std::variant<Elements...>> {
        static std::string convert(const std::variant<Elements...>& variant) {
            if (variant.valueless_by_exception()) {
                return "{valueless variant}";
            } else {
                return std::visit(
                    [](const auto& value) {
                        return ::Catch::Detail::stringify(value);
                    },
                    variant
                );
            }
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_VARIANT_STRINGMAKER

namespace Catch {
    // Import begin/ end from std here
    using std::begin;
    using std::end;

    namespace detail {
        template <typename...>
        struct void_type {
            using type = void;
        };

        template <typename T, typename = void>
        struct is_range_impl : std::false_type {
        };

        template <typename T>
        struct is_range_impl<T, typename void_type<decltype(begin(std::declval<T>()))>::type> : std::true_type {
        };
    } // namespace detail

    template <typename T>
    struct is_range : detail::is_range_impl<T> {
    };

#if defined(_MANAGED) // Managed types are never ranges
    template <typename T>
    struct is_range<T^> {
        static const bool value = false;
    };
#endif

    template<typename Range>
    std::string rangeToString( Range const& range ) {
        return ::Catch::Detail::rangeToString( begin( range ), end( range ) );
    }

    // Handle vector<bool> specially
    template<typename Allocator>
    std::string rangeToString( std::vector<bool, Allocator> const& v ) {
        ReusableStringStream rss;
        rss << "{ ";
        bool first = true;
        for( bool b : v ) {
            if( first )
                first = false;
            else
                rss << ", ";
            rss << ::Catch::Detail::stringify( b );
        }
        rss << " }";
        return rss.str();
    }

    template<typename R>
    struct StringMaker<R, typename std::enable_if<is_range<R>::value && !::Catch::Detail::IsStreamInsertable<R>::value>::type> {
        static std::string convert( R const& range ) {
            return rangeToString( range );
        }
    };

    template <typename T, int SZ>
    struct StringMaker<T[SZ]> {
        static std::string convert(T const(&arr)[SZ]) {
            return rangeToString(arr);
        }
    };

} // namespace Catch

// Separate std::chrono::duration specialization
#if defined(CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER)
#include <ctime>
#include <ratio>
#include <chrono>

namespace Catch {

template <class Ratio>
struct ratio_string {
    static std::string symbol();
};

template <class Ratio>
std::string ratio_string<Ratio>::symbol() {
    Catch::ReusableStringStream rss;
    rss << '[' << Ratio::num << '/'
        << Ratio::den << ']';
    return rss.str();
}
template <>
struct ratio_string<std::atto> {
    static std::string symbol();
};
template <>
struct ratio_string<std::femto> {
    static std::string symbol();
};
template <>
struct ratio_string<std::pico> {
    static std::string symbol();
};
template <>
struct ratio_string<std::nano> {
    static std::string symbol();
};
template <>
struct ratio_string<std::micro> {
    static std::string symbol();
};
template <>
struct ratio_string<std::milli> {
    static std::string symbol();
};

    ////////////
    // std::chrono::duration specializations
    template<typename Value, typename Ratio>
    struct StringMaker<std::chrono::duration<Value, Ratio>> {
        static std::string convert(std::chrono::duration<Value, Ratio> const& duration) {
            ReusableStringStream rss;
            rss << duration.count() << ' ' << ratio_string<Ratio>::symbol() << 's';
            return rss.str();
        }
    };
    template<typename Value>
    struct StringMaker<std::chrono::duration<Value, std::ratio<1>>> {
        static std::string convert(std::chrono::duration<Value, std::ratio<1>> const& duration) {
            ReusableStringStream rss;
            rss << duration.count() << " s";
            return rss.str();
        }
    };
    template<typename Value>
    struct StringMaker<std::chrono::duration<Value, std::ratio<60>>> {
        static std::string convert(std::chrono::duration<Value, std::ratio<60>> const& duration) {
            ReusableStringStream rss;
            rss << duration.count() << " m";
            return rss.str();
        }
    };
    template<typename Value>
    struct StringMaker<std::chrono::duration<Value, std::ratio<3600>>> {
        static std::string convert(std::chrono::duration<Value, std::ratio<3600>> const& duration) {
            ReusableStringStream rss;
            rss << duration.count() << " h";
            return rss.str();
        }
    };

    ////////////
    // std::chrono::time_point specialization
    // Generic time_point cannot be specialized, only std::chrono::time_point<system_clock>
    template<typename Clock, typename Duration>
    struct StringMaker<std::chrono::time_point<Clock, Duration>> {
        static std::string convert(std::chrono::time_point<Clock, Duration> const& time_point) {
            return ::Catch::Detail::stringify(time_point.time_since_epoch()) + " since epoch";
        }
    };
    // std::chrono::time_point<system_clock> specialization
    template<typename Duration>
    struct StringMaker<std::chrono::time_point<std::chrono::system_clock, Duration>> {
        static std::string convert(std::chrono::time_point<std::chrono::system_clock, Duration> const& time_point) {
            auto converted = std::chrono::system_clock::to_time_t(time_point);

#ifdef _MSC_VER
            std::tm timeInfo = {};
            gmtime_s(&timeInfo, &converted);
#else
            std::tm* timeInfo = std::gmtime(&converted);
#endif

            auto const timeStampSize = sizeof("2017-01-16T17:06:45Z");
            char timeStamp[timeStampSize];
            const char * const fmt = "%Y-%m-%dT%H:%M:%SZ";

#ifdef _MSC_VER
            std::strftime(timeStamp, timeStampSize, fmt, &timeInfo);
#else
            std::strftime(timeStamp, timeStampSize, fmt, timeInfo);
#endif
            return std::string(timeStamp);
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER

#define INTERNAL_CATCH_REGISTER_ENUM( enumName, ... ) \
namespace Catch { \
    template<> struct StringMaker<enumName> { \
        static std::string convert( enumName value ) { \
            static const auto& enumInfo = ::Catch::getMutableRegistryHub().getMutableEnumValuesRegistry().registerEnum( #enumName, #__VA_ARGS__, { __VA_ARGS__ } ); \
            return static_cast<std::string>(enumInfo.lookup( static_cast<int>( value ) )); \
        } \
    }; \
}

#define CATCH_REGISTER_ENUM( enumName, ... ) INTERNAL_CATCH_REGISTER_ENUM( enumName, __VA_ARGS__ )

#ifdef _MSC_VER
#pragma warning(pop)
#endif

// end catch_tostring.h
#include <iosfwd>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4389) // '==' : signed/unsigned mismatch
#pragma warning(disable:4018) // more "signed/unsigned mismatch"
#pragma warning(disable:4312) // Converting int to T* using reinterpret_cast (issue on x64 platform)
#pragma warning(disable:4180) // qualifier applied to function type has no meaning
#pragma warning(disable:4800) // Forcing result to true or false
#endif

namespace Catch {

    struct ITransientExpression {
        auto isBinaryExpression() const -> bool { return m_isBinaryExpression; }
        auto getResult() const -> bool { return m_result; }
        virtual void streamReconstructedExpression( std::ostream &os ) const = 0;

        ITransientExpression( bool isBinaryExpression, bool result )
        :   m_isBinaryExpression( isBinaryExpression ),
            m_result( result )
        {}

        // We don't actually need a virtual destructor, but many static analysers
        // complain if it's not here :-(
        virtual ~ITransientExpression();

        bool m_isBinaryExpression;
        bool m_result;

    };

    void formatReconstructedExpression( std::ostream &os, std::string const& lhs, StringRef op, std::string const& rhs );

    template<typename LhsT, typename RhsT>
    class BinaryExpr  : public ITransientExpression {
        LhsT m_lhs;
        StringRef m_op;
        RhsT m_rhs;

        void streamReconstructedExpression( std::ostream &os ) const override {
            formatReconstructedExpression
                    ( os, Catch::Detail::stringify( m_lhs ), m_op, Catch::Detail::stringify( m_rhs ) );
        }

    public:
        BinaryExpr( bool comparisonResult, LhsT lhs, StringRef op, RhsT rhs )
        :   ITransientExpression{ true, comparisonResult },
            m_lhs( lhs ),
            m_op( op ),
            m_rhs( rhs )
        {}

        template<typename T>
        auto operator && ( T ) const -> BinaryExpr<LhsT, RhsT const&> const {
            static_assert(always_false<T>::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template<typename T>
        auto operator || ( T ) const -> BinaryExpr<LhsT, RhsT const&> const {
            static_assert(always_false<T>::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template<typename T>
        auto operator == ( T ) const -> BinaryExpr<LhsT, RhsT const&> const {
            static_assert(always_false<T>::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template<typename T>
        auto operator != ( T ) const -> BinaryExpr<LhsT, RhsT const&> const {
            static_assert(always_false<T>::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template<typename T>
        auto operator > ( T ) const -> BinaryExpr<LhsT, RhsT const&> const {
            static_assert(always_false<T>::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template<typename T>
        auto operator < ( T ) const -> BinaryExpr<LhsT, RhsT const&> const {
            static_assert(always_false<T>::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template<typename T>
        auto operator >= ( T ) const -> BinaryExpr<LhsT, RhsT const&> const {
            static_assert(always_false<T>::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template<typename T>
        auto operator <= ( T ) const -> BinaryExpr<LhsT, RhsT const&> const {
            static_assert(always_false<T>::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }
    };

    template<typename LhsT>
    class UnaryExpr : public ITransientExpression {
        LhsT m_lhs;

        void streamReconstructedExpression( std::ostream &os ) const override {
            os << Catch::Detail::stringify( m_lhs );
        }

    public:
        explicit UnaryExpr( LhsT lhs )
        :   ITransientExpression{ false, static_cast<bool>(lhs) },
            m_lhs( lhs )
        {}
    };

    // Specialised comparison functions to handle equality comparisons between ints and pointers (NULL deduces as an int)
    template<typename LhsT, typename RhsT>
    auto compareEqual( LhsT const& lhs, RhsT const& rhs ) -> bool { return static_cast<bool>(lhs == rhs); }
    template<typename T>
    auto compareEqual( T* const& lhs, int rhs ) -> bool { return lhs == reinterpret_cast<void const*>( rhs ); }
    template<typename T>
    auto compareEqual( T* const& lhs, long rhs ) -> bool { return lhs == reinterpret_cast<void const*>( rhs ); }
    template<typename T>
    auto compareEqual( int lhs, T* const& rhs ) -> bool { return reinterpret_cast<void const*>( lhs ) == rhs; }
    template<typename T>
    auto compareEqual( long lhs, T* const& rhs ) -> bool { return reinterpret_cast<void const*>( lhs ) == rhs; }

    template<typename LhsT, typename RhsT>
    auto compareNotEqual( LhsT const& lhs, RhsT&& rhs ) -> bool { return static_cast<bool>(lhs != rhs); }
    template<typename T>
    auto compareNotEqual( T* const& lhs, int rhs ) -> bool { return lhs != reinterpret_cast<void const*>( rhs ); }
    template<typename T>
    auto compareNotEqual( T* const& lhs, long rhs ) -> bool { return lhs != reinterpret_cast<void const*>( rhs ); }
    template<typename T>
    auto compareNotEqual( int lhs, T* const& rhs ) -> bool { return reinterpret_cast<void const*>( lhs ) != rhs; }
    template<typename T>
    auto compareNotEqual( long lhs, T* const& rhs ) -> bool { return reinterpret_cast<void const*>( lhs ) != rhs; }

    template<typename LhsT>
    class ExprLhs {
        LhsT m_lhs;
    public:
        explicit ExprLhs( LhsT lhs ) : m_lhs( lhs ) {}

        template<typename RhsT>
        auto operator == ( RhsT const& rhs ) -> BinaryExpr<LhsT, RhsT const&> const {
            return { compareEqual( m_lhs, rhs ), m_lhs, "==", rhs };
        }
        auto operator == ( bool rhs ) -> BinaryExpr<LhsT, bool> const {
            return { m_lhs == rhs, m_lhs, "==", rhs };
        }

        template<typename RhsT>
        auto operator != ( RhsT const& rhs ) -> BinaryExpr<LhsT, RhsT const&> const {
            return { compareNotEqual( m_lhs, rhs ), m_lhs, "!=", rhs };
        }
        auto operator != ( bool rhs ) -> BinaryExpr<LhsT, bool> const {
            return { m_lhs != rhs, m_lhs, "!=", rhs };
        }

        template<typename RhsT>
        auto operator > ( RhsT const& rhs ) -> BinaryExpr<LhsT, RhsT const&> const {
            return { static_cast<bool>(m_lhs > rhs), m_lhs, ">", rhs };
        }
        template<typename RhsT>
        auto operator < ( RhsT const& rhs ) -> BinaryExpr<LhsT, RhsT const&> const {
            return { static_cast<bool>(m_lhs < rhs), m_lhs, "<", rhs };
        }
        template<typename RhsT>
        auto operator >= ( RhsT const& rhs ) -> BinaryExpr<LhsT, RhsT const&> const {
            return { static_cast<bool>(m_lhs >= rhs), m_lhs, ">=", rhs };
        }
        template<typename RhsT>
        auto operator <= ( RhsT const& rhs ) -> BinaryExpr<LhsT, RhsT const&> const {
            return { static_cast<bool>(m_lhs <= rhs), m_lhs, "<=", rhs };
        }
        template <typename RhsT>
        auto operator | (RhsT const& rhs) -> BinaryExpr<LhsT, RhsT const&> const {
            return { static_cast<bool>(m_lhs | rhs), m_lhs, "|", rhs };
        }
        template <typename RhsT>
        auto operator & (RhsT const& rhs) -> BinaryExpr<LhsT, RhsT const&> const {
            return { static_cast<bool>(m_lhs & rhs), m_lhs, "&", rhs };
        }
        template <typename RhsT>
        auto operator ^ (RhsT const& rhs) -> BinaryExpr<LhsT, RhsT const&> const {
            return { static_cast<bool>(m_lhs ^ rhs), m_lhs, "^", rhs };
        }

        template<typename RhsT>
        auto operator && ( RhsT const& ) -> BinaryExpr<LhsT, RhsT const&> const {
            static_assert(always_false<RhsT>::value,
            "operator&& is not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template<typename RhsT>
        auto operator || ( RhsT const& ) -> BinaryExpr<LhsT, RhsT const&> const {
            static_assert(always_false<RhsT>::value,
            "operator|| is not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        auto makeUnaryExpr() const -> UnaryExpr<LhsT> {
            return UnaryExpr<LhsT>{ m_lhs };
        }
    };

    void handleExpression( ITransientExpression const& expr );

    template<typename T>
    void handleExpression( ExprLhs<T> const& expr ) {
        handleExpression( expr.makeUnaryExpr() );
    }

    struct Decomposer {
        template<typename T>
        auto operator <= ( T const& lhs ) -> ExprLhs<T const&> {
            return ExprLhs<T const&>{ lhs };
        }

        auto operator <=( bool value ) -> ExprLhs<bool> {
            return ExprLhs<bool>{ value };
        }
    };

} // end namespace Catch

#ifdef _MSC_VER
#pragma warning(pop)
#endif

// end catch_decomposer.h
// start catch_interfaces_capture.h

#include <string>
#include <chrono>

namespace Catch {

    class AssertionResult;
    struct AssertionInfo;
    struct SectionInfo;
    struct SectionEndInfo;
    struct MessageInfo;
    struct MessageBuilder;
    struct Counts;
    struct AssertionReaction;
    struct SourceLineInfo;

    struct ITransientExpression;
    struct IGeneratorTracker;

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
    struct BenchmarkInfo;
    template <typename Duration = std::chrono::duration<double, std::nano>>
    struct BenchmarkStats;
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

    struct IResultCapture {

        virtual ~IResultCapture();

        virtual bool sectionStarted(    SectionInfo const& sectionInfo,
                                        Counts& assertions ) = 0;
        virtual void sectionEnded( SectionEndInfo const& endInfo ) = 0;
        virtual void sectionEndedEarly( SectionEndInfo const& endInfo ) = 0;

        virtual auto acquireGeneratorTracker( StringRef generatorName, SourceLineInfo const& lineInfo ) -> IGeneratorTracker& = 0;

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
        virtual void benchmarkPreparing( std::string const& name ) = 0;
        virtual void benchmarkStarting( BenchmarkInfo const& info ) = 0;
        virtual void benchmarkEnded( BenchmarkStats<> const& stats ) = 0;
        virtual void benchmarkFailed( std::string const& error ) = 0;
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

        virtual void pushScopedMessage( MessageInfo const& message ) = 0;
        virtual void popScopedMessage( MessageInfo const& message ) = 0;

        virtual void emplaceUnscopedMessage( MessageBuilder const& builder ) = 0;

        virtual void handleFatalErrorCondition( StringRef message ) = 0;

        virtual void handleExpr
                (   AssertionInfo const& info,
                    ITransientExpression const& expr,
                    AssertionReaction& reaction ) = 0;
        virtual void handleMessage
                (   AssertionInfo const& info,
                    ResultWas::OfType resultType,
                    StringRef const& message,
                    AssertionReaction& reaction ) = 0;
        virtual void handleUnexpectedExceptionNotThrown
                (   AssertionInfo const& info,
                    AssertionReaction& reaction ) = 0;
        virtual void handleUnexpectedInflightException
                (   AssertionInfo const& info,
                    std::string const& message,
                    AssertionReaction& reaction ) = 0;
        virtual void handleIncomplete
                (   AssertionInfo const& info ) = 0;
        virtual void handleNonExpr
                (   AssertionInfo const &info,
                    ResultWas::OfType resultType,
                    AssertionReaction &reaction ) = 0;

        virtual bool lastAssertionPassed() = 0;
        virtual void assertionPassed() = 0;

        // Deprecated, do not use:
        virtual std::string getCurrentTestName() const = 0;
        virtual const AssertionResult* getLastResult() const = 0;
        virtual void exceptionEarlyReported() = 0;
    };

    IResultCapture& getResultCapture();
}

// end catch_interfaces_capture.h
namespace Catch {

    struct TestFailureException{};
    struct AssertionResultData;
    struct IResultCapture;
    class RunContext;

    class LazyExpression {
        friend class AssertionHandler;
        friend struct AssertionStats;
        friend class RunContext;

        ITransientExpression const* m_transientExpression = nullptr;
        bool m_isNegated;
    public:
        LazyExpression( bool isNegated );
        LazyExpression( LazyExpression const& other );
        LazyExpression& operator = ( LazyExpression const& ) = delete;

        explicit operator bool() const;

        friend auto operator << ( std::ostream& os, LazyExpression const& lazyExpr ) -> std::ostream&;
    };

    struct AssertionReaction {
        bool shouldDebugBreak = false;
        bool shouldThrow = false;
    };

    class AssertionHandler {
        AssertionInfo m_assertionInfo;
        AssertionReaction m_reaction;
        bool m_completed = false;
        IResultCapture& m_resultCapture;

    public:
        AssertionHandler
            (   StringRef const& macroName,
                SourceLineInfo const& lineInfo,
                StringRef capturedExpression,
                ResultDisposition::Flags resultDisposition );
        ~AssertionHandler() {
            if ( !m_completed ) {
                m_resultCapture.handleIncomplete( m_assertionInfo );
            }
        }

        template<typename T>
        void handleExpr( ExprLhs<T> const& expr ) {
            handleExpr( expr.makeUnaryExpr() );
        }
        void handleExpr( ITransientExpression const& expr );

        void handleMessage(ResultWas::OfType resultType, StringRef const& message);

        void handleExceptionThrownAsExpected();
        void handleUnexpectedExceptionNotThrown();
        void handleExceptionNotThrownAsExpected();
        void handleThrowingCallSkipped();
        void handleUnexpectedInflightException();

        void complete();
        void setCompleted();

        // query
        auto allowThrows() const -> bool;
    };

    void handleExceptionMatchExpr( AssertionHandler& handler, std::string const& str, StringRef const& matcherString );

} // namespace Catch

// end catch_assertionhandler.h
// start catch_message.h

#include <string>
#include <vector>

namespace Catch {

    struct MessageInfo {
        MessageInfo(    StringRef const& _macroName,
                        SourceLineInfo const& _lineInfo,
                        ResultWas::OfType _type );

        StringRef macroName;
        std::string message;
        SourceLineInfo lineInfo;
        ResultWas::OfType type;
        unsigned int sequence;

        bool operator == ( MessageInfo const& other ) const;
        bool operator < ( MessageInfo const& other ) const;
    private:
        static unsigned int globalCount;
    };

    struct MessageStream {

        template<typename T>
        MessageStream& operator << ( T const& value ) {
            m_stream << value;
            return *this;
        }

        ReusableStringStream m_stream;
    };

    struct MessageBuilder : MessageStream {
        MessageBuilder( StringRef const& macroName,
                        SourceLineInfo const& lineInfo,
                        ResultWas::OfType type );

        template<typename T>
        MessageBuilder& operator << ( T const& value ) {
            m_stream << value;
            return *this;
        }

        MessageInfo m_info;
    };

    class ScopedMessage {
    public:
        explicit ScopedMessage( MessageBuilder const& builder );
        ScopedMessage( ScopedMessage& duplicate ) = delete;
        ScopedMessage( ScopedMessage&& old );
        ~ScopedMessage();

        MessageInfo m_info;
        bool m_moved;
    };

    class Capturer {
        std::vector<MessageInfo> m_messages;
        IResultCapture& m_resultCapture = getResultCapture();
        size_t m_captured = 0;
    public:
        Capturer( StringRef macroName, SourceLineInfo const& lineInfo, ResultWas::OfType resultType, StringRef names );
        ~Capturer();

        void captureValue( size_t index, std::string const& value );

        template<typename T>
        void captureValues( size_t index, T const& value ) {
            captureValue( index, Catch::Detail::stringify( value ) );
        }

        template<typename T, typename... Ts>
        void captureValues( size_t index, T const& value, Ts const&... values ) {
            captureValue( index, Catch::Detail::stringify(value) );
            captureValues( index+1, values... );
        }
    };

} // end namespace Catch

// end catch_message.h
#if !defined(CATCH_CONFIG_DISABLE)

#if !defined(CATCH_CONFIG_DISABLE_STRINGIFICATION)
  #define CATCH_INTERNAL_STRINGIFY(...) #__VA_ARGS__
#else
  #define CATCH_INTERNAL_STRINGIFY(...) "Disabled by CATCH_CONFIG_DISABLE_STRINGIFICATION"
#endif

#if defined(CATCH_CONFIG_FAST_COMPILE) || defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)

///////////////////////////////////////////////////////////////////////////////
// Another way to speed-up compilation is to omit local try-catch for REQUIRE*
// macros.
#define INTERNAL_CATCH_TRY
#define INTERNAL_CATCH_CATCH( capturer )

#else // CATCH_CONFIG_FAST_COMPILE

#define INTERNAL_CATCH_TRY try
#define INTERNAL_CATCH_CATCH( handler ) catch(...) { handler.handleUnexpectedInflightException(); }

#endif

#define INTERNAL_CATCH_REACT( handler ) handler.complete();

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_TEST( macroName, resultDisposition, ... ) \
    do { \
        CATCH_INTERNAL_IGNORE_BUT_WARN(__VA_ARGS__); \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition ); \
        INTERNAL_CATCH_TRY { \
            CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
            CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS \
            catchAssertionHandler.handleExpr( Catch::Decomposer() <= __VA_ARGS__ ); \
            CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        } INTERNAL_CATCH_CATCH( catchAssertionHandler ) \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( (void)0, (false) && static_cast<bool>( !!(__VA_ARGS__) ) )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_IF( macroName, resultDisposition, ... ) \
    INTERNAL_CATCH_TEST( macroName, resultDisposition, __VA_ARGS__ ); \
    if( Catch::getResultCapture().lastAssertionPassed() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_ELSE( macroName, resultDisposition, ... ) \
    INTERNAL_CATCH_TEST( macroName, resultDisposition, __VA_ARGS__ ); \
    if( !Catch::getResultCapture().lastAssertionPassed() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_NO_THROW( macroName, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition ); \
        try { \
            static_cast<void>(__VA_ARGS__); \
            catchAssertionHandler.handleExceptionNotThrownAsExpected(); \
        } \
        catch( ... ) { \
            catchAssertionHandler.handleUnexpectedInflightException(); \
        } \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS( macroName, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast<void>(__VA_ARGS__); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( ... ) { \
                catchAssertionHandler.handleExceptionThrownAsExpected(); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_AS( macroName, exceptionType, resultDisposition, expr ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(expr) ", " CATCH_INTERNAL_STRINGIFY(exceptionType), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast<void>(expr); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( exceptionType const& ) { \
                catchAssertionHandler.handleExceptionThrownAsExpected(); \
            } \
            catch( ... ) { \
                catchAssertionHandler.handleUnexpectedInflightException(); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_MSG( macroName, messageType, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, Catch::StringRef(), resultDisposition ); \
        catchAssertionHandler.handleMessage( messageType, ( Catch::MessageStream() << __VA_ARGS__ + ::Catch::StreamEndStop() ).m_stream.str() ); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_CAPTURE( varName, macroName, ... ) \
    auto varName = Catch::Capturer( macroName, CATCH_INTERNAL_LINEINFO, Catch::ResultWas::Info, #__VA_ARGS__ ); \
    varName.captureValues( 0, __VA_ARGS__ )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_INFO( macroName, log ) \
    Catch::ScopedMessage INTERNAL_CATCH_UNIQUE_NAME( scopedMessage )( Catch::MessageBuilder( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, Catch::ResultWas::Info ) << log );

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_UNSCOPED_INFO( macroName, log ) \
    Catch::getResultCapture().emplaceUnscopedMessage( Catch::MessageBuilder( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, Catch::ResultWas::Info ) << log )

///////////////////////////////////////////////////////////////////////////////
// Although this is matcher-based, it can be used with just a string
#define INTERNAL_CATCH_THROWS_STR_MATCHES( macroName, resultDisposition, matcher, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__) ", " CATCH_INTERNAL_STRINGIFY(matcher), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast<void>(__VA_ARGS__); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( ... ) { \
                Catch::handleExceptionMatchExpr( catchAssertionHandler, matcher, #matcher##_catch_sr ); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

#endif // CATCH_CONFIG_DISABLE

// end catch_capture.hpp
// start catch_section.h

// start catch_section_info.h

// start catch_totals.h

#include <cstddef>

namespace Catch {

    struct Counts {
        Counts operator - ( Counts const& other ) const;
        Counts& operator += ( Counts const& other );

        std::size_t total() const;
        bool allPassed() const;
        bool allOk() const;

        std::size_t passed = 0;
        std::size_t failed = 0;
        std::size_t failedButOk = 0;
    };

    struct Totals {

        Totals operator - ( Totals const& other ) const;
        Totals& operator += ( Totals const& other );

        Totals delta( Totals const& prevTotals ) const;

        int error = 0;
        Counts assertions;
        Counts testCases;
    };
}

// end catch_totals.h
#include <string>

namespace Catch {

    struct SectionInfo {
        SectionInfo
            (   SourceLineInfo const& _lineInfo,
                std::string const& _name );

        // Deprecated
        SectionInfo
            (   SourceLineInfo const& _lineInfo,
                std::string const& _name,
                std::string const& ) : SectionInfo( _lineInfo, _name ) {}

        std::string name;
        std::string description; // !Deprecated: this will always be empty
        SourceLineInfo lineInfo;
    };

    struct SectionEndInfo {
        SectionInfo sectionInfo;
        Counts prevAssertions;
        double durationInSeconds;
    };

} // end namespace Catch

// end catch_section_info.h
// start catch_timer.h

#include <cstdint>

namespace Catch {

    auto getCurrentNanosecondsSinceEpoch() -> uint64_t;
    auto getEstimatedClockResolution() -> uint64_t;

    class Timer {
        uint64_t m_nanoseconds = 0;
    public:
        void start();
        auto getElapsedNanoseconds() const -> uint64_t;
        auto getElapsedMicroseconds() const -> uint64_t;
        auto getElapsedMilliseconds() const -> unsigned int;
        auto getElapsedSeconds() const -> double;
    };

} // namespace Catch

// end catch_timer.h
#include <string>

namespace Catch {

    class Section : NonCopyable {
    public:
        Section( SectionInfo const& info );
        ~Section();

        // This indicates whether the section should be executed or not
        explicit operator bool() const;

    private:
        SectionInfo m_info;

        std::string m_name;
        Counts m_assertions;
        bool m_sectionIncluded;
        Timer m_timer;
    };

} // end namespace Catch

#define INTERNAL_CATCH_SECTION( ... ) \
    CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
    CATCH_INTERNAL_SUPPRESS_UNUSED_WARNINGS \
    if( Catch::Section const& INTERNAL_CATCH_UNIQUE_NAME( catch_internal_Section ) = Catch::SectionInfo( CATCH_INTERNAL_LINEINFO, __VA_ARGS__ ) ) \
    CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

#define INTERNAL_CATCH_DYNAMIC_SECTION( ... ) \
    CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
    CATCH_INTERNAL_SUPPRESS_UNUSED_WARNINGS \
    if( Catch::Section const& INTERNAL_CATCH_UNIQUE_NAME( catch_internal_Section ) = Catch::SectionInfo( CATCH_INTERNAL_LINEINFO, (Catch::ReusableStringStream() << __VA_ARGS__).str() ) ) \
    CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

// end catch_section.h
// start catch_interfaces_exception.h

// start catch_interfaces_registry_hub.h

#include <string>
#include <memory>

namespace Catch {

    class TestCase;
    struct ITestCaseRegistry;
    struct IExceptionTranslatorRegistry;
    struct IExceptionTranslator;
    struct IReporterRegistry;
    struct IReporterFactory;
    struct ITagAliasRegistry;
    struct IMutableEnumValuesRegistry;

    class StartupExceptionRegistry;

    using IReporterFactoryPtr = std::shared_ptr<IReporterFactory>;

    struct IRegistryHub {
        virtual ~IRegistryHub();

        virtual IReporterRegistry const& getReporterRegistry() const = 0;
        virtual ITestCaseRegistry const& getTestCaseRegistry() const = 0;
        virtual ITagAliasRegistry const& getTagAliasRegistry() const = 0;
        virtual IExceptionTranslatorRegistry const& getExceptionTranslatorRegistry() const = 0;

        virtual StartupExceptionRegistry const& getStartupExceptionRegistry() const = 0;
    };

    struct IMutableRegistryHub {
        virtual ~IMutableRegistryHub();
        virtual void registerReporter( std::string const& name, IReporterFactoryPtr const& factory ) = 0;
        virtual void registerListener( IReporterFactoryPtr const& factory ) = 0;
        virtual void registerTest( TestCase const& testInfo ) = 0;
        virtual void registerTranslator( const IExceptionTranslator* translator ) = 0;
        virtual void registerTagAlias( std::string const& alias, std::string const& tag, SourceLineInfo const& lineInfo ) = 0;
        virtual void registerStartupException() noexcept = 0;
        virtual IMutableEnumValuesRegistry& getMutableEnumValuesRegistry() = 0;
    };

    IRegistryHub const& getRegistryHub();
    IMutableRegistryHub& getMutableRegistryHub();
    void cleanUp();
    std::string translateActiveException();

}

// end catch_interfaces_registry_hub.h
#if defined(CATCH_CONFIG_DISABLE)
    #define INTERNAL_CATCH_TRANSLATE_EXCEPTION_NO_REG( translatorName, signature) \
        static std::string translatorName( signature )
#endif

#include <exception>
#include <string>
#include <vector>

namespace Catch {
    using exceptionTranslateFunction = std::string(*)();

    struct IExceptionTranslator;
    using ExceptionTranslators = std::vector<std::unique_ptr<IExceptionTranslator const>>;

    struct IExceptionTranslator {
        virtual ~IExceptionTranslator();
        virtual std::string translate( ExceptionTranslators::const_iterator it, ExceptionTranslators::const_iterator itEnd ) const = 0;
    };

    struct IExceptionTranslatorRegistry {
        virtual ~IExceptionTranslatorRegistry();

        virtual std::string translateActiveException() const = 0;
    };

    class ExceptionTranslatorRegistrar {
        template<typename T>
        class ExceptionTranslator : public IExceptionTranslator {
        public:

            ExceptionTranslator( std::string(*translateFunction)( T& ) )
            : m_translateFunction( translateFunction )
            {}

            std::string translate( ExceptionTranslators::const_iterator it, ExceptionTranslators::const_iterator itEnd ) const override {
#if defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
                return "";
#else
                try {
                    if( it == itEnd )
                        std::rethrow_exception(std::current_exception());
                    else
                        return (*it)->translate( it+1, itEnd );
                }
                catch( T& ex ) {
                    return m_translateFunction( ex );
                }
#endif
            }

        protected:
            std::string(*m_translateFunction)( T& );
        };

    public:
        template<typename T>
        ExceptionTranslatorRegistrar( std::string(*translateFunction)( T& ) ) {
            getMutableRegistryHub().registerTranslator
                ( new ExceptionTranslator<T>( translateFunction ) );
        }
    };
}

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_TRANSLATE_EXCEPTION2( translatorName, signature ) \
    static std::string translatorName( signature ); \
    CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
    CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
    namespace{ Catch::ExceptionTranslatorRegistrar INTERNAL_CATCH_UNIQUE_NAME( catch_internal_ExceptionRegistrar )( &translatorName ); } \
    CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
    static std::string translatorName( signature )

#define INTERNAL_CATCH_TRANSLATE_EXCEPTION( signature ) INTERNAL_CATCH_TRANSLATE_EXCEPTION2( INTERNAL_CATCH_UNIQUE_NAME( catch_internal_ExceptionTranslator ), signature )

// end catch_interfaces_exception.h
// start catch_approx.h

#include <type_traits>

namespace Catch {
namespace Detail {

    class Approx {
    private:
        bool equalityComparisonImpl(double other) const;
        // Validates the new margin (margin >= 0)
        // out-of-line to avoid including stdexcept in the header
        void setMargin(double margin);
        // Validates the new epsilon (0 < epsilon < 1)
        // out-of-line to avoid including stdexcept in the header
        void setEpsilon(double epsilon);

    public:
        explicit Approx ( double value );

        static Approx custom();

        Approx operator-() const;

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        Approx operator()( T const& value ) {
            Approx approx( static_cast<double>(value) );
            approx.m_epsilon = m_epsilon;
            approx.m_margin = m_margin;
            approx.m_scale = m_scale;
            return approx;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        explicit Approx( T const& value ): Approx(static_cast<double>(value))
        {}

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator == ( const T& lhs, Approx const& rhs ) {
            auto lhs_v = static_cast<double>(lhs);
            return rhs.equalityComparisonImpl(lhs_v);
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator == ( Approx const& lhs, const T& rhs ) {
            return operator==( rhs, lhs );
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator != ( T const& lhs, Approx const& rhs ) {
            return !operator==( lhs, rhs );
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator != ( Approx const& lhs, T const& rhs ) {
            return !operator==( rhs, lhs );
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator <= ( T const& lhs, Approx const& rhs ) {
            return static_cast<double>(lhs) < rhs.m_value || lhs == rhs;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator <= ( Approx const& lhs, T const& rhs ) {
            return lhs.m_value < static_cast<double>(rhs) || lhs == rhs;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator >= ( T const& lhs, Approx const& rhs ) {
            return static_cast<double>(lhs) > rhs.m_value || lhs == rhs;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator >= ( Approx const& lhs, T const& rhs ) {
            return lhs.m_value > static_cast<double>(rhs) || lhs == rhs;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        Approx& epsilon( T const& newEpsilon ) {
            double epsilonAsDouble = static_cast<double>(newEpsilon);
            setEpsilon(epsilonAsDouble);
            return *this;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        Approx& margin( T const& newMargin ) {
            double marginAsDouble = static_cast<double>(newMargin);
            setMargin(marginAsDouble);
            return *this;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        Approx& scale( T const& newScale ) {
            m_scale = static_cast<double>(newScale);
            return *this;
        }

        std::string toString() const;

    private:
        double m_epsilon;
        double m_margin;
        double m_scale;
        double m_value;
    };
} // end namespace Detail

namespace literals {
    Detail::Approx operator "" _a(long double val);
    Detail::Approx operator "" _a(unsigned long long val);
} // end namespace literals

template<>
struct StringMaker<Catch::Detail::Approx> {
    static std::string convert(Catch::Detail::Approx const& value);
};

} // end namespace Catch

// end catch_approx.h
// start catch_string_manip.h

#include <string>
#include <iosfwd>
#include <vector>

namespace Catch {

    bool startsWith( std::string const& s, std::string const& prefix );
    bool startsWith( std::string const& s, char prefix );
    bool endsWith( std::string const& s, std::string const& suffix );
    bool endsWith( std::string const& s, char suffix );
    bool contains( std::string const& s, std::string const& infix );
    void toLowerInPlace( std::string& s );
    std::string toLower( std::string const& s );
    //! Returns a new string without whitespace at the start/end
    std::string trim( std::string const& str );
    //! Returns a substring of the original ref without whitespace. Beware lifetimes!
    StringRef trim(StringRef ref);

    // !!! Be aware, returns refs into original string - make sure original string outlives them
    std::vector<StringRef> splitStringRef( StringRef str, char delimiter );
    bool replaceInPlace( std::string& str, std::string const& replaceThis, std::string const& withThis );

    struct pluralise {
        pluralise( std::size_t count, std::string const& label );

        friend std::ostream& operator << ( std::ostream& os, pluralise const& pluraliser );

        std::size_t m_count;
        std::string m_label;
    };
}

// end catch_string_manip.h
#ifndef CATCH_CONFIG_DISABLE_MATCHERS
// start catch_capture_matchers.h

// start catch_matchers.h

#include <string>
#include <vector>

namespace Catch {
namespace Matchers {
    namespace Impl {

        template<typename ArgT> struct MatchAllOf;
        template<typename ArgT> struct MatchAnyOf;
        template<typename ArgT> struct MatchNotOf;

        class MatcherUntypedBase {
        public:
            MatcherUntypedBase() = default;
            MatcherUntypedBase ( MatcherUntypedBase const& ) = default;
            MatcherUntypedBase& operator = ( MatcherUntypedBase const& ) = delete;
            std::string toString() const;

        protected:
            virtual ~MatcherUntypedBase();
            virtual std::string describe() const = 0;
            mutable std::string m_cachedToString;
        };

#ifdef __clang__
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

        template<typename ObjectT>
        struct MatcherMethod {
            virtual bool match( ObjectT const& arg ) const = 0;
        };

#if defined(__OBJC__)
        // Hack to fix Catch GH issue #1661. Could use id for generic Object support.
        // use of const for Object pointers is very uncommon and under ARC it causes some kind of signature mismatch that breaks compilation
        template<>
        struct MatcherMethod<NSString*> {
            virtual bool match( NSString* arg ) const = 0;
        };
#endif

#ifdef __clang__
#    pragma clang diagnostic pop
#endif

        template<typename T>
        struct MatcherBase : MatcherUntypedBase, MatcherMethod<T> {

            MatchAllOf<T> operator && ( MatcherBase const& other ) const;
            MatchAnyOf<T> operator || ( MatcherBase const& other ) const;
            MatchNotOf<T> operator ! () const;
        };

        template<typename ArgT>
        struct MatchAllOf : MatcherBase<ArgT> {
            bool match( ArgT const& arg ) const override {
                for( auto matcher : m_matchers ) {
                    if (!matcher->match(arg))
                        return false;
                }
                return true;
            }
            std::string describe() const override {
                std::string description;
                description.reserve( 4 + m_matchers.size()*32 );
                description += "( ";
                bool first = true;
                for( auto matcher : m_matchers ) {
                    if( first )
                        first = false;
                    else
                        description += " and ";
                    description += matcher->toString();
                }
                description += " )";
                return description;
            }

            MatchAllOf<ArgT> operator && ( MatcherBase<ArgT> const& other ) {
                auto copy(*this);
                copy.m_matchers.push_back( &other );
                return copy;
            }

            std::vector<MatcherBase<ArgT> const*> m_matchers;
        };
        template<typename ArgT>
        struct MatchAnyOf : MatcherBase<ArgT> {

            bool match( ArgT const& arg ) const override {
                for( auto matcher : m_matchers ) {
                    if (matcher->match(arg))
                        return true;
                }
                return false;
            }
            std::string describe() const override {
                std::string description;
                description.reserve( 4 + m_matchers.size()*32 );
                description += "( ";
                bool first = true;
                for( auto matcher : m_matchers ) {
                    if( first )
                        first = false;
                    else
                        description += " or ";
                    description += matcher->toString();
                }
                description += " )";
                return description;
            }

            MatchAnyOf<ArgT> operator || ( MatcherBase<ArgT> const& other ) {
                auto copy(*this);
                copy.m_matchers.push_back( &other );
                return copy;
            }

            std::vector<MatcherBase<ArgT> const*> m_matchers;
        };

        template<typename ArgT>
        struct MatchNotOf : MatcherBase<ArgT> {

            MatchNotOf( MatcherBase<ArgT> const& underlyingMatcher ) : m_underlyingMatcher( underlyingMatcher ) {}

            bool match( ArgT const& arg ) const override {
                return !m_underlyingMatcher.match( arg );
            }

            std::string describe() const override {
                return "not " + m_underlyingMatcher.toString();
            }
            MatcherBase<ArgT> const& m_underlyingMatcher;
        };

        template<typename T>
        MatchAllOf<T> MatcherBase<T>::operator && ( MatcherBase const& other ) const {
            return MatchAllOf<T>() && *this && other;
        }
        template<typename T>
        MatchAnyOf<T> MatcherBase<T>::operator || ( MatcherBase const& other ) const {
            return MatchAnyOf<T>() || *this || other;
        }
        template<typename T>
        MatchNotOf<T> MatcherBase<T>::operator ! () const {
            return MatchNotOf<T>( *this );
        }

    } // namespace Impl

} // namespace Matchers

using namespace Matchers;
using Matchers::Impl::MatcherBase;

} // namespace Catch

// end catch_matchers.h
// start catch_matchers_exception.hpp

namespace Catch {
namespace Matchers {
namespace Exception {

class ExceptionMessageMatcher : public MatcherBase<std::exception> {
    std::string m_message;
public:

    ExceptionMessageMatcher(std::string const& message):
        m_message(message)
    {}

    bool match(std::exception const& ex) const override;

    std::string describe() const override;
};

} // namespace Exception

Exception::ExceptionMessageMatcher Message(std::string const& message);

} // namespace Matchers
} // namespace Catch

// end catch_matchers_exception.hpp
// start catch_matchers_floating.h

namespace Catch {
namespace Matchers {

    namespace Floating {

        enum class FloatingPointKind : uint8_t;

        struct WithinAbsMatcher : MatcherBase<double> {
            WithinAbsMatcher(double target, double margin);
            bool match(double const& matchee) const override;
            std::string describe() const override;
        private:
            double m_target;
            double m_margin;
        };

        struct WithinUlpsMatcher : MatcherBase<double> {
            WithinUlpsMatcher(double target, uint64_t ulps, FloatingPointKind baseType);
            bool match(double const& matchee) const override;
            std::string describe() const override;
        private:
            double m_target;
            uint64_t m_ulps;
            FloatingPointKind m_type;
        };

        // Given IEEE-754 format for floats and doubles, we can assume
        // that float -> double promotion is lossless. Given this, we can
        // assume that if we do the standard relative comparison of
        // |lhs - rhs| <= epsilon * max(fabs(lhs), fabs(rhs)), then we get
        // the same result if we do this for floats, as if we do this for
        // doubles that were promoted from floats.
        struct WithinRelMatcher : MatcherBase<double> {
            WithinRelMatcher(double target, double epsilon);
            bool match(double const& matchee) const override;
            std::string describe() const override;
        private:
            double m_target;
            double m_epsilon;
        };

    } // namespace Floating

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred
    Floating::WithinUlpsMatcher WithinULP(double target, uint64_t maxUlpDiff);
    Floating::WithinUlpsMatcher WithinULP(float target, uint64_t maxUlpDiff);
    Floating::WithinAbsMatcher WithinAbs(double target, double margin);
    Floating::WithinRelMatcher WithinRel(double target, double eps);
    // defaults epsilon to 100*numeric_limits<double>::epsilon()
    Floating::WithinRelMatcher WithinRel(double target);
    Floating::WithinRelMatcher WithinRel(float target, float eps);
    // defaults epsilon to 100*numeric_limits<float>::epsilon()
    Floating::WithinRelMatcher WithinRel(float target);

} // namespace Matchers
} // namespace Catch

// end catch_matchers_floating.h
// start catch_matchers_generic.hpp

#include <functional>
#include <string>

namespace Catch {
namespace Matchers {
namespace Generic {

namespace Detail {
    std::string finalizeDescription(const std::string& desc);
}

template <typename T>
class PredicateMatcher : public MatcherBase<T> {
    std::function<bool(T const&)> m_predicate;
    std::string m_description;
public:

    PredicateMatcher(std::function<bool(T const&)> const& elem, std::string const& descr)
        :m_predicate(std::move(elem)),
        m_description(Detail::finalizeDescription(descr))
    {}

    bool match( T const& item ) const override {
        return m_predicate(item);
    }

    std::string describe() const override {
        return m_description;
    }
};

} // namespace Generic

    // The following functions create the actual matcher objects.
    // The user has to explicitly specify type to the function, because
    // inferring std::function<bool(T const&)> is hard (but possible) and
    // requires a lot of TMP.
    template<typename T>
    Generic::PredicateMatcher<T> Predicate(std::function<bool(T const&)> const& predicate, std::string const& description = "") {
        return Generic::PredicateMatcher<T>(predicate, description);
    }

} // namespace Matchers
} // namespace Catch

// end catch_matchers_generic.hpp
// start catch_matchers_string.h

#include <string>

namespace Catch {
namespace Matchers {

    namespace StdString {

        struct CasedString
        {
            CasedString( std::string const& str, CaseSensitive::Choice caseSensitivity );
            std::string adjustString( std::string const& str ) const;
            std::string caseSensitivitySuffix() const;

            CaseSensitive::Choice m_caseSensitivity;
            std::string m_str;
        };

        struct StringMatcherBase : MatcherBase<std::string> {
            StringMatcherBase( std::string const& operation, CasedString const& comparator );
            std::string describe() const override;

            CasedString m_comparator;
            std::string m_operation;
        };

        struct EqualsMatcher : StringMatcherBase {
            EqualsMatcher( CasedString const& comparator );
            bool match( std::string const& source ) const override;
        };
        struct ContainsMatcher : StringMatcherBase {
            ContainsMatcher( CasedString const& comparator );
            bool match( std::string const& source ) const override;
        };
        struct StartsWithMatcher : StringMatcherBase {
            StartsWithMatcher( CasedString const& comparator );
            bool match( std::string const& source ) const override;
        };
        struct EndsWithMatcher : StringMatcherBase {
            EndsWithMatcher( CasedString const& comparator );
            bool match( std::string const& source ) const override;
        };

        struct RegexMatcher : MatcherBase<std::string> {
            RegexMatcher( std::string regex, CaseSensitive::Choice caseSensitivity );
            bool match( std::string const& matchee ) const override;
            std::string describe() const override;

        private:
            std::string m_regex;
            CaseSensitive::Choice m_caseSensitivity;
        };

    } // namespace StdString

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred

    StdString::EqualsMatcher Equals( std::string const& str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::ContainsMatcher Contains( std::string const& str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::EndsWithMatcher EndsWith( std::string const& str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::StartsWithMatcher StartsWith( std::string const& str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::RegexMatcher Matches( std::string const& regex, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );

} // namespace Matchers
} // namespace Catch

// end catch_matchers_string.h
// start catch_matchers_vector.h

#include <algorithm>

namespace Catch {
namespace Matchers {

    namespace Vector {
        template<typename T, typename Alloc>
        struct ContainsElementMatcher : MatcherBase<std::vector<T, Alloc>> {

            ContainsElementMatcher(T const &comparator) : m_comparator( comparator) {}

            bool match(std::vector<T, Alloc> const &v) const override {
                for (auto const& el : v) {
                    if (el == m_comparator) {
                        return true;
                    }
                }
                return false;
            }

            std::string describe() const override {
                return "Contains: " + ::Catch::Detail::stringify( m_comparator );
            }

            T const& m_comparator;
        };

        template<typename T, typename AllocComp, typename AllocMatch>
        struct ContainsMatcher : MatcherBase<std::vector<T, AllocMatch>> {

            ContainsMatcher(std::vector<T, AllocComp> const &comparator) : m_comparator( comparator ) {}

            bool match(std::vector<T, AllocMatch> const &v) const override {
                // !TBD: see note in EqualsMatcher
                if (m_comparator.size() > v.size())
                    return false;
                for (auto const& comparator : m_comparator) {
                    auto present = false;
                    for (const auto& el : v) {
                        if (el == comparator) {
                            present = true;
                            break;
                        }
                    }
                    if (!present) {
                        return false;
                    }
                }
                return true;
            }
            std::string describe() const override {
                return "Contains: " + ::Catch::Detail::stringify( m_comparator );
            }

            std::vector<T, AllocComp> const& m_comparator;
        };

        template<typename T, typename AllocComp, typename AllocMatch>
        struct EqualsMatcher : MatcherBase<std::vector<T, AllocMatch>> {

            EqualsMatcher(std::vector<T, AllocComp> const &comparator) : m_comparator( comparator ) {}

            bool match(std::vector<T, AllocMatch> const &v) const override {
                // !TBD: This currently works if all elements can be compared using !=
                // - a more general approach would be via a compare template that defaults
                // to using !=. but could be specialised for, e.g. std::vector<T, Alloc> etc
                // - then just call that directly
                if (m_comparator.size() != v.size())
                    return false;
                for (std::size_t i = 0; i < v.size(); ++i)
                    if (m_comparator[i] != v[i])
                        return false;
                return true;
            }
            std::string describe() const override {
                return "Equals: " + ::Catch::Detail::stringify( m_comparator );
            }
            std::vector<T, AllocComp> const& m_comparator;
        };

        template<typename T, typename AllocComp, typename AllocMatch>
        struct ApproxMatcher : MatcherBase<std::vector<T, AllocMatch>> {

            ApproxMatcher(std::vector<T, AllocComp> const& comparator) : m_comparator( comparator ) {}

            bool match(std::vector<T, AllocMatch> const &v) const override {
                if (m_comparator.size() != v.size())
                    return false;
                for (std::size_t i = 0; i < v.size(); ++i)
                    if (m_comparator[i] != approx(v[i]))
                        return false;
                return true;
            }
            std::string describe() const override {
                return "is approx: " + ::Catch::Detail::stringify( m_comparator );
            }
            template <typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
            ApproxMatcher& epsilon( T const& newEpsilon ) {
                approx.epsilon(newEpsilon);
                return *this;
            }
            template <typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
            ApproxMatcher& margin( T const& newMargin ) {
                approx.margin(newMargin);
                return *this;
            }
            template <typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
            ApproxMatcher& scale( T const& newScale ) {
                approx.scale(newScale);
                return *this;
            }

            std::vector<T, AllocComp> const& m_comparator;
            mutable Catch::Detail::Approx approx = Catch::Detail::Approx::custom();
        };

        template<typename T, typename AllocComp, typename AllocMatch>
        struct UnorderedEqualsMatcher : MatcherBase<std::vector<T, AllocMatch>> {
            UnorderedEqualsMatcher(std::vector<T, AllocComp> const& target) : m_target(target) {}
            bool match(std::vector<T, AllocMatch> const& vec) const override {
                if (m_target.size() != vec.size()) {
                    return false;
                }
                return std::is_permutation(m_target.begin(), m_target.end(), vec.begin());
            }

            std::string describe() const override {
                return "UnorderedEquals: " + ::Catch::Detail::stringify(m_target);
            }
        private:
            std::vector<T, AllocComp> const& m_target;
        };

    } // namespace Vector

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred

    template<typename T, typename AllocComp = std::allocator<T>, typename AllocMatch = AllocComp>
    Vector::ContainsMatcher<T, AllocComp, AllocMatch> Contains( std::vector<T, AllocComp> const& comparator ) {
        return Vector::ContainsMatcher<T, AllocComp, AllocMatch>( comparator );
    }

    template<typename T, typename Alloc = std::allocator<T>>
    Vector::ContainsElementMatcher<T, Alloc> VectorContains( T const& comparator ) {
        return Vector::ContainsElementMatcher<T, Alloc>( comparator );
    }

    template<typename T, typename AllocComp = std::allocator<T>, typename AllocMatch = AllocComp>
    Vector::EqualsMatcher<T, AllocComp, AllocMatch> Equals( std::vector<T, AllocComp> const& comparator ) {
        return Vector::EqualsMatcher<T, AllocComp, AllocMatch>( comparator );
    }

    template<typename T, typename AllocComp = std::allocator<T>, typename AllocMatch = AllocComp>
    Vector::ApproxMatcher<T, AllocComp, AllocMatch> Approx( std::vector<T, AllocComp> const& comparator ) {
        return Vector::ApproxMatcher<T, AllocComp, AllocMatch>( comparator );
    }

    template<typename T, typename AllocComp = std::allocator<T>, typename AllocMatch = AllocComp>
    Vector::UnorderedEqualsMatcher<T, AllocComp, AllocMatch> UnorderedEquals(std::vector<T, AllocComp> const& target) {
        return Vector::UnorderedEqualsMatcher<T, AllocComp, AllocMatch>( target );
    }

} // namespace Matchers
} // namespace Catch

// end catch_matchers_vector.h
namespace Catch {

    template<typename ArgT, typename MatcherT>
    class MatchExpr : public ITransientExpression {
        ArgT const& m_arg;
        MatcherT m_matcher;
        StringRef m_matcherString;
    public:
        MatchExpr( ArgT const& arg, MatcherT const& matcher, StringRef const& matcherString )
        :   ITransientExpression{ true, matcher.match( arg ) },
            m_arg( arg ),
            m_matcher( matcher ),
            m_matcherString( matcherString )
        {}

        void streamReconstructedExpression( std::ostream &os ) const override {
            auto matcherAsString = m_matcher.toString();
            os << Catch::Detail::stringify( m_arg ) << ' ';
            if( matcherAsString == Detail::unprintableString )
                os << m_matcherString;
            else
                os << matcherAsString;
        }
    };

    using StringMatcher = Matchers::Impl::MatcherBase<std::string>;

    void handleExceptionMatchExpr( AssertionHandler& handler, StringMatcher const& matcher, StringRef const& matcherString  );

    template<typename ArgT, typename MatcherT>
    auto makeMatchExpr( ArgT const& arg, MatcherT const& matcher, StringRef const& matcherString  ) -> MatchExpr<ArgT, MatcherT> {
        return MatchExpr<ArgT, MatcherT>( arg, matcher, matcherString );
    }

} // namespace Catch

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CHECK_THAT( macroName, matcher, resultDisposition, arg ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(arg) ", " CATCH_INTERNAL_STRINGIFY(matcher), resultDisposition ); \
        INTERNAL_CATCH_TRY { \
            catchAssertionHandler.handleExpr( Catch::makeMatchExpr( arg, matcher, #matcher##_catch_sr ) ); \
        } INTERNAL_CATCH_CATCH( catchAssertionHandler ) \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_MATCHES( macroName, exceptionType, resultDisposition, matcher, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__) ", " CATCH_INTERNAL_STRINGIFY(exceptionType) ", " CATCH_INTERNAL_STRINGIFY(matcher), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast<void>(__VA_ARGS__ ); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( exceptionType const& ex ) { \
                catchAssertionHandler.handleExpr( Catch::makeMatchExpr( ex, matcher, #matcher##_catch_sr ) ); \
            } \
            catch( ... ) { \
                catchAssertionHandler.handleUnexpectedInflightException(); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

// end catch_capture_matchers.h
#endif
// start catch_generators.hpp

// start catch_interfaces_generatortracker.h


#include <memory>

namespace Catch {

    namespace Generators {
        class GeneratorUntypedBase {
        public:
            GeneratorUntypedBase() = default;
            virtual ~GeneratorUntypedBase();
            // Attempts to move the generator to the next element
             //
             // Returns true iff the move succeeded (and a valid element
             // can be retrieved).
            virtual bool next() = 0;
        };
        using GeneratorBasePtr = std::unique_ptr<GeneratorUntypedBase>;

    } // namespace Generators

    struct IGeneratorTracker {
        virtual ~IGeneratorTracker();
        virtual auto hasGenerator() const -> bool = 0;
        virtual auto getGenerator() const -> Generators::GeneratorBasePtr const& = 0;
        virtual void setGenerator( Generators::GeneratorBasePtr&& generator ) = 0;
    };

} // namespace Catch

// end catch_interfaces_generatortracker.h
// start catch_enforce.h

#include <exception>

namespace Catch {
#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
    template <typename Ex>
    [[noreturn]]
    void throw_exception(Ex const& e) {
        throw e;
    }
#else // ^^ Exceptions are enabled //  Exceptions are disabled vv
    [[noreturn]]
    void throw_exception(std::exception const& e);
#endif

    [[noreturn]]
    void throw_logic_error(std::string const& msg);
    [[noreturn]]
    void throw_domain_error(std::string const& msg);
    [[noreturn]]
    void throw_runtime_error(std::string const& msg);

} // namespace Catch;

#define CATCH_MAKE_MSG(...) \
    (Catch::ReusableStringStream() << __VA_ARGS__).str()

#define CATCH_INTERNAL_ERROR(...) \
    Catch::throw_logic_error(CATCH_MAKE_MSG( CATCH_INTERNAL_LINEINFO << ": Internal Catch2 error: " << __VA_ARGS__))

#define CATCH_ERROR(...) \
    Catch::throw_domain_error(CATCH_MAKE_MSG( __VA_ARGS__ ))

#define CATCH_RUNTIME_ERROR(...) \
    Catch::throw_runtime_error(CATCH_MAKE_MSG( __VA_ARGS__ ))

#define CATCH_ENFORCE( condition, ... ) \
    do{ if( !(condition) ) CATCH_ERROR( __VA_ARGS__ ); } while(false)

// end catch_enforce.h
#include <memory>
#include <vector>
#include <cassert>

#include <utility>
#include <exception>

namespace Catch {

class GeneratorException : public std::exception {
    const char* const m_msg = "";

public:
    GeneratorException(const char* msg):
        m_msg(msg)
    {}

    const char* what() const noexcept override final;
};

namespace Generators {

    // !TBD move this into its own location?
    namespace pf{
        template<typename T, typename... Args>
        std::unique_ptr<T> make_unique( Args&&... args ) {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }
    }

    template<typename T>
    struct IGenerator : GeneratorUntypedBase {
        virtual ~IGenerator() = default;

        // Returns the current element of the generator
        //
        // \Precondition The generator is either freshly constructed,
        // or the last call to `next()` returned true
        virtual T const& get() const = 0;
        using type = T;
    };

    template<typename T>
    class SingleValueGenerator final : public IGenerator<T> {
        T m_value;
    public:
        SingleValueGenerator(T&& value) : m_value(std::move(value)) {}

        T const& get() const override {
            return m_value;
        }
        bool next() override {
            return false;
        }
    };

    template<typename T>
    class FixedValuesGenerator final : public IGenerator<T> {
        static_assert(!std::is_same<T, bool>::value,
            "FixedValuesGenerator does not support bools because of std::vector<bool>"
            "specialization, use SingleValue Generator instead.");
        std::vector<T> m_values;
        size_t m_idx = 0;
    public:
        FixedValuesGenerator( std::initializer_list<T> values ) : m_values( values ) {}

        T const& get() const override {
            return m_values[m_idx];
        }
        bool next() override {
            ++m_idx;
            return m_idx < m_values.size();
        }
    };

    template <typename T>
    class GeneratorWrapper final {
        std::unique_ptr<IGenerator<T>> m_generator;
    public:
        GeneratorWrapper(std::unique_ptr<IGenerator<T>> generator):
            m_generator(std::move(generator))
        {}
        T const& get() const {
            return m_generator->get();
        }
        bool next() {
            return m_generator->next();
        }
    };

    template <typename T>
    GeneratorWrapper<T> value(T&& value) {
        return GeneratorWrapper<T>(pf::make_unique<SingleValueGenerator<T>>(std::forward<T>(value)));
    }
    template <typename T>
    GeneratorWrapper<T> values(std::initializer_list<T> values) {
        return GeneratorWrapper<T>(pf::make_unique<FixedValuesGenerator<T>>(values));
    }

    template<typename T>
    class Generators : public IGenerator<T> {
        std::vector<GeneratorWrapper<T>> m_generators;
        size_t m_current = 0;

        void populate(GeneratorWrapper<T>&& generator) {
            m_generators.emplace_back(std::move(generator));
        }
        void populate(T&& val) {
            m_generators.emplace_back(value(std::forward<T>(val)));
        }
        template<typename U>
        void populate(U&& val) {
            populate(T(std::forward<U>(val)));
        }
        template<typename U, typename... Gs>
        void populate(U&& valueOrGenerator, Gs &&... moreGenerators) {
            populate(std::forward<U>(valueOrGenerator));
            populate(std::forward<Gs>(moreGenerators)...);
        }

    public:
        template <typename... Gs>
        Generators(Gs &&... moreGenerators) {
            m_generators.reserve(sizeof...(Gs));
            populate(std::forward<Gs>(moreGenerators)...);
        }

        T const& get() const override {
            return m_generators[m_current].get();
        }

        bool next() override {
            if (m_current >= m_generators.size()) {
                return false;
            }
            const bool current_status = m_generators[m_current].next();
            if (!current_status) {
                ++m_current;
            }
            return m_current < m_generators.size();
        }
    };

    template<typename... Ts>
    GeneratorWrapper<std::tuple<Ts...>> table( std::initializer_list<std::tuple<typename std::decay<Ts>::type...>> tuples ) {
        return values<std::tuple<Ts...>>( tuples );
    }

    // Tag type to signal that a generator sequence should convert arguments to a specific type
    template <typename T>
    struct as {};

    template<typename T, typename... Gs>
    auto makeGenerators( GeneratorWrapper<T>&& generator, Gs &&... moreGenerators ) -> Generators<T> {
        return Generators<T>(std::move(generator), std::forward<Gs>(moreGenerators)...);
    }
    template<typename T>
    auto makeGenerators( GeneratorWrapper<T>&& generator ) -> Generators<T> {
        return Generators<T>(std::move(generator));
    }
    template<typename T, typename... Gs>
    auto makeGenerators( T&& val, Gs &&... moreGenerators ) -> Generators<T> {
        return makeGenerators( value( std::forward<T>( val ) ), std::forward<Gs>( moreGenerators )... );
    }
    template<typename T, typename U, typename... Gs>
    auto makeGenerators( as<T>, U&& val, Gs &&... moreGenerators ) -> Generators<T> {
        return makeGenerators( value( T( std::forward<U>( val ) ) ), std::forward<Gs>( moreGenerators )... );
    }

    auto acquireGeneratorTracker( StringRef generatorName, SourceLineInfo const& lineInfo ) -> IGeneratorTracker&;

    template<typename L>
    // Note: The type after -> is weird, because VS2015 cannot parse
    //       the expression used in the typedef inside, when it is in
    //       return type. Yeah.
    auto generate( StringRef generatorName, SourceLineInfo const& lineInfo, L const& generatorExpression ) -> decltype(std::declval<decltype(generatorExpression())>().get()) {
        using UnderlyingType = typename decltype(generatorExpression())::type;

        IGeneratorTracker& tracker = acquireGeneratorTracker( generatorName, lineInfo );
        if (!tracker.hasGenerator()) {
            tracker.setGenerator(pf::make_unique<Generators<UnderlyingType>>(generatorExpression()));
        }

        auto const& generator = static_cast<IGenerator<UnderlyingType> const&>( *tracker.getGenerator() );
        return generator.get();
    }

} // namespace Generators
} // namespace Catch

#define GENERATE( ... ) \
    Catch::Generators::generate( INTERNAL_CATCH_STRINGIZE(INTERNAL_CATCH_UNIQUE_NAME(generator)), \
                                 CATCH_INTERNAL_LINEINFO, \
                                 [ ]{ using namespace Catch::Generators; return makeGenerators( __VA_ARGS__ ); } ) //NOLINT(google-build-using-namespace)
#define GENERATE_COPY( ... ) \
    Catch::Generators::generate( INTERNAL_CATCH_STRINGIZE(INTERNAL_CATCH_UNIQUE_NAME(generator)), \
                                 CATCH_INTERNAL_LINEINFO, \
                                 [=]{ using namespace Catch::Generators; return makeGenerators( __VA_ARGS__ ); } ) //NOLINT(google-build-using-namespace)
#define GENERATE_REF( ... ) \
    Catch::Generators::generate( INTERNAL_CATCH_STRINGIZE(INTERNAL_CATCH_UNIQUE_NAME(generator)), \
                                 CATCH_INTERNAL_LINEINFO, \
                                 [&]{ using namespace Catch::Generators; return makeGenerators( __VA_ARGS__ ); } ) //NOLINT(google-build-using-namespace)

// end catch_generators.hpp
// start catch_generators_generic.hpp

namespace Catch {
namespace Generators {

    template <typename T>
    class TakeGenerator : public IGenerator<T> {
        GeneratorWrapper<T> m_generator;
        size_t m_returned = 0;
        size_t m_target;
    public:
        TakeGenerator(size_t target, GeneratorWrapper<T>&& generator):
            m_generator(std::move(generator)),
            m_target(target)
        {
            assert(target != 0 && "Empty generators are not allowed");
        }
        T const& get() const override {
            return m_generator.get();
        }
        bool next() override {
            ++m_returned;
            if (m_returned >= m_target) {
                return false;
            }

            const auto success = m_generator.next();
            // If the underlying generator does not contain enough values
            // then we cut short as well
            if (!success) {
                m_returned = m_target;
            }
            return success;
        }
    };

    template <typename T>
    GeneratorWrapper<T> take(size_t target, GeneratorWrapper<T>&& generator) {
        return GeneratorWrapper<T>(pf::make_unique<TakeGenerator<T>>(target, std::move(generator)));
    }

    template <typename T, typename Predicate>
    class FilterGenerator : public IGenerator<T> {
        GeneratorWrapper<T> m_generator;
        Predicate m_predicate;
    public:
        template <typename P = Predicate>
        FilterGenerator(P&& pred, GeneratorWrapper<T>&& generator):
            m_generator(std::move(generator)),
            m_predicate(std::forward<P>(pred))
        {
            if (!m_predicate(m_generator.get())) {
                // It might happen that there are no values that pass the
                // filter. In that case we throw an exception.
                auto has_initial_value = next();
                if (!has_initial_value) {
                    Catch::throw_exception(GeneratorException("No valid value found in filtered generator"));
                }
            }
        }

        T const& get() const override {
            return m_generator.get();
        }

        bool next() override {
            bool success = m_generator.next();
            if (!success) {
                return false;
            }
            while (!m_predicate(m_generator.get()) && (success = m_generator.next()) == true);
            return success;
        }
    };

    template <typename T, typename Predicate>
    GeneratorWrapper<T> filter(Predicate&& pred, GeneratorWrapper<T>&& generator) {
        return GeneratorWrapper<T>(std::unique_ptr<IGenerator<T>>(pf::make_unique<FilterGenerator<T, Predicate>>(std::forward<Predicate>(pred), std::move(generator))));
    }

    template <typename T>
    class RepeatGenerator : public IGenerator<T> {
        static_assert(!std::is_same<T, bool>::value,
            "RepeatGenerator currently does not support bools"
            "because of std::vector<bool> specialization");
        GeneratorWrapper<T> m_generator;
        mutable std::vector<T> m_returned;
        size_t m_target_repeats;
        size_t m_current_repeat = 0;
        size_t m_repeat_index = 0;
    public:
        RepeatGenerator(size_t repeats, GeneratorWrapper<T>&& generator):
            m_generator(std::move(generator)),
            m_target_repeats(repeats)
        {
            assert(m_target_repeats > 0 && "Repeat generator must repeat at least once");
        }

        T const& get() const override {
            if (m_current_repeat == 0) {
                m_returned.push_back(m_generator.get());
                return m_returned.back();
            }
            return m_returned[m_repeat_index];
        }

        bool next() override {
            // There are 2 basic cases:
            // 1) We are still reading the generator
            // 2) We are reading our own cache

            // In the first case, we need to poke the underlying generator.
            // If it happily moves, we are left in that state, otherwise it is time to start reading from our cache
            if (m_current_repeat == 0) {
                const auto success = m_generator.next();
                if (!success) {
                    ++m_current_repeat;
                }
                return m_current_repeat < m_target_repeats;
            }

            // In the second case, we need to move indices forward and check that we haven't run up against the end
            ++m_repeat_index;
            if (m_repeat_index == m_returned.size()) {
                m_repeat_index = 0;
                ++m_current_repeat;
            }
            return m_current_repeat < m_target_repeats;
        }
    };

    template <typename T>
    GeneratorWrapper<T> repeat(size_t repeats, GeneratorWrapper<T>&& generator) {
        return GeneratorWrapper<T>(pf::make_unique<RepeatGenerator<T>>(repeats, std::move(generator)));
    }

    template <typename T, typename U, typename Func>
    class MapGenerator : public IGenerator<T> {
        // TBD: provide static assert for mapping function, for friendly error message
        GeneratorWrapper<U> m_generator;
        Func m_function;
        // To avoid returning dangling reference, we have to save the values
        T m_cache;
    public:
        template <typename F2 = Func>
        MapGenerator(F2&& function, GeneratorWrapper<U>&& generator) :
            m_generator(std::move(generator)),
            m_function(std::forward<F2>(function)),
            m_cache(m_function(m_generator.get()))
        {}

        T const& get() const override {
            return m_cache;
        }
        bool next() override {
            const auto success = m_generator.next();
            if (success) {
                m_cache = m_function(m_generator.get());
            }
            return success;
        }
    };

    template <typename Func, typename U, typename T = FunctionReturnType<Func, U>>
    GeneratorWrapper<T> map(Func&& function, GeneratorWrapper<U>&& generator) {
        return GeneratorWrapper<T>(
            pf::make_unique<MapGenerator<T, U, Func>>(std::forward<Func>(function), std::move(generator))
        );
    }

    template <typename T, typename U, typename Func>
    GeneratorWrapper<T> map(Func&& function, GeneratorWrapper<U>&& generator) {
        return GeneratorWrapper<T>(
            pf::make_unique<MapGenerator<T, U, Func>>(std::forward<Func>(function), std::move(generator))
        );
    }

    template <typename T>
    class ChunkGenerator final : public IGenerator<std::vector<T>> {
        std::vector<T> m_chunk;
        size_t m_chunk_size;
        GeneratorWrapper<T> m_generator;
        bool m_used_up = false;
    public:
        ChunkGenerator(size_t size, GeneratorWrapper<T> generator) :
            m_chunk_size(size), m_generator(std::move(generator))
        {
            m_chunk.reserve(m_chunk_size);
            if (m_chunk_size != 0) {
                m_chunk.push_back(m_generator.get());
                for (size_t i = 1; i < m_chunk_size; ++i) {
                    if (!m_generator.next()) {
                        Catch::throw_exception(GeneratorException("Not enough values to initialize the first chunk"));
                    }
                    m_chunk.push_back(m_generator.get());
                }
            }
        }
        std::vector<T> const& get() const override {
            return m_chunk;
        }
        bool next() override {
            m_chunk.clear();
            for (size_t idx = 0; idx < m_chunk_size; ++idx) {
                if (!m_generator.next()) {
                    return false;
                }
                m_chunk.push_back(m_generator.get());
            }
            return true;
        }
    };

    template <typename T>
    GeneratorWrapper<std::vector<T>> chunk(size_t size, GeneratorWrapper<T>&& generator) {
        return GeneratorWrapper<std::vector<T>>(
            pf::make_unique<ChunkGenerator<T>>(size, std::move(generator))
        );
    }

} // namespace Generators
} // namespace Catch

// end catch_generators_generic.hpp
// start catch_generators_specific.hpp

// start catch_context.h

#include <memory>

namespace Catch {

    struct IResultCapture;
    struct IRunner;
    struct IConfig;
    struct IMutableContext;

    using IConfigPtr = std::shared_ptr<IConfig const>;

    struct IContext
    {
        virtual ~IContext();

        virtual IResultCapture* getResultCapture() = 0;
        virtual IRunner* getRunner() = 0;
        virtual IConfigPtr const& getConfig() const = 0;
    };

    struct IMutableContext : IContext
    {
        virtual ~IMutableContext();
        virtual void setResultCapture( IResultCapture* resultCapture ) = 0;
        virtual void setRunner( IRunner* runner ) = 0;
        virtual void setConfig( IConfigPtr const& config ) = 0;

    private:
        static IMutableContext *currentContext;
        friend IMutableContext& getCurrentMutableContext();
        friend void cleanUpContext();
        static void createContext();
    };

    inline IMutableContext& getCurrentMutableContext()
    {
        if( !IMutableContext::currentContext )
            IMutableContext::createContext();
        // NOLINTNEXTLINE(clang-analyzer-core.uninitialized.UndefReturn)
        return *IMutableContext::currentContext;
    }

    inline IContext& getCurrentContext()
    {
        return getCurrentMutableContext();
    }

    void cleanUpContext();

    class SimplePcg32;
    SimplePcg32& rng();
}

// end catch_context.h
// start catch_interfaces_config.h

// start catch_option.hpp

namespace Catch {

    // An optional type
    template<typename T>
    class Option {
    public:
        Option() : nullableValue( nullptr ) {}
        Option( T const& _value )
        : nullableValue( new( storage ) T( _value ) )
        {}
        Option( Option const& _other )
        : nullableValue( _other ? new( storage ) T( *_other ) : nullptr )
        {}

        ~Option() {
            reset();
        }

        Option& operator= ( Option const& _other ) {
            if( &_other != this ) {
                reset();
                if( _other )
                    nullableValue = new( storage ) T( *_other );
            }
            return *this;
        }
        Option& operator = ( T const& _value ) {
            reset();
            nullableValue = new( storage ) T( _value );
            return *this;
        }

        void reset() {
            if( nullableValue )
                nullableValue->~T();
            nullableValue = nullptr;
        }

        T& operator*() { return *nullableValue; }
        T const& operator*() const { return *nullableValue; }
        T* operator->() { return nullableValue; }
        const T* operator->() const { return nullableValue; }

        T valueOr( T const& defaultValue ) const {
            return nullableValue ? *nullableValue : defaultValue;
        }

        bool some() const { return nullableValue != nullptr; }
        bool none() const { return nullableValue == nullptr; }

        bool operator !() const { return nullableValue == nullptr; }
        explicit operator bool() const {
            return some();
        }

    private:
        T *nullableValue;
        alignas(alignof(T)) char storage[sizeof(T)];
    };

} // end namespace Catch

// end catch_option.hpp
#include <chrono>
#include <iosfwd>
#include <string>
#include <vector>
#include <memory>

namespace Catch {

    enum class Verbosity {
        Quiet = 0,
        Normal,
        High
    };

    struct WarnAbout { enum What {
        Nothing = 0x00,
        NoAssertions = 0x01,
        NoTests = 0x02
    }; };

    struct ShowDurations { enum OrNot {
        DefaultForReporter,
        Always,
        Never
    }; };
    struct RunTests { enum InWhatOrder {
        InDeclarationOrder,
        InLexicographicalOrder,
        InRandomOrder
    }; };
    struct UseColour { enum YesOrNo {
        Auto,
        Yes,
        No
    }; };
    struct WaitForKeypress { enum When {
        Never,
        BeforeStart = 1,
        BeforeExit = 2,
        BeforeStartAndExit = BeforeStart | BeforeExit
    }; };

    class TestSpec;

    struct IConfig : NonCopyable {

        virtual ~IConfig();

        virtual bool allowThrows() const = 0;
        virtual std::ostream& stream() const = 0;
        virtual std::string name() const = 0;
        virtual bool includeSuccessfulResults() const = 0;
        virtual bool shouldDebugBreak() const = 0;
        virtual bool warnAboutMissingAssertions() const = 0;
        virtual bool warnAboutNoTests() const = 0;
        virtual int abortAfter() const = 0;
        virtual bool showInvisibles() const = 0;
        virtual ShowDurations::OrNot showDurations() const = 0;
        virtual double minDuration() const = 0;
        virtual TestSpec const& testSpec() const = 0;
        virtual bool hasTestFilters() const = 0;
        virtual std::vector<std::string> const& getTestsOrTags() const = 0;
        virtual RunTests::InWhatOrder runOrder() const = 0;
        virtual unsigned int rngSeed() const = 0;
        virtual UseColour::YesOrNo useColour() const = 0;
        virtual std::vector<std::string> const& getSectionsToRun() const = 0;
        virtual Verbosity verbosity() const = 0;

        virtual bool benchmarkNoAnalysis() const = 0;
        virtual int benchmarkSamples() const = 0;
        virtual double benchmarkConfidenceInterval() const = 0;
        virtual unsigned int benchmarkResamples() const = 0;
        virtual std::chrono::milliseconds benchmarkWarmupTime() const = 0;
    };

    using IConfigPtr = std::shared_ptr<IConfig const>;
}

// end catch_interfaces_config.h
// start catch_random_number_generator.h

#include <cstdint>

namespace Catch {

    // This is a simple implementation of C++11 Uniform Random Number
    // Generator. It does not provide all operators, because Catch2
    // does not use it, but it should behave as expected inside stdlib's
    // distributions.
    // The implementation is based on the PCG family (http://pcg-random.org)
    class SimplePcg32 {
        using state_type = std::uint64_t;
    public:
        using result_type = std::uint32_t;
        static constexpr result_type (min)() {
            return 0;
        }
        static constexpr result_type (max)() {
            return static_cast<result_type>(-1);
        }

        // Provide some default initial state for the default constructor
        SimplePcg32():SimplePcg32(0xed743cc4U) {}

        explicit SimplePcg32(result_type seed_);

        void seed(result_type seed_);
        void discard(uint64_t skip);

        result_type operator()();

    private:
        friend bool operator==(SimplePcg32 const& lhs, SimplePcg32 const& rhs);
        friend bool operator!=(SimplePcg32 const& lhs, SimplePcg32 const& rhs);

        // In theory we also need operator<< and operator>>
        // In practice we do not use them, so we will skip them for now

        std::uint64_t m_state;
        // This part of the state determines which "stream" of the numbers
        // is chosen -- we take it as a constant for Catch2, so we only
        // need to deal with seeding the main state.
        // Picked by reading 8 bytes from `/dev/random` :-)
        static const std::uint64_t s_inc = (0x13ed0cc53f939476ULL << 1ULL) | 1ULL;
    };

} // end namespace Catch

// end catch_random_number_generator.h
#include <random>

namespace Catch {
namespace Generators {

template <typename Float>
class RandomFloatingGenerator final : public IGenerator<Float> {
    Catch::SimplePcg32& m_rng;
    std::uniform_real_distribution<Float> m_dist;
    Float m_current_number;
public:

    RandomFloatingGenerator(Float a, Float b):
        m_rng(rng()),
        m_dist(a, b) {
        static_cast<void>(next());
    }

    Float const& get() const override {
        return m_current_number;
    }
    bool next() override {
        m_current_number = m_dist(m_rng);
        return true;
    }
};

template <typename Integer>
class RandomIntegerGenerator final : public IGenerator<Integer> {
    Catch::SimplePcg32& m_rng;
    std::uniform_int_distribution<Integer> m_dist;
    Integer m_current_number;
public:

    RandomIntegerGenerator(Integer a, Integer b):
        m_rng(rng()),
        m_dist(a, b) {
        static_cast<void>(next());
    }

    Integer const& get() const override {
        return m_current_number;
    }
    bool next() override {
        m_current_number = m_dist(m_rng);
        return true;
    }
};

// TODO: Ideally this would be also constrained against the various char types,
//       but I don't expect users to run into that in practice.
template <typename T>
typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, bool>::value,
GeneratorWrapper<T>>::type
random(T a, T b) {
    return GeneratorWrapper<T>(
        pf::make_unique<RandomIntegerGenerator<T>>(a, b)
    );
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value,
GeneratorWrapper<T>>::type
random(T a, T b) {
    return GeneratorWrapper<T>(
        pf::make_unique<RandomFloatingGenerator<T>>(a, b)
    );
}

template <typename T>
class RangeGenerator final : public IGenerator<T> {
    T m_current;
    T m_end;
    T m_step;
    bool m_positive;

public:
    RangeGenerator(T const& start, T const& end, T const& step):
        m_current(start),
        m_end(end),
        m_step(step),
        m_positive(m_step > T(0))
    {
        assert(m_current != m_end && "Range start and end cannot be equal");
        assert(m_step != T(0) && "Step size cannot be zero");
        assert(((m_positive && m_current <= m_end) || (!m_positive && m_current >= m_end)) && "Step moves away from end");
    }

    RangeGenerator(T const& start, T const& end):
        RangeGenerator(start, end, (start < end) ? T(1) : T(-1))
    {}

    T const& get() const override {
        return m_current;
    }

    bool next() override {
        m_current += m_step;
        return (m_positive) ? (m_current < m_end) : (m_current > m_end);
    }
};

template <typename T>
GeneratorWrapper<T> range(T const& start, T const& end, T const& step) {
    static_assert(std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, "Type must be numeric");
    return GeneratorWrapper<T>(pf::make_unique<RangeGenerator<T>>(start, end, step));
}

template <typename T>
GeneratorWrapper<T> range(T const& start, T const& end) {
    static_assert(std::is_integral<T>::value && !std::is_same<T, bool>::value, "Type must be an integer");
    return GeneratorWrapper<T>(pf::make_unique<RangeGenerator<T>>(start, end));
}

template <typename T>
class IteratorGenerator final : public IGenerator<T> {
    static_assert(!std::is_same<T, bool>::value,
        "IteratorGenerator currently does not support bools"
        "because of std::vector<bool> specialization");

    std::vector<T> m_elems;
    size_t m_current = 0;
public:
    template <typename InputIterator, typename InputSentinel>
    IteratorGenerator(InputIterator first, InputSentinel last):m_elems(first, last) {
        if (m_elems.empty()) {
            Catch::throw_exception(GeneratorException("IteratorGenerator received no valid values"));
        }
    }

    T const& get() const override {
        return m_elems[m_current];
    }

    bool next() override {
        ++m_current;
        return m_current != m_elems.size();
    }
};

template <typename InputIterator,
          typename InputSentinel,
          typename ResultType = typename std::iterator_traits<InputIterator>::value_type>
GeneratorWrapper<ResultType> from_range(InputIterator from, InputSentinel to) {
    return GeneratorWrapper<ResultType>(pf::make_unique<IteratorGenerator<ResultType>>(from, to));
}

template <typename Container,
          typename ResultType = typename Container::value_type>
GeneratorWrapper<ResultType> from_range(Container const& cnt) {
    return GeneratorWrapper<ResultType>(pf::make_unique<IteratorGenerator<ResultType>>(cnt.begin(), cnt.end()));
}

} // namespace Generators
} // namespace Catch

// end catch_generators_specific.hpp

// These files are included here so the single_include script doesn't put them
// in the conditionally compiled sections
// start catch_test_case_info.h

#include <string>
#include <vector>
#include <memory>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace Catch {

    struct ITestInvoker;

    struct TestCaseInfo {
        enum SpecialProperties{
            None = 0,
            IsHidden = 1 << 1,
            ShouldFail = 1 << 2,
            MayFail = 1 << 3,
            Throws = 1 << 4,
            NonPortable = 1 << 5,
            Benchmark = 1 << 6
        };

        TestCaseInfo(   std::string const& _name,
                        std::string const& _className,
                        std::string const& _description,
                        std::vector<std::string> const& _tags,
                        SourceLineInfo const& _lineInfo );

        friend void setTags( TestCaseInfo& testCaseInfo, std::vector<std::string> tags );

        bool isHidden() const;
        bool throws() const;
        bool okToFail() const;
        bool expectedToFail() const;

        std::string tagsAsString() const;

        std::string name;
        std::string className;
        std::string description;
        std::vector<std::string> tags;
        std::vector<std::string> lcaseTags;
        SourceLineInfo lineInfo;
        SpecialProperties properties;
    };

    class TestCase : public TestCaseInfo {
    public:

        TestCase( ITestInvoker* testCase, TestCaseInfo&& info );

        TestCase withName( std::string const& _newName ) const;

        void invoke() const;

        TestCaseInfo const& getTestCaseInfo() const;

        bool operator == ( TestCase const& other ) const;
        bool operator < ( TestCase const& other ) const;

    private:
        std::shared_ptr<ITestInvoker> test;
    };

    TestCase makeTestCase(  ITestInvoker* testCase,
                            std::string const& className,
                            NameAndTags const& nameAndTags,
                            SourceLineInfo const& lineInfo );
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_case_info.h
// start catch_interfaces_runner.h

namespace Catch {

    struct IRunner {
        virtual ~IRunner();
        virtual bool aborting() const = 0;
    };
}

// end catch_interfaces_runner.h

#ifdef __OBJC__
// start catch_objc.hpp

#import <objc/runtime.h>

#include <string>

// NB. Any general catch headers included here must be included
// in catch.hpp first to make sure they are included by the single
// header for non obj-usage

///////////////////////////////////////////////////////////////////////////////
// This protocol is really only here for (self) documenting purposes, since
// all its methods are optional.
@protocol OcFixture

@optional

-(void) setUp;
-(void) tearDown;

@end

namespace Catch {

    class OcMethod : public ITestInvoker {

    public:
        OcMethod( Class cls, SEL sel ) : m_cls( cls ), m_sel( sel ) {}

        virtual void invoke() const {
            id obj = [[m_cls alloc] init];

            performOptionalSelector( obj, @selector(setUp)  );
            performOptionalSelector( obj, m_sel );
            performOptionalSelector( obj, @selector(tearDown)  );

            arcSafeRelease( obj );
        }
    private:
        virtual ~OcMethod() {}

        Class m_cls;
        SEL m_sel;
    };

    namespace Detail{

        inline std::string getAnnotation(   Class cls,
                                            std::string const& annotationName,
                                            std::string const& testCaseName ) {
            NSString* selStr = [[NSString alloc] initWithFormat:@"Catch_%s_%s", annotationName.c_str(), testCaseName.c_str()];
            SEL sel = NSSelectorFromString( selStr );
            arcSafeRelease( selStr );
            id value = performOptionalSelector( cls, sel );
            if( value )
                return [(NSString*)value UTF8String];
            return "";
        }
    }

    inline std::size_t registerTestMethods() {
        std::size_t noTestMethods = 0;
        int noClasses = objc_getClassList( nullptr, 0 );

        Class* classes = (CATCH_UNSAFE_UNRETAINED Class *)malloc( sizeof(Class) * noClasses);
        objc_getClassList( classes, noClasses );

        for( int c = 0; c < noClasses; c++ ) {
            Class cls = classes[c];
            {
                u_int count;
                Method* methods = class_copyMethodList( cls, &count );
                for( u_int m = 0; m < count ; m++ ) {
                    SEL selector = method_getName(methods[m]);
                    std::string methodName = sel_getName(selector);
                    if( startsWith( methodName, "Catch_TestCase_" ) ) {
                        std::string testCaseName = methodName.substr( 15 );
                        std::string name = Detail::getAnnotation( cls, "Name", testCaseName );
                        std::string desc = Detail::getAnnotation( cls, "Description", testCaseName );
                        const char* className = class_getName( cls );

                        getMutableRegistryHub().registerTest( makeTestCase( new OcMethod( cls, selector ), className, NameAndTags( name.c_str(), desc.c_str() ), SourceLineInfo("",0) ) );
                        noTestMethods++;
                    }
                }
                free(methods);
            }
        }
        return noTestMethods;
    }

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)

    namespace Matchers {
        namespace Impl {
        namespace NSStringMatchers {

            struct StringHolder : MatcherBase<NSString*>{
                StringHolder( NSString* substr ) : m_substr( [substr copy] ){}
                StringHolder( StringHolder const& other ) : m_substr( [other.m_substr copy] ){}
                StringHolder() {
                    arcSafeRelease( m_substr );
                }

                bool match( NSString* str ) const override {
                    return false;
                }

                NSString* CATCH_ARC_STRONG m_substr;
            };

            struct Equals : StringHolder {
                Equals( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &&
                            [str isEqualToString:m_substr];
                }

                std::string describe() const override {
                    return "equals string: " + Catch::Detail::stringify( m_substr );
                }
            };

            struct Contains : StringHolder {
                Contains( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &&
                            [str rangeOfString:m_substr].location != NSNotFound;
                }

                std::string describe() const override {
                    return "contains string: " + Catch::Detail::stringify( m_substr );
                }
            };

            struct StartsWith : StringHolder {
                StartsWith( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &&
                            [str rangeOfString:m_substr].location == 0;
                }

                std::string describe() const override {
                    return "starts with: " + Catch::Detail::stringify( m_substr );
                }
            };
            struct EndsWith : StringHolder {
                EndsWith( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &&
                            [str rangeOfString:m_substr].location == [str length] - [m_substr length];
                }

                std::string describe() const override {
                    return "ends with: " + Catch::Detail::stringify( m_substr );
                }
            };

        } // namespace NSStringMatchers
        } // namespace Impl

        inline Impl::NSStringMatchers::Equals
            Equals( NSString* substr ){ return Impl::NSStringMatchers::Equals( substr ); }

        inline Impl::NSStringMatchers::Contains
            Contains( NSString* substr ){ return Impl::NSStringMatchers::Contains( substr ); }

        inline Impl::NSStringMatchers::StartsWith
            StartsWith( NSString* substr ){ return Impl::NSStringMatchers::StartsWith( substr ); }

        inline Impl::NSStringMatchers::EndsWith
            EndsWith( NSString* substr ){ return Impl::NSStringMatchers::EndsWith( substr ); }

    } // namespace Matchers

    using namespace Matchers;

#endif // CATCH_CONFIG_DISABLE_MATCHERS

} // namespace Catch

///////////////////////////////////////////////////////////////////////////////
#define OC_MAKE_UNIQUE_NAME( root, uniqueSuffix ) root##uniqueSuffix
#define OC_TEST_CASE2( name, desc, uniqueSuffix ) \
+(NSString*) OC_MAKE_UNIQUE_NAME( Catch_Name_test_, uniqueSuffix ) \
{ \
return @ name; \
} \
+(NSString*) OC_MAKE_UNIQUE_NAME( Catch_Description_test_, uniqueSuffix ) \
{ \
return @ desc; \
} \
-(void) OC_MAKE_UNIQUE_NAME( Catch_TestCase_test_, uniqueSuffix )

#define OC_TEST_CASE( name, desc ) OC_TEST_CASE2( name, desc, __LINE__ )

// end catch_objc.hpp
#endif

// Benchmarking needs the externally-facing parts of reporters to work
#if defined(CATCH_CONFIG_EXTERNAL_INTERFACES) || defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
// start catch_external_interfaces.h

// start catch_reporter_bases.hpp

// start catch_interfaces_reporter.h

// start catch_config.hpp

// start catch_test_spec_parser.h

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// start catch_test_spec.h

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// start catch_wildcard_pattern.h

namespace Catch
{
    class WildcardPattern {
        enum WildcardPosition {
            NoWildcard = 0,
            WildcardAtStart = 1,
            WildcardAtEnd = 2,
            WildcardAtBothEnds = WildcardAtStart | WildcardAtEnd
        };

    public:

        WildcardPattern( std::string const& pattern, CaseSensitive::Choice caseSensitivity );
        virtual ~WildcardPattern() = default;
        virtual bool matches( std::string const& str ) const;

    private:
        std::string normaliseString( std::string const& str ) const;
        CaseSensitive::Choice m_caseSensitivity;
        WildcardPosition m_wildcard = NoWildcard;
        std::string m_pattern;
    };
}

// end catch_wildcard_pattern.h
#include <string>
#include <vector>
#include <memory>

namespace Catch {

    struct IConfig;

    class TestSpec {
        class Pattern {
        public:
            explicit Pattern( std::string const& name );
            virtual ~Pattern();
            virtual bool matches( TestCaseInfo const& testCase ) const = 0;
            std::string const& name() const;
        private:
            std::string const m_name;
        };
        using PatternPtr = std::shared_ptr<Pattern>;

        class NamePattern : public Pattern {
        public:
            explicit NamePattern( std::string const& name, std::string const& filterString );
            bool matches( TestCaseInfo const& testCase ) const override;
        private:
            WildcardPattern m_wildcardPattern;
        };

        class TagPattern : public Pattern {
        public:
            explicit TagPattern( std::string const& tag, std::string const& filterString );
            bool matches( TestCaseInfo const& testCase ) const override;
        private:
            std::string m_tag;
        };

        class ExcludedPattern : public Pattern {
        public:
            explicit ExcludedPattern( PatternPtr const& underlyingPattern );
            bool matches( TestCaseInfo const& testCase ) const override;
        private:
            PatternPtr m_underlyingPattern;
        };

        struct Filter {
            std::vector<PatternPtr> m_patterns;

            bool matches( TestCaseInfo const& testCase ) const;
            std::string name() const;
        };

    public:
        struct FilterMatch {
            std::string name;
            std::vector<TestCase const*> tests;
        };
        using Matches = std::vector<FilterMatch>;
        using vectorStrings = std::vector<std::string>;

        bool hasFilters() const;
        bool matches( TestCaseInfo const& testCase ) const;
        Matches matchesByFilter( std::vector<TestCase> const& testCases, IConfig const& config ) const;
        const vectorStrings & getInvalidArgs() const;

    private:
        std::vector<Filter> m_filters;
        std::vector<std::string> m_invalidArgs;
        friend class TestSpecParser;
    };
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_spec.h
// start catch_interfaces_tag_alias_registry.h

#include <string>

namespace Catch {

    struct TagAlias;

    struct ITagAliasRegistry {
        virtual ~ITagAliasRegistry();
        // Nullptr if not present
        virtual TagAlias const* find( std::string const& alias ) const = 0;
        virtual std::string expandAliases( std::string const& unexpandedTestSpec ) const = 0;

        static ITagAliasRegistry const& get();
    };

} // end namespace Catch

// end catch_interfaces_tag_alias_registry.h
namespace Catch {

    class TestSpecParser {
        enum Mode{ None, Name, QuotedName, Tag, EscapedName };
        Mode m_mode = None;
        Mode lastMode = None;
        bool m_exclusion = false;
        std::size_t m_pos = 0;
        std::size_t m_realPatternPos = 0;
        std::string m_arg;
        std::string m_substring;
        std::string m_patternName;
        std::vector<std::size_t> m_escapeChars;
        TestSpec::Filter m_currentFilter;
        TestSpec m_testSpec;
        ITagAliasRegistry const* m_tagAliases = nullptr;

    public:
        TestSpecParser( ITagAliasRegistry const& tagAliases );

        TestSpecParser& parse( std::string const& arg );
        TestSpec testSpec();

    private:
        bool visitChar( char c );
        void startNewMode( Mode mode );
        bool processNoneChar( char c );
        void processNameChar( char c );
        bool processOtherChar( char c );
        void endMode();
        void escape();
        bool isControlChar( char c ) const;
        void saveLastMode();
        void revertBackToLastMode();
        void addFilter();
        bool separate();

        // Handles common preprocessing of the pattern for name/tag patterns
        std::string preprocessPattern();
        // Adds the current pattern as a test name
        void addNamePattern();
        // Adds the current pattern as a tag
        void addTagPattern();

        inline void addCharToPattern(char c) {
            m_substring += c;
            m_patternName += c;
            m_realPatternPos++;
        }

    };
    TestSpec parseTestSpec( std::string const& arg );

} // namespace Catch

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_spec_parser.h
// Libstdc++ doesn't like incomplete classes for unique_ptr

#include <memory>
#include <vector>
#include <string>

#ifndef CATCH_CONFIG_CONSOLE_WIDTH
#define CATCH_CONFIG_CONSOLE_WIDTH 80
#endif

namespace Catch {

    struct IStream;

    struct ConfigData {
        bool listTests = false;
        bool listTags = false;
        bool listReporters = false;
        bool listTestNamesOnly = false;

        bool showSuccessfulTests = false;
        bool shouldDebugBreak = false;
        bool noThrow = false;
        bool showHelp = false;
        bool showInvisibles = false;
        bool filenamesAsTags = false;
        bool libIdentify = false;

        int abortAfter = -1;
        unsigned int rngSeed = 0;

        bool benchmarkNoAnalysis = false;
        unsigned int benchmarkSamples = 100;
        double benchmarkConfidenceInterval = 0.95;
        unsigned int benchmarkResamples = 100000;
        std::chrono::milliseconds::rep benchmarkWarmupTime = 100;

        Verbosity verbosity = Verbosity::Normal;
        WarnAbout::What warnings = WarnAbout::Nothing;
        ShowDurations::OrNot showDurations = ShowDurations::DefaultForReporter;
        double minDuration = -1;
        RunTests::InWhatOrder runOrder = RunTests::InDeclarationOrder;
        UseColour::YesOrNo useColour = UseColour::Auto;
        WaitForKeypress::When waitForKeypress = WaitForKeypress::Never;

        std::string outputFilename;
        std::string name;
        std::string processName;
#ifndef CATCH_CONFIG_DEFAULT_REPORTER
#define CATCH_CONFIG_DEFAULT_REPORTER "console"
#endif
        std::string reporterName = CATCH_CONFIG_DEFAULT_REPORTER;
#undef CATCH_CONFIG_DEFAULT_REPORTER

        std::vector<std::string> testsOrTags;
        std::vector<std::string> sectionsToRun;
    };

    class Config : public IConfig {
    public:

        Config() = default;
        Config( ConfigData const& data );
        virtual ~Config() = default;

        std::string const& getFilename() const;

        bool listTests() const;
        bool listTestNamesOnly() const;
        bool listTags() const;
        bool listReporters() const;

        std::string getProcessName() const;
        std::string const& getReporterName() const;

        std::vector<std::string> const& getTestsOrTags() const override;
        std::vector<std::string> const& getSectionsToRun() const override;

        TestSpec const& testSpec() const override;
        bool hasTestFilters() const override;

        bool showHelp() const;

        // IConfig interface
        bool allowThrows() const override;
        std::ostream& stream() const override;
        std::string name() const override;
        bool includeSuccessfulResults() const override;
        bool warnAboutMissingAssertions() const override;
        bool warnAboutNoTests() const override;
        ShowDurations::OrNot showDurations() const override;
        double minDuration() const override;
        RunTests::InWhatOrder runOrder() const override;
        unsigned int rngSeed() const override;
        UseColour::YesOrNo useColour() const override;
        bool shouldDebugBreak() const override;
        int abortAfter() const override;
        bool showInvisibles() const override;
        Verbosity verbosity() const override;
        bool benchmarkNoAnalysis() const override;
        int benchmarkSamples() const override;
        double benchmarkConfidenceInterval() const override;
        unsigned int benchmarkResamples() const override;
        std::chrono::milliseconds benchmarkWarmupTime() const override;

    private:

        IStream const* openStream();
        ConfigData m_data;

        std::unique_ptr<IStream const> m_stream;
        TestSpec m_testSpec;
        bool m_hasTestFilters = false;
    };

} // end namespace Catch

// end catch_config.hpp
// start catch_assertionresult.h

#include <string>

namespace Catch {

    struct AssertionResultData
    {
        AssertionResultData() = delete;

        AssertionResultData( ResultWas::OfType _resultType, LazyExpression const& _lazyExpression );

        std::string message;
        mutable std::string reconstructedExpression;
        LazyExpression lazyExpression;
        ResultWas::OfType resultType;

        std::string reconstructExpression() const;
    };

    class AssertionResult {
    public:
        AssertionResult() = delete;
        AssertionResult( AssertionInfo const& info, AssertionResultData const& data );

        bool isOk() const;
        bool succeeded() const;
        ResultWas::OfType getResultType() const;
        bool hasExpression() const;
        bool hasMessage() const;
        std::string getExpression() const;
        std::string getExpressionInMacro() const;
        bool hasExpandedExpression() const;
        std::string getExpandedExpression() const;
        std::string getMessage() const;
        SourceLineInfo getSourceInfo() const;
        StringRef getTestMacroName() const;

    //protected:
        AssertionInfo m_info;
        AssertionResultData m_resultData;
    };

} // end namespace Catch

// end catch_assertionresult.h
#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
// start catch_estimate.hpp

 // Statistics estimates


namespace Catch {
    namespace Benchmark {
        template <typename Duration>
        struct Estimate {
            Duration point;
            Duration lower_bound;
            Duration upper_bound;
            double confidence_interval;

            template <typename Duration2>
            operator Estimate<Duration2>() const {
                return { point, lower_bound, upper_bound, confidence_interval };
            }
        };
    } // namespace Benchmark
} // namespace Catch

// end catch_estimate.hpp
// start catch_outlier_classification.hpp

// Outlier information

namespace Catch {
    namespace Benchmark {
        struct OutlierClassification {
            int samples_seen = 0;
            int low_severe = 0;     // more than 3 times IQR below Q1
            int low_mild = 0;       // 1.5 to 3 times IQR below Q1
            int high_mild = 0;      // 1.5 to 3 times IQR above Q3
            int high_severe = 0;    // more than 3 times IQR above Q3

            int total() const {
                return low_severe + low_mild + high_mild + high_severe;
            }
        };
    } // namespace Benchmark
} // namespace Catch

// end catch_outlier_classification.hpp
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

#include <string>
#include <iosfwd>
#include <map>
#include <set>
#include <memory>
#include <algorithm>

namespace Catch {

    struct ReporterConfig {
        explicit ReporterConfig( IConfigPtr const& _fullConfig );

        ReporterConfig( IConfigPtr const& _fullConfig, std::ostream& _stream );

        std::ostream& stream() const;
        IConfigPtr fullConfig() const;

    private:
        std::ostream* m_stream;
        IConfigPtr m_fullConfig;
    };

    struct ReporterPreferences {
        bool shouldRedirectStdOut = false;
        bool shouldReportAllAssertions = false;
    };

    template<typename T>
    struct LazyStat : Option<T> {
        LazyStat& operator=( T const& _value ) {
            Option<T>::operator=( _value );
            used = false;
            return *this;
        }
        void reset() {
            Option<T>::reset();
            used = false;
        }
        bool used = false;
    };

    struct TestRunInfo {
        TestRunInfo( std::string const& _name );
        std::string name;
    };
    struct GroupInfo {
        GroupInfo(  std::string const& _name,
                    std::size_t _groupIndex,
                    std::size_t _groupsCount );

        std::string name;
        std::size_t groupIndex;
        std::size_t groupsCounts;
    };

    struct AssertionStats {
        AssertionStats( AssertionResult const& _assertionResult,
                        std::vector<MessageInfo> const& _infoMessages,
                        Totals const& _totals );

        AssertionStats( AssertionStats const& )              = default;
        AssertionStats( AssertionStats && )                  = default;
        AssertionStats& operator = ( AssertionStats const& ) = delete;
        AssertionStats& operator = ( AssertionStats && )     = delete;
        virtual ~AssertionStats();

        AssertionResult assertionResult;
        std::vector<MessageInfo> infoMessages;
        Totals totals;
    };

    struct SectionStats {
        SectionStats(   SectionInfo const& _sectionInfo,
                        Counts const& _assertions,
                        double _durationInSeconds,
                        bool _missingAssertions );
        SectionStats( SectionStats const& )              = default;
        SectionStats( SectionStats && )                  = default;
        SectionStats& operator = ( SectionStats const& ) = default;
        SectionStats& operator = ( SectionStats && )     = default;
        virtual ~SectionStats();

        SectionInfo sectionInfo;
        Counts assertions;
        double durationInSeconds;
        bool missingAssertions;
    };

    struct TestCaseStats {
        TestCaseStats(  TestCaseInfo const& _testInfo,
                        Totals const& _totals,
                        std::string const& _stdOut,
                        std::string const& _stdErr,
                        bool _aborting );

        TestCaseStats( TestCaseStats const& )              = default;
        TestCaseStats( TestCaseStats && )                  = default;
        TestCaseStats& operator = ( TestCaseStats const& ) = default;
        TestCaseStats& operator = ( TestCaseStats && )     = default;
        virtual ~TestCaseStats();

        TestCaseInfo testInfo;
        Totals totals;
        std::string stdOut;
        std::string stdErr;
        bool aborting;
    };

    struct TestGroupStats {
        TestGroupStats( GroupInfo const& _groupInfo,
                        Totals const& _totals,
                        bool _aborting );
        TestGroupStats( GroupInfo const& _groupInfo );

        TestGroupStats( TestGroupStats const& )              = default;
        TestGroupStats( TestGroupStats && )                  = default;
        TestGroupStats& operator = ( TestGroupStats const& ) = default;
        TestGroupStats& operator = ( TestGroupStats && )     = default;
        virtual ~TestGroupStats();

        GroupInfo groupInfo;
        Totals totals;
        bool aborting;
    };

    struct TestRunStats {
        TestRunStats(   TestRunInfo const& _runInfo,
                        Totals const& _totals,
                        bool _aborting );

        TestRunStats( TestRunStats const& )              = default;
        TestRunStats( TestRunStats && )                  = default;
        TestRunStats& operator = ( TestRunStats const& ) = default;
        TestRunStats& operator = ( TestRunStats && )     = default;
        virtual ~TestRunStats();

        TestRunInfo runInfo;
        Totals totals;
        bool aborting;
    };

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
    struct BenchmarkInfo {
        std::string name;
        double estimatedDuration;
        int iterations;
        int samples;
        unsigned int resamples;
        double clockResolution;
        double clockCost;
    };

    template <class Duration>
    struct BenchmarkStats {
        BenchmarkInfo info;

        std::vector<Duration> samples;
        Benchmark::Estimate<Duration> mean;
        Benchmark::Estimate<Duration> standardDeviation;
        Benchmark::OutlierClassification outliers;
        double outlierVariance;

        template <typename Duration2>
        operator BenchmarkStats<Duration2>() const {
            std::vector<Duration2> samples2;
            samples2.reserve(samples.size());
            std::transform(samples.begin(), samples.end(), std::back_inserter(samples2), [](Duration d) { return Duration2(d); });
            return {
                info,
                std::move(samples2),
                mean,
                standardDeviation,
                outliers,
                outlierVariance,
            };
        }
    };
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

    struct IStreamingReporter {
        virtual ~IStreamingReporter() = default;

        // Implementing class must also provide the following static methods:
        // static std::string getDescription();
        // static std::set<Verbosity> getSupportedVerbosities()

        virtual ReporterPreferences getPreferences() const = 0;

        virtual void noMatchingTestCases( std::string const& spec ) = 0;

        virtual void reportInvalidArguments(std::string const&) {}

        virtual void testRunStarting( TestRunInfo const& testRunInfo ) = 0;
        virtual void testGroupStarting( GroupInfo const& groupInfo ) = 0;

        virtual void testCaseStarting( TestCaseInfo const& testInfo ) = 0;
        virtual void sectionStarting( SectionInfo const& sectionInfo ) = 0;

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
        virtual void benchmarkPreparing( std::string const& ) {}
        virtual void benchmarkStarting( BenchmarkInfo const& ) {}
        virtual void benchmarkEnded( BenchmarkStats<> const& ) {}
        virtual void benchmarkFailed( std::string const& ) {}
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

        virtual void assertionStarting( AssertionInfo const& assertionInfo ) = 0;

        // The return value indicates if the messages buffer should be cleared:
        virtual bool assertionEnded( AssertionStats const& assertionStats ) = 0;

        virtual void sectionEnded( SectionStats const& sectionStats ) = 0;
        virtual void testCaseEnded( TestCaseStats const& testCaseStats ) = 0;
        virtual void testGroupEnded( TestGroupStats const& testGroupStats ) = 0;
        virtual void testRunEnded( TestRunStats const& testRunStats ) = 0;

        virtual void skipTest( TestCaseInfo const& testInfo ) = 0;

        // Default empty implementation provided
        virtual void fatalErrorEncountered( StringRef name );

        virtual bool isMulti() const;
    };
    using IStreamingReporterPtr = std::unique_ptr<IStreamingReporter>;

    struct IReporterFactory {
        virtual ~IReporterFactory();
        virtual IStreamingReporterPtr create( ReporterConfig const& config ) const = 0;
        virtual std::string getDescription() const = 0;
    };
    using IReporterFactoryPtr = std::shared_ptr<IReporterFactory>;

    struct IReporterRegistry {
        using FactoryMap = std::map<std::string, IReporterFactoryPtr>;
        using Listeners = std::vector<IReporterFactoryPtr>;

        virtual ~IReporterRegistry();
        virtual IStreamingReporterPtr create( std::string const& name, IConfigPtr const& config ) const = 0;
        virtual FactoryMap const& getFactories() const = 0;
        virtual Listeners const& getListeners() const = 0;
    };

} // end namespace Catch

// end catch_interfaces_reporter.h
#include <algorithm>
#include <cstring>
#include <cfloat>
#include <cstdio>
#include <cassert>
#include <memory>
#include <ostream>

namespace Catch {
    void prepareExpandedExpression(AssertionResult& result);

    // Returns double formatted as %.3f (format expected on output)
    std::string getFormattedDuration( double duration );

    //! Should the reporter show
    bool shouldShowDuration( IConfig const& config, double duration );

    std::string serializeFilters( std::vector<std::string> const& container );

    template<typename DerivedT>
    struct StreamingReporterBase : IStreamingReporter {

        StreamingReporterBase( ReporterConfig const& _config )
        :   m_config( _config.fullConfig() ),
            stream( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = false;
            if( !DerivedT::getSupportedVerbosities().count( m_config->verbosity() ) )
                CATCH_ERROR( "Verbosity level not supported by this reporter" );
        }

        ReporterPreferences getPreferences() const override {
            return m_reporterPrefs;
        }

        static std::set<Verbosity> getSupportedVerbosities() {
            return { Verbosity::Normal };
        }

        ~StreamingReporterBase() override = default;

        void noMatchingTestCases(std::string const&) override {}

        void reportInvalidArguments(std::string const&) override {}

        void testRunStarting(TestRunInfo const& _testRunInfo) override {
            currentTestRunInfo = _testRunInfo;
        }

        void testGroupStarting(GroupInfo const& _groupInfo) override {
            currentGroupInfo = _groupInfo;
        }

        void testCaseStarting(TestCaseInfo const& _testInfo) override  {
            currentTestCaseInfo = _testInfo;
        }
        void sectionStarting(SectionInfo const& _sectionInfo) override {
            m_sectionStack.push_back(_sectionInfo);
        }

        void sectionEnded(SectionStats const& /* _sectionStats */) override {
            m_sectionStack.pop_back();
        }
        void testCaseEnded(TestCaseStats const& /* _testCaseStats */) override {
            currentTestCaseInfo.reset();
        }
        void testGroupEnded(TestGroupStats const& /* _testGroupStats */) override {
            currentGroupInfo.reset();
        }
        void testRunEnded(TestRunStats const& /* _testRunStats */) override {
            currentTestCaseInfo.reset();
            currentGroupInfo.reset();
            currentTestRunInfo.reset();
        }

        void skipTest(TestCaseInfo const&) override {
            // Don't do anything with this by default.
            // It can optionally be overridden in the derived class.
        }

        IConfigPtr m_config;
        std::ostream& stream;

        LazyStat<TestRunInfo> currentTestRunInfo;
        LazyStat<GroupInfo> currentGroupInfo;
        LazyStat<TestCaseInfo> currentTestCaseInfo;

        std::vector<SectionInfo> m_sectionStack;
        ReporterPreferences m_reporterPrefs;
    };

    template<typename DerivedT>
    struct CumulativeReporterBase : IStreamingReporter {
        template<typename T, typename ChildNodeT>
        struct Node {
            explicit Node( T const& _value ) : value( _value ) {}
            virtual ~Node() {}

            using ChildNodes = std::vector<std::shared_ptr<ChildNodeT>>;
            T value;
            ChildNodes children;
        };
        struct SectionNode {
            explicit SectionNode(SectionStats const& _stats) : stats(_stats) {}
            virtual ~SectionNode() = default;

            bool operator == (SectionNode const& other) const {
                return stats.sectionInfo.lineInfo == other.stats.sectionInfo.lineInfo;
            }
            bool operator == (std::shared_ptr<SectionNode> const& other) const {
                return operator==(*other);
            }

            SectionStats stats;
            using ChildSections = std::vector<std::shared_ptr<SectionNode>>;
            using Assertions = std::vector<AssertionStats>;
            ChildSections childSections;
            Assertions assertions;
            std::string stdOut;
            std::string stdErr;
        };

        struct BySectionInfo {
            BySectionInfo( SectionInfo const& other ) : m_other( other ) {}
            BySectionInfo( BySectionInfo const& other ) : m_other( other.m_other ) {}
            bool operator() (std::shared_ptr<SectionNode> const& node) const {
                return ((node->stats.sectionInfo.name == m_other.name) &&
                        (node->stats.sectionInfo.lineInfo == m_other.lineInfo));
            }
            void operator=(BySectionInfo const&) = delete;

        private:
            SectionInfo const& m_other;
        };

        using TestCaseNode = Node<TestCaseStats, SectionNode>;
        using TestGroupNode = Node<TestGroupStats, TestCaseNode>;
        using TestRunNode = Node<TestRunStats, TestGroupNode>;

        CumulativeReporterBase( ReporterConfig const& _config )
        :   m_config( _config.fullConfig() ),
            stream( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = false;
            if( !DerivedT::getSupportedVerbosities().count( m_config->verbosity() ) )
                CATCH_ERROR( "Verbosity level not supported by this reporter" );
        }
        ~CumulativeReporterBase() override = default;

        ReporterPreferences getPreferences() const override {
            return m_reporterPrefs;
        }

        static std::set<Verbosity> getSupportedVerbosities() {
            return { Verbosity::Normal };
        }

        void testRunStarting( TestRunInfo const& ) override {}
        void testGroupStarting( GroupInfo const& ) override {}

        void testCaseStarting( TestCaseInfo const& ) override {}

        void sectionStarting( SectionInfo const& sectionInfo ) override {
            SectionStats incompleteStats( sectionInfo, Counts(), 0, false );
            std::shared_ptr<SectionNode> node;
            if( m_sectionStack.empty() ) {
                if( !m_rootSection )
                    m_rootSection = std::make_shared<SectionNode>( incompleteStats );
                node = m_rootSection;
            }
            else {
                SectionNode& parentNode = *m_sectionStack.back();
                auto it =
                    std::find_if(   parentNode.childSections.begin(),
                                    parentNode.childSections.end(),
                                    BySectionInfo( sectionInfo ) );
                if( it == parentNode.childSections.end() ) {
                    node = std::make_shared<SectionNode>( incompleteStats );
                    parentNode.childSections.push_back( node );
                }
                else
                    node = *it;
            }
            m_sectionStack.push_back( node );
            m_deepestSection = std::move(node);
        }

        void assertionStarting(AssertionInfo const&) override {}

        bool assertionEnded(AssertionStats const& assertionStats) override {
            assert(!m_sectionStack.empty());
            // AssertionResult holds a pointer to a temporary DecomposedExpression,
            // which getExpandedExpression() calls to build the expression string.
            // Our section stack copy of the assertionResult will likely outlive the
            // temporary, so it must be expanded or discarded now to avoid calling
            // a destroyed object later.
            prepareExpandedExpression(const_cast<AssertionResult&>( assertionStats.assertionResult ) );
            SectionNode& sectionNode = *m_sectionStack.back();
            sectionNode.assertions.push_back(assertionStats);
            return true;
        }
        void sectionEnded(SectionStats const& sectionStats) override {
            assert(!m_sectionStack.empty());
            SectionNode& node = *m_sectionStack.back();
            node.stats = sectionStats;
            m_sectionStack.pop_back();
        }
        void testCaseEnded(TestCaseStats const& testCaseStats) override {
            auto node = std::make_shared<TestCaseNode>(testCaseStats);
            assert(m_sectionStack.size() == 0);
            node->children.push_back(m_rootSection);
            m_testCases.push_back(node);
            m_rootSection.reset();

            assert(m_deepestSection);
            m_deepestSection->stdOut = testCaseStats.stdOut;
            m_deepestSection->stdErr = testCaseStats.stdErr;
        }
        void testGroupEnded(TestGroupStats const& testGroupStats) override {
            auto node = std::make_shared<TestGroupNode>(testGroupStats);
            node->children.swap(m_testCases);
            m_testGroups.push_back(node);
        }
        void testRunEnded(TestRunStats const& testRunStats) override {
            auto node = std::make_shared<TestRunNode>(testRunStats);
            node->children.swap(m_testGroups);
            m_testRun
