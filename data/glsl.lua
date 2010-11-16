Shader.normal(4, "default",
	[[
		void main(void)
		{
			gl_Position = ftransform();
			gl_TexCoord[0] = gl_MultiTexCoord0;
			gl_FrontColor = gl_Color;
		}
	]],
	[[
		uniform sampler2D tex0;
		void main(void)
		{
			gl_FragColor = gl_Color * texture2D(tex0, gl_TexCoord[0].xy);
		}
	]]
)
