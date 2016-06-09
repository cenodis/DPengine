#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef _WIN32
    typedef char GLchar;
    #include <GL/gl.h>
    #include <windows.h>
    #define GL_COMPILE_STATUS                 0x8B81
    #define GL_LINK_STATUS                    0x8B82
    #define GL_VALIDATE_STATUS                0x8B83
    #define GL_FRAGMENT_SHADER                0x8B30
    #define GL_VERTEX_SHADER                  0x8B31
    #define GL_READ_ONLY                      0x88B8
    #define GL_PIXEL_PACK_BUFFER              0x88EB
    #define GL_READ_FRAMEBUFFER               0x8CA8
    #define GL_DRAW_FRAMEBUFFER               0x8CA9
    #define GL_FRAMEBUFFER                    0x8D40
    #define GL_RENDERBUFFER                   0x8D41
    #define GL_COLOR_ATTACHMENT0              0x8CE0
    #define GL_TEXTURE0                       0x84C0
    #define GL_TEXTURE_CUBE_MAP               0x8513
    #define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
    #define GL_TEXTURE_WRAP_R                 0x8072
    #define GL_TEXTURE_3D                     0x806F
    #define GL_TEXTURE_2D_ARRAY               0x8C1A
    #define GL_ARRAY_BUFFER                   0x8892
    #define GL_ELEMENT_ARRAY_BUFFER           0x8893
    #define GL_DEPTH_COMPONENT16              0x81A5
    #define GL_DEPTH_COMPONENT24              0x81A6
    #define GL_DEPTH_COMPONENT32              0x81A7
    #define GL_DEPTH_ATTACHMENT               0x8D00
    #define GL_STREAM_READ                    0x88E1
    #define GL_STREAM_DRAW                    0x88E0
    #define GL_STATIC_DRAW                    0x88E4
    #define GL_DYNAMIC_DRAW                   0x88E8
    #define GL_CLAMP_TO_EDGE                  0x812F
    #define GL_R8                             0x8229
    #define GL_RG8                            0x822B
    #define GL_RED                            0x1903
    #define GL_RED_INTEGER                    0x8D94
    #define GL_RG                             0x8227
    #define GL_RG_INTEGER                     0x8228
    #define GL_RGB_INTEGER                    0x8D98
    #define GL_RGBA_INTEGER                   0x8D99
    #define GL_BGR_INTEGER                    0x8D9A
    #define GL_BGRA_INTEGER                   0x8D9B
    #define GL_BGRA                           0x80E1
    #define GL_R32F                           0x822E
    #define GL_RG32F                          0x8230
    #define GL_RGB32F                         0x8815
    #define GL_RGBA32F                        0x8814
    #define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
    #define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
    #define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
    #define WGL_CONTEXT_FLAGS_ARB             0x2094
    #define GL_GET_PROC_ADDR(s)  wglGetProcAddress(s)
#elif __APPLE__
    #include <OpenGL/gl.h>
    #include <dlfcn.h>
    #define APIENTRY
    #define GL_RGBA32F                      0x8814
    #define GL_TEXTURE_2D_ARRAY             0x8C1A
    #define GL_GET_PROC_ADDR(s)  dlsym(RTLD_DEFAULT, s)
#else
    #include <GL/gl.h>
    #include <GL/glx.h>
    #define GL_GET_PROC_ADDR(s)  glXGetProcAddress((GLubyte*)(s))
#endif



#define PARTS_OF_OPENGL_FUNCTIONS \
    "iv",       \
    "fv",       \
    "buffer",   \
    "Buffer",   \
    "Data",     \
    "Get",      \
    "Gen",      \
    "Bind",     \
    "Create",   \
    "Delete",   \
    "Program",  \
    "Shader",   \
    "Attrib",   \
    "Uniform",  \
    "Location", \
    "Vertex",   \
    "Texture",  \
    "Frame",    \
    "Render",   \
    "InfoLog",  \
    "EXT"

#define NV_vertex_program3     0x80000000
#define EXT_framebuffer_object 0x00000001

/// Sorry for this...  (._.)
#define MASKED_STRING_OPENGL_FUNCTIONS \
    {/** glUniform1iv                 **/ "\x0E""1\x01",           }, \
    {/** glUniform1fv                 **/ "\x0E""1\x02",           }, \
    {/** glUniform2iv                 **/ "\x0E""2\x01",           }, \
    {/** glUniform2fv                 **/ "\x0E""2\x02",           }, \
    {/** glUniform3iv                 **/ "\x0E""3\x01",           }, \
    {/** glUniform3fv                 **/ "\x0E""3\x02",           }, \
    {/** glUniform4iv                 **/ "\x0E""4\x01",           }, \
    {/** glUniform4fv                 **/ "\x0E""4\x02",           }, \
    {/** glUniformMatrix4fv           **/ "\x0E""Matrix4\x02",     }, \
    {/** glCreateProgram              **/ "\x09\x0B",              }, \
    {/** glDeleteProgram              **/ "\x0A\x0B",              }, \
    {/** glValidateProgram            **/ "Validate\x0B",          }, \
    {/** glLinkProgram                **/ "Link\x0B",              }, \
    {/** glUseProgram                 **/ "Use\x0B",               }, \
    {/** glGetProgramInfoLog          **/ "\x06\x0B\x14",          }, \
    {/** glGetShaderInfoLog           **/ "\x06\x0C\x14",          }, \
    {/** glGetProgramiv               **/ "\x06\x0B\x01",          }, \
    {/** glGetShaderiv                **/ "\x06\x0C\x01",          }, \
    {/** glCreateShader               **/ "\x09\x0C",              }, \
    {/** glDeleteShader               **/ "\x0A\x0C",              }, \
    {/** glAttachShader               **/ "Attach\x0C",            }, \
    {/** glShaderSource               **/ "\x0C""Source",          }, \
    {/** glCompileShader              **/ "Compile\x0C",           }, \
    {/** glGetAttribLocation          **/ "\x06\x0D\x0F",          }, \
    {/** glGetUniformLocation         **/ "\x06\x0E\x0F",          }, \
    {/** glEnableVertexAttribArray    **/ "Enable\x10\x0D""Array", }, \
    {/** glVertexAttribPointer        **/ "\x10\x0D""Pointer",     }, \
    {/** glActiveTexture              **/ "Active\x11",            }, \
    {/** glTexImage3D                 **/ "TexImage3D",            }, \
    {/** glGenBuffers                 **/ "\x07\x04""s",           }, \
    {/** glBindBuffer                 **/ "\x08\x04",              }, \
    {/** glBufferData                 **/ "\x04\x05",              }, \
    {/** glBufferSubData              **/ "\x04""Sub\x05",         }, \
    {/** glDeleteBuffers              **/ "\x0A\x04""s",           }, \
    {/** glMapBuffer                  **/ "Map\x04",               }, \
    {/** glUnmapBuffer                **/ "Unmap\x04",             }, \
    {/** glGenFramebuffersEXT         **/ "\x07\x12\x03""s\x15",   EXT_framebuffer_object}, \
    {/** glGenRenderbuffersEXT        **/ "\x07\x13\x03""s\x15",   EXT_framebuffer_object}, \
    {/** glDeleteFramebuffersEXT      **/ "\x0A\x12\x03""s\x15",   EXT_framebuffer_object}, \
    {/** glDeleteRenderbuffersEXT     **/ "\x0A\x13\x03""s\x15",   EXT_framebuffer_object}, \
    {/** glBindFramebufferEXT         **/ "\x08\x12\x03\x15",      EXT_framebuffer_object}, \
    {/** glBindRenderbufferEXT        **/ "\x08\x13\x03\x15",      EXT_framebuffer_object}, \
    {/** glRenderbufferStorageEXT     **/ "\x13\x03""Storage\x15", EXT_framebuffer_object}, \
    {/** glFramebufferTexture2DEXT    **/ "\x12\x03\x11""2D\x15",  EXT_framebuffer_object}, \
    {/** glFramebufferRenderbufferEXT **/ "\x12\x03\x13\x03\x15",  EXT_framebuffer_object}

/// uniform type constants have to match the corresponding
/// uniform loaders in LoadedOpenGLFunctions[] table
#define UNI_T1IV 0
#define UNI_T1FV 1

#define UNI_T2IV 2
#define UNI_T2FV 3

#define UNI_T3IV 4
#define UNI_T3FV 5

#define UNI_T4IV 6
#define UNI_T4FV 7

#define UNI_TMFV 8

/// minimum and maximum uniform type constants
#define UNI_TMIN 0
#define UNI_TMAX 8

/// this flag is to indicate that the uniform value is immediate
#define UNI_IIII 0x8000

/// immediate uniform types
#define UNI_T1II (UNI_T1IV | UNI_IIII)
#define UNI_T1FI (UNI_T1FV | UNI_IIII)

#define UNI_T2II (UNI_T2IV | UNI_IIII)
#define UNI_T2FI (UNI_T2FV | UNI_IIII)

#define UNI_T3II (UNI_T3IV | UNI_IIII)
#define UNI_T3FI (UNI_T3FV | UNI_IIII)

#define UNI_T4II (UNI_T4IV | UNI_IIII)
#define UNI_T4FI (UNI_T4FV | UNI_IIII)

#define UNI_TMFI (UNI_TMFV | UNI_IIII)

#define GL_UNI_FUNC(type, indx, size, vals) (((GLvoid APIENTRY (*)(GLint, GLsizei, GLvoid*))LoadedOpenGLFunctions[type])(indx, size, vals))

#define glUniform1iv               ((GLvoid  APIENTRY (*)(GLint  ,  GLsizei,  GLint*                                                                       ))LoadedOpenGLFunctions[UNI_T1IV])
#define glUniform1fv               ((GLvoid  APIENTRY (*)(GLint  ,  GLsizei,  GLfloat*                                                                     ))LoadedOpenGLFunctions[UNI_T1FV])
#define glUniform2iv               ((GLvoid  APIENTRY (*)(GLint  ,  GLsizei,  GLint*                                                                       ))LoadedOpenGLFunctions[UNI_T2IV])
#define glUniform2fv               ((GLvoid  APIENTRY (*)(GLint  ,  GLsizei,  GLfloat*                                                                     ))LoadedOpenGLFunctions[UNI_T2FV])
#define glUniform3iv               ((GLvoid  APIENTRY (*)(GLint  ,  GLsizei,  GLint*                                                                       ))LoadedOpenGLFunctions[UNI_T3IV])
#define glUniform3fv               ((GLvoid  APIENTRY (*)(GLint  ,  GLsizei,  GLfloat*                                                                     ))LoadedOpenGLFunctions[UNI_T3FV])
#define glUniform4iv               ((GLvoid  APIENTRY (*)(GLint  ,  GLsizei,  GLint*                                                                       ))LoadedOpenGLFunctions[UNI_T4IV])
#define glUniform4fv               ((GLvoid  APIENTRY (*)(GLint  ,  GLsizei,  GLfloat*                                                                     ))LoadedOpenGLFunctions[UNI_T4FV])
#define glUniformMatrix4fv         ((GLvoid  APIENTRY (*)(GLint  ,  GLsizei,  GLboolean,  GLfloat*                                                         ))LoadedOpenGLFunctions[UNI_TMFV])
/// uniform functions end here
#define glCreateProgram            ((GLuint  APIENTRY (*)(GLvoid                                                                                           ))LoadedOpenGLFunctions[UNI_TMAX +  1])
#define glDeleteProgram            ((GLvoid  APIENTRY (*)(GLuint                                                                                           ))LoadedOpenGLFunctions[UNI_TMAX +  2])
#define glValidateProgram          ((GLvoid  APIENTRY (*)(GLuint                                                                                           ))LoadedOpenGLFunctions[UNI_TMAX +  3])
#define glLinkProgram              ((GLvoid  APIENTRY (*)(GLuint                                                                                           ))LoadedOpenGLFunctions[UNI_TMAX +  4])
#define glUseProgram               ((GLvoid  APIENTRY (*)(GLuint                                                                                           ))LoadedOpenGLFunctions[UNI_TMAX +  5])
#define glGetProgramInfoLog        ((GLvoid  APIENTRY (*)(GLuint ,  GLint  ,  GLint*   ,  GLchar*                                                          ))LoadedOpenGLFunctions[UNI_TMAX +  6])
#define glGetShaderInfoLog         ((GLvoid  APIENTRY (*)(GLuint ,  GLint  ,  GLint*   ,  GLchar*                                                          ))LoadedOpenGLFunctions[UNI_TMAX +  7])
#define glGetProgramiv             ((GLvoid  APIENTRY (*)(GLuint ,  GLenum ,  GLint*                                                                       ))LoadedOpenGLFunctions[UNI_TMAX +  8])
#define glGetShaderiv              ((GLvoid  APIENTRY (*)(GLuint ,  GLenum ,  GLint*                                                                       ))LoadedOpenGLFunctions[UNI_TMAX +  9])
#define glCreateShader             ((GLuint  APIENTRY (*)(GLenum                                                                                           ))LoadedOpenGLFunctions[UNI_TMAX + 10])
#define glDeleteShader             ((GLvoid  APIENTRY (*)(GLuint                                                                                           ))LoadedOpenGLFunctions[UNI_TMAX + 11])
#define glAttachShader             ((GLvoid  APIENTRY (*)(GLuint ,  GLuint                                                                                 ))LoadedOpenGLFunctions[UNI_TMAX + 12])
#define glShaderSource             ((GLvoid  APIENTRY (*)(GLuint ,  GLuint ,  GLchar** ,  GLuint*                                                          ))LoadedOpenGLFunctions[UNI_TMAX + 13])
#define glCompileShader            ((GLvoid  APIENTRY (*)(GLuint                                                                                           ))LoadedOpenGLFunctions[UNI_TMAX + 14])
#define glGetAttribLocation        ((GLint   APIENTRY (*)(GLuint ,  GLchar*                                                                                ))LoadedOpenGLFunctions[UNI_TMAX + 15])
#define glGetUniformLocation       ((GLint   APIENTRY (*)(GLuint ,  GLchar*                                                                                ))LoadedOpenGLFunctions[UNI_TMAX + 16])
#define glEnableVertexAttribArray  ((GLvoid  APIENTRY (*)(GLint                                                                                            ))LoadedOpenGLFunctions[UNI_TMAX + 17])
#define glVertexAttribPointer      ((GLvoid  APIENTRY (*)(GLuint ,  GLint  ,  GLenum   ,  GLboolean,  GLsizei,  GLvoid*                                    ))LoadedOpenGLFunctions[UNI_TMAX + 18])
#define glActiveTexture            ((GLvoid  APIENTRY (*)(GLenum                                                                                           ))LoadedOpenGLFunctions[UNI_TMAX + 19])
#define glTexImage3D               ((GLvoid  APIENTRY (*)(GLenum ,  GLint  ,  GLenum   ,  GLsizei  ,  GLsizei,  GLsizei,  GLint,  GLenum,  GLenum,  GLvoid*))LoadedOpenGLFunctions[UNI_TMAX + 20])
#define glGenBuffers               ((GLvoid  APIENTRY (*)(GLsizei,  GLuint*                                                                                ))LoadedOpenGLFunctions[UNI_TMAX + 21])
#define glBindBuffer               ((GLvoid  APIENTRY (*)(GLenum ,  GLuint                                                                                 ))LoadedOpenGLFunctions[UNI_TMAX + 22])
#define glBufferData               ((GLvoid  APIENTRY (*)(GLenum ,  GLsizei,  GLvoid*  ,  GLenum                                                           ))LoadedOpenGLFunctions[UNI_TMAX + 23])
#define glBufferSubData            ((GLvoid  APIENTRY (*)(GLenum ,  GLint  ,  GLsizei  ,  GLvoid*                                                          ))LoadedOpenGLFunctions[UNI_TMAX + 24])
#define glDeleteBuffers            ((GLvoid  APIENTRY (*)(GLsizei,  GLuint*                                                                                ))LoadedOpenGLFunctions[UNI_TMAX + 25])
#define glMapBuffer                ((GLvoid* APIENTRY (*)(GLenum ,  GLenum                                                                                 ))LoadedOpenGLFunctions[UNI_TMAX + 26])
#define glUnmapBuffer              ((GLvoid  APIENTRY (*)(GLenum                                                                                           ))LoadedOpenGLFunctions[UNI_TMAX + 27])
#define glGenFramebuffers          ((GLvoid  APIENTRY (*)(GLsizei,  GLuint*                                                                                ))LoadedOpenGLFunctions[UNI_TMAX + 28])
#define glGenRenderbuffers         ((GLvoid  APIENTRY (*)(GLsizei,  GLuint*                                                                                ))LoadedOpenGLFunctions[UNI_TMAX + 29])
#define glDeleteFramebuffers       ((GLvoid  APIENTRY (*)(GLsizei,  GLuint*                                                                                ))LoadedOpenGLFunctions[UNI_TMAX + 30])
#define glDeleteRenderbuffers      ((GLvoid  APIENTRY (*)(GLsizei,  GLuint*                                                                                ))LoadedOpenGLFunctions[UNI_TMAX + 31])
#define glBindFramebuffer          ((GLvoid  APIENTRY (*)(GLenum ,  GLuint                                                                                 ))LoadedOpenGLFunctions[UNI_TMAX + 32])
#define glBindRenderbuffer         ((GLvoid  APIENTRY (*)(GLenum ,  GLuint                                                                                 ))LoadedOpenGLFunctions[UNI_TMAX + 33])
#define glRenderbufferStorage      ((GLvoid  APIENTRY (*)(GLenum ,  GLenum ,  GLsizei  ,  GLsizei                                                          ))LoadedOpenGLFunctions[UNI_TMAX + 34])
#define glFramebufferTexture2D     ((GLvoid  APIENTRY (*)(GLenum ,  GLenum ,  GLenum   ,  GLuint   ,  GLint                                                ))LoadedOpenGLFunctions[UNI_TMAX + 35])
#define glFramebufferRenderbuffer  ((GLvoid  APIENTRY (*)(GLenum ,  GLenum ,  GLenum   ,  GLuint                                                           ))LoadedOpenGLFunctions[UNI_TMAX + 36])

#ifndef countof
#define countof(a) (sizeof(a) / sizeof(*(a)))
#endif

#define DTR_CONV (M_PI / 180.0)
#define RTD_CONV (1.0 / DTR_CONV)

#define TEX_NSET 0
#define TEX_DFLT 1
#define TEX_FRMB 2



typedef struct _FTEX {
    GLenum type;
    GLuint indx, xdim, ydim, zdim;
    struct _FVBO *orig;
} FTEX;

typedef struct _UNIF {
    GLenum type, draw;
    GLuint indx, cdat;
    GLvoid *pdat;
    GLchar *name;
} UNIF;

typedef struct _SHDR {
    GLuint prog, cuni;
    UNIF *puni;
} SHDR;

typedef struct _FVBO {
    GLenum  elem;
    GLuint  cind;
    GLuint  cvbo;
    GLuint *pvbo;
    GLuint  ctex;
    FTEX   *ptex;
    GLuint  cshd;
    SHDR   *pshd;
} FVBO;



GLvoid MakeShaderSrc(GLchar ***sver, GLchar ***spix,
                     GLchar  **tver, GLchar  **tpix, ...);
GLvoid FreeShaderSrc(GLchar  **sver, GLchar  **spix);

FTEX  *BindTex(FVBO  *vobj, GLuint bind, GLuint mode);
GLuint MakeTex(FTEX  *retn, GLuint xdim, GLuint ydim, GLuint  zdim,
               GLenum trgt, GLenum wrap, GLint  tmag, GLint   tmin,
               GLenum type, GLenum frmt, GLenum mode, GLvoid *data);

FVBO  *MakeVBO(FVBO *prev, GLchar *vshd[], GLchar *pshd[], GLenum elem,
               GLuint catr, UNIF *patr, GLuint cuni, UNIF *puni, GLuint ctex);
GLvoid DrawVBO(FVBO *vobj, GLuint shad);
GLvoid FreeVBO(FVBO **vobj);

GLchar *LoadOpenGLFunctions(GLuint mask);

extern GLvoid *LoadedOpenGLFunctions[];
