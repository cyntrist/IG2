#pragma once

#include "IG2Object.h"

using Chelo = Heroe;


/// TO DO LIST:
///
/// 1. input (OgreBites::Keycode)
/// 2. leerlo en el parseo (on hold)
/// 3. listener
/// 4. colisiones

// clase heroe (chelo) 
class Heroe : public IG2Object
{
private:

	// puntos y vidas
	int vidas;
	int puntos;
	
	// direccion actual
	Vector3 dir;
	// direccion nueva
	Vector3 newdir;

public:

	// constructora basica, genera el objeto en el origen
	Heroe() : IG2Object() {
		vidas = 3;
		puntos = 0;
	};

	// constructora
	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh)
		: IG2Object(initPos, node, sceneMng, mesh) {
	
		vidas = 3;
		puntos = 0;
	}

	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, int vidas_, int puntos_)
		: IG2Object(initPos, node, sceneMng, mesh), vidas(vidas_), puntos(puntos_) { }


// ------------------- METODOS ------------------------

	// 
	// addInputListener()
	void keypressed(const OgreBites::KeyboardEvent& evt);

	// ---------- MOVIMIENTO -------------
	//
	void updateMovement(Vector3 vec);

	// de momento solo en un eje
	// mDragonNode->yaw(Degree(-180));
	void updateRotation(int degree);

	// devuelve si se puede mover en esa direccion (si no hay muro con el que colisiona)
	bool canMove(Vector3 vec);

	// detecta las colisiones
	bool checkCollision();

	// come una perla
	void eatPearl();

	// añade puntos al score
	void addPoint(int i);

	//


};

