char shadergen_vert[] = "// ShaderGen shader\n"
                        "// new version\n"
                        "#ifdef GL_ES\n"
                        "    precision highp float;\n"
                        "#endif\n"
                        "\n"
                        "#pragma import_defines(GL_LIGHTING, GL_TEXTURE_2D)\n"
                        "\n"
                        "\n"
                        "#ifdef GL_LIGHTING\n"
                        "void directionalLight( int lightNum, vec3 normal, inout vec4 color )\n"
                        "{\n"
                        "    vec3 n = normalize(gl_NormalMatrix * normal);\n"
                        "\n"
                        "    float NdotL = dot( n, normalize(gl_LightSource[lightNum].position.xyz) );\n"
                        "    NdotL = max( 0.0, NdotL );\n"
                        "\n"
                        "    float NdotHV = dot( n, gl_LightSource[lightNum].halfVector.xyz );\n"
                        "    NdotHV = max( 0.0, NdotHV );\n"
                        "\n"
                        "    color *= gl_FrontLightModelProduct.sceneColor +\n"
                        "             gl_FrontLightProduct[lightNum].ambient +\n"
                        "             gl_FrontLightProduct[lightNum].diffuse * NdotL;\n"
                        "\n"
                        "    if ( NdotL * NdotHV > 0.0 )\n"
                        "        color += gl_FrontLightProduct[lightNum].specular * pow( NdotHV, gl_FrontMaterial.shininess );\n"
                        "}\n"
                        "#endif\n"
                        "\n"
                        "varying vec4 vertexColor;\n"
                        "\n"
                        "void main()\n"
                        "{\n"
                        "  gl_Position = ftransform();\n"
                        "\n"
                        "#if defined(GL_TEXTURE_2D)\n"
                        "  gl_TexCoord[0] = gl_MultiTexCoord0;\n"
                        "#endif\n"
                        "\n"
                        "  vertexColor = gl_Color;\n"
                        "\n"
                        "#if defined(GL_LIGHTING)\n"
                        "    directionalLight(0, gl_Normal, vertexColor);\n"
                        "#endif\n"
                        "}\n"
                        "\n";