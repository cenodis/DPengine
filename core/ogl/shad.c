#include "unit.h"
#include <stdarg.h>



GLint ShaderProgramStatus(GLuint prog, GLboolean shad, GLenum parm) {
    GLchar buff[2048];
    GLint stat, slen;

    switch (shad) {
        case GL_FALSE:
            glGetProgramiv(prog, parm, &stat);
            if (stat != GL_TRUE) {
                glGetProgramInfoLog(prog, carrsz(buff), &slen, buff);
                printf("Shader program: %s\n", (GLchar*)buff);
            }
            return stat;

        default:
            glGetShaderiv(prog, parm, &stat);
            if (stat != GL_TRUE) {
                glGetShaderInfoLog(prog, carrsz(buff), &slen, buff);
                printf("Shader: %s\n", (GLchar*)buff);
            }
            return stat;
    }
}



GLboolean ShaderAdd(GLchar *fstr, GLuint prog, GLenum type) {
    GLuint slen, shad;

    if (!(shad = glCreateShader(type))) {
        printf("Shader allocation failed (%d)\n", glGetError());
        glDeleteProgram(prog);
        return GL_FALSE;
    }
    slen = strlen(fstr);
    glShaderSource(shad, 1, &fstr, &slen);
    glCompileShader(shad);

    if (ShaderProgramStatus(shad, GL_TRUE, GL_COMPILE_STATUS) != GL_TRUE) {
        glDeleteShader(shad);
        glDeleteProgram(prog);
        return GL_FALSE;
    }
    glAttachShader(prog, shad);
    glDeleteShader(shad);
    return GL_TRUE;
}



SHDR *MakeShaderList(GLchar *vert[], GLchar *pixl[],
                     GLuint cuni, UNIF *puni, GLuint *cshd) {
    GLchar *curp = NULL, *curv = NULL;
    GLint ctmp, step, name, iter = 0;
    GLboolean stop = GL_FALSE;

    while (pixl[iter]) iter++;

    SHDR *retn = calloc(iter, sizeof(*retn));

    *cshd = iter;
    for (iter = 0; iter < *cshd; iter++) {
        if (pixl[iter] != (GLchar*)-1)
            curp = pixl[iter];
        if (!stop) {
            if (!vert[iter])
                stop = GL_TRUE;
            else if (vert[iter] != (GLchar*)-1)
                curv = vert[iter];
        }
        retn[iter].prog = glCreateProgram();
        ShaderAdd(curp, retn[iter].prog, GL_FRAGMENT_SHADER);
        ShaderAdd(curv, retn[iter].prog, GL_VERTEX_SHADER);
        glLinkProgram(retn[iter].prog);
        glUseProgramObjectARB(retn[iter].prog);
        glGenVertexArrays(1, &retn[iter].pvao);
        glBindVertexArray(retn[iter].pvao);

        for (retn[iter].cuni = ctmp = 0; ctmp < cuni; ctmp++)
            if ((name = glGetUniformLocation(retn[iter].prog,
                                             puni[ctmp].name)) != -1)
                retn[iter].cuni++;

        for (retn[iter].puni = malloc(retn[iter].cuni * sizeof(UNIF)),
             step = ctmp = 0; ctmp < cuni; ctmp++)
            if ((name = glGetUniformLocation(retn[iter].prog,
                                             puni[ctmp].name)) != -1) {
                retn[iter].puni[step] = puni[ctmp];
                retn[iter].puni[step++].name = (GLchar*)name;
            }
    }
    glUseProgramObjectARB(0);
    return retn;
}



char *shader(char *frmt, ...) {
    va_list list;
    char *retn;
    unsigned size;

    size = strlen(frmt);
    va_start(list, frmt);
    while ((retn = va_arg(list, char*)))
        size += strlen(retn);
    va_end(list);

    va_start(list, frmt);
    retn = (char*)calloc(1, size + 1);
    vsprintf(retn, frmt, list);
    va_end(list);

    return retn;
}



char *tver[] = {
/// surf - #: main vertex shader
"#version 130\n\
\n\
uniform usampler2D data;\n\
uniform sampler2D dims;\n\
uniform sampler2D bank;\n\
uniform vec2 disz;\n\
\n\
out vec4 vtex;\n\
out vec4 voff;\n\
\n\
%s\n\
\n\
void main() {\n\
    vec2   vert = vec2(((gl_VertexID + 0) >> 1) & 1,\n\
                       ((gl_VertexID + 1) >> 1) & 1);\n\
    uint   indx = uint(gl_VertexID) >> 2u;\n\
    uvec4  vdat = texelFetch(data, ivec2(indx & txsz, indx >> txlg), 0);\n\
    indx = vdat.y & 0xFFFFFu;\n\
    ivec2  offs = ivec2(indx & txsz, indx >> txlg);\n\
    vec4   vbnk = texelFetch(bank, offs, 0);\n\
    vec4   vdim = texelFetch(dims, offs, 0) \n\
         * vec4(0.5 - (0.5 - vert.x) * (1.0 - float((vdat.y >> 29) & 0x2u)),\n\
                0.5 + (0.5 - vert.y) * (1.0 - float((vdat.y >> 30) & 0x2u)),\n\
                1.0, 1.0);\n\
    indx <<= 8;\n\
    offs = ivec2((int(vdat.x) << 16) >> 16, int(vdat.x) >> 16);\n\
    vtex = vec4(vert.x * vdim.z, vert.y * vdim.w, vdim.z, 0.0);\n\
    voff = vec4(vbnk.y + ((vdat.y >> 20) & 0x3FFu) * vdim.z * vdim.w,\n\
                vbnk.x, indx & txsz, indx >> txlg);\n\
    if (voff.x >= vbnk.z) {\n\
        voff.x -= vbnk.z;\n\
        indx = uint(voff.x / vbnk.w);\n\
        voff.x -= float(indx * uint(vbnk.w));\n\
        voff.y += float(indx + 1u);\n\
    }\n\
    gl_Position = vec4((offs.x + vdim.z * vdim.x) * disz.x - 1.0,\n\
                      -(offs.y - vdim.w * vdim.y) * disz.y + 1.0,\n\
                       -offs.y * disz.y * 0.5 + 1.0, 1.0);\n\
}",

NULL};



char *tpix[] = {
/// surf - 0: display
"#version 130\n\
\n\
uniform usampler2DArray atex;\n\
uniform sampler2D apal;\n\
\n\
in vec4 vtex;\n\
in vec4 voff;\n\
\n\
%s\n\
\n\
void main() {\n\
    uint  offs = uint(voff.x) + uint(vtex.x) + uint(vtex.y) * uint(vtex.z);\n\
    uvec4 indx = texelFetch(atex,\n\
                            ivec3(offs & txsz, offs >> txlg, voff.y), 0);\n\
    if (indx.x == 0xFFu) discard;\n\
    gl_FragColor = texelFetch(apal, ivec2(voff.z + indx.x, voff.w), 0);\n\
}",

NULL};



char **sver, **spix;



GLvoid MakeShaderSrc(GLuint logt) {
    char cons[256];
    long iter;

    sver = calloc(1, sizeof(tver));
    spix = calloc(1, sizeof(tpix));
    sprintf(cons, "const uint txsz = %uu, txlg = %uu;",
           (1 << logt) - 1, logt);

    for (iter = carrsz(tver) - 2; iter >= 0; iter--)
        sver[iter] = shader(tver[iter], cons, NULL);

    for (iter = carrsz(tpix) - 2; iter >= 0; iter--)
        spix[iter] = shader(tpix[iter], cons, NULL);
}



GLvoid FreeShaderSrc() {
    free(sver);
    free(spix);
}
