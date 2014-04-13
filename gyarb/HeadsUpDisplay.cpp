#include "HeadsUpDisplay.h"
#include "Scene.h" //Necessary. Does not include in .h due to inclusion loop.

HeadsUpDisplay::HeadsUpDisplay(std::string tooltipFontPath, Scene* whichScene, sf::RenderWindow* whichWindow, double massMax, double mediumMass, double largeMass) {
	static const unsigned int FONT_SIZE = 20;

	this->scn_ = whichScene;
	this->wdw_ = whichWindow;
	this->v_ = sf::View(sf::FloatRect(0, 0, 960, 540));
	this->mediumMass_ = mediumMass;
	this->largeMass_ = largeMass;
	this->tooltipFont_ = sf::Font();
	this->tooltipFont_.loadFromFile(tooltipFontPath);

	this->addBodyMass_ = new TooltippedSlider(tooltipFont_, FONT_SIZE, sf::Rect<float>(0, 48, 64, 16), *this->wdw_, 0.00, 0.0000001, massMax);
	
	sf::Text t1("Creates a body with custom mass.\nAdjust the slider below to adjust the mass.", tooltipFont_, FONT_SIZE);
	this->addBody_ = new TooltippedButton(t1, sf::Vector2f(0, 64), sf::FloatRect(0, 0, 65, 48), *this->wdw_);

	sf::Text t2("If this is checked, the next body you create will be declared static.\nStatic bodies are not affected by gravity but affect others.\nThey are also not destroyed upon collision.", tooltipFont_, FONT_SIZE);
	this->addBodyStaticTooltip_ = new TooltippedButton(t2, sf::Vector2f(160, 64), sf::FloatRect(160, 0, 32, 32), *this->wdw_);
	
	this->addBodySmall_ = new TooltippedButton(sf::Text("Creates a body with ~0 mass.", tooltipFont_, FONT_SIZE), sf::FloatRect(64, 0, 32, 64), *this->wdw_);
	this->addBodyMedium_ = new TooltippedButton(sf::Text("Creates a body with medium mass.", tooltipFont_, FONT_SIZE), sf::FloatRect(96, 0, 32, 64), *this->wdw_);
	this->addBodyLarge_ = new TooltippedButton(sf::Text("Creates a body with large mass.", tooltipFont_, FONT_SIZE), sf::FloatRect(128, 0, 32, 64), *this->wdw_);

	this->addBodyStatic_ = new Switch(sf::FloatRect(160, 0, 32, 32), *this->wdw_);
	this->clear_ = new TooltippedButton(sf::Text("Clears all bodies.", tooltipFont_, FONT_SIZE), sf::FloatRect(160, 32, 32, 32), *this->wdw_);

	sf::Sprite* s3 = new sf::Sprite(*LoadTexture("ButtonSquare.png"));
	AnimatedSprite* s4 = new AnimatedSprite(*LoadTexture("ButtonSquareFlashing.png"), 130, 130, sf::seconds(0.05), false, true);
	sf::Sprite* s5 = new sf::Sprite(*LoadTexture("TextPause.png"));
	sf::Sprite* s6 = new sf::Sprite(*LoadTexture("TextPlay.png"));
	s3->scale(0.4923076923076925, 0.4923076923076925);
	s4->scale(0.4923076923076925, 0.4923076923076925);
	s5->scale(0.4923076923076925, 0.4923076923076925);
	s6->scale(0.4923076923076925, 0.4923076923076925);
	s3->setPosition(192, 0);
	s4->setPosition(192, 0);
	s5->setPosition(192, 0);
	s6->setPosition(192, 0);
	
	this->pause_ = new Switch(s6, s5, s3, s4, *this->wdw_);

	this->allWidgets_.push_back(pause_);
	this->allWidgets_.push_back(clear_);
	this->allWidgets_.push_back(addBody_);
	this->allWidgets_.push_back(addBodyStaticTooltip_);
	this->allWidgets_.push_back(addBodyStatic_);
	this->allWidgets_.push_back(addBodySmall_);
	this->allWidgets_.push_back(addBodyMedium_);
	this->allWidgets_.push_back(addBodyLarge_);
	this->allWidgets_.push_back(addBodyMass_);
}

HeadsUpDisplay::~HeadsUpDisplay() {
	delete this->pause_;
	delete this->addBody_;
	delete this->addBodyMass_;
	delete this->addBodyStatic_;
	delete this->addBodyStaticTooltip_;
	delete this->addBodySmall_;
	delete this->addBodyMedium_;
	delete this->addBodyLarge_;
	delete this->clear_;
}

void HeadsUpDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) {
	//Applying appropriate view
	sf::View oldv = this->wdw_->getView();
	this->wdw_->setView(this->v_);

	//Drawing widgets
	for(int i = 0; i < allWidgets_.size(); i++)
		target.draw(*allWidgets_[i], states);

	//Resetting the view
	this->wdw_->setView(oldv);
}

void HeadsUpDisplay::update(sf::Time dt) {
	//Applying appropriate view
	sf::View oldv = this->wdw_->getView();
	this->wdw_->setView(this->v_);

	//Updating widgets
	for(auto it = allWidgets_.begin(); it != allWidgets_.end(); it++)
		(*it)->update(dt);

	//Modifying scene
	this->checkButtons();
	this->scn_->setPause(this->pause_->isOn());

	//Resetting the view
	this->wdw_->setView(oldv);
}

void HeadsUpDisplay::checkClick(sf::Vector2<int> pos) {
	//Applying appropriate view
	sf::View oldv = this->wdw_->getView();
	this->wdw_->setView(this->v_);

	//Converting pixels to coordinates
	sf::Vector2<float> p = this->wdw_->mapPixelToCoords(pos);

	//Resetting the view
	this->wdw_->setView(oldv);

	//Doing the actual stuff
	for(auto it = allWidgets_.begin(); it != allWidgets_.end(); it++)
		(*it)->checkClick(p);
}

void HeadsUpDisplay::onWindowResize(sf::Vector2u wsize) {
	this->v_ = sf::View(sf::FloatRect(0, 0, wsize.x, wsize.y));
}

void HeadsUpDisplay::checkButtons() {
	if(this->clear_->clickPending())
		this->scn_->clear();
	if(this->addBody_->clickPending())
		this->scn_->userCreateBody(this->addBodyMass_->getValue(), this->addBodyStatic_->isOn());
	if(this->addBodySmall_->clickPending())
		this->scn_->userCreateBody(0.00000000000000000001, this->addBodyStatic_->isOn());
	if(this->addBodyMedium_->clickPending())
		this->scn_->userCreateBody(mediumMass_, this->addBodyStatic_->isOn());
	if(this->addBodyLarge_->clickPending())
		this->scn_->userCreateBody(largeMass_, this->addBodyStatic_->isOn());
}