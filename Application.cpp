#define GL_SILENCE_DEPRECATION
#include <fstream>
#include <vector>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "Geometry.h"
#include "imgui.h"

const Vector2 imageDimensions(500, 500);

GLuint image_texture = 0;

namespace MyApp
{

	void Init()
	{
		glGenTextures(1, &image_texture);
	    glBindTexture(GL_TEXTURE_2D, image_texture);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	void Update()
	{

	}

	void Render()
	{

		Vector3 clearColour = Vector3(255,0,255);
		std::vector<Vector3> framebuffer(imageDimensions.x*imageDimensions.y,Vector3(clearColour.x,clearColour.y,clearColour.z));

		unsigned char* image_data = new unsigned char[(static_cast<int>(imageDimensions.x)*static_cast<int>(imageDimensions.y))*4];

		for(int i = 0; i < framebuffer.size(); i++)
		{
			image_data[i*4] = framebuffer[i].x;
			image_data[i*4+1] = framebuffer[i].y;
			image_data[i*4+2] = framebuffer[i].z;
			image_data[i*4+3] = 255;
		}

	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageDimensions.x, imageDimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	    ImGui::Begin(" ");
		ImGui::Image((void*)(intptr_t)image_texture, ImVec2(imageDimensions.x*1.5, imageDimensions.y*1.5));
	    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	    ImGui::End();

	    delete[] image_data;
	}
}



