"const int CASCADE_COUNT_FLAG = 3;\n"
"varying vec4 OTEXSHADOW;\n"
"uniform vec4 m_vCascadeOffset[CASCADE_COUNT_FLAG];\n"
"uniform vec4 m_vCascadeScale[CASCADE_COUNT_FLAG];\n"
"uniform float m_fMinBorderPadding;\n"
"uniform float m_fMaxBorderPadding;\n"
"uniform float m_fCascadeBlendArea;\n"
"uniform float m_fShadowPower;\n"
"uniform sampler2D txShadow0;\n"
"uniform sampler2D txShadow1;\n"
"uniform sampler2D txShadow2;\n"
"int iCurrentCascadeIndex = 0;\n"

"void ComputeCoordinatesTransform(in int iCascadeIndex,inout vec4 vShadowTexCoord)\n"
"{\n"
	"vShadowTexCoord.w = vShadowTexCoord.z;\n"
	"vShadowTexCoord.z = iCascadeIndex;\n"
"}\n"

"void CalculateVarianceShadow ( in vec4 vShadowTexCoord, in vec4 vShadowMapTextureCoordViewSpace, int iCascade, out float fPercentLit )\n"
"{\n"
	"fPercentLit = 0.0f;\n"
	
	"vec2 mapDepth = vec2(0);\n"

	"vec2 vShadowTexCoordDDX = dFdx(vShadowMapTextureCoordViewSpace.xy );\n"
	"vShadowTexCoordDDX *= m_vCascadeScale[iCascade].xy; \n"
	"vec2 vShadowTexCoordDDY = dFdy(vShadowMapTextureCoordViewSpace.xy );\n"
	"vShadowTexCoordDDY *= m_vCascadeScale[iCascade].xy; \n"
	
	"if(iCascade == 0)\n"
	"{\n"
		"mapDepth += textureGrad(txShadow0,vShadowTexCoord.xy,vShadowTexCoordDDX,vShadowTexCoordDDY).xy;\n"
	"}\n"
	"else if(iCascade == 1)\n"
	"{\n"
		"mapDepth += textureGrad(txShadow1,vShadowTexCoord.xy,vShadowTexCoordDDX,vShadowTexCoordDDY).xy;\n"
	"}\n"
	"else if(iCascade == 2)\n"
	"{\n"
		"mapDepth += textureGrad(txShadow2,vShadowTexCoord.xy,vShadowTexCoordDDX,vShadowTexCoordDDY).xy;\n"
	"}\n"
	
	"float  fAvgZ  = mapDepth.x;\n"
	"float  fAvgZ2 = mapDepth.y;\n"

"#ifdef VARIANCE_DISABLE\n"
	"vShadowTexCoord.w = floor(vShadowTexCoord.w*255.0f)/255.0f;\n"
"#endif\n"
	"if(vShadowTexCoord.w <= fAvgZ)\n"
	"{\n"
		"fPercentLit = 1;\n"
	"}\n"
	"else\n"
	"{\n"
"#ifndef VARIANCE_DISABLE\n"
		"float variance = (fAvgZ2)-(fAvgZ * fAvgZ);\n"
		"variance = min(1.0f,max(0.0f,variance + 0.00001f));\n"
		"float d = vShadowTexCoord.w - fAvgZ;\n"
		"float p_max = variance / (variance + d*d);\n"
"#else\n"
		"float d = vShadowTexCoord.w - fAvgZ;\n"
		"float p_max = 0.00001f / (0.00001f + d*d);\n"
"#endif\n"

		"fPercentLit = pow(p_max,m_fShadowPower);\n"
	"}\n"
"}\n"

"void CalculateBlendAmountForMap ( in vec4 vShadowMapTextureCoord, \n"
									"inout float fCurrentPixelsBlendBandLocation,\n"
									"out float fBlendBetweenCascadesAmount ) \n"
"{\n"
	"vec2 distanceToOne = vec2 ( 1.0f - vShadowMapTextureCoord.x, 1.0f - vShadowMapTextureCoord.y );\n"
	"fCurrentPixelsBlendBandLocation = min( vShadowMapTextureCoord.x, vShadowMapTextureCoord.y );\n"
	"float fCurrentPixelsBlendBandLocation2 = min( distanceToOne.x, distanceToOne.y );\n"
	"fCurrentPixelsBlendBandLocation = \n"
		"min( fCurrentPixelsBlendBandLocation, fCurrentPixelsBlendBandLocation2 );\n"
	"fBlendBetweenCascadesAmount = fCurrentPixelsBlendBandLocation / m_fCascadeBlendArea;\n"
"}\n"

"float CalculateCascadeVarianceShadow(in vec4 vTexShadow)\n"
"{\n"
	"vec4 vShadowMapTextureCoordViewSpace = vec4(0.0f);\n"
	"vec4 vShadowMapTextureCoord = vec4(0.0f);\n"
	"vec4 vShadowMapTextureCoord_blend = vec4(0.0f);\n"

	"float fPercentLit = 0.0f;\n"
	"float fPercentLit_blend = 0.0f;\n"

	"int iCascadeFound = 0;\n"
	//"int iCurrentCascadeIndex = 0;\n"
	"int iNextCascadeIndex = 0;\n"

	"vShadowMapTextureCoordViewSpace = vTexShadow;\n"
	"for(int iCascadeIndex = 0; iCascadeIndex < CASCADE_COUNT_FLAG && iCascadeFound == 0; ++iCascadeIndex)\n"
	"{\n"
		"vShadowMapTextureCoord = vShadowMapTextureCoordViewSpace * m_vCascadeScale[iCascadeIndex];\n"
		"vShadowMapTextureCoord += m_vCascadeOffset[iCascadeIndex];\n"

		"if(min(vShadowMapTextureCoord.x,vShadowMapTextureCoord.y) > m_fMinBorderPadding\n"
			"&& max(vShadowMapTextureCoord.x,vShadowMapTextureCoord.y) < m_fMaxBorderPadding)\n"
		"{\n"
			"iCurrentCascadeIndex = iCascadeIndex;\n"
			"iCascadeFound = 1;\n"
		"}\n"
	"}\n"
	
	"vShadowMapTextureCoord.y = 1.0f - vShadowMapTextureCoord.y;\n"//y���]
	"ComputeCoordinatesTransform(iCurrentCascadeIndex,vShadowMapTextureCoord);\n"
	
	"float fBlendBetweenCascadesAmount = 1.0f;\n"
	"float fCurrentPixelsBlendBandLocation = 1.0f;\n"
	
	"CalculateVarianceShadow ( vShadowMapTextureCoord, vShadowMapTextureCoordViewSpace, iCurrentCascadeIndex, fPercentLit);\n"
	
	"if(0 < m_fCascadeBlendArea)\n"
	"{\n"
		"iNextCascadeIndex = iCurrentCascadeIndex + 1;\n"
		"if(CASCADE_COUNT_FLAG<=iNextCascadeIndex){iNextCascadeIndex = CASCADE_COUNT_FLAG - 1;}\n"
		
		"vShadowMapTextureCoord_blend = vShadowMapTextureCoordViewSpace * m_vCascadeScale[iNextCascadeIndex];\n"
		"vShadowMapTextureCoord_blend += m_vCascadeOffset[iNextCascadeIndex];\n"
		
		"ComputeCoordinatesTransform(iNextCascadeIndex,vShadowMapTextureCoord_blend);\n"

		"CalculateBlendAmountForMap(vShadowMapTextureCoord,\n"
			"fCurrentPixelsBlendBandLocation,fBlendBetweenCascadesAmount);\n"

		"if(fCurrentPixelsBlendBandLocation < m_fCascadeBlendArea)\n"
		"{\n"
			"CalculateVarianceShadow(vShadowMapTextureCoord_blend,vShadowMapTextureCoordViewSpace,iNextCascadeIndex,fPercentLit_blend);\n"
			"fPercentLit = mix(fPercentLit_blend,fPercentLit,fBlendBetweenCascadesAmount);\n"
		"}\n"
	"}\n"
	
	"return fPercentLit;\n"
"}\n"