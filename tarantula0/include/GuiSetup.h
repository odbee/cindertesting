#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderImGui.h"
#include "DataContainer.h"
#include "IniHandler.h"

class GuiHandler
{
	private:
		void setup();
	public:
		GuiHandler(DataContainer& DATA,IniHandler& IH) : data(DATA),iniHand(IH) { setup(); }
		DataContainer& data;
		IniHandler& iniHand;
		std::string makePath(std::string directory, std::string filename);
		void adjustothers(std::vector<float*>& values, std::vector<float*>& cachedvalues, size_t index);
		void checkforchange(std::vector<float*>& values, std::vector<float*>& cachedvalues);
		void setupImGui();
		void drawParametersWindow();
};

