#include "ola_resource.h"

const char DEFAULT_MATERIAL_NAME[] = "default.mat";
const char DEFAULT_MATERIAL_DATA[] = 
"<ola_material version=\"1.0\">"
"	<instance name=\"default\">"
"		<technique type=\"forward\" source_s=\"default.glsl\"/>"
"		<var name=\"diffuse_map\" type=\"texture\" value=\"default.tga\"/>"
"  </instance>"
"</ola_material>";

const char DEFAULT_SHADER_NAME[] = "default.glsl";
const char DEFAULT_SHADER_DATA[] = 
"#program vert \n"
"	 \n"
"attribute highp 	vec4 a_position; \n"
"attribute highp 	vec3 a_normal; \n"
"attribute mediump 	vec2 a_uv0; \n"
"	 \n"
"uniform highp mat4 u_mvp; \n"
"uniform highp mat4 u_model_invtrans; \n"
"uniform highp mat4 u_model; \n"
"	 \n"
"uniform highp vec3 u_eyepos; \n"
"uniform highp vec3 u_eyedir; \n"
"	 \n"
"uniform highp vec3 u_lightpos0; \n"
"uniform highp vec3 u_lightdir0; \n"
"uniform highp vec3 u_lightcol0; \n"
"	 \n"
"varying mediump vec2 v_uv; \n"
"varying lowp vec3  v_vertexlight; \n"
"	 \n"
"void main() {	 \n"
"	 \n"
"	highp vec3 normal = vec3(normalize(u_model_invtrans * vec4(a_normal,0.0))); \n"
"	 \n"
"	 \n"
"	lowp float ndotl = max(dot(normal,-1.0*u_lightdir0),0.0); \n"
"	lowp vec3 lambient = 0.4 * vec3(1.0,1.0,1.0); \n"
"	lowp vec3 ldiffuse = ndotl * vec3(1.0,1.0,1.0);	 \n"
"	v_vertexlight = min((lambient + ldiffuse),1.0); \n"
"	 \n"
"	 \n"
"	v_uv = a_uv0; \n"
"	 \n"
"	gl_Position = u_mvp * a_position; \n"
"} \n"
"	 \n"
"#end \n"
"	 \n"
"#program frag \n"
"	 \n"
"uniform sampler2D s_diffuse;  \n"
"	 \n"
"varying mediump vec2 v_uv; \n"
"	 \n"
"varying lowp vec3  v_vertexlight; \n"
"	 \n"
"void main() { \n"
"	 \n"
"	lowp vec4 tc = texture2D(s_diffuse,v_uv); \n"
"	 \n"
"	 \n"
"	gl_FragColor = vec4(tc.x * v_vertexlight.x , tc.y * v_vertexlight.y , tc.z * v_vertexlight.z ,1.0); \n"
"	gl_FragColor = vec4(0.79, 0, 0.77,1.0); \n"
"	 \n"
"} \n"
" \n"
"#end";

const char DEFAULT_TEXTURE_NAME[] = "default.tga";
const unsigned char DEFAULT_TEXTURE_DATA[4 * 3] = 
{
202, 0, 197,
202, 0, 197,
202, 0, 197,
255, 255, 255,
};

const char DEFAULT_DML_NAME[] = "default.dml";
const char DEFAULT_DML_DATA[] = 
"<ola_model>"
"	<geometry resource=\"default.ase\"/>"
"	<material num=\"1\">"
"		<submat index=\"0\" name=\"default\" resource=\"default.mat\"/>"
"	</material>"
"</ola_model>";

const char DEFAULT_ASE_NAME[] = "default.ase";
const char DEFAULT_ASE_DATA[] = 
"*3DSMAX_ASCIIEXPORT	200"
"*COMMENT \"AsciiExport Version  2.00 - Wed Apr 24 13:51:13 2013\""
"*SCENE {"
"	*SCENE_FILENAME \"\""
"	*SCENE_FIRSTFRAME 0"
"	*SCENE_LASTFRAME 100"
"	*SCENE_FRAMESPEED 30"
"	*SCENE_TICKSPERFRAME 160"
"	*SCENE_BACKGROUND_STATIC 0.00000	0.00000	0.00000"
"	*SCENE_AMBIENT_STATIC 0.00000	0.00000	0.00000"
"}"
"*MATERIAL_LIST {"
"	*MATERIAL_COUNT 1"
"	*MATERIAL 0 {"
"		*MATERIAL_NAME \"default\""
"		*MATERIAL_CLASS \"Standard\""
"		*MATERIAL_AMBIENT 0.58824	0.58824	0.58824"
"		*MATERIAL_DIFFUSE 0.58824	0.58824	0.58824"
"		*MATERIAL_SPECULAR 0.90000	0.90000	0.90000"
"		*MATERIAL_SHINE 0.10000"
"		*MATERIAL_SHINESTRENGTH 0.00000"
"		*MATERIAL_TRANSPARENCY 0.00000"
"		*MATERIAL_WIRESIZE 1.00000"
"		*MATERIAL_SHADING Blinn"
"		*MATERIAL_XP_FALLOFF 0.00000"
"		*MATERIAL_SELFILLUM 0.00000"
"		*MATERIAL_FALLOFF In"
"		*MATERIAL_XP_TYPE Filter"
"	}"
"}"
"*GEOMOBJECT {"
"	*NODE_NAME \"default\""
"	*NODE_TM {"
"		*NODE_NAME \"default\""
"		*INHERIT_POS 0 0 0"
"		*INHERIT_ROT 0 0 0"
"		*INHERIT_SCL 0 0 0"
"		*TM_ROW0 1.00000	0.00000	0.00000"
"		*TM_ROW1 0.00000	1.00000	0.00000"
"		*TM_ROW2 0.00000	0.00000	1.00000"
"		*TM_ROW3 0.00000	0.00000	0.00000"
"		*TM_POS 0.00000	0.00000	0.00000"
"		*TM_ROTAXIS 0.00000	0.00000	0.00000"
"		*TM_ROTANGLE 0.00000"
"		*TM_SCALE 1.00000	1.00000	1.00000"
"		*TM_SCALEAXIS 0.00000	0.00000	0.00000"
"		*TM_SCALEAXISANG 0.00000"
"	}"
"	*MESH {"
"		*TIMEVALUE 0"
"		*MESH_NUMVERTEX 8"
"		*MESH_NUMFACES 12"
"		*MESH_VERTEX_LIST {"
"			*MESH_VERTEX    0	-0.50000	-0.50000	0.00000"
"			*MESH_VERTEX    1	0.50000	-0.50000	0.00000"
"			*MESH_VERTEX    2	-0.50000	0.50000	0.00000"
"			*MESH_VERTEX    3	0.50000	0.50000	0.00000"
"			*MESH_VERTEX    4	-0.50000	-0.50000	1.00000"
"			*MESH_VERTEX    5	0.50000	-0.50000	1.00000"
"			*MESH_VERTEX    6	-0.50000	0.50000	1.00000"
"			*MESH_VERTEX    7	0.50000	0.50000	1.00000"
"		}"
"		*MESH_FACE_LIST {"
"			*MESH_FACE    0:    A:    0 B:    2 C:    3 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 2 	*MESH_MTLID 1"
"			*MESH_FACE    1:    A:    3 B:    1 C:    0 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 2 	*MESH_MTLID 1"
"			*MESH_FACE    2:    A:    4 B:    5 C:    7 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 3 	*MESH_MTLID 0"
"			*MESH_FACE    3:    A:    7 B:    6 C:    4 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 3 	*MESH_MTLID 0"
"			*MESH_FACE    4:    A:    0 B:    1 C:    5 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 4 	*MESH_MTLID 4"
"			*MESH_FACE    5:    A:    5 B:    4 C:    0 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 4 	*MESH_MTLID 4"
"			*MESH_FACE    6:    A:    1 B:    3 C:    7 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 5 	*MESH_MTLID 3"
"			*MESH_FACE    7:    A:    7 B:    5 C:    1 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 5 	*MESH_MTLID 3"
"			*MESH_FACE    8:    A:    3 B:    2 C:    6 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 6 	*MESH_MTLID 5"
"			*MESH_FACE    9:    A:    6 B:    7 C:    3 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 6 	*MESH_MTLID 5"
"			*MESH_FACE   10:    A:    2 B:    0 C:    4 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 7 	*MESH_MTLID 2"
"			*MESH_FACE   11:    A:    4 B:    6 C:    2 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 7 	*MESH_MTLID 2"
"		}"
"		*MESH_NUMTVERTEX 12"
"		*MESH_TVERTLIST {"
"			*MESH_TVERT 0	0.00000	0.00000	0.00000"
"			*MESH_TVERT 1	1.00000	0.00000	0.00000"
"			*MESH_TVERT 2	0.00000	1.00000	0.00000"
"			*MESH_TVERT 3	1.00000	1.00000	0.00000"
"			*MESH_TVERT 4	0.00000	0.00000	0.00000"
"			*MESH_TVERT 5	1.00000	0.00000	0.00000"
"			*MESH_TVERT 6	0.00000	1.00000	0.00000"
"			*MESH_TVERT 7	1.00000	1.00000	0.00000"
"			*MESH_TVERT 8	0.00000	0.00000	0.00000"
"			*MESH_TVERT 9	1.00000	0.00000	0.00000"
"			*MESH_TVERT 10	0.00000	1.00000	0.00000"
"			*MESH_TVERT 11	1.00000	1.00000	0.00000"
"		}"
"		*MESH_NUMTVFACES 12"
"		*MESH_TFACELIST {"
"			*MESH_TFACE 0	9	11	10"
"			*MESH_TFACE 1	10	8	9"
"			*MESH_TFACE 2	8	9	11"
"			*MESH_TFACE 3	11	10	8"
"			*MESH_TFACE 4	4	5	7"
"			*MESH_TFACE 5	7	6	4"
"			*MESH_TFACE 6	0	1	3"
"			*MESH_TFACE 7	3	2	0"
"			*MESH_TFACE 8	4	5	7"
"			*MESH_TFACE 9	7	6	4"
"			*MESH_TFACE 10	0	1	3"
"			*MESH_TFACE 11	3	2	0"
"		}"
"		*MESH_NORMALS {"
"			*MESH_FACENORMAL 0	0.00000	0.00000	-1.00000"
"				*MESH_VERTEXNORMAL 0	0.00000	0.00000	-1.00000"
"				*MESH_VERTEXNORMAL 2	0.00000	0.00000	-1.00000"
"				*MESH_VERTEXNORMAL 3	0.00000	0.00000	-1.00000"
"			*MESH_FACENORMAL 1	0.00000	0.00000	-1.00000"
"				*MESH_VERTEXNORMAL 3	0.00000	0.00000	-1.00000"
"				*MESH_VERTEXNORMAL 1	0.00000	0.00000	-1.00000"
"				*MESH_VERTEXNORMAL 0	0.00000	0.00000	-1.00000"
"			*MESH_FACENORMAL 2	0.00000	-0.00000	1.00000"
"				*MESH_VERTEXNORMAL 4	0.00000	0.00000	1.00000"
"				*MESH_VERTEXNORMAL 5	0.00000	-0.00000	1.00000"
"				*MESH_VERTEXNORMAL 7	0.00000	0.00000	1.00000"
"			*MESH_FACENORMAL 3	-0.00000	0.00000	1.00000"
"				*MESH_VERTEXNORMAL 7	0.00000	0.00000	1.00000"
"				*MESH_VERTEXNORMAL 6	-0.00000	0.00000	1.00000"
"				*MESH_VERTEXNORMAL 4	0.00000	0.00000	1.00000"
"			*MESH_FACENORMAL 4	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXNORMAL 0	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXNORMAL 1	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXNORMAL 5	0.00000	-1.00000	0.00000"
"			*MESH_FACENORMAL 5	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXNORMAL 5	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXNORMAL 4	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXNORMAL 0	0.00000	-1.00000	0.00000"
"			*MESH_FACENORMAL 6	1.00000	0.00000	-0.00000"
"				*MESH_VERTEXNORMAL 1	1.00000	0.00000	0.00000"
"				*MESH_VERTEXNORMAL 3	1.00000	0.00000	-0.00000"
"				*MESH_VERTEXNORMAL 7	1.00000	0.00000	0.00000"
"			*MESH_FACENORMAL 7	1.00000	-0.00000	0.00000"
"				*MESH_VERTEXNORMAL 7	1.00000	0.00000	0.00000"
"				*MESH_VERTEXNORMAL 5	1.00000	-0.00000	0.00000"
"				*MESH_VERTEXNORMAL 1	1.00000	0.00000	0.00000"
"			*MESH_FACENORMAL 8	0.00000	1.00000	0.00000"
"				*MESH_VERTEXNORMAL 3	0.00000	1.00000	0.00000"
"				*MESH_VERTEXNORMAL 2	0.00000	1.00000	0.00000"
"				*MESH_VERTEXNORMAL 6	0.00000	1.00000	0.00000"
"			*MESH_FACENORMAL 9	0.00000	1.00000	0.00000"
"				*MESH_VERTEXNORMAL 6	0.00000	1.00000	0.00000"
"				*MESH_VERTEXNORMAL 7	0.00000	1.00000	0.00000"
"				*MESH_VERTEXNORMAL 3	0.00000	1.00000	0.00000"
"			*MESH_FACENORMAL 10	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXNORMAL 2	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXNORMAL 0	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXNORMAL 4	-1.00000	0.00000	0.00000"
"			*MESH_FACENORMAL 11	-1.00000	-0.00000	-0.00000"
"				*MESH_VERTEXNORMAL 4	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXNORMAL 6	-1.00000	-0.00000	-0.00000"
"				*MESH_VERTEXNORMAL 2	-1.00000	0.00000	0.00000"
"		}"
"		*MESH_TANGENTS {"
"			*MESH_FACETANGENT 0	"
"				*MESH_VERTEXTANGENT 0	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 0	0.00000	1.00000	0.00000"
"				*MESH_VERTEXTANGENT 2	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 2	0.00000	1.00000	0.00000"
"				*MESH_VERTEXTANGENT 3	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 3	0.00000	1.00000	0.00000"
"			*MESH_FACETANGENT 1	"
"				*MESH_VERTEXTANGENT 3	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 3	0.00000	1.00000	0.00000"
"				*MESH_VERTEXTANGENT 1	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 1	0.00000	1.00000	0.00000"
"				*MESH_VERTEXTANGENT 0	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 0	0.00000	1.00000	0.00000"
"			*MESH_FACETANGENT 2	"
"				*MESH_VERTEXTANGENT 4	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 4	0.00000	1.00000	0.00000"
"				*MESH_VERTEXTANGENT 5	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 5	0.00000	1.00000	0.00000"
"				*MESH_VERTEXTANGENT 7	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 7	0.00000	1.00000	0.00000"
"			*MESH_FACETANGENT 3	"
"				*MESH_VERTEXTANGENT 7	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 7	0.00000	1.00000	0.00000"
"				*MESH_VERTEXTANGENT 6	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 6	0.00000	1.00000	0.00000"
"				*MESH_VERTEXTANGENT 4	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 4	0.00000	1.00000	0.00000"
"			*MESH_FACETANGENT 4	"
"				*MESH_VERTEXTANGENT 0	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 0	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 1	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 1	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 5	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 5	0.00000	0.00000	1.00000"
"			*MESH_FACETANGENT 5	"
"				*MESH_VERTEXTANGENT 5	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 5	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 4	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 4	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 0	1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 0	0.00000	0.00000	1.00000"
"			*MESH_FACETANGENT 6	"
"				*MESH_VERTEXTANGENT 1	0.00000	1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 1	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 3	0.00000	1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 3	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 7	0.00000	1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 7	0.00000	0.00000	1.00000"
"			*MESH_FACETANGENT 7	"
"				*MESH_VERTEXTANGENT 7	0.00000	1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 7	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 5	0.00000	1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 5	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 1	0.00000	1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 1	0.00000	0.00000	1.00000"
"			*MESH_FACETANGENT 8	"
"				*MESH_VERTEXTANGENT 3	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 3	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 2	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 2	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 6	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 6	0.00000	0.00000	1.00000"
"			*MESH_FACETANGENT 9	"
"				*MESH_VERTEXTANGENT 6	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 6	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 7	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 7	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 3	-1.00000	0.00000	0.00000"
"				*MESH_VERTEXBNORMAL 3	0.00000	0.00000	1.00000"
"			*MESH_FACETANGENT 10	"
"				*MESH_VERTEXTANGENT 2	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 2	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 0	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 0	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 4	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 4	0.00000	0.00000	1.00000"
"			*MESH_FACETANGENT 11	"
"				*MESH_VERTEXTANGENT 4	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 4	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 6	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 6	0.00000	0.00000	1.00000"
"				*MESH_VERTEXTANGENT 2	0.00000	-1.00000	0.00000"
"				*MESH_VERTEXBNORMAL 2	0.00000	0.00000	1.00000"
"		}"
"	}"
"	*PROP_MOTIONBLUR 0"
"	*PROP_CASTSHADOW 1"
"	*PROP_RECVSHADOW 1"
"	*MATERIAL_REF 0"
"}"
"";

