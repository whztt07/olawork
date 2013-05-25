
#program vert

attribute highp 	vec4 a_position;
attribute highp 	vec3 a_normal;
attribute highp 	vec2 a_uv0;

uniform highp mat4 u_mvp;
uniform highp mat4 u_model_invtrans;
uniform highp mat4 u_model;

uniform highp vec3 u_eyepos;
uniform highp vec3 u_eyedir;

uniform highp vec3 u_lightpos0;
uniform highp vec3 u_lightdir0;
uniform highp vec3 u_lightcol0;

varying highp vec2 v_uv;

varying highp vec3  v_lightdir;

void main() {	
	
	highp vec3 ws_normal = vec3(normalize(u_model_invtrans * vec4(a_normal,0.0)));												
	highp vec3 ws_position = (u_model * a_position).xyz;
		
	highp vec3 T1 = vec3(1, 0, 1);
	highp vec3 Bi = cross(T1, a_normal);
	highp vec3 newTangent = cross(a_normal, Bi);
	normalize(newTangent);

	if (dot(cross(a_normal,newTangent),Bi) < 0)
		Bi = -1.0 * cross(newTangent, a_normal);
	else
		Bi = 1.0 * cross(newTangent, a_normal);	
	
	highp vec3 ws_tangent = vec3(normalize(u_model_invtrans * vec4(newTangent,0.0)));
	highp vec3 ws_binormal = vec3(normalize(u_model_invtrans * vec4(Bi,0.0)));		
	
	highp mat3 TBN;
  	TBN[0].x = ws_tangent.x;
 	TBN[0].y = ws_binormal.x;
  	TBN[0].z = ws_normal.x;
  	TBN[1].x = ws_tangent.y;
  	TBN[1].y = ws_binormal.y;
  	TBN[1].z = ws_normal.y;
  	TBN[2].x = ws_tangent.z;
  	TBN[2].y = ws_binormal.z;
  	TBN[2].z = ws_normal.z;	
	
	v_uv = a_uv0;
	
	v_lightdir = TBN * normalize(u_lightpos0 - ws_position);	
	
	gl_Position = u_mvp * a_position;
}

#end

#program frag

uniform sampler2D s_diffuse; 
uniform sampler2D s_normal;

varying highp vec2 v_uv;

varying highp vec3  v_lightdir;

void main() {
		
	highp vec4 tc = texture2D(s_diffuse,v_uv);
	highp vec4 nc = texture2D(s_normal,v_uv);
	
	highp vec3 normal;
	normal.xy = nc.rg * 2 - 1;
	normal.z = -1.0 * sqrt(1 - normal.x * normal.x - normal.y * normal.y);					
	
	highp float dnl = max(dot(normal,v_lightdir),0.0);
	
	highp vec3 fc = tc.rgb * dnl;	

	gl_FragColor = vec4(fc.rgb,tc.a);				
}

#end