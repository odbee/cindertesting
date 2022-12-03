#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "GraphSetup.h"
#include "GraphHandler.h"
#include "DrawHandler.h"
#include "DataContainer.h"
#include "IniHandler.h"
#include "GuiSetup.h"
#include "cinder/CameraUi.h"
using namespace ci;
using namespace ci::app;
using namespace std;



class weaverApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void mouseMove(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void update() override;
	void draw() override;
	DataContainer data;
	GraphHandler GH=GraphHandler(data);
	DrawHandler dh = DrawHandler(GH.g ,data);
	IniHandler ih = IniHandler(data);
	GuiHandler GuiH = GuiHandler(data, ih,GH.g,GH.edgesG);
	ci::vec2 mMousePos;
};

void weaverApp::mouseMove(MouseEvent event) {
	mMousePos = event.getPos();
	//ci::app::console() << "mouse moved" << std::endl;
}
void weaverApp::keyDown(KeyEvent event) {
	if (event.getCode() == 99) { // "c"
		if (data.INDEX < GH.getRecipeInfo().size()) {
			GH.addEdgeFromRecipe(data.INDEX++);
		}
		else {
			data.my_log.AddLog("[warning] Max steps received! you can only go back.\n");
			data.INDEX = GH.getRecipeInfo().size();

		}
		
	}
	if (event.getChar() == 'x') { // "c"
		if (data.INDEX > 0) {
			GH.removeEdgeFromRecipe(--data.INDEX);
		}
		else {
			data.my_log.AddLog("[warning] Min steps received! you can only go forward.\n");
			data.INDEX = 0;

		}
		
	}
	if (event.getChar() == 'o') { // "c"
		GH.printOriginalEdges();

	}
}
void weaverApp::setup()
{
	dh.setupCamera();
	GuiH.setupImGui();
	GH.loadEdges(data.fullPath + "edges.csv");
	GH.loadRecipe(data.fullPath + "log.csv");
	GH.setupEdgesGraph();
	GH.initOriginalEdges();
	GH.loadVertices(data.fullPath + "vertices.csv");

	
	GH.InitialWebFromObj(0.9, data.fullPath + data.initialGraphDE);


	GH.AddAllVerts();

}

void weaverApp::mouseDown( MouseEvent event )
{
	ci::app::console() << "clicking old item" << std::endl;

}

void weaverApp::update()
{
	
	GH.relaxPhysics();
	data.hovered_edge = GH.getClosestEdgeFromRay(dh.calculateRay(mMousePos));

}

void weaverApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	GuiH.drawParametersWindow();
	dh.drawCamera();
	//dh.proj = dh.mCamera.getProjectionMatrix() * dh.mCamera.getViewMatrix();
	//int w = getWindowWidth();
	//int h = getWindowHeight();
	//dh.viewp = vec4(0, h, w, -h); // vertical flip is required
	dh.drawPoints();

	{
		dh.drawCamera();

		ci::gl::ScopedMatrices push;
		ci::gl::setMatrices(dh.mCamera);
		dh.drawGraph();
		dh.drawNthEdge();
		dh.drawSelectedEdge();
		dh.drawDivisionPoints(GH.edgesG,GH.edgeMap);

	}
}

CINDER_APP( weaverApp, RendererGl )
