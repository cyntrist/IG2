#include "Heroe.h"
#include "Block.h"
#include "Pearl.h"
#include "Game.h"

void Heroe::init()
{


}

void Heroe::setScale(Vector3 s)
{
	this->mNode->setScale(s);
}


void Heroe::frameRendered(const Ogre::FrameEvent& evt)
{
	if (!visible) return;
	updateMovement(dir);

}

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_UP) {
		std::cout << "UP " << std::endl;
		setOrientation({0, -1, 0});

		newdir = { 0, 1, 0 };
	}
	else if (evt.keysym.sym == SDLK_RIGHT) {
		std::cout << "RIGHT " << std::endl;
		setOrientation({ -1, 0, 0 });


		newdir = { 1, 0, 0 };

	}	
	else if (evt.keysym.sym == SDLK_DOWN) {
		std::cout << "DOWN " << std::endl;

		setOrientation({ 0, 1,0 });


		newdir = { 0, -1, 0 };

	}	
	else if (evt.keysym.sym == SDLK_LEFT) {
		std::cout << "LEFT " << std::endl;
		setOrientation({ 1, 0, 0 });

		newdir = { -1, 0, 0 };

	}


	return true;
}

void Heroe::updateMovement(Vector3 vec)
{
	if (checkMiddle()) {


		//std::cout << "we're so back " << std::endl;
		/*Block* aux = getBlock(dir);
		if (aux->Type() == Block::TYPE::PEARL) eatPearl(aux);*/
		if (newdir != dir) {

			if (!checkCollision(newdir))
				dir = newdir;
		}

		if (checkCollision(dir)) {
			dir = { 0,0,0 };
		}

	}

	if (checkBlockAABB(Vector3().ZERO)) {
		if(!getBlock(Vector3().ZERO)->isDead())
			eatPearl(getBlock(Vector3().ZERO));
	}


	//std::cout << immune << std::endl;
	if (!immune) 
	{
		if (checkVillainAABB()) {
			getHit();
		}
	}
	else {
		immunity();
	}

	
	
	mNode->translate(dir);
}

bool Heroe::canMove(Vector3 vec)
{
	return checkCollision(vec);
}

Block* Heroe::getBlock(Vector3 dir)
{
	int offsetx = lab->getLabSize().x / lab->getWallSize().x / 2;
	int offsety = lab->getLabSize().y / lab->getWallSize().y / 2;

	int auxx = (getPosition().x) / WALL_LENGTH;
	int auxy = (getPosition().y) / WALL_LENGTH;

	int x = offsetx + trunc(auxx / 5);
	int y = offsety + trunc(auxy / 5);
	//std::cout << "dir x " << dir.x << "dir y " << dir.y << std::endl;


	y += dir.y;
	x += dir.x;

	//string auxt = "NONE";
	//auxt = lab->getLabyrinth()[x][y]->Type();
	//if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::WALL) auxt = "WALL";
	//if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::PEARL) auxt = "PEARL";
	//if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::NONE) auxt = "NONE";
	//std::cout << " TYPE " << auxt << std::endl << std::endl << std::endl;

	return lab->getLabyrinth()[y][x];
}

bool Heroe::checkCollision(Vector3 dir)
{
	bool colisiona = false;

	Block* aux = getBlock(dir);

	////std::cout << "BLOCK " << aux->Type() << std::endl;
	//if (aux->Type() == Block::TYPE::PEARL && getAABB().intersects(aux->getAABB())) {
	//	std::cout << "INTERSECCION " << std::endl;
	//}

	//if (aux->Type() == Block::TYPE::PEARL) eatPearl(aux);

	if (aux == nullptr) colisiona = true;
	if (aux->isPass()) colisiona = false;
	if (!aux->isPass()) colisiona = true;

	return colisiona;
}

bool Heroe::checkMiddle()
{
	int x, y, z;
	x = mNode->getPosition().x;
	y = mNode->getPosition().y;
	z = mNode->getPosition().z;

	//std::cout << x << " " << y << " " << z << std::endl;
	//std::cout << lab->getWallSize().x << " " << lab->getWallSize().y << " " << std::endl;

	int wallx = lab->getWallSize().x/2;
	int wally = lab->getWallSize().y/2;

	Vector3 centro(x % 100, y % 100, z % 100);

	//std::cout << centro << " "  << std::endl;


	//Si todos los numeros son multiplos de 100 esta en un centro
	return centro == Vector3().ZERO;
}

bool Heroe::checkBlockAABB(Vector3 dir)
{
	Block* aux = getBlock(dir);

	//std::cout << aux->getAABB() << std::endl;
	
	bool sol = getAABB().intersects(aux->getAABB());
	return sol;
}

bool Heroe::checkVillainAABB()
{
	bool aux = false;
	int i = 0;
	// recorre los villanos

	while (!aux && i < lab->getVillains().size()) {
		aux = getAABB().intersects(lab->getVillains()[i]->getAABB());
		i++;
	}
	return aux;
}

void Heroe::eatPearl(Block* p)
{
	if (!p->isDead()) {
		// 'borra la perla'
		p->setVisible(false);
		p->setDead(true);
		// puntos
		//
		addPoint(pointValue);
	}
	

}

void Heroe::getHit()
{

	lab->getGame()->addLives(-1);
	startImmunity(200);
	std::cout << lab->getGame()->getLives() << std::endl;

	if (lab->getGame()->getLives() <= 0) {
		//lab->getGame()->changeStage(lab->getGame()->getStage() + 1);
		lab->getGame()->changeStage(-1);
	}
}

void Heroe::startImmunity(int time)
{
	immunityCounter = time;
	immune = true;
}

void Heroe::immunity()
{
	if (immunityCounter <= 0) {
		immunityCounter = 0;
		immune = false;
	}
	else {
		immunityCounter--;
	}

}

void Heroe::addPoint(int i)
{
	puntos += i;
	lab->getGame()->addPoints(i);
}

void Heroe::setLight(Ogre::Light* l)
{
	light = l;
}

Ogre::Light* Heroe::getLight(Ogre::Light l)
{
	return light;
}

void Heroe::initLight(int type)
{
	// crea un nodo hijo del heroe
	light = mSM->createLight("light");
	light->setDiffuseColour(1.0f, 1.0f, 1.0f);

	lightNode = mNode->createChildSceneNode();
	lightNode->attachObject(light);


	// UNA TIENE QUE SER SPOTLIGHT Y LA OTRA DIRECTIONAL
	if (type == 0) {
		light->setType(Light::LT_SPOTLIGHT);
		light->setSpotlightInnerAngle(Ogre::Degree(5.0f));
		light->setSpotlightOuterAngle(Ogre::Degree(45.0f));
		light->setSpotlightFalloff(1.0f);
		light->setDirection(0,-1,0);

	}
	else if (type == 1) {
		light = mSM->createLight();
		light->setType(Light::LT_SPOTLIGHT);
		light->setSpotlightInnerAngle(Ogre::Degree(5.0f));
		light->setSpotlightOuterAngle(Ogre::Degree(45.0f));
		light->setSpotlightFalloff(0.0f);
		light->setDiffuseColour(1.0f, 1.0f, 1.0f);
		light->setDiffuseColour(1.0f, 0.0f, 0.0f);
		light->setDiffuseColour(1.0f, 0.0f, 0.0f);

	}

	//  ------------- debug
	//Block* aux;
	//aux = new Block({ 0,50,0 }, mNode->createChildSceneNode("debugblock"), IG2Object::mSM, PEARL_MESH);
	
	// te amo pinguino debug

	//------------------




	// mete la luz en el nodo
	lightNode->setPosition(0,50,0);
	//lightNode->setDirection(Ogre::Vector3(0,0,-1));
}
