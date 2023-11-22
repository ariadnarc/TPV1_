#pragma once

#include "SDL.h"
#include "checkML.h"
#include "GameObject.h"
#include <iostream>
#include "Vector2D.h"

class MotherShip : public GameObject {

	Vector2D<> Aliensdir;

	bool cannotMove = false;

	bool shouldmove = false;

	// enum con los estados, preguntar por cómo funcionan




public:

	//Constructora e initialize por paso de parámetros
	MotherShip(Game* game);
	void Initialize();
	
	//Constructora e initialize por lectura de archivos
	MotherShip(Game* game, std::istream& in);
	void Initialize(std::istream& in);

	// sobresscribe los metodos heredados de GameObject
	void Render() const override {};

	//
	void Update() override;

	//guardado de partida 
	void Save(std::ostream& out)const override;



	// el bool shouldmove se pone a true cuando el tiempo de espera sea igual a cero
	bool ShouldMove() const { return shouldmove; } // por qué es const?



};