#include "TextRenderer.h"
#include "ResourceManager.h"
#include "Global.h"
#include "Utils.h"

TextRenderer* TextRenderer::instance = 0;
TextRenderer::TextRenderer()
{
	//FT_Library ft;
	canDo=false;
	if (FT_Init_FreeType(&ftLib)) {
		Log("Could not init freetype library\n");
		return;
	}
	char path[255];
	strcpy(path,Global::gameResourceDir.c_str());
	strcat(path,"Resources//Fonts//times.ttf");

	if (FT_New_Face(ftLib,path, 0, &face)) {
		Log("Could not open font\n");
		return;
	}
	else
	{
		FT_Set_Pixel_Sizes(face, 0, 48);
		if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
			Log("Could not load character 'X'\n");
			return;
		}
	}
	canDo=true;
	textShader = Global::TextShader;
	glGenTextures(1, &tex);
	glGenBuffers(1, &vbo);
}


TextRenderer::~TextRenderer()
{
	//Delete(textShader);
	glDeleteBuffers(1, &tex);
	glDeleteBuffers(1, &vbo);
	FT_Done_Face(face);
	FT_Done_FreeType(ftLib);
}


void TextRenderer::InitFont(char* fontPath,float fontSize)
{
	if (!canDo)
		return;
	char path[255];
	strcpy(path,Global::gameResourceDir.c_str());
	strcat(path,fontPath);
	Log(fontPath);
	if (FT_New_Face(ftLib, path, 0, &face)) {
		Log("Could not open font\n");
		canDo=false;
	}
	else
	{
		FT_Set_Pixel_Sizes(face, 0, fontSize);
		if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
			Log("Could not load character 'X'\n");
		}
		canDo=true;
	}
	if (!canDo)
	{
		if (FT_New_Face(ftLib, "Resources//Fonts//times.ttf", 0, &face)) {
			Log("Could not open font\n");
			return;
		}
		else
		{
			FT_Set_Pixel_Sizes(face, 0, 48);
			if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
				Log("Could not load character 'X'\n");
				return;
			}
		}
	}
	textShader=Global::TextShader;
	canDo=true;
}

TextRenderer* TextRenderer::GetInstance()
{
	if (!instance)
		instance = new TextRenderer();
	return instance;
}


void TextRenderer::RenderText(const char *text, float x, float y, float sx, float sy)
{
	if (!canDo)
		return;

	glUseProgram(textShader->program);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnableVertexAttribArray(textShader->a_positon);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(textShader->a_positon, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//Init diffuse color: i.e White
	Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	if (textShader->uniformColorText != -1)
	{
		glUniform4fv(textShader->uniformColorText, 1, (GLfloat*)&color);
	}

	const char *p;
	FT_GlyphSlot glyph = face->glyph;
	for (p = text; *p; p++) {
		if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
			continue;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			glyph->bitmap.width,
			glyph->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			glyph->bitmap.buffer
			);



		float x2 = x + glyph->bitmap_left * sx;
		float y2 = -y - glyph->bitmap_top * sy;
		float w = glyph->bitmap.width * sx;
		float h = glyph->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{ x2, -y2, 0, 0 },
			{ x2 + w, -y2, 1, 0 },
			{ x2, -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (glyph->advance.x >> 6) * sx;
		y += (glyph->advance.y >> 6) * sy;
		glBindTexture(GL_TEXTURE_2D, 0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteBuffers(1, &vbo);
	glDisable(GL_BLEND);
	//delete g;
	//delete g;
}

void TextRenderer::RenderText(const char *text, float x, float y,Vector4 color)
{
	if (!canDo)
		return;
	float sx = 2.0f / Global::ScreenWidth;
	float sy = 2.0f / Global::ScreenHeight;
	glUseProgram(textShader->program);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnableVertexAttribArray(textShader->a_positon);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(textShader->a_positon, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//Init diffuse color: i.e White
	//Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	if (textShader->uniformColorText != -1)
	{
		glUniform4fv(textShader->uniformColorText, 1, (GLfloat*)&color);
	}

	const char *p;
	FT_GlyphSlot glyph = face->glyph;
	for (p = text; *p; p++) {
		if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
			continue;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			glyph->bitmap.width,
			glyph->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			glyph->bitmap.buffer
			);



		float x2 = x + glyph->bitmap_left * sx;
		float y2 = -y - glyph->bitmap_top * sy;
		float w = glyph->bitmap.width * sx;
		float h = glyph->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{ x2, -y2, 0, 0 },
			{ x2 + w, -y2, 1, 0 },
			{ x2, -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (glyph->advance.x >> 6) * sx;
		y += (glyph->advance.y >> 6) * sy;
		glBindTexture(GL_TEXTURE_2D, 0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteBuffers(1, &vbo);
	glDisable(GL_BLEND);
	//delete g;
	//delete g;
}