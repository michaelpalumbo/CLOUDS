
/* VBlurVertexShader.glsl */

uniform vec2 dimensions;
varying vec2 v_texCoord;
uniform sampler2DRect source_texture;
uniform sampler2DRect water_texture;
uniform sampler2DRect flow_texture;
varying float v_blurTexCoords[14];

const float epsilon = 1e-6;

void main()
{
//	vec3 paintColor = texture2DRect(source_texture, v_texCoord).rgb;
	float flowAmount    = texture2DRect(water_texture, v_texCoord*.25).r*4.;
	vec2  flowDirection = texture2DRect(flow_texture, v_texCoord).rg * 2.0 - 1.0;

//	vec4 sample = texture2DRect(source_texture, v_texCoord + flowDirection*flowAmount);
//	gl_FragColor.rgb = sample.rgb;
	//gl_FragColor.a = max(max(sample.r,sample.g),max(sample.b,sample.a));
//	gl_FragColor.a = sample.a;
	
	if(flowAmount > epsilon){
		gl_FragColor = vec4(0.0);
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[ 0]*flowAmount)*0.0044299121055113265;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[ 1]*flowAmount)*0.00895781211794;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[ 2]*flowAmount)*0.0215963866053;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[ 3]*flowAmount)*0.0443683338718;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[ 4]*flowAmount)*0.0776744219933;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[ 5]*flowAmount)*0.115876621105;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[ 6]*flowAmount)*0.147308056121;
		gl_FragColor += texture2DRect(source_texture, v_texCoord)*0.159576912161;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[ 7]*flowAmount)*0.147308056121;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[ 8]*flowAmount)*0.115876621105;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[ 9]*flowAmount)*0.0776744219933;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[10]*flowAmount)*0.0443683338718;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[11]*flowAmount)*0.0215963866053;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[12]*flowAmount)*0.00895781211794;
		gl_FragColor += texture2DRect(source_texture, v_texCoord+
										  flowDirection*v_blurTexCoords[13]*flowAmount)*0.0044299121055113265;
	}
	else{
		gl_FragColor = texture2DRect(source_texture, v_texCoord);
	}

	//gl_FragColor.rgb = vec3(blurAmount);
//	gl_FragColor.rgb = 
//	gl_FragColor.rgb = vec3(1.0);
//	gl_FragColor.a = 1.0;
}
