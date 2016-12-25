#include "DynamicObjectCreationUI.h"



DynamicObjectCreationUI::DynamicObjectCreationUI(GLuint program) : program(program), isHidden(true)
{
	setup();
}


DynamicObjectCreationUI::~DynamicObjectCreationUI()
{
}

void DynamicObjectCreationUI::draw() {
	addObjectButton->render(program);

	if (!isHidden) {
		arrow->draw(program);
		addBunny->render(program);
		addTeapot->render(program);
		addTree->render(program);
		addGrass->render(program);
	}
}

bool DynamicObjectCreationUI::mousePressed(float x, float y) {
	if (isHidden) {
		return addObjectButton->mousePressed(x, y);
	}
	else {
		return addObjectButton->mousePressed(x, y)
			|| addBunny->mousePressed(x, y)
			|| addTeapot->mousePressed(x, y)
			|| addTree->mousePressed(x, y)
			|| addGrass->mousePressed(x, y);
	}
}

void DynamicObjectCreationUI::mouseReleased() {
	addBunny->mouseReleased();
	addTeapot->mouseReleased();
	addTree->mouseReleased();
	addGrass->mouseReleased();
}

void DynamicObjectCreationUI::setup() {
	Texture *addObjectButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/addObjectButtonActive.png");
	addObjectButtonTextureActive->Load();
	Texture *addObjectButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/addObjectButtonInactive.png");
	addObjectButtonTextureInactive->Load();
	TexturedObject2D *addObjectButtonTexturedObjectActive = new TexturedObject2D(addObjectButtonTextureActive, glm::vec2(-0.92, -0.92), 0.05, 0.04);
	TexturedObject2D *addObjectButtonTexturedObjectInactive = new TexturedObject2D(addObjectButtonTextureInactive, glm::vec2(-0.92, -0.92), 0.05, 0.04);
	addObjectButton = new Button(addObjectButtonTexturedObjectInactive, addObjectButtonTexturedObjectActive, this);

	Texture *addBunnyButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/addBunnyButtonActive.png");
	addBunnyButtonTextureActive->Load();
	Texture *addBunnyButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/addBunnyButtonInactive.png");
	addBunnyButtonTextureInactive->Load();
	TexturedObject2D *addBunnyButtonTexturedObjectActive = new TexturedObject2D(addBunnyButtonTextureActive, glm::vec2(-0.68, -0.92), 0.05, 0.04);
	TexturedObject2D *addBunnyButtonTexturedObjectInactive = new TexturedObject2D(addBunnyButtonTextureInactive, glm::vec2(-0.68, -0.92), 0.05, 0.04);
	addBunny = new Button(addBunnyButtonTexturedObjectInactive, addBunnyButtonTexturedObjectActive, this);

	Texture *addTeapotButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/addTeapotButtonActive.png");
	addTeapotButtonTextureActive->Load();
	Texture *addTeapotButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/addTeapotButtonInactive.png");
	addTeapotButtonTextureInactive->Load();
	TexturedObject2D *addTeapotButtonTexturedObjectActive = new TexturedObject2D(addTeapotButtonTextureActive, glm::vec2(-0.56, -0.92), 0.05, 0.04);
	TexturedObject2D *addTeapotButtonTexturedObjectInactive = new TexturedObject2D(addTeapotButtonTextureInactive, glm::vec2(-0.56, -0.92), 0.05, 0.04);
	addTeapot = new Button(addTeapotButtonTexturedObjectInactive, addTeapotButtonTexturedObjectActive, this);

	Texture *addTreeButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/addTreeButtonActive.png");
	addTreeButtonTextureActive->Load();
	Texture *addTreeButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/addTreeButtonInactive.png");
	addTreeButtonTextureInactive->Load();
	TexturedObject2D *addTreeButtonTexturedObjectActive = new TexturedObject2D(addTreeButtonTextureActive, glm::vec2(-0.44, -0.92), 0.05, 0.04);
	TexturedObject2D *addTreeButtonTexturedObjectInactive = new TexturedObject2D(addTreeButtonTextureInactive, glm::vec2(-0.44, -0.92), 0.05, 0.04);
	addTree = new Button(addTreeButtonTexturedObjectInactive, addTreeButtonTexturedObjectActive, this);

	Texture *addGrassButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/addGrassButtonActive.png");
	addGrassButtonTextureActive->Load();
	Texture *addGrassButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/addGrassButtonInactive.png");
	addGrassButtonTextureInactive->Load();
	TexturedObject2D *addGrassButtonTexturedObjectActive = new TexturedObject2D(addGrassButtonTextureActive, glm::vec2(-0.32, -0.92), 0.05, 0.04);
	TexturedObject2D *addGrassButtonTexturedObjectInactive = new TexturedObject2D(addGrassButtonTextureInactive, glm::vec2(-0.32, -0.92), 0.05, 0.04);
	addGrass = new Button(addGrassButtonTexturedObjectInactive, addGrassButtonTexturedObjectActive, this);

	Texture *arrowTexture = new Texture(GL_TEXTURE_2D, "Textures/rightArrow.png");
	arrowTexture->Load();
	arrow = new TexturedObject2D(arrowTexture, glm::vec2(-0.80, -0.92), 0.05, 0.04);
}

void DynamicObjectCreationUI::onButtonClick(Button *button) {
	//when the button is clicked we just identify which
	//button it was and then either place an object
	//in a "queue" or just hide/expand the menu
	if (button == addObjectButton) {
		isHidden = !isHidden;
	}
	else if (button == addBunny) {
		isHidden = true;
		queuedObject = "Bunny";
	}
	else if (button == addTeapot) {
		isHidden = true;
		queuedObject = "Teapot";
	}
	else if (button == addTree) {
		isHidden = true;
		queuedObject = "Tree";
	}
	else if (button == addGrass) {
		isHidden = true;
		queuedObject = "Grass";
	}

	addObjectButton->setClicked(!isHidden);
}

void DynamicObjectCreationUI::onButtonRelease(Button *button) {
}

std::string DynamicObjectCreationUI::popQueuedObject() {
	std::string toReturn = queuedObject;
	queuedObject = "";
	return toReturn;
}