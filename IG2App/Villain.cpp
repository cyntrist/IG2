#include "Villain.h"
#include "Labyrinth.h"

void Villain::frameRendered(const FrameEvent& evt)
{

	// lo comento para que no moleste <3 pero con esto se mueven pero no cambain de direccion aun
	// el codigo de colisiones middle y tal es copypaste del heroe
	if (checkMiddle()) {

		// si choca, busca una nueva direccion valida
		if (checkCollisions(dir)) {
			Vector3 aux1 = {dir.y, dir.x, dir.z};
			Vector3 aux2 = -aux1;

			// prueba las direcciones de los lados
			if (checkCollisions(aux1) || checkCollisions(aux2)) {
				// elige la que se acerque mas al player
				if (lab->getHero()->getPosition() < getPosition())
					dir = aux1;
				else
					dir = aux2;

				// esta mal, pero de placeholder sirve
			}
			else {
				// si no tiene direcciones, da la vuelta
				dir = -dir;
			}
		}
	}

	//std::cout << dir << std::endl;

	mNode->translate(dir);

	if (dir == Vector3().ZERO) {
		if (checkCollisions({ 1,0,0 }))
			dir = { 1,0,0 };
		else if (checkCollisions({ -1,0,0 }))
			dir = { -1,0,0 };
	}
}

bool Villain::checkCollisions(Vector3 dir)
{
	bool colisiona = false;

	Block* aux = getB(dir);

	//std::cout << "BLOCK " << aux->Type() << std::endl;
	//if (aux->Type() == Block::TYPE::PEARL && getAABB().intersects(aux->getAABB())) {
	//	std::cout << "INTERSECCION " << std::endl;
	//}

	//if (aux->Type() == Block::TYPE::PEARL) eatPearl(aux);

	if (aux == nullptr) colisiona = true;
	if (aux->isPass()) colisiona = false;
	if (!aux->isPass()) colisiona = true;

	return colisiona;
}

bool Villain::checkMiddle()
{
	int x, y, z;
	x = mNode->getPosition().x;
	y = mNode->getPosition().y;
	z = mNode->getPosition().z;

	Vector3 centro(x % 100, y % 100, z % 100);

	//Si todos los numeros son multiplos de 100 esta en un centro
	return centro == Vector3().ZERO;
}

Block* Villain::getB(Vector3 dir) {
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

	return lab->getLabyrinth()[x][y];


}
