#pragma once

#include "IG2Object.h"
#include "Labyrinth.h"

class Heroe;
using Chelo = Heroe;


/// TO DO LIST:
///
/// 1. input (OgreBites::Keycode)		HECHO
/// 2. leerlo en el parseo (on hold)	HECHO ¿?
/// 3. listener							HECHO
/// 4. movimiento						HECHO
/// 5. colisiones						hechoooooooooooooooooooo

// clase heroe (chelo) 
class Heroe : public IG2Object
{
private:
	// puntos y vidas
	int vidas;
	int puntos;

	int pointValue;

	// direccion actual
	Vector3 dir;
	// direccion nueva
	Vector3 newdir;

	// laberinto
	Labyrinth* lab;

	//
	Light* light;
	SceneNode* lightNode;


public:
	// constructora basica, genera el objeto en el origen
	Heroe() : IG2Object()
	{
		vidas = 3;
		puntos = 0;
	};

	// constructora
	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, Labyrinth* lab_, int p)
		: IG2Object(initPos, node, sceneMng, mesh), pointValue(p), lab(lab_)
	{
		vidas = 3;
		puntos = 0;
	}

	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, int vidas_, int puntos_,
	      Labyrinth* lab_)
		: IG2Object(initPos, node, sceneMng, mesh), vidas(vidas_), puntos(puntos_), lab(lab_)
	{
	}


	void init() override;

	void setScale(Vector3 s);

	// ------------------- METODOS ------------------------

	void frameRendered(const FrameEvent& evt) override;

	// 
	// addInputListener()
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

	// ---------- MOVIMIENTO -------------
	//
	void updateMovement(Vector3 vec);

	// de momento solo en un eje
	// mDragonNode->yaw(Degree(-180));

	// devuelve si se puede mover en esa direccion (si no hay muro con el que colisiona)
	bool canMove(Vector3 vec);

	// detecta las colisiones
	Block* getBlock(Vector3 dir);
	bool checkCollision(Vector3 dir);
	bool checkMiddle();
	bool checkBlockAABB(Vector3 dir);
	bool checkVillainAABB();

	// come una perla
	void eatPearl(Block* p);
	void getHit();

	// añade puntos al score
	void addPoint(int i);

	//
	void setLight(Light* l);
	Light* getLight(Light l);

	void initLight(int type);
};
